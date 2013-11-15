<?php
/**
 * @file
 * jira_analysis.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function jira_analysis_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create jira_analysis content'.
  $permissions['create jira_analysis content'] = array(
    'name' => 'create jira_analysis content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any jira_analysis content'.
  $permissions['delete any jira_analysis content'] = array(
    'name' => 'delete any jira_analysis content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own jira_analysis content'.
  $permissions['delete own jira_analysis content'] = array(
    'name' => 'delete own jira_analysis content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any jira_analysis content'.
  $permissions['edit any jira_analysis content'] = array(
    'name' => 'edit any jira_analysis content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit own jira_analysis content'.
  $permissions['edit own jira_analysis content'] = array(
    'name' => 'edit own jira_analysis content',
    'roles' => array(),
    'module' => 'node',
  );

  return $permissions;
}
