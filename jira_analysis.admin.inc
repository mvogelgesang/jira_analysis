<?php
/**
 * Created by JetBrains PhpStorm.
 * User: mvogelgesang
 * Date: 10/1/13
 * Time: 1:22 PM
 * To change this template use File | Settings | File Templates.
 * @file
 * Administrative page callbacks for jira_analysis module.
 */



/**
 * Implements hook_form().
 */
function jira_analysis_admin_settings_form($node, &$form_state) {
    $form = array();

    $form['overview'] = array(
        '#markup' => t('This interface allows administrators to manage general Jira Analysis Settings'),
        '#prefix' => '<p>',
        '#suffix' => '</p>',
    );


    //$form['jira_analysis_credential_fieldset']
    $form['jira_analysis_default_url'] = array(
        '#title' => t('URL'),
        '#description' => t('Jira REST URL eg "http://yourJiraInstallation.com/rest/api/2/". You must include "/rest/api/2/".'),
        '#type' => 'textfield',
        '#default_value' => variable_get('jira_analysis_default_url', ''),
    );

    //$form['jira_analysis_credential_fieldset']
    $form['jira_analysis_default_user_name'] = array(
        '#title' => t('User Name'),
        '#description' => t(''),
        '#type' => 'textfield',
        '#default_value' => variable_get('jira_analysis_default_user_name', ''),
        '#required' => TRUE,
    );

    //$form['jira_analysis_credential_fieldset']
    $form['jira_analysis_default_password'] = array(
        '#title' => t('Password'),
        '#description' => t(''),
        '#type' => 'password',
        '#default_value' => variable_get('jira_analysis_default_password', ''),
        '#required' => TRUE,
    );

    $result = db_query('SELECT status_id, status_name FROM jira_analysis_status order by status_name');
    $status_options_array = array();
    foreach ($result as $record) {
        $tempID = $record->{'status_id'};
        $status_options_array[$tempID] = $record->{'status_name'};
    }

    $form['jira_analysis_default_status'] = array(
        '#title' => t('Statuses'),
        '#description' => t('Choose the Jira statuses that you would like to have selected by default'),
        '#type' => 'checkboxes',
        '#options' => $status_options_array,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );

    return $form;

    //return $form;
}


/**
 * Validates jira admin settings.
 */
function jira_analysis_admin_settings_form_validate($form, &$form_state) {

    $cred = $form_state['values']['jira_analysis_default_user_name'] . ':' . $form_state['values']['jira_analysis_default_password'];

    $ch = curl_init($form_state['values']['jira_analysis_default_url'] . 'status');
    //curl_setopt($ch, CURLOPT_USERPWD, $form_state['values']['jira_analysis_default_user_name'].':'.$form_state['values']['jira_analysis_default_password']);
    curl_setopt($ch, CURLOPT_USERPWD, $cred);
    curl_setopt($ch, CURLOPT_POST, FALSE);
    curl_setopt($ch, CURLOPT_HTTPGET, TRUE);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_HEADER, TRUE);
    $resp = curl_exec($ch);
    $respSplit = list($header, $body) = explode("\r\n\r\n", $resp, 2);
    $jsonResp = json_decode($respSplit[1]);

    $respCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    if ($respCode != 200) {
        form_set_error('jira_analysis_default_password', t('Validation failed, please check your URL and credentials and re-submit (' . $respCode . ')'));
    } else {
        $schema = drupal_get_schema('jira_analysis_status');
        $info = field_info_field('field_data_field_status');

        // Get a reference to the values
        $values = & $info['settings']['allowed_values'];


        foreach ($jsonResp as $status) {
            //if the schema is empty, insert data
            $nid = db_insert('jira_analysis_status') // Table name no longer needs {}
                ->fields(array(
                    'status_id' => $status->{'id'},
                    'status_name' => $status->{'name'},
                    'status_description' => $status->{'description'},
                    'created' => date('Y-m-d H:i:s', REQUEST_TIME),
                ))
                ->execute();

            //insert values into the jira_analysis_status field allowed values list too
            $values[$status->{'id'}] = $status->{'name'};
        }
        // Save the field
        //field_update_field($info);
    }
    curl_close($ch);

}


/**
 * Create an options array for inserting Statuses
 */
function create_status_list_options($jira_status_list_response) {
    $list_len = count($jira_status_list_response);
    for ($i = 0; $i < $list_len; $i++) {

    }
}

/**
 * Process a validated jira admin cflow settings submission
 */
function jira_analysis_admin_settings_form_submit($form, &$form_state) {
    //Rebuild the form.
    $form_state['rebuild'] = TRUE;

    // Save jira setting variables
    variable_set('jira_analysis_default_url', $form_state['values']['jira_analysis_default_url']);
    variable_set('jira_analysis_default_user_name', $form_state['values']['jira_analysis_default_user_name']);
    variable_set('jira_analysis_default_password', $form_state['values']['jira_analysis_default_password']);
    variable_set('jira_analysis_default_status', $form_state['values']['jira_analysis_default_status']);


    //Nofity User
    drupal_set_message(t('Jira Analysis settings saved'));
}

