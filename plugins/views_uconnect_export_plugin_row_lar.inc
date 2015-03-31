<?php
class views_uconnect_export_plugin_row_lar extends views_plugin_row {

	// possible LAR fields
	protected $lar_elements = array(
		'none' => 'None',
		'accessMode' => 'accessMode',
		'accessRestrictions' => 'accessRestrictions',
		'audienceRefinement' => 'audienceRefinement',
		'copyright' => 'copyright',
		'copyrightHolder' => 'copyrightHolder',
		'contributor' => 'contributor',
		'date' => 'date',
		'description' => 'description',
		'educationLevel' => 'educationLevel',
		'fileSize' => 'fileSize',
		'format' => 'format',
		'identifier' => 'identifier',
		'keyword' => 'keyword',
		'language' => 'language',
		'license' => 'license',
		'metadataTerms' => 'metadataTerms',
		'otherIdentifier' => 'otherIdentifier',
		'readingGradeLevel' => 'readingGradeLevel',
		'readingLevel' => 'readingLevel',
		'relatedResource' => 'relatedResource',
		'subject' => 'subject',
		'standard_alignment_id' => 'standard_alignment_id',
		'standard_alignment_text' => 'standard_alignment_text',
		'standard_asn_id' => 'standard_asn_id',
		'title' => 'title',
		'type' => 'type'
	);
	function render($row) {
		return theme($this -> theme_functions(), array(
			'view' => $this -> view,
			'options' => $this -> options,
			'row' => $row
		));
	}

	function validate() {
		$errors = parent::validate();
		$dc_errors = array();
		$link = $this -> display -> handler -> option_link('Row options', 'row_options');

		$field_handlers = $this -> display -> handler -> get_handlers('field');
		foreach ($field_handlers as $id => $field) {
			$ui_label = $field -> ui_name();
			$label = $field -> label();
			// if no label and not set to exclude
			if ((empty($label) || !in_array($label, $this -> lar_elements)) && $field -> options['exclude'] === 0) {
				$dc_errors[] = t('The field "@title" does not have a LAR label associated with it. Go to the !link page to fix it.', array(
					'@title' => $ui_label,
					'!link' => $link
				));
			}
		}
		return array_merge($errors, $dc_errors);
		return $errors;
	}

	function option_definition() {
		$options = parent::option_definition();
		$options['separator'] = array('default' => ',');
		
		return $options;
	}

	function options_form(&$form, &$form_state) {
		//parent::options_form($form, $form_state);
		$field_handlers = $this -> display -> handler -> get_handlers('field');

		
		foreach ($field_handlers as $id => $handler) {

			$ui_labels[$id] = $handler -> ui_name();
			if ($label = $handler -> label()) {
				$labels[$id] = $label;
			}
		}

		$form['lar_labels'] = array(
			'#type' => 'fieldset',
			'#title' => t('Drupal field to NSDL LAR mapping'),
			'#theme' => 'uconnect_export_field_mapper_form',
		);

		foreach ($ui_labels as $id => $label) {
			$form['lar_labels'][$id] = array(
				'#type' => 'select',
				'#options' => $this -> lar_elements,
				'#default_value' => isset($labels[$id]) && in_array($labels[$id], $this -> lar_elements) ? $labels[$id] : 'none',
			);

			$form['lar_labels'][$id]['drupal_label'] = array('#markup' => $ui_labels[$id], );
		}
	}

	function options_submit(&$form, &$form_state) {
		// It is very important to call the parent function here:
		parent::options_submit($form, $form_state);
		$section = $form_state['section'];
		switch ($section) {
			case 'row_options' :
				$field_handlers = $this -> display -> handler -> get_handlers('field');
				//dpm($form_state);
				$lar_labels = $form_state['values'][$section]['lar_labels'];
				foreach ($field_handlers as $id => $field) {
					$options = $field -> options;
					if ($lar_labels[$id] != 'none') {
						$options['custom_label'] = TRUE;
						$options['label'] = $lar_labels[$id];
						$options['hide_empty'] = 1;
					}
					else {
						unset($options['custom_label']);
						$options['label'] = '';
					}
					$form_state['view'] -> set_item($form_state['display_id'], 'field', $id, $options);
				}
				break;
		}
	}

}
