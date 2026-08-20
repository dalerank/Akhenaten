log_info("akhenaten: invasions started")

invasions = {
	min_invasion_amount : 1
	max_invasion_amount : 150
}

/** Keep in sync with invasion_data_t::warnings size */
invasions.warning_slots = 101

invasions.get_warning = function(index) {
	return new InvasionWarning(index)
}
