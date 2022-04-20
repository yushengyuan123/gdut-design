import {getCurrentDate} from "../../utils";

const cheerio = require('cheerio')
import logger from 'electron-log'
import {
  isAbsolutePath,
  hasProtocols,
  isHttps,
  fetch
} from "./utils"
import { addTaskInfo } from "../database/task"
// @ts-ignore
import buildElectronApp from "../../../../packages/electron-builder"
import {taskAddOptions} from "../../../common/types"

async function taskServices(taskInfo: taskAddOptions) {
  await addBuilderTask(taskInfo)
  const curTime = getCurrentDate()
  let defaultIconPath = 'https://www.electronjs.org//images/favicon.b7a59262df48d6563400baf5671da548.ico'
  
  try {
    defaultIconPath = await getWebSiteIcon(taskInfo.parseUrl)
  } catch (e) {
    logger.error('解析网站图标错误', e)
  }
  
  await addTaskInfo(
    null,
    taskInfo.name,
    taskInfo.parseUrl,
    defaultIconPath,
    taskInfo.desc,
    curTime
  )
}

async function addBuilderTask(
  receiveData: taskAddOptions
) {
  logger.info('execute add task')
  
  const name = receiveData.name
  const outputDir = receiveData.outputDir
  const url = receiveData.parseUrl
  
  await buildElectronApp({
    parseUrl: url,
    outputDir: outputDir,
    appName: name
  })
  
  logger.info('add task finish')
}

async function getWebSiteIcon(url: string) {
  const htmlCode = await fetch(url)
  const $ = cheerio.load(htmlCode)
  const linksDomList = $('link')
  let iconPath = ''
  
  for (let i = 0; i < linksDomList.length; i++) {
    const attrs = linksDomList[i].attribs
    if (attrs.rel === 'icon' || attrs.rel === 'shortcut icon') {
      iconPath = attrs.href
      break
    }
  }
  
  if (!isAbsolutePath(iconPath)) {
    iconPath = url + iconPath
  }
  
  logger.info(`解析到的icon路径为${iconPath}`)
  return iconPath
}


export {
  taskServices
}

// CREATE TABLE IF NOT EXISTS `task_info`(
//   `task_id` INT UNSIGNED AUTO_INCREMENT,
//   `task_name` VARCHAR(100) NOT NULL,
//   `task_desc` VARCHAR(100) NOT NULL,
//   `task_status` INT,
//   `task_url` VARCHAR(40) NOT NULL,
//   `task_create_time` VARCHAR(40) NOT NULL,
//   `task_icon_url` VARCHAR(100) NOT NULL,
//   PRIMARY KEY ( `task_id` )
// )