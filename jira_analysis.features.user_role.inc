<?php
/**
 * @file
 * jira_analysis.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function jira_analysis_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  return $roles;
}
