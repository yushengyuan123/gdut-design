"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.makeInstaller = void 0;
const makeInstaller = (fn, name) => {
    fn.install = (app) => {
        fn._context = app._context;
        app.config.globalProperties[name] = fn;
    };
    return fn;
};
exports.makeInstaller = makeInstaller;
//# sourceMappingURL=utils.js.map