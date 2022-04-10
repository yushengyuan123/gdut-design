<template>
  <div class="task-action-con">
    <div class="task-item-action">
      <file />
    </div>
    <div class="task-item-action" @click="deleteTask">
      <deleteIcon />
    </div>
    <div class="task-item-action">
      <task-details />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from "vue";
import file from "@/components/Icons/file.vue"
import deleteIcon from "@/components/Icons/delete.vue"
import taskDetails from "@/components/Icons/task-details.vue"

interface actions {
  actionName: string
}

export default defineComponent({
  name: 'task-actions',
  components: {
    file,
    deleteIcon,
    'task-details': taskDetails
  },
  props: {

  },
  emits: [
    'deleteTask'
  ],
  setup(props, context) {
    const deleteTask = () => {
      context.emit('deleteTask')
    }

    return {
      deleteTask
    }
  },
})
</script>

<style scoped lang="less">
.task-action-con {
  display: flex;
  align-items: center;
  height: 24px;
  padding: 0 10px;
  margin: 0;
  overflow: hidden;
  float: right;
  cursor: default;
  text-align: right;
  border: 1px solid #F5F5F5;
  color: black;
  //background-color: $--task-item-action-background;
  border-radius: 14px;
  //transition: $--all-transition;
  //&:hover {
  //  background-color: #5b5bfa;
  //}
  &> .task-item-action {
    display: inline-block;
    box-sizing: border-box;
    margin: 0 8px;
    font-size: 0;
    cursor: pointer;
  }
  .icon-con {
    margin-left: 7px;
    margin-right: 7px;
  }
}
</style>