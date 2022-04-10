import { createApp } from 'vue'
import App from "./pages/app.vue"
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import router from './router/index'
import store from "./pinia"
import { initIndexDb } from "./indexDB"

const app = createApp(App)

app.use(router)
app.use(ElementPlus)
app.use(store)

app.mount('#app')

// initIndexDb()