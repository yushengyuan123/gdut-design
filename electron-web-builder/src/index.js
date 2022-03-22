let { BrowserWindow, app } = require("electron")
const path = require("path");

console.log('用户js入口')

function createWindow () {
	const win = new BrowserWindow({})
	
	win.loadURL("https://www.baidu.com")
}

console.log(app)

app.whenReady().then(() => {
	createWindow()
})



