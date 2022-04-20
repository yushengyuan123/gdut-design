<template>
  <title-draggable />
  <el-container id="container">
    <side-bar></side-bar>
    <router-view></router-view>
  </el-container>
</template>

<script lang="ts">
import {defineComponent, onBeforeMount, watch} from "vue";
import SideBar from "./Layout/SideBar.vue"
import {THEME_COLOR_VALUE, usePreferenceStore} from "@/pinia/preference";
import titleDragBar from "./Layout/titleDragBar.vue"

export default defineComponent({
  components: {
    'side-bar': SideBar,
    [titleDragBar.name]: titleDragBar
  },
  setup() {
    const preferenceStore = usePreferenceStore()
    const themeClass = () => {
      let theme = 'theme-'
      switch (preferenceStore.appThemeColor) {
        case THEME_COLOR_VALUE.AUTO: {
          theme += 'auto'
          break
        }
        case THEME_COLOR_VALUE.LIGHT: {
          theme += 'light'
          break
        }
        case  THEME_COLOR_VALUE.DARK: {
          theme += 'dark'
        }
      }
      return theme
    }

    watch(() => {
      return preferenceStore.appThemeColor
    }, () => {
      updateRootClass()
    })

    const updateRootClass = () => {
      document.documentElement.className = themeClass()
    }

    onBeforeMount(() => {
      updateRootClass()
    })
  }
})
</script>

<style scoped lang="less">
.menu-side-bar {
  height: 100%;
  width: 78px;
  background-color: transparent;
}

.task-details {
  background-color: white;
}
</style>