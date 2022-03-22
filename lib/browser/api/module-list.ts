export const browserModuleList: ElectronInternal.ModuleEntry[] = [
  { name: 'app', loader: () => require('./app') },
  { name: 'BrowserWindow', loader: () => require('./browser-window') },
  { name: 'View', loader: () => require('./view') },
  { name: 'WebContentsView', loader: () => require('./web-contents-view') },
  { name: 'webContents', loader: () => require('./web-contents') },
]