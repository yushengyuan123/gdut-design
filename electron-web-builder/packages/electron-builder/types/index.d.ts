declare function getName(id:number|string):string

declare namespace ElectronBuilder {
	interface parseOptions {
		parseUrl: string,
		outputDir: string,
		appName: string,
		cachePath?: string
	}
}
