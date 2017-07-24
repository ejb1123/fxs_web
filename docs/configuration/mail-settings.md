---
title: "Mail settings"
excerpt: ""
---
[block:parameters]
{
  "data": {
    "3-0": "Sendmail",
    "2-0": "PHP mail function",
    "0-0": "Amazon SES",
    "1-0": "MailGun",
    "5-0": "SparkPost",
    "4-0": "SMTP",
    "h-0": "Supported drivers"
  },
  "cols": 1,
  "rows": 6
}
[/block]
Open your **.env** file and change the **MAIL** values with your credentials.
[block:parameters]
{
  "data": {
    "0-0": "MAIL_DRIVER=smtp",
    "5-0": "MAIL_ENCRYPTION=null",
    "4-0": "MAIL_PASSWORD=null",
    "3-0": "MAIL_USERNAME=null",
    "2-0": "MAIL_PORT=2525",
    "1-0": "MAIL_HOST=mailtrap.io",
    "h-0": "Key",
    "h-1": "Description",
    "0-1": "This is the driver that we use to send mail",
    "1-1": "This is the hostname from your outgoing mail server",
    "2-1": "This is the outgoing port for your outgoing server.",
    "3-1": "Enter your username or email address for the outgoing server.",
    "4-1": "Enter your password for the outgoing server.",
    "5-1": "This is used if your outgoing server has SSL configured."
  },
  "cols": 2,
  "rows": 6
}
[/block]