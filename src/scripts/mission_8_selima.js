log_info("akhenaten: mission 8 selima started")

mission8 { // Selima
	start_message : 149, //The finer things, 247 = 146 + 99 - 1
	player_rank : 1
	next_mission : 10
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13, offset:0}
	choice_image1_pos [192, 144]
	choice_title [144, 22]
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true		
	    hide_nilometer : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	buildings [
                BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
				BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
                BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
				BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
                BUILDING_WOOD_CUTTERS, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP,
				BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
                BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	stages { // 
	}

	win_criteria {
		population {enabled : true, goal : 2500 }
		culture    {enabled : true, goal : 25 }
		prosperity {enabled : true, goal : 25 }
		monuments  {enabled : true, goal : 18 }
	}

    enable_scenario_events : true,
	events [
		{
            tag_id : 1
			type: EVENT_TYPE_REQUEST
			year : 2649
			month : 1
			resource : RESOURCE_LUXURY_GOODS
			amount : 2 // * 100
			months_initial : 4
		}
    ]

    invasion_points_land [
        [30, 26]
    ]

    cities [
		{
			name : "Kerma"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell Ebony
            // buys linen, jewelry
		}

		{
			name : "Behdet"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell fish, clay, pottery, beer, flax, papyrus, granite
            // buys bricks, linen, gems, jewelry, tibmer
		}

        {
			name : "Abedju"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell fish, grain, beer, linen, limestone
            // buys gamemeat, clay, bricks, wood, papyrus, sunstone, limestone
		}

        {
			name : "Men-nefer"
            is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell chickpeas, pottery, papyrus
            // buys bricks, barley, beer, jewelry 
		}

        {
			name : "Timna"
            is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell weapons, clay, pottery, copper
            // buys fish, beer, linen, papyrus
		}
	]

	choice [
		{
			name : "Selima"
			id : 8
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 23]
			pos [620, 420]
		}

		{
			name : "Abu"
			id : 9
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 24]
			pos [640, 480]
		}
	]
}