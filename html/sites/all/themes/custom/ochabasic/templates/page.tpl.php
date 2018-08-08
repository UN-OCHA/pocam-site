<?php

/**
 * @file
 * Returns the HTML for a single Drupal page.
 *
 * Complete documentation for this file is available online.
 * @see https://drupal.org/node/1728148
 */
 // Remove messsage.
 unset($page['content']['system_main']['default_message']);
?>
<div class="page-wrapper">
  <a href="#main-content" class="skip-link"><?php print t('Skip to main content'); ?></a>
  <?php include 'header.inc'; ?>
  <?php if($messages): ?>
    <div class="cd-container">
      <?php print $messages; ?>
    </div>
  <?php endif; ?>

  <div class="cd-container" id="main-content">

    <?php if ($tabs): ?>
      <div class="tabs">
        <?php print render($tabs); ?>
      </div>
    <?php endif; ?>

      <?php if (!drupal_is_front_page() && $title && isset($node) && $node->type !== 'ev_event'): ?>
      <h1 class="page__title">
        <?php print $title; ?>
      </h1>
      <?php endif; ?>

      <?php print render($page['content_top_3']); ?>
      <?php print render($page['content_top_1']); ?>
      <?php print render($page['content_top_2']); ?>
      <?php print render($page['content']); ?>

  </div>
</div>
<?php include 'footer.inc'; ?>
