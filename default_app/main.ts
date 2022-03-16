/**
 * 这个main.ts文件中正式加载用户的js代码
 */
import * as path from "path"

const Module = require('module')

let packagePath = null
let debug = true

interface jsonProperties {
  name: string,
  version: string
}

function loadApplicationPackage(packagePath: string) {
  const packageJsonPath = path.join(packagePath, "package.json")
  const packageJsonInfo: unknown = require(packageJsonPath)

  console.log("package name：", (packageJsonInfo as jsonProperties).name)
  console.log("package version：", (packageJsonInfo as jsonProperties).version);
  
  Module._load(packagePath, module, true);
}

if (debug) {
  packagePath = '/Users/yushengyuan/yushengyuan/study/chromium1/src/electron/'
  const entryDir = "electron-web-builder"

  if (packagePath) {
    loadApplicationPackage(path.join(packagePath, entryDir))
  }
} else {
  console.log("暂不支持发布环境");
}

