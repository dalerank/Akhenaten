log_info("akhenaten: mission 44 ramses in the valley started")

mission44 {
	map_file : "data/maps/m_044_ramses_in_the_valley.map"

	// Map points from data/maps/m_044_ramses_in_the_valley.map.
	herd_points_predator [ [213, 113], [212, 105], [79, 52], [102, 86] ]

	start_message : "message_mission_ramses_valley"
	selection_title : "Ramses in the Valley"
	player_rank : 6
	carry_troops : ["archer", "infantry"]

	next_mission : -1

	initial_funds [30040, 20030, 15020, 10010, 7960]
	rescue_loans [6000, 4000, 3000, 2000, 1590]
	debt_interest [4, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C44_mission.mp3"
		victory : "Voice/Mission/C44_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD,
		BUILDING_BRICKLAYERS_GUILD, BUILDING_ARTISANS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_CHARIOTS_WORKSHOP, BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP, BUILDING_WEAPONSMITH,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_TRANSPORT_WHARF, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
		BUILDING_GRAND_ROYAL_TOMB,
	]

	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 50 }
		prosperity    {enabled : true, goal : 55 }
		monuments     {enabled : true, goal : 45 }
		kingdom       {enabled : true, goal : 100 }
		housing_count {enabled : true, goal : 6 }
		housing_level {enabled : true, goal : 17 }
		milestone25_year : 6
		milestone50_year : 12
		milestone75_year : 18
	}

	entry_point [142, 194]
	exit_point [152, 184]
	river_entry_point [188, 149]
	river_exit_point [111, 2]
	disembark_points [ [173, 128], [168, 81] ]
	invasion_points_land [ [125, 111] ]
	invasion_points_sea [ [212, 3] ]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 6 }
		{ resource: RESOURCE_LINEN, required: 16 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 20 }
		{ resource: RESOURCE_PAPYRUS, required: 8 }
		{ resource: RESOURCE_CHARIOTS, required: 6 }
	]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 2 }
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
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
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
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 2 }
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
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
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
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_BLOOD_RIVER
			time { year : 4, month : 4 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 11
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_FROGS
			time { year : 6, month : 7 }
			item { value : 1 }
			amount { value : 6 }
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
			type : EVENT_TYPE_HAILSTORM
			time { year : 10, month : 2 }
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
			city_id : 6
		}
		{
			type : EVENT_TYPE_LOCUSTS
			time { year : 14, month : 2 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 9
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 3 }
			amount { value : 27 }
			months_initial : 9
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 3
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_FIGS }
			amount { value : 12 }
			months_initial : 12
			location_fields [ 5, -1, 5, 6 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 10
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 11 }
			months_initial : 9
			location_fields [ 5, 5, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 1
			on_refusal_action : 3
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 12
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 0, month : 0 }
			item { value : 1 }
			amount { value : 8 }
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
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 10 }
			item { value : RESOURCE_BEER }
			amount { value : 7 }
			months_initial : 6
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 1
			on_refusal_action : 3
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 1
			subtype : 3
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 4 }
			item { value : RESOURCE_BRICKS }
			amount { value : 10 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 1
			on_refusal_action : 3
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 4
			city_id : 7
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 3 }
			item { value : RESOURCE_PAINT }
			amount { value : 7 }
			months_initial : 11
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 16
			on_refusal_action : 17
			on_too_late_action : 16
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_OIL }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 3, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
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
			time { year : 6, month : 4 }
			item { value : RESOURCE_GRAIN }
			amount { value : 10 }
			months_initial : 7
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 19
			on_refusal_action : 20
			on_too_late_action : 19
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_OIL }
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
			city_id : 6
		}
		{
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_GRAIN }
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
		{
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 18, month : 9 }
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
			type : EVENT_TYPE_REQUEST
			time { year : 11, month : 10 }
			item { value : RESOURCE_LINEN }
			amount { value : 5 }
			months_initial : 9
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 23
			on_refusal_action : 24
			on_too_late_action : 23
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_POTTERY }
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_POTTERY }
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 6 }
			item { value : RESOURCE_TROOPS }
			amount { value : 14 }
			months_initial : 10
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 1
			on_refusal_action : 3
			on_too_late_action : 0
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 12, month : 9 }
			item { value : RESOURCE_TROOPS }
			amount { value : 16 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 1
			on_refusal_action : 3
			on_too_late_action : 0
			on_defeat_action : 27
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 3, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 5
		}
	]
	map_background : {pack:PACK_EMPIRE, id:21}

	hide_pak_cities : true
	cities [
		{
			name : "Deir el-Medina"
			idx : 28
			pos : [779, 953]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_BARLEY ]
		}
		{
			name : "Pwenet"
			idx : 2
			pos : [1133, 1325]
			route : 7
			is_open : false
			cost_to_open : 585
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_POTTERY, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Enkomi"
			idx : 29
			pos : [678, 61]
			route : 3
			is_open : false
			cost_to_open : 1780
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_OIL ]
			buys [ RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_OIL, limit: 4000 }
			]
		}
		{
			name : "Kharga Oasis"
			idx : 31
			pos : [647, 1124]
			route : 5
			is_open : false
			cost_to_open : 250
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_HENNA ]
			buys [ RESOURCE_GRAIN, RESOURCE_BRICKS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_HENNA, limit: 2500 }
			]
		}
		{
			name : "Dakhla Oasis"
			idx : 32
			pos : [330, 1058]
			route : 6
			is_open : false
			cost_to_open : 525
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_HENNA ]
			buys [ RESOURCE_STRAW, RESOURCE_BRICKS, RESOURCE_POTTERY ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 1500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_HENNA, limit: 1500 }
			]
		}
		{
			name : "Sumur"
			idx : 34
			pos : [880, 43]
			route : 2
			is_open : false
			cost_to_open : 1700
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LINEN, RESOURCE_TIMBER, RESOURCE_OIL ]
			buys [ RESOURCE_LAMPS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_OIL, limit: 1500 }
				{ resource: RESOURCE_LAMPS, limit: 2500 }
			]
		}
		{
			name : "Piramesse"
			idx : 36
			pos : [567, 421]
			route : 1
			is_open : false
			cost_to_open : 940
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LETTUCE, RESOURCE_WEAPONS, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_CHARIOTS ]
			buys [ RESOURCE_BEER, RESOURCE_OIL, RESOURCE_PAINT ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 4000 }
				{ resource: RESOURCE_CHARIOTS, limit: 1500 }
				{ resource: RESOURCE_OIL, limit: 1500 }
				{ resource: RESOURCE_PAINT, limit: 2500 }
			]
		}
		{
			name : "Timna"
			idx : 40
			pos : [896, 466]
			route : 4
			is_open : false
			cost_to_open : 890
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_COPPER, RESOURCE_OIL ]
			buys [ RESOURCE_GRAIN, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
				{ resource: RESOURCE_OIL, limit: 1500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 0
			pos : [537, 501]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Sawu"
			idx : 3
			pos : [910, 829]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 4
			pos : [872, 133]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Waset"
			idx : 5
			pos : [824, 938]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Abu"
			idx : 30
			pos : [895, 1173]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Thinis"
			idx : 33
			pos : [675, 869]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Qadesh"
			idx : 35
			pos : [954, 9]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Migdol"
			idx : 37
			pos : [672, 384]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Abu Simbel"
			idx : 38
			pos : [769, 1317]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Heh"
			idx : 41
			pos : [701, 1405]
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
				[575, 472], [570, 490], [573, 503], [574, 516], [588, 522], [587, 541],
				[594, 588], [600, 609], [584, 629], [585, 645], [570, 669], [571, 709],
				[565, 722], [583, 739], [587, 761], [595, 778], [596, 794], [612, 812],
				[625, 815], [652, 832], [663, 846], [676, 853], [689, 870], [717, 887],
				[725, 902], [742, 915], [757, 913], [772, 934], [789, 926], [812, 907],
				[825, 923], [827, 945], [814, 963]
			]
		}
		{
			route : 2
			type : 2
			points [
				[883, 66], [868, 109], [851, 206], [835, 296], [776, 335], [725, 343],
				[642, 354], [626, 382], [603, 399], [591, 398], [589, 409], [584, 426],
				[568, 441], [553, 476], [560, 501], [570, 504], [584, 524], [589, 548],
				[591, 590], [598, 609], [586, 628], [587, 643], [569, 667], [569, 706],
				[566, 722], [583, 736], [584, 752], [595, 774], [596, 794], [610, 812],
				[642, 826], [651, 831], [660, 845], [675, 851], [700, 877], [719, 888],
				[724, 901], [744, 918], [758, 914], [775, 934], [797, 920], [814, 906],
				[825, 928], [826, 942], [812, 964]
			]
		}
		{
			route : 3
			type : 2
			points [
				[716, 71], [864, 141], [835, 298], [773, 334], [641, 350], [619, 387],
				[604, 399], [593, 398], [585, 426], [570, 435], [563, 458], [556, 478],
				[561, 500], [573, 505], [583, 524], [590, 555], [598, 609], [586, 630],
				[585, 645], [572, 667], [570, 704], [568, 725], [582, 739], [588, 764],
				[596, 776], [598, 795], [614, 816], [630, 822], [650, 829], [659, 845],
				[676, 856], [693, 873], [717, 888], [728, 905], [745, 918], [757, 914],
				[774, 934], [794, 922], [816, 907], [824, 924], [828, 945], [815, 963]
			]
		}
		{
			route : 4
			type : 1
			points [
				[898, 495], [866, 509], [793, 535], [727, 503], [700, 489], [678, 503],
				[680, 556], [718, 605], [697, 661], [668, 690], [632, 707], [626, 720],
				[592, 747], [627, 804], [701, 868], [710, 907], [768, 949], [783, 959]
			]
		}
		{
			route : 5
			type : 1
			points [
				[671, 1132], [666, 1088], [697, 1074], [775, 1054], [788, 1018], [802, 981]
			]
		}
		{
			route : 6
			type : 1
			points [
				[363, 1087], [402, 1100], [457, 1075], [545, 1088], [645, 1099], [682, 1073],
				[771, 1049], [793, 982]
			]
		}
		{
			route : 7
			type : 1
			points [
				[1137, 1331], [1140, 1268], [1104, 1215], [1085, 1197], [1067, 1120], [1027, 1100],
				[977, 1099], [930, 1083], [888, 1073], [864, 1021], [829, 991], [808, 993],
				[803, 983]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [505, 526], image : 13864, expanded_image : 9 }
		{ pos : [599, 512], image : 13859, expanded_image : 4 }
		{ pos : [532, 537], image : 13855 }
		{ pos : [579, 494], image : 13855 }
		{ pos : [873, 841], image : 13866, expanded_image : 11 }
		{ pos : [916, 39], image : 13863, expanded_image : 8 }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [417, 466] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [686, 1026] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]


	vars {
		start_message_shown : false
		pharaoh_favour_invasion_done : false
	}
}

[es=event_mission_start, mission=mission44]
function mission44_on_start(ev) {
	log_info("mission44: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_KUSHITE)
	scenario.start_year = -1250
	scenario.climate = 2
	__scenario_monuments.first = 36
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_ramses_valley")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

[es=event_advance_month, mission=mission44]
function mission44_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	log_info("akhenaten: mission 44 pharaoh favour invasion size=27 kr=" + city.rating_kingdom)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: 27,
		invasion_id: 8,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_TROOPS
	})
}
