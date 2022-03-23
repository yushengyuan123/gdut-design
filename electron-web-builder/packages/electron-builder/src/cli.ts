#!/usr/bin/env node

// import * as module from "module"
import yargs from 'yargs'
import * as process from "process"
import {spawn} from "child_process"
import * as path from "path"
import buildElectronApp from "./index"


function initCliArgs(argv: Array<string>): ElectronBuilder.parseOptions {
  console.log(argv)
  
  return {
    parseUrl: "213"
  }
}

function startupApp(argv: ElectronBuilder.parseOptions) {
  const electronExecuteAblePath = "/Users/yushengyuan/yushengyuan/study/chromium1/src/"
  const outputFile = "out/testing/Electron.app/Contents/MacOS/Electron"
  // const url = argv.url
  const exeCommand = path.join(electronExecuteAblePath, outputFile)
  
  const electronChild = spawn(exeCommand)
  
  electronChild.on('data', (data) => {
    console.error(`stddata: ${data}`)
  })
  
  electronChild.on('error', (data) => {
    console.error(`stderr: ${data}`)
  })
}

// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
if (require.main === module) {
  const argv = initCliArgs(process.argv)
  // startupApp(argv)
  buildElectronApp(argv).then(() => {
    console.log("完成")
  })
}
