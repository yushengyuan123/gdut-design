import dayjs from 'dayjs'

function getCurTimeSeconds() {
  return new Date().getTime()
}

function getCurrentDate() {
  const curSec = getCurTimeSeconds()
  return dayjs(curSec).format('YYYY-MM-DD HH:mm:ss')
}

export {
  getCurrentDate,
  getCurTimeSeconds
}