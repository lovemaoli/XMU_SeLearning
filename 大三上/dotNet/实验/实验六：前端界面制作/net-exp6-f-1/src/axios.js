import axios from 'axios'
import notification from 'ant-design-vue/es/notification';
import dayjs from 'dayjs';

const maxTimeout = process.env.NODE_ENV === "production" ? 6000 : 99999999;
const request = axios.create({
    timeout: maxTimeout
});

// 异常拦截处理器
const errorHandler = (error) => {
    if (error.response) {
        const data = error.response.data
        if (error.response.status === 403) {
            notification.error({
                message: 'Forbidden',
                description: data.message
            })
        }

        if (error.response.status === 500) {
            notification.error({
                message: '服务器不见了！',
                description: `服务器出现了一些问题，请联系管理员解决，并且附上现在的时间：${dayjs().format("YYYY-M-D H:mm:ss")}。`
            });
            return Promise.reject(`服务器出现了一些问题，请联系管理员解决，并且附上现在的时间：${dayjs().format("YYYY-M-D H:mm:ss")}。`)
        }
    }
    
    return Promise.reject(error)
}

request.interceptors.request.use(req => {
    // 从 localstorage 获取 token
    let requestKey = "accessToken";
    let token = localStorage.getItem(requestKey)
    if (token) {
        req.headers[requestKey] = token;        
    }
    return req;
}, errorHandler);

request.interceptors.response.use(res => {
    return res.data
}, errorHandler);

export default request;
export {
    request as axios
};