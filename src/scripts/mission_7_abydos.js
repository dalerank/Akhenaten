log_info("akhenaten: mission 7 abydos started")

mission7 { // Abydos
	start_message : "message_soldiers_and_forts"
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1
	next_mission : 8
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_WORK_CAMP, BUILDING_FLAX_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_FERRY,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_DOCK,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS,
					BUILDING_BRICKLAYERS_GUILD,
					BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, 
					BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE
				]
	stages {
	}

	enable_scenario_events : false
	events [
		{
			type: EVENT_TYPE_REQUEST
			time { year : 2684, month : 1 }
			resource : RESOURCE_POTTERY
			amount { value : 1400 }
			deadline : 9
		}

		{
			type: EVENT_TYPE_INVASION
			time { year : 2670, month : 2 }
		}

		{
			type: "pharaoh_gift" //EVENT_TYPE_INVASION,
			time { year : 2670, month : 8 }
		}
	]

	cities [
		{
			name : "Byblos"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}
		{
			name : "Perwadjyt"
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		}
	]

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13, offset:0}
	choice_image1_pos [192, 144]
	choice_title [144, 19]
	choice [
		{
			name : "Abydos"
			id : 6
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 20]
			pos [620, 420]
		}

		{
			name : "Behdet"
			id : 7
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 21]
			pos [640, 480]
		}
	]
}