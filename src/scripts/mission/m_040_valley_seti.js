log_info("akhenaten: mission 40 valley seti started")

// Cleopatra campaign scenario 40. Empire id=21.

// Enemy ENEMY_6_KUSHITE. Gods: Osiris(1), Ra(2), Ptah(1). Start year -1290.
// MM subtitle: Tomb for a Pharaoh. Rank 6 (pak). Funds Normal 13720 / loan 3000 / debt 8.
// Win: pop 3000 / culture 40 / prosperity 70 / monuments 33 (Large W=13 → trunc(33);
//   pak goal often listed 32 — we use 33 so finished Large clears the gate) /
//   kingdom 80 / housing_count 12 + housing_level 15.
// Climate desert; map_background empire pack id 23. Our city: Deir el-Medina.
// Burial: weapons×6 beer×12 luxury×10 papyrus×8 chariots×4. Fish points present.
// Empire/events in JS (hide_pak_* + events[]). Robbers: crime_wave + TR engine.
// next_mission -1 (campaign end — must not spill to Sumur 41; clears monument carry).

mission40 { // Seti in the Valley — Tomb for a Pharaoh
	map_file : "data/maps/m_040_valley_seti.map"

	// Map points from data/maps/m_040_valley_seti.map.
	herd_points_predator [ [216, 111], [87, 67], [60, 83], [88, 164] ]

	start_message : "message_mission_seti_valley"
	selection_title : "Seti in the Valley"
	player_rank : 6

	next_mission : -1
	carry_monuments : true

	// pak Normal funds=13720 loan=3000 debt_interest=8 → int_dcy around Normal.
	initial_funds [27440, 18290, 13720, 9150, 7270]
	rescue_loans [6000, 4000, 3000, 2000, 1590]
	debt_interest [4, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		flotsam_enabled : false
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C40_mission.mp3"
		victory : "Voice/Mission/C40_victory.mp3"
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
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_SMALL_ROYAL_TOMB, BUILDING_MEDIUM_ROYAL_TOMB, // carried from m38/m39
		BUILDING_LARGE_ROYAL_TOMB,
	]

	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 40 }
		prosperity    {enabled : true, goal : 70 }
		monuments     {enabled : true, goal : 33 }
		kingdom       {enabled : true, goal : 80 }
		housing_count {enabled : true, goal : 12 }
		housing_level {enabled : true, goal : 15 }
		milestone25_year : 4
		milestone50_year : 8
		milestone75_year : 12
	}

	entry_point [142, 194]
	exit_point [156, 180]
	river_entry_point [110, 3]
	river_exit_point [190, 147]

	// config-only (omit → empty); restore pak fish points.
	fishing_points [
		[145, 52], [123, 26], [182, 138], [118, 15], [137, 46]
	]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 6 }
		{ resource: RESOURCE_BEER, required: 12 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 10 }
		{ resource: RESOURCE_PAPYRUS, required: 8 }
		{ resource: RESOURCE_CHARIOTS, required: 4 }
	]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 6, month : 3 }
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
			city_id : 6
		}
		{
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 8, month : 2 }
			item { value : 1 }
			amount { value : 5 }
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
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 10, month : 11 }
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 13, month : 8 }
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
			type : EVENT_TYPE_CRIME_WAVE
			time { year : 19, month : 1 }
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
		{
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 1 }
			item { value : RESOURCE_LINEN }
			amount { value : 5 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 7
			on_refusal_action : 8
			on_too_late_action : 6
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
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
			city_id : 4
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
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 1 }
			item { value : RESOURCE_LINEN }
			amount { value : 9 }
			months_initial : 10
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 7
			on_refusal_action : 9
			on_too_late_action : 6
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_LOCUSTS
			time { year : 11, month : 2 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 12
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 5, month : 0 }
			item { value : RESOURCE_GRAIN }
			amount { value : 16 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 13
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 0 }
			item { value : RESOURCE_LINEN }
			amount { value : 8 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 6
			on_refusal_action : 9
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 3 }
			item { value : RESOURCE_BRICKS }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 9, 9, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 15
			on_refusal_action : -1
			on_too_late_action : 15
			on_defeat_action : -1
			sender_faction : 0
			subtype : 4
			city_id : 5
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 3, month : 0 }
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 6 }
			item { value : RESOURCE_BEER }
			amount { value : 11 }
			months_initial : 5
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 17
			on_refusal_action : 9
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 1
			subtype : 3
			city_id : 8
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 18
			on_refusal_action : 18
			on_too_late_action : 18
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 0, month : 0 }
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 7, month : 11 }
			item { value : RESOURCE_LINEN }
			amount { value : 6 }
			months_initial : 7
			location_fields [ 11, 11, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 20
			on_refusal_action : 8
			on_too_late_action : 20
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 11, 11, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 9, month : 5 }
			item { value : RESOURCE_POMEGRANATES }
			amount { value : 10 }
			months_initial : 5
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 23
			on_refusal_action : 8
			on_too_late_action : 22
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 6
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 0, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 55
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 22
			on_refusal_action : 22
			on_too_late_action : 22
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_LAND_TRADE_PROBLEM
			time { year : 13, month : 9 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
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
			time { year : 9, month : 4 }
			item { value : RESOURCE_FISH }
			amount { value : 12 }
			months_initial : 8
			location_fields [ 7, 7, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 26
			on_refusal_action : -1
			on_too_late_action : 27
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_BEER }
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
			city_id : 7
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 7, 7, -1, -1 ]
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
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 3 }
			amount { value : 13 }
			months_initial : 12
			location_fields [ 2, -1, 1, 3 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 2
		}
	]

	map_background : {pack:PACK_EMPIRE, id:23}

	hide_pak_cities : true
	cities [
			{
				name : "Itjtawy"
				idx : 0
				pos : [591, 542]
				route : 2
				is_open : false
				cost_to_open : 810
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_GRAIN,
					RESOURCE_STRAW
				]
				buys [
					RESOURCE_POMEGRANATES,
					RESOURCE_LUXURY_GOODS
				]
				route_limits [
					{ resource: RESOURCE_GRAIN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
					{ resource: RESOURCE_STRAW, limit: 4000 }
				]
			}
			{
				name : "Men-nefer"
				idx : 1
				pos : [521, 466]
				route : 1
				is_open : false
				cost_to_open : 900
				is_sea_trade : true
				type : EMPIRE_CITY_PHARAOH_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_GRAIN,
					RESOURCE_WEAPONS,
					RESOURCE_PAPYRUS,
					RESOURCE_CHARIOTS
				]
				buys [
					RESOURCE_LINEN,
					RESOURCE_OIL
				]
				route_limits [
					{ resource: RESOURCE_CHARIOTS, limit: 1500 }
					{ resource: RESOURCE_GRAIN, limit: 4000 }
					{ resource: RESOURCE_LINEN, limit: 1500 }
					{ resource: RESOURCE_OIL, limit: 1500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
					{ resource: RESOURCE_WEAPONS, limit: 1500 }
				]
			}
			{
				name : "Pwenet"
				idx : 3
				pos : [1133, 1325]
				route : 10
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Sawu"
				idx : 4
				pos : [910, 829]
				route : 7
				is_open : false
				cost_to_open : 200
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_LUXURY_GOODS,
					RESOURCE_OIL
				]
				buys [
					RESOURCE_BEER,
					RESOURCE_LINEN
				]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 1500 }
					{ resource: RESOURCE_LINEN, limit: 1500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_OIL, limit: 1500 }
				]
			}
			{
				name : "Tyre"
				idx : 5
				pos : [872, 123]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Waset"
				idx : 6
				pos : [830, 932]
				route : 4
				is_open : false
				cost_to_open : 60
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CLAY ]
				buys [
					RESOURCE_CHARIOTS,
					RESOURCE_PAINT
				]
				route_limits [
					{ resource: RESOURCE_CHARIOTS, limit: 1500 }
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_PAINT, limit: 1500 }
				]
			}
			{
				name : "Deir el-Medina"
				idx : 29
				pos : [779, 953]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [
					RESOURCE_POMEGRANATES,
					RESOURCE_FISH,
					RESOURCE_BARLEY,
					RESOURCE_FLAX
				]
			}
			{
				name : "Enkomi"
				idx : 30
				pos : [678, 61]
				route : 11
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
			{
				name : "Abu"
				idx : 31
				pos : [895, 1173]
				route : 5
				is_open : false
				cost_to_open : 340
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS ]
				buys [
					RESOURCE_WEAPONS,
					RESOURCE_BRICKS
				]
				route_limits [
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
					{ resource: RESOURCE_WEAPONS, limit: 2500 }
				]
			}
			{
				name : "Kharga Oasis"
				idx : 32
				pos : [619, 1112]
				route : 8
				is_open : false
				cost_to_open : 225
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_FIGS,
					RESOURCE_HENNA
				]
				buys [
					RESOURCE_FISH,
					RESOURCE_BRICKS
				]
				route_limits [
					{ resource: RESOURCE_BRICKS, limit: 4000 }
					{ resource: RESOURCE_FIGS, limit: 2500 }
					{ resource: RESOURCE_FISH, limit: 1500 }
					{ resource: RESOURCE_HENNA, limit: 2500 }
				]
			}
			{
				name : "Dakhla Oasis"
				idx : 33
				pos : [330, 1058]
				route : 9
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Thinis"
				idx : 34
				pos : [675, 869]
				route : 3
				is_open : false
				cost_to_open : 125
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_CLAY,
					RESOURCE_POTTERY,
					RESOURCE_LAMPS
				]
				buys [ RESOURCE_BEER ]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_LAMPS, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
				]
			}
			{
				name : "Buhen"
				idx : 35
				pos : [765, 1336]
				route : 6
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			deviation : 8
			points [ [779, 953], [521, 466] ]
		}
		{
			route : 2
			type : 2
			deviation : 8
			points [ [779, 953], [591, 542] ]
		}
		{
			route : 3
			type : 1
			points [ [699, 899], [721, 918], [755, 931], [783, 944], [790, 956] ]
		}
		{
			route : 4
			type : 2
			points [ [832, 940], [822, 950], [818, 962], [815, 975] ]
		}
		{
			route : 5
			type : 2
			deviation : 8
			points [ [779, 953], [895, 1173] ]
		}
		{
			route : 6
			type : 1
			points [ [787, 1340], [806, 1316], [815, 1298], [807, 1287], [789, 1256], [767, 1212], [730, 1185], [688, 1168], [769, 1004], [795, 983] ]
		}
		{
			route : 7
			type : 1
			points [ [912, 858], [910, 871], [891, 879], [872, 911], [869, 938], [855, 972], [832, 972], [822, 974] ]
		}
		{
			route : 8
			type : 1
			points [ [656, 1120], [670, 1103], [673, 1093], [702, 1073], [723, 1061], [745, 1036], [782, 1005], [797, 982] ]
		}
		{
			route : 9
			type : 1
			points [ [367, 1088], [394, 1098], [462, 1099], [534, 1102], [615, 1089], [647, 1097], [700, 1078], [739, 1038] ]
		}
		{
			route : 10
			type : 1
			points [ [1134, 1335], [1107, 1334], [1067, 1318], [1035, 1300], [997, 1296], [941, 1265], [916, 1235], [690, 1158], [674, 1107], [682, 1094], [730, 1058], [775, 1015], [798, 982] ]
		}
		{
			route : 11
			type : 2
			points [ [717, 75], [747, 90], [861, 144], [857, 201], [837, 290], [789, 328], [730, 342], [639, 358], [571, 437], [557, 478], [571, 514], [586, 528], [592, 572], [597, 605], [584, 632], [576, 656], [607, 806], [648, 826], [656, 842], [677, 857], [700, 884], [719, 888], [727, 903], [744, 916], [813, 906], [824, 916], [827, 943], [814, 967] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{
			pos : [498, 512]
			image : 13864
			expanded_image : 9
		}
		{
			pos : [599, 512]
			image : 13859
			expanded_image : 4
		}
		{
			pos : [524, 530]
			image : 13855
		}
		{
			pos : [579, 494]
			image : 13855
		}
		{
			pos : [873, 841]
			image : 13866
			expanded_image : 11
		}
	]
	empire_texts [
		{
			name : "#mediterranean_sea"
			pos : [83, 159]
		}
		{
			name : "#cyprus"
			pos : [594, 107]
		}
		{
			name : "#red_sea"
			pos : [1051, 1561]
		}
		{
			name : "#eastern_desert"
			pos : [702, 773]
		}
		{
			name : "#greece"
			pos : [1, 67]
		}
		{
			name : "#libya"
			pos : [17, 425]
		}
		{
			name : "#lower_egypt"
			pos : [417, 466]
		}
		{
			name : "#delta"
			pos : [518, 362]
		}
		{
			name : "#fayuum"
			pos : [428, 580]
		}
		{
			name : "#nubia"
			pos : [806, 1445]
		}
		{
			name : "#palestine"
			pos : [833, 182]
		}
		{
			name : "#sinai"
			pos : [787, 478]
		}
		{
			name : "#syria"
			pos : [1003, 46]
		}
		{
			name : "#upper_egypt"
			pos : [686, 1026]
		}
		{
			name : "#western_desert"
			pos : [230, 774]
		}
		{
			name : "#lebanon"
			pos : [877, 109]
		}
		{
			name : "#canaan"
			pos : [850, 271]
		}
	]



	vars {
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission40]
function mission40_on_start(ev) {
	scenario.start_year = -1290
	scenario.climate = 2 // CLIMATE_DESERT
	__scenario_monuments.first = 35
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_seti_valley")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
}
