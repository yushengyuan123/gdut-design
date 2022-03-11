declare namespace Electron {

}

declare namespace ElectronInternal {
  type ModuleLoader = () => any;
  
  interface ModuleEntry {
    name: string;
    private?: boolean;
    loader: ModuleLoader;
  }
}