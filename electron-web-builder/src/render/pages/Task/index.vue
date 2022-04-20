<template>
  <div class="task-bar-con">
    <div class="task-status-list-con">
      <div class="task-list-title header-title">任务列表</div>
      <div class="task-status-list-con">
        <router-link
            :to="{path: '/download/pending'}"
            :class="'task-status-item ' + (focusItemIndex === 0 ? 'task-status-item-focus' : '')"
            @click="selectTask(0)"
        >
          <div class="task-status-icon-con">
            <mo-icons
                name="caretRight"
                :style="[ focusItemIndex === 0 ? activeColor : '' ]"
            ></mo-icons>
          </div>
          <div
              class="task-status-text"
              :style="focusItemIndex === 0 ? activeColor : ''"
          >
            下载中
          </div>
        </router-link>
        <router-link
            :to="{path: '/download/finish'}"
            :class="'task-status-item ' + (focusItemIndex === 1 ? 'task-status-item-focus' : '')"
            @click="selectTask(1)"
        >
          <div class="task-status-icon-con">
            <mo-icons
                name="checkSuccess"
                :style="[ focusItemIndex === 1 ? activeColor : '' ]"
            ></mo-icons>
          </div>
          <div
              class="task-status-text"
              :style="focusItemIndex === 1 ? activeColor : ''"
          >
            已完成
          </div>
        </router-link>
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import {computed, defineComponent, ref} from "vue"
import { StrokeColor } from "../../components/Icons/types"
import { storeToRefs } from "pinia";
import {
  usePreferenceStore,
  THEME_COLOR_VALUE
} from "../../pinia/preference"

interface taskMenuRouterItem {
  name: string,
  path: string,
  id: number | string
}

export default defineComponent({
  name: 'TaskBar',
  setup() {
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
      activeColor,
      StrokeColor,
      selectTask
    }
  }
})
</script>

<style scoped lang="less">
.task-bar-con {
  height: 100%;
  color: white;
  padding: 0 16px;
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