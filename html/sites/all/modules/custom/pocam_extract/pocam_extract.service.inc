<?php

/**
 * @file
 * Contains SearchApiDbService.
 */

class PocamExtractSearchApiDbService extends SearchApiDbService {

  /**
   * Splits a keyword expression into separate words.
   */
  protected function splitKeys($keys) {
    if (is_scalar($keys)) {
      $proc = drupal_strtolower(trim($keys));
      if (is_numeric($proc)) {
        return ltrim($proc, '-0');
      }
      elseif (drupal_strlen($proc) < $this->options['min_chars']) {
        $this->ignored[$keys] = 1;
        return NULL;
      }

      $words = preg_split('/[\s,.?]+/u', $proc, -1, PREG_SPLIT_NO_EMPTY);
      if (count($words) > 1) {
        $proc = $this->splitKeys($words);
        if ($proc) {
          $proc['#conjunction'] = 'AND';
        }
        else {
          $proc = NULL;
        }
      }

      return $proc;
    }
    foreach ($keys as $i => $key) {
      if (element_child($i)) {
        $keys[$i] = $this->splitKeys($key);
      }
    }
    return array_filter($keys);
  }

}
