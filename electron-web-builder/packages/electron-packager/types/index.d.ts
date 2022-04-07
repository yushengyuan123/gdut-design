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
    platform: "mac" | "win",
    asar?: boolean,
    useAdvanceOps: {
      startUp: boolean,
      cachePath: string
    }
  }
  
  class MacApp {
    createApp(): Promise<void>
  }
}