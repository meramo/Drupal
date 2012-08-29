<?php

/**
 * Build treesaver_settings_form form.
 *
 *
 */
function treesaver_settings_form($form_state) {
  $form = array();

  $form['treesaver_always_add_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include Treesaver JavaScript always'),
    '#default_value' => variable_get('treesaver_always_add_js'),
  );

  return system_settings_form($form);
}