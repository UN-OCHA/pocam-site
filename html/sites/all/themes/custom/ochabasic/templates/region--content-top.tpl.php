<?php

/**
 * @file
 * Default theme implementation to display a region.
 */
?>
<?php if ($content): ?>
  <div class="<?php print $classes; ?>">
    <details open class="search-filters">
      <summary>Show/Hide filters</summary>
      <?php print $content; ?>
    </details>
  </div>
<?php endif; ?>
