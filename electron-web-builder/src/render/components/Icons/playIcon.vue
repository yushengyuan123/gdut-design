<template>
  <svg t="1649211700073" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg"
       p-id="4544" width="19" height="19" :fill="curColor">
    <path d="M832.0064 512 192 896 192 128 832.0064 512 832.0064 512zM832.0064 512" p-id="4545"></path>
  </svg>
</template>

<script setup lang="ts">
import { defineProps} from "vue";
import { StrokeColor } from './types'

const props = defineProps<{
  strokeColor: StrokeColor
}>();
const curColor: StrokeColor = props.strokeColor
</script>
