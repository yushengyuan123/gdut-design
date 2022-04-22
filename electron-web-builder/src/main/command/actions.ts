import {
  shell,
  nativeTheme,
  dialog
} from 'electron'

function openSysDefaultBrowser(url: string) {
  shell.openExternal(url)
}

async function openFinderFolder(filePath: string) {
  const res = await shell.openPath(filePath)
  if (res) {
    dialog.showErrorBox('发生错误', res)
  }
}

function getSystemTheme() {
  return  nativeTheme.shouldUseDarkColors
}

export {
  openSysDefaultBrowser,
  openFinderFolder,
  getSystemTheme
}