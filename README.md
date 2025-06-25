Node View Count
======================

Node View Count module counts node views. Unlike the statistics module, this
module records each view of a node with the user uid and timestamp. This allows
us to count how many times the same person viewed node by day, week, or month.


Features
---------

* Choose which node types
* Choose which display modes
* Choose which user roles
* Choose how the module should record the count
  Note: If you want to count anonymous vuews you must choose JavaScript.
* Views integration


Installation <!-- This section is required. -->
------------

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

- Visit the configuration page under Administration > Configuration > Content
  authoring > Node view count (admin/config/content/nodeviewcount) and enter the required information.


Issues <!-- This section is required. -->
------

Bugs and feature requests should be reported in [the Issue Queue](https://github.com/backdrop-contrib/foo-project/issues).


Differences from Drupal 7 <!-- Do not include if there are no differences. -->
-------------------------

- Built-in upgrade from 7.x-2.6 release (no need to update to 3.0-beta1 first).
- Labels descriptions on the settings form have been improved.
- Views Group has been changed from "Count views" to "Nodeview count".
- Entity API integration has been replaced by a single db_select().


Current Maintainers <!-- This section is required. -->
-------------------

- [Jen Lampton](https://github.com/jenlampton).
- Seeking additional maintainers.


Credits <!-- This section is required. -->
-------

- Ported to Backdrop CMS by [Jen Lampton](https://github.com/jenlampton).
- Maintained for Drupal by [adcillc](https://www.drupal.org/u/adcillc).
- Maintained for Drupal by [adci_contributor](https://www.drupal.org/u/adci_contributor).
- Inital development sponsored by [ADCI Solutions](https://www.drupal.org/adci-solutions)


License <!-- This section is required. -->
-------

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.
