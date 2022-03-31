<template>
  <el-dialog
      v-model="addDialogShow"
      width="64vw"
      custom-class="add-task-dialog"
      destroy-on-close
      :append-to-body="true"
      center
  >
    <template #title>
      <div class="add-task-dialog-header">
        添加任务
      </div>
    </template>

    <el-input
        :autosize="{ minRows: 2, maxRows: 4 }"
        type="textarea"
        placeholder="任务描述"
    />

    <template #footer>
      <span class="dialog-footer">
        <el-button @click="centerDialogVisible = false">Cancel</el-button>
        <el-button type="primary" @click="centerDialogVisible = false"
        >Confirm</el-button
        >
      </span>
    </template>
  </el-dialog>
</template>

<script setup lang="ts">
import { ref } from 'vue'

const addDialogShow = ref(true)


</script>

<style scoped lang="less">

.add-task-dialog-header {
  height: 40px;
  line-height: 40px;
  text-align: left;
  border-bottom: 2px solid #606060;
  font-size: 14px;
  color: #a2a3a4;
}
</style>

<style>
.add-task-dialog {
  background-color: #343434 !important;
}
</style>