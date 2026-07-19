log_info("akhenaten: mission 15 north dahshur started")

mission15 { // North Dahshur — The True Pyramid
	start_message : "message_mission_north_dahshur"
	selection_title : "North Dahshur"
	player_rank : 2

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 34]

	// After North Dahshur the player chooses the next pair: Iunet (16) / On (17).
	// Both of those converge on Rostja (18). NOTE: 16/17 are not scripted yet, so the
	// choice targets are currently dead ends (see task B5 — choice[] targets are not
	// validated). Tooltip/text ids [144, 35/36] are placeholders — verify vs original.
	choice [
		{
			name : "Iunet"
			id : 16
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 35]
			pos [620, 420]
		}

		{
			name : "On"
			id : 17
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 36]
			pos [640, 480]
		}
	]

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
		briefing : "Voice/Mission/215_mission.mp3"
		victory : "Voice/Mission/215_victory.mp3"
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
                BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
				BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM,
				BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 3000, culture 20, prosperity 30, monument 32 (1 large true pyramid), kingdom 55.
	// The true (smooth) pyramid (BUILDING_LARGE_PYRAMID = 255) is not implemented yet (task C3).
	// Stand-in: require BOTH stepped pyramids — small (8) + medium (16) = sum 24 ->
	// 2.25*24+4.5 = 58 (additive rating, see city/monuments.js). A bigger build than
	// mission 14's single medium stepped, matching "the largest pyramid yet". Temporary
	// monument goal 58 (needs both stepped pyramids finished).
	// TODO(C3/F3): restore goal 32 and swap the two stepped pyramids for
	// BUILDING_LARGE_PYRAMID once true pyramids and calibrated weights land.
	win_criteria {
		population {enabled : true, goal : 3000 }
		culture    {enabled : true, goal : 20 }
		prosperity {enabled : true, goal : 30 }
		monuments  {enabled : true, goal : 58 }
		kingdom    {enabled : true, goal : 55 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. From the briefing
	// (message_history_north_dahshur): wood (timber) is imported from Byblos for the
	// construction ramps. Byblos is overseas (normally sea trade); this inland map is
	// served by land caravan here (is_sea_trade:false) so timber is reachable without
	// a dock — verify against the original map.
	cities [
		{
			name : "Byblos"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_TIMBER ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_BEER ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
		}

		{
			name : "Abu"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_CHICKPEAS ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
		}
	]

	vars {
		pharaoh_requested_grain : false
		pharaoh_requested_straw : false
		pharaoh_requested_barley : false
		pharaoh_requested_limestone : false
		libyan_invasion_started : false
		bedouin_invasion_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission15]
function mission15_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_BARBARIAN)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	mission_show_start_message(mission, "message_mission_north_dahshur")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests (walkthrough order: grain, straw, barley, limestone). Years and
// amounts are placeholders — verify against the original .pak.

[es=event_advance_month, mission=mission15]
function mission15_pharaoh_request_grain(ev) {
	if (mission.pharaoh_requested_grain) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_grain = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_GRAIN, amount: 18, months_initial: 18 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission15]
function mission15_pharaoh_request_straw(ev) {
	if (mission.pharaoh_requested_straw) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_straw = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_STRAW, amount: 15, months_initial: 18 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission15]
function mission15_pharaoh_request_barley(ev) {
	if (mission.pharaoh_requested_barley) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_barley = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_BARLEY, amount: 14, months_initial: 18 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}

[es=event_advance_month, mission=mission15]
function mission15_pharaoh_request_limestone(ev) {
	if (mission.pharaoh_requested_limestone) {
		return
	}

	if (ev.years_since_start < 5) {
		return
	}

	mission.pharaoh_requested_limestone = true
	var request = city.create_good_request({ tag_id: 4, resource: RESOURCE_LIMESTONE, amount: 24, months_initial: 18 })
	city.create_chain_event({ tag_id: 401, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 402, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(401)
	request.set_refusal_action_tag(402)
	request.execute()
}

// Recurring raids in the original: Libyans from the north-west, Bedouins from the west.
// Scripted here as one representative wave each; timing/size are placeholders.
[es=event_advance_month, mission=mission15]
function mission15_libyan_invasion(ev) {
	if (mission.libyan_invasion_started) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 6) {
		return
	}

	mission.libyan_invasion_started = true
	log_info("akhenaten: mission 15 north dahshur:${ev.years_since_start}:${ev.month} libyan invasion", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_7_LIBIAN, size: 14, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}

[es=event_advance_month, mission=mission15]
function mission15_bedouin_invasion(ev) {
	if (mission.bedouin_invasion_started) {
		return
	}

	if (ev.years_since_start < 5 || ev.month < 11) {
		return
	}

	mission.bedouin_invasion_started = true
	log_info("akhenaten: mission 15 north dahshur:${ev.years_since_start}:${ev.month} bedouin invasion", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 1, enemy: ENEMY_0_BARBARIAN, size: 12, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}
