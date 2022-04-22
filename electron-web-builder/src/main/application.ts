import { BrowserWindow, app, Menu, ipcMain } from 'electron'
import { EventEmitter } from 'events'
import path from "path"
import { registerCommands } from "./command"
import appServer from "./core/tcpServer"
import logger from 'electron-log'
import {registerKoaApiRouter} from "./core/apiRouter"
import { connectMysql } from "./core/database"
import is from 'electron-is'
import {
  connInstance
} from "./core/database/types"

const bodyParser = require('koa-bodyparser')

const debuggerServerAddr = 'http://localhost:3000/'

process.env['ELECTRON_DISABLE_SECURITY_WARNINGS'] = 'true'

class Application extends EventEmitter {
  private singletonBrowser: BrowserWindow | undefined
  private appServer: any
  private mysqlConnectObj!: connInstance
  
  constructor() {
    super()
    this.handleEvents()
    
    this.initAppState()
    
    this.initBackEndHttpServer()
    
    this.initApiRouter()
    
    this.initKoaMiddleWare()
    
    this.initDataBase()
  }
  
  getMysqlConnectObj(): connInstance {
    return this.mysqlConnectObj
  }
  
  initAppState() {
    app.whenReady().then(() => {
      this.createWindow()
  
      this.handleIpcMessage()
      // this.hiddenTopMenu()
    })
  }
  
  handleEvents() {
    registerCommands.call(this)
  }
  
  initBackEndHttpServer() {
    this.appServer = appServer
  }
  
  initApiRouter() {
    const app = this.appServer.getApp()
    app.use(bodyParser())
    
    registerKoaApiRouter()
  }
  
  initKoaMiddleWare() {
    const app = this.appServer.getApp()
    const router = this.appServer.getRouter()
  
    app.use(router.routes()).use(router.allowedMethods())
  }
  
  initDataBase() {
    this.mysqlConnectObj = connectMysql()
    this.mysqlConnectObj.connect()
  }
  
  getMainBrowser() {
    if (!this.singletonBrowser) {
      return null
    }
    return this.singletonBrowser
  }
  
  createWindow () {
    const win = new BrowserWindow({
      width: 838,
      height: 768,
      webPreferences: {
        preload: path.join(__dirname, 'renderPreload.js'),
        contextIsolation: false,
        webSecurity: !is.dev()
      },
      titleBarStyle: 'hiddenInset',
    })
    
    this.singletonBrowser = win
    
    if (is.dev()) {
      win.loadURL(debuggerServerAddr)
    } else {
      win.loadFile(path.join(__dirname, './dist/index.html'))
    }
    
    if (is.dev()) {
      win.webContents.openDevTools()
    }
  }
  
  hiddenTopMenu() {
    Menu.setApplicationMenu(null)
  }
  
  handleIpcMessage() {
    ipcMain.on('command', (event, command, ...args) => {
      this.emit(command, ...args)
    })
  }
}

export default Application