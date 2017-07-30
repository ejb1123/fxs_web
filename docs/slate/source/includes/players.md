# Players


## Get All Players

To retrieve a list of all the current players on the server send a **GET** request to `/fsdata/players/`

Parameter | Description
----------|-----------
coords  | This will return the screen coordniates .
identifiers  | This will return the ip and steam id.
name  | This will return the gamertag.

```shell
curl --request GET \
  --url https://example.com/fsdata/players.json \
  --user 'admin:demo'
```


>**The above command returns JSON structured like this:**    

```json
{"players":[{"coords": {"x":0,"y":0,"z":0},"identifiers":["ip:127.0.0.1"],"name":"Streetcorps"}]}
```

## Get a Specific Player

To get information about a specific player, send a **GET** request to `/fsdata/players/{net_id}`

**URL Parameters**

Parameter|Description
---------|-----------
net_id   | This is the id of the player.


## Actions

To perform a task on a specific player send a **GET** request to `/fsdata/players/{net_id}/actions/{action}`

**URL Parameters**

Parameter|Description
---|---
action|s
net_id| This is the id of the player

###  **Available Actions**

  Action|Description
  ---|---
  kick| Kicks the palyer.
  ban| Bans the player.
  message|Sends a message to the player.
