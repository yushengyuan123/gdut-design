import logger from 'electron-log'
import {
  ColValues
} from "./types"

function wrapperBrace(str: string) {
  return `(` + str + ')'
}

function wrapperInsert(
  tableName: string,
  columns: string,
  values: string,
  where: string
) {
  return `insert into ${tableName} ${columns} values ${values} where ${where}`
}

function insertSql<colType = any>(
  tableName: string,
  colValues: ColValues<colType>[],
  where: string
) {
  const len = colValues.length
  
  let columnsTemplateString = ``
  let valuesTemplateString = ``
  
  colValues.forEach((item: ColValues, index: number) => {
    if (index !== len - 1) {
      columnsTemplateString += item.columns + ','
      valuesTemplateString += item.columns + ','
    } else {
      columnsTemplateString += item.columns
      valuesTemplateString += item.columns
    }
  })
  
  columnsTemplateString = wrapperBrace(columnsTemplateString)
  valuesTemplateString = wrapperBrace(valuesTemplateString)
  
  const sql = wrapperInsert(tableName, columnsTemplateString, valuesTemplateString, where)
  
  logger.warn(`execute sql $sql`)
  
  return sql
}

function selectSql() {

}

export {
  insertSql,
  selectSql,
}