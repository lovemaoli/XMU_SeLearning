
<template>
    <div id="userLayout" class="user-layout-wrapper">
        <div class="container">
            <div class="user-layout-content">
                <div class="top">
                    <div class="header">
                        <a href="/">
                            <img src="@/assets/images/xmu-logo.svg" class="logo" alt="logo">
                            <span class="title">实验六</span>
                        </a>
                    </div>
                    <div class="desc">
                        实验六讲述了制作登录和实体的增删查改的基本套路。
                    </div>
                </div>

                <!-- 登录页面的本体：开始 -->
                <div class="main">
                    <a-form id="formLogin" class="user-layout-login" ref="formRef" :rules="rules" :model="model">
                        <a-tabs activeKey="tab1" :tabBarStyle="{ textAlign: 'center', borderBottom: 'unset' }">
                            <a-tab-pane key="tab1" tab="账号密码登录">
                                <a-alert v-if="isLoginError" type="error" showIcon style="margin-bottom: 24px;"
                                    :message="loginFailMessage" />
                                <a-form-item name="loginToken">
                                    <a-input size="large" type="text" placeholder="请输入用户名/手机号/电子邮箱" v-model:value="model.loginToken">
                                        <template #prefix>
                                            <user-outlined :style="{ color: 'rgba(0,0,0,.25)' }" />
                                        </template>
                                    </a-input>
                                </a-form-item>

                                <a-form-item name="password">
                                    <a-input-password size="large" placeholder="请输入密码" v-model:value="model.password">
                                        <template #prefix>
                                            <lock-outlined :style="{ color: 'rgba(0,0,0,.25)' }" />
                                        </template>
                                    </a-input-password>
                                </a-form-item>
                            </a-tab-pane>
                        </a-tabs>

                        <a-form-item style="margin-top:24px">
                            <a-button size="large" htmlType="submit" class="login-button" type="primary"
                                @click="onSubmit">使用账号密码登录</a-button>
                        </a-form-item>
                    </a-form>
                </div>
                <!-- 登录页面的本体：结束 -->

                <div class="footer">
                    <div class="copyright">
                        &copy; <a target="_blank" href="javascript:;">版权声明信息</a>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script setup>
import useLoginForm from './useLoginForm'
let { isLoginError, loginFailMessage, model, rules, formRef, onSubmit } = useLoginForm();
</script>

<style lang="less">
@import "@/global.less";

#userLayout.user-layout-wrapper {
    height: 100%;
    background-color: @blue-1;

    &.mobile {
        .container {
            .main {
                max-width: 368px;
                width: 98%;
            }
        }
    }

    .container {
        width: 100%;
        min-height: 100%;
        background: #f0f2f5 url(~@/assets/images/background.svg) no-repeat 50%;
        background-size: 100%;
        //padding: 50px 0 84px;
        position: relative;

        .user-layout-lang {
            width: 100%;
            height: 40px;
            line-height: 44px;
            text-align: right;

            .select-lang-trigger {
                cursor: pointer;
                padding: 12px;
                margin-right: 24px;
                display: inline-flex;
                align-items: center;
                justify-content: center;
                font-size: 18px;
                vertical-align: middle;
            }
        }

        .user-layout-content {
            padding: 72px 0 24px;

            .top {
                text-align: center;

                .header {
                    height: 44px;
                    line-height: 44px;

                    .badge {
                        position: absolute;
                        display: inline-block;
                        line-height: 1;
                        vertical-align: middle;
                        margin-left: -12px;
                        margin-top: -10px;
                        opacity: 0.8;
                    }

                    .logo {
                        height: 44px;
                        vertical-align: top;
                        margin-right: 16px;
                        border-style: none;
                    }

                    .title {
                        font-size: 33px;
                        color: rgba(0, 0, 0, .85);
                        font-family: Avenir, 'Helvetica Neue', Arial, Helvetica, sans-serif;
                        font-weight: 600;
                        position: relative;
                        top: 2px;
                    }
                }

                .desc {
                    font-size: 14px;
                    color: rgba(0, 0, 0, 0.45);
                    margin-top: 12px;
                    margin-bottom: 40px;
                }
            }

            .main {
                min-width: 260px;
                width: 368px;
                margin: 0 auto;
            }

            .footer {
                // position: absolute;
                width: 100%;
                bottom: 0;
                padding: 0 16px;
                margin: 48px 0 24px;
                text-align: center;

                .links {
                    margin-bottom: 8px;
                    font-size: 14px;

                    a {
                        color: rgba(0, 0, 0, 0.45);
                        transition: all 0.3s;

                        &:not(:last-child) {
                            margin-right: 40px;
                        }
                    }
                }

                .copyright {
                    color: rgba(0, 0, 0, 0.45);
                    font-size: 14px;
                }
            }
        }

        a {
            text-decoration: none;
        }

    }
}
</style>