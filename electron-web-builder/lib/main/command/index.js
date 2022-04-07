"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.registerCommands = exports.commandSorts = void 0;
const commandLIst_1 = require("./commandLIst");
const electron_log_1 = __importDefault(require("electron-log"));
function registerCommands() {
    commandLIst_1.builderCommandLists.forEach((commands) => {
        electron_log_1.default.info('listening events ', commands.command);
        this.on(commands.command, commands.action);
    });
}
exports.registerCommands = registerCommands;
var commandTypes_1 = require("./commandTypes");
Object.defineProperty(exports, "commandSorts", { enumerable: true, get: function () { return commandTypes_1.commandSorts; } });
//# sourceMappingURL=index.js.map