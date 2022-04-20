<template>
  <ul class="theme-switcher">
    <li
        v-for="(themeItem, index) in themeOptionsArr"
        :class="['theme-item', themeItem.className, { active: currentValue === index}]"
        :key="themeItem.className"
        @click="changeColor(index)"
    >
      <div class="theme-thumb"></div>
      <span>{{themeItem.text}}</span>
    </li>
  </ul>
</template>

<script lang="ts">
import { defineComponent, ref } from "vue"
import { usePreferenceStore, THEME_COLOR_VALUE } from "../../pinia/preference";

interface themeClassName {
  'theme-item-auto': string,
  'theme-item-light': string,
  'theme-item-dark': string
}

interface themeOptions {
  text: string,
  className: keyof themeClassName,
}

export default defineComponent({
  name: "theme-switcher",
  setup() {
    const themeOptionsArr = ref<themeOptions[]>([
      {
        className: 'theme-item-auto',
        text: '自动',
      },
      {
        className: 'theme-item-light',
        text: '浅色'
      },
      {
        className: 'theme-item-dark',
        text: '深色'
      }
    ])
    const preferenceStore = usePreferenceStore()
    const themeColor = preferenceStore.appThemeColor

    const currentValue = ref<THEME_COLOR_VALUE>(themeColor)
    const changeColor = (index) => {
      currentValue.value = index
      preferenceStore.updateAppThemeColor(index)
    }

    return {
      themeOptionsArr,
      currentValue,
      changeColor
    }
  }
})
</script>

<style scoped lang="less">
.theme-switcher {
  padding: 0;
  margin: 0;
  font-size: 0;
  line-height: 0;

  .theme-item {
    text-align: center;
    display: inline-block;
    margin: 0 16px 0 0;
    cursor: pointer;

    span {
      font-size: 13px;
      line-height: 20px;
    }

    &.active {
      .theme-thumb {
        border-color: #5b5bfa;
        box-shadow: 0 0 1px #5b5bfa;
      }
      span {
        color: #5b5bfa;
      }
    }
    &.theme-item-auto .theme-thumb {
      background: url('@/asserts/theme-auto@2x.png') center center no-repeat;
      background-size: 68px 44px;
    }
    &.theme-item-light .theme-thumb {
      background: url('@/asserts/theme-light@2x.png') center center no-repeat;
      background-size: 68px 44px;
    }
    &.theme-item-dark .theme-thumb {
      background: url('@/asserts/theme-dark@2x.png') center center no-repeat;
      background-size: 68px 44px;
    }

    .theme-thumb {
      box-sizing: border-box;
      border: 1px solid #aaa;
      border-radius: 5px;
      width: 68px;
      height: 44px;
      margin-bottom: 8px;
    }

  }
}
</style>