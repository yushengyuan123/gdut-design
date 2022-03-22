const bindings = process._linkedBinding('electron_browser_app');

const { app } = bindings;

export default app;