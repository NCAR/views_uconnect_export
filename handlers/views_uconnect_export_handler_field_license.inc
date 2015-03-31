<?php
/**
 * @file
 *   Views field handler
 */

/**
 * Views field handler
 *
 * The only thing we're doing here is making sure the field_alias
 * gets set properly, and that none of the sql-specific query functionality
 * gets called.
 */
class views_uconnect_export_handler_field_license extends views_handler_field {
	/**
	 * Add some required fields needed on render().
	 */
	function construct() {
		parent::construct();
	}

	/**
	 * Loads additional fields.
	 */
	function query() {
		$this -> ensure_my_table();
		$this->field_alias = $this->real_field;
	}

	/**
	 * Default options form.
	 */
	function option_definition() {
		$options = parent::option_definition();

		$options['license_name'] = array('default' => '');
		$options['license_url'] = array('default' => '');
		$options['license_explanation'] = array('default' => '');
		for ($i = 0; $i < 5; $i++) {
			$options['license_properties'][$i]['license_property'] = array('default' => '');
		}

		return $options;
	}

	/**
	 * Creates the form item for the options added.
	 */
	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);

		$form['license_name'] = array(
			'#type' => 'textfield',
			'#title' => t('License name'),
			'#default_value' => $this -> options['license_name'],
			'#description' => t('The name of the license.'),
		);

		$form['license_url'] = array(
			'#type' => 'textfield',
			'#title' => t('License URL'),
			'#default_value' => $this -> options['license_url'],
			'#description' => t('The URL of the License.'),
		);
		
		$form['license_explanation'] = array(
			'#type' => 'textfield',
			'#title' => t('Explanation of the license'),
			'#default_value' => $this -> options['license_explanation'],
			'#description' => t('The explanation of the License.'),
		);
		
		$form['license_properties'] = array(
			'#type' => 'fieldset',
			'#title' => t('UCARConnect License Properties'),
			'#description' => t('This is only used for content that is exported to the UCARConnect resource catalog'),
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
		);

		for ($i = 0; $i < 5; $i++) {

			$form['license_properties'][$i]['license_property'] = array(
				'#type' => 'textfield',
				'#default_value' => $this -> options['license_properties'][$i]['license_property'],
				'#description' => t('Type in the value for the property'),
				'#title' => t('License Property'),
			);

		}
	}

	/**
	 * Renders the field handler.
	 */
	function render($values) {
		$properties = array();
		for ($i = 0; $i < 5; $i++) {
			$properties[$i] = $this -> options['license_properties'][$i]['license_property'];
		}
		
		$data = array(
			'name' => $this->options['license_name'],
			'url' => $this->options['license_url'],
			'explanation' => $this->options['license_explanation'],
			'properties' => $properties,
		);
		return $data;

	}
}
