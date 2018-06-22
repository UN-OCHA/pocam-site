Feature: Home page
  When on the website
  As a visitor
  I should be able to use home page search

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
      | title       | field_text            | field_document_type | field_theme | field_year |
      | Extract1    | Lorem ipsum extract 1 | Resolution          | Sub 1       | 2018       |
      | Extract2    | Lorem ipsum extract 2 | Statement           | Sub 2       | 2014       |
      | Extract3    | Lorem ipsum extract 3 | Resolution          | Sub 4       | 2018       |
    And I run drush "search-api-index"

  @api
  Scenario: Check homepage
    Given I am on the homepage
    Then I should see "Search Security Council Resolutions and Statements"

  @api
  Scenario: See the extracts
    Given I am on the homepage
    When I fill in "search_api_views_fulltext" with "extract 1"
    And I press "edit-submit-extracts"
    Then I should see "extract 1"
    And I should not see "extract 2"
    And I should not see "extract 3"
