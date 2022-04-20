"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.registerKoaApiRouter = void 0;
const taskController_1 = __importDefault(require("./taskController"));
const routerFunc = [
    taskController_1.default
];
function registerKoaApiRouter() {
    routerFunc.forEach(func => {
        func();
    });
}
exports.registerKoaApiRouter = registerKoaApiRouter;
//# sourceMappingURL=index.js.map