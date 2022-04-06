<template>
  <div class="task-bar-con">
    <TaskBar></TaskBar>
  </div>
  <div class="task-details">
    <router-view />
  </div>
</template>

<script lang="ts">
import TaskBar from "./Task/index.vue";
import { defineComponent } from "vue";

export default defineComponent({
  components: {
    TaskBar,
  },
  name: 'download-task'
})
</script>

<style lang="less">
.panel-content {
  padding: 0;
  height: 100%;
}
.task-details {
  display: flex;
  width: 600px;
}
.download-header {
  width: 100%;
  padding: 30px 0 12px;
  border-bottom: 2px solid rgba(0, 0, 0, 0.1);
  font-size: 15px;
}

.no-task {
  display: flex;
  height: 100%;
  width: 100%;
  align-items: center;
  justify-content: center;
  color: #555;
  text-align: center;

  .no-task-inner {
    width: 100%;
    background: transparent url('@/asserts/no-task.svg') top center no-repeat;
    padding-top: 360px;
    font-size: 14px;
  }
}
</style>
