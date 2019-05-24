FROM unocha/unified-builder:7.2.18-r0-201905-08 as builder
COPY ./html /srv/www/html
WORKDIR /srv/www/html/sites/all/themes/custom/ocha_basic
RUN npm install && \
      npm run gulp build && \
      rm -rf ./node_modules

FROM unocha/php7-k8s:7.2.18-r0-201905-08-NR
ENV NGINX_SERVERNAME=poc-aide-memoire.unocha.org
ENV PHP_MEMORY_LIMIT=256M
ENV PHP_MAX_CHILDREN=16
COPY --from=builder /srv/www/html /srv/www/html
