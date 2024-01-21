import { createVNode } from "vue";
import * as Icons from '@ant-design/icons-vue';

export const iconComponents = {};

for (let i in Icons) {
    const ele = Icons[i];
    let name = i.replace(/(?!^)([A-Z])/g, "-$1").toLowerCase();
    iconComponents[name] = ele;
}

const Icon = (props, { attrs }) => {    
    const { icon } = props;
    let com = iconComponents[icon] || Icons[icon];

    if (com) {
        return createVNode(com, attrs);
    } else {
        return createVNode(iconComponents["question-circle-outlined"], attrs);
    }
}

function install (app) {
    app.component("a-icon", Icon);
    for (let key in iconComponents) {
        let com = iconComponents[key];
        app.component(key, (prop, { attrs }) => {
            return createVNode(com, attrs);
        });
    }
}

export default install;