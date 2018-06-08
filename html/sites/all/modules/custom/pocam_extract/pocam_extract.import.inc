<?php

/**
 * @file
 * Admin.
 */

/**
 * Import locations form.
 */
function pocam_extract_import_extract($form, &$form_state) {
  if (!variable_get('file_private_path')) {
    $form['private_path'] = array(
      '#type' => 'markup',
      '#markup' => t('You must specify a private file system path in the !settings so we can save the created files there.', array('!settings' => l(t('file system settings'), 'admin/config/media/file-system'))),
    );
  }
  else {
    $form['csv_separator'] = array(
      '#type' => 'radios',
      '#title' => t('CSV separator'),
      '#required' => TRUE,
      '#options' => array(
        ',' => ', (comma)',
        ';' => '; (semicolon)',
      ),
      '#default_value' => ';',
    );

    $form['csv'] = array(
      '#type' => 'file',
      '#title' => t('Upload csv file'),
      '#size' => 48,
    );

    $form['strategy'] = array(
      '#type' => 'radios',
      '#title' => t('Import strategy'),
      '#required' => TRUE,
      '#options' => array(
        'overwrite' => 'Overwrite all extracts',
        'append' => 'Append extracts defined in csv',
      ),
      '#default_value' => 'append',
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Import extracts'),
    );
  }
  $form['#validate'] = array('pocam_extract_import_extract_validate');
  $form['#submit'] = array('pocam_extract_import_extract_submit');
  return $form;
}

/**
 * Form validate callback.
 */
function pocam_extract_import_extract_validate($form, &$form_state) {
  $validators['file_validate_extensions'] = array('csv');

  // Upload to the temp directory.
  $file = file_save_upload('csv', $validators, FALSE, FILE_EXISTS_REPLACE);
  if (!$file) {
    form_error($form['csv'], t('Something went wrong while uploading the file.'));
    return;
  }
  $form_state['values']['csv'] = $file;
}

/**
 * Form submit callback.
 */
function pocam_extract_import_extract_submit($form, $form_state) {
  $file = $form_state['values']['csv'];
  pocam_extract_import_extract_populate_queue($file->uri, $form_state['values']['strategy'], $form_state['values']['csv_separator']);
}

/**
 * Populate queue.
 */
function pocam_extract_import_extract_populate_queue($csv_file, $strategy, $csv_separator) {
  $batch = array(
    'operations' => array(),
    'title' => t('Importing'),
    'init_message' => t('Initializing.'),
    'progress_message' => t('Processed @current out of @total.'),
    'file' => drupal_get_path('module', 'pocam_extract') . '/pocam_extract.import.inc',
    'finished' => 'pocam_extract_import_extract_finished',
  );

  // Check file for UTF-8 and BOM.
  pocam_extract_check_csv_file_utf8_bom($csv_file);

  $encoding_list[] = "UTF-8";
  $encoding_list[] = "ASCII";
  $encoding_list[] = "ISO-8859-1";

  $handle = fopen($csv_file, 'r');
  // Assume 1 header line.
  $header = fgetcsv($handle, 0, $csv_separator, '"');
  $header_lowercase = array_map('drupal_strtolower', $header);

  while ($row = fgetcsv($handle, 0, $csv_separator, '"')) {
    $data = array();
    for ($i = 0; $i < count($row); $i++) {
      $content = $row[$i];
      if (mb_detect_encoding($content, $encoding_list, TRUE) == 'ISO-8859-1') {
        $row[$i] = utf8_encode($content);
      }
      elseif (!mb_check_encoding($content, 'UTF-8') || !($content === mb_convert_encoding(mb_convert_encoding($content, 'UTF-32', 'UTF-8'), 'UTF-8', 'UTF-32'))) {
        $content = mb_convert_encoding($content, 'UTF-8');
        if (mb_check_encoding($content, 'UTF-8')) {
          $row[$i] = $content;
        }
      }
      $data[$header_lowercase[$i]] = $row[$i];
    }

    $batch['operations'][] = array(
      'pocam_extract_import_extract_line',
      array($data, $strategy),
    );
  }
  fclose($handle);
  batch_set($batch);
  batch_process(current_path());
}

/**
 * Import node data.
 */
