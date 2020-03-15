FROM unocha/unified-builder:7.2.27-r0-202003-02 as builder
COPY ./html /srv/www/html
WORKDIR /srv/www/html/sites/all/themes/custom/ocha_basic
RUN npm install && \
      npm run gulp build && \
      rm -rf ./node_modules

FROM unocha/php7-k8s:7.2.27-r0-202003-03-NR

ARG VCS_REF
ARG VCS_URL
ARG BUILD_DATE
ARG GITHUB_ACTOR
ARG GITHUB_REPOSITORY
ARG GITHUB_SHA
ARG GITHUB_REF

ENV  NGINX_SERVERNAME=poc-aide-memoire.unocha.org
ENV  PHP_ENVIRONMENT=production
ENV  PHP_MEMORY_LIMIT=256M
ENV  PHP_MAX_CHILDREN=32
ENV  GIT_BLAME=$GITHUB_ACTOR
ENV  GIT_REPO=$GITHUB_REPOSITORY
ENV  GIT_SHA=$GITHUB_SHA
ENV  GIT_REF=$GITHUB_REF
LABEL info.humanitarianresponse.build.date=$BUILD_DATE \
      info.humanitarianresponse.build.vcs-url=$VCS_URL \
      info.humanitarianresponse.build.vcs-ref=$VCS_REF

COPY ./html /srv/www/html
COPY ./composer.* /srv/www/
