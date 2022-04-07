import appServer from "../tcpServer"
import logger from 'electron-log'
// @ts-ignore
import buildElectronApp from "../../../../packages/electron-builder"
import {taskAddOptions} from "../../../common/types"
import {Message, setResData, Status} from "./utils"

const initTaskRouter = () => {
  const router = appServer.getRouter()
  logger.warn('register task router')
  
  router.post('/task/add', async (context: any) => {
    const taskInfo: taskAddOptions = context.request.body
    let res = null
    
    try {
      await addBuilderTask(taskInfo)
      res = setResData(Status.Success, Message.success, null)
      logger.warn('创建任务成功', res)
    } catch (e) {
      logger.error('创建任务失败,失败原因', e)
      res = setResData(Status.Fail, Message.error, null)
    }
    
    context.body = res
  })
}

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

export default initTaskRouter