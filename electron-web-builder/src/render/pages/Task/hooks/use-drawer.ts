import {
  ref
} from 'vue'

const useDrawer = () => {
  const visible = ref(false)
  
  const setDrawerStatus = (status: boolean) => {
    visible.value = status
  }
  
  return {
    visible,
    setDrawerStatus
  }
}

export {
  useDrawer
}
