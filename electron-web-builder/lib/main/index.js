"use strict";
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
exports.application = void 0;
const application_1 = __importDefault(require("./application"));
const path = require("path");
process.env.CUR_MODE = 'debug';
const application = new application_1.default();
exports.application = application;
//# sourceMappingURL=index.js.map