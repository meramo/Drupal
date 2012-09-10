<?php

/**
 * System settings form for blacklisting passwords.
 */
function pass_alter_passwords_form($form, &$form_state) {
  $form['pass_alter_badpasswords'] = array(
    '#type' => 'textfield',
    '#title' => t('Bad Passwords'),
    '#default_value' => variable_get('pass_alter_badpasswords'),
    '#description' => t('Enter a list of bad passes here'),
    );

  return(system_settings_form($form)); // Does variable_set()
}
