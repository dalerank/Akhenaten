log_info("akhenaten: mission 36 rowarty started")

// Mission 36 — Rowarty (Avaris), "The Sea People". Rank 10 (Pharaoh).
//
// Goals:     population 7000, culture 65, prosperity 50, monuments 29, kingdom 80, housing level 10.
// Start:     funds 10000, rescue loan 5000, debt interest 20% (normal difficulty).
// Gods:      Osiris, Ptah, Seth (patron).
// Monuments: mausoleum, medium mudbrick pyramid, small mudbrick pyramid (burial goods: 12 pottery,
//            12 beer, 8 linen, 4 luxury goods).
// Trade:     nothing open at start; can open — Abu (by sea), Byblos (by sea), Itjtawy; route-status
//            events of the request chains can change routes; display only — Bahariya Oasis, Dakhla
//            Oasis, Farafra Oasis, Gaza, Heh, Iken, Kerma, Men-nefer, Mycenae, Qadesh, Tyre.
// Enemies:   Assyrian raids by sea (the briefing's Sea People); favour armies of 30 in four waves
//            (Egyptian, Egyptian, scenario enemy, Egyptian) if the kingdom rating falls to 0.
// Timeline:  raids by sea (announced, then attacking): 38 with 5 warships y2m8, y3m1 (as it attacks:
//            request 42 henna, which otherwise comes at y8m3); 20 with 2 y3m1, y3m7; 35 with 6 y5m8,
//            y6m2; 44 with 8 y7m1, y7m7; 56 with 6 y45m10, y46m4, again every time its army is gone. Requests: y6m9 10 grain; y10m11 93 henna; y22m1 80 troops; y34m7
//            19 oil; recurring from y23m5 6 grain, y24m9 6 grain, y39m2 6 timber, y42m4 6 weapons,
//            y52m4 70 troops (not sent: raid 72 by sea with 12 warships announced 9 months later, attacking
//            6 months after that). The henna, oil and troops
//            requests lead into chained requests whose outcomes conquer cities, open or lose routes,
//            bring gifts (sandstone, limestone, granite, oil) or move the kingdom rating.
//
// Notes for developers:
// - events[] holds the original event table and is run by the engine. Its invasion entries are
//   no-ops except the favour armies, so the timed raids and the troops-70 raid follow the OG invasion
//   cycle from JS (missions.js mission_raids_month: warnings from the event's month, the attack
//   months_initial months later, the point rolled from the event's location_fields: 1..8 land points,
//   9..16 sea points).
// - The briefing speaks of two mausoleums; the original monument slots are kept (mausoleum, medium
//   and small mudbrick pyramids).
// - next_mission is -1: the campaign ends here.

