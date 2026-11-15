// Custom mission 134 — Default (Cleopatra map Default.map). Rank 0 (Village Elder).
//
// Goals:     house count 6, housing level 2.
// Start:     funds 3750, rescue loan 3750 (normal difficulty).
// Gods:      none (no temples allowed).
// Monuments: none.
// Trade:     no empire cities configured.
// Enemies:   none.
// Timeline:  no events.
//
// Notes for developers: a placeholder copied from the sandbox stub — only houses and roads can be built,
// and "message_default" has no entry in the game messages.

mission134 { // Default, custom mission
	start_message : "message_default"
    selection_title : "Default"
    selection_text : "This is a default mission. You can build whatever you want."

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