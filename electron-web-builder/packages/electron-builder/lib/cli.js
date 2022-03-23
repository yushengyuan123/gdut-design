#!/usr/bin/env node
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const process = require("process");
const child_process_1 = require("child_process");
const path = require("path");
const index_1 = require("./index");
function initCliArgs(argv) {
    console.log(argv);
    return {
        parseUrl: "213"
    };
}
function startupApp(argv) {
    const electronExecuteAblePath = "/Users/yushengyuan/yushengyuan/study/chromium1/src/";
    const outputFile = "out/testing/Electron.app/Contents/MacOS/Electron";
    // const url = argv.url
    const exeCommand = path.join(electronExecuteAblePath, outputFile);
    const electronChild = (0, child_process_1.spawn)(exeCommand);
    electronChild.on('data', (data) => {
        console.error(`stddata: ${data}`);
    });
    electronChild.on('error', (data) => {
        console.error(`stderr: ${data}`);
    });
}
// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
if (require.main === module) {
    const argv = initCliArgs(process.argv);
    // startupApp(argv)
    (0, index_1.default)(argv).then(() => {
        console.log("完成");
    });
}
//# sourceMappingURL=cli.js.map