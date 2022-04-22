import { createRouter, RouteRecordRaw, createWebHashHistory } from "vue-router"
import download from "../pages/download.vue"
import settings from "../pages/settings.vue"
import menuPending from '../pages/Task/menu-pending.vue'
import menuFinish from '../pages/Task/menu-finish.vue'
import baseSettings from '../pages/Preference/base-settings.vue'

const routes: RouteRecordRaw[] = [
  {
    path: '/',
    redirect: '/download'
  },
  {
    path: '/download',
    component: download,
    name: 'download',
    redirect: '/download/finish',
    children: [
      {
        path: 'pending',
        component: menuPending,
        name: 'menu-pending'
      },
      {
        path: 'finish',
        component: menuFinish,
        name: 'menu-finish'
      }
    ]
  },
  {
    path: '/settings',
    component: settings,
    name: 'settings',
    redirect: '/settings/baseSettings',
    children: [
      {
        path: 'baseSettings',
        component: baseSettings,
        name: 'baseSettings'
      }
    ]
  }
]

const router = createRouter({
  // 4. 内部提供了 history 模式的实现。为了简单起见，我们在这里使用 hash 模式。
  history: createWebHashHistory(),
  routes, // `routes: routes` 的缩写
})

export default router