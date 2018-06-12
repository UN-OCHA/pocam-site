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
        'facetapi-7TqCFBUvppfBoYrlTYxf0VxXrnz4llZ7' => array(
          'module' => 'facetapi',
          'delta' => '7TqCFBUvppfBoYrlTYxf0VxXrnz4llZ7',
          'region' => 'content',
          'weight' => '-9',
        ),
        'facetapi-jMt8phZnpIgZZNTtJ71tATNsoZgFxqKb' => array(
          'module' => 'facetapi',
          'delta' => 'jMt8phZnpIgZZNTtJ71tATNsoZgFxqKb',
          'region' => 'content',
          'weight' => '-8',
        ),
        'facetapi-h3E804ufRqmwuxTFodspV21rBJb00L2X' => array(
          'module' => 'facetapi',
          'delta' => 'h3E804ufRqmwuxTFodspV21rBJb00L2X',
          'region' => 'content',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Extract search');
  $export['extract_search'] = $context;

  return $export;
}
