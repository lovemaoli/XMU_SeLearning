<template>
    <a-config-provider :locale="zhCN">
        <Suspense>
            <a-app>
                <div id="app-container">
                    <router-view />
                </div>
            </a-app>
        </Suspense>
    </a-config-provider>
</template>

<script setup>
import { ConfigProvider } from "ant-design-vue";
import zhCN from "ant-design-vue/es/locale/zh_CN";

ConfigProvider.config({
    locale: zhCN
});
</script>

<style lang="less">
@import "@/assets/main.less";
</style>