<?php

/**
 * @file
 * Database functions.
 */

define('DEFAULT_TIME_FORMAT', 'Y-m-d H:i:sP');

/**
 * Insert node view.
 *
 * @param int $nid
 *   The viewed node.
 * @param int $uid
 *   The user who viewed node.
 * @param int $uip
 *   The user ip who viewed node.
 *
 * @return bool|int
 *   Count written records or FALSE.
 */
function nodeviewcount_db_insert_node_view($nid, $uid, $uip) {
  $dateTime = new DateTime('NOW');
  $dateTime->setTimeZone(new DateTimeZone(date_default_timezone_get()));
  $fields = array(
    'nid' => $nid,
    'uid' => $uid,
    'datetime' => $dateTime->format(DEFAULT_TIME_FORMAT),
    'uip' => $uip,
  );
  return drupal_write_record('nodeviewcount', $fields);
}

/**
 * Count node views.
 * Note: I'm not sure this is ever used.
 *
 * @param object $node
 *   Node.
 * @param object $user
 *   User.
 * @param bool $distinct_users
 *   Distinct user or not.
 *
 * @return int
 *   Count of node views.
 */
function nodeviewcount_db_count_node_views($node, $user = NULL, $distinct_users = FALSE) {
  $query = db_select('nodeviewcount', 'nvc')->condition('nid', $node->nid);

  if ($user) {
    $query->pcondition('uid', $user->uid);
  }
  if ($distinct_users) {
    $query->count('DISTINCT uid');
  }
  else {
    $query->count();
  }
  $result = $query->execute();

  return $result;
}