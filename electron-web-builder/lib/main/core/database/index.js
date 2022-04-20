"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.initSqlTemplate = exports.connectMysql = void 0;
// @ts-ignore
const mysql_1 = require("mysql");
const electron_log_1 = __importDefault(require("electron-log"));
const config_1 = __importDefault(require("./config"));
const utils_1 = require("./utils");
function connectMysql() {
    electron_log_1.default.info('连接数据库');
    const sqlTpl = {
        'insert': utils_1.insertSql,
        'select': utils_1.selectSql
    };
    const con = (0, mysql_1.createConnection)({
        host: config_1.default.host,
        user: config_1.default.user,
        password: config_1.default.password,
        database: config_1.default.database
    });
    initSqlTemplate(con, sqlTpl);
    return con;
}
exports.connectMysql = connectMysql;
function initSqlTemplate(connectInstance, sqlTemplateFunc) {
    for (const key in sqlTemplateFunc) {
        // @ts-ignore
        connectInstance[key] = sqlTemplateFunc[key];
    }
}
exports.initSqlTemplate = initSqlTemplate;
//# sourceMappingURL=index.js.map