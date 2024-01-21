const path = require('path')
const webpack = require('webpack')
const buildDate = JSON.stringify(new Date().toLocaleString())
const { defineConfig } = require('@vue/cli-service')

function resolve(dir) {
    return path.join(__dirname, dir)
}

const isProd = process.env.NODE_ENV === 'production'

const useRemote = false;
const proxyRemote = useRemote ? "remote url" : "local url";

const assetsCDN = {
    // webpack build externals
    externals: {
    },
    css: [
        "http://cdn.ricebird.cn/hljs/atom-one-dark.min.css",
    ],
    // https://unpkg.com/browse/vue@2.6.10/
    js: [
    ]
}

// 文档说明 https://webpack.js.org/configuration/dev-server/#staticoptions
const vueConfig = {
    publicPath: process.env.NODE_ENV === "production" ? "/" : "/",
    configureWebpack: {
        // webpack plugins
        plugins: [
            // Ignore all locale files of moment.js
            // new webpack.IgnorePlugin(/^\.\/locale$/, /moment$/),
            new webpack.DefinePlugin({
                APP_VERSION: `"${require('./package.json').version}"`,
                BUILD_DATE: buildDate
            }),
            
        ],
        // if prod, add externals
        externals: assetsCDN.externals
    },
    chainWebpack: config => {
        config.resolve.alias.set('@', resolve('src'))
        config.resolve.alias.set('@v', resolve('src/views'))
        config.resolve.alias.set('@vc', resolve('src/views/cores'))
        config.resolve.alias.set('@vm', resolve('src/views/modules'))

        const svgRule = config.module.rule('svg')
        svgRule.uses.clear()
        svgRule
            .oneOf('inline')
            .resourceQuery(/inline/)
            .use('vue-svg-icon-loader')
            .loader('vue-svg-icon-loader')
            .end()
            .end()
        // .oneOf('external')
        // .use('file-loader')
        // .loader('file-loader')
        // .options({
        //     name: 'assets/[name].[hash:8].[ext]',
        //     esModule: false
        // })

        config.module
            .rule('vue')
            .use('vue-loader')
            .tap((options) => {
                return {
                    ...options,
                    reactivityTransform: true
                }
            })
            
        // if prod is on
        // assets require on cdn
        config.plugin('html').tap(args => {
            args[0].cdn = assetsCDN
            return args
        })
    },
    css: {
        loaderOptions: {
            less: {
                lessOptions: {
                    javascriptEnabled: true,
                    modifyVars: {
                        // less vars，customize ant design theme
                        // 'blue-base': '#003a88',
                        // 'red-base': '#d74024'
                    },
                }
            }
        }
    },
    devServer: {
        // development server port 8000
        port: 8000,
        // 配置静态文件
        // https://webpack.js.org/configuration/dev-server/#staticoptions
        static: {
            directory: resolve("../static"), // 这个是静态文件的本地目录
            publicPath: "/static" // 映射到的虚拟目录
        },
        // If you want to turn on the proxy, please remove the mockjs /src/main.jsL11
        // proxy: {
        //   '/api': {
        //     target: 'https://mock.ihx.me/mock/5baf3052f7da7e07e04a5116/antd-pro',
        //     ws: false,
        //     changeOrigin: true
        //   }
        // }
        // proxy: {
        //     "/api": {
        //         target: `http://${proxyRemote}`, //"http://localhost:2034", // 
        //         changeOrigin: true
        //     },
        //     "/signalr": {
        //         target: `ws://${proxyRemote}`, //"ws://localhost:2034", // 
        //         changeOrigin: true,
        //         ws: true
        //     },
        //     "/debug": {
        //         target: `http://${proxyRemote}`, //"http://localhost:2034", // 
        //         changeOrigin: true
        //     },
        //     "/permanent": {
        //         target: `http://${proxyRemote}`, //"http://localhost:2034", // 
        //         changeOrigin: true
        //     },
        // }
    },
    // disable source map in production
    productionSourceMap: false,
    lintOnSave: undefined,
    // babel-loader no-ignore node_modules/*
    transpileDependencies: []
}

module.exports = defineConfig(vueConfig);

