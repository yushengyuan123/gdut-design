"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.isArgFormatInvalid = void 0;
function isArgFormatInvalid(arg) {
    return ((arg.startsWith('---') ||
        /^--[a-z]$/i.exec(arg) !== null ||
        /^-[a-z]{2,}$/i.exec(arg) !== null) &&
        !['--x', '--y'].includes(arg) // exception for long args --{x,y}
    );
}
exports.isArgFormatInvalid = isArgFormatInvalid;
//# sourceMappingURL=helpers.js.map