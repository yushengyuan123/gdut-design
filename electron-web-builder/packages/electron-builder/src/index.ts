import * as path from "path"
import {prepareElectronApp} from "./build/prepareElectronApp"
import { packager } from "../../electron-packager"

const parseUrl = process.argv[1] || 'xxx.xxx.xxx'
const rawOptions: ElectronBuilder.parseOptions = {
  parseUrl: parseUrl
}

async function buildElectronApp(rawsOptions: ElectronBuilder.parseOptions) {
  const templatePath = path.join(__dirname, '../', './template')
  const destinationPath = path.join(__dirname, '../', './output')
  const userSourceDir = path.join(__dirname, 'output')
  const outputDir = '/Users/yushengyuan/yushengyuan/opcua'
  
  const packagerOptions = {
    sourceDir: userSourceDir,
    outputDir: outputDir,
    asar: false,
    platform: 'mac'
  }
  
  console.log("userSourceDir", userSourceDir)
  console.log("outputDir", outputDir)
  
  await prepareElectronApp(templatePath, destinationPath, rawsOptions)
  await packager(packagerOptions)
  
  console.log("complete")
}

export default buildElectronApp