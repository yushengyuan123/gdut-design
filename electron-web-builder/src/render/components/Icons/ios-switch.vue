<template>
  <svg t="1649383046328" class="icon" viewBox="0 0 1024 1024" version="1.1" xmlns="http://www.w3.org/2000/svg"
       p-id="3341" width="20" height="20" :fill="curColor">
    <path d="M288 736m-84 0a84 84 0 1 0 168 0 84 84 0 1 0-168 0Z" p-id="3342"></path>
    <path
        d="M735 544h-446C182.4 544 96 630.4 96 737S182.4 928 289 928h446c106.6 0 193-84.4 193-191S841.6 544 735 544zM288 864c-70.6 0-128-57.4-128-128s57.4-128 128-128 128 57.4 128 128-57.4 128-128 128z"
        p-id="3343"></path>
    <path d="M736 288m-84 0a84 84 0 1 0 168 0 84 84 0 1 0-168 0Z" p-id="3344"></path>
    <path
        d="M289 480h446c106.6 0 193-84.4 193-191S841.6 96 735 96h-446C182.4 96 96 182.4 96 289S182.4 480 289 480zM736 160c70.6 0 128 57.4 128 128s-57.4 128-128 128-128-57.4-128-128 57.4-128 128-128z"
        p-id="3345"></path>
  </svg>
</template>

<script setup lang="ts">
import {defineProps} from "vue";
import {StrokeColor} from './types'

const props = defineProps<{
  strokeColor: StrokeColor
}>();

const curColor: StrokeColor = props.strokeColor
</script>
