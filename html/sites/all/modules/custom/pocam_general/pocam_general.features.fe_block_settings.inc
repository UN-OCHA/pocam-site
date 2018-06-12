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

  return $export;
}
