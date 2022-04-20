<script lang=tsx>
import {
  defineComponent,
  h,
  resolveComponent,
  watchEffect,
  watch,
  ref, reactive
} from 'vue'
import {
  THEME_COLOR_VALUE,
  usePreferenceStore
} from "../../pinia/preference"
import {
  storeToRefs
} from "pinia"
import iconDarkModeMap from "../Theme/IconDark"

interface IconInfo {
  name: string,
  elementUIComponentName: string,
  fontSize?: number,
  color?: string,
  adaptDarkMode?: boolean
}

const icons: any = {}

function registerIcon(iconInfo: IconInfo) {
  const name = iconInfo.name
  icons[name] = {
    name: name,
    elementUIComponentName: iconInfo.elementUIComponentName,
    fontSize: (iconInfo?.fontSize || 16) + 'px',
    color: '#9B9B9B',
    adaptDarkMode: typeof iconInfo.adaptDarkMode == "boolean"
        ? iconInfo.adaptDarkMode : true,
  }
}

export default defineComponent({
  props: {
    name: {
      type: String
    },
    color: {
      type: String
    }
  },
  setup(props) {
    const preferenceStore = usePreferenceStore()
    const preferenceRef = storeToRefs(preferenceStore)
    const { appThemeColor } = preferenceRef
    // @ts-ignore
    const icon: Required<IconInfo> = icons[props.name]
    const componentName = icon.elementUIComponentName
    let style = reactive({
      'font-size': icon.fontSize,
      "color": icon.color
    })

    const switchToDarkColor = () => {
      const adaptDarkMode = icon.adaptDarkMode
      if (adaptDarkMode && iconDarkModeMap[icon.name]) {
        if (appThemeColor.value === THEME_COLOR_VALUE.DARK) {
          style.color = iconDarkModeMap[icon.name].darkColor
        } else {
          style.color = iconDarkModeMap[icon.name].lightColor
        }
      } else if (!adaptDarkMode && iconDarkModeMap[icon.name]) {
        style.color = iconDarkModeMap[icon.name].defaultColor
      }
    }

    watch(() => appThemeColor.value, () => {
      switchToDarkColor()
    }, {
      immediate: true
    })

    return () => {
      return (
        <el-icon style={style}>
          { h(resolveComponent(componentName)) }
        </el-icon>
      )
    }
  },
})
export {
  registerIcon,
  IconInfo
}
</script>
