import Application from "./application"

const path = require("path")

process.env.CUR_MODE = 'debug'

const application = new Application()

export {
  application
}


