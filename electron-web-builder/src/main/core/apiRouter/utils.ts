enum Status {
  Success = 200,
  Fail = -30001
}

enum Message {
  success = 'success',
  error = '发生未知错误，请稍后再试。'
}

function setResData<R = any>(
  code: Status,
  message: string | Message,
  data: R
) {
  return {
    code: code,
    message: message,
    data: data
  }
}

export {
  Status,
  Message,
  setResData
}