<?php
/**
 * Define artwork controller class.
 */

class ArtworkController extends DrupalDefaultEntityController {
  function artwork_load($aid = NULL, $vid = NULL, $reset = FALSE) {
      $aids = (isset($aid) ? array($aid) : array());
      $conditions = (isset($vid) ? array('vid' => $vid) : array());
      $artwork = artwork_load_multiple($aids, $conditions, $reset);
      return $artwork ? reset($artwork) : FALSE;
 }
    function artwork_load_multiple($aids = array(), $conditions = array(),
    $reset = FALSE) {
      return entity_load('artwork', $aids, $conditions, $reset);
    }
  }