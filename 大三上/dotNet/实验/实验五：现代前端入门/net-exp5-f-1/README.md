# .NET平台技术课程 - 实验五

## 介绍
.NET平台课第五课脚手架，同时也是之后所有实验的前端脚手架。

## 安装教程
### 1. 拿到此代码后，需要执行：
npm i --legacy-peer-deps

#### 1.1 新建页面需要先在 @/routers/index.js 中添加一条记录，然后再对应的地址中新建页面
#### 1.2 本脚手架仅供实验5使用，之后的实验会在本脚手架的基础上重新扩展，届时需要重新下载

### 2. 上为当前代码指定git远端
git remote add origin <你的git远端地址>
git远端地址指的是例如：https://gitee.com/bluesky234/net-exp5.git 这样的东西
如果使用GitHub则不需要这些，直接点击源代码管理里的“发布Branch”即可

### 3. 调试此代码需要使用：
npm run serve

### 4. 编译此代码需要使用：
npm run build
在生成之后，将dist文件夹的结果放到C#项目的wwwroot下，即可访问