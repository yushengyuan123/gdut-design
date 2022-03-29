#!/usr/bin/env node
"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
// import * as module from "module"
const yargs_1 = require("yargs");
const process = require("process");
const index_1 = require("./index");
const helpers_1 = require("./helpers");
// eslint-disable-next-line @typescript-eslint/no-var-requires
const { hideBin } = require('yargs/helpers');
function sanitizeArgs(argv) {
    const sanitizedArgs = [];
    argv.forEach((arg) => {
        if ((0, helpers_1.isArgFormatInvalid)(arg)) {
            throw new Error(`Invalid argument passed: ${arg} .\nelectron-builder supports short options (like "-n") and long options (like "--name"), all lowercase. Run "nativefier --help" for help.\nAborting`);
        }
        const isLastArg = sanitizedArgs.length + 1 === argv.length;
        if (sanitizedArgs.length > 0) {
            const previousArg = sanitizedArgs[sanitizedArgs.length - 1];
            // Work around commander.js not supporting default argument for options
            if (previousArg === '--tray' &&
                !['true', 'false', 'start-in-tray'].includes(arg)) {
                sanitizedArgs.push('true');
            }
        }
        sanitizedArgs.push(arg);
        if (arg === '--tray' && isLastArg) {
            // Add a true if --tray is last so it gets enabled
            sanitizedArgs.push('true');
        }
    });
    return sanitizedArgs;
}
function initCliArgs(argv) {
    const sanitizedArgs = sanitizeArgs(argv);
    const args = (0, yargs_1.default)(sanitizedArgs)
        .scriptName('electron-builder')
        .usage('$0 <targetUrl> [outputDirectory] [other options]\nor\n$0 --upgrade <pathToExistingApp> [other options]')
        .example('$0 <targetUrl> -n <name>', 'Make an app from <targetUrl> and set the application name to <name>')
        .positional('targetUrl', {
        description: 'the URL that you wish to to turn into a native app; required if not using --upgrade',
        type: 'string',
    })
        .parse();
    args.argv;
    return args;
}
function parseArgs(args) {
    const parsed = { ...args.argv };
    if (args._.length > 0) {
        parsed.parseUrl = (args._)[0].toString();
    }
    else {
        parsed.parseUrl = undefined;
    }
    return parsed;
}
// eslint-disable-next-line @typescript-eslint/ban-ts-comment
// @ts-ignore
if (require.main === module) {
    const args = initCliArgs(process.argv.slice(2));
    const parsedArgs = parseArgs(args);
    (0, index_1.default)(parsedArgs).then(() => {
        console.log('完成');
    });
}
//# sourceMappingURL=cli.js.map