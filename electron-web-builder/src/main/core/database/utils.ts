import logger from 'electron-log'
import {
  ColValues, connInstance
} from "./types"
import {application} from "../../index"

function wrapperBrace(str: string) {
  return `(` + str + ')'
}

function wrapperInsert(
  tableName: string,
  columns: string,
  values: string,
) {
  return `insert into ${tableName} ${columns} values ${values}`
}

function wrapperSelect(
  tableName: string,
  columns: string,
  where: string | null
) {
  if (!where) {
    return `select ${columns} from ${tableName}`
  }
  return `select ${columns} from ${tableName} where ${where}`
}

function wrapperDelete(
  tableName: string,
  where: string
) {
  return `delete from ${tableName} where ${where}`
}

function executeSql(
  sql: string
): Promise<any> {
  const conInstance = application.getMysqlConnectObj()
  return new Promise((resolve, reject) => {
    conInstance.query(sql, (err: string, res: any) => {
      if (err) {
        logger.error('mysql语句执行失败，失败原因', err)
        reject(false)
      } else {
        resolve(res)
      }
    })
  })
}

function wrapperQuote(str: string) {
  return "'" + str + "'"
}

async function insertSql<colType = any>(
  tableName: string,
  colValues: ColValues<colType>[],
) {
  const len = colValues.length
  
  let columnsTemplateString = ``
  let valuesTemplateString = ``
  
  colValues.forEach((item: ColValues, index: number) => {
    if (item.value) {
      item.value = wrapperQuote(item.value)
    }
    
    if (index !== len - 1) {
      columnsTemplateString += item.columns + ','
      valuesTemplateString += item.value + ','
    } else {
      columnsTemplateString += item.columns
      valuesTemplateString += item.value
    }
  })
  
  columnsTemplateString = wrapperBrace(columnsTemplateString)
  valuesTemplateString = wrapperBrace(valuesTemplateString)
  
  const sql = wrapperInsert(tableName, columnsTemplateString, valuesTemplateString)
  
  logger.warn(`execute sql ${sql}`)
  
  await executeSql(sql)
}

async function selectSql<R = any, T extends R[] = R[]>(
  tableName: string,
  columns: T,
  where: string | null
): Promise<any[]> {
  let columnValueStr = ``
  const len = columns.length
  
  columns.forEach((item, index) => {
    if (index !== len - 1) {
      columnValueStr += item + ','
    } else {
      columnValueStr += item
    }
  })
  
  if (where) {
    where = wrapperBrace(where)
  }
  
  const sql = wrapperSelect(tableName, columnValueStr, where)
  
  logger.warn(`execute sql ${sql}`)
  
  return await executeSql(sql)
}

async function deleteSql(
  tableName: string,
  where: string
) {
  const sql = wrapperDelete(tableName, where)
  
  logger.warn(`execute sql ${sql}`)
  
  await executeSql(sql)
}

export {
  insertSql,
  selectSql,
  deleteSql
}