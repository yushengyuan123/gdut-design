<template>
  <div class="main-con">
    <div class="menu-side-bar">
      <SideBar></SideBar>
    </div>
    <div class="task-bar-con">
      <TaskBar></TaskBar>
    </div>
    <div class="task-details"></div>
  </div>
</template>

<script setup>
import SideBar from './Layout/SideBar.vue'
import TaskBar from "./Task/TaskBar";
</script>

<style scoped lang="less">
.main-con {
  height: 100%;
  display: flex;
  flex-direction: row;
}

.menu-side-bar {
  height: 100%;
  width: 78px;
  background-color: black;
}

.task-details {
  flex: 1;
  background-color: #343434;
}
</style>