<?php
/**
 * @file
 * Views include file with views hooks.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_uconnect_export_views_plugins() {
  $path = drupal_get_path('module', 'views_uconnect_export');

  $style_defaults = array(
    'path' => $path . '/plugins',
    'parent' => 'views_uconnect_export',
    'theme' => 'views_uconnect_export_response',
    'theme path' => $path . '/theme',
    'theme file' => 'views_uconnect_export.theme.inc',
    'uses row plugin' => TRUE,
    'uses fields' => TRUE,
    'uses options' => TRUE,
    'type' => 'uconnect-export',
  );

  return array(
  	
    'display' => array (
      'views_uconnect_export' => array(
        'title' => t('UCARConnect Export'),
        'help' => t('Export the view results to LAR'),
        'path' => $path . '/plugins',
        'handler' => 'views_uconnect_export_plugin_display',
        'parent' => 'page',
        'uses hook menu' => TRUE,
        'use ajax' => FALSE,
        'use pager' => TRUE,
        'accept attachments' => FALSE,
        'admin' => t('uconnect-export'),
        'help topic' => 'display-uconnect-export',
      ),
    ),
    'style' => array(
      'views_uconnect_export' => array(
        // this isn't really a display but is necessary so the file can
        // be included.
        'no ui' => TRUE,
        'handler' => 'views_uconnect_export_plugin_style',
        'path' => $path . '/plugins',
        'theme path' => $path . '/theme',
        'theme file' => 'views_uconnect_export.theme.inc',
        'additional themes' => array(
          'views_uconnect_export_header' => 'style',
          'views_uconnect_export_footer' => 'style',
        ),
        'additional themes base' => 'views_uconnect_export',
       ),
      'views_uconnect_export_lar' => array(
        'title' => t('Learning Application Ready (lar)'),
        'help' => t('Export the display as LAR'),
        'handler' => 'views_uconnect_export_plugin_style_lar',
        'additional themes' => array(
          'views_uconnect_export_lar_record_footer' => 'style',
          'views_uconnect_export_lar_record_header' => 'style',
          'views_uconnect_export_lar_record' => 'style',
          'views_uconnect_export_plugin_row_lar' => 'style',
          'views_uconnect_export_plugin_row_lar_fields' => 'style',
        ),
        'additional themes base' => 'views_uconnect_export',
      ) + $style_defaults,
    ),
    'row' => array(
      'lar' => array(
        'title' => t('LAR Fields'),
        'help' => t('Displays the fields with as LARelements.'),
        'path' => $path . '/plugins',
        'handler' => 'views_uconnect_export_plugin_row_lar',
        'theme' => 'views_uconnect_export_row_lar_fields',
        'parent' => 'views_uconnect_export',
        'theme path' => $path . '/theme',
        'theme file' => 'views_uconnect_export.theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'views_uconnect_export_lar',
        'help topic' => 'style-row-fields',
      ) ,
      ),
    );
}

/**
 * Implementation of hook_views_data_alter().
 */
 function views_uconnect_export_views_data_alter(&$data){
 	// NOTE:  I wanted to change the field handler for only this display type
 	// however this changes the handler for all of them.  
	foreach($data as $table=>$config){
 		foreach ($config as $item => $item_config) {
 			
 			if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_custom'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_custom';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_date'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_date';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_node'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_node';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_node_path'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_node_path';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_field'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_field';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_user_name'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_user_name';
 			} else if(isset($item_config['field']['handler']) && $item_config['field']['handler'] == 'views_handler_field_term_node_tid'){
 				$data[$table][$item]['field']['handler'] = 'views_uconnect_export_handler_field_term_node_tid';
 			}
		}
 	}

	return $data;
	
 }
 
