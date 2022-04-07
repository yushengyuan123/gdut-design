interface taskAddOptions {
  name: string,
  desc: string,
  outputDir: string,
  parseDir: string
}

interface httpResponseData<T> {
  code: number,
  message: string,
  data: T
}

export {
  taskAddOptions,
  httpResponseData
}