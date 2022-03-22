/// <reference path="../electron.d.ts" />

declare namespace Electron {

  class View {}

}

declare namespace ElectronInternal {
  type ModuleLoader = () => any;
  
  interface ModuleEntry {
    name: string;
    private?: boolean;
    loader: ModuleLoader;
  }
}