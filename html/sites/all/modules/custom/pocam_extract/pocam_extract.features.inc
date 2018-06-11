<?php
/**
 * @file
 * pocam_extract.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pocam_extract_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function pocam_extract_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

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

/**
 * Implements hook_default_search_api_index().
 */
function pocam_extract_default_search_api_index() {
  $items = array();
  $items['pocam_extracts'] = entity_import('search_api_index', '{
    "name" : "Extracts",
    "machine_name" : "pocam_extracts",
    "description" : null,
    "server" : "local",
    "item_type" : "node",
    "options" : {
      "datasource" : { "bundles" : [ "pocam_extract" ] },
      "index_directly" : 1,
      "cron_limit" : "50",
      "fields" : {
        "field_document_type:name" : { "type" : "list\\u003Ctext\\u003E" },
        "field_link:title" : { "type" : "text" },
        "field_see_also:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_text:value" : { "type" : "text", "boost" : "2.0" },
        "field_theme:field_long_name" : { "type" : "text" },
        "field_theme:field_see_also:title" : { "type" : "list\\u003Ctext\\u003E" },
        "field_theme:name" : { "type" : "text" },
        "search_api_language" : { "type" : "string" }
      },
      "data_alter_callbacks" : {
        "search_api_alter_bundle_filter" : {
          "status" : 0,
          "weight" : "-10",
          "settings" : { "default" : "1", "bundles" : [] }
        },
        "search_api_alter_add_url" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_aggregation" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_add_viewed_entity" : { "status" : 0, "weight" : "0", "settings" : { "mode" : "full" } },
        "search_api_alter_add_hierarchy" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : { "field_document_type:parents_all" : "field_document_type:parents_all" } }
        },
        "search_api_alter_node_access" : { "status" : 0, "weight" : "0", "settings" : [] },
        "search_api_alter_node_status" : { "status" : 1, "weight" : "0", "settings" : [] }
      },
      "processors" : {
        "search_api_case_ignore" : {
          "status" : 1,
          "weight" : "0",
          "settings" : { "fields" : {
              "field_text:value" : true,
              "field_link:title" : true,
              "field_see_also:title" : true
            }
          }
        },
        "search_api_html_filter" : {
          "status" : 1,
          "weight" : "10",
          "settings" : {
            "fields" : { "field_text:value" : true },
            "title" : 0,
            "alt" : 0,
            "tags" : "h1 = 5\\r\\nh2 = 3\\r\\nh3 = 2\\r\\nstrong = 2\\r\\nb = 2\\r\\nem = 1.5\\r\\nu = 1.5"
          }
        },
        "search_api_tokenizer" : {
          "status" : 0,
          "weight" : "20",
          "settings" : {
            "fields" : {
              "field_text:value" : true,
              "field_link:title" : true,
              "field_see_also:title" : true
            },
            "spaces" : "[^[:alnum:]]",
            "ignorable" : "[\\u0027]"
          }
        },
        "search_api_stopwords" : {
          "status" : 0,
          "weight" : "30",
          "settings" : {
            "fields" : {
              "field_text:value" : true,
              "field_link:title" : true,
              "field_see_also:title" : true
            },
            "file" : "",
            "stopwords" : "but\\r\\ndid\\r\\nthe this that those\\r\\netc"
          }
        },
        "search_api_porter_stemmer" : {
          "status" : 0,
          "weight" : "35",
          "settings" : {
            "fields" : {
              "field_text:value" : true,
              "field_link:title" : true,
              "field_see_also:title" : true
            },
            "exceptions" : "texan=texa"
          }
        },
        "search_api_highlighting" : {
          "status" : 1,
          "weight" : "40",
          "settings" : {
            "prefix" : "\\u003Cstrong\\u003E",
            "suffix" : "\\u003C\\/strong\\u003E",
            "excerpt" : 1,
            "excerpt_length" : "256",
            "exclude_fields" : {
              "field_link:title" : "field_link:title",
              "field_see_also:title" : "field_see_also:title"
            },
            "highlight" : "always",
            "highlight_partial" : 1
          }
        }
      }
    },
    "enabled" : "1",
    "read_only" : "0"
  }');
  return $items;
}

/**
 * Implements hook_default_search_api_server().
 */
function pocam_extract_default_search_api_server() {
  $items = array();
  $items['local'] = entity_import('search_api_server', '{
    "name" : "local",
    "machine_name" : "local",
    "description" : "",
    "class" : "search_api_db_service",
    "options" : {
      "database" : "default:default",
      "min_chars" : "1",
      "partial_matches" : 1,
      "indexes" : { "pocam_extracts" : {
          "search_api_language" : {
            "table" : "search_api_db_pocam_extracts",
            "column" : "search_api_language",
            "type" : "string",
            "boost" : "1.0"
          },
          "field_text:value" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "text",
            "boost" : "2.0"
          },
          "field_link:title" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_see_also:title" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "list\\u003Ctext\\u003E",
            "boost" : "1.0"
          },
          "field_document_type:name" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "list\\u003Ctext\\u003E",
            "boost" : "1.0"
          },
          "field_theme:name" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_theme:field_long_name" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "text",
            "boost" : "1.0"
          },
          "field_theme:field_see_also:title" : {
            "table" : "search_api_db_pocam_extracts_text",
            "type" : "list\\u003Ctext\\u003E",
            "boost" : "1.0"
          }
        }
      }
    },
    "enabled" : "1"
  }');
  return $items;
}
