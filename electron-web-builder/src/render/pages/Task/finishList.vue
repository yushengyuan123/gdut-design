<template>
  <div class="task-list-outer" v-if="finishListRef.length > 0">
    <el-row
        v-for="(rowItem) in finishListRef"
        type="flex"
        :justify="'start'"
        style="margin-bottom: 20px"
        :gutter="2"
    >
      <el-col :span="11" v-for="(item, index) in rowItem.rowElement" :key="item.taskId" :offset="index > 0 ? 2 : 0">
        <el-card style="cursor: pointer" :body-style="cardStyle">
          <div class="task-actions-con">
            <task-actions
                :task="item"
                @deleteTask="deleteTask"
            />
          </div>
          <div class="task-icon-con">
            <img class="task-icon" :src="item.iconUrl" />
          </div>
          <div class="task-info-con">
            <span>{{ item.taskName }}</span>
            <div class="time-con">
              <time class="time">创建时间:{{ item.createDate }}</time>
            </div>
          </div>
        </el-card>
      </el-col>
    </el-row>
  </div>
  <div v-else class="no-task">
    <div class="no-task-inner">
      当前没有已经完成的任务
    </div>
  </div>
</template>

<script lang="ts">
import {
  computed,
  defineComponent,
  ref,
  toRaw,
  watchEffect
} from "vue";
import taskActions from './task-action.vue'
import {
  useTaskInfo
} from "./hooks/useTaskInfo"
import {
  usePreferenceStore,
    THEME_COLOR_VALUE
} from "../../pinia/preference"

export default defineComponent({
  name: 'finish-list',
  components: {
    [taskActions.name]: taskActions,
  },
  setup() {
    const {finishListRef, removeTask} = useTaskInfo()
    const preferenceStore = usePreferenceStore()
    const cardStyle = computed(() => {
      let defaultColor = '#080808c7'
      const themeColor = preferenceStore.appThemeColor

      if (themeColor === THEME_COLOR_VALUE.LIGHT) {
        defaultColor = 'white'
      }
      return {
        padding: '0px',
        'background-color': defaultColor
      }
    })

    const deleteTask = (taskInfo: {
      taskId: number
    }) => {
      removeTask(taskInfo.taskId)
    }

    return {
      finishListRef,
      deleteTask,
      cardStyle
    }
  }
})
</script>

<style scoped lang="less">
.task-list-outer {
  width: 100%;
  padding: 0 36px;
  box-sizing: border-box;
  margin-top: 30px;
}

.task-icon-con {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-bottom: 10px;

  .task-icon {
    height: 150px;
    border-radius: 50%;
    margin-top: 10px;
  }
}

.task-actions-con {
  height: 30px;
  padding: 5px;

  &::after {
    content: '';
    clear: both;
  }
}

.task-info-con {
  padding: 0 14px 10px;

  span {
    font-size: 16px;
  }

  .time-con {
    margin-top: 10px;
    font-size: 14px;
  }
}

.no-task {
  display: flex;
  height: 100%;
  width: 100%;
  align-items: center;
  justify-content: center;
  text-align: center;

  .no-task-inner {
    width: 100%;
    background: transparent url('@/asserts/no-task.svg') top center no-repeat;
    padding-top: 360px;
    font-size: 14px;
  }
}
</style>