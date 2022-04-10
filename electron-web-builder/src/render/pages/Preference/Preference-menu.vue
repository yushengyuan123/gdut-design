<template>
  <div class="task-bar-con">
    <div class="task-status-list-con">
      <div class="task-list-title">偏好设置</div>
      <div class="task-status-list-con">
        <router-link :to="{path: item.path}" v-for="(item, index) in taskMenuItem" :class="'task-status-item ' +
      (focusItemIndex === index ? 'task-status-item-focus' : '')" @click="selectTask(index)">
          <div class="task-status-icon-con">
            <ios-switch :strokeColor="StrokeColor.Focus"/>
          </div>
          <div
              class="task-status-text"
              :style="focusItemIndex === index ? `color: ${StrokeColor.Focus}` : ''"
          >{{item.name}}</div>
        </router-link>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import {defineComponent, ref} from "vue"
import { StrokeColor } from "@/components/Icons/types"
import iosSwitch from '@/components/Icons/ios-switch.vue'

interface taskMenuRouterItem {
  name: string,
  path: string,
  id: number | string
}

export default defineComponent({
  name: 'preference-menu',
  components: {
    'ios-switch': iosSwitch
  },
  setup() {
    const taskMenuItem: taskMenuRouterItem[] = [
      {
        name: '基础设置',
        path: '/download/pending',
        id: 1
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