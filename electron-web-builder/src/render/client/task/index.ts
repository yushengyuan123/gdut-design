// @ts-ignore
import axios from '@/client/api'
import {ElMessage} from "element-plus"

interface addTaskData {
  name: string,
  desc: string,
  outputDir: string,
  parseUrl: string
}

const taskModuleApi = {
  async fetchFinishTaskList() {
    return await axios.get('/query/task')
  },
  async addTask(formData: addTaskData) {
    return await axios.post('/task/add', {
      name: formData.name,
      desc: formData.desc,
      outputDir: formData.outputDir,
      parseUrl: formData.parseUrl,
    })
  },
  async removeTask(taskId: number) {
    return await axios.post('/task/remove', {
      taskId: taskId
    })
  }
}

export default taskModuleApi
export {
  addTaskData
}