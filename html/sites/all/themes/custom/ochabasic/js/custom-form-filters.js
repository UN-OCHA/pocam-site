/**
 * @file
 * Custom functions for form filters.
 */

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

      // Add button to all p tags.
      $('.views-field-field-text-value p').after('<div class="data--read-more"><button>Read more</button></div>');

      // Add click handler.
      $('.data--read-more').click(function (e) {
        $(e.target)
          .parent().parent()
          .find('p')
          .toggleClass('collapsed');

        e.stopPropagation();
      });
    }
  };

  Drupal.behaviors.ochaFilters = {
    attach: function (context, settings) {
      'use strict';

      // Add button to add filters.
      var button = $('<button class="toggle-button">Add filters</button>');
      button.click(function (e) {
        $('.region-content-top-2').toggle();
      });

      $('#block-views-exp-extracts-page').append(button);

      // Hide by default.
      $('.region-content-top-2').hide();
    }
  };

})(jQuery);
