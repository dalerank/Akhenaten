log_info("akhenaten: mission 1 started")

mission1 {
	start_message : "message_gold_and_crime"
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 0,
	hide_won_screen : true,
	initial_funds [7500, 5000, 3750, 2500, 2000],
	rescue_loans [7500, 5000, 3750, 2500, 2000],

	buildings  [
					BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
					BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_WATER_SUPPLY,
					BUILDING_GOLD_MINE, BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				]
	stages {
		tutorial_gods [BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE],
		tutorial_entertainment [BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL]
	}

	vars {
		gold_mined : 500
		victory_last_action_delay : 4
		nogranary_populcation_cap : 150
	}
}