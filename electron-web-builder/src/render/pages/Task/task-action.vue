<template>
  <div class="task-action-con">
    <div class="task-item-action" @click="openLocationFolder">
      <mo-icons name="file"></mo-icons>
    </div>
    <div class="task-item-action" @click="deleteTask">
      <mo-icons name="close"></mo-icons>
    </div>
    <div class="task-item-action" @click="openLinkUrl">
      <mo-icons name="link"></mo-icons>
    </div>
    <div class="task-item-action" @click="detailsDrawerVisible">
      <mo-icons name="infoFilled"></mo-icons>
    </div>
    <el-drawer
        custom-class="task-detail-drawer"
        v-model="visible"
        size="61.8%"
        :append-to-body="true"
        title="任务详情"
        direction="rtl"
    >
      <el-form
          :label-width="formLabelWidth"
      >
        <el-form-item label="任务名称：">
          <div class="form-static-value">
            {{ taskInfo.taskName }}
          </div>
        </el-form-item>
        <el-form-item label="任务描述：">
          <div class="form-static-value">
            {{ taskInfo.taskDesc }}
          </div>
        </el-form-item>
        <el-form-item label="创建时间：">
          <div class="form-static-value">
            {{ taskInfo.createDate }}
          </div>
        </el-form-item>
        <el-divider>
          <span>网站信息</span>
        </el-divider>
        <el-form-item label="解析url：">
          <div class="form-static-value">
            {{ taskInfo.parseUrl }}
          </div>
        </el-form-item>
        <el-form-item label="网站标识：">
          <div class="form-static-value">
            {{ taskInfo.iconUrl }}
          </div>
        </el-form-item>
      </el-form>
    </el-drawer>
  </div>
</template>

<script lang="ts">
import {defineComponent, PropType, ref} from "vue";
import {
  useDrawer
} from "./hooks/use-drawer";

import type {
  finishListData
} from "./hooks/useTaskInfo";

interface actions {
  actionName: string
}

export default defineComponent({
  name: 'task-actions',
  emits: [
    'deleteTask'
  ],
  props: {
    task: {
      type: Object as PropType<finishListData>
    }
  },
  setup(props, context) {
    const taskInfo = props.task
    const {visible, setDrawerStatus} = useDrawer()
    const formLabelWidth = ref('25%')

    const openLocationFolder = () => {
      const filePath = `/Users/yushengyuan/yushengyuan/tests/${taskInfo.taskName}-darwin-arm64`
      electronApi.ipcRenderer.send('command', 'system:open-finder', filePath)
    }

    const deleteTask = () => {
      context.emit('deleteTask', {
        taskId: taskInfo.taskId
      })
    }

    const detailsDrawerVisible = () => {
      setDrawerStatus(true)
    }

    const openLinkUrl = () => {
      const url = taskInfo.parseUrl
      electronApi.ipcRenderer.send('command', 'system:open-browser', url)
    }

    return {
      deleteTask,
      detailsDrawerVisible,
      openLinkUrl,
      openLocationFolder,
      visible,
      formLabelWidth,
      taskInfo
    }
  },
})
</script>

<style lang="less">
.task-detail-drawer {
  .el-drawer__header {
    padding-top: 2rem;
    margin-bottom: 0;
  }
}
</style>

<style scoped lang="less">
.task-action-con {
  display: flex;
  align-items: center;
  height: 24px;
  padding: 0 10px;
  margin: 0;
  overflow: hidden;
  float: right;
  cursor: default;
  text-align: right;
  color: black;
  //background-color: $--task-item-action-background;
  border-radius: 14px;
  //transition: $--all-transition;
  //&:hover {
  //  background-color: #5b5bfa;
  //}
  & > .task-item-action {
    display: inline-block;
    box-sizing: border-box;
    margin: 0 8px;
    font-size: 0;
    cursor: pointer;
  }

  .icon-con {
    margin-left: 7px;
    margin-right: 7px;
  }
}

.form-static-value {
  color: #e7e7e7;
}
</style>