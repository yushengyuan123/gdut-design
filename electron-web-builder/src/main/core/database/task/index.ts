import {
  application
} from "../../../index"
import type {
  ColValues,
  taskTableColumn
} from '../types'
import logger from "electron-log";
import {deleteSql} from "../utils";

async function addTaskInfo(
  task_id: string | null,
  task_name: string,
  task_url: string,
  task_icon_url: string,
  task_desc: string,
  task_create_time: string
) {
  if (!task_desc.trim()) {
    task_desc = `${task_name}桌面端应用`
  }
  
  const conInstance = application.getMysqlConnectObj()
  const columnValueMap: taskTableColumn[]
    = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', "task_status",'task_create_time']
  const valuesArr = [task_id, task_name, task_url, task_icon_url, task_desc, 1, task_create_time]
  const insertValueMap: ColValues<taskTableColumn>[] = []
  
  columnValueMap.forEach((colName, index) => {
    insertValueMap.push({
      columns: colName,
      value: valuesArr[index]
    })
  })
  
  await conInstance.insert(
    'task_info',
    insertValueMap
  )
}

async function queryAllTaskInfo() {
  const conInstance = application.getMysqlConnectObj()
  const columns: taskTableColumn[]
    = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', 'task_create_time']
  
  type taskResData<R = 'task_id'> = {
    [key in taskTableColumn]: R extends 'task_id' ? number : string
  }
  
  const res: taskResData[] = await conInstance.select(
    'task_info',
    columns,
    null
  )
  
  return res
}

async function removeTask(
  taskId: number
) {
  await deleteSql('task_info', `task_id = ${taskId}`)
}

export {
  addTaskInfo,
  queryAllTaskInfo,
  removeTask
}