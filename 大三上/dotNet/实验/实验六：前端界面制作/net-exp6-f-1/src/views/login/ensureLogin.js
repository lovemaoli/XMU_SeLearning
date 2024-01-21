import axios from "@/axios";
import router from "@/routers";
import { reactive } from 'vue';
async function ensureLogin () {
    let msg = await axios.post("/api/auth/ValidateLoginState");
    // console.log(msg);
    if (!msg.success) {
        router.push({
            name: 'login'
        });
        return { userName: "" };
    }

    return reactive(msg.currentUser);
}

export default ensureLogin;