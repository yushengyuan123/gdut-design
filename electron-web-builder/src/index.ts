const { BrowserWindow, app } = require("electron")
const path = require("path")
const { log } = require('./utils.ts')

console.log('用户js入口caonima')
log()

function createWindow () {
  const win = new BrowserWindow({})
  
  win.loadURL("https://www.google.com")
}

app.whenReady().then(() => {
  createWindow()
})



