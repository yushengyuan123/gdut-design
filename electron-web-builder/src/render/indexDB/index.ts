

function initIndexDb() {
  const req = indexedDB.open('electron-web-builder', 1)
  
  req.addEventListener('success', e => {
    console.log('数据库连接成功')
  })
  
  req.addEventListener('error', e => {
    console.log('数据库连接失败', e)
  })
}

export {
  initIndexDb
}
