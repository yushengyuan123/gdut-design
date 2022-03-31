"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const electron_1 = require("electron");
const path_1 = __importDefault(require("path"));
const debuggerServerAddr = 'http://localhost:3000/';
class Application {
    singletonBrowser;
    constructor() {
        this.initAppState();
    }
    initAppState() {
        electron_1.app.whenReady().then(() => {
            this.createWindow();
            // this.hiddenTopMenu()
        });
    }
    getMainBrowser() {
        if (!this.singletonBrowser) {
            return null;
        }
        return this.singletonBrowser;
    }
    createWindow() {
        const win = new electron_1.BrowserWindow({
            width: 800,
            height: 600,
            webPreferences: {
                preload: path_1.default.join(__dirname, 'renderPreload.js'),
                contextIsolation: false,
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
}
exports.default = Application;
//# sourceMappingURL=application.js.map