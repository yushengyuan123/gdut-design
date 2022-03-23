import * as fs from 'fs-extra'
import * as path from "path"

type Pick<T, K extends keyof T> = {
  [P in K]: T[P]
}

type templateProjectConfig = Pick<ElectronBuilder.parseOptions, 'parseUrl'>

function generateConfig(
  options: ElectronBuilder.parseOptions
): templateProjectConfig {
  return {
    parseUrl: options.parseUrl,
  }
}

export async function prepareElectronApp(
  templateSrc: string,
  destinationSrc: string,
  options: ElectronBuilder.parseOptions
) {
  // 把electron的文件复制到目标目录下
  try {
    console.debug(`正在复制模版文件`)
    await fs.copy(templateSrc, destinationSrc)
    console.debug(`模版文件复制完成`)
  } catch (e) {
    throw new Error(`模版文件复制失败：${e}`)
  }

  const configFilePath = path.join(destinationSrc, '/electronBuilderConfig.json')
  const configFileJson = generateConfig(options)

  console.debug('writing the config file')
  try {
    await fs.writeFileSync(configFilePath, JSON.stringify(configFileJson))
  } catch (e) {
    console.debug("writing the config's json fail")
  }
}