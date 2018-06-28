<?php

/**
 * @file
 * Theme implementation to display a single Drupal page.
 */

// Remove messsage.
unset($page['content']['system_main']['default_message']);

?>
  <div class="page-wrapper">
    <?php include 'header.inc'; ?>

    <?php if($messages): ?>
    <div id="messages" class="container">
      <?php print $messages; ?>
    </div>
    <?php endif; ?>

    <div id="main" class="container">
      <?php if ($tabs): ?>
        <div class="tabs">
          <?php print render($tabs); ?>
        </div>
      <?php endif; ?>

      <?php if (!drupal_is_front_page() && $title && isset($node) && $node->type !== 'ev_event'): ?>
      <h1>
        <?php print $title; ?>
      </h1>
      <?php endif; ?>

      <?php print render($page['content_top_1']); ?>
      <?php print render($page['content_top_2']); ?>
      <?php print render($page['content_top_3']); ?>
      <?php print render($page['content']); ?>
    </div>
  </div>
  <?php include 'footer.inc'; ?>
