# Application Layer

As Application Layer we denote a middleware layer based on Node-RED that connects the platform generated events (or other types of services) with some concrete application logic.

In the specific example, we have events generated for the traffic state of the city of Madrid in various measurement points (PMs) that indicate the state of the traffic (good/bad). Thus an application layer may receive as input a user location in GPS lat lon coordinates and check the distance between the user and the respective measurement point. If this distance is smaller than a given radius,
an alarm is triggered that can be directed to whatever kind of output (e.g. mobilde device again).



