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

  public function create($type = '') {
    return (object) array(
      'aid' => '',
      'type' => $type,
      'title' => '',
    );
  }

  public function save($artwork) {
    $transaction = db_transaction(); // Transactions allow multiple database queries to either all succeed or all fail together
      try {
        global $user;
        // Determine if we will be inserting a new artwork.
        $artwork->is_new = empty($artwork->aid);
        // Set the timestamp fields.
        if (empty($artwork->created)) {
          $artwork->created = REQUEST_TIME;
        }
        $artwork->changed = REQUEST_TIME;
        $artwork->revision_timestamp = REQUEST_TIME;
        $update_artwork = TRUE;
        // Give modules the opportunity to prepare field data for saving.
        field_attach_presave('artwork', $artwork);
        if (!$artwork->is_new && !empty($artwork->revision) && $artwork->vid) {
          $artwork->old_vid = $artwork->vid;
          unset($artwork->vid);
        }
        // If this is a new artwork...
        if ($artwork->is_new) {
          // Save the new artwork.
          drupal_write_record('artwork', $artwork);
        }
        // Save the initial revision.
          $this->saveRevision($artwork, $user->uid);
          $op = 'insert';
        }
        else {
        // Save the updated artwork.
        drupal_write_record('artwork', $artwork, 'aid');
        if (!empty($artwork->revision)) {
          $this->saveRevision($artwork, $user->uid);
        }
        else {
          $this->saveRevision($artwork, $user->uid, TRUE);
          $update_artwork = FALSE;
        }
        $op = 'update';
        }
        // If the revision ID is new or updated, save it to the artwork.
        if ($update_artwork) {
          db_update('artwork')
            ->fields(array('vid' => $artwork->vid))
            ->condition('aid', $artwork->aid)
            ->execute();
        }
        // Save fields.
        $function = 'field_attach_' . $op;
        $function('artwork', $artwork);
        module_invoke_all('entity_' . $op, $artwork, 'artwork');
        // Clear internal properties.
        unset($artwork->is_new);
        // Ignore slave server temporarily to give time for the saved
        // order to be propagated to the slave.
        db_ignore_slave();

    return $artwork;
  }

    catch (Exception $e) {
      $transaction->rollback();
        watchdog_exception('artwork', $e, NULL, WATCHDOG_ERROR);

    return FALSE;
    }

}