<?php
/**
 * @file
 * Modifies data table.
 */

/**
 * Implements hook_views_data().
 */
function nodeviewcount_views_data() {
  $data = array();
  $data['nodeviewcount']['table']['group'] = t('Nodeview count');
  $data['nodeviewcount']['table']['base'] = array(
    'field' => 'nid',
    'title' => t('Nodeview counts'),
    'help' => t('This table contains views of nodes.'),
    'weight' => -10,
  );
  $data['nodeviewcount']['table']['join'] = array(
    'node' => array(
      'handler' => 'views_join',
      'left_table' => 'node',
      'left_field' => 'nid',
      'field' => 'nid',
    ),
    'users' => array(
      'handler' => 'views_join',
      'left_table' => 'users',
      'left_field' => 'uid',
      'field' => 'uid',
    ),
  );
  $data['nodeviewcount']['id'] = array(
    'title' => t('Nodeview count ID'),
    'help' => t('ID for the node view count.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_group_by_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_group_by_numeric',
    ),
  );
  $data['nodeviewcount']['nid'] = array(
    'title' => t('Nodeview content nid'),
    'help' => t('Node ID forcontent that was viewed.'),
    'relationship' => array(
      'title' => t('Nodeview content ID'),
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
      'label' => t('Node ID'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['nodeviewcount']['uid'] = array(
    'title' => t('Nodeview User account ID'),
    'help' => t('The User account ID for the person Who viewed the node.'),
    'relationship' => array(
      'title' => t('Nodeview User ID'),
      'base' => 'users',
      'field' => 'uid',
      'handler' => 'views_handler_relationship',
      'label' => t('User ID'),
    ),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );
  $data['nodeviewcount']['datetime'] = array(
    'title' => t('Nodeview time'),
    'help' => t('The date and time when the node was viewed.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
  );
  $data['nodeviewcount']['uip'] = array(
    'title' => t('Nodeview User IP'),
    'help' => t('IP for user account that viewed the node.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );

  return $data;
}
