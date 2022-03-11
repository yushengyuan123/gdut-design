const bindings = process._linkedBinding('electron_browser_app');

const app = bindings;

console.log("init 文件");

console.log(app);

export default app;