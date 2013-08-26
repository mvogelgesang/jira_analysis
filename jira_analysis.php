<?php 
/**
 * @file
 * A module that displays data about Jira tickets
 */

  /**
   * Implements hook_help
   * 
   * Displays help and module information
   * 
   */
   function jira_analysis_help($path, $arg) {
   	switch($path) {
		case "admin/help#jira_analysis":
			return '<p>' . t('Displays data about Jira tickets') . '</p>';
			break;
   	}
   } 
