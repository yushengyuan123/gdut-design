import logger from 'electron-log'
import {
  taskAddOptions
} from "../../common/types"
// @ts-ignore
import buildElectronApp from "../../../packages/electron-builder"

async function addBuilderTask(
  receiveData: taskAddOptions
) {
  logger.info('execute add task')
  
  const name = receiveData.name
  const outputDir = receiveData.outputDir
  const url = receiveData.parseDir
  
  await buildElectronApp({
    parseUrl: url,
    outputDir: outputDir,
    appName: name
  })
  
  logger.info('add task finish')
}

export {
  addBuilderTask
}