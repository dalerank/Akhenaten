log_info("akhenaten: mission 16 iunet started")

mission16 { // Iunet (Dendera) — The Defense of Egypt
	start_message : "message_mission_dendera"
	selection_title : "Iunet"
	player_rank : 3

	// Iunet (16) and On (17) are a choice pair; both converge on Rostja (18).
	next_mission : 18

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		bricks: { type:RESOURCE_BRICKS, allow: true},
	}

	env {
		has_animals : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/216_mission.mp3"
		victory : "Voice/Mission/216_victory.mp3"
	}

	buildings [
                BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
				BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
                BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY,
				BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
				BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
				BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
				BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
                BUILDING_BRICKS_WORKSHOP, BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP,
				BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_WEAVER_WORKSHOP,
				BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
				BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
				BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
				BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
                BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
				BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM,
				BUILDING_FISHING_WHARF, BUILDING_CATTLE_RANCH,
				BUILDING_STONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_GOLD_MINE, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
				BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 4000, culture 30, prosperity 30, monument 9 (1 small mastaba), kingdom 65.
	// The small mastaba is implemented and yields rating 9 (2.25*2+4.5, additive rating,
	// see city/monuments.js) — the goal matches the original, no stand-in needed.
	win_criteria {
		population {enabled : true, goal : 4000 }
		culture    {enabled : true, goal : 30 }
		prosperity {enabled : true, goal : 30 }
		monuments  {enabled : true, goal : 9 }
		kingdom    {enabled : true, goal : 65 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. From the briefing
	// (message_history_iunet): routes open to Abu and Men-nefer; ivory reaches Egypt as
	// luxury goods via Byblos (no dedicated ivory resource in this build). Export copper,
	// granite, gold.
	cities [
		{
			name : "Abu"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_CHICKPEAS ]
			buys [ RESOURCE_GRANITE, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_BEER ]
			buys [ RESOURCE_GRANITE, RESOURCE_GOLD, RESOURCE_POTTERY ]
		}

		{
			name : "Byblos"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_GOLD, RESOURCE_GRANITE, RESOURCE_PAPYRUS ]
		}
	]

	vars {
		pharaoh_requested_fish : false
		pharaoh_requested_meat : false
		pharaoh_requested_pottery : false
		kushite_invasion_1_started : false
		kushite_invasion_2_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission16]
function mission16_on_start(ev) {
	mission_show_start_message(mission, "message_mission_dendera")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh Khufu's requests (walkthrough: fish, meat, pottery). Years/amounts placeholder.

[es=event_advance_month, mission=mission16]
function mission16_pharaoh_request_fish(ev) {
	if (mission.pharaoh_requested_fish) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_fish = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_FISH, amount: 12, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission16]
function mission16_pharaoh_request_meat(ev) {
	if (mission.pharaoh_requested_meat) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_meat = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_MEAT, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission16]
function mission16_pharaoh_request_pottery(ev) {
	if (mission.pharaoh_requested_pottery) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_pottery = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_POTTERY, amount: 12, months_initial: 12 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}

// Kushite attacks (walkthrough: they sail in from the east). Enemy naval transports are
// not implemented yet (task E3), so these are scripted as land armies from the default
// entry point as a proxy — TODO(E3): make these true naval landings from the east.
[es=event_advance_month, mission=mission16]
function mission16_kushite_invasion_1(ev) {
	if (mission.kushite_invasion_1_started) {
		return
	}

	if (ev.years_since_start < 2 || ev.month < 8) {
		return
	}

	mission.kushite_invasion_1_started = true
	log_info("akhenaten: mission 16 iunet:${ev.years_since_start}:${ev.month} kushite invasion 1", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_6_KUSHITE, size: 12, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}

[es=event_advance_month, mission=mission16]
function mission16_kushite_invasion_2(ev) {
	if (mission.kushite_invasion_2_started) {
		return
	}

	if (ev.years_since_start < 5 || ev.month < 4) {
		return
	}

	mission.kushite_invasion_2_started = true
	log_info("akhenaten: mission 16 iunet:${ev.years_since_start}:${ev.month} kushite invasion 2", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 1, enemy: ENEMY_6_KUSHITE, size: 16, tilex: -1, tiley: -1, want_destroy_buildings: 12 })
}
