let source = null;
let sender = null;

function login(uname) {
    sender = uname;
    setMessageInnerHTML("登录成功");
    if (!!window.EventSource) {
        source = new EventSource('http://localhost:8080/sse/connect/?uname=' + uname);

        source.addEventListener('message', function (e) {
            setMessageInnerHTML(e.data);
        });

        source.addEventListener('error', function (e) {
            if (e.readyState === EventSource.CLOSED) {
                setMessageInnerHTML("连接关闭");
            } else {
                console.log(e);
            }
        }, false);

    } else {
        setMessageInnerHTML("你的浏览器不支持SSE");
    }

    window.onbeforeunload = function () {
        closeSse();
    };
}

function closeSse() {
    source.close();
    const httpRequest = new XMLHttpRequest();
    httpRequest.open('GET', 'http://localhost:8080/sse/close/?uname=' + sender, true);
    httpRequest.send();
    setMessageInnerHTML("登出成功");
}

function connectWithUser(receiver) {
    $.post(`http://localhost:8080/user/connect?sender=${sender}&receiver=${receiver}`, ()=>{
        setMessageInnerHTML(`开始与${receiver}的聊天`)
    });
}

function listUsers() {
    $.get('http://localhost:8080/user/list', (data)=>{
        setMessageInnerHTML("当前在线用户：" + data)
    });
}

function enterGroup(group) {
    $.post(`http://localhost:8080/group/enter?user=${sender}&group=${group}`, ()=>{
        setMessageInnerHTML(`已加入群聊：${group}`)
    });
}

function connectWithGroup(group) {
    $.post(`http://localhost:8080/group/connect?user=${sender}&group=${group}`, ()=>{
        setMessageInnerHTML(`已连接群聊：${group}`)
    });
}

function listGroup() {
    $.get('http://localhost:8080/group/list', (data)=>{
        setMessageInnerHTML("目前已有群聊：" + data)
    });
}

function sendMessage(content) {
    $.ajax('http://localhost:8080/message/send', {
        type: 'post',
        data: JSON.stringify({sender: sender, content: content}),
        contentType: 'application/json;charset=UTF-8'
    });
}

function saveMessage() {
    $.post(`http://localhost:8080/message/save?uname=${sender}`, ()=>{
        setMessageInnerHTML('存储消息完毕,存储在\"C:\\Users\\86189\\Downloads\\app.txt\"中');
    });
}

function broadcastMessage(content) {
    $.ajax('http://localhost:8080/message/broadcast', {
        type: 'post',
        data: JSON.stringify({sender: sender, content: content}),
        contentType: 'application/json;charset=UTF-8'
    });
}

function baiduTranslate(transContent) {
    $.get(`http://localhost:8080/translate/query?query=${transContent}`, (data)=>{
        setMessageInnerHTML("翻译结果：" + data);
    });
}

function changeTranslate(){
    $.post(`http://localhost:8080/translate/changeTranslate`, (data)=>{
        setMessageInnerHTML('翻译的目标语言切换为：' + data);
    });
}

// 将消息显示在网页上
function setMessageInnerHTML(innerHTML) {
    $('#message')[0].innerHTML += innerHTML + '<br/>';
}

