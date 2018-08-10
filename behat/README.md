# Behat instructions

## Travis

See root .travis.yml file

## Locally

### Site install

```
cd ../html
rm -f sites/all/test.db
export PHP_OPTIONS="-d sendmail_path=`which true`"
../behat/bin/drush site-install pocam --root=$PWD --db-url=sqlite://sites/all/test.db --sites-subdir=8888.127.0.0.1 --account-pass=admin -y
```

### Webserver

```
cd ../html/sites/8888.127.0.0.1
../../../behat/bin/drush runserver 8888
```

### Chromedriver

```
wget -N https://chromedriver.storage.googleapis.com/2.36/chromedriver_linux64.zip
unzip chromedriver_linux64.zip
./chromedriver
```

### Behat

```
bin/behat --config behat.local.yml --format pretty
```
