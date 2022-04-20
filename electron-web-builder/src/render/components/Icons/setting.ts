import { registerIcon } from './Index.vue'

console.log('加载')

registerIcon({
  name: 'setting',
  elementUIComponentName: 'Setting',
  fontSize: 25,
  adaptDarkMode: false
})