"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.addTaskInfo = void 0;
const index_1 = require("../../../index");
function addTaskInfo() {
    const conInstance = index_1.application.getMysqlConnectObj();
    const columnValue = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', 'task_create_time'];
    const insertValue = [];
    columnValue.forEach(colName => {
        insertValue.push({
            columns: colName,
            value: '321'
        });
    });
    conInstance.insert('task_info', insertValue, []);
}
exports.addTaskInfo = addTaskInfo;
//# sourceMappingURL=index.js.map