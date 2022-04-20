"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.fetch = exports.isHttps = exports.hasProtocols = exports.isAbsolutePath = void 0;
const request = require('request');
function isAbsolutePath(path) {
    return /(^\w+:)*\/\//.test(path);
}
exports.isAbsolutePath = isAbsolutePath;
function hasProtocols(url) {
    return /^(http(s)?:)/.test(url);
}
exports.hasProtocols = hasProtocols;
function isHttps(url) {
    return /^(https)/.test(url);
}
exports.isHttps = isHttps;
function fetch(url) {
    return new Promise(((resolve, reject) => {
        request(url, (error, res, body) => {
            if (error) {
                reject(error);
            }
            else {
                resolve(body);
            }
        });
    }));
}
exports.fetch = fetch;
//# sourceMappingURL=utils.js.map