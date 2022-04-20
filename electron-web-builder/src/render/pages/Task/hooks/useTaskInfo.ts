import {
  onMounted,
  reactive,
  ref, toRaw,
} from "vue"
import { storeToRefs } from 'pinia'
// @ts-ignore
import {useTaskStore} from "@/pinia/task"
// @ts-ignore
import type {taskListResData} from "@/pinia/task"
// @ts-ignore
import axios from '@/client/api'
import taskModuleApi from "../../../client/task";

export interface finishListData {
  taskId: number,
  taskName: string,
  createDate: string,
  taskDesc: string,
  parseUrl: string,
  iconUrl: string
}

async function fetchTaskInfo() {
  const useTask = useTaskStore()
  await useTask.fetchTaskList()
}

const useTaskInfo = () => {
  const useTask = useTaskStore()
  const { rowFinishListData } = storeToRefs(useTask)
  const finishListRef = rowFinishListData
  
  onMounted(async () => {
    await fetchTaskInfo()
  })
  
  const removeTask = async (taskId: number) => {
    const taskStore = useTaskStore()
    const { data } = await taskModuleApi.removeTask(taskId)
    
    taskStore.setFinishTaskListData(data)
    taskStore.setRowTaskData()
  
    console.log('移除成功', data)
  }
  
  return {
    finishListRef,
    removeTask
  }
}

export {
  useTaskInfo
}