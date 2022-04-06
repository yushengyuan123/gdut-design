<template>
  <el-dialog
    v-model="props.showDialog"
    width="64vw"
    custom-class="tab-title-dialog add-task-dialog"
    :destroy-on-close="true"
    :append-to-body="true"
    :center="true"
    @open="dialogOpen"
    @close="dialogClose"
  >
    <div class="add-task-dialog-header">添加任务</div>
    <el-form :model="addTaskForm" label-width="120px" label-position="left">
      <div class="des-field">
        <el-input
            v-model="addTaskForm.desc"
          :autosize="{ minRows: 3, maxRows: 5 }"
          minlength="70px"
          type="textarea"
          placeholder="任务描述"
        />
      </div>
      <el-form-item label="重命名:" label-width="100px">
        <el-input v-model="addTaskForm.name" />
      </el-form-item>
      <el-form-item label="存储路径:" label-width="100px">
        <el-input v-model="addTaskForm.name" />
      </el-form-item>
    </el-form>
    <template #footer>
      <div class="dialog-footer">
        <el-button @click="dialogClose">取消</el-button>
        <el-button
            type="primary"
            @click="taskSubmit"
            color="#5b5bfa"
          >提交</el-button
        >
      </div>
    </template>
  </el-dialog>
</template>

<script setup lang="ts">
import { ref, defineProps, defineEmits, reactive } from "vue";
// import { ipcRenderer } from 'electron'


interface addTaskFormData {
  name: string;
  dir: string;
  desc: string
}

const props = defineProps<{
  showDialog: boolean;
}>();

const addTaskForm = reactive<addTaskFormData>({
  name: "nihao",
  desc: '任务描述',
  dir: "capo",
});

const emitEvents = defineEmits<{
  (e: "update:showDialog", status: boolean): void;
}>();
const dialogOpen = () => {
  emitEvents("update:showDialog", true);
};
const dialogClose = () => {
  emitEvents("update:showDialog", false);
};

const taskSubmit  = () => {
  console.log('创建任务')
  // ipcRenderer.send('command', 'task:add-task')
}

</script>

<style scoped lang="less">
.add-task-dialog-header {
  height: 40px;
  line-height: 40px;
  text-align: left;
  border-bottom: 2px solid #e4e7ed;
  font-size: 14px;
  color: #a2a3a4;
  margin-bottom: 15px;
}

.des-field {
  margin-bottom: 18px;
}
</style>

<style lang="less">
.tab-title-dialog {
  .el-dialog__header {
    padding: 0 20px;
    position: relative;
    z-index: 10;
  }

  .el-dialog__body {
    padding-top: 10px !important;
    padding-bottom: 10px;
  }

  .el-dialog__footer {
    padding: 20px !important;
    background-color: #f5f5f5;
    border-radius: 0 0 5px 5px;
    text-align: right !important;
  }
}


</style>