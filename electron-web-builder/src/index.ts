const { BrowserWindow, app } = require("electron")
const path = require("path")

console.log('用户js入口caonima')

function createWindow () {
  const win = new BrowserWindow({})
  
  win.loadURL("https://www.google.com")
}

console.log(app)

app.whenReady().then(() => {
  createWindow()
})



