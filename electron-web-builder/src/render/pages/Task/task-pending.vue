<template>
  <el-progress
      :percentage="50"
      :indeterminate="true"
      :show-text="false"
      :color="color"
  />
</template>

<script lang="ts">
import {defineComponent, defineExpose} from "vue";

export default defineComponent({
  name: 'task-pending',
  props: {
    color: String
  },
  setup: (props) => {
    const color = props.color

    return {
      color
    }
  }
})
</script>

<style scoped>

</style>