<template>
  <div class="task-list-outer" v-if="finishList.length > 0">
    <el-row
        v-for="(rowItem, index) in finishList"
        type="flex"
        :justify="'center'"
        style="margin-bottom: 20px"
    >
      <el-col :span="10" v-for="(item, index) in rowItem.rowElement" :key="item.taskId" :offset="index > 0 ? 2 : 0">
        <el-popover
            placement="top-start"
            title="描述"
            :content="item.taskDesc"
        >
          <template #reference>
            <el-card style="cursor: pointer" :body-style="{ padding: '0px' }">
              <div class="task-actions-con">
                <task-actions
                    @deleteTask="removeTask"
                />
              </div>
              <div class="task-icon-con">
                <img
                    class="task-icon"
                    src="https://shadow.elemecdn.com/app/element/hamburger.9cf7b091-55e9-11e9-a976-7f4d0b07eef6.png" c
                >
              </div>
              <div class="task-info-con">
                <span>{{item.taskName}}</span>
                <div class="time-con">
                  <time class="time">创建时间:{{item.createDate}}</time>
                </div>
              </div>
            </el-card>
          </template>
        </el-popover>
      </el-col>
    </el-row>
<!--    <div v-for="taskItem in taskList" class="task-item-con">-->
<!--      <div class="task-item-name">-->
<!--        <span>{{taskItem.taskName}}</span>-->
<!--      </div>-->
<!--      <div class="task-item-name">-->
<!--        <span>{{taskItem.taskName}}</span>-->
<!--      </div>-->
<!--      <task-actions />-->
<!--    </div>-->
  </div>
  <div v-else class="no-task">
    <div class="no-task-inner">
      当前没有已经完成的任务
    </div>
  </div>
</template>

<script lang="ts">
import { defineComponent, ref } from "vue";
import taskActions from './task-action.vue'

/**
 * 需要描述，名字，创建的logo图片，创建时间
 */
interface finishListData {
  taskName: string,
  taskId: number,
  createDate: string,
  taskDesc: string
}

interface rowTaskData<R = finishListData> {
  row: number,
  rowElement: R[]
}

export default defineComponent({
  name: 'finish-list',
  components: {
    [taskActions.name]: taskActions,
  },
  setup() {
    const originListData: finishListData[] = [{
      taskName: '123',
      taskId: 1,
      createDate: '2022 11 1',
      taskDesc: '简单描述'
    },{
      taskName: '123',
      taskId: 2,
      createDate: '2022 11 1',
      taskDesc: '简单描述'
    },{
      taskName: '123',
      taskId: 3,
      createDate: '2022 11 1',
      taskDesc: '简单描述'
    }]
    const rowCount = Math.floor(originListData.length / 2)
    const rowTaskListData: rowTaskData[] = []
    for (let i = 0; i < rowCount; i++) {
      rowTaskListData.push({
        row: i + 1,
        rowElement: originListData.slice(i * 2, (i * 2) + 2)
      })
    }

    if (originListData.length % 2) {
      rowTaskListData.push({
        row: rowTaskListData.length + 1,
        rowElement: [originListData[originListData.length - 1]]
      })
    }

    console.log(rowTaskListData)

    const finishList = ref<rowTaskData[]>(rowTaskListData)

    const removeTask = () => {
      console.log('移除任务')
    }

    return {
      finishList,
      removeTask
    }
  }
})
</script>

<style scoped lang="less">
.task-list-outer {
  width: 100%;
  padding: 0 20px;
  box-sizing: border-box;
  margin-top: 30px;
}
.task-icon-con {
  display: flex;
  justify-content: center;
  align-items: center;
  margin-bottom: 10px;
  .task-icon {
    height: 150px;
    border-radius: 50%;
    margin-top: 10px;
  }
}
.task-actions-con {
  height: 30px;
  padding: 5px;

  &::after {
    content: '';
    clear: both;
  }
}
.task-info-con {
  padding: 0 14px 10px;

  span {
    color: #4D515A;
    font-size: 16px;
  }

  .time-con {
    margin-top: 10px;
    font-size: 14px;
  }
}
</style>