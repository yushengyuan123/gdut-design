import { defineStore } from "pinia"

export interface basicSettings {
  appThemeColor: number,
  autoStartup: boolean,
  downloadDefaultDir: string,
  cachePath: string
}

const usePreferenceStore 
  = defineStore<string, basicSettings>({
    id: 'preferenceSettings',
    state: () => {
      return {
        downloadDefaultDir: '/Users/yushengyuan/Downloads',
        appThemeColor: 1,
        cachePath: '',
        autoStartup: false
      }
    },
    actions: {
      updateDownloadPath(newPath: string) {
        this.downloadDefaultDir = newPath
      }
    }
  })

export {
  usePreferenceStore
}