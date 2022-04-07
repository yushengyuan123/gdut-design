import axios, {Axios, AxiosResponse} from "axios"
import { ElMessage } from 'element-plus'

const basicUrl = 'http://localhost:8080'

const _request: Axios = axios.create({
  baseURL: basicUrl,
  headers: {
    'Content-Type': 'application/json',
  },
})

_request.interceptors.request.use(config => {
  return config
}, (error) => {
  ElMessage.error(error)
})

_request.interceptors.response.use((res: AxiosResponse) => {
  return res.data
}, (error => {
  ElMessage.error(error)
}))

export default _request