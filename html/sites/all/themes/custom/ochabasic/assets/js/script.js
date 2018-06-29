(function ($) {
  Drupal.behaviors.ochaCommon = {
    attach: function (context, settings) {
      'use strict';

      // Add class and handler to all p tags.
      $('.views-field-field-text-value p')
        .addClass('collapsed')
        .click(function (e) {
          $(e.target).toggleClass('collapsed');
        });

      // Add click handler.
      $('.data--read-more').click(function (e) {
        $(e.target)
          .parent()
          .find('.views-field-field-text-value p')
          .toggleClass('collapsed');
      });
    }
  };

  Drupal.behaviors.ochaFilters = {
    attach: function (context, settings) {
      'use strict';

      // Add button to show/hide filters.
      var button = $('<button class="toggle-button">Show/Hide filters</button>');
      button.click(function (e) {
        $('.region-content-top-2').toggle();
      });

      $('#block-views-exp-extracts-page').append(button);
    }
  };

})(jQuery);