mission36 { // Rowarty (Avaris) — The Sea People
	map_file : "data/maps/m_036_rowarty.map"
	start_message : "message_mission_avarist"
	selection_title : "Rowarty"
	player_rank : 10

	next_mission : -1

	// pak Normal funds=10000 loan=5000 debt_interest=20 → int_dcy around Normal.
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [10000, 6700, 5000, 3400, 2700]
	debt_interest [10, 15, 20, 25, 30]

	env {
		// pak animals=0; enable so prey update after create_herds (hunting lodge).
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/236_mission.mp3"
		victory : "Voice/Mission/236_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM, BUILDING_LETTUCE_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MAUSOLEUM, BUILDING_MEDIUM_MUDBRICK_PYRAMID, BUILDING_SMALL_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	// Goal 29 = pak: Mausoleum+Med+Small mudbrick (5+12+4) → 29; burial goods all below one divisor.
	win_criteria {
		population    {enabled : true, goal : 7000 }
		culture       {enabled : true, goal : 65 }
		prosperity    {enabled : true, goal : 50 }
		monuments     {enabled : true, goal : 29 }
		kingdom       {enabled : true, goal : 80 }
		housing_level {enabled : true, goal : 10 }
		milestone25_year : 10
		milestone50_year : 20
		milestone75_year : 30
	}

	entry_point [199, 137]
	exit_point [199, 87]
	river_entry_point [191, 144]
	// pak river_exit invalid — omit (keep empty).
	disembark_points [
		[179, 117], [151, 73], [164, 123]
	]
	invasion_points_land [
		[121, 112], [180, 82], [158, 71], [132, 50],
		[117, 30], [99, 6], [56, 117], [151, 153]
	]
	invasion_points_sea [
		[215, 3], [155, 33], [177, 44], [204, 65],
		[218, 85], [209, 109], [166, 6], [40, 183]
	]
	// pak type FIGURE_NONE — spawn slots only.
	herd_points_predator [
		[157, 66], [96, 54], [119, 175]
	]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_POTTERY, required: 12 }
		{ resource: RESOURCE_BEER, required: 12 }
		{ resource: RESOURCE_LINEN, required: 8 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 4 }
	]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_INVASION
			time { year : 3, month : 1 }
			item { value : 1 }
			amount { value : 20 }
			months_initial : 6
			location_fields [ 11, -1, 9, 13 ]
			warships : 2
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 0
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 0
		}
		{ // pak i=1
			type : EVENT_TYPE_INVASION
			time { year : 5, month : 8 }
			item { value : 1 }
			amount { value : 35 }
			months_initial : 6
			location_fields [ 11, -1, 9, 15 ]
			warships : 6
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 1
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 4
		}
		{ // pak i=2
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 9 }
			item { value : RESOURCE_GRAIN }
			amount { value : 10 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 2
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 4
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=3
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 0, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 3
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=4
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 0, month : 8 }
			item { value : 1 }
			amount { value : 1 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 4
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=5
			type : EVENT_TYPE_INVASION
			time { year : 7, month : 1 }
			item { value : 1 }
			amount { value : 44 }
			months_initial : 6
			location_fields [ 10, -1, 9, 13 ]
			warships : 8
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 5
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 0
		}
		{ // pak i=6
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 3 }
			item { value : RESOURCE_HENNA }
			amount { value : 42 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 6
			on_completed_action : 7
			on_refusal_action : 18
			on_too_late_action : 18
			on_defeat_action : 18
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=7
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 103 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 4
		}
		{ // pak i=8
			type : EVENT_TYPE_INVASION
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 38 }
			months_initial : 5
			location_fields [ 9, -1, 9, 13 ]
			warships : 5
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 8
			on_completed_action : 6
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 1
		}
		{ // pak i=9
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 8 }
			item { value : RESOURCE_OIL }
			amount { value : 656 }
			months_initial : 2
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 9
			on_completed_action : 10
			on_refusal_action : 20
			on_too_late_action : 20
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 5
		}
		{ // pak i=10
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 0, month : 8 }
			item { value : 1 }
			amount { value : 106 }
			months_initial : 6
			location_fields [ 0, -1, 0, 2 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 10
			on_completed_action : 21
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=11
			type : EVENT_TYPE_INVASION
			time { year : 45, month : 10 }
			item { value : 1 }
			amount { value : 56 }
			months_initial : 6
			location_fields [ 12, -1, 9, 13 ]
			warships : 6
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 11
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{ // pak i=12
			type : EVENT_TYPE_REQUEST
			time { year : 10, month : 11 }
			item { value : RESOURCE_HENNA }
			amount { value : 93 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 12
			on_completed_action : 13
			on_refusal_action : 16
			on_too_late_action : 16
			on_defeat_action : 16
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=13
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 112 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 13
			on_completed_action : 14
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 5
		}
		{ // pak i=14
			type : EVENT_TYPE_REQUEST
			time { year : 22, month : 8 }
			item { value : RESOURCE_TROOPS }
			amount { value : 48 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 14
			on_completed_action : 15
			on_refusal_action : 16
			on_too_late_action : 16
			on_defeat_action : 16
			sender_faction : 0
			subtype : 1
			city_id : 6
		}
		{ // pak i=15
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 110 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 15
			on_completed_action : 25
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=16
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 16
			on_completed_action : 17
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=17
			type : EVENT_TYPE_REQUEST
			time { year : 21, month : 8 }
			item { value : RESOURCE_HENNA }
			amount { value : 84 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 17
			on_completed_action : 13
			on_refusal_action : 16
			on_too_late_action : 16
			on_defeat_action : 16
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=18
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 18
			on_completed_action : 19
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=19
			type : EVENT_TYPE_REQUEST
			time { year : 18, month : 8 }
			item { value : RESOURCE_HENNA }
			amount { value : 86 }
			months_initial : 3
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 19
			on_completed_action : 7
			on_refusal_action : 18
			on_too_late_action : 18
			on_defeat_action : 18
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=20
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 20
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=21
			type : EVENT_TYPE_REQUEST
			time { year : 49, month : 8 }
			item { value : RESOURCE_TROOPS }
			amount { value : 96 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 21
			on_completed_action : 22
			on_refusal_action : 23
			on_too_late_action : 23
			on_defeat_action : 24
			sender_faction : 0
			subtype : 1
			city_id : 4
		}
		{ // pak i=22
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 1, month : 8 }
			item { value : RESOURCE_GRANITE }
			amount { value : 107 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 22
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=23
			type : EVENT_TYPE_LAND_TRADE_PROBLEM
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 102 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 23
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=24
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 97 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 24
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{ // pak i=25
			type : EVENT_TYPE_REQUEST
			time { year : 25, month : 8 }
			item { value : RESOURCE_TROOPS }
			amount { value : 58 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 25
			on_completed_action : 26
			on_refusal_action : 27
			on_too_late_action : 27
			on_defeat_action : 28
			sender_faction : 0
			subtype : 1
			city_id : 5
		}
		{ // pak i=26
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 4, month : 8 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 28 }
			months_initial : 6
			location_fields [ 9, -1, 9, 13 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 26
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=27
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 4, month : 8 }
			item { value : 1 }
			amount { value : 97 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 27
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=28
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 98 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 28
			on_completed_action : 14
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=29
			type : EVENT_TYPE_REQUEST
			time { year : 23, month : 5 }
			item { value : RESOURCE_GRAIN }
			amount { value : 6 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 29
			on_completed_action : 30
			on_refusal_action : 31
			on_too_late_action : 31
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=30
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 30
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=31
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 31
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=32
			type : EVENT_TYPE_REQUEST
			time { year : 34, month : 7 }
			item { value : RESOURCE_OIL }
			amount { value : 19 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 32
			on_completed_action : 33
			on_refusal_action : 34
			on_too_late_action : 35
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=33
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 96 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 33
			on_completed_action : 36
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=34
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 8 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 34
			on_completed_action : 35
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=35
			type : EVENT_TYPE_REQUEST
			time { year : 17, month : 8 }
			item { value : RESOURCE_OIL }
			amount { value : 8 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 35
			on_completed_action : 33
			on_refusal_action : 34
			on_too_late_action : 34
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=36
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 20, month : 8 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 28 }
			months_initial : 6
			location_fields [ 9, -1, 9, 13 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 36
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=37
			type : EVENT_TYPE_REQUEST
			time { year : 42, month : 4 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 6 }
			months_initial : 9
			location_fields [ 2, -1, 1, 4 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 37
			on_completed_action : 30
			on_refusal_action : 31
			on_too_late_action : 31
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=38
			type : EVENT_TYPE_REQUEST
			time { year : 39, month : 2 }
			item { value : RESOURCE_TIMBER }
			amount { value : 6 }
			months_initial : 3
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 38
			on_completed_action : 39
			on_refusal_action : 4
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=39
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_SANDSTONE }
			amount { value : 7 }
			months_initial : 2
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 39
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=40
			type : EVENT_TYPE_REQUEST
			time { year : 24, month : 9 }
			item { value : RESOURCE_GRAIN }
			amount { value : 6 }
			months_initial : 6
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 40
			on_completed_action : 41
			on_refusal_action : 4
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=41
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_LIMESTONE }
			amount { value : 10 }
			months_initial : 2
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 41
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=42
			type : EVENT_TYPE_REQUEST
			time { year : 22, month : 1 }
			item { value : RESOURCE_TROOPS }
			amount { value : 80 }
			months_initial : 6
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			tag_id : 42
			on_completed_action : 43
			on_refusal_action : 44
			on_too_late_action : 44
			on_defeat_action : 44
			sender_faction : 0
			subtype : 1
			city_id : 4
		}
		{ // pak i=43
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_GRANITE }
			amount { value : 7 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 43
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=44
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 6 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 44
			on_completed_action : 45
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=45
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 57 }
			months_initial : 6
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 45
			on_completed_action : 43
			on_refusal_action : 46
			on_too_late_action : 46
			on_defeat_action : 46
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{ // pak i=46
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 46
			on_completed_action : 47
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{ // pak i=47
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 42 }
			months_initial : 3
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 47
			on_completed_action : 48
			on_refusal_action : 49
			on_too_late_action : 49
			on_defeat_action : 49
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{ // pak i=48
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 7 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 48
			on_completed_action : 45
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=49
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 49
			on_completed_action : 50
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=50
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 18 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 50
			on_completed_action : 51
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=51
			type : EVENT_TYPE_REQUEST
			time { year : 33, month : 0 }
			item { value : RESOURCE_HENNA }
			amount { value : 51 }
			months_initial : 6
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 51
			on_completed_action : 52
			on_refusal_action : 50
			on_too_late_action : 50
			on_defeat_action : 50
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=52
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 52
			on_completed_action : 53
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 4
		}
		{ // pak i=53
			type : EVENT_TYPE_REQUEST
			time { year : 57, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 56 }
			months_initial : 6
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 53
			on_completed_action : 48
			on_refusal_action : 49
			on_too_late_action : 49
			on_defeat_action : 49
			sender_faction : 0
			subtype : 1
			city_id : 5
		}
		{ // pak i=54
			type : EVENT_TYPE_REQUEST
			time { year : 52, month : 4 }
			item { value : RESOURCE_TROOPS }
			amount { value : 70 }
			months_initial : 9
			location_fields [ 6, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			tag_id : 54
			on_completed_action : 55
			on_refusal_action : 56
			on_too_late_action : 56
			on_defeat_action : 56
			sender_faction : 0
			subtype : 1
			city_id : 6
		}
		{ // pak i=55
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 7 }
			months_initial : 2
			location_fields [ 7, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 55
			on_completed_action : 57
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=56
			type : EVENT_TYPE_INVASION
			time { year : 9, month : 0 }
			item { value : 1 }
			amount { value : 72 }
			months_initial : 6
			location_fields [ 10, -1, 9, 16 ]
			warships : 12
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 56
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 4
		}
		{ // pak i=57
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_OIL }
			amount { value : 8 }
			months_initial : 2
			location_fields [ 4, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 57
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=58
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 2 }
			amount { value : 30 }
			months_initial : 6
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 58
			on_completed_action : 59
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 4
		}
		{ // pak i=59
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : 2 }
			amount { value : 30 }
			months_initial : 0
			location_fields [ 3, -1, 3, 4 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 59
			on_completed_action : 60
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{ // pak i=60
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : 1 }
			amount { value : 30 }
			months_initial : 0
			location_fields [ 5, -1, 5, 6 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 60
			on_completed_action : 61
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 4
		}
		{ // pak i=61
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : 2 }
			amount { value : 30 }
			months_initial : 0
			location_fields [ 7, -1, 7, 8 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 61
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 4
		}
	]

	map_background : {pack:PACK_EMPIRE, id:35}
	hide_pak_cities : true
	cities [
		{
			name : "Rowarty"
			idx : 14
			pos : [612, 389]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE, RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_TIMBER, RESOURCE_REEDS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
		}
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 1
			is_open : false
			cost_to_open : 1100
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 1500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 3
			is_open : false
			cost_to_open : 550
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}
		{
			name : "Dakhla Oasis"
			idx : 3
			pos : [349, 1037]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Farafra Oasis"
			idx : 4
			pos : [327, 831]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Gaza"
			idx : 5
			pos : [846, 280]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Heh"
			idx : 6
			pos : [698, 1414]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Iken"
			idx : 7
			pos : [735, 1380]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Itjtawy"
			idx : 8
			pos : [568, 557]
			route : 8
			is_open : false
			cost_to_open : 175
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
			]
		}
		{
			name : "Kerma"
			idx : 9
			pos : [732, 1491]
			route : 4
			cost_to_open : 1600
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Men-nefer"
			idx : 10
			pos : [545, 487]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Mycenae"
			idx : 11
			pos : [15, 11]
			route : 5
			cost_to_open : 1100
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Qadesh"
			idx : 13
			pos : [962, 10]
			route : 2
			cost_to_open : 600
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 15
			pos : [877, 121]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[888, 1175], [882, 1152], [889, 1140], [877, 1114], [884, 1101], [875, 1090],
				[879, 1081], [864, 1050], [864, 1036], [850, 1019], [834, 1015], [814, 986],
				[829, 944], [816, 908], [775, 936], [760, 923], [720, 897], [676, 864],
				[630, 824], [597, 795], [595, 777], [584, 756], [584, 737], [568, 723],
				[569, 710], [571, 670], [583, 647], [584, 625], [602, 611], [585, 529],
				[563, 501], [575, 469], [573, 464], [589, 458], [597, 443], [638, 426]
			]
		}
		{
			route : 2
			type : 1
			points [
				[974, 30], [972, 67], [953, 95], [927, 131], [914, 172], [901, 208],
				[896, 258], [888, 317], [880, 330], [853, 343], [796, 375], [639, 421]
			]
		}
		{
			route : 3
			type : 2
			points [
				[901, 90], [872, 105], [865, 151], [861, 190], [851, 239], [848, 283],
				[839, 297], [816, 317], [775, 339], [740, 341], [696, 362], [637, 359],
				[631, 371], [633, 415]
			]
		}
		{
			route : 4
			type : 2
			points [
				[734, 1502], [731, 1486], [694, 1466], [716, 1459], [721, 1448], [780, 1397],
				[788, 1379], [798, 1369], [800, 1347], [844, 1303], [861, 1319], [879, 1303],
				[901, 1251], [905, 1227], [898, 1216], [889, 1210], [895, 1199], [888, 1155],
				[895, 1139], [884, 1116], [888, 1101], [871, 1051], [867, 1033], [849, 1012],
				[837, 1010], [821, 988], [833, 948], [817, 904], [775, 928], [603, 794],
				[601, 774], [590, 756], [591, 736], [575, 724], [574, 672], [591, 649],
				[590, 629], [611, 611], [587, 526], [568, 498], [583, 465], [630, 421]
			]
		}
		{
			route : 5
			type : 2
			points [
				[42, 23], [55, 71], [61, 95], [64, 119], [54, 142], [57, 161],
				[72, 181], [99, 193], [70, 344], [82, 374], [129, 401], [170, 404],
				[213, 423], [265, 430], [327, 438], [360, 451], [405, 412], [443, 378],
				[516, 344], [570, 345], [604, 333], [630, 350], [630, 414]
			]
		}
		{
			route : 6
			type : 2
			points [
				[406, 237], [478, 255], [524, 275], [575, 300], [629, 337], [637, 375],
				[635, 416]
			]
		}
		{
			route : 7
			type : 2
			points [
				[765, 124], [711, 187], [661, 281], [639, 343], [632, 412]
			]
		}
		{
			route : 8
			type : 1
			points [
				[594, 570], [609, 530], [616, 492], [625, 453], [633, 418]
			]
		}
	]
	hide_pak_objects : true
	empire_ornaments [
		{ pos : [535, 437], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [483, 514], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [563, 588], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [617, 725], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [636, 725], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [603, 428], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [608, 516], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [622, 750], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [632, 775], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [661, 818], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [577, 503], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [516, 527], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [872, 1006], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [864, 839], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [666, 1418], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [879, 1021], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [875, 903], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [711, 1380], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [859, 903], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [922, 65], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [915, 1221], image : "pharaoh_general/empire_bits_00125" }
	]

	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [440, 480] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		raids : ""
		start_message_shown : false
		henna6_fired : false
	}
}

[es=event_mission_start, mission=mission36]
function mission36_on_start(ev) {
	__image_request_pak(PACK_ENEMY_ASSYRIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_avarist")
	empire.set_id(35)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_1_ASSYRIAN)
	scenario.start_year = -1279
	scenario.climate = 0 // CLIMATE_CENTRAL (pak)
	__scenario_monuments.first = 26
	__scenario_monuments.second = 4
	__scenario_monuments.third = 3
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak i=0, 1, 5, 8 (chains the henna request i=6 as it attacks), 11 (recurring), 56 (after troops-70 fails).
function mission36_raid_list() {
	var A = ENEMY_1_ASSYRIAN
	var E = EVENT_INVADER_ENEMY
	return [
		{ key: "i0", invasion_id: 0, year: 3, month: 1, invader: E, enemy: A, amount: 20, months_initial: 6,
			location: [11, -1, 9, 13], warships: 2, attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i1", invasion_id: 1, year: 5, month: 8, invader: E, enemy: A, amount: 35, months_initial: 6,
			location: [11, -1, 9, 15], warships: 6, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i5", invasion_id: 5, year: 7, month: 1, invader: E, enemy: A, amount: 44, months_initial: 6,
			location: [10, -1, 9, 13], warships: 8, attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i8", invasion_id: 8, year: 2, month: 8, invader: E, enemy: A, amount: 38, months_initial: 5,
			location: [9, -1, 9, 13], warships: 5, attack_target: EVENT_ATTACK_TARGET_VAULTS, on_attack: mission36_raid_i8_chain },
		{ key: "i11", invasion_id: 11, year: 45, month: 10, invader: E, enemy: A, amount: 56, months_initial: 6,
			location: [12, -1, 9, 13], warships: 6, attack_target: EVENT_ATTACK_TARGET_RANDOM, recurring: true },
		{ key: "i56", invasion_id: 56, invader: E, enemy: A, amount: 72, months_initial: 6, location: [10, -1, 9, 16],
			warships: 12, attack_target: EVENT_ATTACK_TARGET_RANDOM }
	]
}

function mission36_raid_i8_chain() {
	if (!mission.henna6_fired) {
		mission.henna6_fired = true
		__city_event_fire_chain(6)
	}
}

[es=event_advance_month, mission=mission36]
function mission36_raids(ev) {
	mission_raids_month(mission, mission36, ev, mission36_raid_list())
	if (!mission.henna6_fired && ev.years_since_start == 8 && ev.month == 3) {
		mission.henna6_fired = true
		log_info("akhenaten: mission 36 henna×42 calendar (i=6)")
		__city_event_fire_chain(6)
	}
}

// pak i=54 troops×70 refused, late or lost → i=56, due 9 months on (its time.year).
[es=event_request_cleared, mission=mission36]
function mission36_on_request_cleared(ev) {
	if (ev.tag_id == 54 && mission_request_outcome(ev) != "ok") {
		mission_raid_schedule(mission, mission36_raid_list(), "i56", 9)
	}
}
