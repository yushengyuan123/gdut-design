import type {App} from 'vue'
import pluginsArr from "./plugins"
import logger from 'electron-log'

const registerPluginsInVue = {
  install(app: App) {
    pluginsArr.forEach(item => {
      app.use(item.ctor)
    })
  },
  version: '1.0.0'
}

const registerPluginsInWindows = () => {
  pluginsArr.forEach(item => {
    logger.info('register electronApi in windows')
    // @ts-ignore
    window[item.name] = item.ctor
  })
}

export {
  registerPluginsInVue,
  registerPluginsInWindows
}


