const { BrowserWindow } = process._linkedBinding('electron_browser_window') 

BrowserWindow.prototype.loadURL = function () {
  console.log('输入loadUrl')
}

module.exports = BrowserWindow