<?php
/**
 * @file
 * Necessery function for module to work.
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
function nodeviewcount_insert_node_view($nid, $uid, $uip) {
  $node_view = nodeviewcount_db_insert_node_view($nid, $uid, $uip);
  return $node_view;
}

/**
 * Check node on content type for node view count.
 *
 * @param object $node
 *   The node for checking.
 *
 * @return bool
 *   TRUE if the node content type checked for count views, otherwise FALSE.
 */
function nodeviewcount_is_node_type_count($node) {
  $node_types = variable_get('nodeviewcount_node_types', array());
  if (!empty($node_types[$node->type])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Check node on content type for node view count.
 *
 * @param string $view_mode
 *   The node view mode for checking.
 *
 * @return bool
 *   TRUE if the node content type checked for count views, otherwise FALSE.
 */
function nodeviewcount_is_node_view_mode_count($view_mode) {
  $node_view_modes = variable_get('nodeviewcount_node_view_modes', array());
  if (!empty($node_view_modes[$view_mode])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Collects node view modes.
 *
 * @return array
 *   Array with node view modes.
 */
function nodeviewcount_get_node_view_modes_count() {
  $node_view_modes_count = array();
  $node_view_modes = variable_get('nodeviewcount_node_view_modes', array());
  foreach ($node_view_modes as $node_view_mode) {
    if ($node_view_mode !== 0) {
      $node_view_modes_count[] = $node_view_mode;
    }
  }
  return $node_view_modes_count;
}

/**
 * Check user on user roles for node view count.
 *
 * @param object $user
 *   The user for checking.
 *
 * @return bool
 *   TRUE if the user role checked for count views, otherwise FALSE.
 */
function nodeviewcount_is_user_role_count($user) {

  // Excluded roles will be considered first.
  $excluded_user_roles = variable_get('nodeviewcount_excluded_user_roles', array());
  foreach ($excluded_user_roles as $role_name) {
    if (in_array($role_name, $user->roles)) {
      return FALSE;
    }
  }

  // Then check for included roles.
  $nodeviewcount_user_roles = variable_get('nodeviewcount_user_roles', array());
  foreach ($nodeviewcount_user_roles as $role_name) {
    if (in_array($role_name, $user->roles)) {
      return TRUE;
    }
  }

  // Do not record unless instructed.
  return FALSE;
}

/**
 * Count node views.
 *
 * @param object $node
 *   Chosen node for counting.
 * @param object|null $user
 *   Chosen user for counting.
 * @param bool $distinct_users
 *   Distinct user or not.
 *
 * @return int
 *   Count of node views.
 */
function nodeviewcountcount_count_node_views($node, $user = NULL, $distinct_users = FALSE) {
  $is_node_count = nodeviewcount_is_node_type_count($node);
  if (!$is_node_count) {
    return FALSE;
  }
  $is_user_count = nodeviewcount_is_user_role_count($user);
  if (!is_null($user) && !$is_user_count) {
    return FALSE;
  }
  $node_view_count = nodeviewcount_db_count_node_views($node, $user, $distinct_users);
  return $node_view_count;
}