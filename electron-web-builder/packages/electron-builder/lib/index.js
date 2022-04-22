"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const path = require("path");
const childProcess = require("child_process");
function spawnLocalNode(rawOptions) {
    childProcess.spawnSync('nativefier', [rawOptions.parseUrl,
        rawOptions.outputDir,
        '-n',
        rawOptions.appName
    ]);
}
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
    spawnLocalNode(rawsOptions);
    // await prepareElectronApp(templatePath, destinationPath, rawsOptions)
    // await packager(packagerOptions)
    // await buildNativefierApp({
    //   targetUrl: rawsOptions.parseUrl,
    //   out: rawsOptions.outputDir,
    //   name: rawsOptions.appName
    // })
    console.log("complete");
}
exports.default = buildElectronApp;
//# sourceMappingURL=index.js.map