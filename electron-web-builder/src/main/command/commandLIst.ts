import {commandSorts} from "./commandTypes"
import {
  getSystemTheme,
  openFinderFolder,
  openSysDefaultBrowser
} from "./actions"

export interface builderCommand {
  command: commandSorts,
  action: (...args: any) => any
}

export const builderCommandLists: Array<builderCommand> = [
  {
    command: commandSorts.systemOpenDefaultBrowser,
    action: openSysDefaultBrowser
  },
  {
    command: commandSorts.systemOpenFinderFolder,
    action: openFinderFolder
  },
  {
    command: commandSorts.systemTheme,
    action: getSystemTheme
  }
]