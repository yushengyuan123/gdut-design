<template>
  <div class="main-con">
    <div class="menu-side-bar">
      <SideBar />
    </div>
    <router-view></router-view>
  </div>
</template>

<script setup lang="ts">
import SideBar from "./Layout/SideBar.vue"
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
  background-color: white;
}
</style>