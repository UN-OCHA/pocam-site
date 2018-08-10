Feature: Check static pages
  When on the website
  As a visitor
  I should see static pages

  Background:
    Given I am an anonymous user

  @api
  Scenario: Check about page
    Given I am viewing a "page" content with the alias "about" and menu "menu-footer-menu:About":
      | title                | What is the Protection of Civilians Aide Memoire?         |
      | body:value           | "<p>The Security Council Aide Memoire for the Consideration of Issues pertaining to the Protection of Civilians in Armed Conflict was elaborated in 2002 upon a request from the President of the Security Council to the Secretary-General (<a href='https://www.un.org/en/ga/search/view_doc.asp?symbol=S/2001/614' target='_blank'>S/2001/614</a>), and is periodically updated by OCHA. All editions of the Aide Memoire were discussed by the Security Council and annexed to a Security Council Presidential Statement.</p><p>The Aide Memoire serves as a reference tool on the Security Council’s normative practice on the protection of civilians in armed conflict. Based on this practice, it lists the main themes and sub-themes that pertain to the protection of civilians, and proposes model language to address those, including verbatim examples of Security Council agreed language on each identified theme and sub-theme. This site offers a user-friendly interface to search into the addendum of the Aide-Memoire, entirely populated with official Security Council language on the protection of civilians in armed conflict.</p><p>The physical version of the Aide Memoire, having evolved from a 7-page document (<a href='https://www.un.org/en/ga/search/view_doc.asp?symbol=S/PRST/2002/6' target='_blank'>S/PRST/2002/6</a>) to several hundred pages of references (most recent reference to be added), is in itself a testament to the relevance of the protection of civilians to the Security Council, and the importance the Security Council gives to this issue, which it called “one of the core issues on its agenda” (<a href='https://undocs.org/S/PRST/2015/23' target='_blank'>S/PRST/2015/23</a>).</p><p>[pocam-general:themes-list]</p>" |
      | body:format          | full_html          |
    And I am viewing a "page" content with the alias "theme" and menu "main-menu:Themes":
      | title                | Themes                         |
      | body:value           | <p>[pocam-general:themes-list]</p> |
      | body:format          | full_html                          |
    When I follow "About"
    Then I should see "What is the Protection of Civilians Aide Memoire?"

  @api
  Scenario: Check themes page
    Given I am viewing a "page" content with the alias "theme" and menu "main-menu:Themes":
      | title                | Themes                         |
      | body:value           | <p>[pocam-general:themes-list]</p> |
      | body:format          | full_html                          |
    And I am viewing a "page" content with the alias "about" and menu "menu-footer-menu:About":
      | title                | What is the Protection of Civilians Aide Memoire?         |
      | body:value           | "<p>The Security Council Aide Memoire for the Consideration of Issues pertaining to the Protection of Civilians in Armed Conflict was elaborated in 2002 upon a request from the President of the Security Council to the Secretary-General (<a href='https://www.un.org/en/ga/search/view_doc.asp?symbol=S/2001/614' target='_blank'>S/2001/614</a>), and is periodically updated by OCHA. All editions of the Aide Memoire were discussed by the Security Council and annexed to a Security Council Presidential Statement.</p><p>The Aide Memoire serves as a reference tool on the Security Council’s normative practice on the protection of civilians in armed conflict. Based on this practice, it lists the main themes and sub-themes that pertain to the protection of civilians, and proposes model language to address those, including verbatim examples of Security Council agreed language on each identified theme and sub-theme. This site offers a user-friendly interface to search into the addendum of the Aide-Memoire, entirely populated with official Security Council language on the protection of civilians in armed conflict.</p><p>The physical version of the Aide Memoire, having evolved from a 7-page document (<a href='https://www.un.org/en/ga/search/view_doc.asp?symbol=S/PRST/2002/6' target='_blank'>S/PRST/2002/6</a>) to several hundred pages of references (most recent reference to be added), is in itself a testament to the relevance of the protection of civilians to the Security Council, and the importance the Security Council gives to this issue, which it called “one of the core issues on its agenda” (<a href='https://undocs.org/S/PRST/2015/23' target='_blank'>S/PRST/2015/23</a>).</p><p>[pocam-general:themes-list]</p>" |
      | body:format          | full_html          |
    When I follow "Themes"
    Then I should see "Themes"
