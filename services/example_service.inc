<?php

/**
 * @file
 * This is an example service.
 */

/**
 * Fire a menu callback (example in this case).
 */
function example_hello_test($args) {
  global $api_static;

  $result = db_select('items', 'i')
    ->fields('i', array('field1', 'field2'))
    ->range(0, 10)
    ->execute()
    ->fetchAll();

  render_json(200, array('items' => $result));
}
