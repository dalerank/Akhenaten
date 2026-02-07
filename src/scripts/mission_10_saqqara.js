log_info("akhenaten: mission 10 saqqara started")

mission10 { // Saqqara
	start_message : "message_innovations"
	player_rank : 1
	next_mission : 11
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13, offset:0}
	choice_image1_pos [192, 144]
	choice_title [144, 22]
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		bricks: { type:RESOURCE_BRICKS, allow: true},
	}

	env {
		has_animals : true
	    hide_nilometer : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	buildings [
                BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
				BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
                BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY,
				BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
				BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
				BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
				BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_BRICKS_WORKSHOP,
                BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_WEAVER_WORKSHOP,
				BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
                BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET,
				BUILDING_POMEGRANATES_MEADOW_FARM,
				BUILDING_STONE_QUARRY, BUILDING_GOLD_MINE,
				BUILDING_FERRY,
				BUILDING_MEDIUM_STEPPED_PYRAMID, BUILDING_SMALL_MASTABA,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	win_criteria {
		population {enabled : true, goal : 3500 }
		culture    {enabled : true, goal : 25 }
		prosperity {enabled : true, goal : 15 }
		monuments  {enabled : true, goal : 19 }
        kingdom    {enabled : true, goal : 50 }
	}

	cities [
		{
			name : "Nubt"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell Ebony
            // buys linen, jewelry
		}

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
            sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
            buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
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
            sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
            buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Abu"
            is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sell chickpeas, pottery, papyrus
            // buys bricks, barley, beer, jewelry
		}

        {
			name : "Selima Oasis"
            is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
            buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_COPPER, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
		}
	]

	vars {
		pharaoh_requested_gamemeat : false
		pharaoh_requested_pomegranates : false
	}
}

[es=event_register_mission_animals, mission=mission10]
function mission10_register_animals(ev) {
	city.remove_animals()

	city.add_animals_point(0, /*x*/55, /*y*/75, FIGURE_OSTRICH, 5)
	city.set_animals_area(0, 16)

	city.add_animals_point(1, /*x*/85, /*y*/135, FIGURE_OSTRICH, 5)
	city.set_animals_area(1, 16)

	city.add_animals_point(1, /*x*/90, /*y*/155, FIGURE_HYENA, 5)
	city.set_animals_area(1, 16)
}

[es=event_advance_month, mission=mission10]
function mission10_pharaoh_requested1_gamemeat(ev) {
	if (mission.pharaoh_requested_gamemeat) {
		return
	}

	log_info("akhenaten: mission 10 saqqara:${ev.years_since_start}:${ev.month} pharaoh requested gamemeat", {ev:ev})
	if (ev.years_since_start < 2 && ev.month < 2) {
		return
	}

	mission.pharaoh_requested_gamemeat = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_GAMEMEAT, amount: 7, months_initial: 4 })
	request.execute()
}

[es=event_advance_month, mission=mission10]
function mission10_pharaoh_requested1_pomegranates(ev) {
	if (mission.pharaoh_requested_pomegranates) {
		return
	}

	log_info("akhenaten: mission 10 saqqara:${ev.years_since_start}:${ev.month} pharaoh requested pomegranates", {ev:ev})
	if (ev.years_since_start < 3 && ev.month < 3) {
		return
	}

	mission.pharaoh_requested_pomegranates = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_POMEGRANATES, amount: 11, months_initial: 4 })
	request.execute()
}