<template>
  <el-container id="container">
    <el-aside width="200px">
      <preference-menu />
    </el-aside>
    <el-main class="panel-content">
      <div class="settings-con panel">
        <router-view />
      </div>
    </el-main>
  </el-container>
</template>

<script lang="ts">
import { defineComponent } from "vue"
import preferenceMenu from './Preference/Preference-menu.vue'

export default defineComponent({
  components: {
    'preference-menu': preferenceMenu
  }
})
</script>

<style scoped lang="less">
.settings-con {
  height: 100%;
  display: flex;
}
</style>
