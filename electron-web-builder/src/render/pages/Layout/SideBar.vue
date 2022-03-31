<template>
  <div class="left-side-bar-con">
    <div class="menu-download menu-btn">
      <img
          style="width: 32px;
          height: 32px"
          src="../../asserts/add.png"
          alt=""
          @click="addTask"
      >
    </div>
    <div class="menu-download-list menu-btn">
      <img
          style="width: 25px; height: 25px"
          class="menu-download-list-img"
          src="../../asserts/list.png"
          alt=""
      >
    </div>

    <AddTaskDialog
        :showAddTaskDialog="showAddTaskDialog"
    />
  </div>
</template>

<script setup lang="ts">
import { ref, defineProps } from "vue"
import AddTaskDialog from '../../component/AddTaskDialog/AddTaskDialog.vue'

const showAddTaskDialog = ref<boolean>(false)
// const props = defineProps<{
//   foo: boolean
// }>({
//   foo: true
// })

const addTask = () => {
  console.log('add')
}

</script>

<style scoped lang="less">
.left-side-bar-con {
  width: 28px;
  margin: 40px auto auto;
}

.menu-download-list-img {
  height: 28px;
  width: 28px;
}

.menu-btn {
  display: flex;
  flex-direction: row;
  justify-content: center;
  height: 28px;
  width: 28px;
  margin-top: 24px;
  cursor: pointer;
}

</style>