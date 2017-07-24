---
title: "PHP CodeSniffer"
excerpt: ""
---
PHP CodeSniffer is a set of two PHP scripts; the main phpcs script that tokenizes PHP, JavaScript and CSS files to detect violations of a defined coding standard, and a second phpcbf script to automatically correct coding standard violations. PHP_CodeSniffer is an essential development tool that ensures your code remains clean and consistent.
[block:api-header]
{
  "type": "basic",
  "title": "1. Installation"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "curl -OL https://squizlabs.github.io/PHP_CodeSniffer/phpcs.phar\nphp phpcs.phar -h\n\ncurl -OL https://squizlabs.github.io/PHP_CodeSniffer/phpcbf.phar\nphp phpcbf.phar -h",
      "language": "shell",
      "name": "Linux Shell"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "2. Copy the fines to /bin"
}
[/block]

[block:code]
{
  "codes": [
    {
      "code": "sudo mv phpcs.phar /bin/phpcs\nsudo mv phpcbf.phar /bin/phpcbf\n\nsudo chmod +x /bin/phpcs\nsudo chmod +x /bin/phpcbf\n",
      "language": "shell",
      "name": "Linux Shell"
    }
  ]
}
[/block]

[block:api-header]
{
  "title": "PHPCS Commands"
}
[/block]

[block:parameters]
{
  "data": {
    "h-0": "Task name",
    "h-1": "Description",
    "0-0": "phpcs -vvv",
    "0-1": "Print verbose output"
  },
  "cols": 2,
  "rows": 1
}
[/block]