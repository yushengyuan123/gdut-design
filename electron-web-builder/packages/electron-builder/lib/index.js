"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const prepareElectronApp_1 = require("./build/prepareElectronApp");
const electron_packager_1 = require("../../electron-packager");
const parseUrl = process.argv[1] || 'xxx.xxx.xxx';
const rawOptions = {
    parseUrl: parseUrl
};
async function buildElectronApp(rawsOptions) {
    const templatePath = path.join(__dirname, '../', './template');
    const destinationPath = path.join(__dirname, '../', './output');
    const userSourceDir = path.join(__dirname, 'output');
    const outputDir = '/Users/yushengyuan/yushengyuan/opcua';
    const packagerOptions = {
        sourceDir: userSourceDir,
        outputDir: outputDir,
        asar: false,
        platform: 'mac'
    };
    console.log("userSourceDir", userSourceDir);
    console.log("outputDir", outputDir);
    await (0, prepareElectronApp_1.prepareElectronApp)(templatePath, destinationPath, rawsOptions);
    await (0, electron_packager_1.packager)(packagerOptions);
    console.log("complete");
}
exports.default = buildElectronApp;
//# sourceMappingURL=index.js.map