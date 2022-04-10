<template>
  <el-container>
    <el-header>
      <div class="download-header">已完成</div>
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