<?php
/**
 * @file
 * Displays the site footer.
 */

?>
<footer class="cd-footer" role="contentinfo">
  <div class="cd-container cd-footer__inner">

    <?php if ($secondary_menu): ?>
      <?php print theme('links__menu_footer_menu',
        array(
          'links' => menu_navigation_links('menu-footer-menu'),
          'attributes' => array(
            'id' => 'footer-menu',
            'class' => array('footer__nav cd-footer-menu cd-footer__section'),
          ),
        )
      ); ?>
    <?php
endif; ?>


  <?php include 'components/cd-provided-by.inc'; ?>

  <?php include 'components/cd-copyright.html'; ?>

 </div>
</footer>
