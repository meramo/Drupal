<?php

function menu_magic_extra($wildcard) {
  $content = array(
    '#type' => 'markup',
    '#markup' => '<p>'.t('The wildcard contains "%wildcard".',
      array('%wildcard' => $wildcard)).'</p>',
  );
  return $content;
}
