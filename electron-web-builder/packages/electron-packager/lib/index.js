"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.packager = void 0;
/**
 * 目标提供两个参数，sourceDir，outputDir
 */
const mac_1 = require("./mac");
const download = require("./download");
const extract = require("extract-zip");
const fs = require("fs-extra");
const path = require("path");
class Packager {
    ops;
    useAdvanceOps;
    constructor(options) {
        this.ops = options;
        this.ops.asar = options.asar || false;
        this.useAdvanceOps = options.useAdvanceOps.startUp;
    }
    async createAppDir() {
        const buildDir = path.join(this.ops.outputDir, `${this.ops.appName}-electron`);
        console.log('创建目录');
        await fs.ensureDir(buildDir);
        return buildDir;
    }
    async createApp() {
        let app;
        const platform = this.ops.platform;
        const buildDir = await this.createAppDir();
        // 是否启用electron缓存功能
        if (!this.useAdvanceOps) {
            const zipPath = await this.downloadElectronZip();
            await this.extractElectronZip(zipPath, buildDir);
        }
        else {
            console.log('使用缓存复制功能', buildDir);
            const cachePath = this.ops.useAdvanceOps.cachePath;
            await this.copyElectronFromCachePath(cachePath, buildDir);
            console.log('复制完成');
        }
        this.ops.outputDir = buildDir;
        switch (platform) {
            case 'mac':
                app = new mac_1.default(this.ops);
                break;
            case 'win':
            default: {
                console.log('暂不支持别的平台打包');
            }
        }
        return app.createApp();
    }
    async downloadElectronZip() {
        return await download.downloadElectronZip();
    }
    async copyElectronFromCachePath(cachePath, target) {
        return await fs.copy(cachePath, target);
    }
    async extractElectronZip(zipPath, target) {
        console.log('开始解压，解压路径', zipPath);
        if (await fs.pathExists(target)) {
            console.log('当前解压文件出现同名', target);
            fs.removeSync(target);
        }
        await extract(zipPath, { dir: target });
        console.log('解压文件完成');
    }
}
async function packager(options) {
    const packager = new Packager(options);
    await packager.createApp();
}
exports.packager = packager;
//# sourceMappingURL=index.js.map