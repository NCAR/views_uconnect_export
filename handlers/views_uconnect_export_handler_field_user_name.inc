<?php
/**
 * A handler to display dates as just the time if today, otherwise as time and date.
 *
 * @ingroup views_field_handlers
 */
class views_uconnect_export_handler_field_user_name extends views_handler_field_user_name {
	protected $uconnect_attributes_name = array(
		'' => 'None',
		'role' => 'role'
	);
	protected $uconnect_attributes_value = array(
		'' => 'None',
		'Creator' => 'Creator',
		'Editor' => 'Editor',
		'Collection Developer' => 'Collection Developer',
		'Funder' => 'Funder',
		'Publisher' => 'Publisher'
	);
	function option_definition() {
		$options = parent::option_definition();
		$options['uconnect_attribute_name'] = array('default' => 'type');
		$options['uconnect_attribute_value'] = array('default' => '');
		return $options;
	}

	function options_form(&$form, &$form_state) {
		parent::options_form($form, $form_state);
		$form['date_format']['#options']['uconnect_lar_date'] = t('UCARConnect LAR date field');

		$form['uconnect_attributes'] = array(
			'#type' => 'fieldset',
			'#title' => t('UCARConnect Field Attributes'),
			'#description' => t('This is only used for content that is exported to the UCARConnect resource catalog'),
			'#collapsible' => TRUE,
			'#collapsed' => FALSE,
			'#weight' => 9,
			'#theme' => 'uconnect_export_field_single_attributes_mapper_form',
		);

		$form['uconnect_attribute_name'] = array(
			'#options' => $this -> uconnect_attributes_name,
			'#type' => 'select',
			'#default_value' => $this -> options['uconnect_attribute_name'],
			'#description' => t('Choose the name of the attribute'),
			'#fieldset' => 'uconnect_attributes',
		);

		$form['uconnect_attribute_value'] = array(
			'#options' => $this -> uconnect_attributes_value,
			'#type' => 'select',
			'#default_value' => $this -> options['uconnect_attribute_value'],
			'#description' => t('Choose the value of the attribute'),
			'#fieldset' => 'uconnect_attributes',
		);
	}

}
