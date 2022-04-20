import initTaskRouter from "./taskController"

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
