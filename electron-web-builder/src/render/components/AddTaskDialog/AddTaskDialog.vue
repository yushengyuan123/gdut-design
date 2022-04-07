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
      <el-form-item label="解析url:" label-width="100px">
        <el-input v-model="addTaskForm.parseDir" />
      </el-form-item>
      <el-form-item label="存储路径:" label-width="100px">
        <el-input v-model="addTaskForm.outputDir" />
      </el-form-item>
    </el-form>
    <div v-if="showAdvanced">
      <el-form :model="advanceForm" label-width="120px" label-position="left">
        <el-form-item label="缓存路径:" label-width="100px">
          <el-input v-model="advanceForm.cachePath" />
        </el-form-item>
      </el-form>
    </div>
    <template #footer>
      <div class="dialog-footer">
        <el-checkbox v-model="showAdvanced" label="高级选项" class="chk"/>
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
import {
  defineProps,
  defineEmits,
  reactive,
  toRaw, ref
} from "vue";
import {
  taskAddOptions
} from "../../../common/types";
import {
  ElMessage
} from "element-plus";
import axios from '@/client/api'
import {AxiosResponse} from "axios";

const props = defineProps<{
  showDialog: boolean;
}>();

const showAdvanced = ref<boolean>(true)
const addTaskForm = reactive<taskAddOptions>({
  name: "whatsapp",
  desc: '任务描述',
  outputDir: "/Users/yushengyuan/yushengyuan/tests",
  parseDir: 'https://www.baidu.com'
});
const advanceForm = reactive({
  cachePath: '/Users/yushengyuan/yushengyuan/tests/dist'
})

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
  const basicForm = toRaw(addTaskForm)

  axios.post('/task/add', {
    name: basicForm.name,
    desc: basicForm.desc,
    outputDir: basicForm.outputDir,
    parseUrl: basicForm.parseDir,
  }).then(res => {
    ElMessage.success('任务添加成功')
    console.log(res)
  })
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

.dialog-footer {
  .chk {
    float: left;
    line-height: 28px;
    &.el-checkbox {
      & .el-checkbox__input {
        line-height: 19px;
      }
      & .el-checkbox__label {
        padding-left: 6px;
      }
    }
  }
}


</style>