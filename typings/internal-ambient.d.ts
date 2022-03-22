declare namespace NodeJS {
  type AsarFileInfo = {
    size: number;
    unpacked: boolean;
    offset: number;
    integrity?: {
      algorithm: 'SHA256';
      hash: string;
    }
  };

  type AsarFileStat = {
    size: number;
    offset: number;
    isFile: boolean;
    isDirectory: boolean;
    isLink: boolean;
  }

  interface AsarArchive {
    getFileInfo(path: string): AsarFileInfo | false;
    stat(path: string): AsarFileStat | false;
    readdir(path: string): string[] | false;
    realpath(path: string): string | false;
    copyFileOut(path: string): string | false;
    getFdAndValidateIntegrityLater(): number | -1;
  }

  interface AsarBinding {
    createArchive(path: string): AsarArchive;
    splitPath(path: string): {
      isAsar: false;
    } | {
      isAsar: true;
      asarPath: string;
      filePath: string;
    };
    initAsarSupport(require: NodeJS.Require): void;
  }

  interface Process {
    noAsar: boolean;

    internalBinding?(name: string): any;

    _linkedBinding(name: string): any;

    _linkedBinding(name: 'electron_browser_view'): { View: Electron.View };

    _firstFileName?: string;
  }
}