"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.prepareElectronApp = void 0;
const fs = require("fs-extra");
const path = require("path");
function generateConfig(options) {
    console.log('生成的config', options);
    return {
        parseUrl: options.parseUrl,
    };
}
async function prepareElectronApp(templateSrc, destinationSrc, options) {
    // 把electron的文件复制到目标目录下
    try {
        console.debug(`正在复制模版文件`);
        await fs.copy(templateSrc, destinationSrc);
        console.debug(`模版文件复制完成`);
    }
    catch (e) {
        throw new Error(`模版文件复制失败：${e}`);
    }
    const configFilePath = path.join(destinationSrc, '/electronBuilderConfig.json');
    const configFileJson = generateConfig(options);
    console.debug('writing the config file');
    try {
        await fs.writeFileSync(configFilePath, JSON.stringify(configFileJson));
    }
    catch (e) {
        console.debug("writing the config's json fail");
    }
}
exports.prepareElectronApp = prepareElectronApp;
//# sourceMappingURL=prepareElectronApp.js.map