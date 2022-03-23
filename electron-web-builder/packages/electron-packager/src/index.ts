/**
 * 目标提供两个参数，sourceDir，outputDir
 */
import MacApp from "./mac"

class Packager {
  public ops: ElectronPackager.startupOptions
  
  constructor(options: ElectronPackager.startupOptions) {
    this.ops = options
    this.ops.asar = options.asar || false
  }
  
  async createApp() {
    let app: ElectronPackager.MacApp
    const platform = this.ops.platform
    
    switch (platform) {
    case 'mac':
      app = new MacApp()
      break
    case 'win':
    default: {
      console.log('暂不支持别的平台打包')
    }
    }
    
    await app.copyTemplate(this.ops.outputDir)
    await app.addUserDirToElectronApp(this.ops.sourceDir, this.ops.asar)
  }
  
}

async function packager(options: ElectronPackager.startupOptions) {
  const packager = new Packager(options)
  
  await packager.createApp()
}

export {
  packager
}