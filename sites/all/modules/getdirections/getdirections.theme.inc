<?php
// $Id: getdirections.theme.inc,v 1.2.2.3 2010/03/22 23:17:07 hutch Exp $
// $Name: DRUPAL-6--1-3 $

/**
 * @file
 * getdirections module theming
 */


/**
 * Implementation of hook_theme().
 *
 * This lets us tell Drupal about our theme functions and their arguments.
 */
function getdirections_theme() {
  return array(
    'getdirections_show' => array(
      'arguments' => array(
        'form' => array(),
        'width' => '',
        'height' => '',
      ),
    ),
    'getdirections_show_locations' => array(
      'arguments' => array(
        'width' => '',
        'height' => '',
        'fromlocs' => '',
        'tolocs' => '',
      ),
    ),
    'getdirections_show_locations_via' => array(
      'arguments' => array(
        'width' => '',
        'height' => '',
        'locs' => NULL,
      ),
    ),
    'getdirections_direction_form' => array(
      'arguments' => array('form' => NULL),
    ),
  );
}

/**
 * Theme to use for when one or no locations are supplied.
 *
 */
function theme_getdirections_show($form, $width, $height) {
  $output = $form;
  $header = array();

  $rows[] = array(
    array(
      'data' => '<div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );
  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  return $output;
}

/**
 * Theme to use for when both locations are supplied.
 *
 */
function theme_getdirections_show_locations($width, $height, $fromlocs, $tolocs) {
  $output = "";
  $output .= "<div class='getdirections_display'><label>". t('From') .":</label> ". $fromlocs ."</div>";
  $output .= "<div class='getdirections_display'><label>". t('To') .":</label> ". $tolocs ."</div>";

  $header = array();

  $rows[] = array(
    array(
      'data' => '<div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );
  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  return $output;
}

/**
 * Theme to use for when both locations are supplied with waypoints.
 *
 */
function theme_getdirections_show_locations_via($width, $height, $locs) {
  $output = "";
  foreach ($locs AS $key => $loc) {
    if ($key == 0) {
      $label = t('From');
    }
    elseif ($key == count($locs)-1) {
      $label = t('To');
    }
    else {
      $label = t('Via');
    }
    $output .= "<div class='getdirections_display'><label>". $label .":</label> ". $loc ."</div>";
  }

  $header = array();

  $rows[] = array(
    array(
      'data' => '<div id="getdirections_map_canvas" style="width: '. $width .'; height: '. $height .'" ></div>',
      'valign' => 'top',
      'align' => 'center',
      'class' => 'getdirections-map',
    ),
    array(
      'data' => '<div id="getdirections_directions"></div>',
      'valign' => 'top' ,
      'align' => 'left',
      'class' => 'getdirections-list',
    ),
  );
  $output .= '<div class="getdirections">'. theme('table', $header, $rows) .'</div>';
  return $output;
}


function theme_getdirections_direction_form($form) {
  // if you want to do fancy things with the form, do it here ;-)
  $output = '';
  $output .= drupal_render($form);
  return $output;
}
