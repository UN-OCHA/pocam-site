<?php
/**
 * @file
 * pocam_general.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function pocam_general_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'extract_search';
  $context->description = 'Extract search';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'extracts:page' => 'extracts:page',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'facetapi-jMt8phZnpIgZZNTtJ71tATNsoZgFxqKb' => array(
          'module' => 'facetapi',
          'delta' => 'jMt8phZnpIgZZNTtJ71tATNsoZgFxqKb',
          'region' => 'content_top',
          'weight' => '-10',
        ),
        'facetapi-h3E804ufRqmwuxTFodspV21rBJb00L2X' => array(
          'module' => 'facetapi',
          'delta' => 'h3E804ufRqmwuxTFodspV21rBJb00L2X',
          'region' => 'content_top',
          'weight' => '-9',
        ),
        'facetapi-7TqCFBUvppfBoYrlTYxf0VxXrnz4llZ7' => array(
          'module' => 'facetapi',
          'delta' => '7TqCFBUvppfBoYrlTYxf0VxXrnz4llZ7',
          'region' => 'content_top',
          'weight' => '-8',
        ),
        'views--exp-extracts-page' => array(
          'module' => 'views',
          'delta' => '-exp-extracts-page',
          'region' => 'content_top',
          'weight' => '-7',
        ),
        'current_search-standard' => array(
          'module' => 'current_search',
          'delta' => 'standard',
          'region' => 'content_top',
          'weight' => '-6',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Extract search');
  $export['extract_search'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'home_page';
  $context->description = 'Home page';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views--exp-extracts-page' => array(
          'module' => 'views',
          'delta' => '-exp-extracts-page',
          'region' => 'content',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Home page');
  $export['home_page'] = $context;

  return $export;
}
