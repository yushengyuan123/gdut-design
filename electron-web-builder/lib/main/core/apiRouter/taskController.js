"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const tcpServer_1 = __importDefault(require("../tcpServer"));
const electron_log_1 = __importDefault(require("electron-log"));
const utils_1 = require("./utils");
const task_1 = require("../database/task");
const taskServices_1 = require("../services/taskServices");
function addTaskRouter() {
    const router = tcpServer_1.default.getRouter();
    router.post('/task/add', async (context) => {
        const taskInfo = context.request.body;
        let res = null;
        try {
            await (0, taskServices_1.taskServices)(taskInfo);
            res = (0, utils_1.setResData)(utils_1.Status.Success, utils_1.Message.success, await (0, task_1.queryAllTaskInfo)());
            electron_log_1.default.warn('创建任务成功', res);
        }
        catch (e) {
            electron_log_1.default.error('创建任务失败,失败原因', e);
            res = (0, utils_1.setResData)(utils_1.Status.Fail, utils_1.Message.error, null);
        }
        context.body = res;
    });
}
function queryAllTaskRouter() {
    const router = tcpServer_1.default.getRouter();
    router.get('/query/task', async (context) => {
        let res = null;
        try {
            electron_log_1.default.warn('正在执行task查询');
            res = (0, utils_1.setResData)(utils_1.Status.Success, utils_1.Message.success, await (0, task_1.queryAllTaskInfo)());
        }
        catch (e) {
            electron_log_1.default.error('创建任务失败,失败原因', e);
            res = (0, utils_1.setResData)(utils_1.Status.Fail, utils_1.Message.error, null);
        }
        context.body = res;
    });
}
function removeTaskRouter() {
    const router = tcpServer_1.default.getRouter();
    router.post('/task/remove', async (context) => {
        const body = context.request.body;
        const taskId = body.taskId;
        let res = null;
        try {
            electron_log_1.default.warn('正在执行task移除操作');
            await (0, task_1.removeTask)(taskId);
            res = (0, utils_1.setResData)(utils_1.Status.Success, utils_1.Message.success, await (0, task_1.queryAllTaskInfo)());
        }
        catch (e) {
            electron_log_1.default.error('创建任务失败,失败原因', e);
            res = (0, utils_1.setResData)(utils_1.Status.Fail, utils_1.Message.error, null);
        }
        context.body = res;
    });
}
const initTaskRouter = async () => {
    electron_log_1.default.warn('register task router');
    addTaskRouter();
    queryAllTaskRouter();
    removeTaskRouter();
};
exports.default = initTaskRouter;
//# sourceMappingURL=taskController.js.map