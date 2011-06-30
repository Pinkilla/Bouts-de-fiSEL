// $Id: getdirections_v2.js,v 1.1.2.1 2010/03/22 23:17:07 hutch Exp $
// $Name: DRUPAL-6--1-3 $

/**
 * @file
 * Javascript functions for getdirections module
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * code derived from gmap_direx module
 * this is for googlemaps API version 2
*/

// Global killswitch
if (Drupal.jsEnabled) {

  var map;
  var gdir;

  function initialize() {
    if (GBrowserIsCompatible()) {
      Drupal.settings.getdirections.map = new GMap2(document.getElementById("getdirections_map_canvas"));
      var lat = Drupal.settings.getdirections.lat;
      var lng = Drupal.settings.getdirections.lng;
      var zoom = Drupal.settings.getdirections.zoom;
      var controltype = Drupal.settings.getdirections.controltype;
      var mtc = Drupal.settings.getdirections.mtc;
      var scale = Drupal.settings.getdirections.scale;
      var overview = Drupal.settings.getdirections.overview;
      var maptype = (Drupal.settings.getdirections.maptype ? Drupal.settings.getdirections.maptype : '');
      var baselayers = (Drupal.settings.getdirections.baselayers ? Drupal.settings.getdirections.baselayers : '');

      var fromlatlon = (Drupal.settings.getdirections.fromlatlon ? Drupal.settings.getdirections.fromlatlon : '');
      var tolatlon = (Drupal.settings.getdirections.tolatlon ? Drupal.settings.getdirections.tolatlon : '');
      var mylocale = (Drupal.settings.getdirections.mylocale ? Drupal.settings.getdirections.mylocale : 'en');
      // pipe delim
      var latlons = (Drupal.settings.getdirections.latlons ? Drupal.settings.getdirections.latlons : '');

      // menu type
      if (mtc == 'standard') {
        Drupal.settings.getdirections.map.addControl(new GMapTypeControl());
      }
      else if (mtc == 'hier') {
        Drupal.settings.getdirections.map.addControl(new GHierarchicalMapTypeControl());
      }
      else if (mtc == 'menu') {
        Drupal.settings.getdirections.map.addControl(new GMenuMapTypeControl());
      }

      // nav control type
      if (controltype == 'Micro') {
        Drupal.settings.getdirections.map.addControl(new GSmallZoomControl());
      }
      else if (controltype == 'Micro3D') {
        Drupal.settings.getdirections.map.addControl(new GSmallZoomControl3D());
      }
      else if (controltype == 'Small') {
        Drupal.settings.getdirections.map.addControl(new GSmallMapControl());
      }
      else if (controltype == 'Large') {
        Drupal.settings.getdirections.map.addControl(new GLargeMapControl());
      }
      else if (controltype == 'Large3D') {
        Drupal.settings.getdirections.map.addControl(new GLargeMapControl3D());
      }

      if (baselayers['Physical']) {
        Drupal.settings.getdirections.map.addMapType(G_PHYSICAL_MAP);
      }

      // map type
      if (maptype) {
        if (maptype == 'Map' && baselayers['Map']) {
          Drupal.settings.getdirections.map.setMapType(G_NORMAL_MAP);
        }
        if (maptype == 'Satellite' && baselayers['Satellite'] ) {
          Drupal.settings.getdirections.map.setMapType(G_SATELLITE_MAP);

        }
        if (maptype == 'Hybrid' && baselayers['Hybrid'] ) {
          Drupal.settings.getdirections.map.setMapType(G_HYBRID_MAP);

        }
        if (maptype == 'Physical' && baselayers['Physical'] ) {
          Drupal.settings.getdirections.map.setMapType(G_PHYSICAL_MAP);
        }
      }

      //GScaleControl()
      if (scale) {
        Drupal.settings.getdirections.map.addControl(new GScaleControl());
      }
      //GOverviewMapControl()
      if (overview) {
        Drupal.settings.getdirections.map.addControl(new GOverviewMapControl());
      }

      latlng = new GLatLng(lat, lng);
      Drupal.settings.getdirections.map.setCenter(latlng, parseInt(zoom));

      gdir = new GDirections(Drupal.settings.getdirections.map, document.getElementById("getdirections_directions"));
      GEvent.addListener(gdir, "load", onGDirectionsLoad);
      GEvent.addListener(gdir, "error", handleErrors);

      if (fromlatlon && tolatlon) {
        setDirectionsfromto(fromlatlon, tolatlon, mylocale);
      }
      if (latlons) {
        setDirectionsvia(latlons, mylocale);
      }
    }
  }

  // without location module
  function setDirectionsfromto(fromAddress, toAddress, locale) {
    gdir.load("from: " + fromAddress + " to: " + toAddress, { "locale": locale });
  }

  // with location module
  function setDirectionsfromto2(fromCountry, fromAddress, toCountry, toAddress, locale) {
    var s = "from: " + fromAddress + ", " + fromCountry + " to: " + toAddress + ", " + toCountry;
    gdir.load(s, { "locale": locale });
  }
  function setDirectionsfrom(fromAddress, toCountry, toAddress, locale) {
    var s = "from: " + fromAddress + " to: " + toAddress + ", " + toCountry;
    gdir.load(s, { "locale": locale });
  }
  function setDirectionsto(fromCountry, fromAddress, toAddress, locale) {
    var s = "from: " + fromAddress + ", " + fromCountry + " to: " + toAddress;
    gdir.load(s, { "locale": locale });
  }
  function setDirectionsvia(lls, locale) {
    arr = new Array();
    arr = lls.split('|');
    gdir.loadFromWaypoints(arr, { "locale": locale });
  }

  function handleErrors(){
    if (gdir.getStatus().code == G_GEO_UNKNOWN_ADDRESS)
      alert("No corresponding geographic location could be found for one of the specified addresses. This may be due to the fact that the address is relatively new, or it may be incorrect.\nError code: " + gdir.getStatus().code);

    else if (gdir.getStatus().code == G_GEO_SERVER_ERROR)
      alert("A geocoding or directions request could not be successfully processed, yet the exact reason for the failure is not known.\n Error code: " + gdir.getStatus().code);

    else if (gdir.getStatus().code == G_GEO_MISSING_QUERY)
      alert("The HTTP q parameter was either missing or had no value. For geocoder requests, this means that an empty address was specified as input. For directions requests, this means that no query was specified in the input.\n Error code: " + gdir.getStatus().code);

//   else if (gdir.getStatus().code == G_UNAVAILABLE_ADDRESS)  <--- Doc bug... this is either not defined, or Doc is wrong
//     alert("The geocode for the given address or the route for the given directions query cannot be returned due to legal or contractual reasons.\n Error code: " + gdir.getStatus().code);

    else if (gdir.getStatus().code == G_GEO_BAD_KEY)
      alert("The given key is either invalid or does not match the domain for which it was given. \n Error code: " + gdir.getStatus().code);

    else if (gdir.getStatus().code == G_GEO_BAD_REQUEST)
      alert("A directions request could not be successfully parsed.\n Error code: " + gdir.getStatus().code);

    else alert("An unknown error occurred.");

  }

  function onGDirectionsLoad(){
    // Use this function to access information about the latest load() results.
    // e.g.
    //document.getElementById("getdirections_info").innerHTML = gdir.getStatus().code;
    // and yada yada yada...
  }

  $(document).ready( function() {
    initialize();
  });
  $(window).unload(function(){
    GUnload();
  });
}
