<?php

/**
 * @file
 * Contains the SearchApiHighlight class.
 */

/**
 * Processor for highlighting search results.
 */
class PocamExtractSearchApiHighlight extends SearchApiHighlight {

    /**
   * {@inheritdoc}
   */
  public function __construct(SearchApiIndex $index, array $options = array()) {
    parent::__construct($index, $options);

    self::$split = '/[\s,.?]+/iu';
  }

}