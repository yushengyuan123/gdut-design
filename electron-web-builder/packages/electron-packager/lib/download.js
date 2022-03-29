"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.downloadElectronZip = void 0;
const get_1 = require("@electron/get");
const debug = require("debug");
async function downloadElectronZip() {
    debug(`Downloading Electron`);
    return await (0, get_1.downloadArtifact)({
        version: '18.0.0',
        platform: 'darwin',
        artifactName: 'electron',
        arch: 'x64',
    });
}
exports.downloadElectronZip = downloadElectronZip;
//# sourceMappingURL=download.js.map