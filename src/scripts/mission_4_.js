log_info("akhenaten: mission 4 started")

mission4 {
	start_message : "message_farming_along_the_nile"
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings  [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_MUD_WALL,

					BUILDING_BULLFIGHT_SCHOOL, BUILDING_MUD_GATEHOUSE, BUILDING_TOWER_GATEHOUSE, BUILDING_MUD_TOWER,
				]
	stages {
		tutorial_education { buildings: [BUILDING_REED_GATHERER, BUILDING_PAPYRUS_WORKSHOP, BUILDING_SCRIBAL_SCHOOL] }
		tutorial_trading { buildings: [BUILDING_DOCK] }
		tutorial_monuments { buildings: [BUILDING_BRICKLAYERS_GUILD, BUILDING_SMALL_MASTABA] }
	}

	cities [
		{
			name : "Nekhen"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name : "Perwadjyt"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}
	]

	vars {
		spacious_apartment_built : 1
		papyrus_stored : 100
		victory_last_action_delay : 3
	}
}
