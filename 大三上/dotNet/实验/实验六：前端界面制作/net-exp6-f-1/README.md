# .NET平台技术课程 - 实验五

## 介绍
.NET平台课第六课脚手架，本次实验主要介绍了登录页面的制作方法，以及数据实体制作的基本套路。

## 安装教程
### 1. 拿到此代码后，需要执行：
npm i --legacy-peer-deps

### 2. 配置代理
先运行后端代码，然后进入vue.config.js，配置 proxyRemote 。
需要注意的是，这里所有接口都必须是 /api 开头，否则无法转发

### 3. 添加页面
添加页面，并且在router/index.js中添加路由。其中 路由“/”是默认页面。

## 验证手段
在Vue中，表单验证的常用手段是：[async-validator](https://github.com/yiminghe/async-validator)，也可以访问[国内镜像](https://gitee.com/x-github/async-validator)。
验证的基本数据结构是声明一个rules：
rules: {
    '需要验证的字段名': [
        {}, // 验证项1
        {}, // 验证项2
    ] // 这一层是数组
} // 这一层是对象

常用的验证手段是：
必填：{ type: '数据类型', required: true, message: "必须填写该字段" }
数据类型：[参见文档](https://gitee.com/x-github/async-validator#type)
正则验证：{ type: 'string', pattern: '正则表达式', message: '验证失败提示' }
常用的正则表达式：
 * 手机号：^1((34[0-8])|(8\d{2})|(([35][0-35-9]|4[579]|66|7[35678]|9[1389])\d{1}))\d{7}$
 * 电子邮箱：^[a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+$
长度验证：{ type: 'string', min: 0, max: 10, message: '' }
枚举验证：{ type: 'enum', enum: ['admin', 'user', 'guest'] }
函数式验证：
validator (rule, value, callback) {
    // rule 指的是验证的规则，一般不用
    // value 指的是被验证的值
    // callback指的是返回正确以否
    if (value === password.value) {
        callback(); // 验证通过
    } else {
        callback('两次输入的密码必须一致'); // 验证失败，callback的参数是错误提示
    }
}
