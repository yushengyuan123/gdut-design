<template>
  <el-container id="container">
    <el-header class="panel-header">
      <div class="download-header header-title">已完成</div>
    </el-header>
    <el-main class="panel-content">
      <finish-list />
    </el-main>
  </el-container>
</template>

<script lang="ts">
import { defineComponent } from "vue";
import finishList from "./finishList.vue";

export default defineComponent({
  name: "menu-finish",
  components: {
    [finishList.name]: finishList
  }
})
</script>

<style scoped>

</style>