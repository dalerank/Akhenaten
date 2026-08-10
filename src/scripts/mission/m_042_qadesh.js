log_info("akhenaten: mission 42 qadesh started")

mission42 {
	map_file : "data/maps/m_042_qadesh.map"

	// Map points from data/maps/m_042_qadesh.map.
	herd_points_predator [ [88, 92] ]

	start_message : "message_mission_qadesh"
	selection_title : "Qadesh"
	player_rank : 10
	// CO2: best infantry + chariot companies from Sumur (41) if campaign advance.
	carry_troops : ["infantry", "chariot"]

	next_mission : 43

	initial_funds [36000, 24000, 18000, 12000, 9540]
	rescue_loans [3000, 2000, 1500, 1000, 800]
	debt_interest [4, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C42_mission.mp3"
		victory : "Voice/Mission/C42_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
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
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GEMSTONE_MINE, BUILDING_COPPER_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	win_criteria {
		population    {enabled : true, goal : 1800 }
		culture       {enabled : false, goal : 15 }
		prosperity    {enabled : true, goal : 20 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 50 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 14 }
		time_limit    {enabled : true, years : 7 }
		milestone25_year : 2
		milestone50_year : 4
		milestone75_year : 6
	}

	entry_point [109, 100]
	exit_point [119, 90]

	hide_pak_burial : true
	burial_provisions [ ]

	map_background : {pack:PACK_EMPIRE, id:21}
	hide_pak_cities : true
	cities [
		{
			name : "Qadesh"
			idx : 4
			pos : [952, 2]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_POMEGRANATES, RESOURCE_GEMS ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
		}
		{
			name : "Sumur"
			idx : 29
			pos : [874, 39]
			route : 1
			is_open : false
			cost_to_open : 70
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_WEAPONS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_POMEGRANATES ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POMEGRANATES, limit: 4000 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}
		{
			name : "Jericho"
			idx : 24
			pos : [901, 253]
			route : 2
			is_open : false
			cost_to_open : 250
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY ]
			buys [ RESOURCE_POMEGRANATES, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Timna"
			idx : 26
			pos : [898, 469]
			route : 3
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_COPPER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Migdol"
			idx : 28
			pos : [666, 372]
			route : 4
			is_open : false
			cost_to_open : 490
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LETTUCE, RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_CHARIOTS ]
			buys [ RESOURCE_WEAPONS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_CHARIOTS, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 2
			pos : [575, 494]
			route : 5
			is_open : false
			cost_to_open : 630
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_BEER ]
			buys [ RESOURCE_WEAPONS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}
		{
			name : "Waset"
			idx : 6
			pos : [818, 925]
			route : 6
			is_open : false
			cost_to_open : 1080
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_PHARAOH
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
			name : "Dakhla Oasis"
			idx : 1
			pos : [328, 1065]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 5
			pos : [868, 158]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Enkomi"
			idx : 25
			pos : [692, 56]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 1
			points [
				[897, 44], [912, 35], [929, 39], [939, 34], [954, 39]
			]
		}
		{
			route : 2
			type : 1
			points [
				[936, 264], [942, 254], [929, 221], [925, 199], [936, 171],
				[936, 152], [936, 114], [952, 85], [959, 70], [969, 57]
			]
		}
		{
			route : 3
			type : 1
			points [
				[911, 468], [899, 398], [863, 359], [840, 324], [861, 308],
				[874, 255], [901, 189], [901, 130], [915, 87], [939, 67], [951, 52]
			]
		}
		{
			route : 4
			type : 1
			points [
				[701, 394], [743, 374], [803, 358], [842, 330], [860, 289],
				[882, 211], [908, 186], [931, 151], [938, 113], [973, 56]
			]
		}
		{
			route : 5
			type : 1
			points [
				[601, 514], [666, 438], [703, 400], [806, 363],
				[866, 311], [901, 198], [912, 121], [957, 56]
			]
		}
		{
			route : 6
			type : 1
			points [
				[837, 944], [824, 887], [799, 813], [767, 730], [768, 650],
				[723, 604], [683, 552], [684, 507], [705, 485], [762, 453],
				[793, 389], [872, 316], [914, 220], [935, 212], [947, 154],
				[953, 103], [976, 56]
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

	enable_scenario_events : true

	vars {
		chain_leaves_wired : false

		event0_luxury_done : false
		event5_luxury_done : false
		event10_troops_done : false
		event14_beer_done : false
		event17_gems_done : false
		event20_trade_done : false
		event21_pomegranates_done : false

		inv_wave1_done : false
		inv_wave1_seq : 0
		inv_wave1_abs : -1
		inv_wave2_done : false
		inv_wave2_seq : 0
		inv_wave2_abs : -1
		inv_wave3_done : false

		kr_seq : 0

		start_message_shown : false
	}
}

function mission42_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) {
		leaf.set_param("months_initial", months)
	}
	return leaf
}

function mission42_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag, city_name) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	if (sender_faction !== undefined) {
		request.set_sender_faction(sender_faction)
	}
	if (ok_tag) {
		request.set_completed_action_tag(ok_tag)
	}
	if (fail_tag) {
		request.set_refusal_action_tag(fail_tag)
	}
	if (late_tag) {
		request.set_too_late_action_tag(late_tag)
	}
	if (defeat_tag) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.execute()
	return request
}

