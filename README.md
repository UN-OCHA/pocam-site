# POCAM - Aide Memoire

## Behat

```
cd behat
composer install
```

### Terminal 1

```
wget -N https://chromedriver.storage.googleapis.com/2.40/chromedriver_linux64.zip
unzip chromedriver_linux64.zip
./chromedriver
```

### Terminal 2

```
cd html
../behat/bin/drush site-install pocam --debug --root=$PWD --db-url=sqlite://sites/all/test.db --sites-subdir=8888.localhost --account-pass=admin -y

cd sites/8888.localhost/
../../../behat/bin/drush runserver 8888
```

### Terminal 3

```
cd behat
bin/behat --config behat.local.yml --format pretty
```
