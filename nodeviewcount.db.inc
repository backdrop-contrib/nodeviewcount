<?php
/**
 * @file
 * Database functions.
 */

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
  $date_format = config_get('nodeviewcount.settings', 'date_format');

  $dateTime = new DateTime(REQUEST_TIME);
  $dateTime->setTimeZone(new DateTimeZone(date_default_timezone_get()));
  $fields = array(
    'nid' => $nid,
    'uid' => $uid,
    'datetime' => $dateTime->format('U'),
    'uip' => $uip,
  );

  return backdrop_write_record('nodeviewcount', $fields);
}

/**
 * Count node views.
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
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'nodeviewcount');
  $query->propertyCondition('nid', $node->nid);
  if ($user) {
    $query->propertyCondition('uid', $user->uid);
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
