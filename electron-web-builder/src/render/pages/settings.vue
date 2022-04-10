<template>
  <preferenceMenu />
  <div class="settings-con">
    <router-view />
  </div>
</template>

<script setup lang="ts">
import preferenceMenu from './Preference/Preference-menu.vue'
</script>

<style scoped lang="less">
.settings-con {
  display: flex;
  width: 600px;
}
</style>
