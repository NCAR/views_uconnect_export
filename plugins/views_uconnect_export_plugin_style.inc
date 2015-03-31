<?php
class views_uconnect_export_plugin_style extends views_plugin_style {
  function render() {
    $content = '';
   
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    $records   = $this->render_content();
   	
    // need to get headers and footers
	$header = theme('views_uconnect_export_header',array('view' => $this->view));
	$footer = theme('views_uconnect_export_footer');
    return theme('views_uconnect_export_response', array('header'=>$header, 'footer'=>$footer, 'records' => $records));
  }

  function render_content() {
    return $this->render_records();
  }

  /**
   * Provide a full list of possible theme templates used by this style.
  **/
  function theme_functions($hook = NULL) {
    if (is_null($hook)) {
      $hook = $this->definition['theme'];
    }
    return views_theme_functions($hook, $this->view, $this->display);
  }
}
