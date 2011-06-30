<?php
// $Id: getdirections.api.inc,v 1.1.2.4 2010/03/24 22:27:30 hutch Exp $
// $Name: DRUPAL-6--1-3 $

/**
 * @file
 * Get directions API
 */

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_location_path('to', $vid);
 * $url = l(t('Get directions'), $path);
 *
 * @param $direction
 *   Required. The direction the supplied input applies to. Must be either 'to' or 'from'
 * @param $vid
 *   Required. The vid of the location node
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_location_path($direction, $vid) {
  if (module_exists('location') && is_numeric($vid) && ($direction == 'to' || $direction == 'from')) {
    return "getdirections/location/$direction/$vid";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_location_user_path('to', $vid);
 * $url = l(t('Get directions'), $path);
 *
 * @param $direction
 *   Required. The direction the supplied input applies to. Must be either 'to' or 'from'
 * @param $uid
 *   Required. The uid of the location owner
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_location_user_path($direction, $uid) {
  if (module_exists('location') && is_numeric($uid) && ($direction == 'to' || $direction == 'from')) {
    return "getdirections/location_user/$direction/$uid";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_locations_path($fromvid, $tovid);
 * $url = l(t('Get directions'), $path);
 *
 *
 *
 * @param $fromvid
 *   Required. The vid  of the location node of the starting point
 * @param $tovid
 *   Required. The vid of the location node of the destination
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_locations_path($fromvid, $tovid) {
  if (module_exists('location') && is_numeric($fromvid) && is_numeric($tovid)) {
    return "getdirections/locations/$fromvid/$tovid";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_locations_user_path($fromuid, $touid);
 * $url = l(t('Get directions'), $path);
 *
 *
 *
 * @param $fromuid
 *   Required. The uid  of the location user of the starting point
 * @param $touid
 *   Required. The uid of the location user of the destination
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_locations_user_path($fromuid, $touid) {
  if (module_exists('location') && is_numeric($fromuid) && is_numeric($touid)) {
    return "getdirections/locations_user/$fromuid/$touid";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $uids = "1,2,3,4";
 * where '1' is the uid of the starting point
 * '4' is the uid of the end point
 * and the numbers in between are the uids of the waypoints
 * $path = getdirections_locations_user_via_path($uids);
 * $url = l(t('Get directions'), $path);
 *
 * @param $uids
 *   Required. String. A comma delimited list of uid numbers
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_locations_user_via_path($uids) {
  if (module_exists('location')) {
    return "getdirections/locations_user_via/$uids";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $vids = "1,2,3,4";
 * where '1' is the vid of the starting point
 * '4' is the vid of the end point
 * and the numbers in between are the vids of the waypoints
 * $path = getdirections_locations_via_path($vids);
 * $url = l(t('Get directions'), $path);
 *
 * @param $vids
 *   Required. String. A comma delimited list of uid numbers
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_locations_via_path($vids) {
  if (module_exists('location')) {
    return "getdirections/locations_via/$vids";
  }
}


/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_location_u2n_path($fromuid, $tovid);
 * $url = l(t('Get directions'), $path);
 *
 *
 *
 * @param $fromuid
 *   Required. The uid  of the location user of the starting point
 * @param $tovid
 *   Required. The vid of the location node of the destination
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_location_u2n_path($fromuid, $tovid) {
  if (module_exists('location') && is_numeric($fromuid) && is_numeric($tovid)) {
    return "getdirections/location_u2n/$fromuid/$tovid";
  }
}

/**
 * API Function to generate a url path for use by other modules/themes.
 *
 * Example Usage:
 * $path = getdirections_location_n2u_path($fromvid, $touid);
 * $url = l(t('Get directions'), $path);
 *
 *
 *
 * @param $fromvid
 *   Required. The vid  of the location node of the starting point
 * @param $touid
 *   Required. The uid of the location user of the destination
 * @return
 *   Returns a path relative to the drupal root.
 */
function getdirections_location_n2u_path($fromvid, $touid) {
  if (module_exists('location') && is_numeric($fromvid) && is_numeric($touid)) {
    return "getdirections/location_u2n/$fromvid/$touid";
  }
}

/**
 * API Function to setup a map with two points
 *
 * @param $fromlocs
 *   Required. The string to display for From.
 * @param $fromlatlon
 *   Required. The location point for From. In decimal latitude,longitude
 * @param $tolocs
 *   Required. The string to display for To.
 * @param $tolatlon
 *   Required. The location point for To. In decimal latitude,longitude
 * @return
 *   Returns the themed map.
 */
function getdirections_locations_bylatlon($fromlocs, $fromlatlon, $tolocs, $tolatlon) {
  return getdirections_locations($fromlocs, $fromlatlon, $tolocs, $tolatlon);
}
