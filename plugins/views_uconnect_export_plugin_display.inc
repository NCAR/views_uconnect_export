<?php

/**
 * @file
 * Contains the LAR display plugin.
 *
 */

/**
 *
 * We are based on a feed display for compatibility.
 *
 * @ingroup views_display_plugins
 */
class views_uconnect_export_plugin_display extends views_plugin_display_page {

	function init(&$view, &$display, $options = NULL) {
		parent::init($view, $display, $options);

		// Set the default row style. Ideally this would be part of the option
		// definition, but in this case it's dependent on the view's base table,
		// which we don't know until init().
		$row_plugins = views_fetch_plugin_names('row', $this -> get_style_type(), array($view -> base_table));
		$default_row_plugin = key($row_plugins);
		if ($this -> options['row_plugin'] == '') {
			$this -> options['row_plugin'] = $default_row_plugin;
		}

	}

	/**
	 * Return the type of styles we require.
	 */
	function get_style_type() {
		return 'uconnect-export';
	}

	/**
	 * Return the sections that can be defaultable.
	 */
	function defaultable_sections($section = NULL) {
		if (in_array($section, array(
			'style_plugin',
			'items_per_page',
			'offset',
			'use_pager',
			'pager_element',
		))) {
			return FALSE;
		}

		return parent::defaultable_sections($section);
	}

	/**
	 * Define the option for this view.
	 */
	function option_definition() {
		$options = parent::option_definition();

		$options['style_plugin']['default'] = 'views_uconnect_export_lar';
		$options['row_plugin']['default'] = 'lar';

		$options['items_per_page'] = array('default' => '0');
		if (isset($options['defaults']['default']['items_per_page'])) {
			$options['defaults']['default']['items_per_page'] = FALSE;
		}
		$options['displays'] = array('default' => array());
		$options['defaults']['fields']['hide_empty'] = array('default' => TRUE);
		$options['defaults']['hide_empty'] = array('default' => TRUE);
		// Overrides for standard stuff:
		$options['defaults']['default']['style_plugin'] = FALSE;
		$options['defaults']['default']['style_options'] = FALSE;
		$options['defaults']['default']['row_plugin'] = FALSE;
		$options['defaults']['default']['row_options'] = FALSE;
		

		return $options;
	}

	/**
	 * Provide the summary for page options in the views UI.
	 *
	 * This output is returned as an array.
	 */
	function options_summary(&$categories, &$options) {
		// It is very important to call the parent function here:
		parent::options_summary($categories, $options);

		$categories['page']['#title'] = t('LAR settings');

	}

	/**
	 * Provide the default form for setting options.
	 */
	function options_form(&$form, &$form_state) {
		// It is very important to call the parent function here:
		parent::options_form($form, $form_state);
	

	}

	/**
	 * Save the options from the options form.
	 */

	/**
	 * Execute this display handler.
	 *
	 */
	function execute() {
		$datestamp = (db_query("SELECT max(changed) FROM {node} ") -> fetchField())+7;
		$togmt = 60*60*7;
		$date_mod = $datestamp + $togmt;
		drupal_add_http_header('Content-Type', 'application/xml');
		$max_age = '2592000';
  		drupal_add_http_header('Cache-Control', 'public, max-age=' . $max_age);
		$expires = date('D, j M Y h:i:s ',$date_mod + $max_age);
  		drupal_add_http_header('Expires',  $expires.'GMT');
		
  		drupal_add_http_header('Last-Modified',  date('D, j M Y h:i:s ',$date_mod).'GMT');
		drupal_add_http_header('X-Microcachable',0);
		
		print $this -> view -> render();

	}

	/**
	 * Render the display.
	 */
	function render() {
		
		return $this -> view -> style_plugin -> render();
	}

	function query() {
 		$this->view->query->add_field('node', 'nid'); 
 		$this->view->query->add_field('node', 'changed');
      	$this->view->query->add_orderby('node', 'nid', 'asc');
		return parent::query();

	}

	function preview() {
		if (!empty($this -> view -> live_preview)) {
			return '<pre>' . check_plain($this -> view -> render()) . '</pre>';
		}
		return $this -> view -> render();
	}

}
