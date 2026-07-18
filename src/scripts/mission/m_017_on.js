log_info("akhenaten: mission 17 on started")

mission17 { // On (Heliopolis) — Ivory from the East
	start_message : "message_mission_heliopolis"
	selection_title : "On"
	player_rank : 3

	// On (17) and Iunet (16) are a choice pair; both converge on Rostja (18).
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
		briefing : "Voice/Mission/217_mission.mp3"
		victory : "Voice/Mission/217_victory.mp3"
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
				BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS,
                BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
				BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
				BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_FISHING_WHARF,
				BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
				BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 4000, culture 40, prosperity 35, monument 18 (3 small mastabas), kingdom 60.
	// NOTE: the reimplemented monument rating formula (6.32*sqrt(sum)+0.5 in
	// city/monuments.js) does not reproduce the original per-monument totals for multiple
	// monuments — 3 small mastabas (weight 2 each, sum 6) yield 15, not the original 18.
	// Temporary monument goal 15 so the intended "3 small mastabas" wins.
	// TODO: reconcile MONUMENT_WEIGHTS / rating formula with original values, then restore 18.
	win_criteria {
		population {enabled : true, goal : 4000 }
		culture    {enabled : true, goal : 40 }
		prosperity {enabled : true, goal : 35 }
		monuments  {enabled : true, goal : 15 }
		kingdom    {enabled : true, goal : 60 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. From the briefing
	// (message_history_on): fine white limestone is the local export; ivory reaches Egypt
	// as luxury goods via Byblos. Export pottery, papyrus, limestone.
	cities [
		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_REEDS, RESOURCE_BEER ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
		}

		{
			name : "Behdet"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_CLAY ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Byblos"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_PAPYRUS, RESOURCE_POTTERY ]
		}
	]

	vars {
		pharaoh_requested_limestone : false
		pharaoh_requested_gamemeat : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission17]
function mission17_on_start(ev) {
	mission_show_start_message(mission, "message_mission_heliopolis")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests (walkthrough: limestone ~26 blocks early, game meat in year 3).
// Amounts/years placeholder — verify vs .pak.

[es=event_advance_month, mission=mission17]
function mission17_pharaoh_request_limestone(ev) {
	if (mission.pharaoh_requested_limestone) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_limestone = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_LIMESTONE, amount: 26, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission17]
function mission17_pharaoh_request_gamemeat(ev) {
	if (mission.pharaoh_requested_gamemeat) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_gamemeat = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_GAMEMEAT, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}
