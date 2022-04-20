<template>
  <el-container id="container">
    <el-aside width="200px">
      <div class="task-bar-con hidden-sm-only">
        <task-bar></task-bar>
      </div>
    </el-aside>
    <el-main class="panel-content">
      <div class="panel">
        <router-view />
      </div>
    </el-main>
  </el-container>
</template>

<script lang="ts">
import TaskBar from "./Task/index.vue";
import { defineComponent } from "vue";

export default defineComponent({
  components: {
    'task-bar': TaskBar,
  },
  name: 'download-task'
})
</script>

<style scoped lang="less">
.task-bar-con {
  height: 100%;
}
.panel {
  height: 100%;
}
</style>
