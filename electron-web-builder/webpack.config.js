// eslint-disable-next-line @typescript-eslint/no-var-requires
const path = require('path')
const webpack = require('webpack')

module.exports = {
  target: 'node',
  entry: ['./src/main/index.ts'],
  devServer: {
    // contentBase: path.resolve(__dirname, 'webpackOutput'),
    liveReload: true,
    historyApiFallback: true,
    port: 9090,
    compress: true
  },
  module: {
    rules: [
      {
        test: /\.ts$/,
        use: 'ts-loader', // https://webpack.js.org/guides/typescript/
        exclude: /node_modules/,
      },
    ],
  },
  node: {
    __dirname: false,
  },
  // Prevent bundling of certain imported packages and instead retrieve these
  // external deps at runtime. This is what we want for electron, placed in the
  // app by electron-packager. https://webpack.js.org/configuration/externals/
  externals: {
    electron: 'commonjs electron',
  },
  resolve: {
    extensions: [ '.ts', '.js' ],
  },
  output: {
    filename: 'main.js',
    path: path.resolve(__dirname, 'webpackOutput'),
  },
  mode: 'none',
  plugins: [
    new webpack.HotModuleReplacementPlugin()
  ],
}