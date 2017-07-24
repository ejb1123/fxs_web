---
title: "BrowserSync"
excerpt: ""
---
**BrowserSync **can automatically monitor files for changes, and inject the changes into the browser without requiring a manual refresh
[block:api-header]
{
  "title": "Configuration"
}
[/block]
We need to configure the proxy url before we can use **BrowserSync**.
Open **webpack.mix.js** and change **localhost:8000** to your web server url.
[block:code]
{
  "codes": [
    {
      "code": "const { mix } = require('laravel-mix');\n\n/*\n |--------------------------------------------------------------------------\n | Mix Asset Management\n |--------------------------------------------------------------------------\n |\n | Mix provides a clean, fluent API for defining some Webpack build steps\n | for your Laravel application. By default, we are compiling the Sass\n | file for the application as well as bundling up all the JS files.\n |\n */\n\n mix.js('resources/assets/js/app.js', 'public/js')\n    .sass('resources/assets/sass/app.scss', 'public/css');\n\n/*\n |--------------------------------------------------------------------------\n | BrowserSync\n |--------------------------------------------------------------------------\n |\n | BrowserSync will automatically monitor your files for changes, and insert\n | your changes into the browser, all without requiring a manual refresh.\n |\n */\n\n mix.browserSync({proxy: 'localhost:8000'});",
      "language": "javascript",
      "name": "webpack.mix.js"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "Run BrowserSync"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "npm run watch",
      "language": "shell"
    }
  ]
}
[/block]
After that a new browser window will open http://127.0.0.1:3000