<?php

/**
 * Page callback for the 'user/%/magic tab'.
 */
function menu_magic_user_tab($wildcard) {
  if (is_numeric($wildcard) && ($account = user_load($wildcard))) {
    return array(
      '#type' => 'markup',
      '#markup' => t("%username is awesome man.",
        array('%username' => $account->name)),
    );
  }
  else {
    return drupal_not_found();
  }
}
