log_info("akhenaten: mission 13 buhen started")

mission13 { // Buhen — Expansion to Nubia
	start_message : "message_mission_buhen"
	selection_title : "Buhen"
	player_rank : 2

	// Buhen and South Dahshur are a choice pair (picked at the end of mission 11/12).
	// Both converge on North Dahshur (15) — linear next_mission, no choice[] here.
	// NOTE: mission 15 is not scripted yet; until it exists the campaign ends after
	// this mission (mission_end_compute_next returns -1 for an invalid next id).
	next_mission : 15

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
		briefing : "Voice/Mission/213_mission.mp3"
		victory : "Voice/Mission/213_victory.mp3"
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
				BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
				BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 3000, culture 25, prosperity 25, monument 9 (small obelisk), kingdom 75.
	// The small obelisk (BUILDING_SMALL_OBELISK, granite) is not implemented yet (task C7).
	// A small mastaba (weight 2) yields the same rating: 6.32*sqrt(2)+0.5 = 9, so the
	// original monument goal 9 is kept and a small mastaba stands in for the obelisk.
	// TODO(C7): add BUILDING_SMALL_OBELISK to the buildings list (granite imported from
	// Abu) and, if desired, drop the mastaba stand-in.
	win_criteria {
		population {enabled : true, goal : 3000 }
		culture    {enabled : true, goal : 25 }
		prosperity {enabled : true, goal : 25 }
		monuments  {enabled : true, goal : 9 }
		kingdom    {enabled : true, goal : 75 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. Known from the briefing
	// (message_history_buhen): no granite this far south -> import from Abu; copper from
	// Enkomi (Cyprus) and, more cheaply, from Serabit Khadim (erratic supply).
	cities [
		{
			name : "Abu"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRANITE, RESOURCE_POTTERY ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Enkomi"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_BEER, RESOURCE_PAPYRUS ]
		}

		{
			name : "Serabit Khadim"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_COPPER, RESOURCE_GEMS ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_GRAIN ]
		}
	]

	vars {
		pharaoh_requested_limestone : false
		pharaoh_requested_beer : false
		pharaoh_requested_stone : false
		distant_battle_requested : false
		nubian_invasion_1_started : false
		nubian_invasion_2_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission13]
function mission13_on_start(ev) {
	mission_show_start_message(mission, "message_mission_buhen")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests support his pyramid at Dahshur. Order from the walkthrough
// (limestone, beer, plain stone); years and amounts are placeholders — verify vs .pak.

[es=event_advance_month, mission=mission13]
function mission13_pharaoh_request_limestone(ev) {
	if (mission.pharaoh_requested_limestone) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_limestone = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_LIMESTONE, amount: 12, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission13]
function mission13_pharaoh_request_beer(ev) {
	if (mission.pharaoh_requested_beer) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_beer = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_BEER, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission13]
function mission13_pharaoh_request_stone(ev) {
	if (mission.pharaoh_requested_stone) {
		return
	}

	if (ev.years_since_start < 5) {
		return
	}

	mission.pharaoh_requested_stone = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_STONE, amount: 15, months_initial: 12 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}

// First Nubian attack from the north-west (~year 3). ENEMY_8_NUBIAN.
[es=event_advance_month, mission=mission13]
function mission13_nubian_invasion_1(ev) {
	if (mission.nubian_invasion_1_started) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 3) {
		return
	}

	mission.nubian_invasion_1_started = true
	log_info("akhenaten: mission 13 buhen:${ev.years_since_start}:${ev.month} nubian invasion 1", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_8_NUBIAN, size: 12, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}

// Distant-battle request to defend another Egyptian city (walkthrough: 2571 BC).
[es=event_advance_month, mission=mission13]
function mission13_distant_battle(ev) {
	if (mission.distant_battle_requested) {
		return
	}

	if (ev.years_since_start < 4 || ev.month < 1) {
		return
	}

	mission.distant_battle_requested = true
	log_info("akhenaten: mission 13 buhen:${ev.years_since_start}:${ev.month} distant battle request", {ev:ev})

	var battle = city.create_distant_battle({ tag_id: 4, city: "Kerma" })
	battle.set_location_fields(-1, -1, -1, -1)
	battle.set_image("pharaoh_unloaded/dialougedrawing_00012")
	battle.set_param("months_initial", 14)
	battle.set_param("amount", 2)
	battle.set_reasons(PHRASE_distant_battle_initial_announcement_P, -1, -1, -1)
	battle.execute()
}

// Second, larger Nubian attack later in the mission (~year 6).
[es=event_advance_month, mission=mission13]
function mission13_nubian_invasion_2(ev) {
	if (mission.nubian_invasion_2_started) {
		return
	}

	if (ev.years_since_start < 6 || ev.month < 4) {
		return
	}

	mission.nubian_invasion_2_started = true
	log_info("akhenaten: mission 13 buhen:${ev.years_since_start}:${ev.month} nubian invasion 2", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 1, enemy: ENEMY_8_NUBIAN, size: 16, tilex: -1, tiley: -1, want_destroy_buildings: 12 })
}
