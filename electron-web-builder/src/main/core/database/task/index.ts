import {
  application
} from "../../../index"
import type {
  ColValues,
  taskTableColumn
} from '../types'

function addTaskInfo() {
  const conInstance = application.getMysqlConnectObj()
  const columnValue: taskTableColumn[]
    = ['task_id', 'task_name', 'task_url', 'task_icon_url', 'task_desc', 'task_create_time']
  const insertValue: ColValues<taskTableColumn>[] = []
  
  columnValue.forEach(colName => {
    insertValue.push({
      columns: colName,
      value: '321'
    })
  })
  
  conInstance.insert(
    'task_info',
    insertValue,
    []
  )
}

export {
  addTaskInfo
}