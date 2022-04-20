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
) => void

type selectFunc<R = any, T extends R[] = R[]> = (
  tableName: string,
  columns: T,
  where: string | null
) => Promise<any[]>

type deleteFunc = (
  tableName: string,
  where: string
) => void

interface connInstance {
  insert: insertFunc,
  select: selectFunc,
  delete: deleteFunc,
  connect: Function,
  query: Function,
  end: Function
}

export {
  connInstance,
  insertFunc,
  selectFunc,
  deleteFunc,
  taskTableColumn,
  ColValues
}