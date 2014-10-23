<?php

/**
 * @file
 * Core service helpers included for all requests.
 */

/**
 * Create and register globals which will be reused.
 */
function register_api_globals() {
  global $api_static;
  $api_static['version'] = get_api_version();
  $api_static['accept_content_type'] = get_accept_content_type();
}

/**
 * Fetch the requested version of the API.
 *
 * @return string
 *   The version of the API to use.
 */
function get_api_version() {
  $version_parts = preg_match('/(v[0-9]+)/', $_SERVER['HTTP_ACCEPT'], $matches);
  return (!empty($matches[0])) ? $matches[0] : 'v1';
}

/**
 * Pull out the requested content type.
 *
 * @return string
 *   The content type that was requested.
 */
function get_accept_content_type() {
  $content_type = preg_match('/(?<=[0-9{0,2}]\+)(json|xml)/', $_SERVER['HTTP_ACCEPT'], $matches);
  return (!empty($matches[0])) ? $matches[0] : 'json';
}

/**
 * Throw a not found error.
 *
 * This method takes care of not only delivering the 'not found' message but it
 * also handles returning the content type (JSON, XML, HTML).
 */
function render_not_found() {
  global $api_static;

  if ($api_static['accept_content_type'] == 'xml') {
    render_xml_404();
  }
  else {
    render_json_404();
  }
}

/**
 * Render a 404 - JSON style.
 */
function render_json_404() {
  render_json(404);
}

/**
 * Render a 404 for XML responses.
 *
 * This should really be more like the JSON equivalent.
 */
function render_xml_404() {
  header('Content-Type: application/xml');
  echo '<?xml version="1.0"?><message>Not found</message>';
  exit;
}

/**
 * Render a JSON response.
 *
 * @param int $status_code
 *   The HTTP status code to send.
 * @param array $data
 *   Array of information to render within the response.
 */
function render_json($status_code, $data = array()) {
  header('Content-Type: application/json');

  $status_map = array(
    200 => 'OK',
    301 => 'Moved permanently',
    304 => 'Not modified',
    400 => 'Bad request',
    401 => 'Unauthorized',
    401 => 'Forbidden',
    404 => 'Not found',
    405 => 'Method not allowed',
    500 => 'Server error',
    503 => 'Service unavailable',
  );

  header($_SERVER['SERVER_PROTOCOL'] . " {$status_code} {$status_map[$status_code]}");
  $base_data = array(
    'timestamp' => date('c'),
    'message' => $status_map[$status_code],
  );

  $output_data = array_merge($base_data, $data);

  echo json_encode($output_data);
  exit;
}
