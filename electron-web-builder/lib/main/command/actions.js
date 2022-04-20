"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.openFinderFolder = exports.openSysDefaultBrowser = void 0;
const electron_1 = require("electron");
function openSysDefaultBrowser(url) {
    electron_1.shell.openExternal(url);
}
exports.openSysDefaultBrowser = openSysDefaultBrowser;
function openFinderFolder(filePath) {
    electron_1.shell.showItemInFolder(filePath);
}
exports.openFinderFolder = openFinderFolder;
//# sourceMappingURL=actions.js.map