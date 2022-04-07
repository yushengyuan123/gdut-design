import initTaskRouter from "./addTask"

const routerFunc = [
  initTaskRouter
]

function registerKoaApiRouter() {
  routerFunc.forEach(func => {
    func()
  })
}

export {
  registerKoaApiRouter
}
