"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.deleteSql = exports.selectSql = exports.insertSql = void 0;
const electron_log_1 = __importDefault(require("electron-log"));
const index_1 = require("../../index");
function wrapperBrace(str) {
    return `(` + str + ')';
}
function wrapperInsert(tableName, columns, values) {
    return `insert into ${tableName} ${columns} values ${values}`;
}
function wrapperSelect(tableName, columns, where) {
    if (!where) {
        return `select ${columns} from ${tableName}`;
    }
    return `select ${columns} from ${tableName} where ${where}`;
}
function wrapperDelete(tableName, where) {
    return `delete from ${tableName} where ${where}`;
}
function executeSql(sql) {
    const conInstance = index_1.application.getMysqlConnectObj();
    return new Promise((resolve, reject) => {
        conInstance.query(sql, (err, res) => {
            if (err) {
                electron_log_1.default.error('mysql语句执行失败，失败原因', err);
                reject(false);
            }
            else {
                resolve(res);
            }
        });
    });
}
function wrapperQuote(str) {
    return "'" + str + "'";
}
async function insertSql(tableName, colValues) {
    const len = colValues.length;
    let columnsTemplateString = ``;
    let valuesTemplateString = ``;
    colValues.forEach((item, index) => {
        if (item.value) {
            item.value = wrapperQuote(item.value);
        }
        if (index !== len - 1) {
            columnsTemplateString += item.columns + ',';
            valuesTemplateString += item.value + ',';
        }
        else {
            columnsTemplateString += item.columns;
            valuesTemplateString += item.value;
        }
    });
    columnsTemplateString = wrapperBrace(columnsTemplateString);
    valuesTemplateString = wrapperBrace(valuesTemplateString);
    const sql = wrapperInsert(tableName, columnsTemplateString, valuesTemplateString);
    electron_log_1.default.warn(`execute sql ${sql}`);
    await executeSql(sql);
}
exports.insertSql = insertSql;
async function selectSql(tableName, columns, where) {
    let columnValueStr = ``;
    const len = columns.length;
    columns.forEach((item, index) => {
        if (index !== len - 1) {
            columnValueStr += item + ',';
        }
        else {
            columnValueStr += item;
        }
    });
    if (where) {
        where = wrapperBrace(where);
    }
    const sql = wrapperSelect(tableName, columnValueStr, where);
    electron_log_1.default.warn(`execute sql ${sql}`);
    return await executeSql(sql);
}
exports.selectSql = selectSql;
async function deleteSql(tableName, where) {
    const sql = wrapperDelete(tableName, where);
    electron_log_1.default.warn(`execute sql ${sql}`);
    await executeSql(sql);
}
exports.deleteSql = deleteSql;
//# sourceMappingURL=utils.js.map