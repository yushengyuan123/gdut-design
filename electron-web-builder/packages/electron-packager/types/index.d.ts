declare namespace ElectronPackager {
  export enum Platform {
    mac = "mac",
    win = "win"
  }
  
  export interface startupOptions {
    sourceDir: string,
    outputDir: string,
    asar?: boolean,
    platform: "mac" | "win"
  }
  
  class MacApp {
    copyTemplate(outputDir: string): Promise<void>
  
    addUserDirToElectronApp(userDir: string, isAsar: boolean): Promise<void>
  }
}