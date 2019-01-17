<?php

/**
 * @file
 * Minimal profile for POCAM.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 */
function pocam_form_install_configure_form_alter(&$form, $form_state) {
  $form['site_information']['site_name']['#default_value'] = 'Aide Memoire';
}
