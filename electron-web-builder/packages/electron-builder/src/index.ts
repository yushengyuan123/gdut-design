import * as path from "path"
import {prepareElectronApp} from "./build/prepareElectronApp"
import { packager } from "../../electron-packager"

async function buildElectronApp(rawsOptions: ElectronBuilder.parseOptions) {
  const templatePath = path.join(__dirname, '../', './template')
  const destinationPath = path.join(__dirname, '../', './output')
  const userSourceDir = path.join(__dirname, '../', 'output')
  const useAdvanceOps = true
  const outputDir = rawsOptions.outputDir
    || "/Users/yushengyuan/yushengyuan/study/chromium1/src/electron/electron-web-builder/packages/electron-builder/tests"

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
  }
  
  if (useAdvanceOps) {
    packagerOptions.useAdvanceOps.cachePath = '/Users/yushengyuan/yushengyuan/cache/electron-v18.0.0-darwin-x64'
  }
  
  await prepareElectronApp(templatePath, destinationPath, rawsOptions)
  await packager(packagerOptions)
  
  console.log("complete")
}

export default buildElectronApp