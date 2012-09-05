<?php

/**
 * Returns a renderable form array for a given form ID.
 */
function form_fun_cake_page() {
  return drupal_get_form('form_fun_cake');
}

function form_fun_cake($form, &$form_state) {
  $form = array();

  $form['choice'] = array(
    '#type' => 'select',
    '#title' => t('Cake or pie?'),
    '#description' => t('Would you like cake or pie?'),
    '#options' => array(
      'cake' => t('Cake please'),
      'pie' => t('Pie I guess'),
    ),
    '#default_value' => 'cake',
    '#required' => TRUE,
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  $form['buttons']['unsure'] = array(
    '#type' => 'submit',
    '#value' => t('Equivocate'),
    '#submit' => array('form_fun_cake_unsure'),
    '#validate' => array(),
  );

  return $form;
}

function form_fun_cake_validate(&$form, &$form_state) {
  if ($form_state['values']['choice'] == 'cake') {
    form_set_error('choice', t('We are out of cake'));
  }
}

function form_fun_cake_submit(&$form, &$form_state) {
  dsm($form_state['values']);
  $form_state['redirect'] = '';
}

function form_fun_cake_unsure(&$form, &$form_state) {
  drupal_set_message(t('Make up your mind'), 'warning');

}


