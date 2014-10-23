<?php

/**
 * @file
 * This is the router for the services.
 */

/**
 * Create a menu handler for routes.
 */
function initialise_menu_handler() {
  // Here we need a clean URL - no query parameters!
  $incoming_route = check_plain($_GET['q']);
  $routes = router_definition();

  if (!$routes[$incoming_route]) {
    render_not_found();
  }

  // Should the service have a 'file' defined, let's include it so that we
  // can leverage all the functionality it has defined.
  if (!empty($routes[$incoming_route]['file'])) {
    $file = $routes[$incoming_route]['file'];
    require_once "services/$file.inc";
  }

  // Invoke the service callback.
  call_user_func_array($routes[$incoming_route]['callback'], $routes[$incoming_route]['callback arguments']);
}

/**
 * Define all the available routes and options.
 *
 * @return array
 *   Routes keyed to the path they should reside on and options.
 */
function router_definition() {
  return array(
    'hello/world' => array(
      'file' => 'example_service',
      'callback' => 'example_hello_test',
      'callback arguments' => array($_GET['example']),
    ),
  );
}
