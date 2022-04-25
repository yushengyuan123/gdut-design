import { defineStore } from "pinia"
import taskModuleApi from "../../client/task"
import {finishListData} from "../../pages/Task/hooks/useTaskInfo"
import {toRaw} from "vue"

interface taskListResData {
  'task_id': number,
  'task_name': string,
  'task_url': string,
  'task_icon_url': string,
  'task_desc': string,
  'task_create_time': string
}

interface rowTaskData<R = finishListData> {
  row: number,
  rowElement: R[]
}

interface taskStoreState {
  finishTaskList: taskListResData[]
}

const useTaskStore = defineStore({
  id: 'taskInfo',
  state: () => {
    return {
      finishTaskList: [] as taskListResData[],
      rowFinishListData: [] as rowTaskData[]
    }
  },
  actions: {
    async fetchTaskList() {
      const { data } = await taskModuleApi.fetchFinishTaskList()
      this.setFinishTaskListData(data)
      this.setRowTaskData()
      return data
    },
    setFinishTaskListData(newTaskList: taskListResData[]) {
      this.finishTaskList = newTaskList
    },
    setRowTaskData() {
      const finishListData: finishListData[] = this.finishTaskList.map(item => {
        return {
          taskId: item.task_id,
          taskName: item.task_name,
          taskDesc: item.task_desc,
          createDate: item.task_create_time,
          parseUrl: item.task_url,
          iconUrl: item.task_icon_url
        }
      })
      this.rowFinishListData = []
  
      const originListData: finishListData[] = toRaw(finishListData)
      const rowCount = Math.floor(originListData.length / 2)
  
      for (let i = 0; i < rowCount; i++) {
        this.rowFinishListData.push({
          row: i + 1,
          rowElement: originListData.slice(i * 2, (i * 2) + 2)
        })
      }
  
      if (originListData.length % 2) {
        this.rowFinishListData.push({
          row: this.rowFinishListData.length + 1,
          rowElement: [originListData[originListData.length - 1]]
        })
      }
      return this.rowFinishListData
    }
  }
})

export {
  useTaskStore,
  taskStoreState
}