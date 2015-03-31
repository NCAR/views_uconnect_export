<?php
/**
 * A handler to display dates as just the time if today, otherwise as time and date.
 *
 * @ingroup views_field_handlers
 */
class views_uconnect_export_handler_field_custom extends views_handler_field_custom {

	function option_definition() {
		$options = parent::option_definition();

		for ($i = 0; $i < 5; $i++) {
			$options['uconnect_attributes'][$i]['uconnect_attribute_name'] = array('default' => '');
			$options['uconnect_attributes'][$i]['uconnect_attribute_value'] = array('default' => '');
		}
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
			'#theme' => 'uconnect_export_field_multiple_attributes_mapper_form',
		);

		for ($i = 0; $i < 5; $i++) {

			$form['uconnect_attributes'][$i]['uconnect_attribute_name'] = array(
				'#type' => 'textfield',
				'#default_value' => $this -> options['uconnect_attributes'][$i]['uconnect_attribute_name'],
				'#description' => t('Type in the name of the attribute'),
				'#title' => t('Attribute name'),
			);

			$form['uconnect_attributes'][$i]['uconnect_attribute_value'] = array(
				'#type' => 'textfield',
				'#default_value' => $this -> options['uconnect_attributes'][$i]['uconnect_attribute_value'],
				'#description' => t('Type in the value of the attribute'),
				'#title' => t('Attribute value'),
			);
		}

	}

}
