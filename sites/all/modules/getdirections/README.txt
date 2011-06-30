getdirections module for Drupal 6.x

If you have any questions or suggestions please contact me at
http://drupal.org/user/52366

This module provides a form to make a google directions map.

Installation
Upload the whole getdirections directory into sites/all/modules/ or
sites/<domain>/modules/ for multisite setups.

Login to Drupal site as a user with administrative rights and go to
Administer > Site building > Modules. Scroll down to Other modules section, you
should now see Getdirections module listed there. Tick it and save configuration.

After installation go to Administer > Site configuration > Get directions and
select your preferences and Save Configuration.

If you have the gmap module installed and configured, getdirections will
use its configuration as a starting point.

Also remember to go to Administer > User management > Permissions and
set up permissions according to your needs.

If you have the location module installed you can make use of any nodes
containing location information.

For instance, if you want to "preload" the getdirections form with information
about the destination use a URL in this format:

getdirections/location/to/99

Where '99' is the vid of the location.
The user will only have to fill in the starting point.

To do it the other way around use
getdirections/location/from/99

You can also get a map with waypoints
getdirections/locations_via/1,2,3,99

If you have both the starting point and destination vids then you can use
getdirections/locations/1/99

Where '1' is the starting point vid and 99 is the destination vid
(note the 's' in locations)

If you are using the location_user module you can make a link to a user's location:
getdirections/location_user/to/66

Same goes for from

You can also get a map with waypoints of user locations
getdirections/locations_user_via/1,2,3,99

You can mix nodes and users with
getdirections/location_u2n/66/99
Where 66 is is user id, 99 is node id

and vice-versa
getdirections/location_n2u/99/66
Where 66 is is user id, 99 is node id


------------------
Get Directions API
There are functions available to generate these paths:

getdirections_location_path($direction, $vid)
Where $direction is either 'to' or 'from' and $vid is the vid concerned.

getdirections_locations_path($fromvid, $tovid)
Where $fromvid is the starting point and $tovid is the destination

getdirections_locations_via_path($vids)
Where $vids is a comma delimited list, eg "1,2,3,99"
Google imposes a limit of 25 points

If you have the latitude and longitude of the start and end points you can use

getdirections_locations_bylatlon($fromlocs, $fromlatlon, $tolocs, $tolatlon)
Where $fromlocs is a description of the starting point,
$fromlatlon is the latitude,longitude of the starting point
and $tolocs and $tolatlon are the same thing for the endpoint

See getdirections.api.inc for more detail.

If you are using Views and Location it will provide a 'Get driving directions' block 
when you are viewing a location node or a user with a location.

Getdirections now supports the Googlemaps API version 3, this has many new features.
