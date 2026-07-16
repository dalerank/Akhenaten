log_info("akhenaten: mission 12 meidum started")

mission12 { // Meidum
	start_message : "message_mission_meidum"
	selection_title : "Meidum"
	player_rank : 1

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 31]

	// Same post-victory fork as mission 11: both 11 and 12 lead to Buhen/Dahshur.
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

	init_resources : {
		bricks: { type:RESOURCE_BRICKS, allow: true},
	}

	env {
		has_animals : true
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/212_mission.mp3"
		victory : "Voice/Mission/212_victory.mp3"
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
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
				BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
                BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
				BUILDING_STONE_QUARRY, BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_WOOD_CUTTERS,
				BUILDING_FERRY,
				BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 3000, culture 25, prosperity 25, monument 39, kingdom 40.
	// Original monuments: small stepped pyramid + stepped pyramid COMPLEX (weight 44).
	// The complex is not implemented yet (task C1) -> temporary monument goal 31,
	// reachable with small (8) + medium (16) stepped pyramids: 6.32*sqrt(24)+0.5 = 31.
	// TODO(C1): restore goal 39 and swap BUILDING_MEDIUM_STEPPED_PYRAMID for
	// BUILDING_STEPPED_PYRAMID_COMPLEX in the buildings list.
	win_criteria {
		population {enabled : true, goal : 3000 }
		culture    {enabled : true, goal : 25 }
		prosperity {enabled : true, goal : 25 }
		monuments  {enabled : true, goal : 31 }
		kingdom    {enabled : true, goal : 40 }
	}

	enable_scenario_events : true

	cities [
		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_BEER ]
			buys [ RESOURCE_PAPYRUS, RESOURCE_TIMBER, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Behdet"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            sells [ RESOURCE_FISH, RESOURCE_CLAY ]
            buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
		}

        {
			name : "Selima Oasis"
            is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
            sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
            buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
		}

		{
			name : "Serabit Khadim"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_PAPYRUS, RESOURCE_GRAIN ]
		}
	]

	vars {
		pharaoh_requested_timber : false
		pharaoh_requested_reeds : false
		pharaoh_requested_pottery : false
		pharaoh_requested_papyrus : false
		pharaoh_requested_grain : false
		pharaoh_requested_stone : false
		libyan_warning_shown : false
		libyan_invasion_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission12]
function mission12_on_start(ev) {
	mission_show_start_message(mission, "message_mission_meidum")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests. The walkthrough gives the order (wood, reeds, pottery,
// papyrus, grain, plain stone) and only the first year (wood, year 3);
// later years and all amounts are placeholders — verify against the original .pak.

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_timber(ev) {
	if (mission.pharaoh_requested_timber) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_timber = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_TIMBER, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_reeds(ev) {
	if (mission.pharaoh_requested_reeds) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_reeds = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_REEDS, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_pottery(ev) {
	if (mission.pharaoh_requested_pottery) {
		return
	}

	if (ev.years_since_start < 5) {
		return
	}

	mission.pharaoh_requested_pottery = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_POTTERY, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_papyrus(ev) {
	if (mission.pharaoh_requested_papyrus) {
		return
	}

	if (ev.years_since_start < 6) {
		return
	}

	mission.pharaoh_requested_papyrus = true
	var request = city.create_good_request({ tag_id: 4, resource: RESOURCE_PAPYRUS, amount: 15, months_initial: 12 })
	city.create_chain_event({ tag_id: 401, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 402, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(401)
	request.set_refusal_action_tag(402)
	request.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_grain(ev) {
	if (mission.pharaoh_requested_grain) {
		return
	}

	if (ev.years_since_start < 7) {
		return
	}

	mission.pharaoh_requested_grain = true
	var request = city.create_good_request({ tag_id: 5, resource: RESOURCE_GRAIN, amount: 20, months_initial: 12 })
	city.create_chain_event({ tag_id: 501, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 502, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(501)
	request.set_refusal_action_tag(502)
	request.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_pharaoh_request_stone(ev) {
	if (mission.pharaoh_requested_stone) {
		return
	}

	if (ev.years_since_start < 8) {
		return
	}

	mission.pharaoh_requested_stone = true
	var request = city.create_good_request({ tag_id: 6, resource: RESOURCE_STONE, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 601, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 602, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(601)
	request.set_refusal_action_tag(602)
	request.execute()
}

// Libyan invasion from the east (walkthrough: lands on the marshland island).
// Timing and size are placeholders — verify against the original .pak.
// Entry point -1/-1 = default invasion point; TODO: set the island entry tile
// once the original map data is checked.

[es=event_advance_month, mission=mission12]
function mission12_libyan_warning(ev) {
	if (mission.libyan_warning_shown) {
		return
	}

	if (ev.years_since_start < 4 || ev.month < 5) {
		return
	}

	mission.libyan_warning_shown = true
	log_info("akhenaten: mission 12 meidum:${ev.years_since_start}:${ev.month} libyan attack warning", {ev:ev})

	var warning = city.create_foreign_army_attack_warning({ tag_id: 7, sender_faction: ENEMY_7_LIBIAN })
	warning.set_location_fields(-1, -1, -1, -1)
	warning.set_image("pharaoh_unloaded/dialougedrawing_00012")
	warning.set_reasons(PHRASE_foreign_army_attacks_you_1month_Warning, PHRASE_foreign_army_attacks_you_no_reason_A, -1, -1)
	warning.execute()
}

[es=event_advance_month, mission=mission12]
function mission12_libyan_invasion(ev) {
	if (mission.libyan_invasion_started) {
		return
	}

	if (ev.years_since_start < 4 || ev.month < 6) {
		return
	}

	mission.libyan_invasion_started = true
	log_info("akhenaten: mission 12 meidum:${ev.years_since_start}:${ev.month} libyan invasion", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_7_LIBIAN, size: 12, tilex: -1, tiley: -1, want_destroy_buildings: 10 })

	var alert = city.create_foreign_army_attack_warning({ tag_id: 8, sender_faction: ENEMY_7_LIBIAN })
	alert.set_location_fields(-1, -1, -1, -1)
	alert.set_image("pharaoh_unloaded/dialougedrawing_00012")
	alert.set_reasons(PHRASE_foreign_army_attacks_you_city_attacked_alert, PHRASE_foreign_army_attacks_you_no_reason_A, -1, -1)
	alert.execute()
}
