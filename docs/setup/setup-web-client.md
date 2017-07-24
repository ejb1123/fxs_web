---
title: "Setup web client"
excerpt: ""
---
[block:api-header]
{
  "title": "1 Get the latest version from Github"
}
[/block]
**FXS-WEB** is constantly evolving, we advise you to download the latest release.
[block:code]
{
  "codes": [
    {
      "code": "cd /var/www \ngit clone ",
      "language": "shell",
      "name": " "
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "2 Install the framework"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "cd fxs-web\ncomposer install",
      "language": "shell"
    }
  ]
}
[/block]

[block:callout]
{
  "type": "info",
  "body": "By default **FXS-WEB** comes with a .env.example file.\nYou need to **rename **this file to **.env** regardless of what environment you're working on."
}
[/block]

[block:api-header]
{
  "title": "3. Auto generate key for .env"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "php artisan key:generate",
      "language": "shell"
    }
  ]
}
[/block]