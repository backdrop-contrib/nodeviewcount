<?php
/**
 * @file
 * Admin form defenition.
 */

/**
 * Nodeviewcount admin form.
 */
function nodeviewcount_admin_settings_form($form, &$form_state) {
  $config = config('nodeviewcount.settings');
  $form['#config'] = 'nodeviewcount.settings';

  // Get node types options.
  $options_node_type = nodeviewcount_get_checked_node_types();
  $form['nodeviewcount_node_types'] = array(
    '#title' => t('Content types: count views on content of this type'),
    '#type' => 'checkboxes',
    '#options' => $options_node_type,
    '#default_value' => $config->get('nodeviewcount_node_types'),
  );
  // Get node view modes.
  $form['nodeviewcount_node_modes'] = array(
    '#title' => t('Node display modes'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $options_node_view_modes = nodeviewcount_get_node_view_modes();
  $form['nodeviewcount_node_modes']['nodeviewcount_node_view_modes'] = array(
    '#description' => t('Choose node view modes to count views of node.'),
    '#type' => 'checkboxes',
    '#options' => $options_node_view_modes,
    '#default_value' => $config->get('nodeviewcount_node_view_modes'),
  );
  // Get user roles options.
  $options_user_roles = node_view_count_get_user_roles();
  $form['nodeviewcount_user_roles'] = array(
    '#title' => t('Recorded user roles'),
    '#title' => t('User roles: count views from people in these roles'),
    '#type' => 'checkboxes',
    '#options' => $options_user_roles,
    '#default_value' => $config->get('nodeviewcount_user_roles'),
  );
  // Get excluded user roles.
  $form['nodeviewcount_excluded_roles'] = array(
    '#title' => t('Excluded user roles'),
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $options_excluded_user_roles = node_view_count_get_excluded_user_roles();
  $form['nodeviewcount_excluded_roles']['nodeviewcount_excluded_user_roles'] = array(
    '#description' => t('Choose user roles which will be excluded from counting node views.'),
    '#type' => 'checkboxes',
    '#options' => $options_excluded_user_roles,
    '#default_value' => $config->get('nodeviewcount_excluded_user_roles'),
  );
  // Get user roles options.
  $options_user_roles = node_view_count_get_user_roles();
  $form['nodeviewcount_user_roles'] = array(
    '#title' => t('User roles'),
    '#description' => t('Choose user roles to count node views for.'),
    '#type' => 'checkboxes',
    '#options' => $options_user_roles,
    '#default_value' => $config->get('nodeviewcount_user_roles'),
  );
  // Get ways of counting options.
  $options_way_counting = array(
    NODEVIEWCOUNT_JS_WAY_COUNT_VIEWS => t('JavaScript (reommended)'),
    NODEVIEWCOUNT_PHP_WAY_COUNT_VIEWS => t('PHP (Anonymos views cannot be counted)'),
  );
  $form['nodeviewcount_way_counting'] = array(
    '#title' => t('Method of counting'),
    '#type' => 'radios',
    '#options' => $options_way_counting,
    '#default_value' => $config->get('nodeviewcount_way_counting'),
  );
  $options_flush_log_timer = array(
    0 => t('Never'),
  );
  $time_intervals = array(
    0,
    86400,
    604800,
    1209600,
    2592000,
    15552000,
    31536000,
  );
  $options_flush_log_timer += backdrop_map_assoc($time_intervals, 'format_interval');
  $cron_path = array(
    '@cron' => url('admin/reports/status'),
  );
  $form['nodeviewcount_flush_log_timer'] = array(
    '#type' => 'select',
    '#title' => t('Discard node views logs older than'),
    '#default_value' => $config->get('nodeviewcount_flush_log_timer'),
    '#options' => $options_flush_log_timer,
    '#description' => t('Older log entries will be automatically discarded, (Requires a correctly configured <a href="@cron">cron maintenance task</a>.). Pick Never if you dont want logs to be deleted.', $cron_path),
  );
  $options_views_intervals = array(
    0 => t('Never'),
  );
  $time_views_intervals = array(
    0,
    600,
    3600,
    36000,
    86400,
  );
  $options_views_intervals += backdrop_map_assoc($time_views_intervals, 'format_interval');
  $form['nodeviewcount_views_limit'] = array(
    '#title' => t('Single page view limit'),
    '#description' => t('It stops increasing the number of views for a specific user and specific node during the selected time period. It may be necessary to protect the database from flooding.'),
    '#type' => 'select',
    '#options' => $options_views_intervals,
    '#default_value' => $config->get('nodeviewcount_views_limit'),
  );
  $secret_key = $config->get('nodeviewcount_secret_key');
  if (empty($secret_key)) {
    $secret_key = backdrop_random_key();
  }
  $form['nodeviewcount_secret_key'] = array(
    '#title' => t('Secret key'),
    '#description' => t('Secret key used to generate tokens for URL validation.'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#disabled' => TRUE,
    '#default_value' => $secret_key,
  );

  // Date format will be 'Y-m-d H:i:sP' on new installs.
  $form['date_format'] = array(
    '#title' => t('PHP Date format used to store the date in the database'),
    '#description' => t('The date format cannot be changed after data has been collected.'),
    '#type' => 'textfield',
    '#default_value' => $config->get('date_format'),
  );
  if (db_select('nodeviewcount')->countQuery()->execute()->fetchField() > 0) {
    $more = t('Truncate the nodeviewcount table to change the Date format.');
    $form['date_format']['#description'] = ' ' . $more;
    $form['date_format']['#disabled'] = TRUE;
  }

  $form = system_settings_form($form);

  return $form;
}

/**
 * Get node types options.
 *
 * @return array
 *   Associative array of all node types.
 */
function nodeviewcount_get_checked_node_types() {
  $options = array();
  // All node types on site.
  $node_field_types = node_type_get_types();
  foreach ($node_field_types as $node_field_type) {
    $options[$node_field_type->type] = $node_field_type->name;
  }
  return $options;
}

/**
 * Get user roles options.
 *
 * @return array
 *   Associative array of user roles.
 */
function node_view_count_get_user_roles() {
  $options = array();
  // Excluded user roles.
  $config = config('nodeviewcount.settings');
  $excluded_user_roles = $config->get('nodeviewcount_excluded_user_roles');
  // All user roles on site.
  $user_roles = user_roles();
  foreach ($user_roles as $key => $user_role) {
    if (empty($excluded_user_roles[$key])) {
      $options[$key] = $user_role;
    }
  }
  return $options;
}

/**
 * Get excluded user roles options.
 *
 * @return array
 *   Associative array of user roles.
 */
function node_view_count_get_excluded_user_roles() {
  $options = array();
  // Counting user roles.
  $config = config('nodeviewcount.settings');
  $counting_user_roles = $config->get('nodeviewcount_user_roles');
  // All user roles on site.
  $user_roles = user_roles();
  foreach ($user_roles as $key => $user_role) {
    if (empty($counting_user_roles[$key])) {
      $options[$key] = $user_role;
    }
  }
  return $options;
}

/**
 * Get node view modes options.
 *
 * @return array
 *   Associative array of node view modes.
 */
function nodeviewcount_get_node_view_modes() {
  $options = array();
  $node_info = entity_get_info('node');
  $node_view_modes = $node_info['view modes'];
  foreach ($node_view_modes as $key => $node_view_mode) {
    $options[$key] = $node_view_mode['label'];
  }
  return $options;
}
