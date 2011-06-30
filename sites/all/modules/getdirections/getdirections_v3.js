// $Id: getdirections_v3.js,v 1.1.2.1 2010/03/22 23:17:07 hutch Exp $
// $Name: DRUPAL-6--1-3 $

/**
 * @file
 * Javascript functions for getdirections module
 *
 * @author Bob Hutchinson http://drupal.org/user/52366
 * code derived from gmap_direx module
 * this is for googlemaps API version 3
*/

var dirservice;
var dirrenderer;
var unitsys;
var trmode;

function initialize() {
  var lat = parseFloat(Drupal.settings.getdirections.lat);
  var lng = parseFloat(Drupal.settings.getdirections.lng);
  var selzoom = parseInt(Drupal.settings.getdirections.zoom);
  var controltype = Drupal.settings.getdirections.controltype;
  var scale = Drupal.settings.getdirections.scale;
  var scrollw = Drupal.settings.getdirections.scrollwheel;
  var drag = Drupal.settings.getdirections.draggable;
  unitsys = Drupal.settings.getdirections.unitsystem;
  var maptype = (Drupal.settings.getdirections.maptype ? Drupal.settings.getdirections.maptype : '');
  var baselayers = (Drupal.settings.getdirections.baselayers ? Drupal.settings.getdirections.baselayers : '');

  var fromlatlon = (Drupal.settings.getdirections.fromlatlon ? Drupal.settings.getdirections.fromlatlon : '');
  var tolatlon = (Drupal.settings.getdirections.tolatlon ? Drupal.settings.getdirections.tolatlon : '');
  var mylocale = (Drupal.settings.getdirections.mylocale ? Drupal.settings.getdirections.mylocale : 'en');
  // pipe delim
  var latlons = (Drupal.settings.getdirections.latlons ? Drupal.settings.getdirections.latlons : '');

  // menu type
  var mtc = Drupal.settings.getdirections.mtc;
  if (mtc == 'standard') {
    mtc = google.maps.MapTypeControlStyle.HORIZONTAL_BAR;
  }
  else if (mtc == 'menu' ) {
    mtc = google.maps.MapTypeControlStyle.DROPDOWN_MENU;
  }
  else {
    mtc = false;
  }

  // nav control type
  if (controltype == 'android') {
    controltype = google.maps.NavigationControlStyle.ANDROID;
  }
  else if (controltype == 'small') {
    controltype = google.maps.NavigationControlStyle.SMALL;
  }
  else if (controltype == 'large') {
    controltype = google.maps.NavigationControlStyle.ZOOM_PAN;
  }
  else if (controltype == 'default') {
    controltype = google.maps.NavigationControlStyle.DEFAULT;
  }
  else {
    controltype = false;
  }

  // map type
  if (maptype) {
    if (maptype == 'Map' && baselayers['Map']) {
      maptype = google.maps.MapTypeId.ROADMAP;
    }
    if (maptype == 'Satellite' && baselayers['Satellite'] ) {
      maptype = google.maps.MapTypeId.SATELLITE;
    }
    if (maptype == 'Hybrid' && baselayers['Hybrid'] ) {
      maptype = google.maps.MapTypeId.HYBRID;
    }
    if (maptype == 'Physical' && baselayers['Physical'] ) {
      maptype = google.maps.MapTypeId.TERRAIN;
    }
  }
  else {
    maptype = google.maps.MapTypeId.ROADMAP;
  }

  var mapOpts = {
    zoom: selzoom,
    center: new google.maps.LatLng(lat, lng),
    mapTypeControl: (mtc ? true : false),
    mapTypeControlOptions: {style: mtc},
    navigationControl: (controltype ? true : false),
    navigationControlOptions: {style: controltype},
    mapTypeId: maptype,
    scrollwheel: (scrollw ? true : false),
    draggable: (drag ? true : false),
    scaleControl: (scale ? true : false),
    scaleControlOptions: {style: google.maps.ScaleControlStyle.DEFAULT}
  }
  map = new google.maps.Map(document.getElementById("getdirections_map_canvas"), mapOpts);

  dirrenderer = new google.maps.DirectionsRenderer();
  dirrenderer.setMap(map);
  dirrenderer.setPanel(document.getElementById("getdirections_directions"));
  dirservice = new google.maps.DirectionsService();
  trmode = google.maps.DirectionsTravelMode.DRIVING;

  if (fromlatlon && tolatlon) {
    request = setDirectionsfromto(fromlatlon, tolatlon);
    renderdirections(request);
  }
  if (latlons) {
    setDirectionsvia(latlons);
  }
}

function renderdirections(request) {
  dirservice.route(request, function(response, status) {
    if (status == google.maps.DirectionsStatus.OK) {
      dirrenderer.setDirections(response);
    } else {
      var err = getdirectionserrcode(status);
      alert('Error: ' + err);
    }
  });
}

