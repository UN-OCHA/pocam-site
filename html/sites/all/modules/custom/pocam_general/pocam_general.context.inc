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
        'facetapi-0Pusq0zftXdOJDSRLOSFYp7IB6GKKuh1' => array(
          'module' => 'facetapi',
          'delta' => '0Pusq0zftXdOJDSRLOSFYp7IB6GKKuh1',
          'region' => 'content',
          'weight' => '-10',
        ),
        'facetapi-h4J767t1sdzXEtEOAD03WQ9E8BvwROxn' => array(
          'module' => 'facetapi',
          'delta' => 'h4J767t1sdzXEtEOAD03WQ9E8BvwROxn',
          'region' => 'content',
          'weight' => '-9',
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
