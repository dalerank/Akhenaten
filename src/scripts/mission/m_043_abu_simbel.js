log_info("akhenaten: mission 43 abu simbel started")

mission43 {
	map_file : "data/maps/m_043_abu_simbel.map"

	// Map points from data/maps/m_043_abu_simbel.map.
	herd_points_predator [ [43, 19], [14, 60] ]

	start_message : "message_mission_abu_simbel"
	selection_title : "Abu Simbel"
	player_rank : 5
	carry_troops : ["infantry"]

	next_mission : 44

	initial_funds [16000, 10670, 8000, 5360, 4240]
	rescue_loans [4000, 2670, 2000, 1340, 1060]
	debt_interest [6, 8, 10, 12, 14]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C43_mission.mp3"
		victory : "Voice/Mission/C43_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_TRANSPORT_WHARF, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_CATTLE_RANCH,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_SANDSTONE_QUARRY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
		BUILDING_ABU_SIMBEL,
	]

	win_criteria {
		population    {enabled : true, goal : 2200 }
		culture       {enabled : true, goal : 35 }
		prosperity    {enabled : true, goal : 35 }
		monuments     {enabled : true, goal : 44 }
		kingdom       {enabled : true, goal : 80 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 10 }
		milestone25_year : 5
		milestone50_year : 9
		milestone75_year : 13
	}

	entry_point [88, 32]
	exit_point [95, 72]
	river_entry_point [80, 87]
	river_exit_point [50, 5]
	disembark_points [ [62, 40], [59, 31] ]
	invasion_points_land [ [51, 51] ]
	invasion_points_sea [ [105, 4] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_BLOOD_RIVER
			time { year : 4, month : 10 }
			item { value : 1 }
			amount { value : 3 }
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
		{
			type : EVENT_TYPE_FROGS
			time { year : 10, month : 4 }
			item { value : 1 }
			amount { value : 4 }
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
		{
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 3, month : 3 }
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
			city_id : 6
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 1 }
			item { value : RESOURCE_SANDSTONE }
			amount { value : 34 }
			months_initial : 12
			location_fields [ 14, 14, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 4
			on_refusal_action : 7
			on_too_late_action : 6
			on_defeat_action : -1
			sender_faction : 1
			subtype : 4
			city_id : 4
		}
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 6
		}
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
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
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 2 }
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
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 10 }
			item { value : RESOURCE_LINEN }
			amount { value : 15 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 0, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 9 }
			months_initial : 11
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 5
			on_refusal_action : 7
			on_too_late_action : 4
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 3 }
			item { value : RESOURCE_FIGS }
			amount { value : 7 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 11
			on_refusal_action : 12
			on_too_late_action : 13
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			tag_id : 2010
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_DEBEN }
			amount { value : 334 }
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
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 25 }
			months_initial : 6
			location_fields [ 2, -1, 1, 3 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
			invasion_attack_target : 4
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 3 }
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
		{
			type : EVENT_TYPE_REQUEST
			time { year : 2, month : 4 }
			item { value : RESOURCE_FIGS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 15
			on_refusal_action : 6
			on_too_late_action : 15
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 4
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
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
			subtype : 2
			city_id : 8
		}
		{
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 14, month : 6 }
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
		{
			type : EVENT_TYPE_WAGE_INCREASE
			time { year : 4, month : 0 }
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
		{
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 10 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 6 }
			months_initial : 9
			location_fields [ 14, 14, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 19
			on_refusal_action : 7
			on_too_late_action : 4
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_LINEN }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 14, 14, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 5
			on_refusal_action : 4
			on_too_late_action : 4
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 8, month : 1 }
			item { value : 1 }
			amount { value : 27 }
			months_initial : 9
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 21
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 3
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 22
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 0 }
			item { value : RESOURCE_TROOPS }
			amount { value : 12 }
			months_initial : 8
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 23
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 1
			subtype : 2
			city_id : 5
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 24
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 7
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 0, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 4
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 7 }
			item { value : RESOURCE_POTTERY }
			amount { value : 11 }
			months_initial : 7
			location_fields [ 5, -1, 5, 6 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 4
			on_refusal_action : 7
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 3 }
			amount { value : 15 }
			months_initial : 8
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
			invasion_attack_target : 0
		}
	]
	map_background : {pack:PACK_EMPIRE, id:21}

	hide_pak_cities : true
	cities [
		{
			name : "Abu Simbel"
			idx : 27
			pos : [777, 1328]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_MEAT, RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_SANDSTONE ]
		}
		{
			name : "Men-nefer"
			idx : 1
			pos : [575, 494]
			route : 4
			is_open : false
			cost_to_open : 1300
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CHICKPEAS, RESOURCE_BEER, RESOURCE_TIMBER ]
			buys [ RESOURCE_BARLEY, RESOURCE_LUXURY_GOODS, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
		{
			name : "Waset"
			idx : 4
			pos : [818, 925]
			route : 3
			is_open : false
			cost_to_open : 650
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_STRAW, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Sumur"
			idx : 26
			pos : [874, 39]
			route : 7
			is_open : false
			cost_to_open : 2000
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_FIGS, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
			]
		}
		{
			name : "Heh"
			idx : 28
			pos : [702, 1412]
			route : 1
			is_open : false
			cost_to_open : 140
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS ]
			buys [ RESOURCE_MEAT, RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 4000 }
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
			]
		}
		{
			name : "Kerma"
			idx : 30
			pos : [755, 1514]
			route : 2
			is_open : false
			cost_to_open : 400
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_FIGS, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Pwenet"
			idx : 31
			pos : [1137, 1343]
			route : 5
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}
		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [424, 653]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Qadesh"
			idx : 3
			pos : [952, 2]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Jericho"
			idx : 22
			pos : [901, 253]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Enkomi"
			idx : 23
			pos : [692, 56]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Timna"
			idx : 24
			pos : [898, 469]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Kharga Oasis"
			idx : 29
			pos : [648, 1153]
			route : 6
			is_open : false
			cost_to_open : 150
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Abu"
			idx : 32
			pos : [860, 1164]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Piramesse"
			idx : 33
			pos : [582, 405]
			route : 0
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[740, 1432], [762, 1416], [781, 1395], [789, 1377], [800, 1366], [800, 1355]
			]
		}
		{
			route : 2
			type : 2
			points [
				[750, 1534], [736, 1525], [723, 1513], [713, 1504], [715, 1500], [730, 1501],
				[736, 1496], [730, 1482], [712, 1480], [702, 1473], [694, 1464], [717, 1457],
				[718, 1449], [735, 1436], [758, 1416], [783, 1392], [788, 1378], [800, 1367],
				[803, 1358]
			]
		}
		{
			route : 3
			type : 2
			points [
				[817, 956], [821, 972], [813, 986], [826, 998], [833, 1010], [852, 1025],
				[867, 1036], [866, 1048], [879, 1066], [878, 1092], [884, 1103], [879, 1111],
				[887, 1134], [883, 1160], [892, 1186], [894, 1197], [890, 1208], [901, 1219],
				[905, 1231], [891, 1268], [878, 1302], [864, 1320], [848, 1304], [824, 1319],
				[813, 1335]
			]
		}
		{
			route : 4
			type : 2
			points [
				[586, 527], [588, 548], [593, 585], [598, 595], [597, 610], [584, 629],
				[583, 647], [570, 672], [567, 723], [582, 740], [595, 775], [598, 794],
				[621, 814], [640, 823], [652, 841], [673, 851], [678, 864], [702, 883],
				[719, 888], [721, 900], [743, 917], [760, 912], [763, 924], [774, 935],
				[813, 906], [825, 924], [820, 961], [811, 987], [834, 1014], [864, 1034],
				[867, 1052], [878, 1066], [884, 1102], [879, 1118], [886, 1136], [883, 1167],
				[895, 1196], [891, 1211], [906, 1231], [884, 1284], [864, 1320], [846, 1303],
				[823, 1319], [810, 1336]
			]
		}
		{
			route : 5
			type : 1
			points [
				[1137, 1347], [1116, 1348], [1087, 1317], [1048, 1307], [1012, 1294], [974, 1282],
				[947, 1275], [930, 1285], [915, 1315], [889, 1332], [855, 1339], [815, 1342]
			]
		}
		{
			route : 6
			type : 1
			points [
				[662, 1184], [659, 1204], [664, 1221], [682, 1237], [739, 1264], [753, 1301],
				[782, 1340]
			]
		}
		{
			route : 7
			type : 2
			points [
				[889, 71], [864, 118], [830, 296], [730, 337], [639, 357], [612, 390],
				[589, 404], [585, 425], [568, 441], [555, 477], [573, 507], [587, 539],
				[596, 591], [599, 608], [584, 633], [571, 672], [569, 725], [584, 746],
				[599, 795], [640, 823], [652, 841], [675, 852], [698, 879], [720, 888],
				[727, 905], [744, 917], [759, 916], [775, 937], [815, 907], [828, 928],
				[820, 963], [813, 988], [834, 1014], [865, 1036], [868, 1056], [878, 1067],
				[881, 1102], [887, 1133], [883, 1166], [897, 1193], [892, 1210], [906, 1230],
				[866, 1320], [846, 1302], [824, 1316], [812, 1333]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [906, 49], image : 13863, expanded_image : 8 }
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
		{ name : "#palestine", pos : [865, 144] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [908, 93] }
		{ name : "#canaan", pos : [854, 294] }
	]


	vars {
		start_message_shown : false
		pharaoh_favour_invasion_done : false
		inv20_done : false
		inv20_seq : 0
		inv20_chain_done : false
		inv12_done : false
	}
}

