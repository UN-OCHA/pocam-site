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
        'overwrite' => 'Remove all extracts and themes first',
        'append' => 'Append extracts and themes',
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
  if ($form_state['values']['strategy'] === 'overwrite') {
    pocam_extract_delete_content();
  }

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

  $id = 1;
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
    $data['_id'] = $id++;

    $batch['operations'][] = array(
      'pocam_extract_import_extract_line',
      array($data, $strategy),
    );
  }
  fclose($handle);

  // Clear temp storage.
  variable_del('pocam_extract_import_previous_row');

  // Start batch.
  batch_set($batch);
  batch_process(current_path());
}

/**
 * Import node data.
 * *
 * @SuppressWarnings(PHPMD)
 */
function pocam_extract_import_extract_line($data, $strategy, &$context) {
  if (!isset($data['text']) || empty($data['text'])) {
    return;
  }

  $previous_row = variable_get('pocam_extract_import_previous_row', array());
  if (empty($previous_row)) {
    $previous_row = $data;
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

  // Ellipsis break drupal_write_record.
  $data['text'] = str_replace('…', '...', $data['text']);

  $node_wrapper->title->set(truncate_utf8($data['text'], 76, TRUE, TRUE));
  $node_wrapper->field_text->set(array(
    'value' => $data['text'],
  ));

  if (isset($data['ref']) && !empty($data['ref'])) {
    $parts = explode(' ', $data['ref']);

    // Set node title.
    $node_wrapper->title->set('Excerpt from ' . $data['ref']);

    // Document type.
    if (strpos($parts[0], '/RES/') !== FALSE) {
      $node_wrapper->field_link->set(array(
        'title' => $data['ref'],
        'url' => 'https://undocs.org/' . $parts[0] . str_replace(',', '', $parts[1]),
      ));

      $term = pocam_extract_create_terms('Resolution', 'type');
      $node_wrapper->field_document_type->set($term->tid);

      // Year.
      $year = str_replace(array('(', ')', ','), '', $parts[1]);
      $year = (int) trim($year);
      $node_wrapper->field_year->set($year);
    }
    else {
      $node_wrapper->field_link->set(array(
        'title' => $data['ref'],
        'url' => 'https://undocs.org/' . str_replace(',', '', $parts[0]),
      ));

      $term = pocam_extract_create_terms('Statement', 'type');
      $node_wrapper->field_document_type->set($term->tid);

      // Year.
      $year_parts = explode('/', $parts[0]);
      $year = (int) $year_parts[2];
      $node_wrapper->field_year->set($year);
    }
  }

  // Merge previous row if needed.
  if (isset($data['level 0']) && empty($data['level 0'])) {
    $data['level 0'] = $previous_row['level 0'];
    if (isset($data['level 1']) && empty($data['level 1'])) {
      $data['level 1'] = $previous_row['level 1'];
      if (isset($data['level 2']) && empty($data['level 2'])) {
        $data['level 2'] = $previous_row['level 2'];
      }
    }
  }
  if (isset($data['see also']) && empty($data['see also'])) {
    $data['see also'] = $previous_row['see also'];
  }

  // Theme.
  $themes = array();
  if (isset($data['level 0']) && !empty($data['level 0'])) {
    $themes[] = $data['level 0'];
  }
  if (isset($data['level 1']) && !empty($data['level 1'])) {
    $themes[] = $data['level 1'];
  }
  if (isset($data['level 2']) && !empty($data['level 2'])) {
    $themes[] = $data['level 2'];
  }

  if (!empty($themes)) {
    $term = pocam_extract_create_terms($themes, 'theme', $data['_id']);
    $node_wrapper->field_theme->set($term->tid);

    // Update see also fields on term.
    if (isset($data['see also']) && !empty($data['see also'])) {
      // Only update if it's empty.
      if (!isset($term->field_see_also[LANGUAGE_NONE]) || empty($term->field_see_also[LANGUAGE_NONE])) {
        $see_also = $data['see also'];
        $see_also = str_replace('See also, for example, ', '', $see_also);
        $see_alsos = explode(';', $see_also);

        $links = array();
        foreach ($see_alsos as $item) {
          $parts = explode(' ', trim($item));
          $links[] = array(
            'title' => trim($item),
            'url' => 'https://undocs.org/' . $parts[0] . str_replace(',', '', $parts[1]),
          );
        }
        $term->field_see_also[LANGUAGE_NONE] = $links;
        taxonomy_term_save($term);
      }
    }
  }

  $node_wrapper->save();
  $context['results']['succes'][] = 'Imported row ' . $node_wrapper->getIdentifier();

  // Update previous row.
  $previous_row['level 0'] = $data['level 0'];
  $previous_row['level 1'] = $data['level 1'];
  $previous_row['level 2'] = $data['level 2'];
  $previous_row['see also'] = $data['see also'];

  variable_set('pocam_extract_import_previous_row', $previous_row);
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
function pocam_extract_create_terms($terms, $voc, $term_weight = 1) {
  $vocabularies = taxonomy_vocabulary_get_names();

  // Make sure we have an array.
  if (is_string($terms)) {
    $terms = array($terms);
  }

  $parent = FALSE;
  foreach ($terms as $term_name) {
    // Make sure term name is not too long.
    $short_term_name = $term_name;
    if (drupal_strlen($term_name) > 250) {
      $short_term_name = truncate_utf8($term_name, 250, TRUE, TRUE);
    }

    $existing = taxonomy_get_term_by_name($short_term_name, $voc);
    if (!empty($existing)) {
      $term = reset($existing);
      $parent = $term;
      continue;
    }

    $term = new stdClass();
    $term->vid = $vocabularies[$voc]->vid;
    $term->name = $short_term_name;
    $term->weight = $term_weight;
    $term->description = $term_name;
    if (isset($parent) && isset($parent->tid)) {
      $term->parent = $parent->tid;
    }
    taxonomy_term_save($term);
    $parent = $term;
  }

  return $term;
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

function pocam_extract_delete_content() {
  $results = db_select('node', 'n')
    ->fields('n', array('nid'))
    ->condition('type', 'pocam_extract')
    ->execute();

  foreach ($results as $result) {
    $nids[] = $result->nid;
  }

  if (!empty($nids)) {
    node_delete_multiple($nids);
    drupal_set_message(t('Deleted %count nodes.', array('%count' => count($nids))));
  }

  $vid = taxonomy_vocabulary_machine_name_load('theme')->vid;
  foreach (taxonomy_get_tree($vid) as $term) {
    taxonomy_term_delete($term->tid);
  }
}
