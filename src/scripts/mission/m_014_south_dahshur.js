log_info("akhenaten: mission 14 south dahshur started")

mission14 { // South Dahshur — Snofru's Bent Pyramid
	start_message : "message_mission_south_dahshur"
	selection_title : "South Dahshur"
	player_rank : 2

	// Choice-pair partner of Buhen (13); both converge on North Dahshur (15).
	// Linear next_mission, no choice[] here.
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
		briefing : "Voice/Mission/214_mission.mp3"
		victory : "Voice/Mission/214_victory.mp3"
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
                BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
				BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_BENT_PYRAMID, BUILDING_MEDIUM_BENT_PYRAMID,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_LIBRARY,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// pop 3500, culture 0 (disabled), prosperity 25, monument 21 (1 medium bent pyramid),
	// kingdom 50.
	// Bent pyramids are now implemented (task C4). A finished BUILDING_MEDIUM_BENT_PYRAMID
	// (weight 8) gives 2.25*8+4.5 = 22 (additive rating, see city/monuments.js), which
	// satisfies the original goal of 21. Weights are still placeholders — F3 will
	// recalibrate the per-type monument point table against the original .pak.
	win_criteria {
		population {enabled : true, goal : 3500 }
		culture    {enabled : false }
		prosperity {enabled : true, goal : 25 }
		monuments  {enabled : true, goal : 21 }
		kingdom    {enabled : true, goal : 50 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. From the briefing
	// (message_history_south_dahshur): local limestone at Dahshur, plain stone must be
	// imported; copper from Enkomi; gems from Serabit Khadim (erratic). Export pottery
	// and limestone.
	cities [
		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_BEER ]
			buys [ RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_PAPYRUS ]
		}

		{
			name : "Abu"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_CHICKPEAS ]
			buys [ RESOURCE_LIMESTONE, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Serabit Khadim"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_GRAIN ]
		}
	]

	vars {
		pharaoh_requested_grain : false
		pharaoh_requested_limestone : false
		pharaoh_requested_beer : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission14]
function mission14_on_start(ev) {
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_BENT_PYRAMID)
	mission_show_start_message(mission, "message_mission_south_dahshur")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests (walkthrough: grain, limestone, beer). Years and amounts are
// placeholders — verify against the original .pak.

[es=event_advance_month, mission=mission14]
function mission14_pharaoh_request_grain(ev) {
	if (mission.pharaoh_requested_grain) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_grain = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_GRAIN, amount: 16, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission14]
function mission14_pharaoh_request_limestone(ev) {
	if (mission.pharaoh_requested_limestone) {
		return
	}

	if (ev.years_since_start < 3) {
		return
	}

	mission.pharaoh_requested_limestone = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_LIMESTONE, amount: 12, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

[es=event_advance_month, mission=mission14]
function mission14_pharaoh_request_beer(ev) {
	if (mission.pharaoh_requested_beer) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_beer = true
	var request = city.create_good_request({ tag_id: 3, resource: RESOURCE_BEER, amount: 10, months_initial: 12 })
	city.create_chain_event({ tag_id: 301, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 302, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 6 })
	request.set_completed_action_tag(301)
	request.set_refusal_action_tag(302)
	request.execute()
}
