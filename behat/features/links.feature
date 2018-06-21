Feature: Check menu links
  When on the website
  As a visitor
  I should see links

  Background:
    Given I am an anonymous user

  Scenario: Check links
    Given I am on the homepage
    Then I should see "About"
    And I should see "Login"
    And I should see "Themes"

  Scenario: Check about link
    Given I am on the homepage
    When I follow "About"
    Then I should see "What is the Protection of Civilians Aide Memoire?"

  Scenario: Check themes link
    Given I am on the homepage
    When I follow "Themes"
    Then I should see "Themes"
