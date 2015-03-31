<?php

/**
 * @file
 * Theme related functions for processing our output style plugins.
 *
 * Views bug: http://drupal.org/node/593336
 */

function theme_views_uconnect_export_row_lar_fields($vars) {
	$view = $vars['view'];

	// Loop through the fields for this view.
	$previous_inline = FALSE;
	$vars['fields'] = array();

	$row_index = $view -> row_index;

	foreach ($view->field as $id => $field) {
		// clear attribs each round
		$a_attribs = array();

		$field_output = $view -> style_plugin -> get_field($row_index, $id);

		$empty = $field_output !== 0 && empty($field_output);
		if (empty($field -> options['exclude']) && (!$empty || (empty($field -> options['hide_empty']) && empty($vars['options']['hide_empty'])))) {
			$key = check_plain(_views_uconnect_export_xml_tag_clean($view -> field[$id] -> label()));

			// TODO: special handling for license

			if (!empty($field -> options['uconnect_attributes'])) {

				// handle multiple attribs
				foreach ($field -> options['uconnect_attributes'] as $index => $attribs) {
					$trim_name = trim($attribs['uconnect_attribute_name']);
					$trim_value = trim($attribs['uconnect_attribute_value']);
					if (!empty($trim_name) && !empty($trim_value)) {
						$a_attribs[$attribs['uconnect_attribute_name']] = $attribs['uconnect_attribute_value'];
					}
				}
			}
			else if (!empty($field -> options['uconnect_attribute_name']) && !empty($field -> options['uconnect_attribute_value'])) {
				// handle single attrib
				// if set then we have attributes to account for
				$a_attribs = array($field -> options['uconnect_attribute_name'] => $field -> options['uconnect_attribute_value']);
			}

			// check for underscores which is how I account for nested fields
			// EXCEPTION do not split for standard_asn_id
			if ($key != 'standard_asn_id' && strpos($key, '_') !== false) {
				$a_key_parts = explode('_', $key);

				// reverse array and work backwards
				$a_rev = array_reverse($a_key_parts);
				$counter = 0;
				$total = count($a_rev);
				foreach ($a_rev as $sub_index => $sub_value) {
					if ($counter == 0) {
						$last_sub_item = array();
						$last_sub_item['key'] = $sub_value;
						$last_sub_item['value'] = _views_uconnect_export_xmlstr($field_output);
						$last_sub_item['attributes'] = $a_attribs;
						// reset attribs because attribute was only for child value
						$a_attribs = array();
					}
					else if ($counter != $total - 1) {
						$sub_item = array();
						$sub_item['key'] = $sub_value;
						$sub_item['value'] = array($last_sub_item);
						$sub_item['attributes'] = $a_attribs;
						$last_sub_item = $sub_item;
					}
					else {
						$item = array();
						$item['key'] = $sub_value;
						$item['value'] = array($last_sub_item);
						$item['attributes'] = $a_attribs;

						$items[] = $item;
					}
					$counter++;
				}
				// here, need to see if field has delimiters
			}
			else if ($key == 'standard_asn_id') {

				// need to split value by comma
				$a_field_items = explode(',', $field_output);
				foreach ($a_field_items as $item_index => $item_value) {
					$item = $subitem = $subsubitem = array();

					$subsubitem['key'] = 'id';
					$subsubitem['value'] = _views_uconnect_export_xmlstr(trim($item_value));
					$subsubitem['attributes'] = array('type' => 'asn');

					$subitem['key'] = 'alignment';
					$subitem['value'] = array($subsubitem);
					$subitem['attributes'] = array();

					$item['key'] = 'standard';
					$item['value'] = array($subitem);
					$item['attributes'] = array();

					$items[] = $item;

				}
			}
			else if (isset($field -> multiple) && !empty($field -> multiple)) {
				$separator = $field -> options['separator'];
				foreach (explode($separator, $field_output) as $value) {

					$item['key'] = $key;
					$item['value'] = _views_uconnect_export_xmlstr(trim($value));
					$item['attributes'] = $a_attribs;

					$items[] = $item;
				}
			}
			else if ($key == 'license') {
				// special handling for license nested fields

				// handle child values
				$children = array();

				// name is required
				if (!empty($field -> options['license_name'])) {
					if (!empty($field -> options['license_url'])) {
						$a_attribs['URL'] = _views_uconnect_export_xmlstr(trim($field -> options['license_url']));
					}
					$childitem = array();
					$childitem['key'] = 'name';
					$childitem['value'] = _views_uconnect_export_xmlstr(trim($field -> options['license_name']));
					$childitem['attributes'] = $a_attribs;

					$children[] = $childitem;
					$a_attribs = array();
					foreach ($field->options['license_properties'] as $item_index => $item_value) {
						if (!empty($item_value['license_property'])) {
							$childitem = array();
							$childitem['key'] = 'property';
							$childitem['value'] = _views_uconnect_export_xmlstr(trim($item_value['license_property']));
							$childitem['attributes'] = $a_attribs;

							$children[] = $childitem;
						}
					}
					if (!empty($field -> options['license_explanation'])) {
						$childitem = array();
						$childitem['key'] = 'explanation';
						$childitem['value'] = _views_uconnect_export_xmlstr(trim($field -> options['license_explanation']));
						$childitem['attributes'] = $a_attribs;

						$children[] = $childitem;
					}

					// add license
					$item = array();
					$item['key'] = $key;
					$item['value'] = $children;
					$item['attributes'] = $a_attribs;

					$items[] = $item;
				}
			} else if (($key == 'keyword' || $key == 'educationLevel' || $key == 'subject' || $key == 'resourceType') && strpos($field_output, ',') !== false) {
				// need to split value by comma
				$a_field_items = explode(',', $field_output);
				foreach ($a_field_items as $item_index => $item_value) {
					$item = array();
					$item['key'] = $key;
					$item['value'] = _views_uconnect_export_xmlstr(trim($item_value));
					$item['attributes'] = $a_attribs;

					$items[] = $item;
				}
			}
			else if (isset($field -> items) && !empty($field -> items)) {
				// if multiple entries exist, then add multiple fields in output
				foreach ($field->items as $item_data) {
					foreach ($item_data as $item_index => $item_value) {
						$item = array();
						$item['key'] = $key;
						$item['value'] = _views_uconnect_export_xmlstr($item_value['name']);
						$item['attributes'] = $a_attribs;

						$items[] = $item;
					}
				}
			}
			else {
				$item['key'] = $key;
				$item['value'] = _views_uconnect_export_xmlstr($field_output);
				$item['attributes'] = $a_attribs;

				$items[] = $item;
			}
		}
	}

	if (isset($items)) {
		return format_xml_elements($items);
	}
	else {
		return false;
	}
}

