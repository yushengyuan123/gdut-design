"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.taskServices = void 0;
const utils_1 = require("../../utils");
const cheerio = require('cheerio');
const electron_log_1 = __importDefault(require("electron-log"));
const utils_2 = require("./utils");
const task_1 = require("../database/task");
// @ts-ignore
const electron_builder_1 = __importDefault(require("../../../../packages/electron-builder"));
async function taskServices(taskInfo) {
    await addBuilderTask(taskInfo);
    const curTime = (0, utils_1.getCurrentDate)();
    let defaultIconPath = 'https://www.electronjs.org//images/favicon.b7a59262df48d6563400baf5671da548.ico';
    try {
        defaultIconPath = await getWebSiteIcon(taskInfo.parseUrl);
    }
    catch (e) {
        electron_log_1.default.error('解析网站图标错误', e);
    }
    await (0, task_1.addTaskInfo)(null, taskInfo.name, taskInfo.parseUrl, defaultIconPath, taskInfo.desc, curTime);
}
exports.taskServices = taskServices;
async function addBuilderTask(receiveData) {
    electron_log_1.default.info('execute add task');
    const name = receiveData.name;
    const outputDir = receiveData.outputDir;
    const url = receiveData.parseUrl;
    await (0, electron_builder_1.default)({
        parseUrl: url,
        outputDir: outputDir,
        appName: name
    });
    electron_log_1.default.info('add task finish');
}
async function getWebSiteIcon(url) {
    const htmlCode = await (0, utils_2.fetch)(url);
    const $ = cheerio.load(htmlCode);
    const linksDomList = $('link');
    let iconPath = '';
    for (let i = 0; i < linksDomList.length; i++) {
        const attrs = linksDomList[i].attribs;
        if (attrs.rel === 'icon' || attrs.rel === 'shortcut icon') {
            iconPath = attrs.href;
            break;
        }
    }
    if (!(0, utils_2.isAbsolutePath)(iconPath)) {
        iconPath = url + iconPath;
    }
    electron_log_1.default.info(`解析到的icon路径为${iconPath}`);
    return iconPath;
}
// CREATE TABLE IF NOT EXISTS `task_info`(
//   `task_id` INT UNSIGNED AUTO_INCREMENT,
//   `task_name` VARCHAR(100) NOT NULL,
//   `task_desc` VARCHAR(100) NOT NULL,
//   `task_status` INT,
//   `task_url` VARCHAR(40) NOT NULL,
//   `task_create_time` VARCHAR(40) NOT NULL,
//   `task_icon_url` VARCHAR(100) NOT NULL,
//   PRIMARY KEY ( `task_id` )
// )
//# sourceMappingURL=taskServices.js.map