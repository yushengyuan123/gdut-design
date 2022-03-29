import * as path from "path"
import * as fs from 'fs-extra'

class MacApp implements ElectronPackager.MacApp {
  private readonly electronAppDir: string
  
  // 用户electron js文件存放目录
  readonly electronUserFileDir: string
    = 'app'
  
  readonly electronAppRelativePath: string
    = "Contents/MacOS/Electron"
  
  readonly electronResourcePath: string
    = "Contents/Resources"
  
  readonly electronAppDefaultName: string
    = 'Electron.app'
  
  readonly defaultAsarPath: string
    = "Contents/Resources/default_app.asar"
  
  readonly ops: ElectronPackager.startupOptions
  
  
  constructor(ops: ElectronPackager.startupOptions) {
    this.ops = ops
    this.electronAppDir = ops.outputDir + `/${this.electronAppDefaultName}`
  }
  
  getElectronAppPath(): string {
    return path.join(this.electronAppDir, this.electronAppRelativePath)
  }
  
  getElectronResourcePath(): string {
    return path.join(this.electronAppDir, this.electronResourcePath)
  }
  
  // 拷贝模版进入Electron Resources里面
  async copyExtraResources() {
    console.log('开始进行目录拷贝')
    const resourcesDirPath = this.getElectronResourcePath()
    const userFilePath = path.join(resourcesDirPath, this.electronUserFileDir)
    
    await fs.ensureDir(userFilePath)
    
    try {
      fs.copySync(this.ops.sourceDir, userFilePath)
    } catch (e) {
      throw new Error(e)
    }
  
    console.log('模版目录拷贝完成')
  }
  
  async renameElectronApp() {
    console.log('开始执行名字修改')
    const olaName = this.electronAppDefaultName
    const newName = this.ops.appName
    const newOutputPath = path.join(this.ops.outputDir, newName)
    
    if (await fs.pathExists(newOutputPath)) {
      console.log('当前文件已经存在，即将删除，更新为最新版本')
      fs.removeSync(newOutputPath)
    }
    
    await fs.rename(path.join(this.ops.outputDir, olaName), newOutputPath)
  }
  
  async deleteElectronDefaultAsar() {
    const defaultAsarPath = path.join(this.electronAppDir, this.defaultAsarPath)
    
    if (await fs.pathExists(defaultAsarPath)) {
      console.log('正在移除electron默认asar文件')
      fs.removeSync(defaultAsarPath)
    }
  }
  
  
  // 正式创建应用
  async createApp() {
    await this.copyExtraResources()
    await this.deleteElectronDefaultAsar()
    await this.renameElectronApp()
  }
  
}

export default MacApp