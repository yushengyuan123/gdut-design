import * as path from 'path';

const Module = require('module');

process.argv.splice(1, 1);

const app = require('electron');

console.log(app);

let packagePath = "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app/";

Module._load(path.join(packagePath, "main.js"), Module, true);