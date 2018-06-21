cd ../html
export PHP_OPTIONS="-d sendmail_path=`which true`"
../behat/bin/drush site-install pocam --debug --root=$TRAVIS_BUILD_DIR/html --db-url=sqlite://sites/all/test.db --sites-subdir=8888.localhost --account-pass=admin -y
