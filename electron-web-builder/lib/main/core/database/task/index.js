"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.removeTask = exports.queryAllTaskInfo = exports.addTaskInfo = void 0;
const index_1 = require("../../../index");
const utils_1 = require("../utils");
async function addTaskInfo(task_id, task_name, task_url, task_icon_url, task_desc, task_create_time) {
    if (!task_desc.trim()) {
        task_desc = `${task_name}桌面端应用`;
    }
    const conInstance = index_1.application.getMysqlConnectObj();
    const columnValueMap = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', "task_status", 'task_create_time'];
    const valuesArr = [task_id, task_name, task_url, task_icon_url, task_desc, 1, task_create_time];
    const insertValueMap = [];
    columnValueMap.forEach((colName, index) => {
        insertValueMap.push({
            columns: colName,
            value: valuesArr[index]
        });
    });
    await conInstance.insert('task_info', insertValueMap);
}
exports.addTaskInfo = addTaskInfo;
async function queryAllTaskInfo() {
    const conInstance = index_1.application.getMysqlConnectObj();
    const columns = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', 'task_create_time'];
    const res = await conInstance.select('task_info', columns, null);
    return res;
}
exports.queryAllTaskInfo = queryAllTaskInfo;
async function removeTask(taskId) {
    await (0, utils_1.deleteSql)('task_info', `task_id = ${taskId}`);
}
exports.removeTask = removeTask;
//# sourceMappingURL=index.js.map