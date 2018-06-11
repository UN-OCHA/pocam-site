<?php
/**
 * @file
 * pocam_general.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function pocam_general_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['facetapi-0Pusq0zftXdOJDSRLOSFYp7IB6GKKuh1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '0Pusq0zftXdOJDSRLOSFYp7IB6GKKuh1',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Document type',
    'visibility' => 0,
  );

  $export['facetapi-h4J767t1sdzXEtEOAD03WQ9E8BvwROxn'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'h4J767t1sdzXEtEOAD03WQ9E8BvwROxn',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bartik',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Theme',
    'visibility' => 0,
  );

  return $export;
}
