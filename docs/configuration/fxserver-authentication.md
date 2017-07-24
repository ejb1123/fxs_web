---
title: "FXServer Authentication"
excerpt: ""
---
Open your .env file and change the values for FX_
[block:parameters]
{
  "data": {
    "h-0": "Key",
    "h-1": "Description",
    "0-0": "**FX_IP** ",
    "0-1": "This is the IP address from your FXServer",
    "1-0": "**FX_PORT** ",
    "2-0": "**FX_USERNAME** ",
    "3-0": "**FX_PASSWORD** ",
    "1-1": "This is the port from your FXServer",
    "2-1": "This is the username that is used for authenticating the API",
    "3-1": "This is the password that is used for authenticating the API"
  },
  "cols": 2,
  "rows": 4
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "FX_IP=127.0.0.1\nFX_PORT=30120\nFX_USERNAME=null\nFX_PASSWORD=null",
      "language": "yaml",
      "name": ".env"
    }
  ]
}
[/block]