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
import {ElMessageBox, ElMessage} from "element-plus";

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
    ElMessageBox.confirm('你确定要删除吗？', {
      title: '操作确认',
      confirmButtonText: '确定',
      cancelButtonText: '取消'
    }).then(async () => {
      const taskStore = useTaskStore()
      const { data } = await taskModuleApi.removeTask(taskId)
  
      taskStore.setFinishTaskListData(data)
      taskStore.setRowTaskData()
      ElMessage.success('删除成功！')
    })
  }
  
  return {
    finishListRef,
    removeTask
  }
}

export {
  useTaskInfo
}