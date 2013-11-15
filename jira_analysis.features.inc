<?php
/**
 * @file
 * jira_analysis.features.inc
 */

/**
 * Implements hook_node_info().
 */
function jira_analysis_node_info() {
  $items = array(
    'jira_analysis' => array(
      'name' => t('Jira Analysis'),
      'base' => 'node_content',
      'description' => t('Type to display charts and graphs of Jira queries'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
