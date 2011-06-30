<?php
// $Id: getdirections.admin.inc,v 1.3.2.2 2010/03/22 23:17:07 hutch Exp $
// $Name: DRUPAL-6--1-3 $

// optionally using version 3 googlemaps API

/**
 * @file
 * getdirections module administration functions.
 */

/**
 * Function to display the getdirections admin settings form
 * @return
 *   Returns the form.
 */
function getdirections_settings_form() {
  $getdirections_defaults = getdirections_defaults();
  $form = array();
  $form['use_v3'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Googlemaps version 3'),
    '#description' => t('Use version 3 of the Googlemaps API instead of version 2.'),
    '#default_value' => variable_get('use_v3', 0),
    '#return_value' => 1,
  );
  if (! variable_get('use_v3', 0)) {
    if ( module_exists('gmap')) {
      $gmap_key = gmap_get_key();
    }
    else {
      $gmap_key = '';
    }
    $form['getdirections_api_key'] = array(
      '#type' => 'textfield',
      '#title' => t('Your Google Maps API key'),
      '#disabled' => ($gmap_key ? TRUE : FALSE),
      '#default_value' => (variable_get('getdirections_api_key', '') ? variable_get('getdirections_api_key', '') : $gmap_key),
      '#description' => t('Required for version 2 of the Googlemaps API.'),
    );
  }

  $form['getdirections_default'] = array(
    '#type' => 'fieldset',
    '#title' => t('Get directions map settings'),
    // This will store all the defaults in one variable.
    '#tree' => TRUE,
  );
  if (! variable_get('use_v3', 0)) {
    $form['getdirections_default']['api_version'] = array(
      '#type' => 'textfield',
      '#title' => t('Your Google Maps API version'),
      '#size' => 15,
      '#description' => t("The Google Maps API version to use. Cen be a specific version number or '2' for Current, '2.x' for Latest or '2.s' for Stable."),
      '#default_value' => ($getdirections_defaults['api_version'] ? $getdirections_defaults['api_version'] : (defined('GMAP_API_VERSION') ? GMAP_API_VERSION : 2)),
    );
  }

  $form['getdirections_default']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Default width'),
    '#default_value' => $getdirections_defaults['width'],
    '#size' => 25,
    '#maxlength' => 25,
    '#description' => t('The default width of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>'),
  );
  $form['getdirections_default']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Default height'),
    '#default_value' => $getdirections_defaults['height'],
    '#size' => 25,
    '#maxlength' => 25,
    '#description' => t('The default height of a Google map, as a CSS length or percentage. Examples: <em>50px</em>, <em>5em</em>, <em>2.5in</em>, <em>95%</em>'),
  );
  $form['getdirections_default']['latlong'] = array(
    '#type' => 'textfield',
    '#title' => t('Map center'),
    '#default_value' => $getdirections_defaults['latlong'],
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('The default center coordinates of Google map, expressed as a decimal latitude and longitude, separated by a comma.'),
  );
  $form['getdirections_default']['zoom'] = array(
    '#type' => 'select',
    '#title' => t('Zoom'),
    '#default_value' => $getdirections_defaults['zoom'],
    '#options' => drupal_map_assoc(range(0, 17)),
    '#description' => t('The default zoom level of a Google map.'),
  );
  if (! variable_get('use_v3', 0)) {
    $version = $getdirections_defaults['api_version'];
    if ($version == '2' || $version == '2.x' || $version == '2.s') {
      $opts = array(
        'None' => t('None'),
        'Micro' => t('Micro'),
        'Micro3D' => t('Micro 3D'),
        'Small' => t('Small'),
        'Large' => t('Large'),
        'Large3D' => t('Large 3D'),
      );
    }
    else {
      $opts = array(
        'None' => t('None'),
        'Micro' => t('Micro'),
        'Small' => t('Small'),
        'Large' => t('Large'),
      );
    }
    $opts2 = array(
      'none' => t('None'),
      'standard' => t('Standard (GMapTypeControl)'),
      'hier' => t('Hierarchical (GHierarchicalMapTypeControl)'),
      'menu' => t('Dropdown (GMenuMapTypeControl)'),
    );
  }
  else {
    // v3
    $opts = array(
      'none' => t('None'),
      'default' => t('Default'),
      'android' => t('Android'),
      'small' => t('Small'),
      'large' => t('Large'),
    );
    $opts2 = array(
      'none' => t('None'),
      'standard' => t('Horizontal bar'),
      'menu' => t('Dropdown'),
    );
  }
  $form['getdirections_default']['controltype'] = array(
    '#type' => 'select',
    '#title' => t('Control type'),
    '#options' => $opts,
    '#default_value' => $getdirections_defaults['controltype'],
  );

  $form['getdirections_default']['mtc'] = array(
    '#type' => 'select',
    '#title' => t('Map Type Control selection'),
    '#options' => $opts2,
    '#default_value' => $getdirections_defaults['mtc'],
  );
  if (! variable_get('use_v3', 0)) {
    if (module_exists('gmap')) {
      // layers
      $baselayers = array();
      foreach (module_implements('gmap') as $module) {
        call_user_func_array($module .'_gmap', array('baselayers', &$baselayers));
      }
      $options = array();
      foreach ($baselayers as $name => $layers) {
        $options[$name] = array();
        foreach ($layers as $key => $layer) {
          // @@@TODO: Only show the enabled ones? an attempt
          if ( $getdirections_defaults['baselayers'][$key] ) {
            $options[$name][$key] = $layer['title'];
          }
        }
      }
      $form['getdirections_default']['maptype'] = array(
        '#type' => 'select',
        '#title' => t('Default map type'),
        '#default_value' => $getdirections_defaults['maptype'],
        '#options' => $options,
      );
      foreach ($baselayers as $name => $layers) {
        foreach ($layers as $key => $layer) {
          $form['getdirections_default']['baselayers'][$key] = array(
            '#type' => 'checkbox',
            '#title' => $layer['title'],
            '#description' => $layer['help'],
            '#default_value' => $getdirections_defaults['baselayers'][$key],
            '#return_value' => 1,
          );
        }
      }
    }
  }
  else {
    $form['getdirections_default']['maptype'] = array(
      '#type' => 'select',
      '#title' => t('Default map type'),
      '#default_value' => $getdirections_defaults['maptype'],
      '#options' => array(
        'Map' => t('Standard street map'),
        'Satellite' => t('Standard satellite map'),
        'Hybrid' => t('Hybrid satellite map'),
        'Physical' => t('Terrain map'),
      ),
    );
    $form['getdirections_default']['baselayers']['Map'] = array(
      '#type' => 'checkbox',
      '#title' => t('Standard street map'),
      '#description' => t('The standard default street map.'),
      '#default_value' => $getdirections_defaults['baselayers']['Map'],
      '#return_value' => 1,
      '#prefix' => '<fieldset><legend>' . t('Enable map types') . '</legend>',
    );
    $form['getdirections_default']['baselayers']['Satellite'] = array(
      '#type' => 'checkbox',
      '#title' => t('Standard satellite map'),
      '#description' => t('Satellite view without street overlay.'),
      '#default_value' => $getdirections_defaults['baselayers']['Satellite'],
      '#return_value' => 1,
    );
    $form['getdirections_default']['baselayers']['Hybrid'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hybrid satellite map'),
      '#description' => t('Satellite view with street overlay.'),
      '#default_value' => $getdirections_defaults['baselayers']['Hybrid'],
      '#return_value' => 1,
    );
    $form['getdirections_default']['baselayers']['Physical'] = array(
      '#type' => 'checkbox',
      '#title' => t('Terrain map'),
      '#description' => t('Map with physical data (terrain, vegetation.)'),
      '#default_value' => $getdirections_defaults['baselayers']['Physical'],
      '#return_value' => 1,
      '#suffix' => '</fieldset>',
    );
    $form['getdirections_default']['unitsystem'] = array(
      '#type' => 'select',
      '#title' => t('Default distance units'),
      '#description' => t("Units to display distances in. 'Automatic' uses the country of origin."),
      '#default_value' => $getdirections_defaults['unitsystem'],
      '#options' => array(
        'auto' => t('Automatic'),
        'metric' => t('Metric'),
        'imperial' => t('Imperial'),
      ),
    );
  }

  $form['getdirections_default']['behavior']['scale'] = array(
    '#type' => 'checkbox',
    '#title' => t('Scale'),
    '#description' => t('Show scale'),
    '#default_value' =>  $getdirections_defaults['behavior']['scale'],
    '#return_value' => 1,
  );

  if (! variable_get('use_v3', 0)) {
    $form['getdirections_default']['behavior']['overview'] = array(
      '#type' => 'checkbox',
      '#title' => t('Overview map'),
      '#description' => t('Show overview map'),
      '#default_value' =>  $getdirections_defaults['behavior']['overview'],
      '#return_value' => 1,
    );
  }
  else {
    $form['getdirections_default']['behavior']['scrollwheel'] = array(
      '#type' => 'checkbox',
      '#title' => t('Scrollwheel'),
      '#description' => t('Enable scrollwheel zooming'),
      '#default_value' =>  $getdirections_defaults['behavior']['scrollwheel'],
      '#return_value' => 1,
    );

    $form['getdirections_default']['behavior']['draggable'] = array(
      '#type' => 'checkbox',
      '#title' => t('Draggable'),
      '#description' => t('Enable dragging on the map'),
      '#default_value' =>  $getdirections_defaults['behavior']['draggable'],
      '#return_value' => 1,
    );

    $form['getdirections_default']['travelmode_show'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show travel mode'),
      '#description' => t('Enable travel mode selector.'),
      '#default_value' =>  $getdirections_defaults['travelmode_show'],
      '#return_value' => 1,
    );
    $form['getdirections_default']['travelextras_show'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show travel extras'),
      '#description' => t('Enable travel extras checkboxes.'),
      '#default_value' =>  $getdirections_defaults['travelextras_show'],
      '#return_value' => 1,
    );
  }

  $form['getdirections_default']['from_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width of From box'),
    '#default_value' => $getdirections_defaults['from_width'],
    '#size' => 5,
    '#description' => t("The width of the Get directions 'From' box."),
  );
  $form['getdirections_default']['to_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Width of To box'),
    '#default_value' => $getdirections_defaults['to_width'],
    '#size' => 5,
    '#description' => t("The width of the Get directions 'To' box."),
  );

  return system_settings_form($form);

}
