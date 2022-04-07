"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.addBuilderTask = void 0;
const electron_log_1 = __importDefault(require("electron-log"));
// @ts-ignore
const electron_builder_1 = __importDefault(require("../../../packages/electron-builder"));
async function addBuilderTask(receiveData) {
    electron_log_1.default.info('execute add task');
    const name = receiveData.name;
    const outputDir = receiveData.outputDir;
    const url = receiveData.parseDir;
    await (0, electron_builder_1.default)({
        parseUrl: url,
        outputDir: outputDir,
        appName: name
    });
    electron_log_1.default.info('add task finish');
}
exports.addBuilderTask = addBuilderTask;
//# sourceMappingURL=actions.js.map