interface taskAddOptions {
  name: string,
  desc: string,
  outputDir: string,
  parseUrl: string
}

interface removeTaskBody {
  taskId: number
}

interface httpResponseData<T> {
  code: number,
  message: string,
  data: T
}

export {
  taskAddOptions,
  httpResponseData,
  removeTaskBody
}