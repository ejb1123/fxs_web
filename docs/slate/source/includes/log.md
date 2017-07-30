# Log

## Retrieve
```shell
curl --request GET \
  --url https://example.com/fsdata/log \
  --basic \
  --user 'admin:demo'
```


>**The above command returns JSON structured like this:**    

```json

```

To retrieve the log file from your **FXServer**, send a **GET** request to `/fsdata/log`.

## Actions

```shell
curl --request POST \
  --url https://example.com/fsdata/log/actions/{action} \
  --basic \
  --user 'admin:demo'
```


>**The above command returns JSON structured like this:**    

```json

```

You can use one of these predefined actions:

Name | Description
-----|------------
rotate | Backup the current log and create a new log file.
clear | Clears the current log file.
