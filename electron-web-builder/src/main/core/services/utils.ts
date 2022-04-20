const request = require('request')

function isAbsolutePath(path: string) {
  return /(^\w+:)*\/\//.test(path)
}

function hasProtocols(url: string) {
  return /^(http(s)?:)/.test(url)
}

function isHttps(url: string) {
  return /^(https)/.test(url)
}

function fetch(url: string): Promise<any> {
  return new Promise(((resolve, reject) => {
    request(url, (error: any, res: any, body: any) => {
      if (error) {
        reject(error)
      } else {
        resolve(body)
      }
    })
  }))
}

export {
  isAbsolutePath,
  hasProtocols,
  isHttps,
  fetch
}