function mission42_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	var event = city.create_chain_event(opts)
	event.execute()
	return event
}

function mission42_fire_kr(delta) {
	var type = delta >= 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE
	var amount = delta >= 0 ? delta : -delta
	mission.kr_seq = (mission.kr_seq | 0) + 1
	mission42_fire_simple_event(8000 + mission.kr_seq, type, undefined, amount)
}

function mission42_canaanite_raid(invasion_id, size, attack_target, on_completed_tag) {
	log_info("akhenaten: mission 42 canaanite raid size=" + size + " id=" + invasion_id)
	__image_request_pak(PACK_ENEMY_CANAANITE)
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_2_CANAANITE,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	return city.start_foreign_army_invasion(opts)
}

function mission42_invasion_outcome(seq) {
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

function mission42_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) {
		return
	}
	mission.chain_leaves_wired = true

	mission42_make_leaf(1002, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_CHICKPEAS, 7, 12)
	mission42_make_leaf(1004, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_FISH, 4, 12)

	mission42_make_leaf(1006, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 12,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Waset")
	mission42_make_leaf(1007, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_POTTERY, 5, 12)

	var msg_won = mission42_make_leaf(1011, EVENT_TYPE_MESSAGE, undefined, 8, 12,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Jericho")
	msg_won.set_completed_action_tag(1016)
	mission42_make_leaf(1016, EVENT_TYPE_REPUTATION_INCREASE, undefined, 3, 12)

	var msg_lost = mission42_make_leaf(1012, EVENT_TYPE_MESSAGE, undefined, 8, 12,
		EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, "Enkomi")
	msg_lost.set_completed_action_tag(1013)
	var lost = mission42_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Enkomi")
	lost.set_completed_action_tag(1030)
	mission42_make_leaf(1030, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 12)

	mission42_make_leaf(1015, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LETTUCE, 10, 12)

	mission42_make_leaf(1018, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LUXURY_GOODS, 8, 12, undefined, "Waset")

	mission42_make_leaf(1019, EVENT_TYPE_INVASION, undefined, 12, 0)
	mission42_make_leaf(1022, EVENT_TYPE_INVASION, undefined, 0, 0)
}

[es=event_mission_start, mission=mission42]
function mission42_on_start(ev) {
	log_info("mission42: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_CANAANITE)
	scenario.start_year = -1277
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_qadesh")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_2_CANAANITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission42_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission42]
function mission42_invasion_followup(ev) {
	var abs = ev.years_since_start * 12 + ev.month

	if (mission.inv_wave1_done && !mission.inv_wave2_done) {
		if (mission.inv_wave1_abs < 0) {
			mission.inv_wave1_abs = abs
		}
		var ready2 = false
		if (mission.inv_wave1_seq > 0) {
			var o1 = mission42_invasion_outcome(mission.inv_wave1_seq)
			if (o1 == 1) {
				ready2 = true
			} else if (o1 == 2 || o1 == 3) {
				mission.inv_wave2_done = true
				mission.inv_wave3_done = true
				log_info("akhenaten: mission 42 skip invasion chain after wave1 non-ok", {
					seq: mission.inv_wave1_seq, outcome: o1
				})
				return
			}
		} else if (abs - mission.inv_wave1_abs >= 3) {
			ready2 = true
		}
		if (ready2) {
			mission.inv_wave2_done = true
			mission.inv_wave2_abs = abs
			mission.inv_wave2_seq = mission42_canaanite_raid(19, 30, EVENT_ATTACK_TARGET_TROOPS, 1022)
			log_info("akhenaten: mission 42 canaanite×30 after wave1", {
				seq: mission.inv_wave2_seq, abs: abs
			})
		}
		return
	}

	if (mission.inv_wave2_done && !mission.inv_wave3_done) {
		if (mission.inv_wave2_abs < 0) {
			mission.inv_wave2_abs = abs
		}
		var ready3 = false
		if (mission.inv_wave2_seq > 0) {
			var o2 = mission42_invasion_outcome(mission.inv_wave2_seq)
			if (o2 == 1) {
				ready3 = true
			} else if (o2 == 2 || o2 == 3) {
				mission.inv_wave3_done = true
				log_info("akhenaten: mission 42 skip canaanite×35 after wave2 non-ok", {
					seq: mission.inv_wave2_seq, outcome: o2
				})
				return
			}
		} else if (abs - mission.inv_wave2_abs >= 3) {
			ready3 = true
		}
		if (ready3) {
			mission.inv_wave3_done = true
			mission42_canaanite_raid(22, 35, EVENT_ATTACK_TARGET_RANDOM)
			log_info("akhenaten: mission 42 canaanite×35 after wave2", {abs: abs})
		}
	}
}

[es=event_advance_month, mission=mission42]
function mission42_event_i0_luxury(ev) {
	if (mission.event0_luxury_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 6)) {
		return
	}
	mission.event0_luxury_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 luxury×5", {ev:ev})
	mission42_fire_request(2000, RESOURCE_LUXURY_GOODS, 5, 8, 1002, 0, 1004, 0, 0, undefined, "Waset")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i1_invasion(ev) {
	if (mission.inv_wave1_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 4)) {
		return
	}
	mission.inv_wave1_done = true
	mission.inv_wave1_abs = -1
	mission42_ensure_chain_leaves()
	mission.inv_wave1_seq = mission42_canaanite_raid(1, 50, EVENT_ATTACK_TARGET_TROOPS, 1019)
	log_info("akhenaten: mission 42 canaanite×50", {ev:ev, seq: mission.inv_wave1_seq})
}

[es=event_advance_month, mission=mission42]
function mission42_event_i5_luxury(ev) {
	if (mission.event5_luxury_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 8)) {
		return
	}
	mission.event5_luxury_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 luxury×7", {ev:ev})
	mission42_fire_request(2005, RESOURCE_LUXURY_GOODS, 7, 10, 1006, 0, 1007, 0, 0, undefined, "Waset")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i10_troops(ev) {
	if (mission.event10_troops_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 5)) {
		return
	}
	mission.event10_troops_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 troops×27", {ev:ev})
	mission42_fire_request(2010, RESOURCE_TROOPS, 27, 4, 1011, 1012, 1011, 2, 0, 1012, "Jericho")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i14_beer(ev) {
	if (mission.event14_beer_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 6)) {
		return
	}
	mission.event14_beer_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 beer×6", {ev:ev})
	mission42_fire_request(2014, RESOURCE_BEER, 6, 7, 1015, 0, 1015, 3, 0, undefined, "Qadesh")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i17_gems(ev) {
	if (mission.event17_gems_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 10)) {
		return
	}
	mission.event17_gems_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 gems×11", {ev:ev})
	mission42_fire_request(2017, RESOURCE_GEMS, 11, 8, 1018, 0, 0, 0, 0, undefined, "Enkomi")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i20_trade(ev) {
	if (mission.event20_trade_done) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 3)) {
		return
	}
	mission.event20_trade_done = true
	log_info("akhenaten: mission 42 land trade problem", {ev:ev})
	mission42_fire_simple_event(2020, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 8, "Enkomi")
}

[es=event_advance_month, mission=mission42]
function mission42_event_i21_pomegranates(ev) {
	if (mission.event21_pomegranates_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 2)) {
		return
	}
	mission.event21_pomegranates_done = true
	mission42_ensure_chain_leaves()
	log_info("akhenaten: mission 42 pomegranates×8", {ev:ev})
	mission42_fire_request(2021, RESOURCE_POMEGRANATES, 8, 6, 0, 0, 0, 5, 0, undefined, "Waset")
}

[es=event_request_cleared, mission=mission42]
function mission42_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	var tag = ev.tag_id

	if (tag == 2000 || tag == 2005 || tag == 2014 || tag == 2017) {
		if (outcome == "refuse") {
			mission42_fire_kr(-3)
		}
		return
	}

	if (tag == 2021) {
		if (outcome == "ok") {
			mission42_fire_kr(3)
		} else if (outcome == "refuse") {
			mission42_fire_kr(-3)
		}
	}
}
