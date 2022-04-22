import type {
  storageItemKey
} from "./types"
import {
  ObjectToString,
  StringToObject
} from "./utils"
import type {
  basicSettings
} from "../pinia/preference"

function setUserPreference<T extends basicSettings = basicSettings>(
  value: T
) {
  setStorage<storageItemKey, T>('preference', value)
}

function setStorage<K extends string = string, R = any>(
  key: K,
  value: R
) {
  let valueString: string = ''
  
  if (typeof value === 'object') {
    valueString = ObjectToString(value)
  } else if (typeof value === "string") {
    valueString = value
  } else if (typeof value === 'number') {
    valueString = value.toString()
  } else {
    console.log('key为其他类型')
  }
  
  localStorage.setItem(key, valueString)
}

function getStorageItem<T extends string = string>(key: T){
  return localStorage.getItem(key)
}

function checkIsExist<R extends string = string>(key: R)  {
  return !!getStorageItem(key)
}

export {
  setStorage,
  setUserPreference,
  checkIsExist,
  getStorageItem
}