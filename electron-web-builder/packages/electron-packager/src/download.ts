import { downloadArtifact } from '@electron/get'
import * as debug from 'debug'

async function downloadElectronZip() {
  debug(`Downloading Electron`)
  
  return await downloadArtifact({
    version: '18.0.0',
    platform: 'darwin',
    artifactName: 'electron',
    arch: 'x64',
  })
}



export {
  downloadElectronZip
}