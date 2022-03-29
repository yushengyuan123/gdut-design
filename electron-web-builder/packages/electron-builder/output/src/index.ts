import { BrowserWindow, app } from 'electron'
import { BuildConfig } from "./helpers/helpers"

const buildConfigInfo = new BuildConfig()

function createWindow () {
  const win = new BrowserWindow({})
  const config = buildConfigInfo.getFileContent()
  
  win.loadURL(config.parseUrl)
}

app.whenReady().then(() => {
  createWindow()
})
