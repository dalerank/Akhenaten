log_info("akhenaten: mission 6 behdet started")

mission6 = { // Behdet
	start_message : 245, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	player_rank : 1
	next_mission : 8
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
	    has_animals : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	buildings [   
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_WORK_CAMP, BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_FERRY, BUILDING_DOCK,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
				]
	stages {
	}

	enable_scenario_events : false,
	events [
		{
			time { year : 2684, month : 1 }
			resource : "pottery",
			amount { value : 1400 },
			deadline : 9,
		}

		{
			time { year : 2683, month : 1 }
			resource : "beer",
			amount { value : 1100 },
			deadline : 12,
		}
	]

	cities [
		{
			name : "Byblos",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name: "Perwadjyt",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name: "Men-nefer",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		}
	]

	choice_background {pack:PACK_UNLOADED, id:12},
	choice_image1 {pack:PACK_UNLOADED, id:13, offset:0},
	choice_image1_pos [192, 144],
	choice_title [144, 19],
	choice [
		{
			name : "Abydos",
			id : 6,
			image {pack:PACK_UNLOADED, id:20, offset:0},
			tooltip [144, 20],
			pos [620, 420],
		}

		{
			name : "Behdet",
			id : 7,
			image {pack:PACK_UNLOADED, id:20},
			tooltip [144, 21],
			pos [640, 480],
		}
	],
}