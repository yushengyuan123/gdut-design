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

interface resData {
  code: number,
  message: string,
  data: any
}

_request.interceptors.response.use
((res: AxiosResponse<resData>) => {
  const data = res.data
  const { code, message } = data
  
  if (code !== 200) {
    ElMessage.error(message)
    return Promise.reject(message)
  }
  
  return data
}, (error => {
  ElMessage.error(error)
}))


export default _request