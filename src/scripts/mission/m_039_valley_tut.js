log_info("akhenaten: mission 39 valley tut started")

mission39 { // Tut in the Valley — Death of Tutankhamun
	map_file : "data/maps/m_039_valley_tut.map"

	// Map points from data/maps/m_039_valley_tut.map.
	herd_points_predator [ [71, 58], [59, 83], [104, 85] ]

	start_message : "message_mission_tutankhamun_valley"
	selection_title : "Tut in the Valley"
	player_rank : 6

	next_mission : 40
	carry_monuments : true

	// pak Normal funds=8500 loan=3000 debt_interest=12 → int_dcy around Normal.
	initial_funds [17000, 11330, 8500, 5670, 4505]
	rescue_loans [6000, 4000, 3000, 2000, 1590]
	debt_interest [8, 10, 12, 14, 16]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		flotsam_enabled : false
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C39_mission.mp3"
		victory : "Voice/Mission/C39_victory.mp3"
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
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_TRANSPORT_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_SMALL_ROYAL_TOMB, // carried preexisting from m38 (menu; not a second build goal)
		BUILDING_MEDIUM_ROYAL_TOMB,
	]

	win_criteria {
		population    {enabled : true, goal : 1500 }
		culture       {enabled : false, goal : 35 }
		prosperity    {enabled : false, goal : 40 }
		monuments     {enabled : true, goal : 22 }
		kingdom       {enabled : true, goal : 45 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 14 }
		time_limit    {enabled : true, years : 8 }
		milestone25_year : 2
		milestone50_year : 4
		milestone75_year : 6
	}

	entry_point [142, 194]
	exit_point [149, 187]
	river_entry_point [109, 4]
	river_exit_point [189, 147]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 3 }
		{ resource: RESOURCE_POTTERY, required: 6 }
		{ resource: RESOURCE_LINEN, required: 2 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 6 }
		{ resource: RESOURCE_CHARIOTS, required: 1 }
	]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_PERFECT_FLOOD
			time { year : 0, month : 10 }
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
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 1 }
			item { value : RESOURCE_LETTUCE }
			amount { value : 4 }
			months_initial : 7
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 2
			on_refusal_action : 3
			on_too_late_action : 2
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
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
			city_id : 4
		}
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
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
			city_id : 8
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 2, month : 1 }
			item { value : RESOURCE_POTTERY }
			amount { value : 4 }
			months_initial : 8
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 5
			on_refusal_action : 6
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_OIL }
			amount { value : 4 }
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
		{
			type : EVENT_TYPE_PRICE_INCREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
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
			city_id : 7
		}
		{
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 5, month : 4 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
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
			type : EVENT_TYPE_WAGE_DECREASE
			time { year : 3, month : 2 }
			item { value : 1 }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 54
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_CLAY_PIT_FLOOD
			time { year : 10, month : 0 }
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
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 4, month : 0 }
			item { value : RESOURCE_HENNA }
			amount { value : 5 }
			months_initial : 8
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 11
			on_refusal_action : 3
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{
			type : EVENT_TYPE_DEMAND_INCREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_POTTERY }
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
			city_id : 7
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
				cost_to_open : 370
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_GRAIN,
					RESOURCE_WEAPONS,
					RESOURCE_BEER,
					RESOURCE_TIMBER,
					RESOURCE_CHARIOTS
				]
				buys [
					RESOURCE_CHICKPEAS,
					RESOURCE_POTTERY
				]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
					{ resource: RESOURCE_GRAIN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 1500 }
					{ resource: RESOURCE_WEAPONS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 1500 }
					{ resource: RESOURCE_CHARIOTS, limit: 1500 }
				]
			}
			{
				name : "Kerma"
				idx : 1
				pos : [734, 1492]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Men-nefer"
				idx : 2
				pos : [521, 466]
				route : 0
				trade : false
				type : EMPIRE_CITY_PHARAOH
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
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
			{
				name : "Sawu"
				idx : 6
				pos : [910, 829]
				route : 4
				is_open : false
				cost_to_open : 245
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [
					RESOURCE_LUXURY_GOODS,
					RESOURCE_OIL
				]
				buys [
					RESOURCE_GRAIN,
					RESOURCE_BEER,
					RESOURCE_LAMPS
				]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_GRAIN, limit: 4000 }
					{ resource: RESOURCE_LAMPS, limit: 1500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_OIL, limit: 1500 }
				]
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
					RESOURCE_BARLEY,
					RESOURCE_LINEN
				]
				buys [
					RESOURCE_POTTERY,
					RESOURCE_HENNA
				]
				route_limits [
					{ resource: RESOURCE_BARLEY, limit: 2500 }
					{ resource: RESOURCE_HENNA, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
				]
			}
			{
				name : "Deir el-Medina"
				idx : 34
				pos : [779, 953]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [
					RESOURCE_LETTUCE,
					RESOURCE_CHICKPEAS,
					RESOURCE_CLAY,
					RESOURCE_HENNA
				]
			}
			{
				name : "Enkomi"
				idx : 35
				pos : [678, 61]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
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
				route : 3
				is_open : false
				cost_to_open : 335
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS ]
				buys [
					RESOURCE_BEER,
					RESOURCE_TIMBER,
					RESOURCE_PAINT
				]
				route_limits [
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_PAINT, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 4000 }
				]
			}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [834, 944], [826, 950], [818, 958], [819, 966], [818, 971], [814, 976] ]
		}
		{
			route : 2
			type : 2
			deviation : 8
			points [ [779, 953], [591, 542] ]
		}
		{
			route : 3
			type : 2
			deviation : 8
			points [ [779, 953], [895, 1186] ]
		}
		{
			route : 4
			type : 1
			points [ [914, 858], [929, 879], [930, 903], [930, 944], [919, 956], [904, 964], [871, 961], [848, 972] ]
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
	}
}

[es=event_mission_start, mission=mission39]
function mission39_on_start(ev) {
	scenario.start_year = -1325
	scenario.climate = 2 // CLIMATE_DESERT
	__scenario_monuments.first = 34
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_tutankhamun_valley")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
}
