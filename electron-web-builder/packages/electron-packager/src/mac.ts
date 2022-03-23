import * as path from "path"
import * as fs from 'fs-extra'

class MacApp implements ElectronPackager.MacApp {
  private readonly electronAppDir: string = "/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app"
  private readonly electronAppRelativePath: string = "Contents/MacOS/Electron"
  private readonly electronResourcePath: string = "Contents/Resources"
  
  getElectronAppPath() {
    return path.join(this.electronAppDir, this.electronAppRelativePath)
  }
  
  getElectronResourcePath() {
    return path.join(this.electronAppDir, this.electronResourcePath)
  }
  
  async copyTemplate(outputDir: string) {
    try {
      console.log(this.electronAppDir)
      console.log(outputDir)
      fs.copySync("/Users/yushengyuan/yushengyuan/study/chromium1/src/out/testing/Electron.app", '/Users/yushengyuan/yushengyuan/opcua/tests')
    } catch (e) {
      throw new Error(e)
    }
  }
  
  async addUserDirToElectronApp(userDir: string, isAsar: boolean) {
    const electronResourcePath = this.getElectronResourcePath()
    if (!isAsar) {
      try {
        fs.copySync(userDir, electronResourcePath)
      } catch (e) {
        throw new Error(e)
      }
    } else {
      throw new Error('暂不支持asar打包')
    }
  }
  
}

export default MacApp