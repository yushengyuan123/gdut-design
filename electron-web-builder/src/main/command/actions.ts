import {
  shell
} from 'electron'

function openSysDefaultBrowser(url: string) {
  shell.openExternal(url)
}

function openFinderFolder(filePath: string) {
  shell.showItemInFolder(filePath)
}

export {
  openSysDefaultBrowser,
  openFinderFolder
}