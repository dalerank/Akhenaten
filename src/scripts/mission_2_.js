log_info("akhenaten: mission 2 started")

mission2 {
	start_message : "message_farming_along_the_nile"
	env {
		has_animals : true		
	    gods_least_mood : 50
	}
	player_rank : 0,
	initial_funds [7500, 5000, 3750, 2500, 2000],
	rescue_loans [7500, 5000, 3750, 2500, 2000],
	house_tax_multipliers [300, 200, 150, 100, 75],

	buildings [
					BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE, BUILDING_WATER_SUPPLY,
					BUILDING_FIGS_FARM, BUILDING_WORK_CAMP, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BAZAAR, BUILDING_GRANARY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_FESTIVAL_SQUARE
				]
	stages {
		tutorial_industry { buildings: [BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_STORAGE_YARD] }
		tutorial_health { buildings: [BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN] }
		tutorial_gardens { buildings: [BUILDING_ROADBLOCK, BUILDING_FERRY, BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA] },
	}

	vars {
		figs_stored : 800
		pottery_step1_stored : 100
		pottery_step1_population_cap : 500
		pottery_step2_stored : 200
		victory_last_action_delay : 3
	}

	marshland_grow : default_marshland_grow
	tree_grow : default_tree_grow
}