/**
 * Preprocessor for views-uconnect-export-header template
 **/
function template_preprocess_views_uconnect_export_header(&$vars) {
	global $base_url;

	$view = $vars['view'];
	$path = $view -> display_handler -> get_path();

	$datestamp = db_query("SELECT min(changed) FROM {node} ") -> fetchField();

	// TODO:  account for if these are empty
	$repository_name = $view -> style_options['repository_name'];

	$vars['repository_name'] = $repository_name;
	//$vars['base_url'] = $base_url . '/' . $path;
	$vars['base_url'] = 'http://uc2.dls.ucar.edu/cgi-bin/gateway/gateway.cgi/' . preg_replace("(^https?://)", "", $base_url) . '/' . $path;
	$vars['protocol_version'] = '2.0';
	$vars['admin_email'] = variable_get('site_mail', '');
	$vars['earliest_timestamp'] = gmstrftime('%Y-%m-%dT%H:%M:%SZ', $datestamp);
	$vars['deleted_record'] = 'no';
	$vars['granularity'] = 'YYYY-MM-DD';
	$vars['oai_metadata_prefix'] = 'lar';
	$vars['oai_schema'] = 'http://ns.nsdl.org/ncs/lar/1.00/schemas/lar.xsd';
	$vars['oai_metadata_namespace'] = 'http://ns.nsdl.org/ncs/lar';
}

/**
 * For mapping Drupal fields to xml fields
 **/
function theme_uconnect_export_field_mapper_form($vars) {
	$form = $vars['form'];
	foreach (element_children($form) as $key) {
		$rows[] = array(
			drupal_render($form[$key]['drupal_label']),
			drupal_render($form[$key])
		);
	}

	$header = array(
		t('Drupal field label'),
		t('LAR element name')
	);
	$output = theme('table', array(
		'header' => $header,
		'rows' => $rows
	));

	$output .= drupal_render_children($form);
	return $output;
}

/* for lar attributes on fields that are known to only have one */
function theme_uconnect_export_field_single_attributes_mapper_form($vars) {

	$form = $vars['form'];

	foreach (element_children($form) as $key) {

		$a_keys[] = drupal_render($form[$key]);
	}
	$rows[] = $a_keys;

	$header = array(
		t('Attribute Name'),
		t('Attribute Value')
	);
	$output = theme('table', array(
		'header' => $header,
		'rows' => $rows
	));

	$output .= drupal_render_children($form);
	return $output;
}

/* for lar attributes on fields that may have more than one */
function theme_uconnect_export_field_multiple_attributes_mapper_form($vars) {
	$form = $vars['form'];
	foreach (element_children($form) as $key) {
		$rows[] = array(
			drupal_render($form[$key]['uconnect_attribute_name']),
			drupal_render($form[$key]['uconnect_attribute_value'])
		);
	}

	$header = array(
		t('Attribute Name'),
		t('Attribute Value')
	);
	$output = theme('table', array(
		'header' => $header,
		'rows' => $rows
	));

	$output .= drupal_render_children($form);
	return $output;
}

/**
 * Returns a valid XML tag formed from the given input.
 *
 * @param $tag The string that should be made into a valid XML tag.
 * @return The valid XML tag or an empty string if the string contained no valid
 * XML tag characters.
 */
function _views_uconnect_export_xml_tag_clean($tag) {

	// This regex matches characters that are not valid in XML tags, and the
	// unicode ones that are. We don't bother with unicode, because it would so
	// the preg_replace down a lot.
	static $invalid_tag_chars_regex = '#[^\:A-Za-z_\-.0-9]+#';

	// These characters are not valid at the start of an XML tag:
	static $invalid_start_chars = '-.0123456789';

	// Convert invalid chars to '-':
	$tag = preg_replace($invalid_tag_chars_regex, '-', $tag);

	// Need to trim invalid characters from the start of the string:
	$tag = ltrim($tag, $invalid_start_chars);

	return $tag;
}

function _views_uconnect_export_xmlstr($string, $charset = 'iso8859-1', $xmlescaped = 'false') {
	$xmlstr = stripslashes(trim($string));
	// just remove invalid characters
	$pattern = "/[\x-\x8\xb-\xc\xe-\x1f]/";
	$xmlstr = preg_replace($pattern, '', $xmlstr);

	// escape only if string is not escaped
	if (!$xmlescaped) {
		$xmlstr = htmlspecialchars($xmlstr, ENT_QUOTES);
	}

	return $xmlstr;
}
