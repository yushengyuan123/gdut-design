import {
  reactive, ref, SetupContext, toRaw, toRefs, toRef
} from "vue"
import {taskAddOptions} from "../../../../common/types"
import {usePreferenceStore} from "../../../pinia/preference"
import {storeToRefs} from "pinia"
import {useTaskStore} from "../../../pinia/task"
import taskModuleApi from "../../../client/task"
import {ElMessage} from "element-plus"

function checkURLLegal(url: string) {
  return /^(?:http(s)?:\/\/)?[\w.-]+(?:\.[\w.-]+)+[\w\-._~:/?#[\]@!$&'*+,;=.]+$/.test(url)
}

function checkFormDataLegal(formData: taskAddOptions) {
  const url = formData.parseUrl
  const appName = formData.name
  
  if (!checkURLLegal(url)) {
    ElMessage.error('请输入正确的解析url地址')
    return false
  }
  
  if (!appName.trim()) {
    ElMessage.error('请输入应用的名称')
    return false
  }
  
  return true
}

function emitEventInit(context: SetupContext) {
  const dialogOpen = () => {
    context.emit("update:visible", true)
  }
  const dialogClose = () => {
    context.emit("update:visible", false)
  }
  return {
    dialogOpen,
    dialogClose
  }
}

const useTaskForm = (props: any, context: SetupContext) => {
  console.log('重新执行hooks')
  const preferenceStore = usePreferenceStore()
  const { downloadDefaultDir, cachePath } = storeToRefs(preferenceStore)
  const visible = toRef(props, 'visible')
  const baseFormData = reactive<taskAddOptions>({
    name: '',
    desc: '',
    outputDir: downloadDefaultDir.value,
    parseUrl: ''
  })
  const advanceFormData = reactive({
    cachePath: cachePath.value
  })
  
  const { dialogOpen, dialogClose } = emitEventInit(context)
  
  const taskSubmit  = () => {
    const basicForm = toRaw(baseFormData)
    const taskStore = useTaskStore()
    
    if (!checkFormDataLegal(baseFormData)) {
      return
    }
    
    dialogClose()
    
    taskModuleApi.addTask({
      name: basicForm.name,
      desc: basicForm.desc,
      outputDir: basicForm.outputDir,
      parseUrl: basicForm.parseUrl,
    }).then(res => {
      ElMessage.success('任务添加成功')
      const data = res.data
      taskStore.setFinishTaskListData(data)
      taskStore.setRowTaskData()
    })
  }
  
  return {
    baseFormData,
    advanceFormData,
    visible,
    dialogClose,
    dialogOpen,
    taskSubmit
  }
}

export default useTaskForm