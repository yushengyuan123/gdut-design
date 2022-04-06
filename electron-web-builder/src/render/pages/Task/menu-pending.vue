<template>
  <el-container>
    <el-header>
      <div class="download-header">下载中</div>
    </el-header>
    <el-main class="panel-content">
      <task-list />
    </el-main>
  </el-container>
</template>

<script lang="ts">
import taskList from "./taskList.vue";
import { defineComponent } from "vue";

export default defineComponent({
  name: "menu-pending",
  components: {
    [taskList.name]: taskList
  }
})
</script>

<style scoped>

</style>