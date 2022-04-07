import {commandSorts} from "./commandTypes"
import {
  addBuilderTask
} from "./actions"

export interface builderCommand {
  command: commandSorts,
  action: (...args: any) => any
}

export const builderCommandLists: Array<builderCommand> = [
  {
    command: commandSorts.AddTask,
    action: addBuilderTask
  }
]