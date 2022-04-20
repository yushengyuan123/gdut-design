<template>
  <div class="task-list-outer" v-if="taskList.length > 0">
    <div v-for="taskItem in taskList" class="task-item-con">
      <div class="task-item-name">
        <span>{{taskItem.taskName}}</span>
      </div>
      <task-actions />
      <div class="task-pending">
        <task-pending :color="'#5b5bfa'"/>
      </div>
    </div>
  </div>
  <div v-else class="no-task">
    <div class="no-task-inner">
      当前没有下载任务
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from "vue";
import taskActions from './task-action.vue'
import taskPending from './task-pending.vue'

interface taskListData {
  taskName: string,
  taskId: number
}

export default defineComponent({
  name: 'task-list',
  components: {
    [taskActions.name]: taskActions,
    [taskPending.name]: taskPending
  },
  setup() {
    const taskList = ref<taskListData[]>([{
      taskName: '123',
      taskId: 1
    }])

    return {
      taskList
    }
  }
})
</script>

<style scoped lang="less">
.task-list-outer {
  padding: 0 36px;
  box-sizing: border-box;
  margin-top: 30px;
}
.task-item-con {
  position: relative;
  min-height: 78px;
  box-sizing: border-box;
  padding: 16px 12px;
  border-radius: 6px;
  margin-bottom: 16px;
  border: 1px solid #ccc;
}
.task-item-name {
  color: #505753;
  margin-bottom: 1.5rem;
  margin-right: 200px;
  word-break: break-all;
  min-height: 26px;
  &> span {
    font-size: 14px;
    line-height: 26px;
    overflow : hidden;
    text-overflow: ellipsis;
    display: -webkit-box;
    -webkit-line-clamp: 2;
    -webkit-box-orient: vertical;
  }
}
</style>