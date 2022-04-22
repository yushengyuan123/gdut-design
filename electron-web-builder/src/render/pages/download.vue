<template>
  <el-container id="container">
    <el-aside width="200px" class="hidden-subnav-only">
      <div class="task-bar-con">
        <task-bar></task-bar>
      </div>
    </el-aside>
    <el-main class="panel-content">
      <div class="panel task-content">
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
.task-content {
  height: 100%;
}
</style>
