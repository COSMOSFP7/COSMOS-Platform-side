The flow may be used in order to register to Twitter and start receiving tweets based on filters of geolocation. The tweets are processed in order to keep only a part of the information and annotate them with sentiment analysis from the built-in nodered node.
Needs configuration on one node (Twitlib), needs Twitter OAth credentials:
https://dev.twitter.com/oauth/overview/application-owner-access-tokens

You also need to import tne node.js lib https://github.com/ttezel/twit and follow a process for including
it in Node-RED mentioned in nodered.org (http://nodered.org/docs/writing-functions)

Potential issues may arise due to server desynchronization issues with timezones, typical of running inside VMs. For this purpose you can periodically update (e.g. with a cronjob) through a suitable command:
ntpdate -u 2.pool.ntp.org

Lack of synchronization with a timezone will result in authentication errors and timestamp issues when trying to access the Twitter API.
