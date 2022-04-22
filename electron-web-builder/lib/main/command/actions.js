"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.getSystemTheme = exports.openFinderFolder = exports.openSysDefaultBrowser = void 0;
const electron_1 = require("electron");
function openSysDefaultBrowser(url) {
    electron_1.shell.openExternal(url);
}
exports.openSysDefaultBrowser = openSysDefaultBrowser;
async function openFinderFolder(filePath) {
    const res = await electron_1.shell.openPath(filePath);
    if (res) {
        electron_1.dialog.showErrorBox('发生错误', res);
    }
}
exports.openFinderFolder = openFinderFolder;
function getSystemTheme() {
    return electron_1.nativeTheme.shouldUseDarkColors;
}
exports.getSystemTheme = getSystemTheme;
//# sourceMappingURL=actions.js.map