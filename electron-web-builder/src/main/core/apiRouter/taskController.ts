import appServer from "../tcpServer"
import logger from 'electron-log'
import type {
  taskAddOptions,
  removeTaskBody
} from "../../../common/types"
import {Message, setResData, Status} from "./utils"
import {
  addTaskInfo, queryAllTaskInfo, removeTask
} from "../database/task"
import {taskServices} from "../services/taskServices";

function addTaskRouter() {
  const router = appServer.getRouter()
  router.post('/task/add', async (context: any) => {
    const taskInfo: taskAddOptions = context.request.body
    let res = null
    
    try {
      await taskServices(taskInfo)
      
      res = setResData(Status.Success, Message.success, await queryAllTaskInfo())
      logger.warn('创建任务成功', res)
    } catch (e) {
      logger.error('创建任务失败,失败原因', e)
      res = setResData(Status.Fail, Message.error, null)
    }
    
    context.body = res
  })
}

function queryAllTaskRouter() {
  const router = appServer.getRouter()
  router.get('/query/task', async (context: any) => {
    let res = null
    
    try {
      logger.warn('正在执行task查询')
      res = setResData(Status.Success, Message.success, await queryAllTaskInfo())
    } catch (e) {
      logger.error('创建任务失败,失败原因', e)
      res = setResData(Status.Fail, Message.error, null)
    }
  
    context.body = res
  })
}

function removeTaskRouter() {
  const router = appServer.getRouter()
  router.post('/task/remove', async (context: any) => {
    const body: removeTaskBody = context.request.body
    const taskId = body.taskId
    let res = null
    
    try {
      logger.warn('正在执行task移除操作')
      await removeTask(taskId)
      res = setResData(Status.Success, Message.success, await queryAllTaskInfo())
    } catch (e) {
      logger.error('创建任务失败,失败原因', e)
      res = setResData(Status.Fail, Message.error, null)
    }
    
    context.body = res
  })
}


const initTaskRouter = async () => {
  logger.warn('register task router')
  
  addTaskRouter()
  queryAllTaskRouter()
  removeTaskRouter()
}


export default initTaskRouter