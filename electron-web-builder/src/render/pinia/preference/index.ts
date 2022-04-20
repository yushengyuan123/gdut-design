import { defineStore } from "pinia"

export interface basicSettings {
  appThemeColor: THEME_COLOR_VALUE,
  autoStartup: boolean,
  downloadDefaultDir: string,
  cachePath: string
}

export enum THEME_COLOR_VALUE {
  AUTO,
  LIGHT,
  DARK
}

const usePreferenceStore 
  = defineStore({
    id: 'preferenceSettings',
    state: () => {
      return {
        downloadDefaultDir: '/Users/yushengyuan/Downloads',
        appThemeColor: THEME_COLOR_VALUE.DARK,
        cachePath: '',
        autoStartup: false
      }
    },
    getters: {
      getAppThemeColor(state) {
        return state.appThemeColor
      }
    },
    actions: {
      updateDownloadPath(newPath: string) {
        this.downloadDefaultDir = newPath
      },
      updateAppThemeColor(newColor: THEME_COLOR_VALUE) {
        this.appThemeColor = newColor
      }
    }
  })

export {
  usePreferenceStore
}