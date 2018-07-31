<?php

/**
 * @file
 * Template overrides, (pre-)process and alter hooks for the OCHA Basic theme.
 */

 /**
  * Returns HTML for the facet title, usually the title of the block.
  */
function ochabasic_facetapi_title($variables) {
  return t('Filter by @title', array('@title' => drupal_strtolower($variables['title'])));
}

/**
 * Returns HTML for a search keys facet item.
 */
function ochabasic_current_search_keys($variables) {
  $link_text = check_plain($variables['keys']);

  $variables['path'] = current_path();
  $variables['text'] = 'X ' . $link_text;
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['title'] = t('Remove keyword: @text', array('@text' => $link_text));

  return theme('link', $variables);
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

/**
 * Implements hook_preprocess_page().
 */
function ochabasic_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form') {
    $form['#attributes']['role'] = 'search';
    $form['search_block_form']['#attributes']['placeholder'] = t('What are you looking for?');
    $form['actions']['submit'] = array(
      '#type' => 'item',
      '#markup' => '<button type="submit" class="cd-search__submit">Go <span class="icon-arrow-right" aria-hidden="true"></span></button>',
      '#weight' => 1000,
    );
  }
}

/**
 * Implements hook_preprocess_search_block_form().
 */
function ochabasic_preprocess_search_block_form(&$vars) {
  $vars['search_form'] = str_replace('type="text"', 'type="search"', $vars['search_form']);
}

/**
 * Implements hook_preprocess_html().
 */
function ochabasic_preprocess_html(&$vars) {
  $apple = array(
    '#tag' => 'link',
    '#attributes' => array(
      'href' => base_path() . path_to_theme() . '/apple-touch-icon.png',
      'rel' => 'apple-touch-icon',
      'sizes' => '180x180',
    ),
  );
  drupal_add_html_head($apple, 'apple-touch-icon');
  $fav_32 = array(
    '#tag' => 'link',
    '#attributes' => array(
      'href' => base_path() . path_to_theme() . '/favicon-32x32.png',
      'rel' => 'icon',
      'sizes' => '32x32',
      'type' => 'image/png',
    ),
  );
  drupal_add_html_head($fav_32, 'favicon-32x32');
  $fav_16 = array(
    '#tag' => 'link',
    '#attributes' => array(
      'href' => base_path() . path_to_theme() . '/favicon-16x16.png',
      'rel' => 'icon',
      'sizes' => '16x16',
      'type' => 'image/png',
    ),
  );
  drupal_add_html_head($fav_16, 'favicon-16x16');
  $safari_pinned_tab = array(
    '#tag' => 'link',
    '#attributes' => array(
      'href' => base_path() . path_to_theme() . '/safari-pinned-tab.svg',
      'rel' => 'mask-icon',
      'color' => '#5bbad5',
    ),
  );
  drupal_add_html_head($safari_pinned_tab, 'safari_pinned_tab');
}

/**
 * Implements hook_pwa_manifest_alter().
 */
function ochabasic_pwa_manifest_alter(&$manifest) {
  // Hard-code a theme-color into the manifest.
  $manifest['theme_color'] = '#026CB6';

  // Override the PWA default icons with OCHA defaults.
  //
  // If you are using this theme as a starterkit feel free to manually adjust
  // this code block, otherwise copy this hook into your subtheme and customize
  // to your heart's content.
  $manifest['icons'] = [
    [
      'src' => url(drupal_get_path('theme', 'ocha_basic') . '/android-chrome-512x512.png'),
      'sizes' => '512x512',
      'type' => 'image/png',
    ],
    [
      'src' => url(drupal_get_path('theme', 'ocha_basic') . '/android-chrome-192x192.png'),
      'sizes' => '192x192',
      'type' => 'image/png',
    ],
  ];
}
