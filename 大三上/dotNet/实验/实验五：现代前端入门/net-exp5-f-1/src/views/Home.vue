<template>
    <div id="home">
        <div class="page-wrapper" id="introduce">
            <div class="page-div">
                <h1>一、初见现代前端</h1>
                <p>
                    现代前端是一种依托于Html5 + CSS3 + ES的前端技术。其中，Html5是一种标签化的语言，本实验所有页面均使用Html5技术制作；CSS3是描述Html5标签显示样式的语言，
                    不过单纯的CSS并不好用，所以本次使用的是CSS的超集：LESS技术；ES指的是ECMA Script，其前身是Javascript。本次课程使用的语言版本是2019年制定的ES10。
                </p>
                <p>
                    由于选用了ES10技术，所以可以使用ES庞大的生态环境。正确的使用环境中已经存在的框架，前端库等可以有效的缩短开发时间。本次使用的前端框架是
                    <a href="https://vuejs.org/guide/introduction.html"
                        target="_blank">Vue</a>，该框架的中文文档页面暂时无法访问，翻阅时请做好心理准备。本次实验使用的前端框架是
                    <a href="https://www.antdv.com/components/overview-cn/"
                        target="_blank">Antdv</a>，该框架是由蚂蚁金融开发的Ant-design框架修改而来，适用于我国各大信息系统。
                </p>
                <p>
                    本次实验包括以下内容：
                </p>
                <ul>
                    <li>
                        <a href="#exp5-1">
                            1. 学习ES10的基本语法；
                        </a>
                    </li>
                    <li>
                        <a href="/vue" target="_blank">
                            2. 学习Vue的基本语法；
                        </a>
                    </li>
                    <li>
                        <a href="javascript:;">
                            3. 学习使用Antdv的组件。
                        </a>
                    </li>
                </ul>
            </div>
        </div>
        <exp1></exp1>
        <a-back-top />
    </div>
</template>

<script setup>
import Exp1 from './Exp5-1';
</script>

<style lang="less">
@import "@/assets/word-like.less";
@import "@/assets/paper.less";

#home {
    width: 793px;
    margin: 20px auto;
    color: #000;
    font-size: 16px;
}
</style>