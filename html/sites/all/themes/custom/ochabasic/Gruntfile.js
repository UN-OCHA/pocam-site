module.exports = function(grunt) {

  grunt.initConfig({
    pkg: grunt.file.readJSON('package.json'),

    sass_import: {
      options: {},
      dist: {
        files: {
          'assets/css/styles.scss': ['assets/sass/variables/*.scss', 'assets/sass/mixins/*.scss', 'assets/sass/base/*.scss', 'assets/sass/components/**/*.scss'],
        }
      }
    },
    sass: {
      dist: {
        files: {
          'assets/css/styles.css': 'assets/css/styles.scss'
        }
      }
    },
    watch: {
      sass: {
        files: ['assets/sass/**/*.scss'],
        tasks: ['sass_import', 'sass', 'autoprefixer'],
        options: {
          spawn: false,
        }
      }
    },
    autoprefixer: {
      dist: {
        files: {
          'assets/css/styles.css': 'assets/css/styles.css'
        },
        options: {
          browsers: ['last 2 versions', 'iOS 8']
        }
      }
    },
    cssmin: {
      target: {
        files: {
          'assets/css/styles.css': 'assets/css/styles.css',
          'critical-css/anonymous/urls/front.css': 'critical-css/anonymous/urls/front.css',
          'critical-css/anonymous/urls/extracts.css': 'critical-css/anonymous/urls/extracts.css',
          'critical-css/anonymous/type/pocam_extract.css': 'critical-css/anonymous/type/pocam_extract.css'
        }
      }
    },

    modernizr: {
      dist: {
        crawl: false,
        dest: 'assets/js/modernizr-output.js',
        tests: [
          'flexbox'
        ],
        options: [
          'setClasses'
        ],
        uglify: true
      }
    },

    criticalcss: {
      options: {
        filename: 'assets/css/styles.css',
        width: 1200,
        height: 900,
        buffer: 1200*1200
      },
      home: {
        options: {
          url: 'http://aide.docksal',
          outputfile: 'critical-css/anonymous/urls/front.css',
        }
      },
      extract: {
        options: {
          url: 'http://aide.docksal/extracts',
          outputfile: 'critical-css/anonymous/urls/extracts.css',
        }
      },
      page: {
        options: {
          url: 'http://aide.docksal/node/1',
          outputfile: 'critical-css/anonymous/type/pocam_extract.css',
        }
      },
    }
  });

  require('load-grunt-tasks')(grunt);
  grunt.loadNpmTasks("grunt-modernizr"); //not picked up by load-grunt-tasks

  grunt.registerTask('default', ['sass_import','sass', 'autoprefixer', 'cssmin', 'modernizr']);
  grunt.registerTask('critical', ['criticalcss', 'cssmin', 'modernizr']);

};
