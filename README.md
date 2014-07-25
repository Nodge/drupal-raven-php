Raven-php for Drupal
====================

[Raven-php](https://github.com/getsentry/raven-php) is a PHP client for
[Sentry](http://aboutsentry.com/).
This module allows for integration of
[Raven-php](https://github.com/getsentry/raven-php) client into Drupal.

[Sentry](http://aboutsentry.com/) is a realtime event logging and
aggregation platform. It specializes in monitoring errors and extracting
all the information needed to do a proper post-mortem without
any of the hassle of the standard user feedback loop.


## Features

This module logs errors in a few ways:

* Register error handler for uncaught exceptions
* Register error handler for php errors
* Register error handler for fatal errors
* Handle watchdog messages

You can choose which errors you want to catch by enabling
desired error handlers and select error levels.


## Installation for Drupal 7

Download and install the [Libraries API 2](http://drupal.org/project/libraries)
module and the Raven-php module as normal. Then download the
[Raven-php client library](https://github.com/getsentry/raven-php/releases).

Unpack and rename the library directory to "raven" and
place it inside the `sites/all/libraries` directory.
Make sure the path to the library files
becomes like this: `sites/all/libraries/raven/lib/Raven/Client.php`.


## Dependencies

* The [Raven-php client library](https://github.com/getsentry/raven-php)
installed in `sites/all/libraries`
* [Libraries API 2](http://drupal.org/project/libraries)


## Information for developers

You can attach an extra information to error reports (logged in user details,
modules versions, etc). See `raven.api.php` for examples.


## Sponsors

This project was sponsored by [Seenta](http://seenta.ru/).
