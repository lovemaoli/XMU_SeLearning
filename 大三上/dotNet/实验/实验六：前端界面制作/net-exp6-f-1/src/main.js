import { createApp } from 'vue';
import Antd from 'ant-design-vue';
import App from './App';
import router from './routers';
import components from './components';

const app = createApp(App);

app.use(Antd);
app.use(router);
app.use(components);
app.mount("#app");