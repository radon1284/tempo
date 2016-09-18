angular.module('app.routes', [])

.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider
    
  

      .state('menu.home', {
    url: '/home',
    views: {
      'side-menu21': {
        templateUrl: 'templates/home.html',
        controller: 'homeCtrl'
      }
    }
  })

  .state('menu.aircon', {
    url: '/aircon',
    views: {
      'side-menu21': {
        templateUrl: 'templates/aircon.html',
        controller: 'airconCtrl'
      }
    }
  })

  .state('menu', {
    url: '/side-menu21',
    templateUrl: 'templates/menu.html',
    controller: 'menuCtrl'
  })

  .state('menu.body', {
    url: '/body',
    views: {
      'side-menu21': {
        templateUrl: 'templates/body.html',
        controller: 'bodyCtrl'
      }
    }
  })

  .state('menu.remoteControl', {
    url: '/remote',
    views: {
      'side-menu21': {
        templateUrl: 'templates/remoteControl.html',
        controller: 'remoteControlCtrl'
      }
    }
  })

$urlRouterProvider.otherwise('/side-menu21/home')

  

});