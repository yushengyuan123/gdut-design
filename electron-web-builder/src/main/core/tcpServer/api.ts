import logger from 'electron-log'
import httpServerConfig from "./config"
const Koa = require('koa')
const Router = require('koa-router')

export default class httpServer {
  private app: any
  private router: any
  
  constructor() {
    this.init()
  }
  
  getRouter() {
    return this.router
  }
  
  getApp() {
    return this.app
  }
  
  init() {
    this.startHttpServer()
    this.initRouter()
  }
  
  startHttpServer() {
    const port = httpServerConfig.port
    this.app = new Koa()
    this.app.listen(port, () => {
      logger.warn('http server start')
    })
  }
  
  initRouter() {
    this.router = new Router()
  }
}