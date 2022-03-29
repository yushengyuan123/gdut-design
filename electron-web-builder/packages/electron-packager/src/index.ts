/**
 * 目标提供两个参数，sourceDir，outputDir
 */
import MacApp from "./mac"
import * as download from './download'
import * as extract from 'extract-zip'
import * as fs from 'fs-extra'
import * as path from "path"

class Packager {
  public ops: ElectronPackager.startupOptions
  
  constructor(options: ElectronPackager.startupOptions) {
    this.ops = options
    this.ops.asar = options.asar || false
  }
  
  async createAppDir() {
    const buildDir = path.join(this.ops.outputDir, `${this.ops.appName}-electron`)
    console.log('创建目录')
    await fs.ensureDir(buildDir)
    
    return buildDir
  }
  
  async createApp() {
    let app: ElectronPackager.MacApp
    const platform = this.ops.platform
  
    const buildDir = await this.createAppDir()
    const zipPath = await this.downloadElectronZip()
    await this.extractElectronZip(zipPath, buildDir)
    
    this.ops.outputDir = buildDir
    
    switch (platform) {
    case 'mac':
      app = new MacApp(this.ops)
      break
    case 'win':
    default: {
      console.log('暂不支持别的平台打包')
    }
    }
    
    return app.createApp()
  }
  
  async downloadElectronZip() {
    return await download.downloadElectronZip()
  }
  
  async extractElectronZip(zipPath, target) {
    console.log('开始解压，解压路径')
    
    if (await fs.pathExists(target)) {
      console.log('当前解压文件出现同名')
      fs.removeSync(target)
    }
    
    await extract(zipPath, { dir: target })
    console.log('解压文件完成')
  }
  
}

async function packager(options: ElectronPackager.startupOptions) {
  const packager = new Packager(options)
  
  await packager.createApp()
}

export {
  packager
}