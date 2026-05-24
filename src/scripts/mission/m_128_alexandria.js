log_info("akhenaten: mission 128 alexandria started")

mission128 { // Alexandria, custom mission
	start_message : "message_alexandria"
    selection_title : "Alexandria"
    selection_subtitle : "The Alexandria Library"
    selection_text : "Alexandria is a city of great importance to Egypt. It is the capital of Egypt and the center of the Egyptian civilization."

	env {
		has_animals : true
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
		hide_nilometer : true
	}
	religion_enabled : true
	hide_won_screen : false
	player_rank : 0

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD
	]

	win_criteria {
		housing_count {enabled : true, goal : 6 }
		housing_level {enabled : true, goal : 2 }
	}

	vars {

	}
}
