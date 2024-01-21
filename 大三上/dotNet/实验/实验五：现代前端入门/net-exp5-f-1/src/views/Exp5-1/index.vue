<template>
    <word-page id="exp5-1">
        <h1>实验一：ES10的基本语法</h1>
        <p>
            ES10的语法与C语言基本相同，均可以分为声明语句，表达式语句，条件语句和循环语句。也同样有数组，函数和对象的概念。只不过在声明这些主体时，使用的语法与C和C#均有不同。
            另外，由于ES10经常使用于浏览器中，所以其没有一般意义上的main函数，也没有一般意义上的控制台。这使其输入和输出与一般语句不同。
        </p>
        <div class="part1-1">
            <h2>
                1.1 声明语句
            </h2>
            <p>
                ES10的声明语句使用var, let, const三个关键字。其中，var和let语句声明的是变量，只不过let语句声明的变量只能在当前语句体中使用。在一般情况下，都使用
                let定义变量。请看下例：
            </p>
            <highlightjs language="javascript" :code="code1" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code1)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>ES是一种弱类型语言，即该门语言的变量可以接受任何类型的值，请看下例：</p>
            <highlightjs language="javascript" :code="code2" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code2)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>
                数组的声明使用方括号包裹，对象的声明使用花括号包裹。与一般的面向对象语言不同，ES10的对象是键值对，对Python中的字典类似。但在键值对中，值可以是一个函数，当其值为函数时，
                就可以视为C#中的成员函数。其值为变量时，视为成员变量。
            </p>
            <highlightjs language="javascript" :code="code3" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code3)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>函数的声明有两种形式，一种是Lambda表达式，另一种是使用function关键字。请看下例：</p>
            <highlightjs language="javascript" :code="code4" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code4)" href="javascript:;"> 点此运行上例</a>
            </p>
        </div> <!-- 1.1 声明语句 -->
        <div class="part1-2">
            <h2>
                1.2 表达式
            </h2>
            <p>在ES10中，表达式基本于C语言相同。无论是操作符或者是优先级，都没有太大的区别。只有一个运算符需要特别注意，即比较运算符“==”和全等运算符“===”。</p>
            <p>由于ES是弱类型语言，所以两种类型不同的变量可以放在一起比较。同时ES有特别规定，对于数字，number型和string型只要表达的意义相同，则判定为相同。如下例：</p>
            <highlightjs language="javascript" :code="code5" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code5)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>
                但在实际生产过程中，这种判断是模糊的，不准确的。所以，需要使用全等运算符“===”。这种运算符要求变量的类型和数值全部相同。
                因此，在平时的编程过程中，如果没有特殊必要，尽可能的使用“===”而不是比较运算符可以减少BUG的产生。
            </p>
            <highlightjs language="javascript" :code="code6" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code6)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>比较运算符和全等运算符的逆运算符是“!=”和“!==”。它们之间有如下等价关系：</p>
            <ul class="img-area">
                <li>x != y 等价于 !(x == y)</li>
                <li>x !== y 等价于 !(x === y)</li>
                <li>注：!== 是两个等号，不要写成 !===</li>
            </ul>
            <p>
                与C语言相同的是，在ES10的条件语句中，除了可以直接使用布尔值以外，还可以使用非0等值表示真。这时，将所有无法通过if语句的
                值称为非真值（falsy）。有以下非真值需要记忆：
            </p>
            <highlightjs language="javascript" :code="code7" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code7)" href="javascript:;"> 点此运行上例</a>
            </p>
            <p>
                与C#相同的是，ES10也有插值字符串的写法。通过``将字符串包裹起来，就可以在其中使用${}进行插值。如下例：
            </p>
            <highlightjs language="javascript" :code="code8" />
            <p class="img-area">
                按下F12呼出控制端，<a @click="runExp(code8)" href="javascript:;"> 点此运行上例</a>
            </p>
        </div><!-- 表达式 -->

    </word-page>
</template>

<script setup>
let code1 = `let e1 = 1;
if (e1 == 1) {
    let e2 = 2;
    console.log(e1, e2); // 输出 1 2
}
console.log(e1); // 输出 1。修改此代码，使其输出e2会报错`;

let code2 = `let e1 = 1;
console.log(e1, typeof(e1)); // 1 'number'
e1 = 'abc' // 在ES中，没有字符串和字符型的区别。
console.log(e1, typeof(e1)); // abc string
e1 = "abc" // 无论单引号包裹还是双引号包裹，都是字符串！
console.log(e1, typeof(e1)); // abc string
e1 = 1.1 // number可以表示所有类型的数字
console.log(e1, typeof(e1)); // 1.1 'number'`;

let code3 = `let array = [1, 'abc', "abc", 1.1];
console.log(array); // 弱类型语言，每一个元素的类型都可不同
let key2 = 'k2';
let object = {
    k1: 'v1', // k1是键，v1是值
    [key2]: 1 // 键名可以是变量
}
console.log(object);
console.log(object.k1); // 读取键的方法
console.log(object[key2]); //读取键的方法2`;

let code4 = `let f = x => x + 1;
console.log(f(1)); // lambda表达式或者匿名函数必须先定义后使用
console.log(g(1)); // 使用function表达式声明函数可以先使用后定义
function g (y) {
    return y + 1;
}`;

let code5 = `console.log('12' == 12); // 意义相同，则返回真`;
let code6 = `console.log('12' === 12); // 类型不同，返回为假`;
let code7 = `let falsy = [false, 0, '', null, undefined, NaN];
for (let ele of falsy){
    let str = ele ? 'truly' : 'falsy';
    console.log(ele + " is " + str);
}`;

let code8 = "let falsy = [false, 0, '', null, undefined, NaN];\n\
for (let ele of falsy){\n\
    console.log(`${ele} is ${ele ? 'truly' : 'falsy'}`);\n\
}"; // 注：使用双引号包裹的字符串，在每一行的结尾加上 \ 表示字符串还未结束，下一行继续
// 使用这种方法时，不会默认加换行符。所以需要手动加 \n
// 使用插值字符串时，则默认有多行字符串的功效，不需要手动加 \，也会自动加\n如前面的例子。

function runExp(code) {
    eval(code); // 运行字符串形式的ES代码
}
</script>

<style lang="less"></style>