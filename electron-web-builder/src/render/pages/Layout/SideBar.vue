<template>
  <div class="aside-inner">
    <div class="menu-top">
      <div class="menu-download menu-btn">
        <router-link to="/download">
          <menu-download />
        </router-link>
      </div>
      <div class="menu-download-list menu-btn" @click="addTask">
        <add />
      </div>
    </div>
    <div class="menu-bottom menu-btn">
      <router-link to="/settings">
        <perference />
      </router-link>
    </div>
  </div>
  <AddTaskDialog v-model:showDialog="showAddTaskDialog" />
</template>

<script setup lang="ts">
import { ref, defineProps } from "vue";
import add from "@/components/Icons/add.vue"
import perference from "@/components/Icons/perference.vue"
import menuDownload from "@/components/Icons/menu-download.vue"
import AddTaskDialog from "../../components/AddTaskDialog/AddTaskDialog.vue";

const showAddTaskDialog = ref<boolean>(false);

const addTask = () => {
  showAddTaskDialog.value = true;
};
</script>

<style scoped lang="less">
.aside-inner {
  display: flex;
  flex-flow: column;
  height: 100%;
  width: 28px;
  margin: auto;
}

.menu-top {
  flex: 1;
  margin-top: 20px;
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

.menu-bottom {
  margin-bottom: 24px;
  align-items: flex-end;
}
</style>