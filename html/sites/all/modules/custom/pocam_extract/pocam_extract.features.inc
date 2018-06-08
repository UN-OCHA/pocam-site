<?php
/**
 * @file
 * pocam_extract.features.inc
 */

/**
 * Implements hook_node_info().
 */
function pocam_extract_node_info() {
  $items = array(
    'pocam_extract' => array(
      'name' => t('Extract'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
