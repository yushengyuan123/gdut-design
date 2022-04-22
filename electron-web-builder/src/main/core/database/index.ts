// @ts-ignore
import { createConnection } from 'mysql'
import logger from "electron-log"
import databaseConfig from "./config"
import {
  insertSql,
  selectSql
} from "./utils"
import {
  connInstance
} from "./types"

function connectMysql(): connInstance {
  logger.info('连接数据库')
  
  const sqlTpl = {
    'insert': insertSql,
    'select': selectSql
  }
  
  const con = createConnection({
    host: databaseConfig.host,
    user: databaseConfig.user,
    password: databaseConfig.password,
    database: databaseConfig.database
  })
  
  initSqlTemplate(con, sqlTpl)
  
  return con
}

function initSqlTemplate<R extends Object, Tpl extends Object>(
  connectInstance: R,
  sqlTemplateFunc: Tpl
) {
  for (const key in sqlTemplateFunc) {
    // @ts-ignore
    connectInstance[key] = sqlTemplateFunc[key]
  }
}


export {
  connectMysql,
  initSqlTemplate
}