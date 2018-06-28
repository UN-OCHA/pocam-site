(function ($) {
  Drupal.behaviors.ocha = {
    attach: function (context, settings) {
      'use strict';

      // Add class to all p tags.
      $('.views-field-field-text-value p').addClass('collapsed');

      // Add click handler.
      $('.data--read-more').click(function (e) {
        $(e.target)
          .parent()
          .find('.views-field-field-text-value p')
          .toggleClass('collapsed');
      });
    }
  };
})(jQuery);
