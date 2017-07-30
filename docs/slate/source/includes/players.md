# Players


## Get All Players

To retrieve a list of all the current players on the server send a **GET** request to `/fsdata/players/`    
The response will be a JSON object contain the following attributes:    

Name | Description
----------|-----------
adress  | This is the players IP adress .
coords  | This will return the players position.
identifiers  | This will return the ip and steam id.
lastseen  | This will return the time that we have seen the player on the server in milliseconds
name  | This will return the players gamertag.
netbase |
netid | this will return the network id for the player
tcpendpoint |


```shell
curl --request GET \
  --url https://example.com/fsdata/players \
  --user 'admin:demo'
```


>**The above command returns JSON structured like this:**    

```json
{"players":[
  {
    "adress":"[::ffff:127.0.0.1]:50169",
    "coords":{"x":657.722717285156,"y":457.3427734375,"z":144.638854980469},
    "guid":"148618792060534757",
    "identifiers":["ip:127.0.0.1"],
    "lastseen":65137022,
    "name":"ejb1123",
    "netbase":62369531,
    "netid":1,
    "tcpendpoint":"127.0.0.1"
  }
 ]}
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
