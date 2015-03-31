<?php
/**
 * @file
 */

class views_uconnect_export_plugin_style_lar extends views_uconnect_export_plugin_style {
	
	
	/**
	 * Define the option for this view.
	 */
	function option_definition() {
		$options = parent::option_definition();

		
		$options['repository_name'] = array('default' => 'UCARConnect LAR Repository');
		$options['record_prefix'] = array('default' => 'RECORD');
		$options['id_prefix'] = array('default' => 'oai.ucarconnect.ucar.edu');

		return $options;
	}


	/**
	 * Provide the default form for setting options.
	 */
	function options_form(&$form, &$form_state) {
		// It is very important to call the parent function here:
		//parent::options_form($form, $form_state);

		$form['repository_name'] = array(
					'#type' => 'textfield',
					'#title' => t('Repository Name'),
					'#description' => t('The name of this collection.  EX: UCAR SciEd Teaching Boxes'),
					'#weight' => 0,
					'#default_value' => $this -> options['repository_name'],
				);

				$form['record_prefix'] = array(
					'#type' => 'textfield',
					'#title' => t('Record Prefix'),
					'#description' => t('The prefix that should be added to each record.  EX: UCARSCIED'),
					'#weight' => 0,
					'#default_value' => $this -> options['record_prefix'],
				);

				$form['id_prefix'] = array(
					'#type' => 'textfield',
					'#title' => t('ID Prefix'),
					'#description' => t('A unique ID prefix for each record.  EX: oai.scied.ucar.edu'),
					'#weight' => 1,
					'#default_value' => $this -> options['id_prefix'],
				);
		
		

	}
	

	
  function render_records() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }
   
   // TODO:  account for if these are empty
   
	$record_prefix = $this->options['record_prefix'];
	$id_prefix = $this->options['id_prefix'];
	
    $records = '';
	// prefix with unique identifier
	$record_prefix = $record_prefix.'-ID-';
	$id_prefix = $id_prefix.':'.$record_prefix;
    if ($this->uses_row_plugin()) {
      $rows = array();
	  $footer = theme('views_uconnect_export_lar_record_footer');
	  $datestamp = date('Y-m-d');
      foreach ($this->view->result as $row_index => $row) {
      	
        $this->view->row_index = $row_index;
        $lar_fields = $this->row_plugin->render($row);	
		$padding_zero_nid = str_pad($row->nid,9 ,"0",STR_PAD_LEFT);
		$identifier = $id_prefix.substr(chunk_split($padding_zero_nid,3,'-'),0,-1);
		$recordID = $record_prefix.substr(chunk_split($padding_zero_nid,3,'-'),0,-1);
		
		if(isset($row->_field_data)){
			$datestamp = date('Y-m-d',$row->_field_data['nid']['entity']->revision_timestamp);	
			$created_datestamp = date('Y-m-d',$row->_field_data['nid']['entity']->created);	
		}

		$header = theme('views_uconnect_export_lar_record_header',array('datestamp' => $datestamp, 'identifier' => $identifier, 'recordID'=> $recordID, 'recordDate'=>$created_datestamp));	
        $records .= theme('views_uconnect_export_lar_record', array('header' => $header, 'footer' => $footer, 'fields' => $lar_fields));
      }
    }
  	return $records;
  }
}
