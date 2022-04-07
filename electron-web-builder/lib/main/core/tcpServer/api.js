"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const electron_log_1 = __importDefault(require("electron-log"));
const config_1 = __importDefault(require("./config"));
const Koa = require('koa');
const Router = require('koa-router');
class httpServer {
    app;
    router;
    constructor() {
        this.init();
    }
    getRouter() {
        return this.router;
    }
    getApp() {
        return this.app;
    }
    init() {
        this.startHttpServer();
        this.initRouter();
    }
    startHttpServer() {
        const port = config_1.default.port;
        this.app = new Koa();
        this.app.listen(port, () => {
            electron_log_1.default.warn('http server start');
        });
    }
    initRouter() {
        this.router = new Router();
    }
}
exports.default = httpServer;
//# sourceMappingURL=api.js.map