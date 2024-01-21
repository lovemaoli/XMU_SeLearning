<template>
    <div id="vue-page">
        <word-page id="exp5-2">
            <h1>二、Vue的基本语法</h1>
            <p>
                在本次课程中，每个Vue页面都有如下的基本结构。观察下例，注意每一段的注释的语句的写法。
            </p>
            <highlightjs language="html" :code="code1" />
            <div class="part2-1">
                <h2>
                    2.1 Vue的插值
                </h2>
                <p>
                    在Vue中，有两种插值，一种是使用两个花括号的方法可以在文中<b>{{ text }}</b>一个表达式。在这一行字中，所有加粗的文字都是<b>{{ text }}</b>的。请自行翻看源代码。
                </p>
                <p v-html="para"></p>
                <p>被插入的值如果发生变动，则所有对应位置都会发生变动。试着<a href="javascript:;" @click="toggleText">点击这里</a>查看所有<b>{{ text }}</b>的文字。</p>
                <p>不过，要使用这种特性，所有值都必须使用ref函数包裹。可以试着将变量text的ref删除，看看再点击代码会有什么效果？</p>
                <highlightjs language="javascript" :code="code2" />
            </div>
            <div class="part2-2">
                <h2>
                    2.2 v-if指令
                </h2>
            </div>
            <div class="part2-3">
                <h2>
                    2.3 v-for指令
                </h2>
            </div>
        </word-page>
    </div>
</template>

<script setup>
import { ref, reactive } from 'vue';
document.title = "Vue的基本语法 - .NET平台技术";
let code1 = "<template>\n<!-- 在这里书写HTML代码 -->\n</template>\n<script setup>\n//在这里书写ES代码\n<\/script>\n<style lang=\"less\">\n/* 在这里书写LESS代码 */\n</style>";
let para = "另一种方法是直接html指令插入整段文字，这种方法插入的方法比较凶险，因为字符中会被解释为Html并且被浏览器执行。如果在字符串中有恶意代码，则会被执行。所以除非你可以信任字符串的\
来源，否则不要使用这种方法！由其不能直接将用户的输入使用这种方法插入到页面中。本段文字就是使用这种方法插入的，请自行翻看代码。";

let code2 = `import { ref } from 'vue';
let i = 1;
let textArray = ["Insert", "插入"];
let text = ref(textArray[i]);
function toggleText() {
    i = ++i % 2;
    text.value = textArray[i]; // 绝不能写成 text = textArray[i];
}`;

let i = 1;
let textArray = ["Insert", "插入"];
let text = ref(textArray[i]);
function toggleText() {
    i = ++i % 2;
    text.value = textArray[i];
}

</script>

<style lang="less">
@import "@/assets/word-like.less";
@import "@/assets/paper.less";

#vue-page {
    width: 793px;
    margin: 20px auto;
    color: #000;
    font-size: 16px;
}
</style>