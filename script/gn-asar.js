/**
 * @description 这个文件的含义就是把参数files的文件拷贝到临时目录中，然后通过asar打包输出到参数out目录中
 * 使用之前需要先装包
 */

const asar = require('asar');
const assert = require('assert');
const fs = require('fs-extra');
const os = require('os');
const path = require('path');

// 函数的作用就是查看参数--xxx xxx xxx，把它加入到group数组中，return出去
const getArgGroup = (name) => {
  const group = [];
  let inGroup = false;
  for (const arg of process.argv) {
    // At the next flag we stop being in the current group
    if (arg.startsWith('--')) inGroup = false;
    // Push all args in the group
    if (inGroup) group.push(arg);
    // If we find the start flag, start pushing
    if (arg === `--${name}`) inGroup = true;
  }

  return group;
};

const base = getArgGroup('base');
const files = getArgGroup('files');
const out = getArgGroup('out');

assert(base.length === 1, 'should have a single base dir');
assert(files.length >= 1, 'should have at least one input file');
assert(out.length === 1, 'should have a single out path');

// Ensure all files are inside the base dir
for (const file of files) {
  if (!file.startsWith(base[0])) {
    console.error(`Expected all files to be inside the base dir but "${file}" was not in "${base[0]}"`);
    process.exit(1);
  }
}
// os.tmpdir() 以字符串形式返回操作系统默认的临时文件的目录。
// /var/folders/s2/w5skl87951x1sz4nvy1plfbc0000gn/T
// 获得一个临时的路径
const tmpPath = fs.mkdtempSync(path.resolve(os.tmpdir(), 'electron-gn-asar-'));

// 直到这里含义应该是把files的文件全部写到这个临时目录中
try {
  // Copy all files to a tmp dir to avoid including scrap files in the ASAR
  for (const file of files) {
    const newLocation = path.resolve(tmpPath, path.relative(base[0], file));
    fs.mkdirsSync(path.dirname(newLocation));
    fs.writeFileSync(newLocation, fs.readFileSync(file));
  }
} catch (err) {
  console.error('Unexpected error while generating ASAR', err);
  fs.remove(tmpPath)
    .then(() => process.exit(1))
    .catch(() => process.exit(1));
  return;
}

// Create the ASAR archive
// 利用这个asar把我们刚刚创建的临时文件打包，存放到这个out[0]目录中
asar.createPackageWithOptions(tmpPath, out[0], {})
  .catch(err => {
    const exit = () => {
      console.error('Unexpected error while generating ASAR', err);
      process.exit(1);
    };
    fs.remove(tmpPath).then(exit).catch(exit);
  }).then(() => fs.remove(tmpPath));
