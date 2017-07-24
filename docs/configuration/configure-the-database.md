---
title: "Database settings"
excerpt: ""
---
[block:api-header]
{
  "type": "basic",
  "title": "1. Configure your database credentials"
}
[/block]
open **.env **  and change the database settings
[block:code]
{
  "codes": [
    {
      "code": "DB_HOST=localhost\nDB_DATABASE=homestead\nDB_USERNAME=homestead\nDB_PASSWORD=secret",
      "language": "text",
      "name": ".env"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "2. Install database tables"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "php artisan migrate install\nphp artisan migrate",
      "language": "shell",
      "name": "Shell"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "3. Import required database settings"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "php artisan db:seed",
      "language": "shell"
    }
  ]
}
[/block]