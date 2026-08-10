log_info("akhenaten: mission 49 alexandria_2 started")

// Full empire redefine (CC49). Dump 2026-08-01 Cleop.
// MM briefing: message_mission_ptolemy_alexandria (443) — *A Beacon of Light*.
// Pak map subtitle: "The Glory of Ptolemy" (UI uses start_message subtitle).
// Rank 10. Year -305. Enemy ENEMY_10_PHOENICIAN. Empire id 0, image_id 26.
// Win: pop 7000 / culture 75 / prosperity 75 / monuments 28 /
//      kingdom 75 / housing 6x lv16 / time_limit OFF (milestones 6/12/18).
// Monuments: first=29 Library, second=28 Pharos (gr198).
// Rating: Library W=6 + Pharos W=5 → trunc(2.25*11+4.5)=29 ≥ goal 28.
// Burial: none. Gods: Ra(2) Ptah(1) Bast(1).
// Enkomi sells marble (briefing OK). Orphan routes Knossos/Migdol/Waset -> route 0.
// SKIP empty map_obj idx=8. Invasions: 0. next_mission 50 (Maritis → Notes §13.13).

mission49 { // Ptolemy's Alexandria - A Beacon of Light
	map_file : "data/maps/m_049_alexandria_2.map"
	start_message : "message_mission_ptolemy_alexandria"
	selection_title : "Ptolemy's Alexandria"
	player_rank : 10
	carry_troops : ["archer", "infantry"]
	carry_monuments : true

	next_mission : 50

	// pak Normal funds=30000 loan=5000 debt_interest=6 -> int_dcy around Normal.
	initial_funds [60000, 40000, 30000, 20100, 15900]
	rescue_loans [10000, 6670, 5000, 3350, 2650]
	debt_interest [3, 4, 6, 8, 10]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C49_mission.mp3"
		victory : "Voice/Mission/C49_victory.mp3"
	}

	// buildings[] synced to pak_editor_allow: +gold/chariot/senet/zoo; -water_lift/academy/warship.
	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_TRANSPORT_WHARF, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_LETTUCE_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_COPPER_MINE,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
		BUILDING_ALEXANDRIA_LIBRARY, BUILDING_PHAROS_LIGHTHOUSE,
	]

	win_criteria {
		population    {enabled : true, goal : 7000 }
		culture       {enabled : true, goal : 75 }
		prosperity    {enabled : true, goal : 75 }
		monuments     {enabled : true, goal : 28 }
		kingdom       {enabled : true, goal : 75 }
		housing_count {enabled : true, goal : 6 }
		housing_level {enabled : true, goal : 16 }
		time_limit    {enabled : false, years : 12 }
		milestone25_year : 6
		milestone50_year : 12
		milestone75_year : 18
	}

	entry_point [207, 96]
	exit_point [169, 167]
	river_entry_point [94, 20]
	river_exit_point [126, 15]
	fishing_points [
		[95, 32], [127, 22], [102, 23]
	]
	herd_points_predator [ [30, 124], [78, 185], [69, 165] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 2 }
			item { value : RESOURCE_GRAIN }
			amount { value : 5 }
			months_initial : 8
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 1
			on_refusal_action : 2
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=1
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_GEMS }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : 4
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=2
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 3, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=3
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_GEMS }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : 4
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=4
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=5
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 2 }
			item { value : RESOURCE_TROOPS }
			amount { value : 12 }
			months_initial : 6
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 6
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : 9
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=6
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=7
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=8
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=9
			type : EVENT_TYPE_LAND_TRADE_PROBLEM
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=10
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 8 }
			item { value : RESOURCE_TROOPS }
			amount { value : 19 }
			months_initial : 8
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 6
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : 11
			sender_faction : 0
			subtype : 1
			city_id : 6
		}
		{ // pak i=11
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 8 }
			months_initial : 8
			location_fields [ 15, 15, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 3
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : 12
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{ // pak i=12
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=13
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 7 }
			item { value : RESOURCE_FISH }
			amount { value : 7 }
			months_initial : 6
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 14
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 6
		}
		{ // pak i=14
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : 4
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=15
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 7, month : 8 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=16
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 11, month : 7 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=17
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 9, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=18
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 12 }
			months_initial : 6
			location_fields [ 10, 10, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 19
			on_refusal_action : 20
			on_too_late_action : 19
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=19
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 11 }
			months_initial : 12
			location_fields [ 10, 10, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 21
			on_refusal_action : 4
			on_too_late_action : 21
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=20
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 12, 12, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=21
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 13, 13, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 22
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=22
			type : EVENT_TYPE_REQUEST
			time { year : 16, month : 5 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 6
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=23
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 8, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, -1, 1, 3 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=24
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 4 }
			item { value : RESOURCE_BEER }
			amount { value : 11 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 25
			on_refusal_action : 7
			on_too_late_action : 26
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 6
		}
		{ // pak i=25
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=26
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=27
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 2 }
			item { value : RESOURCE_POTTERY }
			amount { value : 8 }
			months_initial : 10
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 28
			on_refusal_action : 4
			on_too_late_action : 29
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=28
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=29
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=30
			type : EVENT_TYPE_WAGE_DECREASE
			time { year : 9, month : 10 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=31
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 17, month : 8 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=32
			type : EVENT_TYPE_REQUEST
			time { year : 15, month : 2 }
			item { value : RESOURCE_GRAIN }
			amount { value : 12 }
			months_initial : 9
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 44
			on_refusal_action : -1
			on_too_late_action : 44
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=33
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 24, month : 8 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=34
			type : EVENT_TYPE_REQUEST
			time { year : 18, month : 0 }
			item { value : RESOURCE_BEER }
			amount { value : 12 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 36
			on_refusal_action : 7
			on_too_late_action : 37
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 5
		}
		{ // pak i=35
			type : EVENT_TYPE_REQUEST
			time { year : 20, month : 7 }
			item { value : RESOURCE_GRAIN }
			amount { value : 13 }
			months_initial : 8
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 38
			on_refusal_action : 40
			on_too_late_action : 39
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 6
		}
		{ // pak i=36
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 15 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=37
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 12 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=38
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 4
		}
		{ // pak i=39
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_GEMS }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=40
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{ // pak i=41
			type : EVENT_TYPE_REQUEST
			time { year : 24, month : 7 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 13 }
			months_initial : 9
			location_fields [ 1, -1, 1, 3 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 42
			on_refusal_action : 4
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=42
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=43
			type : EVENT_TYPE_HAILSTORM
			time { year : 13, month : 3 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=44
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
	]

	map_background : {pack:PACK_EMPIRE, id:26}

	hide_pak_cities : true
	cities [
		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [410, 646]
			route : 6
			is_open : false
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_GAMEMEAT ]
			buys [ RESOURCE_FISH, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Enkomi"
			idx : 1
			pos : [679, 49]
			route : 2
			is_open : false
			cost_to_open : 675
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_TIMBER, RESOURCE_COPPER, RESOURCE_MARBLE ]
			buys [ RESOURCE_GRAIN, RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_MARBLE, limit: 4000 }
			]
		}
		{
			name : "Gaza"
			idx : 2
			pos : [853, 275]
			route : 10
			trade : false
			cost_to_open : 700
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Iunet"
			idx : 3
			pos : [783, 892]
			route : 7
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_FLAX ]
			buys [ RESOURCE_STRAW, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
			]
		}
		{
			name : "Knossos"
			idx : 4
			pos : [190, 133]
			route : 0
			trade : false
			cost_to_open : 525
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Kyrene"
			idx : 5
			pos : [22, 341]
			route : 3
			is_open : false
			cost_to_open : 515
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_GEMS ]
			buys [ RESOURCE_BEER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 6
			pos : [558, 499]
			route : 4
			is_open : false
			cost_to_open : 155
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Athens"
			idx : 7
			pos : [19, 9]
			route : 1
			is_open : false
			cost_to_open : 760
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_PAPYRUS, RESOURCE_MARBLE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 4000 }
				{ resource: RESOURCE_MARBLE, limit: 2500 }
			]
		}
		{
			name : "Pwenet"
			idx : 9
			pos : [1133, 1325]
			route : 8
			trade : false
			cost_to_open : 1300
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 10
			pos : [880, 123]
			route : 13
			trade : false
			cost_to_open : 810
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Alexandria"
			idx : 27
			pos : [404, 390]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_REEDS ]
		}
		{
			name : "Migdol"
			idx : 28
			pos : [651, 388]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "On"
			idx : 29
			pos : [585, 466]
			route : 14
			trade : false
			cost_to_open : 190
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Meidum"
			idx : 33
			pos : [569, 588]
			route : 5
			is_open : false
			cost_to_open : 250
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW ]
			buys [ RESOURCE_WEAPONS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
			]
		}
		{
			name : "Waset"
			idx : 36
			pos : [830, 937]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Serabit Khadim"
			idx : 40
			pos : [799, 573]
			route : 9
			trade : false
			cost_to_open : 600
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Buhen"
			idx : 41
			pos : [763, 1344]
			route : 11
			trade : false
			cost_to_open : 1560
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Byblos"
			idx : 42
			pos : [907, 66]
			route : 12
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [42, 40], [54, 66], [63, 96], [57, 127], [52, 148], [57, 173], [74, 200], [100, 208], [173, 212], [224, 222], [276, 282], [324, 342], [374, 393], [411, 413] ]
		}
		{
			route : 2
			type : 2
			points [ [706, 69], [724, 73], [871, 138], [862, 196], [852, 267], [818, 308], [769, 334], [729, 331], [682, 353], [657, 349], [597, 329], [539, 337], [492, 346], [460, 361], [424, 383], [411, 415] ]
		}
		{
			route : 3
			type : 2
			points [ [51, 345], [75, 345], [111, 365], [169, 400], [276, 429], [373, 433], [409, 414] ]
		}
		{
			route : 4
			type : 1
			points [ [562, 513], [520, 504], [501, 488], [482, 467], [459, 450], [448, 444] ]
		}
		{
			route : 5
			type : 1
			points [ [588, 594], [564, 574], [533, 547], [502, 530], [482, 513], [472, 486], [445, 464], [433, 444] ]
		}
		{
			route : 6
			type : 1
			points [ [424, 652], [412, 619], [421, 589], [408, 526], [426, 506], [428, 471], [429, 440] ]
		}
		{
			route : 7
			type : 2
			points [ [803, 916], [789, 926], [774, 935], [760, 925], [757, 914], [748, 918], [738, 910], [721, 897], [718, 885], [708, 885], [676, 858], [674, 852], [661, 847], [654, 840], [653, 833], [642, 823], [631, 822], [623, 811], [607, 809], [595, 794], [596, 776], [585, 761], [583, 745], [581, 735], [570, 727], [567, 711], [569, 671], [580, 647], [583, 628], [598, 611], [594, 592], [593, 569], [588, 551], [580, 525], [568, 505], [552, 498], [538, 489], [522, 471], [518, 456], [506, 437], [491, 417], [473, 401], [458, 375], [449, 371], [439, 385], [425, 396], [414, 412] ]
		}
		{
			route : 8
			type : 2
			points [ [1167, 1334], [1177, 1322], [1169, 1283], [1162, 1251], [1132, 1210], [1098, 1079], [1025, 913], [920, 780], [887, 724], [854, 686], [729, 567], [702, 507], [694, 478], [672, 446], [638, 419], [653, 403], [647, 387], [634, 366], [640, 352], [611, 335], [555, 336], [494, 351], [434, 379], [423, 406] ]
		}
		{
			route : 9
			type : 1
			points [ [809, 586], [784, 557], [751, 542], [726, 500], [706, 490], [679, 496], [634, 501], [602, 502], [585, 507], [555, 514], [541, 519], [504, 510], [477, 470], [461, 457], [440, 443] ]
		}
		{
			route : 10
			type : 2
			points [ [861, 288], [847, 287], [837, 301], [800, 326], [771, 341], [730, 339], [686, 359], [658, 355], [633, 342], [609, 327], [588, 326], [530, 333], [483, 342], [421, 368], [409, 391], [409, 414] ]
		}
		{
			route : 11
			type : 2
			points [ [789, 1359], [844, 1304], [864, 1318], [897, 1250], [903, 1223], [889, 1209], [896, 1179], [883, 1156], [884, 1130], [881, 1097], [876, 1060], [862, 1033], [814, 989], [825, 943], [815, 908], [774, 935], [753, 915], [719, 898], [717, 884], [702, 883], [674, 852], [650, 829], [624, 818], [602, 804], [593, 772], [579, 734], [568, 712], [569, 666], [597, 608], [590, 543], [568, 505], [538, 489], [507, 441], [476, 425], [451, 418] ]
		}
		{
			route : 12
			type : 2
			points [ [905, 82], [885, 87], [867, 111], [852, 216], [846, 262], [816, 302], [769, 326], [726, 325], [683, 344], [658, 343], [608, 322], [572, 322], [515, 329], [448, 350], [420, 375], [415, 413] ]
		}
		{
			route : 13
			type : 2
			points [ [878, 148], [853, 158], [837, 256], [811, 294], [772, 316], [721, 319], [681, 337], [655, 335], [614, 317], [551, 319], [511, 323], [454, 341], [421, 362], [404, 389], [413, 415] ]
		}
		{
			route : 14
			type : 1
			points [ [587, 488], [555, 504], [533, 501], [515, 485], [501, 470], [487, 460], [469, 454], [455, 437] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [519, 492], image : 13856, expanded_image : 1 }
		{ pos : [503, 495], image : 13855, expanded_image : 0 }
		{ pos : [569, 576], image : 13856, expanded_image : 1 }
		{ pos : [551, 551], image : 13858, expanded_image : 3 }
		{ pos : [515, 505], image : 13864, expanded_image : 9 }
		{ pos : [794, 956], image : 13868, expanded_image : 13 }
		{ pos : [819, 964], image : 13869, expanded_image : 14 }
		{ pos : [844, 1282], image : 13868, expanded_image : 13 }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [530, 454] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
	]

	vars {
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission49]
function mission49_on_start(ev) {
	__image_request_pak(PACK_ENEMY_PHOENICIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -305
	__scenario_monuments.first = 29
	__scenario_monuments.second = 28
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_ptolemy_alexandria")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_10_PHOENICIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}
