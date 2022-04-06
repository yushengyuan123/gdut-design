<template>
  <div class="task-action-con">
    <div class="task-item-action">
      <file />
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from "vue";
import file from "@/components/Icons/file.vue"

interface actions {
  actionName: string
}

export default defineComponent({
  name: 'task-actions',
  components: {
    file
  },
  setup() {
    const taskActions = ref<actions[]>([
      {
        actionName: 'add'
      }
    ])
  },
})
</script>

<style scoped lang="less">
.task-action-con {
  // width: 28px;
  position: absolute;
  height: 22px;
  top: 16px;
  right: 12px;
  padding: 0 10px;
  margin: 0;
  overflow: hidden;
  user-select: none;
  cursor: default;
  text-align: right;
  direction: rtl;
  border: 1px solid #F5F5F5;
  color: black;
  //background-color: $--task-item-action-background;
  border-radius: 14px;
  //transition: $--all-transition;
  //&:hover {
  //  border-color: $--task-item-action-hover-border-color;
  //  color: $--task-item-action-hover-color;
  //  background-color: $--task-item-action-hover-background;
  //  width: auto;
  //}
  &> .task-item-action {
    display: inline-block;
    box-sizing: border-box;
    padding: 2px;
    margin: 0 4px;
    font-size: 0;
    cursor: pointer;
  }
}
</style>