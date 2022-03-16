export const browserModuleList: ElectronInternal.ModuleEntry[] = [
  { name: 'app', loader: () => require('./app') },
  { name: 'BrowserWindow', loader: () => require('./browser-window') },
]