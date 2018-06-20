cp scripts/sites.php ../html/sites/
cd ../html
export PHP_OPTIONS="-d sendmail_path=`which true`"
ls $TRAVIS_BUILD_DIR/html/profiles
ls profiles
echo $PWD
../behat/bin/drush site-install pocam --debug --root=$TRAVIS_BUILD_DIR/html --db-url=sqlite://sites/all/test.db --sites-subdir=8888.localhost --account-pass=admin -y
../../../behat/bin/drush cc all
../../../behat/bin/drush fra -y
../../../behat/bin/drush search-api-index
