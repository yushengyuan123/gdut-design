<template>
  <el-dialog
      v-model="visible"
      width="64vw"
      custom-class="tab-title-dialog add-task-dialog"
      :append-to-body="true"
      :center="true"
      @open="dialogOpen"
      @close="dialogClose"
  >
    <div class="add-task-dialog-header">添加任务</div>
    <el-form :model="baseFormData" label-width="120px" label-position="left">
      <div class="des-field">
        <el-input
            v-model="baseFormData.desc"
            :autosize="{ minRows: 3, maxRows: 4 }"
            minlength="60px"
            type="textarea"
            placeholder="任务描述"
        />
      </div>
      <el-row :gutter="20">
        <el-col :span="9">
          <el-form-item label="重命名:" label-width="70px">
            <el-input v-model="baseFormData.name"/>
          </el-form-item>
        </el-col>
        <el-col :span="15">
          <el-form-item label="解析url:" label-width="70px">
            <el-input v-model="baseFormData.parseUrl"/>
          </el-form-item>
        </el-col>
      </el-row>
      <el-form-item label="存储路径:" label-width="100px">
        <el-input v-model="baseFormData.outputDir"/>
      </el-form-item>
    </el-form>
    <div v-if="advanceVisible">
      <el-form :model="advanceFormData" label-width="120px" label-position="left">
        <el-form-item label="缓存路径:" label-width="100px">
          <el-input v-model="advanceFormData.cachePath"/>
        </el-form-item>
      </el-form>
    </div>
    <template #footer>
      <div class="dialog-footer">
        <el-checkbox v-model="advanceVisible" label="高级选项" class="chk"/>
        <el-button @click="dialogClose">取消</el-button>
        <el-button
            type="primary"
            @click="taskSubmit"
            color="#5b5bfa"
        >提交
        </el-button
        >
      </div>
    </template>
  </el-dialog>
</template>

<script lang="ts">
import {
  ref, defineComponent, toRef, SetupContext, onMounted
} from "vue";
import useTaskForm from "./hooks"

export default defineComponent({
  name: 'add-task-dialog',
  props: {
    visible: {
      type: Boolean
    }
  },
  setup(props, context) {
    const {
      baseFormData,
      advanceFormData,
      visible,
      dialogOpen,
      dialogClose,
      taskSubmit
    } = useTaskForm(props, context)
    const advanceVisible = ref<boolean>(false)

    return {
      advanceVisible,
      baseFormData,
      advanceFormData,
      visible,
      dialogClose,
      dialogOpen,
      taskSubmit
    }
  }
})
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