# Server

```shell
curl --request GET \
     --url https://example.com/fsdata/server.json
     --basic \
     --user 'admin:demo'
```

>**The above command returns JSON structured like this:**    

```json
{"name":"FXServer test!",
"resources":
{"_cfx_internal":{"state":"started"},
"baseevents":{"state":"stopped"},
"betaguns":{"state":"stopped"},
"channelfeed":{"state":"stopped"},
"chat":{"state":"started"},
"es_admin":{"state":"started"},
"essentialmode":{"state":"started"},
"fivem":{"state":"stopped"},
"fivem-awesome1501":{"state":"stopped"},
"fivem-map-hipster":{"state":"stopped"},
"fivem-map-skater":{"state":"started"},
"fs_freeroam":{"state":"started"},
"gameInit":{"state":"stopped"},
"irc":{"state":"stopped"},
"keks":{"state":"stopped"},
"mapmanager":{"state":"started"},
"obituary":{"state":"stopped"},
"obituary-deaths":{"state":"stopped"},
"race":{"state":"stopped"},
"race-test":{"state":"stopped"},
"rconlog":{"state":"started"},
"scoreboard":{"state":"stopped"},
"sessionmanager":{"state":"started"},
"spawnmanager":{"state":"started"}},
"totalPlayers":1}
```
To retrieve information from the server send a GET request to `/fsdata/server`.    
The response will be a JSON object contain the following attributes:

Parameter|Description
---------|-----------
name | This will return the server name.
resources | This will return all the resoources and the state of it.
totalPlayers | This will return a total of the connected players.
