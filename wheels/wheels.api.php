<?php
/**
 * @file
 * Hooks provided by this module.
 */


/**
 * Acts on wheels being loaded from the database.
 *
 * This hook is invoked during $wheels loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of $wheels entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_wheels_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a $wheels is inserted.
 *
 * This hook is invoked after the $wheels is inserted into the database.
 *
 * @param Wheels $wheels
 *   The $wheels that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_wheels_insert(Wheels $wheels) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('wheels', $wheels),
      'extra' => print_r($wheels, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a $wheels being inserted or updated.
 *
 * This hook is invoked before the $wheels is saved to the database.
 *
 * @param Wheels $wheels
 *   The $wheels that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_wheels_presave(Wheels $wheels) {
  $wheels->name = 'foo';
}

/**
 * Responds to a $wheels being updated.
 *
 * This hook is invoked after the $wheels has been updated in the database.
 *
 * @param Wheels $wheels
 *   The $wheels that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_wheels_update(Wheels $wheels) {
  db_update('mytable')
    ->fields(array('extra' => print_r($wheels, TRUE)))
    ->condition('id', entity_id('wheels', $wheels))
    ->execute();
}

/**
 * Responds to $wheels deletion.
 *
 * This hook is invoked after the $wheels has been removed from the database.
 *
 * @param Wheels $wheels
 *   The $wheels that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_wheels_delete(Wheels $wheels) {
  db_delete('mytable')
    ->condition('pid', entity_id('wheels', $wheels))
    ->execute();
}

/**
 * Act on a wheels that is being assembled before rendering.
 *
 * @param $wheels
 *   The wheels entity.
 * @param $view_mode
 *   The view mode the wheels is rendered in.
 * @param $langcode
 *   The language code used for rendering.
 *
 * The module may add elements to $wheels->content prior to rendering. The
 * structure of $wheels->content is a renderable array as expected by
 * drupal_render().
 *
 * @see hook_entity_prepare_view()
 * @see hook_entity_view()
 */
function hook_wheels_view($wheels, $view_mode, $langcode) {
  $wheels->content['my_additional_field'] = array(
    '#markup' => $additional_field,
    '#weight' => 10,
    '#theme' => 'mymodule_my_additional_field',
  );
}

/**
 * Alter the results of entity_view() for wheels.
 *
 * @param $build
 *   A renderable array representing the wheels content.
 *
 * This hook is called after the content has been assembled in a structured
 * array and may be used for doing processing which requires that the complete
 * wheels content structure has been built.
 *
 * If the module wishes to act on the rendered HTML of the wheels rather than
 * the structured content array, it may use this hook to add a #post_render
 * callback. Alternatively, it could also implement hook_preprocess_wheels().
 * See drupal_render() and theme() documentation respectively for details.
 *
 * @see hook_entity_view_alter()
 */
function hook_wheels_view_alter($build) {
  if ($build['#view_mode'] == 'full' && isset($build['an_additional_field'])) {
    // Change its weight.
    $build['an_additional_field']['#weight'] = -10;

    // Add a #post_render callback to act on the rendered HTML of the entity.
    $build['#post_render'][] = 'my_module_post_render';
  }
}

/**
 * Acts on wheels_type being loaded from the database.
 *
 * This hook is invoked during wheels_type loading, which is handled by
 * entity_load(), via the EntityCRUDController.
 *
 * @param array $entities
 *   An array of wheels_type entities being loaded, keyed by id.
 *
 * @see hook_entity_load()
 */
function hook_wheels_type_load(array $entities) {
  $result = db_query('SELECT pid, foo FROM {mytable} WHERE pid IN(:ids)', array(':ids' => array_keys($entities)));
  foreach ($result as $record) {
    $entities[$record->pid]->foo = $record->foo;
  }
}

/**
 * Responds when a wheels_type is inserted.
 *
 * This hook is invoked after the wheels_type is inserted into the database.
 *
 * @param WheelsType $wheels_type
 *   The wheels_type that is being inserted.
 *
 * @see hook_entity_insert()
 */
function hook_wheels_type_insert(WheelsType $wheels_type) {
  db_insert('mytable')
    ->fields(array(
      'id' => entity_id('wheels_type', $wheels_type),
      'extra' => print_r($wheels_type, TRUE),
    ))
    ->execute();
}

/**
 * Acts on a wheels_type being inserted or updated.
 *
 * This hook is invoked before the wheels_type is saved to the database.
 *
 * @param WheelsType $wheels_type
 *   The wheels_type that is being inserted or updated.
 *
 * @see hook_entity_presave()
 */
function hook_wheels_type_presave(WheelsType $wheels_type) {
  $wheels_type->name = 'foo';
}

/**
 * Responds to a wheels_type being updated.
 *
 * This hook is invoked after the wheels_type has been updated in the database.
 *
 * @param WheelsType $wheels_type
 *   The wheels_type that is being updated.
 *
 * @see hook_entity_update()
 */
function hook_wheels_type_update(WheelsType $wheels_type) {
  db_update('mytable')
    ->fields(array('extra' => print_r($wheels_type, TRUE)))
    ->condition('id', entity_id('wheels_type', $wheels_type))
    ->execute();
}

/**
 * Responds to wheels_type deletion.
 *
 * This hook is invoked after the wheels_type has been removed from the database.
 *
 * @param WheelsType $wheels_type
 *   The wheels_type that is being deleted.
 *
 * @see hook_entity_delete()
 */
function hook_wheels_type_delete(WheelsType $wheels_type) {
  db_delete('mytable')
    ->condition('pid', entity_id('wheels_type', $wheels_type))
    ->execute();
}

/**
 * Define default wheels_type configurations.
 *
 * @return
 *   An array of default wheels_type, keyed by machine names.
 *
 * @see hook_default_wheels_type_alter()
 */
function hook_default_wheels_type() {
  $defaults['main'] = entity_create('wheels_type', array(
    // …
  ));
  return $defaults;
}

/**
 * Alter default wheels_type configurations.
 *
 * @param array $defaults
 *   An array of default wheels_type, keyed by machine names.
 *
 * @see hook_default_wheels_type()
 */
function hook_default_wheels_type_alter(array &$defaults) {
  $defaults['main']->name = 'custom name';
}
