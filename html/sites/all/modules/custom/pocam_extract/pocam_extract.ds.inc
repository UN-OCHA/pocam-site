<?php
/**
 * @file
 * pocam_extract.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function pocam_extract_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|pocam_extract|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'pocam_extract';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_text',
      ),
      'right' => array(
        1 => 'field_year',
        2 => 'field_document_type',
        3 => 'theme_full_tree',
        4 => 'field_link',
        5 => 'theme_see_also',
      ),
    ),
    'fields' => array(
      'field_text' => 'left',
      'field_year' => 'right',
      'field_document_type' => 'right',
      'theme_full_tree' => 'right',
      'field_link' => 'right',
      'theme_see_also' => 'right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'left' => 'section',
      'right' => 'aside',
    ),
    'layout_wrapper' => 'article',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
    'hide_page_title' => '1',
    'page_option_title' => '',
  );
  $export['node|pocam_extract|full'] = $ds_layout;

  return $export;
}
