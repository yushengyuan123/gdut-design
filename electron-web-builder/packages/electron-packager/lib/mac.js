"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const fs = require("fs-extra");
class MacApp {
    electronAppDir = "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app";
    electronAppRelativePath = "Contents/MacOS/Electron";
    electronResourcePath = "Contents/Resources";
    getElectronAppPath() {
        return path.join(this.electronAppDir, this.electronAppRelativePath);
    }
    getElectronResourcePath() {
        return path.join(this.electronAppDir, this.electronResourcePath);
    }
    async copyTemplate(outputDir) {
        try {
            console.log(this.electronAppDir);
            console.log(outputDir);
            fs.copySync("/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app", '/Users/yushengyuan/yushengyuan/opcua/tests');
        }
        catch (e) {
            throw new Error(e);
        }
    }
    async addUserDirToElectronApp(userDir, isAsar) {
        const electronResourcePath = this.getElectronResourcePath();
        if (!isAsar) {
            try {
                fs.copySync(userDir, electronResourcePath);
            }
            catch (e) {
                throw new Error(e);
            }
        }
        else {
            throw new Error('暂不支持asar打包');
        }
    }
}
exports.default = MacApp;
//# sourceMappingURL=mac.js.map