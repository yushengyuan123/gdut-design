"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.registerPluginsInWindows = exports.registerPluginsInVue = void 0;
const plugins_1 = __importDefault(require("./plugins"));
const electron_log_1 = __importDefault(require("electron-log"));
const registerPluginsInVue = {
    install(app) {
        plugins_1.default.forEach(item => {
            app.use(item.ctor);
        });
    },
    version: '1.0.0'
};
exports.registerPluginsInVue = registerPluginsInVue;
const registerPluginsInWindows = () => {
    plugins_1.default.forEach(item => {
        electron_log_1.default.info('register electronApi in windows');
        // @ts-ignore
        window[item.name] = item.ctor;
    });
};
exports.registerPluginsInWindows = registerPluginsInWindows;
//# sourceMappingURL=install.js.map