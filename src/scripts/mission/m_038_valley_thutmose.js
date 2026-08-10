log_info("akhenaten: mission 38 valley thutmose started")

mission38 { // Thutmose in the Valley — The First Tomb
	map_file : "data/maps/m_038_valley_thutmose.map"

	// Map points from data/maps/m_038_valley_thutmose.map.
	herd_points_predator [ [215, 111], [60, 83], [86, 66] ]

	start_message : "message_mission_thutmose_valley"
	selection_title : "Thutmose in the Valley"
	player_rank : 5

	next_mission : 39

	// pak Normal funds=8000 loan=2500 debt_interest=9 → int_dcy around Normal.
	initial_funds [16000, 10670, 8000, 5360, 4240]
	rescue_loans [5000, 3330, 2500, 1670, 1325]
	debt_interest [5, 7, 9, 11, 13]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		flotsam_enabled : false
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C38_mission.mp3"
		victory : "Voice/Mission/C38_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD,
		BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_CHARIOTS_WORKSHOP, BUILDING_WEAPONSMITH,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_TRANSPORT_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		// Lamp / paint / artisans / tomb unlock via mission38 tutorial stages (CL-VK / RT5).
	]

	win_criteria {
		population    {enabled : false, goal : 2000 }
		culture       {enabled : true, goal : 35 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : true, goal : 65 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 14 }
		milestone25_year : 4
		milestone50_year : 8
		milestone75_year : 12
	}

	entry_point [179, 67]
	exit_point [209, 128]
	river_entry_point [110, 3]
	river_exit_point [189, 147]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_BEER, required: 3 }
		{ resource: RESOURCE_LINEN, required: 4 }
		{ resource: RESOURCE_GEMS, required: 4 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 6 }
		{ resource: RESOURCE_CHARIOTS, required: 1 }
	]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 9, month : 7 }
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
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 8 }
			item { value : RESOURCE_BEER }
			amount { value : 16 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 2
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 0 }
			item { value : RESOURCE_HENNA }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
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
			city_id : 6
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
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 1 }
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
			type : EVENT_TYPE_FAILED_FLOOD
			time { year : 4, month : 6 }
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
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 3 }
			item { value : RESOURCE_LINEN }
			amount { value : 5 }
			months_initial : 8
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 8
			on_refusal_action : 4
			on_too_late_action : 9
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 8, 8, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_OIL }
			amount { value : 5 }
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
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 4 }
			item { value : RESOURCE_PAINT }
			amount { value : 7 }
			months_initial : 10
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 11
			on_refusal_action : 12
			on_too_late_action : 11
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_STRAW }
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
			type : EVENT_TYPE_PRICE_INCREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_STRAW }
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
		{
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 0 }
			item { value : RESOURCE_HENNA }
			amount { value : 12 }
			months_initial : 10
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 14
			on_refusal_action : 4
			on_too_late_action : 14
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 3 }
			item { value : RESOURCE_OIL }
			amount { value : 5 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 3 }
			amount { value : 13 }
			months_initial : 12
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 1 }
			item { value : RESOURCE_BRICKS }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 4
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 10, month : 4 }
			item { value : RESOURCE_CLAY }
			amount { value : 8 }
			months_initial : 9
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 13, month : 3 }
			item { value : RESOURCE_GRAIN }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 3
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
	]

	map_background : {pack:PACK_EMPIRE, id:23}

	hide_pak_cities : true
	cities [
			{
				name : "Itjtawy"
				idx : 0
				pos : [592, 548]
				route : 3
				is_open : false
				cost_to_open : 825
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_STRAW,
					RESOURCE_PAPYRUS
				]
				buys [
					RESOURCE_BEER,
					RESOURCE_FLAX,
					RESOURCE_LAMPS
				]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_FLAX, limit: 1500 }
					{ resource: RESOURCE_LAMPS, limit: 1500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
					{ resource: RESOURCE_STRAW, limit: 2500 }
				]
			}
			{
				name : "Kerma"
				idx : 1
				pos : [734, 1492]
				route : 5
				is_open : false
				cost_to_open : 940
				is_sea_trade : true
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS ]
				buys [
					RESOURCE_LINEN,
					RESOURCE_PAINT
				]
				route_limits [
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_PAINT, limit: 1500 }
				]
			}
			{
				name : "Men-nefer"
				idx : 2
				pos : [521, 466]
				route : 2
				is_open : false
				cost_to_open : 940
				is_sea_trade : true
				type : EMPIRE_CITY_PHARAOH_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_GRAIN,
					RESOURCE_MEAT,
					RESOURCE_BEER,
					RESOURCE_PAPYRUS,
					RESOURCE_CHARIOTS
				]
				buys [
					RESOURCE_CHICKPEAS,
					RESOURCE_BARLEY
				]
				route_limits [
					{ resource: RESOURCE_BARLEY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 4000 }
					{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
					{ resource: RESOURCE_GRAIN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
					{ resource: RESOURCE_MEAT, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
					{ resource: RESOURCE_CHARIOTS, limit: 1500 }
				]
			}
			{
				name : "Menat Khufu"
				idx : 3
				pos : [578, 720]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
			{
				name : "Pwenet"
				idx : 5
				pos : [1133, 1325]
				route : 6
				is_open : false
				cost_to_open : 525
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_GEMS,
					RESOURCE_LUXURY_GOODS
				]
				buys [
					RESOURCE_CHICKPEAS,
					RESOURCE_POTTERY
				]
				route_limits [
					{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
					{ resource: RESOURCE_GEMS, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 1500 }
				]
			}
			{
				name : "Sawu"
				idx : 6
				pos : [910, 829]
				route : 8
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Tyre"
				idx : 7
				pos : [872, 123]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Waset"
				idx : 8
				pos : [830, 932]
				route : 1
				is_open : false
				cost_to_open : 80
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_MEAT,
					RESOURCE_BARLEY
				]
				buys [ RESOURCE_BRICKS ]
				route_limits [
					{ resource: RESOURCE_BARLEY, limit: 2500 }
					{ resource: RESOURCE_BRICKS, limit: 4000 }
					{ resource: RESOURCE_MEAT, limit: 2500 }
				]
			}
			{
				name : "Deir el-Medina"
				idx : 34
				pos : [774, 968]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [
					RESOURCE_CHICKPEAS,
					RESOURCE_CLAY,
					RESOURCE_FLAX,
					RESOURCE_HENNA
				]
			}
			{
				name : "Enkomi"
				idx : 35
				pos : [678, 61]
				route : 7
				is_open : false
				cost_to_open : 1700
				is_sea_trade : true
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_OIL ]
				buys [
					RESOURCE_LINEN,
					RESOURCE_LUXURY_GOODS
				]
				route_limits [
					{ resource: RESOURCE_LINEN, limit: 1500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_OIL, limit: 4000 }
				]
			}
			{
				name : "Byblos"
				idx : 36
				pos : [892, 42]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Abu"
				idx : 37
				pos : [895, 1186]
				route : 4
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [828, 948], [817, 957], [820, 966], [815, 979], [814, 983], [806, 986] ]
		}
		{
			route : 2
			type : 2
			deviation : 8
			points [ [774, 968], [521, 466] ]
		}
		{
			route : 3
			type : 2
			deviation : 8
			points [ [774, 968], [592, 548] ]
		}
		{
			route : 4
			type : 2
			points [ [898, 1198], [893, 1190], [893, 1178], [882, 1157], [888, 1135], [880, 1117], [884, 1102], [879, 1090], [845, 1019], [833, 1011], [826, 998], [810, 986] ]
		}
		{
			route : 5
			type : 2
			deviation : 8
			points [ [774, 968], [734, 1492] ]
		}
		{
			route : 6
			type : 1
			points [ [1135, 1330], [1108, 1317], [1047, 1252], [948, 1192], [939, 1132], [913, 1102], [904, 1064] ]
		}
		{
			route : 7
			type : 2
			deviation : 8
			points [ [774, 968], [678, 61] ]
		}
		{
			route : 8
			type : 1
			points [ [914, 860], [907, 875], [890, 888], [858, 913], [839, 930], [833, 964], [821, 978], [812, 983] ]
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
			pos : [615, 707]
			image : 13863
			expanded_image : 8
		}
		{
			pos : [635, 711]
			image : 13863
			expanded_image : 8
		}
		{
			pos : [599, 512]
			image : 13859
			expanded_image : 4
		}
		{
			pos : [616, 733]
			image : 13856
			expanded_image : 1
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
		tutorial_lamps_unlocked : false
		tutorial_tomb_unlocked : false
	}
}

[es=event_mission_start, mission=mission38]
function mission38_on_start(ev) {
	scenario.start_year = -1490
	scenario.climate = 2 // CLIMATE_DESERT
	__scenario_monuments.first = 33
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_thutmose_valley")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
}

// CL-VK / RT5: gradual unlock — lamps+guilds first, then Small royal tomb.
// Thresholds provisional until pak dump of OG tutorial beats.
[event=event_population_changed, mission=mission38]
function mission38_tutorial_unlocks(ev) {
	var pop = ev.value | 0
	if (!mission.tutorial_lamps_unlocked && pop >= 400) {
		city.use_building(BUILDING_LAMP_WORKSHOP, true)
		city.use_building(BUILDING_PAINT_WORKSHOP, true)
		city.use_building(BUILDING_ARTISANS_GUILD, true)
		mission.tutorial_lamps_unlocked = true
	}
	if (!mission.tutorial_tomb_unlocked && pop >= 800) {
		city.use_building(BUILDING_SMALL_ROYAL_TOMB, true)
		mission.tutorial_tomb_unlocked = true
	}
}
