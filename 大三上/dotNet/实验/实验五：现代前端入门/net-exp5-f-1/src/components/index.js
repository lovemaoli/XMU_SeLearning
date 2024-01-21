import WordPage from './word-page.vue'
import hljs from './highlight.js'
export default {
    install (app) {
        app.component("word-page", WordPage);
        hljs(app);
    }
}