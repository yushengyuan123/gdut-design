"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const events_1 = require("events");
const path_1 = __importDefault(require("path"));
const command_1 = require("./command");
const tcpServer_1 = __importDefault(require("./core/tcpServer"));
const apiRouter_1 = require("./core/apiRouter");
const bodyParser = require('koa-bodyparser');
const debuggerServerAddr = 'http://localhost:3000/';
class Application extends events_1.EventEmitter {
    singletonBrowser;
    appServer;
    constructor() {
        super();
        this.handleEvents();
        this.initAppState();
        this.initBackEndHttpServer();
        this.initApiRouter();
        this.initKoaMiddleWare();
    }
    initAppState() {
        electron_1.app.whenReady().then(() => {
            this.createWindow();
            this.handleIpcMessage();
            // this.hiddenTopMenu()
        });
    }
    handleEvents() {
        command_1.registerCommands.call(this);
    }
    initBackEndHttpServer() {
        this.appServer = tcpServer_1.default;
    }
    initApiRouter() {
        const app = this.appServer.getApp();
        app.use(bodyParser());
        (0, apiRouter_1.registerKoaApiRouter)();
    }
    initKoaMiddleWare() {
        const app = this.appServer.getApp();
        const router = this.appServer.getRouter();
        app.use(router.routes()).use(router.allowedMethods());
    }
    getMainBrowser() {
        if (!this.singletonBrowser) {
            return null;
        }
        return this.singletonBrowser;
    }
    createWindow() {
        const win = new electron_1.BrowserWindow({
            width: 1200,
            height: 600,
            webPreferences: {
                preload: path_1.default.join(__dirname, 'renderPreload.js'),
                contextIsolation: false,
                webSecurity: false
            },
            titleBarStyle: 'hidden'
        });
        this.singletonBrowser = win;
        if (process.env.CUR_MODE == 'debug') {
            win.loadURL(debuggerServerAddr);
        }
        else {
            win.loadFile('index.html');
        }
        win.webContents.openDevTools();
    }
    hiddenTopMenu() {
        electron_1.Menu.setApplicationMenu(null);
    }
    handleIpcMessage() {
        electron_1.ipcMain.on('command', (event, command, ...args) => {
            this.emit(command, ...args);
        });
    }
}
exports.default = Application;
//# sourceMappingURL=application.js.map