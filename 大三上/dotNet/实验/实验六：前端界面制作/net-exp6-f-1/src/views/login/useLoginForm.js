import { ref, reactive } from "vue";
import axios from "@/axios";
import router from "@/routers";

let isLoginError = ref(false);
let loginFailMessage = ref("");
let model = reactive({
    loginToken: "test",
    password: "pwd",
});
let rules = {
    loginToken: [
        { required: true, message: "必须填写用户名/密码/邮箱" },
        { min: 2, max: 16, message: "用户名/密码/邮箱的长度必须在2-16位之间" }
    ],
    password: [
        { required: true, message: '必须填写登录密码' }
    ]
};
let formRef = ref('');
async function onSubmit() {
    formRef.value
        .validate()
        .then(async () => {
            isLoginError.value = false;
            let msg = await axios.post("/api/login", model);
            // console.log(msg);
            if (!msg.success) {
                isLoginError.value = true;
                loginFailMessage.value = msg.msg;
            } else {
                localStorage.setItem("accessToken", msg.token);
                router.push({
                    name: 'user'
                })
            }
        })
        .catch((err) => {
            console.log("valid", err)
        });
}

function useLoginForm () {
    return { 
        isLoginError, 
        loginFailMessage, 
        model, 
        rules, 
        formRef, 
        onSubmit 
    };
}
export default useLoginForm;