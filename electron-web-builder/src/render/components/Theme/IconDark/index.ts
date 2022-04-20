import {
  iconsNameKey
} from "../../Icons/types"

type iconDarkModeMapTypes = {
  [key in iconsNameKey]: {
    lightColor?: string,
    darkColor?: string,
    defaultColor?: string
  }
}

const iconDarkModeMap: Partial<iconDarkModeMapTypes> = {
  switch: {
    lightColor: 'rgb(155, 155, 155)',
    darkColor: 'white'
  },
  setting: {
    defaultColor: '#ffffff'
  },
  add: {
    defaultColor: '#ffffff'
  },
  download: {
    defaultColor: '#ffffff'
  },
  file: {
    lightColor: 'rgb(155, 155, 155)',
    darkColor: 'white'
  },
  close: {
    lightColor: 'rgb(155, 155, 155)',
    darkColor: 'white'
  },
  link: {
    lightColor: 'rgb(155, 155, 155)',
    darkColor: 'white'
  },
  infoFilled: {
    lightColor: 'rgb(155, 155, 155)',
    darkColor: 'white'
  }
}

export default iconDarkModeMap