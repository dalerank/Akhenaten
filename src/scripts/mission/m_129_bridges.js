log_info("akhenaten: mission 129 bridges started")

mission129 { // Bridges, custom mission
	start_message : "message_bridges"
    selection_title : "Bridges"
    selection_text : "Keep an eye on the clock, as Pharaoh will send his hordes if you don't complete his obelisk in time. The region has all the resources needed to complete the monument, and you won't be hounded by any outside distractions like requests for items.  Successful cities will have carefully planned roads and will make skillful use of the available land."

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
