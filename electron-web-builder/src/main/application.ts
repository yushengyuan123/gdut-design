import { BrowserWindow, app, Menu } from 'electron'
import path from "path"

const debuggerServerAddr = 'http://localhost:3000/'

class Application {
  private singletonBrowser: BrowserWindow | undefined
  
  constructor() {
    this.initAppState()
  }
  
  initAppState() {
    app.whenReady().then(() => {
      this.createWindow()
      // this.hiddenTopMenu()
    })
  }
  
  getMainBrowser() {
    if (!this.singletonBrowser) {
      return null
    }
    return this.singletonBrowser
  }
  
  createWindow () {
    const win = new BrowserWindow({
      width: 800,
      height: 600,
      webPreferences: {
        preload: path.join(__dirname, 'renderPreload.js'),
        contextIsolation: false,
      },
      titleBarStyle: 'hidden'
    })
    
    this.singletonBrowser = win
    
    if (process.env.CUR_MODE == 'debug') {
      win.loadURL(debuggerServerAddr)
    } else {
      win.loadFile('index.html')
    }
    
    win.webContents.openDevTools()
  }
  
  hiddenTopMenu() {
    Menu.setApplicationMenu(null)
  }
}

export default Application