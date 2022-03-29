declare namespace ElectronPackager {
  export enum Platform {
    mac = "mac",
    win = "win"
  }
  
  export interface startupOptions {
    // app的名字
    appName: string,
    // 需要拷贝的目录模版目录
    sourceDir: string,
    // 资源的输出目录
    outputDir: string,
    asar?: boolean,
    platform: "mac" | "win"
  }
  
  class MacApp {
    createApp(): Promise<void>
  }
}