interface ColValues<T = any, R = any> {
  columns: T,
  value: R
}

type taskTableColumn =
  'task_id' |
  'task_name' |
  'task_url' |
  'task_icon_url' |
  'task_desc' |
  'task_create_time'

type insertFunc = (
  tableName: string,
  colValues: ColValues[],
  where: string
) => void

type selectFunc = (

) => void

interface connInstance {
  insert: insertFunc,
  select: selectFunc,
  connect: Function
}

export {
  connInstance,
  insertFunc,
  selectFunc,
  taskTableColumn,
  ColValues
}