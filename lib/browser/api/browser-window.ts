const { BrowserWindow, showSaveDialog } = process._linkedBinding('electron_browser_window')


// BrowserWindow.prototype._init = function () {
//   console.log("init函数");
  

// }

// @ts-ignore
BrowserWindow.prototype.loadURL = function (...args) {
  console.log("loadURL ts", args);

  // console.log(this);
  console.log("haha");
  
  console.log(this.webContents);
  console.log("11111");
  
  
  
  
  return this.webContents.loadURL(...args);
}

module.exports = BrowserWindow