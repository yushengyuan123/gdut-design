import * as path from 'path';
import { EventEmitter } from 'events';

const Module = require('module');

process.argv.splice(1, 1);

require('../common/reset-search-paths');

process._linkedBinding('electron_browser_event_emitter').setEventEmitterPrototype(EventEmitter.prototype);

const v8Util = process._linkedBinding('electron_common_v8_util');
let packagePath = null;
let packageJson = null;
const searchPaths: string[] = v8Util.getHiddenValue(global, 'appSearchPaths');


if (process.resourcesPath) {
  for (packagePath of searchPaths) {
    console.log(packagePath);
    
    try {
      packagePath = path.join(process.resourcesPath, packagePath);
      packageJson = Module._load(path.join(packagePath, 'package.json'));
      break;
    } catch {
      continue;
    }
  }
}

if (packageJson == null) {
  process.nextTick(function () {
    return process.exit(1);
  });
  throw new Error('Unable to find a valid app');
}

const mainStartupScript = packageJson.main || 'index.js';

if (packagePath) {
  // Finally load app's main.js and transfer control to C++.
  process._firstFileName = Module._resolveFilename(path.join(packagePath, mainStartupScript), null, false);
  Module._load(path.join(packagePath, mainStartupScript), Module, true);
}


// let packagePath = "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app/";

// process._firstFileName = Module._resolveFilename(path.join(packagePath, "main.js"), null, false);
// Module._load(path.join(packagePath, "main.js"), Module, true);