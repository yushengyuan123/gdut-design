import { defineStore } from "pinia"

enum StrokeColor  {
  Focus = "#5b5bfa",
  defaultColor = "#303133",
  DarkColor = 'red'
}

const useIconsStore = defineStore({
  id: 'svg-icon',
  state: () => {
    return {
      currentColor: '' as StrokeColor
    }
  },
  actions: {
    updateCurrentColor(newColor: StrokeColor) {
      this.currentColor = newColor
    }
  }
})

export default {
  StrokeColor,
  useIconsStore
}