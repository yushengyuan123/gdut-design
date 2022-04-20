<template>
  <el-aside width="78px" class="draggable">
    <div class="aside-inner">
      <div class="menu-top">
        <div class="menu-download menu-btn">
          <router-link to="/download">
            <mo-icons name='download' />
          </router-link>
        </div>
        <div class="menu-download-list menu-btn" @click="addTask">
          <mo-icons name='add' />
        </div>
      </div>
      <div class="menu-bottom menu-btn">
        <router-link to="/settings">
          <mo-icons name='setting' />
        </router-link>
      </div>
    </div>
  </el-aside>
  <AddTaskDialog v-model:showDialog="showAddTaskDialog" />
</template>

<script lang="ts">
import { ref, defineComponent } from "vue";
import AddTaskDialog from "../../components/AddTaskDialog/AddTaskDialog.vue";

export default defineComponent({
  components: {
    AddTaskDialog
  },
  setup() {
    const showAddTaskDialog = ref<boolean>(false);
    const addTask = () => {
      showAddTaskDialog.value = true;
    };
    return {
      showAddTaskDialog,
      addTask
    }
  }
})
</script>

<style scoped lang="less">
.aside-inner {
  display: flex;
  flex-flow: column;
  height: 100%;
  width: 100%;
  background-color: #000000db;
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
  margin: 24px auto;
  cursor: pointer;

}

.menu-bottom {
  margin-bottom: 24px;
  align-items: flex-end;
}
</style>