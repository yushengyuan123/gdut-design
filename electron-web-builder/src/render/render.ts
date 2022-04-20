import { createApp } from 'vue'
import App from "./pages/app.vue"
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import router from './router/index'
import store from "./pinia"
import '@/components/Theme/Index.less'
import * as ElementPlusIcons from '@element-plus/icons-vue'
import Icons from '@/components/Icons/Index.vue'
import '@/components/Icons/index'

function registerElementPlusIcons(app) {
  console.log(ElementPlusIcons);
  
  for (const iconName in ElementPlusIcons) {
    app.component(iconName, ElementPlusIcons[iconName])
  }
}

const app = createApp(App)

registerElementPlusIcons(app)

app.component('mo-icons', Icons)
app.use(router)
app.use(ElementPlus)
app.use(store)

app.mount('#app')



// initIndexDb()