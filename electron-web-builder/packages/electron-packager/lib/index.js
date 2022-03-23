"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.packager = void 0;
/**
 * 目标提供两个参数，sourceDir，outputDir
 */
const mac_1 = require("./mac");
class Packager {
    ops;
    constructor(options) {
        this.ops = options;
        this.ops.asar = options.asar || false;
    }
    async createApp() {
        let app;
        const platform = this.ops.platform;
        switch (platform) {
            case 'mac':
                app = new mac_1.default();
                break;
            case 'win':
            default: {
                console.log('暂不支持别的平台打包');
            }
        }
        await app.copyTemplate(this.ops.outputDir);
        await app.addUserDirToElectronApp(this.ops.sourceDir, this.ops.asar);
    }
}
async function packager(options) {
    const packager = new Packager(options);
    await packager.createApp();
}
exports.packager = packager;
//# sourceMappingURL=index.js.map