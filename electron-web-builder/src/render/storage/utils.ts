function ObjectToString(obj: Object) {
  return JSON.stringify(obj)
}

function StringToObject<T = any>(string: string): T {
  return JSON.parse(string)
}

export {
  ObjectToString,
  StringToObject
}