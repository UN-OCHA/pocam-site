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
      | title       | field_text            | field_document_type | field_theme | field_year |
      | Extract1    | Lorem ipsum extract 1 | Resolution          | Sub 1       | 2018       |
      | Extract2    | Lorem ipsum extract 2 | Statement           | Sub 2       | 2014       |
      | Extract3    | Lorem ipsum extract 3 | Resolution          | Sub 4       | 2018       |
    And I run drush "search-api-index"

  @api
  Scenario: Check about link
    Given I am viewing a "page" content with the alias "theme":
      | title                | Themes                         |
      | body:value           | <p>[pocam-general:themes-list]</p> |
      | body:format          | full_html                          |
    Given I am viewing a "page" content:
      | title                | Post title         |
      | body:value           | "<div class='intro'>Search Security Council Resolutions and Statements</div><p>[pocam-general:search-block]</p><p>The Aide Memoire <strong>serves</strong> is a reference tool on the Security Council’s normative practice on the protection of civilians in armed conflict. Based on this practice, it lists <a href='/theme'>the main themes and sub-themes</a> that pertain to the protection of civilians, and proposes model language to address those, including verbatim examples of Security Council agreed language on each identified theme and sub-theme. This site offers a user-friendly interface to search into the addendum of the Aide-Memoire, entirely populated with official Security Council language on the protection of civilians in armed conflict.</p><p><a class='btn--browse' href='/theme'>Browse by theme</a></p>" |
      | body:format          | full_html          |
    When I follow "Browse by theme"
    Then I should see "Top A"
    And I should see "Sub 2"
    And I should not see "Sub 5"