/**
 * @file
 * Administrative page callbacks for jira_analysis module.
 */

/**
 * Implements hook_form().
 */
function jira_analysis_cflow_page() {
    $result = db_query('SELECT * FROM jira_ref_cumulative_flow');

    $header = array('Title', array('data' => t('Operations'), 'colspan' => '2'));
    $rows = array();
    foreach ($result as $menu) {
        $row = array(check_plain($menu->cf_type_name) . '<div class="description">' . filter_xss_admin($menu->cf_type_description) . '</div>');
        //$row = array($menu->cf_type_name, $menu->cf_type_description);
        $row[] = array('data' => l(t('view'), 'admin/config/jira_analysis/settings/clfow/' . $menu->cf_type_id . '/view'));
        $row[] = array('data' => l(t('edit'), 'admin/config/jira_analysis/settings/clfow/' . $menu->cf_type_id . '/edit'));
        $rows[] = $row;
    }
    return theme('table', array('header' => $header, 'rows' => $rows));
    //return $form;
}

/**
 * Menu callback; Build the form that handles the adding/editing of a cumulative flow items.
 */
function jira_analysis_cflow_edit($form, &$form_state, $type, $menu = array()) {

}

/**
 * Submit function for adding or editing cflow settings submissions
 */
/*function jira_analysis_cflow_submit($form, &$form_state) {
    $menu = $form_state['values'];
    $path = 'admin/structure/menu/manage/';
    if ($form['#insert']) {

    }
    else {
        jira_analysis_cflow_save($menu);
    }
}*/


/**
 * Implements hook_form().
 */
function jira_analysis_cycletime_page() {
    $result = db_query('SELECT count(jct.ct_id) as ct_rec_count, max(jct.created) as ct_update, jrct.ct_type_id, jrct.ct_type_name, jrct.ct_type_description
                        FROM jira_ref_cycle_time jrct, jira_cycle_time jct
                        WHERE jrct.ct_type_id = jct.ct_type_id
                        GROUP BY jrct.ct_type_id, jrct.ct_type_name, jrct.ct_type_description, jct.created');

    $header = array('Title', 'Record Count', 'Last Updated', array('data' => t('Operations'), 'colspan' => '2'));
    $rows = array();
    foreach ($result as $menu) {
        dpm($menu);
        $row = array(check_plain($menu->ct_type_name) . '<div class="description">' . filter_xss_admin($menu->ct_type_description) . '</div>');
        $row[] = $menu->ct_rec_count;
        $row[] = $menu->ct_update;
        //$row = array($menu->cf_type_name, $menu->cf_type_description);
        $row[] = array('data' => l(t('view'), 'admin/config/jira_analysis/settings/clfow/' . $menu->ct_type_id . '/view'));
        $row[] = array('data' => l(t('edit'), 'admin/config/jira_analysis/settings/clfow/' . $menu->ct_type_id . '/edit'));
        $rows[] = $row;
    }
    return theme('table', array('header' => $header, 'rows' => $rows));
    //return $form;
}

/**
 * cycletime callback; Build the form that handles the adding/editing of a custom jira analysis cycle time reports.
 */
function jira_analysis_cycletime_edit($form, &$form_state, $type, $menu = array()) {

    $menu += array(
        'menu_name' => '',
        'old_name' => !empty($menu['menu_name']) ? $menu['menu_name'] : '',
        'title' => '',
        'description' => '',
    );
    // Allow menu_edit_menu_submit() and other form submit handlers to determine
    // whether the menu already exists.
    $form['#insert'] = empty($menu['old_name']);
    $form['old_name'] = array(
        '#type' => 'value',
        '#value' => $menu['old_name'],
    );

    $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#default_value' => $menu['title'],
        '#required' => TRUE,
        // The title of a system menu cannot be altered.
        //'#access' => !isset($system_menus[$menu['menu_name']]),
    );

    //$form['s']
    /*$form['menu_name'] = array(
        '#type' => 'machine_name',
        '#title' => t('Menu name'),
        '#default_value' => $menu['menu_name'],
        '#maxlength' => MENU_MAX_MENU_NAME_LENGTH_UI,
        '#description' => t('A unique name to construct the URL for the menu. It must only contain lowercase letters, numbers and hyphens.'),
        '#machine_name' => array(
            'exists' => 'menu_edit_menu_name_exists',
            'source' => array('title'),
            'replace_pattern' => '[^a-z0-9-]+',
            'replace' => '-',
        ),
        // A menu's machine name cannot be changed.
        '#disabled' => !empty($menu['old_name']) || isset($system_menus[$menu['menu_name']]),
    ); */

    $form['description'] = array(
        '#type' => 'textarea',
        '#title' => t('Description'),
        '#default_value' => $menu['description'],
    );
    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
    );
    // Only custom menus may be deleted.


    return $form;
}