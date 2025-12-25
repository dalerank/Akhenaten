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

	win_criteria {
		population {enabled : true, goal : 2500 }
		culture    {enabled : true, goal : 25 }
		prosperity {enabled : true, goal : 25 }
		monuments  {enabled : true, goal : 18 }
	}

    enable_scenario_events : true


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

	vars {
		pharaoh_requested_luxury_goods : false
		random_trade_city_under_siege : false
		foreign_army_attack_warning_shown : false
		foreign_army_attacked_city : false
		distant_battle_requested : false
	}
}

[event=event_register_mission_animals, mission=mission8]
function mission8_register_animals(ev) {
	city.remove_animals()

	city.add_animals_point(0, /*x*/70, /*y*/50, FIGURE_OSTRICH, 5)
	city.set_animals_area(0, 16)

	city.add_animals_point(1, /*x*/45, /*y*/80, FIGURE_OSTRICH, 5)
	city.set_animals_area(1, 16)
}

[event=event_advance_month, mission=mission8]
function mission8_pharaoh_requested1_luxury_goods(ev) {
	if (mission.pharaoh_requested_luxury_goods) {
		return
	}

	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} pharaoh requested luxury goods", {ev:ev})
	if (ev.years_since_start < 2 && ev.month < 2) {
		return
	}

	mission.pharaoh_requested_luxury_goods = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_LUXURY_GOODS, amount: 2, months_initial: 4 })
	request.execute()
}

[event=event_advance_month, mission=mission8]
function mission8_pharaoh_requested2_luxury_goods(ev) {
	if (mission.pharaoh_requested_luxury_goods) {
		return
	}

	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} pharaoh requested luxury goods", {ev:ev})
	if (ev.years_since_start < 4 && ev.month < 4) {
		return
	}

	mission.pharaoh_requested_luxury_goods = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_LUXURY_GOODS, amount: 2, months_initial: 4 })
	request.execute()
}

[event=event_advance_month, mission=mission8]
function mission8_random_trade_city_under_siege(ev) {
	if (mission.random_trade_city_under_siege) {
		return
	}

	if (ev.years_since_start < 2 && ev.month < 2) {
		return
	}

	mission.random_trade_city_under_siege = true

	var request = city.create_trade_city_under_siege(/*tag_id*/2, /*months_initial*/12)
	request.set_reasons(PHRASE_trade_city_siege_no_reason_A, PHRASE_trade_city_siege_no_reason_B, PHRASE_trade_city_siege_no_reason_C, -1)
	request.execute()
}

[event=event_advance_month, mission=mission8]
function mission8_foreign_army_attack_warning(ev) {
	if (mission.foreign_army_attack_warning_shown) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 5) {
		return
	}

	mission.foreign_army_attack_warning_shown = true

	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} foreign army attack warning", {ev:ev})

	var request = city.create_foreign_army_attack_warning({ tag_id: 4, sender_faction: ENEMY_7_LIBIAN })
	request.set_location_fields(-1, -1, -1, -1)
	request.set_image("pharaoh_unloaded/dialougedrawing_00012")
	request.set_reasons(PHRASE_foreign_army_attacks_you_1month_Warning, PHRASE_foreign_army_attacks_you_no_reason_A, -1, -1)
	request.execute()
}

[event=event_advance_month, mission=mission8]
function mission8_foreign_army_attack(ev) {	
	if (mission.foreign_army_attacked_city) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 6) {
		return
	}

	mission.foreign_army_attacked_city = true
	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} foreign army attack", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_7_LIBIAN, size: 10, tilex: 30, tiley: 26, want_destroy_buildings: 10 })

	var event = city.create_foreign_army_attack_warning({ tag_id: 5, sender_faction: ENEMY_7_LIBIAN })
	event.set_location_fields(-1, -1, -1, -1)
	event.set_image("pharaoh_unloaded/dialougedrawing_00012")
	event.set_reasons(PHRASE_foreign_army_attacks_you_city_attacked_alert, PHRASE_foreign_army_attacks_you_no_reason_A, -1, -1)
	event.execute()
}

[event=event_advance_month, mission=mission8]
function mission8_distant_battle_request(ev) {
	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} distant battle request", {ev:ev})
	if (mission.distant_battle_requested) {
		return
	}

	if (ev.years_since_start < 5 || ev.month < 1) {
		return
	}

	mission.distant_battle_requested = true
	log_info("akhenaten: mission 8 selima:${ev.years_since_start}:${ev.month} distant battle request", {ev:ev})

	var battle = city.create_distant_battle({ tag_id: 5, city: "Kerma" })
	battle.set_location_fields(-1, -1, -1, -1)
	battle.set_image("pharaoh_unloaded/dialougedrawing_00012")
	battle.set_param("months_initial", 14)
	battle.set_reasons(PHRASE_distant_battle_initial_announcement_P, -1, -1, -1)
	battle.execute()
}