log_info("akhenaten: mission 37 hetepsensusret started")

// Empire id=23. Enemy ASSYRIAN (pak). Gods Osiris/Ra/Ptah/Bast x2. Rank 10.
// Funds 2000/3000/20. Win pop 12000 / C80 / Pr80 / M70 / K75 / house lvl 14.
// Monuments 27/7/5 = Mausoleum skin2 + Grand Mudbrick Complex + Large Mudbrick
//   (W=5+44+12 -> clamp 100 >=70). Soft goal 70. Briefing "true>Khufu" = flavor.
// Burial x5 all 32 (pottery/linen/luxury/papyrus/weapons). next_mission -1 (no Cleo).
// SKIP map_obj idx=11. Routes 1-11 copy. Farafra NEW_TRADE cosmetic (no route).
// Favour egypt x40; pak inv empty -> land-proxy [80,40] near entry.
// Truncate junk late>=50 on non-request; defeat 0/998/999 -> -1.
// Dump 2026-08-01. events[] engine (Seti/Tanis pattern).

mission37 { // Hetepsensusret (Kahun) — The Glory of Pharaoh
	map_file : "data/maps/m_037_hetepsensusret.map"
	start_message : "message_mission_kahun"
	selection_title : "Hetepsensusret"
	player_rank : 10

	next_mission : -1

	// pak Normal funds=2000 loan=3000 debt_interest=20 → int_dcy around Normal.
	initial_funds [4000, 2660, 2000, 1340, 1060]
	rescue_loans [6000, 4000, 3000, 2000, 1590]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		// pak animals=0; enable so prey update after create_herds (hunting lodge).
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/237_mission.mp3"
		victory : "Voice/Mission/237_victory.mp3"
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
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MAUSOLEUM, BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX, BUILDING_LARGE_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	// Soft goal 70; engine weights Mausoleum+Grand Mudbrick Complex+Large Mudbrick W=5+44+12 → clamp 100.
	win_criteria {
		population    {enabled : true, goal : 12000 }
		culture       {enabled : true, goal : 80 }
		prosperity    {enabled : true, goal : 80 }
		monuments     {enabled : true, goal : 70 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 14 }
		milestone25_year : 10
		milestone50_year : 20
		milestone75_year : 30
	}

	entry_point [80, 34]
	exit_point [8, 119]
	river_entry_point [165, 171]
	river_exit_point [122, 11]
	// pak inv_land/sea empty — land-proxy near entry for favour egypt×40.
	invasion_points_land [ [80, 40] ]
	fishing_points [
		[135, 90], [155, 170], [60, 164]
	]
	// pak type FIGURE_NONE — spawn slots only.
	herd_points_predator [
		[144, 160], [26, 131], [106, 24], [139, 106]
	]
	herd_points_prey [
		[39, 141], [80, 185]
	]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 32 }
		{ resource: RESOURCE_POTTERY, required: 32 }
		{ resource: RESOURCE_LINEN, required: 32 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 32 }
		{ resource: RESOURCE_PAPYRUS, required: 32 }
	]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 0
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=1
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 7 }
			months_initial : 0
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=2
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 0
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=3
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 32
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=4
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=5
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=6
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 25, month : 2 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=7
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 19
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=8
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 16, month : 0 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=9
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
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
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 15, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 10, 10, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=11
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 35, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 11, 11, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=12
			type : EVENT_TYPE_REQUEST
			time { year : 0, month : 11 }
			item { value : RESOURCE_TIMBER }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 15
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=13
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 8 }
			item { value : RESOURCE_DEBEN }
			amount { value : 500 }
			months_initial : 6
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 15
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 4
			city_id : 5
		}
		{ // pak i=14
			type : EVENT_TYPE_REQUEST
			time { year : 2, month : 8 }
			item { value : RESOURCE_GAMEMEAT }
			amount { value : 11 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 15
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=15
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=16
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 1 }
			item { value : RESOURCE_BRICKS }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 17
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 4
			city_id : 5
		}
		{ // pak i=17
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 2, month : 8 }
			item { value : RESOURCE_LIMESTONE }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=18
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 3 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 12 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 7
			on_refusal_action : 1
			on_too_late_action : 7
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=19
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 36, month : 8 }
			item { value : RESOURCE_LIMESTONE }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{ // pak i=20
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 6 }
			item { value : RESOURCE_FISH }
			amount { value : 18 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 21
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{ // pak i=21
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 3
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=22
			type : EVENT_TYPE_REQUEST
			time { year : 11, month : 0 }
			item { value : RESOURCE_REEDS }
			amount { value : 26 }
			months_initial : 9
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 4
			on_refusal_action : 1
			on_too_late_action : 4
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=23
			type : EVENT_TYPE_REQUEST
			time { year : 13, month : 8 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 32 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 24
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=24
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 8 }
			item { value : RESOURCE_BRICKS }
			amount { value : 64 }
			months_initial : 0
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=25
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 17, month : 2 }
			item { value : RESOURCE_BRICKS }
			amount { value : 73 }
			months_initial : 0
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=26
			type : EVENT_TYPE_FAILED_FLOOD
			time { year : 20, month : 1 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 27
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=27
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 8 }
			item { value : RESOURCE_FISH }
			amount { value : 29 }
			months_initial : 9
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 29
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 8
		}
		{ // pak i=28
			type : EVENT_TYPE_FAILED_FLOOD
			time { year : 24, month : 1 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 27
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=29
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 6, month : 8 }
			item { value : RESOURCE_BRICKS }
			amount { value : 42 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{ // pak i=30
			type : EVENT_TYPE_REQUEST
			time { year : 22, month : 3 }
			item { value : RESOURCE_GRAIN }
			amount { value : 24 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 33
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 5
		}
		{ // pak i=31
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 20, month : 10 }
			item { value : RESOURCE_SANDSTONE }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=32
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 72, month : 8 }
			item { value : RESOURCE_SANDSTONE }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=33
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 0
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 5
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{ // pak i=34
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 18, month : 8 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=35
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 60, month : 8 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=36
			type : EVENT_TYPE_REQUEST
			time { year : 30, month : 2 }
			item { value : RESOURCE_TROOPS }
			amount { value : 15 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 0
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : 66
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{ // pak i=37
			type : EVENT_TYPE_REQUEST
			time { year : 31, month : 6 }
			item { value : RESOURCE_TROOPS }
			amount { value : 36 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 0
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : 66
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{ // pak i=38
			type : EVENT_TYPE_REQUEST
			time { year : 34, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 60 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 0
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : 66
			sender_faction : 0
			subtype : 1
			city_id : 8
		}
		{ // pak i=39
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 29, month : 8 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=40
			type : EVENT_TYPE_REQUEST
			time { year : 36, month : 7 }
			item { value : RESOURCE_TROOPS }
			amount { value : 36 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 41
			on_refusal_action : 1
			on_too_late_action : 41
			on_defeat_action : 66
			sender_faction : 0
			subtype : 1
			city_id : 6
		}
		{ // pak i=41
			type : EVENT_TYPE_MESSAGE
			time { year : 12, month : 11 }
			item { value : 1 }
			amount { value : 100 }
			months_initial : 8
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 42
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=42
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 11 }
			item { value : RESOURCE_TROOPS }
			amount { value : 24 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 43
			on_refusal_action : 1
			on_too_late_action : -1
			on_defeat_action : 66
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{ // pak i=43
			type : EVENT_TYPE_MESSAGE
			time { year : 12, month : 11 }
			item { value : 1 }
			amount { value : 100 }
			months_initial : 8
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 44
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 5
		}
		{ // pak i=44
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 6, month : 11 }
			item { value : 1 }
			amount { value : 250 }
			months_initial : 2
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=45
			type : EVENT_TYPE_PERFECT_FLOOD
			time { year : 40, month : 3 }
			item { value : 1 }
			amount { value : 250 }
			months_initial : 2
			location_fields [ 10, 10, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 46
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=46
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 11 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 24 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 0
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 4
		}
		{ // pak i=47
			type : EVENT_TYPE_REQUEST
			time { year : 45, month : 1 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 32 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 29
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=48
			type : EVENT_TYPE_FAILED_FLOOD
			time { year : 49, month : 3 }
			item { value : 1 }
			amount { value : 150 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 49
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=49
			type : EVENT_TYPE_REQUEST
			time { year : 49, month : 6 }
			item { value : RESOURCE_GAMEMEAT }
			amount { value : 19 }
			months_initial : 9
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 52
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 5
		}
		{ // pak i=50
			type : EVENT_TYPE_REQUEST
			time { year : 49, month : 5 }
			item { value : RESOURCE_GRAIN }
			amount { value : 19 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 53
			on_refusal_action : 1
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 6
		}
		{ // pak i=51
			type : EVENT_TYPE_REQUEST
			time { year : 49, month : 7 }
			item { value : RESOURCE_FISH }
			amount { value : 16 }
			months_initial : 9
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 54
			on_refusal_action : 1
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 8
		}
		{ // pak i=52
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_LIMESTONE }
			amount { value : 64 }
			months_initial : 2
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
		{ // pak i=53
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_SANDSTONE }
			amount { value : 64 }
			months_initial : 2
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
		{ // pak i=54
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_LINEN }
			amount { value : 32 }
			months_initial : 2
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=55
			type : EVENT_TYPE_REQUEST
			time { year : 55, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 32 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 56
			on_refusal_action : 57
			on_too_late_action : 57
			on_defeat_action : 57
			sender_faction : 0
			subtype : 1
			city_id : 5
		}
		{ // pak i=56
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 12, month : 0 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 2
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 58
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=57
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 12, month : 0 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 2
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 58
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=58
			type : EVENT_TYPE_REQUEST
			time { year : 96, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 17 }
			months_initial : 2
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 56
			on_refusal_action : 57
			on_too_late_action : 57
			on_defeat_action : 57
			sender_faction : 0
			subtype : 1
			city_id : 6
		}
		{ // pak i=59
			type : EVENT_TYPE_CONTAMINATED_WATER
			time { year : 60, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 3, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 60
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=60
			type : EVENT_TYPE_REQUEST
			time { year : 72, month : 0 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 14 }
			months_initial : 9
			location_fields [ 6, -1, 6, 9 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 61
			on_refusal_action : 62
			on_too_late_action : 62
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=61
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 9, month : 0 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 2
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 60
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=62
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 9, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 999, 999, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 60
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=63
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 2 }
			amount { value : 40 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : 64
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{ // pak i=64
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : 2 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 65
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{ // pak i=65
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : 2 }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
			invasion_attack_target : 4
		}
		{ // pak i=66
			type : EVENT_TYPE_MESSAGE
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 2
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=67
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 26, month : 0 }
			item { value : RESOURCE_BRICKS }
			amount { value : 96 }
			months_initial : 2
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=68
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 46, month : 6 }
			item { value : RESOURCE_LIMESTONE }
			amount { value : 96 }
			months_initial : 2
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
	]

	map_background : {pack:PACK_EMPIRE, id:23}
	hide_pak_cities : true
	cities [
		{
			name : "Hetepsenusret"
			idx : 5
			pos : [527, 588]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_FISH, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_TIMBER, RESOURCE_REEDS ]
		}
		{
			name : "Baki"
			idx : 2
			pos : [902, 1218]
			route : 1
			is_open : false
			cost_to_open : 1000
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
		{
			name : "Dakhla Oasis"
			idx : 3
			pos : [349, 1037]
			route : 6
			is_open : false
			cost_to_open : 650
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
			buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 2
			cost_to_open : 1000
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			// Display foreign; NEW_TRADE cosmetic (no polyline).
			name : "Farafra Oasis"
			idx : 4
			pos : [327, 831]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Itjtawy"
			idx : 6
			pos : [571, 551]
			route : 7
			cost_to_open : 400
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Knossos"
			idx : 7
			pos : [175, 131]
			route : 10
			cost_to_open : 2000
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Men-nefer"
			idx : 8
			pos : [545, 487]
			route : 8
			cost_to_open : 300
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Menat Khufu"
			idx : 9
			pos : [578, 720]
			route : 9
			cost_to_open : 600
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Mycenae"
			idx : 10
			pos : [15, 11]
			route : 11
			cost_to_open : 2000
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Pwenet"
			idx : 12
			pos : [1133, 1325]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Qadesh"
			idx : 13
			pos : [962, 10]
			route : 5
			cost_to_open : 950
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Rowarty"
			idx : 14
			pos : [612, 389]
			route : 3
			cost_to_open : 275
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Tyre"
			idx : 15
			pos : [877, 121]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Waset"
			idx : 16
			pos : [811, 968]
			route : 4
			cost_to_open : 750
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 1
			points [
				[922, 1235], [882, 1230], [851, 1229], [803, 1217], [784, 1200], [758, 1187],
				[739, 1182], [714, 1174], [697, 1168], [675, 1162], [663, 1157], [658, 1155],
				[643, 1152], [583, 1135], [439, 1122], [420, 1113], [402, 1105], [391, 1081],
				[376, 1031], [369, 1002], [365, 862], [368, 815], [376, 742], [405, 696],
				[446, 658], [495, 638], [551, 629]
			]
		}
		{
			route : 2
			type : 2
			points [
				[889, 1178], [884, 1157], [888, 1135], [878, 1114], [883, 1100], [875, 1089],
				[879, 1066], [867, 1052], [862, 1035], [849, 1019], [835, 1011], [824, 994],
				[809, 969], [811, 955], [818, 940], [818, 922], [805, 922], [791, 928],
				[782, 933], [749, 920], [735, 907], [729, 898], [648, 829], [587, 784],
				[572, 751], [561, 700], [566, 654], [564, 631], [557, 616], [558, 615]
			]
		}
		{
			route : 3
			type : 1
			points [
				[641, 412], [628, 425], [599, 442], [595, 448], [589, 458], [576, 465],
				[576, 475], [571, 484], [570, 495], [570, 504], [569, 508], [563, 556],
				[564, 579], [564, 611], [564, 614], [564, 615]
			]
		}
		{
			route : 4
			type : 2
			points [
				[825, 987], [818, 961], [828, 943], [826, 924], [818, 910], [809, 908],
				[782, 920], [760, 913], [741, 891], [706, 860], [594, 774], [570, 701],
				[577, 659], [575, 629], [559, 615], [558, 615]
			]
		}
		{
			route : 5
			type : 1
			points [
				[974, 29], [968, 55], [957, 80], [937, 108], [887, 117], [883, 170],
				[876, 202], [870, 232], [869, 267], [861, 298], [850, 320], [831, 334],
				[804, 351], [778, 361], [758, 368], [732, 368], [721, 381], [701, 391],
				[632, 434], [602, 458], [586, 473], [578, 487], [564, 507], [558, 557],
				[555, 604], [555, 617]
			]
		}
		{
			route : 6
			type : 1
			points [
				[366, 1054], [362, 1014], [352, 996], [351, 961], [351, 921], [349, 873],
				[349, 854], [349, 782], [355, 750], [358, 736], [366, 714], [375, 694],
				[381, 683], [386, 673], [456, 627], [475, 622], [491, 615], [504, 612],
				[526, 610], [550, 610], [553, 611], [553, 612]
			]
		}
		{
			route : 7
			type : 1
			points [
				[586, 574], [553, 614], [553, 614]
			]
		}
		{
			route : 8
			type : 1
			points [
				[563, 501], [553, 617], [553, 617]
			]
		}
		{
			route : 9
			type : 1
			points [
				[597, 739], [596, 688], [592, 678], [592, 657], [589, 641], [582, 631],
				[555, 616], [554, 616]
			]
		}
		{
			route : 10
			type : 1
			points [
				[198, 151], [242, 119], [283, 83], [330, 61], [380, 57], [396, 47],
				[403, 17], [491, 24], [536, 40], [619, 44], [669, 28], [729, 5],
				[754, 2], [843, 8], [841, 27], [867, 50], [890, 83], [867, 105],
				[859, 154], [849, 220], [843, 268], [834, 294], [807, 317], [766, 331],
				[706, 345], [682, 352], [638, 362], [622, 382], [605, 397], [591, 402],
				[584, 423], [557, 471], [557, 482], [558, 498], [547, 608], [549, 616]
			]
		}
		{
			route : 11
			type : 1
			points [
				[45, 29], [75, 13], [85, 14], [111, 18], [122, 11], [136, 10],
				[181, 10], [217, 5], [225, 10], [238, 26], [265, 34], [271, 49],
				[301, 54], [342, 69], [397, 63], [413, 27], [473, 30], [538, 49],
				[620, 54], [744, 9], [775, 12], [826, 11], [835, 34], [875, 81],
				[852, 102], [823, 282], [783, 308], [719, 317], [653, 336], [635, 355],
				[607, 385], [591, 393], [589, 394], [575, 410], [552, 463], [545, 498],
				[542, 552], [540, 598], [549, 615], [549, 615]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [537, 430], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [475, 515], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [562, 577], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [616, 707], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [635, 709], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [603, 428], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [596, 515], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [619, 732], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [634, 762], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [663, 810], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [575, 497], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [502, 533], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [922, 42], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [842, 965], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [869, 841], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [932, 1226], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [652, 1426], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [842, 979], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [868, 908], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [849, 907], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [708, 1394], image : "pharaoh_general/empire_bits_00121" }
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
		{ name : "#upper_egypt", pos : [686, 1000] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission37]
function mission37_on_start(ev) {
	__image_request_pak(PACK_ENEMY_ASSYRIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_kahun")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_1_ASSYRIAN)
	scenario.start_year = -1382
	scenario.climate = 0 // CLIMATE_CENTRAL (pak)
	// Gods from pak: Osiris/Ra/Ptah known, Bast patron — city.gods.set_known is bool-only
	// (would demote Bast PATRON→KNOWN); leave religion status from scenario load.
	__scenario_monuments.first = 27
	__scenario_monuments.second = 7
	__scenario_monuments.third = 5
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}
