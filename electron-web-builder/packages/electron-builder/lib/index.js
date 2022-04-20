"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const prepareElectronApp_1 = require("./build/prepareElectronApp");
const electron_packager_1 = require("../../electron-packager");
async function buildElectronApp(rawsOptions) {
    const templatePath = path.join(__dirname, '../', './template');
    const destinationPath = path.join(__dirname, '../', './output');
    const userSourceDir = path.join(__dirname, '../', 'output');
    const useAdvanceOps = true;
    const outputDir = rawsOptions.outputDir
        || "/Users/yushengyuan/yushengyuan/study/chromium1/src/electron/electron-web-builder/packages/electron-builder/tests";
    const packagerOptions = {
        sourceDir: userSourceDir,
        outputDir: outputDir,
        appName: rawsOptions.appName || 'default',
        asar: false,
        useAdvanceOps: {
            startUp: useAdvanceOps,
            cachePath: ''
        },
        platform: 'mac',
    };
    if (useAdvanceOps) {
        packagerOptions.useAdvanceOps.cachePath = '/Users/yushengyuan/yushengyuan/cache/electron-v18.0.0-darwin-x64';
    }
    await (0, prepareElectronApp_1.prepareElectronApp)(templatePath, destinationPath, rawsOptions);
    await (0, electron_packager_1.packager)(packagerOptions);
    // await buildNativefierApp({
    //   targetUrl: rawsOptions.parseUrl,
    //   out: rawsOptions.outputDir,
    //   name: rawsOptions.appName
    // })
    console.log("complete");
}
exports.default = buildElectronApp;
//# sourceMappingURL=index.js.map