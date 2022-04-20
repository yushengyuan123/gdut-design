"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.getCurTimeSeconds = exports.getCurrentDate = void 0;
const dayjs_1 = __importDefault(require("dayjs"));
function getCurTimeSeconds() {
    return new Date().getTime();
}
exports.getCurTimeSeconds = getCurTimeSeconds;
function getCurrentDate() {
    const curSec = getCurTimeSeconds();
    return (0, dayjs_1.default)(curSec).format('YYYY-MM-DD HH:mm:ss');
}
exports.getCurrentDate = getCurrentDate;
//# sourceMappingURL=index.js.map