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
            <theme-switcher />
          </el-col>
        </el-form-item>
        <el-form-item
            label="启动:"
            :label-width="formLabelWidth"
        >
            <el-checkbox v-model="basicSettingsForm.autoStartup">
              开机时启动
            </el-checkbox>
        </el-form-item>
        <el-form-item
            label="默认下载路径:"
            :label-width="formLabelWidth"
        >
          <el-input v-model="basicSettingsForm.downloadDefaultDir" size="default"/>
        </el-form-item>
        <el-form-item
            label="缓存路径:"
            :label-width="formLabelWidth"
        >
          <el-input v-model="basicSettingsForm.cachePath" size="default"/>
        </el-form-item>
      </el-form>
      <div class="form-actions">
        <el-button type="primary" size="default">
          保存并应用
        </el-button>
        <el-button size="default">
          放弃
        </el-button>
      </div>
    </el-main>
  </el-container>
</template>

<script lang="ts">
import {defineComponent, reactive, ref} from "vue";
import themeSwitch from './theme-switcher.vue'
import {
  usePreferenceStore,
} from "../../pinia/preference";
import { storeToRefs } from "pinia"

import type {
  basicSettings
} from "../../pinia/preference";

export default defineComponent({
  name: "base-settings",
  components: {
    [themeSwitch.name]: themeSwitch
  },
  setup() {
    const formLabelWidth = ref<string>('25%')
    const preferenceStore = usePreferenceStore()
    const {
      appThemeColor,
      autoStartup,
      downloadDefaultDir,
      cachePath
    } = storeToRefs(preferenceStore)

    const basicSettingsForm = reactive<basicSettings>({
      appThemeColor: appThemeColor,
      autoStartup: autoStartup,
      downloadDefaultDir: downloadDefaultDir,
      cachePath: cachePath
    })

    return {
      formLabelWidth,
      basicSettingsForm
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