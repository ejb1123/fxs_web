---
title: API Reference

language_tabs: # must be one of https://git.io/vQNgJ
  - lua
  - csharp: C#

toc_footers:
  - <a href='#'>Sign Up for a Developer Key</a>
  - <a href='https://github.com/tripit/slate'>Documentation Powered by Slate</a>

includes:
  - players
  - errors
 

search: true
---

# Introduction
**fs_fxs-web** is a **FXServer** component that adds custom endpoints to the existing HTTP server.

# Is something wrong?

If our documentation is missing something, please feel to contribute!
You can click on the Suggest Edits link on the top right side of any documentation page.

# Installation

## 1. Download FXS-WEB
    Download FXS-WEB from our repository then copy **fs-web.dll** to your **FXServer** root folder  
    Then open **composer.json** and add **"fs:web"**  this should look like on the right

```JSON
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
  "fs:data",
  "svadhesive",
  "citizen:scripting:mono"
}
```
## 2. Configure the authentication

We need to configure the username and password to use FSX-WEB.
Go to your **server.cfg** and add the following lines

|Parameter|Description|
|---|---|
|set FX_USERNAME|This is the username to authenticate to the API|
|set FX_PASSWORD|This is the password to authenticate to the API|

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
set FX_USERNAME www-data
set FX_PASSWORD temp16
```

# Authentication

fxs_web uses HTTP Basic Auth

