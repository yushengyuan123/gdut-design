import vue from '@vitejs/plugin-vue'
import VueJsx from '@vitejs/plugin-vue-jsx'
import { defineConfig } from "vite"
const path = require('path')

export default defineConfig({
  // base: path.resolve(__dirname, './dist'),
  plugins: [
    vue(),
    VueJsx()
  ]
})