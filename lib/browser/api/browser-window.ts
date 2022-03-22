// @ts-ignore
const { WebContents } = process._linkedBinding('electron_browser_web_contents');
const { BrowserWindow } = process._linkedBinding('electron_browser_window')

// @ts-ignore
BrowserWindow.prototype.loadURL = function (url) {
  console.log(this.webContents);
  
  return this.webContents._loadURL(url, {});
}

module.exports = BrowserWindow