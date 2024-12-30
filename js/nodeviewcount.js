/**
 * @file
 * Javascript functions for nvc module.
 */

/**
 * Send info about node viewing.
 */
jQuery(document).ready(function ($) {
  var nodeviewcount_insert_node_view = function (nid, uid, uip) {
    var nodeviewcount_path = Backdrop.settings.nodeviewcount.nodeviewcount_path;
    var nodeviewcount_timestamp = Backdrop.settings.nodeviewcount.nodeviewcount_timestamp;
    var nodeviewcount_token = Backdrop.settings.nodeviewcount.nodeviewcount_token;
    $.ajax({
      type: 'POST',
      url: Backdrop.settings.basePath + nodeviewcount_path + '/' + nid + '/' + uid + '/' + nodeviewcount_timestamp + '/' + uip +'/'+ nodeviewcount_token,
      dataType: 'json'
    });
  }
  var nodeviewcount_nid = Backdrop.settings.nodeviewcount.nodeviewcount_nid;
  var nodeviewcount_uid = Backdrop.settings.nodeviewcount.nodeviewcount_uid;
  var nodeviewcount_uip = Backdrop.settings.nodeviewcount.nodeviewcount_uip;
  nodeviewcount_insert_node_view(nodeviewcount_nid, nodeviewcount_uid, nodeviewcount_uip);
});
