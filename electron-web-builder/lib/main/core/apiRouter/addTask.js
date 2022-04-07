"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const tcpServer_1 = __importDefault(require("../tcpServer"));
const electron_log_1 = __importDefault(require("electron-log"));
// @ts-ignore
const electron_builder_1 = __importDefault(require("../../../../packages/electron-builder"));
const utils_1 = require("./utils");
const initTaskRouter = () => {
    const router = tcpServer_1.default.getRouter();
    electron_log_1.default.warn('register task router');
    router.post('/task/add', async (context) => {
        const taskInfo = context.request.body;
        let res = null;
        try {
            await addBuilderTask(taskInfo);
            res = (0, utils_1.setResData)(utils_1.Status.Success, utils_1.Message.success, null);
            electron_log_1.default.warn('创建任务成功', res);
        }
        catch (e) {
            electron_log_1.default.error('创建任务失败,失败原因', e);
            res = (0, utils_1.setResData)(utils_1.Status.Fail, utils_1.Message.error, null);
        }
        context.body = res;
    });
};
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
exports.default = initTaskRouter;
//# sourceMappingURL=addTask.js.map