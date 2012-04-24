<?php

/**
 * Generates the wheels type editing form.
 */
function wheels_type_form($form, &$form_state, $wheels_type, $op = 'edit') {

  if ($op == 'clone') {
    $wheels_type->label .= ' (cloned)';
    $wheels_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $wheels_type->label,
    '#description' => t('The human-readable name of this wheels type.'),
    '#required' => TRUE,
    '#size' => 30,
  );

  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($wheels_type->type) ? $wheels_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $wheels_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'wheels_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this wheels type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($wheels_type->description) ? $wheels_type->description : '',
    '#description' => t('Description about the wheels type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save wheels type'),
    '#weight' => 40,
  );

  if (!$wheels_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete wheels type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('wheels_type_form_submit_delete')
    );
  }
  return $form;
}

/**
 * Submit handler for creating/editing wheels_type.
 */
function wheels_type_form_submit(&$form, &$form_state) {
  $wheels_type = entity_ui_form_submit_build_entity($form, $form_state);
  // Save and go back.
  wheels_type_save($wheels_type);

  // Redirect user back to list of wheels types.
  $form_state['redirect'] = 'admin/structure/wheels-types';
}

function wheels_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/wheels-types/' . $form_state['wheels_type']->type . '/delete';
}

/**
 * Wheels type delete form.
 */
function wheels_type_form_delete_confirm($form, &$form_state, $wheels_type) {
  $form_state['wheels_type'] = $wheels_type;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['wheels_type_id'] = array('#type' => 'value', '#value' => entity_id('wheels_type' ,$wheels_type));
  return confirm_form($form,
    t('Are you sure you want to delete wheels type %title?', array('%title' => entity_label('wheels_type', $wheels_type))),
    'wheels/' . entity_id('wheels_type' ,$wheels_type),
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Wheels type delete form submit handler.
 */
function wheels_type_form_delete_confirm_submit($form, &$form_state) {
  $wheels_type = $form_state['wheels_type'];
  wheels_type_delete($wheels_type);

  watchdog('wheels_type', '@type: deleted %title.', array('@type' => $wheels_type->type, '%title' => $wheels_type->label));
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $wheels_type->type, '%title' => $wheels_type->label)));

  $form_state['redirect'] = 'admin/structure/wheels-types';
}

/**
 * Page to select wheels Type to add new wheels.
 */
function wheels_admin_add_page() {
  $items = array();
  foreach (wheels_types() as $wheels_type_key => $wheels_type) {
    $items[] = l(entity_label('wheels_type', $wheels_type), 'wheels/add/' . $wheels_type_key);
  }
  return array('list' => array('#theme' => 'item_list', '#items' => $items, '#title' => t('Select type of wheels to create.')));
}

/**
 * Add new wheels page callback.
 */
function wheels_add($type) {
  $wheels_type = wheels_types($type);

  $wheels = entity_create('wheels', array('type' => $type));
  drupal_set_title(t('Create @name', array('@name' => entity_label('wheels_type', $wheels_type))));

  $output = drupal_get_form('wheels_form', $wheels);

  return $output;
}

/**
 * Wheels Form.
 */
function wheels_form($form, &$form_state, $wheels) {
  $form_state['wheels'] = $wheels;

  $form['title'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('Name'),
    '#default_value' => $wheels->title,
  );

  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Description'),
    '#default_value' => $wheels->description,
  );

  $form['uid'] = array(
    '#type' => 'value',
    '#value' => $wheels->uid,
  );

  field_attach_form('wheels', $wheels, $form, $form_state);

  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions'] = array(
    '#weight' => 100,
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save wheels'),
    '#submit' => $submit + array('wheels_form_submit'),
  );

  // Show Delete button if we edit wheels.
  $wheels_id = entity_id('wheels' ,$wheels);
  if (!empty($wheels_id) && wheels_access('edit', $wheels)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('wheels_form_submit_delete'),
    );
  }

  $form['#validate'][] = 'wheels_form_validate';

  return $form;
}

function wheels_form_validate($form, &$form_state) {

}

/**
 * Wheels submit handler.
 */
function wheels_form_submit($form, &$form_state) {
  $wheels = $form_state['wheels'];

  entity_form_submit_build_entity('wheels', $wheels, $form, $form_state);

  wheels_save($wheels);

  $wheels_uri = entity_uri('wheels', $wheels);

  $form_state['redirect'] = $wheels_uri['path'];

  drupal_set_message(t('Wheels %title saved.', array('%title' => entity_label('wheels', $wheels))));
}

function wheels_form_submit_delete($form, &$form_state) {
  $wheels = $form_state['wheels'];
  $wheels_uri = entity_uri('wheels', $wheels);
  $form_state['redirect'] = $wheels_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 */
function wheels_delete_form($form, &$form_state, $wheels) {
  $form_state['wheels'] = $wheels;
  // Always provide entity id in the same form key as in the entity edit form.
  $form['wheels_type_id'] = array('#type' => 'value', '#value' => entity_id('wheels' ,$wheels));
  $wheels_uri = entity_uri('wheels', $wheels);
  return confirm_form($form,
    t('Are you sure you want to delete wheels %title?', array('%title' => entity_label('wheels', $wheels))),
    $wheels_uri['path'],
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete form submit handler.
 */
function wheels_delete_form_submit($form, &$form_state) {
  $wheels = $form_state['wheels'];
  wheels_delete($wheels);

  drupal_set_message(t('Wheels %title deleted.', array('%title' => entity_label('wheels', $wheels))));

  $form_state['redirect'] = '<front>';
}
