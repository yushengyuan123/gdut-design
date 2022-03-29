// eslint-disable-next-line @typescript-eslint/no-var-requires
const fs = require('fs')
import * as path from "path"

class BuildConfig {
  private fileContent: templateElectronApp.BuildConfig;
  
  constructor() {
    this.parseConfigJson()
  }
  
  async parseConfigJson() {
    const fileContent
      = fs.readFileSync(path.join(__dirname, '../', 'electronBuilderConfig.json')).toString()
  
    this.fileContent = JSON.parse(fileContent)
  }
  
  getFileContent() {
    if (!this.fileContent) {
      throw new Error('未初始化配置文件的内容')
    }
    
    return this.fileContent
  }
}

export {
  BuildConfig
}