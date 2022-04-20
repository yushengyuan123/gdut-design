<template>
  <div class="task-bar-con">
    <div class="task-status-list-con">
      <div class="task-list-title header-title">偏好设置</div>
      <div class="task-status-list-con">
        <router-link :to="{path: item.path}" v-for="(item, index) in taskMenuItem" :class="'task-status-item ' +
      (focusItemIndex === index ? 'task-status-item-focus' : '')" @click="selectTask(index)">
          <div class="task-status-icon-con">
            <mo-icons
                name="switch"
                :style="[ activeColor ]"
            ></mo-icons>
          </div>
          <div
              class="task-status-text"
              :style="[ activeColor ]"
          >{{item.name}}</div>
        </router-link>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import {computed, defineComponent, ref} from "vue"
import { StrokeColor } from "@/components/Icons/types"
import {THEME_COLOR_VALUE, usePreferenceStore} from "../../pinia/preference";
import {storeToRefs} from "pinia";

interface taskMenuRouterItem {
  name: string,
  path: string,
  id: number | string
}

export default defineComponent({
  name: 'preference-menu',
  setup() {
    const taskMenuItem: taskMenuRouterItem[] = [
      {
        name: '基础设置',
        path: '/download/pending',
        id: 1
      }
    ]
    const preferenceStore = usePreferenceStore()
    const preferenceStoreRef = storeToRefs(preferenceStore)
    const activeColor = computed(() => {
      const { appThemeColor } = preferenceStoreRef
      if (appThemeColor.value === THEME_COLOR_VALUE.DARK) {
        return {
          color: '#ffffff'
        }
      } else {
        return {
          color: 'rgb(91, 91, 250)'
        }
      }
    })
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
      selectTask,
      activeColor
    }
  }
})
</script>

<style scoped lang="less">
.task-bar-con {
  height: 100%;
  padding: 0 16px;
  background-color: #F4F5F7;
}

.task-status-list-con {
  .task-list-title {
    line-height: 24px;
    font-size: 16px;
    margin-bottom: 28px;
    padding-top: 44px;
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