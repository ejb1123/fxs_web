---
title: API Reference

language_tabs: # must be one of https://git.io/vQNgJ
  - shell: CURL
  - csharp: C#
  - lua: Lua

includes:
  - errors
  - log
  - players
  - server


search: true
---

# Introduction
**FXS-Web** is a **FXServer** component that extends the default HTTP server with custom data and endpoints.    
You can use this component for webservices or your **FiveM** resources.


# Is something wrong?

If you discover a bug or security vulnerability, please contact us on our [Discord](https://discord.gg/eNJraMf).


# Installation

## 1. Download FXS-WEB
>**components.json**

```json
{
  "net:base",
  "net:tcp-server",
  "net:http-server",
  "citizen:server:net",
  "citizen:scripting:core",
  "citizen:scripting:lua",
  "conhost:server",
  "citizen:server:main",
  "citizen:server:instance",
  "citizen:server:impl",
  "citizen:resources:core",
  "citizen:resources:metadata:lua",
  "vfs:core",
  "vfs:impl:server",
  "scripting:server",
  "svadhesive",
  "citizen:scripting:mono",
  "fs:data"
}
```

The first thing todo is getting **FXS-Web** from our repository.    
Copy **fs-web.dll** to your **FXServer** root folder.    
After the dll has been placed in the root folder, open **components.json** and add **"fs:web"**.


![alt text](fxfolder.png "FXServer directory")

## 2. Setup authentication
>**Server.cfg**

```
endpoint_add_tcp "0.0.0.0:30120"
endpoint_add_udp "0.0.0.0:30120"

start mapmanager
start chat
start spawnmanager
start fivem
start hardcap
start rconlog

sv_scriptHookAllowed 1

# change this
rcon_password temp16

sv_hostname "FXServer test!"

# nested configs!
#exec server_internal.cfg

# loading a server icon (96x96 PNG file)
#load_server_icon myLogo.png

# convars for use from script
set temp_convar "hey world!"

# FXS-WEB
set FX_USERNAME admin
set FX_PASSWORD demo
```

We need to configure the username and password to use **FXS-Web**.    
Go to your **server.cfg** and add the following lines

|Parameter|Description|
|---|---|
|set FX_USERNAME|This is the username to authenticate to the API|
|set FX_PASSWORD|This is the password to authenticate to the API|

# Authentication
```shell
# The code below is an example on howto use basic auth.
curl --request GET \
  --url https://example.com/fsdata/players \
  --basic \
  --user 'admin:demo'
```

```lua
local auth = "admin:demo"
PerformHttpRequest("https://example.com/fsdata/players", function(err, rText, headers)
if err == 0 then
  print("-------------------------------------------------------------")
  print("--- You have been successfully authenticated              ---")
  print("-------------------------------------------------------------")
else
  print("--------------------------------------------------------------")
  print("--- Error detected ( " .. err .. " ): " .. rText               )
  print("--------------------------------------------------------------")
 end
end, "GET", "", {["Content-Type"] = "application/json", Authorization = "Basic " .. auth})

```

You will need to authenticate for each request that you make to **FXS-Web**.    
You can authenticate by using **Basic Auth**.
