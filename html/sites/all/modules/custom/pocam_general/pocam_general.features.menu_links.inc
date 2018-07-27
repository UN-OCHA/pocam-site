<?php
/**
 * @file
 * pocam_general.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function pocam_general_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-footer-menu_about:about.
  $menu_links['menu-footer-menu_about:about'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'about',
    'router_path' => 'about',
    'link_title' => 'About',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_about:about',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: user-menu_login:login.
  $menu_links['user-menu_login:login'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'login',
    'router_path' => 'login',
    'link_title' => 'Login',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_login:login',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Login');

  return $menu_links;
}
