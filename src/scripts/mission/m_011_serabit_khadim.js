log_info("akhenaten: mission 11 serabit khadim started")

mission11 { // Serabit Khadim
	start_message : "message_mission_serabit_khadim"
	selection_title : "Serabit Khadim"
	player_rank : 1

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 31]

	choice [
		{
			name : "Buhen"
			id : 13
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 32]
			pos [620, 420]
		}

		{
			name : "Dahshur"
			id : 14
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 33]
			pos [640, 480]
		}
	]

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
	    hide_nilometer : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/211_mission.mp3"
		victory : "Voice/Mission/211_victory.mp3"
	}

	buildings [
                BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
				BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
                BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
				BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
				BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
                BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
				BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS,
                BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
				BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
				BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
			  ]

	// Goals match Pharaoh walkthroughs (Pharaoh Heaven, Impressions wiki):
	// pop 2000, kingdom 80; no culture, prosperity, or monument rating goals.
	win_criteria {
		population {enabled : true, goal : 2000 }
		culture    {enabled : false }
		prosperity {enabled : false }
		monuments  {enabled : false }
		kingdom    {enabled : true, goal : 80 }
	}

	enable_scenario_events : true

	cities [
		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sells chickpeas, pottery, papyrus
            // buys bricks, barley, beer, luxury goods
		}

		{
			name : "Kebet"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            // sells fish, reeds, clay
		}

		{
			name : "Abu"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
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
			name : "Selima Oasis"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
            buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_COPPER, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
		}
	]

	vars {
		pharaoh_requested_copper : false
		pharaoh_requested_gems : false
		pharaoh_requested_weapons : false
		pharaoh_requested_luxury_goods : false
		bedouin_invasion_started : false
		canaanite_invasion_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission11]
function mission11_on_start(ev) {
	mission_show_start_message(mission, "message_mission_serabit_khadim")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

[es=(city_animals, create_herds), mission=mission11]
function mission11_register_animals(ev) {
	city.remove_animals()

	city.add_animals_point(0, /*x*/55, /*y*/75, FIGURE_OSTRICH, 5)
	city.set_animals_area(0, 16)

	city.add_animals_point(1, /*x*/85, /*y*/135, FIGURE_OSTRICH, 5)
	city.set_animals_area(1, 16)
}

[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_copper(ev) {
	if (mission.pharaoh_requested_copper) {
		return
	}

	if (ev.years_since_start < 1) {
		return
	}

	mission.pharaoh_requested_copper = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_COPPER, amount: 8, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_gems(ev) {
	if (mission.pharaoh_requested_gems) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_gems = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_GEMS, amount: 6, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_weapons(ev) {
	if (mission.pharaoh_requested_weapons) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_weapons = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_WEAPONS, amount: 8, months_initial: 12 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}

[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_luxury_goods(ev) {
	if (mission.pharaoh_requested_luxury_goods) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_luxury_goods = true
	var request = city.create_good_request({ tag_id: 4, resource: RESOURCE_LUXURY_GOODS, amount: 4, months_initial: 12 })
	city.create_chain_event({ tag_id: 401, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 402, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(401)
	request.set_refusal_action_tag(402)
	request.execute()
}

// First Bedouin attack ~year 2 (Pharaoh Heaven walkthrough).
[es=event_advance_month, mission=mission11]
function mission11_bedouin_invasion(ev) {
	if (mission.bedouin_invasion_started) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.bedouin_invasion_started = true
	log_info("akhenaten: mission 11 serabit khadim:${ev.years_since_start}:${ev.month} bedouin invasion", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_0_BARBARIAN, size: 8, tilex: -1, tiley: -1, want_destroy_buildings: 8 })
}

// Canaanite attacks follow Bedouin raids (walkthrough: SW, north, east).
[es=event_advance_month, mission=mission11]
function mission11_canaanite_invasion(ev) {
	if (mission.canaanite_invasion_started) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 6) {
		return
	}

	mission.canaanite_invasion_started = true
	log_info("akhenaten: mission 11 serabit khadim:${ev.years_since_start}:${ev.month} canaanite invasion", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 1, enemy: ENEMY_2_CANAANITE, size: 10, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}
