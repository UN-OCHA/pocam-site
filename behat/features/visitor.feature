Feature: See extracts
  When on the website
  As a visitor
  I should be able to see extracts

  Background:
    Given I am an anonymous user
    And "type" terms:
      | name       |
      | Resolution |
      | Statement  |
    And "theme" with terms:
      | name        | parent      |
      | Sub 1       | Top A       |
      | Sub 2       | Top A       |
      | Sub 3       | Top A       |
      | Sub 4       | Top B       |
      | Sub 5       | Top B       |
    And list of extracts:
      | title       | field_text            | field_document_type | field_theme |
      | Extract1    | Lorem ipsum extract 1 | Resolution          | Sub 1       |
      | Extract2    | Lorem ipsum extract 2 | Statement           | Sub 2       |
      | Extract3    | Lorem ipsum extract 3 | Resolution          | Sub 4       |
    And I run drush "search-api-index"

  @api
  Scenario: Check homepage
    Given I am on the homepage
    Then I should see "Fulltext search"

  @api
  Scenario: See the extracts
    When I go to "extracts"
    And I wait for AJAX to finish
    Then I should see "extract 1"
    And I should see "extract 2"
    And I should see "extract 3"
