import {builderCommand, builderCommandLists} from "./commandLIst"
import logger from 'electron-log'
import Application from "../application"

function registerCommands(this: Application) {
  builderCommandLists.forEach((commands: builderCommand) => {
    logger.info('listening events ', commands.command)
    this.on(commands.command, commands.action)
  })
}

export { commandSorts } from './commandTypes'
export {
  registerCommands
}