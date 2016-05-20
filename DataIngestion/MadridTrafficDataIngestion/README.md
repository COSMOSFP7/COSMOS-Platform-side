The flow may be used in order to acquire public data from Madrid City council Open Data portal.

Needs import of the Dateformat node.js function (in settings.js)

Beware that in some of the nodes (e.g. file nodes) specific path dependencies may exist that point to the file. Change them according to your folder structure.

You may also need to include the following line
process.env.NODE_TLS_REJECT_UNAUTHORIZED = "0";
in your settings.js file in order to be able to acquire data from https locations with self signed certificates.
