log_info("akhenaten: mission 18 rostja started")

mission18 { // Rostja (Giza) — The Great Pyramid and Sphinx
	start_message : "message_mission_giza"
	selection_title : "Rostja"
	player_rank : 3

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 37]

	// Convergence of the Iunet/On fork; itself the entry to the next pair:
	// Bahariya (19) / Djedu (20). Those are not scripted yet, so the choice screen
	// currently leads to dead ends (task B5). Tooltip ids are placeholders.
	choice [
		{
			name : "Bahariya"
			id : 19
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 38]
			pos [620, 420]
		}

		{
			name : "Djedu"
			id : 20
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 39]
			pos [640, 480]
		}
	]

	initial_funds [10000, 8000, 6000, 4000, 3000]
	rescue_loans [10000, 8000, 6000, 4000, 3000]
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
		briefing : "Voice/Mission/218_mission.mp3"
		victory : "Voice/Mission/218_victory.mp3"
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
				BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_CLAY_PIT,
				BUILDING_FERRY,
				BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID,
				BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_PAVILLION,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Goals from the Pharaoh Heaven walkthrough (original .pak values NOT yet verified):
	// no population / culture / prosperity requirement; monument 53 (Sphinx + pyramid
	// complex + pyramid), kingdom 50. A pure monument-and-loyalty mission.
	// C3 (true pyramid / complex) and C6 (sphinx) are NOT implemented; the available
	// monuments cannot reach the original 53. Stand-in: require the full available set —
	// both stepped pyramids (8+16) + both mastabas (2+2) = sum 28 -> 2.25*28+4.5 = 67
	// (additive rating, see city/monuments.js). Temporary monument goal 67 (needs all
	// four monuments finished).
	// TODO(C3+C6/F3): restore goal 53 and replace the stepped pyramids/mastabas with
	// BUILDING_PYRAMID_COMPLEX + BUILDING_LARGE_PYRAMID (prince) + BUILDING_SPHINX.
	win_criteria {
		population {enabled : false }
		culture    {enabled : false }
		prosperity {enabled : false }
		monuments  {enabled : true, goal : 67 }
		kingdom    {enabled : true, goal : 50 }
	}

	enable_scenario_events : true

	// Trade partners are NOT verified against the original .pak. From the briefing
	// (message_history_rostja): some limestone is provided, much must be bought; the
	// funeral barge needs Lebanese cedar (timber from Byblos); granite for the sarcophagus.
	cities [
		{
			name : "On"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LIMESTONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_PAPYRUS ]
		}

		{
			name : "Men-nefer"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_BEER ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS, RESOURCE_LUXURY_GOODS ]
		}

		{
			name : "Byblos"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_TIMBER ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS, RESOURCE_LUXURY_GOODS ]
		}
	]

	vars {
		pharaoh_requested_limestone : false
		pharaoh_requested_stone : false
		libyan_invasion_1_started : false
		libyan_invasion_2_started : false
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission18]
function mission18_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	mission_show_start_message(mission, "message_mission_giza")
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// Pharaoh's requests (walkthrough: gems/luxury/game meat/wood; simplified to the stone
// chain here). Amounts/years placeholder — verify vs .pak.

[es=event_advance_month, mission=mission18]
function mission18_pharaoh_request_limestone(ev) {
	if (mission.pharaoh_requested_limestone) {
		return
	}

	if (ev.years_since_start < 2) {
		return
	}

	mission.pharaoh_requested_limestone = true
	var request = city.create_good_request({ tag_id: 1, resource: RESOURCE_LIMESTONE, amount: 20, months_initial: 12 })
	city.create_chain_event({ tag_id: 101, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 102, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(101)
	request.set_refusal_action_tag(102)
	request.execute()
}

[es=event_advance_month, mission=mission18]
function mission18_pharaoh_request_stone(ev) {
	if (mission.pharaoh_requested_stone) {
		return
	}

	if (ev.years_since_start < 4) {
		return
	}

	mission.pharaoh_requested_stone = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_STONE, amount: 20, months_initial: 12 })
	city.create_chain_event({ tag_id: 201, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 8 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.execute()
}

// Libyan raids (walkthrough: mid-east region, then south-east shore).
[es=event_advance_month, mission=mission18]
function mission18_libyan_invasion_1(ev) {
	if (mission.libyan_invasion_1_started) {
		return
	}

	if (ev.years_since_start < 3 || ev.month < 6) {
		return
	}

	mission.libyan_invasion_1_started = true
	log_info("akhenaten: mission 18 rostja:${ev.years_since_start}:${ev.month} libyan invasion 1", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 0, enemy: ENEMY_7_LIBIAN, size: 14, tilex: -1, tiley: -1, want_destroy_buildings: 10 })
}

[es=event_advance_month, mission=mission18]
function mission18_libyan_invasion_2(ev) {
	if (mission.libyan_invasion_2_started) {
		return
	}

	if (ev.years_since_start < 6 || ev.month < 1) {
		return
	}

	mission.libyan_invasion_2_started = true
	log_info("akhenaten: mission 18 rostja:${ev.years_since_start}:${ev.month} libyan invasion 2", {ev:ev})

	city.start_foreign_army_invasion({ invasion_id: 1, enemy: ENEMY_7_LIBIAN, size: 18, tilex: -1, tiley: -1, want_destroy_buildings: 12 })
}
