import * as electron from 'electron'
import { makeInstaller } from "../utils"

export const electronApi = makeInstaller(electron, '$electron')
export default electronApi