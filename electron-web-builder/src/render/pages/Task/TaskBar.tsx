import {defineComponent, reactive, ref} from "vue"
// @ts-ignore
import TaskBarCss from './TaskBar.less'
// @ts-ignore
import playIcon from '../../asserts/play.png'

console.log(TaskBarCss)

const TaskBar = defineComponent({
  name: 'TaskBar',
  setup(props, context) {
    const taskListItem: Array<{
      id: number,
      value: string
    }> = ['下载中', '已停止', '等待中'].map((value, index) => {
      return {
        id: index,
        value: value
      }
    })
    
    return () => (
      <div class="task-status-list-con">
        <div class="task-list-title">任务列表</div>
        <div class="task-status-list-con">
          {
            taskListItem.map((item, index) => {
              return (
                <div class="task-status-item">
                  <div class="task-status-icon-con">
                    <img style="height:20px; width:16px;" class="task-status-icon" src={playIcon} alt=""/>
                  </div>
                  <div class="task-status-text">{item.value}</div>
                </div>
              )
            })
          }
        </div>
      </div>
    )
  },
})

export default TaskBar