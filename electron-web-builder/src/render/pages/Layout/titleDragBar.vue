<template>
  <div class="title-bar-draggable"></div>
</template>

<script>
import { defineComponent } from "vue";

export default defineComponent({
  name: 'title-draggable'
})
</script>

<style scoped lang="less">
.title-bar-draggable {
  position: fixed;
  top: 0;
  left: 0;
  height: 36px;
  width: 100%;
  z-index: 5000;
  -webkit-app-region: drag;
}
</style>