import WordPage from './word-page.vue'
import hljs from './highlight.js'
import icon from './Icons'
export default {
    install (app) {
        app.component("word-page", WordPage);
        hljs(app);
        icon(app);
    }
}