import vue from '@vitejs/plugin-vue'
import VueJsx from '@vitejs/plugin-vue-jsx'
import { defineConfig } from "vite"
const path = require('path')

export default defineConfig({
  base: './',
  build: {
    rollupOptions: {
      output: {
        dir: path.join(__dirname, 'lib/main/dist')
      }
    }
  },
  plugins: [
    vue(),
    VueJsx()
  ],
  resolve: {
    alias: {
      '@': path.resolve(__dirname, "src/render") //把src改为@
    }
  }
})