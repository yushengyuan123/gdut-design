"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.setResData = exports.Message = exports.Status = void 0;
var Status;
(function (Status) {
    Status[Status["Success"] = 200] = "Success";
    Status[Status["Fail"] = -30001] = "Fail";
})(Status || (Status = {}));
exports.Status = Status;
var Message;
(function (Message) {
    Message["success"] = "success";
    Message["error"] = "\u53D1\u751F\u672A\u77E5\u9519\u8BEF\uFF0C\u8BF7\u7A0D\u540E\u518D\u8BD5\u3002";
})(Message || (Message = {}));
exports.Message = Message;
function setResData(code, message, data) {
    return {
        code: code,
        message: message,
        data: data
    };
}
exports.setResData = setResData;
//# sourceMappingURL=utils.js.map