[es=event_mission_start, mission=mission43]
function mission43_on_start(ev) {
	log_info("mission43: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_KUSHITE)
	scenario.start_year = -1270
	scenario.climate = 2
	__scenario_monuments.first = 37
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_abu_simbel")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

function mission43_invasion_outcome(seq) {
	if (!seq) {
		return -1
	}
	var n = city.invasion_history_count()
	for (var i = 0; i < n; i++) {
		var h = city.invasion_history_at(i)
		if (h.seq == seq) {
			return h.outcome
		}
	}
	return -1
}

function mission43_fire_inv20_win_chain() {
	city.create_chain_event({
		tag_id: 1021,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 8,
		subtype: 3,
		city_id: 5,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
	city.create_chain_event({
		tag_id: 1004,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 2,
		subtype: 3,
		city_id: 6
	})
	var newtrade = city.create_chain_event({
		tag_id: 1024,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 8,
		subtype: 2,
		city_id: 5
	})
	newtrade.set_completed_action_tag(1004)
	var conquered = city.create_chain_event({
		tag_id: 1023,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 8,
		subtype: 1,
		city_id: 7
	})
	conquered.set_completed_action_tag(1024)
	city.create_chain_event({
		tag_id: 1007,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 5,
		subtype: 3,
		city_id: 8
	})
	var troops = city.create_good_request({
		tag_id: 1022,
		resource: RESOURCE_TROOPS,
		amount: 12,
		months_initial: 8,
		subtype: 2,
		city_id: 5
	})
	troops.set_sender_faction(1)
	troops.set_completed_action_tag(1023)
	troops.set_refusal_action_tag(1007)
	troops.execute()
}

[es=event_advance_month, mission=mission43]
function mission43_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	log_info("akhenaten: mission 43 pharaoh favour invasion size=15 kr=" + city.rating_kingdom)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: 15,
		invasion_id: 26,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_FOOD
	})
}

[es=event_advance_month, mission=mission43]
function mission43_calendar_invasion_i20(ev) {
	if (mission.inv20_done) {
		if (mission.inv20_chain_done || mission.inv20_seq <= 0) {
			return
		}
		var outcome = mission43_invasion_outcome(mission.inv20_seq)
		if (outcome == 1) {
			mission.inv20_chain_done = true
			log_info("akhenaten: mission 43 invasion x27 won -> LOST_TRADE chain", {seq: mission.inv20_seq})
			mission43_fire_inv20_win_chain()
		} else if (outcome == 2 || outcome == 3) {
			mission.inv20_chain_done = true
			log_info("akhenaten: mission 43 invasion x27 lost/retreat - skip chain", {outcome: outcome})
		}
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 1)) {
		return
	}
	mission.inv20_done = true
	__image_request_pak(PACK_ENEMY_KUSHITE)
	mission.inv20_seq = city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_6_KUSHITE,
		size: 27,
		invasion_id: 20,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_TROOPS
	})
	log_info("akhenaten: mission 43 enemy x27 calendar", {seq: mission.inv20_seq})
}

[es=event_request_cleared, mission=mission43]
function mission43_on_request_cleared(ev) {
	if (mission.inv12_done || ev.tag_id != 2010) {
		return
	}
	if (mission_request_outcome(ev) != "refuse") {
		return
	}
	mission.inv12_done = true
	__image_request_pak(PACK_ENEMY_KUSHITE)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_6_KUSHITE,
		size: 25,
		invasion_id: 12,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
	log_info("akhenaten: mission 43 enemy x25 after figs refuse", {ev:ev})
}
