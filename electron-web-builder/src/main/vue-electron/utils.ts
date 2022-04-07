import type { AppContext, Plugin, App } from 'vue'

export type FnWithInstall<T> = T & Plugin

export type FnInstallWithContext<T> = FnWithInstall<T> & {
  _context: AppContext | null
}

export const makeInstaller = <T>(fn: T, name: string) => {
  (fn as FnWithInstall<T>).install = (app: App) => {
    (fn as FnInstallWithContext<T>)._context = app._context
    app.config.globalProperties[name] = fn
  }
  return fn as FnInstallWithContext<T>
}