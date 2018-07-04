<?php

/**
 * @file
 * Theme functions.
 */

/**
 * Returns HTML for the facet title, usually the title of the block.
 */
function ochabasic_facetapi_title($variables) {
  return t('Filter by @title', array('@title' => drupal_strtolower($variables['title'])));
}

/**
 * Returns HTML for an active facet item.
 */
function ochabasic_facetapi_link_active($variables) {
  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $link_text,
    'active' => TRUE,
  );

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
  );
  $variables['text'] = t('!facetapi_deactivate_widget !facetapi_accessible_markup', $replacements);
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['title'] = t('Remove filter: @text', array('@text' => $link_text));
  return theme('link', $variables);
}

/**
 * Returns HTML for the deactivation widget.
 */
function ochabasic_facetapi_deactivate_widget($variables) {
  return 'X';
}

/**
 * Returns HTML that adds accessible markup to facet links.
 */
function ochabasic_facetapi_accessible_markup($variables) {
  $vars = array('@text' => $variables['text']);
  $text = ($variables['active']) ? t('Remove filter', $vars) : t('Apply filter', $vars);
  // Add spaces before and after the text, since other content may be displayed
  // inline with this and we don't want the words to run together. However, the
  // spaces must be inside the <span> so as not to disrupt the layout for
  // sighted users.
  return '<span class="element-invisible"> ' . $text . ' </span>' . $variables['text'];
}
