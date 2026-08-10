log_info("akhenaten: mission 51 alexandria_3 started")

// Full empire redefine (CC51). Dump 2026-08-01 Cleop.
// MM briefing: message_mission_cleopatra_alexandria (445) — *The Legacy of a Queen*.
// Pak map subtitle: "The Legacy of Cleopatra" (UI uses start_message subtitle).
// Rank 10. Year -40. Enemy ENEMY_9_PERSIAN. Empire id 0, image_id 26.
// Win: pop 10000 / culture 80 / prosperity 70 / monuments 24 /
//      kingdom 80 / housing 6x lv19 / time_limit OFF (milestones 5/10/15).
// Monuments: first=30 Caesareum, second=27 Mausoleum (gr198 skin 2).
// Rating: Caesareum W=8 + Mausoleum W=5 → trunc(2.25*13+4.5)=33 ≥ goal 24.
// Burial: weapons4 linen4 gems5 luxury7 papyrus2. Gods: Ra(2) Ptah(1) Bast(1).
// Rome sells weapons; Enkomi marble+timber. Orphans Migdol/Buhen/Kyrene → route 0.
// SKIP empty map_obj idx=8. Chain invasion x1 (i=39). next_mission 52 (Actium §13.15).

mission51 { // Cleopatra's Alexandria - The Legacy of a Queen
	map_file : "data/maps/m_051_alexandria_3.map"
	start_message : "message_mission_cleopatra_alexandria"
	selection_title : "Cleopatra's Alexandria"
	player_rank : 10
	carry_monuments : true

	next_mission : 52

	// pak Normal funds=56000 loan=4000 debt_interest=7 -> int_dcy around Normal.
	initial_funds [112000, 74670, 56000, 37520, 29680]
	rescue_loans [8000, 5330, 4000, 2680, 2120]
	debt_interest [4, 5, 7, 9, 11]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C51_mission.mp3"
		victory : "Voice/Mission/C51_victory.mp3"
	}

	// buildings[] synced to pak_editor_allow: +gold/chariot/senet/zoo/transport;
	// -water_lift/academy/warship. Monuments: Caesareum + Mausoleum (pak first/second).
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
		BUILDING_CAESAREUM, BUILDING_MAUSOLEUM,
	]

	win_criteria {
		population    {enabled : true, goal : 10000 }
		culture       {enabled : true, goal : 80 }
		prosperity    {enabled : true, goal : 70 }
		monuments     {enabled : true, goal : 24 }
		kingdom       {enabled : true, goal : 80 }
		housing_count {enabled : true, goal : 6 }
		housing_level {enabled : true, goal : 19 }
		time_limit    {enabled : false, years : 12 }
		milestone25_year : 5
		milestone50_year : 10
		milestone75_year : 15
	}

	entry_point [207, 96]
	exit_point [169, 167]
	river_entry_point [94, 20]
	river_exit_point [127, 16]
	// pak inv land/sea empty - omit (chain invasion falls back to map exit).
	fishing_points [
		[80, 37], [115, 10], [127, 22], [89, 39], [104, 16]
	]
	herd_points_predator [ [176, 150], [75, 179], [69, 152] ]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 4 }
		{ resource: RESOURCE_LINEN, required: 4 }
		{ resource: RESOURCE_GEMS, required: 5 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 7 }
		{ resource: RESOURCE_PAPYRUS, required: 2 }
	]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 0, month : 8 }
			item { value : RESOURCE_TIMBER }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=1
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 2
			on_refusal_action : -1
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=2
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 4
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=3
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 7, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 4
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=4
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 7 }
			months_initial : 10
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
		{ // pak i=5
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 7 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 5 }
			months_initial : 11
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 6
			on_refusal_action : 39
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=6
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 5, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=7
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
			city_id : 8
		}
		{ // pak i=8
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=9
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 0, month : 0 }
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
			city_id : 8
		}
		{ // pak i=10
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 3 }
			item { value : RESOURCE_BEER }
			amount { value : 7 }
			months_initial : 8
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 11
			on_refusal_action : 12
			on_too_late_action : 11
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=11
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=12
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=13
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 9 }
			item { value : RESOURCE_TROOPS }
			amount { value : 6 }
			months_initial : 7
			location_fields [ 16, 16, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 9
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=14
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 8 }
			item { value : RESOURCE_FISH }
			amount { value : 13 }
			months_initial : 12
			location_fields [ 11, -1, 10, 12 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 9
			on_refusal_action : 7
			on_too_late_action : 7
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 4
		}
		{ // pak i=15
			type : EVENT_TYPE_LOCUSTS
			time { year : 9, month : 4 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 16
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=16
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 26 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=17
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 10, month : 1 }
			item { value : RESOURCE_GEMS }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 18
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=18
			type : EVENT_TYPE_REQUEST
			time { year : 0, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 6 }
			months_initial : 9
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 19
			on_refusal_action : 20
			on_too_late_action : 19
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=19
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_GEMS }
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
			city_id : 6
		}
		{ // pak i=20
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 3, month : 0 }
			item { value : RESOURCE_GEMS }
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
		{ // pak i=21
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 10, month : 3 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 10, 10, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 22
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=22
			type : EVENT_TYPE_REQUEST
			time { year : 11, month : 11 }
			item { value : RESOURCE_LINEN }
			amount { value : 9 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 2
			on_refusal_action : 23
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=23
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
		{ // pak i=24
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 4 }
			item { value : RESOURCE_TROOPS }
			amount { value : 23 }
			months_initial : 6
			location_fields [ 11, 11, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 6
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{ // pak i=25
			type : EVENT_TYPE_LOCUSTS
			time { year : 19, month : 4 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 16
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=26
			type : EVENT_TYPE_REQUEST
			time { year : 16, month : 2 }
			item { value : RESOURCE_TROOPS }
			amount { value : 25 }
			months_initial : 5
			location_fields [ 16, 16, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 9
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=27
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 6, month : 6 }
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
			city_id : 4
		}
		{ // pak i=28
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 13, month : 2 }
			item { value : 1 }
			amount { value : 1 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=29
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 21, month : 10 }
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
		{ // pak i=30
			type : EVENT_TYPE_REQUEST
			time { year : 15, month : 1 }
			item { value : RESOURCE_BEER }
			amount { value : 10 }
			months_initial : 9
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 31
			on_refusal_action : 32
			on_too_late_action : 33
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 5
		}
		{ // pak i=31
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_LINEN }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=32
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=33
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_BARLEY }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=34
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 14, month : 3 }
			item { value : RESOURCE_MARBLE }
			amount { value : 29 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
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
			time { year : 0, month : 0 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 12 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 36
			on_refusal_action : 38
			on_too_late_action : 37
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=36
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 10 }
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
		{ // pak i=37
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 4, month : 0 }
			item { value : RESOURCE_MARBLE }
			amount { value : 7 }
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
		{ // pak i=38
			type : EVENT_TYPE_DEMAND_DECREASE
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
			city_id : 8
		}
		{ // pak i=39
			type : EVENT_TYPE_INVASION
			time { year : 6, month : 0 }
			item { value : 1 }
			amount { value : 0 }
			months_initial : 12
			location_fields [ 9, -1, 9, 10 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{ // pak i=40
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 0, month : 6 }
			item { value : RESOURCE_CHICKPEAS }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 41
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=41
			type : EVENT_TYPE_REQUEST
			time { year : 10, month : 0 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 5 }
			months_initial : 10
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 9
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=42
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 4, month : 3 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
	]

	map_background : {pack:PACK_EMPIRE, id:26}

	hide_pak_cities : true
	cities [
		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [410, 646]
			route : 11
			is_open : false
			cost_to_open : 235
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT ]
			buys [ RESOURCE_FISH, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
			]
		}
		{
			name : "Enkomi"
			idx : 1
			pos : [679, 49]
			route : 4
			is_open : false
			cost_to_open : 670
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_TIMBER, RESOURCE_MARBLE ]
			buys [ RESOURCE_GRAIN, RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_MARBLE, limit: 4000 }
			]
		}
		{
			name : "Gaza"
			idx : 2
			pos : [853, 275]
			route : 6
			is_open : false
			cost_to_open : 620
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Iunet"
			idx : 3
			pos : [783, 892]
			route : 12
			is_open : false
			cost_to_open : 990
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 1500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}
		{
			name : "Knossos"
			idx : 4
			pos : [190, 133]
			route : 3
			is_open : false
			cost_to_open : 430
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_POTTERY ]
			buys [ RESOURCE_GRAIN, RESOURCE_BEER, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Kyrene"
			idx : 5
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Men-nefer"
			idx : 6
			pos : [545, 487]
			route : 8
			is_open : false
			cost_to_open : 150
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Athens"
			idx : 7
			pos : [27, 7]
			route : 2
			is_open : false
			cost_to_open : 700
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_GEMS, RESOURCE_MARBLE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_MARBLE, limit: 2500 }
			]
		}
		{
			name : "Pwenet"
			idx : 9
			pos : [1133, 1325]
			route : 13
			is_open : false
			cost_to_open : 1500
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Tyre"
			idx : 10
			pos : [879, 124]
			route : 5
			is_open : false
			cost_to_open : 750
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_GRAIN, RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
			]
		}
		{
			name : "Alexandria"
			idx : 27
			pos : [404, 390]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_FISH, RESOURCE_BARLEY, RESOURCE_REEDS ]
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
			route : 9
			trade : false
			cost_to_open : 165
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Meidum"
			idx : 33
			pos : [568, 581]
			route : 10
			trade : false
			cost_to_open : 240
			type : EMPIRE_CITY_EGYPTIAN
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
			route : 7
			is_open : false
			cost_to_open : 515
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Buhen"
			idx : 41
			pos : [763, 1344]
			route : 0
			trade : false
			cost_to_open : 1560
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Byblos"
			idx : 42
			pos : [906, 64]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Rome"
			idx : 43
			pos : [0, 207]
			route : 1
			is_open : false
			cost_to_open : 820
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS ]
			buys [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [37, 228], [57, 247], [113, 265], [212, 323], [398, 387], [413, 411] ]
		}
		{
			route : 2
			type : 2
			points [ [50, 40], [65, 76], [113, 99], [213, 116], [264, 128], [281, 151], [394, 377], [412, 409] ]
		}
		{
			route : 3
			type : 2
			points [ [226, 141], [257, 136], [276, 156], [387, 376], [413, 411] ]
		}
		{
			route : 4
			type : 2
			points [ [718, 72], [740, 91], [682, 132], [645, 161], [602, 165], [538, 322], [485, 336], [421, 380], [409, 394], [413, 409] ]
		}
		{
			route : 5
			type : 2
			points [ [875, 145], [861, 153], [856, 197], [844, 277], [792, 324], [728, 331], [677, 353], [603, 325], [540, 329], [485, 344], [426, 385], [416, 396], [415, 410] ]
		}
		{
			route : 6
			type : 2
			points [ [854, 292], [839, 296], [795, 333], [734, 339], [675, 361], [599, 332], [540, 337], [486, 352], [451, 375], [421, 399], [418, 411] ]
		}
		{
			route : 7
			type : 1
			points [ [799, 579], [762, 549], [744, 529], [720, 495], [695, 490], [654, 495], [594, 508], [565, 532], [527, 526], [496, 511], [482, 475], [440, 445] ]
		}
		{
			route : 8
			type : 1
			points [ [543, 503], [521, 488], [514, 486], [500, 473], [482, 464], [450, 447] ]
		}
		{
			route : 9
			type : 1
			points [ [584, 481], [563, 483], [546, 481], [526, 450], [503, 461], [474, 454], [457, 444] ]
		}
		{
			route : 10
			type : 1
			points [ [576, 584], [580, 554], [556, 541], [502, 521], [488, 510], [481, 475], [440, 446] ]
		}
		{
			route : 11
			type : 1
			points [ [427, 652], [425, 621], [434, 591], [440, 564], [438, 523], [424, 493], [427, 466], [430, 446] ]
		}
		{
			route : 12
			type : 2
			points [ [791, 923], [773, 933], [758, 921], [755, 915], [745, 917], [718, 894], [715, 888], [701, 882], [676, 861], [675, 851], [655, 840], [641, 821], [631, 820], [625, 813], [613, 812], [598, 789], [594, 770], [586, 757], [581, 735], [568, 725], [569, 710], [572, 663], [583, 645], [585, 629], [603, 609], [593, 579], [590, 559], [584, 526], [571, 514], [544, 494], [529, 481], [519, 459], [513, 444], [477, 428], [451, 421] ]
		}
		{
			route : 13
			type : 2
			points [ [1168, 1332], [1176, 1322], [1161, 1251], [1093, 1081], [1024, 912], [913, 780], [891, 729], [851, 688], [723, 559], [701, 505], [694, 475], [670, 446], [630, 426], [652, 402], [634, 364], [639, 354], [597, 335], [527, 344], [484, 360], [440, 388], [417, 408] ]
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
	]

	vars {
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission51]
function mission51_on_start(ev) {
	__image_request_pak(PACK_ENEMY_PERSIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -40
	__scenario_monuments.first = 30
	__scenario_monuments.second = 27
	__scenario_monuments.third = 0
	// pak alt_predator=1 (has_animals off — flag still carried for map fidelity / 50·52 parity).
	scenario.alt_predator_type = true
	mission_show_start_message(mission, "message_mission_cleopatra_alexandria")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_9_PERSIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}
