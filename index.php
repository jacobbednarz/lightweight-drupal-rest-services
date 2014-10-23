<?php

/**
 * @file
 * Lightweight REST index for building fast services.
 */

define('DRUPAL_ROOT', dirname(getcwd()));

// Get Drupal to a state where we have database connectivity.
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);

// Load our required base functionality.
require_once 'includes/core.inc';

register_api_globals();

// Boot the menu router.
require_once 'includes/route.inc';
initialise_menu_handler();
