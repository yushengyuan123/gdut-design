"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.selectSql = exports.insertSql = void 0;
const electron_log_1 = __importDefault(require("electron-log"));
function wrapperBrace(str) {
    return `(` + str + ')';
}
function wrapperInsert(tableName, columns, values, where) {
    return `insert into ${tableName} ${columns} values ${values} where ${where}`;
}
function insertSql(tableName, colValues, where) {
    const len = colValues.length;
    let columnsTemplateString = ``;
    let valuesTemplateString = ``;
    colValues.forEach((item, index) => {
        if (index !== len - 1) {
            columnsTemplateString += item.columns + ',';
            valuesTemplateString += item.columns + ',';
        }
        else {
            columnsTemplateString += item.columns;
            valuesTemplateString += item.columns;
        }
    });
    columnsTemplateString = wrapperBrace(columnsTemplateString);
    valuesTemplateString = wrapperBrace(valuesTemplateString);
    const sql = wrapperInsert(tableName, columnsTemplateString, valuesTemplateString, where);
    electron_log_1.default.warn(`execute sql $sql`);
    return sql;
}
exports.insertSql = insertSql;
function selectSql() {
}
exports.selectSql = selectSql;
//# sourceMappingURL=utils.js.map