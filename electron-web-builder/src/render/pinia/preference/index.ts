import { defineStore } from "pinia"
import {
  checkIsExist,
  setUserPreference,
  getStorageItem
} from "../../storage"
import {
  StringToObject
} from "../../storage/utils"
import {
  storageItemKey
} from "../../storage/types"

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

function initState() {
  const stateString = getStorageItem<storageItemKey>('preference')
  if (!stateString) {
    const defaultState = {
      downloadDefaultDir: '/Users/yushengyuan/yushengyuan/tests',
      appThemeColor: THEME_COLOR_VALUE.DARK,
      cachePath: '/Users/yushengyuan/yushengyuan/tests/dist',
      autoStartup: false
    }
    setUserPreference(defaultState)
    return defaultState
  }
  return StringToObject<basicSettings>(stateString)
}

const usePreferenceStore 
  = defineStore({
    id: 'preferenceSettings',
    state: () => {
      return initState()
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
      },
      updateStartupSet(status: boolean) {
        this.autoStartup = status
      },
      updateCachePath(newCachePath: string) {
        this.cachePath = newCachePath
      }
    }
  })

export {
  usePreferenceStore
}