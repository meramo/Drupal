<?php

/**
 * Wheels view callback.
 */
function wheels_view($wheels) {
  drupal_set_title(entity_label('wheels', $wheels));
  return entity_view('wheels', array(entity_id('wheels', $wheels) => $wheels), 'full');
}
