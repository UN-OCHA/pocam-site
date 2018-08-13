<?php if ($secondary_menu): ?>
  <?php print theme('links__system_secondary_menu',
    array(
      'links' => $secondary_menu,
      'attributes' => array(
        'id' => 'secondary-menu',
        'class' => array('cd-user-menu'),
      ),
    )
  ); ?>
<?php endif; ?>

<?php if (isset($page['language_switcher'])): ?>
<div class="cd-global-header__language-switcher">
  <?php print $page['language_switcher']; ?>
</div>
<?php endif; ?>