function getRequest(fromAddress, toAddress, waypts) {
  var request = new Object();
  request = {
    origin: fromAddress,
    destination: toAddress,
  };

  var tmode = $("#edit-travelmode").val();
  if (tmode == 'walking') {
    trmode = google.maps.DirectionsTravelMode.WALKING;
  }
  else if (tmode == 'bicycling') {
   trmode = google.maps.DirectionsTravelMode.BICYCLING;
  }
  else {
   trmode = google.maps.DirectionsTravelMode.DRIVING;
  }
  request.travelMode = trmode;

  if (unitsys == 'metric') {
    request.unitSystem = google.maps.DirectionsUnitSystem.METRIC;
  }
  else if (unitsys == 'imperial') {
    request.unitSystem = google.maps.DirectionsUnitSystem.IMPERIAL;
  }

  var avoidh = false;
  if ($("#edit-travelextras-avoidhighways").attr('checked')) {
    avoidh = true;
  }
  request.avoidHighways = avoidh;

  var avoidt = false;
  if ($("#edit-travelextras-avoidtolls").attr('checked')) {
    avoidt = true;
  }
  request.avoidTolls = avoidt;

  var routealt = false;
  if ($("#edit-travelextras-altroute").attr('checked')) {
    routealt = true;
  }
  request.provideRouteAlternatives = routealt;

  if (waypts) {
    request.waypoints = waypts;
    request.optimizeWaypoints = true;
  }

  return request;
}

// both addresses supplied. as lat,lon
function setDirectionsfromto(fromAddress, toAddress, mylocale) {
  flatarr = fromAddress.split(","); flat = parseFloat(flatarr[0]); flon = parseFloat(flatarr[1]);
  from = new google.maps.LatLng(flat, flon);
  tlatarr = toAddress.split(","); tlat = parseFloat(tlatarr[0]); tlon = parseFloat(tlatarr[1]);
  to = new google.maps.LatLng(tlat, tlon);
  var request = getRequest(from, to, '');
  renderdirections(request);
}

// both addresses supplied. as strings
function setDirectionsfromto2(fromAddress, fromCountry, toAddress, toCountry, mylocale) {
  from = fromAddress + ", " + fromCountry;
  to = toAddress + ", " + toCountry;
  var request = getRequest(from, to, '');
  renderdirections(request);
}

// from is lat,lon  to is address
function setDirectionsfrom(fromAddress, toAddress, toCountry, mylocale) {
  flatarr = fromAddress.split(","); flat = parseFloat(flatarr[0]); flon = parseFloat(flatarr[1]);
  from = new google.maps.LatLng(flat, flon);
  to = toAddress + ", " + toCountry;
  var request = getRequest(from, to, '');
  renderdirections(request);
}

// to is lat,lon  from is address
function setDirectionsto(fromCountry, fromAddress, toAddress, mylocale) {
  from = fromAddress + ", " + fromCountry;
  tlatarr = toAddress.split(","); tlat = parseFloat(tlatarr[0]); tlon = parseFloat(tlatarr[1]);
  to = new google.maps.LatLng(tlat, tlon);
  var request = getRequest(from, to, '');
  renderdirections(request);
}

// with waypoints
function setDirectionsvia(lls, mylocale) {
  var arr = lls.split('|');
  var len = arr.length;
  var wp = 0;
  var fromAddress = '';
  var toAddress = '';
  var viaAddress = '';
  var waypts = new Array();
  for (var i = 0; i < len; i++) {
    if (i == 0) {
      fromAddress = arr[i];
      flatarr = fromAddress.split(","); flat = parseFloat(flatarr[0]); flon = parseFloat(flatarr[1]);
      var from = new google.maps.LatLng(flat, flon);
    }
    else if (i == len-1) {
      toAddress = arr[i];
      tlatarr = toAddress.split(","); tlat = parseFloat(tlatarr[0]); tlon = parseFloat(tlatarr[1]);
      var to = new google.maps.LatLng(tlat, tlon);
    }
    else {
      wp++;
      if (wp < 24) {
        viaAddress = arr[i];
        vlatarr = viaAddress.split(","); vlat = parseFloat(vlatarr[0]); vlon = parseFloat(vlatarr[1]);
        via = new google.maps.LatLng(vlat, vlon);
        waypts.push({
          location: via,
          stopover: true
        });
      }
    }
  }
  var request = getRequest(from, to, waypts);
  renderdirections(request);

}

// error codes
function getdirectionserrcode(errcode) {
  if (errcode == google.maps.DirectionsStatus.INVALID_REQUEST) {
    errstr = "The DirectionsRequest provided was invalid.";
  }
  else if (errcode == google.maps.DirectionsStatus.MAX_WAYPOINTS_EXCEEDED) {
    errstr = "Too many DirectionsWaypoints were provided in the DirectionsRequest. The total allowed waypoints is 23, plus the origin, and destination.";
  }
  else if (errcode == google.maps.DirectionsStatus.NOT_FOUND) {
    errstr = "At least one of the origin, destination, or waypoints could not be geocoded.";
  }
  else if (errcode == google.maps.DirectionsStatus.OVER_QUERY_LIMIT) {
    errstr = "The webpage has gone over the requests limit in too short a period of time.";
  }
  else if (errcode == google.maps.DirectionsStatus.REQUEST_DENIED) {
    errstr = "The webpage is not allowed to use the directions service.";
  }
  else if (errcode == google.maps.DirectionsStatus.UNKNOWN_ERROR) {
    errstr = "A directions request could not be processed due to a server error. The request may succeed if you try again.";
  }
  else if (errcode == google.maps.DirectionsStatus.ZERO_RESULTS) {
    errstr = "No route could be found between the origin and destination.";
  }
  return errstr;
}

// gogogo
$(document).ready( function() {
  initialize();
});