function pocam_extract_import_extract_line($data, $strategy, &$context) {
  if (!isset($data['text']) || empty($data['text'])) {
    return;
  }

  global $user;

  $values = array(
    'type' => 'pocam_extract',
    'uid' => $user->uid,
    'status' => 1,
    'comment' => 0,
    'promote' => 0,
  );
  $entity = entity_create('node', $values);

  $node_wrapper = entity_metadata_wrapper('node', $entity);

  $node_wrapper->title->set(substr($data['text'], 0, 54) . ' ...');
  $node_wrapper->field_text->set(array(
    'value' => $data['text'],
  ));

  if (isset($data['ref']) && !empty($data['ref'])) {
    $parts = explode(' ', $data['ref']);
    $node_wrapper->field_link->set(array(
      'title' => $data['ref'],
      'url' => 'https://undocs.org/' . $parts[0] . str_replace(',', '', $parts[1]),
    ));
  }

  $node_wrapper->save();
  $context['results']['succes'][] = 'Imported row ' . $node_wrapper->getIdentifier();
}

function pocam_extract_import_extract_finished($success, $results, $operations) {
  if ($success) {
    if (!isset($results['succes'])) {
      $results['succes'] = array();
    }
    $message = t('@count extracts successfully imported', array('@count' => count($results['succes'])));
    drupal_set_message($message);

    if (!empty($results['failures'])) {
      $message = t('Failed to import @count locations', array('@count' => count($results['failures'])));
      drupal_set_message($message, 'error');
      drupal_set_message(implode('<br>', $results['failures']), 'error');
    }
  }
}

/**
 * Recursively create terms.
 */
function pocam_extract_create_terms_location($terms, $voc) {
  $parent = 0;
  foreach ($terms as $term_info) {
    if (!empty($term_info['name'])) {
      $q = db_select('taxonomy_term_data', 't')->fields('t', array('tid'));
      $q->join('taxonomy_term_hierarchy', 'hierarchy', 't.tid = hierarchy.tid');
      $q->join('field_data_field_pcode', 'pcode', 't.tid = pcode.entity_id');
      $existing = $q->condition('pcode.field_pcode_value', $term_info['pcode'])
        ->condition('vid', $voc->vid)
        ->condition('parent', $parent)
        ->range(0, 1)
        ->execute()
        ->fetchField();

      if ($existing) {
        // Check if we need to update.
        $term = taxonomy_term_load($existing);
        if ($term->name != $term_info['name']) {
          $term->name = $term_info['name'];
          $term->name_field['en'][0]['value'] = $term_info['name'];
          $wrapped = entity_metadata_wrapper('taxonomy_term', $term);
          taxonomy_term_save($term);
        }
        $parent = $existing;
        continue;
      }

      $term = new stdClass();
      $term->language = 'en';
      $term->name = $term_info['name'];
      $term->name_field['en'][0]['value'] = $term_info['name'];
      $term->field_pcode['und'][0]['value'] = $term_info['pcode'];
      $term->field_loc_admin_level['und'][0]['value'] = $term_info['admin'];
      $term->vid = $voc->vid;
      $term->parent = $parent;
      $term->vocabulary_machine_name = $voc->machine_name;
      $wrapped = entity_metadata_wrapper('taxonomy_term', $term);
      taxonomy_term_save($term);
      $parent = $term->tid;
    }
  }
  return $parent;
}

/**
 * Check file for UTF-8 and BOM.
 */
function pocam_extract_check_csv_file_utf8_bom($csv_file) {
  // Make sure it's UTF-8.
  $contents = file_get_contents($csv_file);
  if (!mb_check_encoding($contents, 'UTF-8')) {
    $encoding_list[] = "UTF-8";
    $encoding_list[] = "ASCII";
    $encoding_list[] = "ISO-8859-1";
    file_put_contents($csv_file, mb_convert_encoding($contents, 'UTF-8', mb_detect_encoding($contents, $encoding_list, TRUE)));
  }

  // Make sure it's has no BOM.
  $contents = file_get_contents($csv_file);
  $bom = pack('CCC', 0xEF, 0xBB, 0xBF);
  if (strncmp($contents, $bom, 3) === 0) {
    $contents = substr($contents, 3);
    file_put_contents($csv_file, $contents);
  }
}
