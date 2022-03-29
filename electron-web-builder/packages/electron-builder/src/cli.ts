#!/usr/bin/env node

// import * as module from "module"
import yargs from 'yargs'
import * as process from "process"
import {spawn} from "child_process"
import * as path from "path"
import buildElectronApp from "./index"
import {isArgFormatInvalid} from "./helpers"

// eslint-disable-next-line @typescript-eslint/no-var-requires
const { hideBin } = require('yargs/helpers')

function sanitizeArgs(argv: string[]): string[] {
  const sanitizedArgs: string[] = []
  argv.forEach((arg) => {
    if (isArgFormatInvalid(arg)) {
      throw new Error(
        `Invalid argument passed: ${arg} .\nelectron-builder supports short options (like "-n") and long options (like "--name"), all lowercase. Run "nativefier --help" for help.\nAborting`,
      )
    }
    const isLastArg = sanitizedArgs.length + 1 === argv.length
    if (sanitizedArgs.length > 0) {
      const previousArg = sanitizedArgs[sanitizedArgs.length - 1]
      
      // Work around commander.js not supporting default argument for options
      if (
        previousArg === '--tray' &&
        !['true', 'false', 'start-in-tray'].includes(arg)
      ) {
        sanitizedArgs.push('true')
      }
    }
    sanitizedArgs.push(arg)
    
    if (arg === '--tray' && isLastArg) {
      // Add a true if --tray is last so it gets enabled
      sanitizedArgs.push('true')
    }
  })
  
  return sanitizedArgs
}

function initCliArgs(argv: Array<string>): yargs.Argv<ElectronBuilder.parseOptions> {
  const sanitizedArgs = sanitizeArgs(argv)
  
  const args: yargs.Argv<ElectronBuilder.parseOptions> = yargs(sanitizedArgs)
    .scriptName('electron-builder')
    .usage(
      '$0 <targetUrl> [outputDirectory] [other options]\nor\n$0 --upgrade <pathToExistingApp> [other options]',
    )
    .example(
      '$0 <targetUrl> -n <name>',
      'Make an app from <targetUrl> and set the application name to <name>',
    )
    .positional('targetUrl', {
      description:
        'the URL that you wish to to turn into a native app; required if not using --upgrade',
      type: 'string',
    })
    .parse()
  
  args.argv
  
  return args
}

function parseArgs(args: yargs.Argv<ElectronBuilder.parseOptions>)
  : ElectronBuilder.parseOptions {
  const parsed: ElectronBuilder.parseOptions = { ...args.argv }
  
  if (args._.length > 0) {
    parsed.parseUrl = (args._)[0].toString()
  } else {
    parsed.parseUrl = undefined
  }
  
  return parsed
}


// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
if (require.main === module) {
  const args: yargs.Argv<ElectronBuilder.parseOptions>
    = initCliArgs(process.argv.slice(2))
  
  const parsedArgs: ElectronBuilder.parseOptions = parseArgs(args)
  
  buildElectronApp(parsedArgs).then(() => {
    console.log('完成')
  })
}
