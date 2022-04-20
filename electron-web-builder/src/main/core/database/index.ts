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

// try {
//   connect = connectMysql()
//
//   connect.connect()
//
//   const sql = "insert into task_info (task_id, task_name, task_url, task_icon_url, task_desc, task_create_time) values (null, 'whatsapp', 'www.baidu.com', '123', 'nihao', '2021')"
//   connect.query(sql,function(err: any,rows: any,fields: any){
//     if(err) {
//       console.log(err)
//     } else{
//       console.log(rows)
//     }
//
//     connect.end()
//   })
// } catch (e) {
//   logger.error('数据库连接失败', e)
// }


export {
  connectMysql,
  initSqlTemplate
}