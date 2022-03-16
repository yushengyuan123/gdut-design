const { BrowserWindow } = require("electron")

console.log(BrowserWindow)

console.log('用户js入口')

const win = new BrowserWindow()

win.loadURL()

