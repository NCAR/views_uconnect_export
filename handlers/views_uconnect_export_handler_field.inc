<?php
/**
 * A handler to display dates as just the time if today, otherwise as time and date.
 *
 * @ingroup views_field_handlers
 */
class views_uconnect_export_handler_field extends views_handler_field {

	function option_definition() {
		$options = parent::option_definition();
		return $options;
	}

}
