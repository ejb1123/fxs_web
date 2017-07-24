---
title: "Setup component"
excerpt: ""
---
[block:api-header]
{
  "title": "1.Download FXS-WEB"
}
[/block]
Download FXS-WEB from our repository then copy **fs-web.dll** to your **FXServer ** root folder 
Then open **composer.json** and add **"fs:web"**  this should look like below
[block:code]
{
  "codes": [
    {
      "code": "[\n  \"net:base\",\n  \"net:tcp-server\",\n  \"net:http-server\",\n  \"citizen:server:net\",\n  \"citizen:scripting:core\",\n  \"citizen:scripting:lua\",\n  \"conhost:server\",\n  \"citizen:server:main\",\n  \"citizen:server:instance\",\n  \"citizen:server:impl\",\n  \"citizen:resources:core\",\n  \"citizen:resources:metadata:lua\",\n  \"vfs:core\",\n  \"vfs:impl:server\",\n  \"scripting:server\",\n  \"svadhesive\",\n  \"citizen:scripting:mono\",\n  \"fs:web\"\n]",
      "language": "json",
      "name": "composer.json"
    }
  ]
}
[/block]

[block:api-header]
{
  "type": "basic",
  "title": "2. Configure the authentication"
}
[/block]
We need to configure the username and password to use FSX-WEB.
Go to your **server.cfg** and add the following lines
[block:parameters]
{
  "data": {
    "h-0": "Parameter",
    "h-1": "Description",
    "0-0": "set FX_USERNAME",
    "0-1": "This is the username to authenticate to the API",
    "1-0": "set FX_PASSWORD",
    "1-1": "This is the password to authenticate to the API"
  },
  "cols": 2,
  "rows": 2
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "endpoint_add_tcp \"0.0.0.0:30120\"\nendpoint_add_udp \"0.0.0.0:30120\"\n\nstart mapmanager\nstart chat\nstart spawnmanager\nstart fivem\nstart hardcap\nstart rconlog\n\nsv_scriptHookAllowed 1\n\n# change this\nrcon_password temp16\n\nsv_hostname \"FXServer test!\"\n\n# nested configs!\n#exec server_internal.cfg\n\n# loading a server icon (96x96 PNG file)\n#load_server_icon myLogo.png\n\n# convars for use from script\nset temp_convar \"hey world!\"\n\n# FXS-WEB\nset FX_USERNAME www-data\nset FX_PASSWORD temp16",
      "language": "text",
      "name": "server.cfg"
    }
  ]
}
[/block]