<template>
  <el-container>
    <el-header class="panel-header">
      <div class="settings-header header-title">基础设置</div>
    </el-header>
    <el-main class="panel-content">
      <el-form
          class="form-preference"
          size="mini"
      >
        <el-form-item
            :modal="basicSettingsForm"
            label="外观:"
            :label-width="formLabelWidth"
        >
          <el-col class="form-item-sub" :span="24">
            <theme-switcher/>
          </el-col>
        </el-form-item>
        <el-form-item
            label="启动:"
            :label-width="formLabelWidth"
        >
          <el-checkbox
              v-model="basicSettingsForm.autoStartup"
              @change="inputChange"
          >
            开机时启动
          </el-checkbox>
        </el-form-item>
        <el-form-item
            label="默认下载路径:"
            :label-width="formLabelWidth"
        >
          <el-input
              v-model="basicSettingsForm.downloadDefaultDir"
              size="default"
              @change="inputChange"
          />
        </el-form-item>
        <el-form-item
            label="使用缓存路径加速:"
            :label-width="formLabelWidth"
        >
          <el-input
              v-model="basicSettingsForm.cachePath"
              size="default"
              @change="inputChange"
          />
        </el-form-item>
      </el-form>
      <div class="form-actions">
        <el-button
            type="primary"
            size="default"
            @click="saveSettings"
        >
          保存并应用
        </el-button>
        <el-button
            size="default"
            @click="dropSettings"
        >
          放弃
        </el-button>
      </div>
    </el-main>
  </el-container>
</template>

<script lang="ts">
import {defineComponent, reactive, ref, toRaw} from "vue";
import themeSwitch from './theme-switcher.vue'
import {
  usePreferenceStore,
} from "../../pinia/preference";
import { onBeforeRouteLeave } from 'vue-router'
import {
  setUserPreference
} from "../../storage"

import type {
  basicSettings
} from "../../pinia/preference";
import {
  ElMessageBox,
  ElMessage
} from "element-plus";

export default defineComponent({
  name: "base-settings",
  components: {
    [themeSwitch.name]: themeSwitch
  },
  setup() {
    const formLabelWidth = ref<string>('25%')
    const preferenceStore = usePreferenceStore()
    const basicSettingsForm = reactive<basicSettings>({
      appThemeColor: preferenceStore.appThemeColor,
      autoStartup: preferenceStore.autoStartup,
      downloadDefaultDir: preferenceStore.downloadDefaultDir,
      cachePath: preferenceStore.cachePath
    })
    let oldThemeColor = basicSettingsForm.appThemeColor
    let hasChange = false

    const saveSettings = () => {
      const { appThemeColor } = preferenceStore
      basicSettingsForm.appThemeColor = appThemeColor

      ElMessageBox.confirm('你确定保存更改吗？', {
        title: '操作确认',
        confirmButtonText: '确定',
        cancelButtonText: '取消'
      }).then(() => {
        hasChange = false
        oldThemeColor = preferenceStore.appThemeColor
        const rawValue = toRaw(basicSettingsForm)
        setUserPreference(rawValue)
        preferenceStore.updateCachePath(basicSettingsForm.cachePath)
        preferenceStore.updateStartupSet(basicSettingsForm.autoStartup)
        preferenceStore.updateDownloadPath(basicSettingsForm.downloadDefaultDir)
        ElMessage({
          message: '保存成功！',
          type: 'success',
        })
      })
    }

    const inputChange = () => {
      hasChange = true
    }

    const dropSettings = () => {
      preferenceStore.updateAppThemeColor(oldThemeColor)
      basicSettingsForm.downloadDefaultDir = preferenceStore.downloadDefaultDir
      basicSettingsForm.autoStartup = preferenceStore.autoStartup
      basicSettingsForm.cachePath = preferenceStore.cachePath
    }

    onBeforeRouteLeave((to, from, next) => {
      const curThemeColor = preferenceStore.appThemeColor
      if (!hasChange &&
          curThemeColor === oldThemeColor) {
        next()
        return
      }
      ElMessageBox.confirm('你的更改上没有保存，你确定要离开吗？', {
        title: '操作确认',
        confirmButtonText: '确定',
        cancelButtonText: '取消'
      }).then(() => {
        preferenceStore.updateAppThemeColor(oldThemeColor)
        next()
      }).catch(() => {
        next(false)
      })
    })

    return {
      formLabelWidth,
      basicSettingsForm,
      inputChange,
      saveSettings,
      dropSettings,
    }
  }
})
</script>

<style scoped lang="less">
.panel-content {
  position: relative;
}

.settings-header {
  width: 100%;
  font-size: 15px;
}

.form-preference {
  position: relative;
  padding: 20px 10% 64px 16px;
}

.form-actions {
  padding: 24px 36px;
  position: absolute;
  bottom: 0;
  left: auto;
  z-index: 10;
}
</style>