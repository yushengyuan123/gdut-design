<template>
  <div class="task-bar-con">
    <div class="task-status-list-con">
      <div class="task-list-title">任务列表</div>
      <div class="task-status-list-con">
        <router-link :to="{path: item.path}" v-for="(item, index) in taskMenuItem" :class="'task-status-item ' +
      (focusItemIndex === index ? 'task-status-item-focus' : '')" @click="selectTask(index)">
          <div class="task-status-icon-con">
            <playIcon v-if="index === 0 && focusItemIndex
          === 0" :strokeColor="StrokeColor.taskFocus" />
            <playIcon v-else-if="index === 0 && focusItemIndex
          !== 0" :strokeColor="StrokeColor.defaultColor" />
            <complete v-else-if="index === 1 && focusItemIndex === 1"
                      :strokeColor="StrokeColor.taskFocus" />
            <complete v-else :strokeColor="StrokeColor.defaultColor" />
          </div>
          <div
              class="task-status-text"
              :style="focusItemIndex === index ? 'color: #5b5bfa' : ''"
          >{{item.name}}</div>
        </router-link>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import {defineComponent, ref} from "vue"
import { StrokeColor } from "../../components/Icons/types"
import playIcon from '@/components/Icons/playIcon.vue'
import complete from '@/components/Icons/complete.vue'

interface taskMenuRouterItem {
  name: string,
  path: string,
  id: number | string
}

export default defineComponent({
  name: 'TaskBar',
  components: {
    playIcon,
    complete
  },
  setup() {
    const taskMenuItem: taskMenuRouterItem[] = [
      {
        name: '下载中',
        path: '/download/pending',
        id: 1
      },
      {
        name: '已完成',
        path: '/download/finish',
        id: 2
      }
    ]

    const focusItemIndex = ref(0)
    const selectTask = (
        index: number
    ) => {
      focusItemIndex.value = index
    }

    return {
      focusItemIndex,
      taskMenuItem,
      StrokeColor,
      selectTask
    }
  }
})
</script>

<style scoped lang="less">
.task-bar-con {
  height: 100%;
  width: 160px;
  color: white;
  padding: 0 16px;
  background-color: #F4F5F7;
}

.task-status-list-con {
  color: black;

  .task-list-title {
    line-height: 24px;
    font-size: 16px;
    margin-bottom: 28px;
    padding-top: 40px;
    color: #303133;
  }

  .task-status-item-focus {
    background-color: #EAECF0;
  }

  .task-status-item {
    height: 20px;
    margin-bottom: 8px;
    padding: 8px 10px;
    font-size: 0;
    line-height: 20px;
    border-radius: 3px;
    cursor: pointer;
    display: flex;
    flex-direction: row;
    color: #4D515A;

    .task-status-text {
      font-size: 14px;
    }

    .task-status-icon-con {
      display: flex;
      flex-direction: row;
      justify-content: center;
      height: 100%;
      margin-right: 12px;

      img {
        height: 20px;
        width: 16px;
      }
    }
  }
}

</style>