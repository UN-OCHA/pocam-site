<?php

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Gherkin\Node\PyStringNode;
use Behat\Gherkin\Node\TableNode;
use Behat\Behat\Tester\Exception\PendingException;
use Behat\Mink\Driver\Selenium2Driver;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Behat\Hook\Scope\AfterStepScope;
use Behat\Behat\Hook\Scope\BeforeStepScope;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  public $screenshots;
  public $lastStep = 'none';

  /**
   * Initializes context.
   *
   * Every scenario gets its own context instance.
   * You can also pass arbitrary arguments to the
   * context constructor through behat.yml.
   */
  public function __construct($screenshots = '') {
    $this->screenshots = $screenshots ? $screenshots : '/tmp';
  }

  /**
   * @Then /^I wait for the ajax response$/
   */
  public function iWaitForTheAjaxResponse()
  {
    $this->getSession()->wait(5000, '(0 === jQuery.active)');
  }

  /**
   * @When /^I set the chosen element "([^"]*)" to "([^"]*)"$/
   */
  public function iSetChosenElement($locator, $value) {
    $session = $this->getSession();
    $element = $session->getPage()->find('css', $locator);

    if (empty($element)) {
      throw new ExpectationException(t('No such select element @locator ', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $element_id = str_replace('-', '_', $element->getAttribute('id')) . '_chosen';

    $element = $session->getPage()->find('xpath', "//div[@id='{$element_id}']");
    if ($element->hasClass('chosen-container-single')) {
      // This is a single select element.
      $element = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/a[@class='chosen-single']");
      $element->click();
    }
    elseif ($element->hasClass('chosen-container-multi')) {
      // This is a multi select element.
      $element = $session->getPage()->find('xpath', "//div[@id='{$element_id}']/ul[@class='chosen-choices']/li[@class='search-field']/input");
      $element->click();
    }

    $selector = "//div[@id='{$element_id}']/div[@class='chosen-drop']/ul[@class='chosen-results']/li[contains(., '{$value}')]";
    $element = $session->getPage()->find('xpath', $selector);

    if (empty($element)) {
      throw new ExpectationException(t('No such option @value in @locator ', array(
        '@value' => $value,
        '@locator' => $locator,
      )), $session);
    }

    $element->click();
  }

  /**
   * Creates one or more terms on an existing vocabulary.
   *
   * Provide term data in the following format:
   *
   * | name  | parent | description | weight | taxonomy_field_image |
   * | Snook | Fish   | Marine fish | 10     | snook-123.jpg        |
   * | ...   | ...    | ...         | ...    | ...                  |
   *
   * Only the 'name' field is required.
   *
   * @Given :vocabulary with terms:
   */
  public function createTerms($vocabulary, TableNode $termsTable) {
    foreach ($termsTable->getHash() as $termsHash) {
      $term = (object) $termsHash;
      if (isset($term->parent)) {
        $term->parent = trim($term->parent);
      }
      $term->vocabulary_machine_name = $vocabulary;
      $this->_termCreateWithParent($term);
    }
  }

  /**
   * Create a term.
   *
   * @return object
   *   The created term.
   */
  public function _termCreateWithParent($term) {
    if (!empty($term->parent)) {
      if (!$parent = $this->_getExistingTerm($term->parent, $term->vocabulary_machine_name)) {
        $parent = $this->termCreate((object) array(
          'vocabulary_machine_name' => $term->vocabulary_machine_name,
          'name' => $term->parent,
        ));
      }
      $term->parent = $parent->tid;
    }
    $this->dispatchHooks('BeforeTermCreateScope', $term);
    $this->parseEntityFields('taxonomy_term', $term);
    $saved = $this->getDriver()->createTerm($term);
    $this->dispatchHooks('AfterTermCreateScope', $saved);
    $this->terms[] = $saved;
    return $saved;
  }

  /**
   * Returns a testing term.
   *
   * @param string $name
   *   The term name to check.
   * @param string $vid
   *   The term vocabulary ID.
   *
   * @return \stdClass|null
   *   The term object or NULL if no term has been created yet.
   */
  protected function _getExistingTerm($name, $vid) {
    foreach ($this->terms as $term) {
      if ($term->name === $name && $term->vocabulary_machine_name === $vid) {
        return $term;
      }
    }
    return NULL;
  }

  /**
   * Creates content of a given type provided in the form:
   *
   * @Given list of extracts:
   */
  public function createExtracts(TableNode $nodesTable) {
    foreach ($nodesTable->getHash() as $nodeHash) {
      $node = (object) $nodeHash;
      $node->type = 'pocam_extract';
      $this->nodeCreate($node);
    }
  }

  /**
   * @BeforeStep
   */
  public function trackLastStep(BeforeStepScope $scope) {
    $this->lastStep = $scope->getStep();
  }

  /**
   * @AfterStep
   */
  public function takeScreenShotAfterFailedStep(afterStepScope $scope) {
    if (99 === $scope->getTestResult()->getResultCode()) {
      $driver = $this->getSession()->getDriver();
      if (!($driver instanceof Selenium2Driver)) {
        return;
      }
      $filename = preg_replace('/[^a-zA-Z0-9]/', '-', $this->lastStep->getText());
      file_put_contents($this->screenshots . '/' . $filename . '.png', $this->getSession()->getDriver()->getScreenshot());
    }
  }

  /**
   * @When I scroll to the :selector element
   */
  public function scrollToElement($selector) {
    $this->getSession()->executeScript('document.querySelector("' . $selector . '").scrollIntoView()');
  }

  /**
   * @Given I click the :arg1 element
   */
  public function iClickTheElement($selector) {
    $page = $this->getSession()->getPage();
    $element = $page->find('css', $selector);

    if (empty($element)) {
      throw new Exception("No html element found for the selector ('$selector')");
    }

    $element->click();
  }

  /**
   * @Given I am viewing a :arg1 content with the alias :arg2:
   */
  public function iAmViewingAContentWithTheAlias($type, $alias, TableNode $fields) {
    $node = (object) array(
      'type' => $type,
    );

    foreach ($fields->getRowsHash() as $field => $value) {
      $node->{$field} = $value;
    }

    $saved = $this->nodeCreate($node);

    // Save path.
    $path = array(
      'source' => 'node/' . $saved->nid,
      'alias' => $alias,
    );
    path_save($path);

    // Set internal browser on the node.
    $this->getSession()->visit($this->locatePath('/node/' . $saved->nid));
  }

  /**
   * @Given I am viewing a :arg1 content with the alias :arg2 and menu :menu:
   */
  public function iAmViewingAContentWithTheAliasAndMenu($type, $alias, $menu, TableNode $fields) {
    $node = (object) array(
      'type' => $type,
    );

    foreach ($fields->getRowsHash() as $field => $value) {
      $node->{$field} = $value;
    }

    $saved = $this->nodeCreate($node);

    // Save path.
    $path = array(
      'source' => 'node/' . $saved->nid,
      'alias' => $alias,
    );
    path_save($path);

    // Save menu.
    if (!empty($menu)) {
      list($menu_name, $link_title) = explode(':', $menu);
      $item = array(
        'menu_name' => $menu_name,
        'link_path' => drupal_get_normal_path($alias),
        'link_title' => $link_title,
        'weight' => 0,
        'customized' => 1,
      );
      menu_link_save($item);
      menu_cache_clear_all();
    }

    // Set internal browser on the node.
    $this->getSession()->visit($this->locatePath('/node/' . $saved->nid));
  }
}
