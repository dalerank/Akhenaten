log_info("akhenaten: mission 41 sumur started")

// Cleop mission1.pak scenario 41 (dump 2026-07-28). Empire id=23.
// Scenario enemy ENEMY_2_CANAANITE (briefing = Hittites — pak id wins).
// Gods: Ra(2), Ptah(1). MM subtitle: Lands of the Levant. Start year -1300.
// Funds Normal 5565 / loan 1500 / debt_interest 9. Rank 6 (pak).
// Win: pop 3000 / culture 35 / prosperity 40 / monuments TEMP 9 (pak raw 6;
//   first=22 Small Obelisk → formula 2.25×2+4.5=9) / kingdom 90 / housing level 14.
// Climate northern; map_background empire pack id 21.
// Full empire redefine (hide_pak_*) + JS event graph. SKIP empty map_obj idx=6.
// Chain-only invasion i=11 (after LOST Qadesh) → JS chain via event_request_cleared.
// Favour egypt×23 (i=30). Calendar canaanite×33 (i=31). next_mission 42 (Qadesh §13.4).
// Recurring request/gift outcomes fire via request_cleared (shared ONLY_VIA = ALREADY_FIRED once).
// Gift refuse paths are dead (engine gifts always COMPLETE).
// Timber i=6 vs i=24 same m2/resource: handoff y16 (i=6 stops, i=24 starts).
// Tag map: gift i5=3500+y; copper i5=7100+y (must differ — execute_event is first-tag-wins).

mission41 { // Sumur — Lands of the Levant
	map_file : "data/maps/m_041_sumur.map"

	// Map points from data/maps/m_041_sumur.map.
	herd_points_predator [ [113, 63], [73, 24] ]

	start_message : "message_mission_sumur"
	selection_title : "Sumur"
	player_rank : 6

	next_mission : 42

	// pak Normal funds=5565 loan=1500 debt_interest=9 → int_dcy around Normal.
	initial_funds [11130, 7420, 5565, 3730, 2950]
	rescue_loans [3000, 2000, 1500, 1000, 800]
	debt_interest [5, 7, 9, 11, 13]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C41_mission.mp3"
		victory : "Voice/Mission/C41_victory.mp3"
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
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_SMALL_OBELISK,
	]

	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 35 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 90 }
		housing_level {enabled : true, goal : 14 }
	}

	entry_point [108, 101]
	exit_point [108, 40]
	river_entry_point [71, 135]
	river_exit_point [21, 89]
	disembark_points [ [30, 85], [50, 99] ]
	invasion_points_land [ [54, 72] ]
	invasion_points_sea [ [16, 134] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:21}
	hide_pak_cities : true
	cities [
		{
			name : "Sumur"
			idx : 32
			pos : [876, 34]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FISH, RESOURCE_TIMBER, RESOURCE_COPPER ]
		}
		{
			name : "Men-nefer"
			idx : 4
			pos : [575, 494]
			route : 1
			is_open : false
			cost_to_open : 850
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_WEAPONS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_OIL ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 4000 }
				{ resource: RESOURCE_OIL, limit: 2500 }
			]
		}
		{
			name : "Rowarty"
			idx : 9
			pos : [612, 389]
			route : 2
			is_open : false
			cost_to_open : 625
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LETTUCE, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN ]
			buys [ RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}
		{
			name : "Waset"
			idx : 11
			pos : [818, 924]
			route : 4
			is_open : false
			cost_to_open : 1600
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_FLAX, RESOURCE_GRANITE ]
			buys [ RESOURCE_WEAPONS, RESOURCE_TIMBER, RESOURCE_OIL ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_OIL, limit: 4000 }
			]
		}
		{
			name : "Timna"
			idx : 31
			pos : [898, 469]
			route : 6
			is_open : false
			cost_to_open : 450
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_LINEN, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}
		{
			name : "Jericho"
			idx : 29
			pos : [901, 253]
			route : 7
			is_open : false
			cost_to_open : 210
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_OIL ]
			buys [ RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_OIL, limit: 2500 }
			]
		}
		{
			name : "Qadesh"
			idx : 8
			pos : [965, 22]
			route : 9
			is_open : true
			cost_to_open : 65
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_OIL ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_OIL, limit: 1500 }
			]
		}
		{
			name : "Enkomi"
			idx : 30
			pos : [692, 56]
			route : 10
			is_open : false
			cost_to_open : 185
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_TIMBER, RESOURCE_COPPER, RESOURCE_OIL ]
			buys [ RESOURCE_LINEN, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_OIL, limit: 2500 }
			]
		}
		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [425, 653]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Dakhla Oasis"
			idx : 1
			pos : [334, 1056]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Itjtawy"
			idx : 2
			pos : [594, 551]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Knossos"
			idx : 3
			pos : [175, 131]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Menat Khufu"
			idx : 5
			pos : [578, 720]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Pwenet"
			idx : 7
			pos : [1133, 1325]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 10
			pos : [861, 152]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[572, 518], [555, 478], [567, 442], [556, 414], [563, 399], [563, 379],
				[573, 350], [598, 331], [672, 356], [718, 338], [767, 338], [814, 310],
				[845, 266], [866, 135], [871, 96], [887, 65]
			]
		}
		{
			route : 2
			type : 2
			points [
				[631, 392], [639, 356], [676, 362], [719, 344], [770, 343], [820, 316],
				[853, 268], [858, 202], [871, 131], [883, 64]
			]
		}
		{
			route : 3
			type : 2
			points [
				[592, 562], [587, 539], [584, 523], [573, 514], [569, 504], [559, 498],
				[555, 475], [573, 430], [587, 420], [593, 398], [616, 388], [623, 366],
				[651, 342], [710, 333], [764, 327], [804, 304], [838, 260], [854, 133],
				[877, 63]
			]
		}
		{
			route : 4
			type : 2
			points [
				[825, 945], [827, 927], [812, 906], [790, 917], [777, 935], [756, 915],
				[745, 918], [720, 895], [716, 886], [699, 880], [676, 857], [650, 827],
				[610, 812], [596, 791], [593, 774], [580, 744], [567, 722], [569, 668],
				[581, 644], [601, 607], [591, 580], [585, 517], [562, 497], [552, 475],
				[544, 454], [541, 432], [532, 418], [522, 393], [521, 347], [541, 334],
				[596, 327], [643, 337], [756, 321], [799, 297], [830, 254], [846, 133],
				[876, 60], [879, 61]
			]
		}
		{
			route : 5
			type : 2
			points [
				[1168, 1333], [1178, 1315], [1164, 1253], [1097, 1072], [1025, 913], [891, 724],
				[852, 686], [722, 561], [703, 505], [692, 469], [673, 446], [621, 430],
				[650, 407], [649, 383], [635, 366], [640, 351], [680, 345], [766, 332],
				[814, 301], [842, 250], [860, 134], [879, 63]
			]
		}
		{
			route : 6
			type : 1
			points [
				[916, 476], [931, 439], [928, 391], [922, 347], [888, 287], [891, 204],
				[911, 151], [916, 105], [902, 62]
			]
		}
		{
			route : 7
			type : 1
			points [
				[916, 253], [902, 215], [915, 144], [919, 105], [916, 76], [908, 62]
			]
		}
		{
			route : 8
			type : 1
			points [
				[887, 160], [897, 122], [904, 87], [890, 63]
			]
		}
		{
			route : 9
			type : 1
			points [
				[966, 38], [951, 31], [941, 37], [934, 49], [907, 52]
			]
		}
		{
			route : 10
			type : 2
			points [
				[729, 73], [761, 62], [806, 61], [833, 50], [846, 47], [877, 49]
			]
		}
		{
			route : 11
			type : 2
			points [
				[213, 138], [257, 129], [350, 122], [579, 158], [615, 167], [647, 157],
				[692, 134], [736, 94], [807, 66], [874, 53]
			]
		}
		{
			route : 12
			type : 1
			points [
				[451, 664], [480, 583], [536, 557], [597, 546], [686, 493], [713, 486],
				[787, 410], [860, 325], [876, 233], [898, 156], [921, 92], [913, 68]
			]
		}
		{
			route : 13
			type : 1
			points [
				[931, 51], [913, 51]
			]
		}
	]

	hide_pak_objects : true
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
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [854, 294] }
	]

	fishing_points [ [56, 121], [82, 117], [76, 102], [74, 118] ]

	vars {
		chain_leaves_wired : false

		event0_gift_done : false
		event5_gift_armed : false
		event5_gift_last_year : -1
		event6_timber_armed : false
		event9_gems_done : false
		event13_water_armed : false
		event13_water_last_year : -1
		event14_demand_done : false
		event15_demand_done : false
		event16_oil_armed : false
		event18_sea_done : false
		event19_wage_done : false
		event20_grain_done : false
		event23_wage_done : false
		event24_timber_armed : false
		event27_sea_done : false
		event28_timber_done : false
		event31_invasion_done : false

		timber6_recurring_was_busy : false
		timber6_recurring_idle_since_abs : -1
		oil_recurring_was_busy : false
		oil_recurring_idle_since_abs : -1
		timber24_recurring_was_busy : false
		timber24_recurring_idle_since_abs : -1
		copper5_recurring_was_busy : false
		copper5_recurring_idle_since_abs : -1

		inv_lost_qadesh_done : false
		pharaoh_favour_invasion_done : false

		kr_seq : 0
		gift_seq : 0

		start_message_shown : false
	}
}

function mission41_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission41_make_chain_request(tag, resource, amount, months, subtype, sender_faction, city_name) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(sender_faction === undefined ? 0 : sender_faction)
	return request
}

function mission41_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, city_name) {
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
	request.execute()
	return request
}

function mission41_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag, refuse_tag) {
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
	if (ok_tag) {
		event.set_completed_action_tag(ok_tag)
	}
	if (refuse_tag) {
		event.set_refusal_action_tag(refuse_tag)
	}
	event.execute()
	return event
}

// pak loc is 1-based invasion-point index; out of range → entry fallback (-1,-1).
function mission41_loc_tile(loc) {
	if (loc == 1) {
		return [54, 72] // invasion_points_land[0]
	}
	if (loc == 2) {
		return [30, 85] // disembark_points[0]
	}
	return [-1, -1]
}

function mission41_canaanite_raid(invasion_id, size, attack_target, loc) {
	var tile = mission41_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 41 canaanite raid size=" + size + " id=" + invasion_id
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_CANAANITE)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_2_CANAANITE,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	})
}

function mission41_egypt_raid(invasion_id, size, attack_target, loc) {
	var tile = mission41_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 41 egypt raid size=" + size + " id=" + invasion_id
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		invasion_id: invasion_id,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: 0,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	})
}

// Multi-fire outcomes (KR / gifts) must NOT use shared ONLY_VIA leaves — master becomes
// ALREADY_FIRED after first via. Fire unique EVENT_TRIGGER_ONCE events instead.
function mission41_fire_kr(delta) {
	var type = delta >= 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE
	var amount = delta >= 0 ? delta : -delta
	mission.kr_seq = (mission.kr_seq | 0) + 1
	mission41_fire_simple_event(8000 + mission.kr_seq, type, undefined, amount)
}

function mission41_fire_gift(resource, amount) {
	mission.gift_seq = (mission.gift_seq | 0) + 1
	mission41_fire_simple_event(8500 + mission.gift_seq, EVENT_TYPE_GIFT_FROM_PHARAOH, resource, amount)
}

function mission41_apply_copper_outcome(outcome) {
	if (outcome == "ok") {
		mission41_fire_kr(4)
	} else if (outcome == "refuse") {
		mission41_fire_kr(-3)
	} else {
		mission41_fire_kr(1)
	}
}

function mission41_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) {
		return
	}
	mission.chain_leaves_wired = true

	// pak i=10 weapons×20 (chain from gems ok): any → LOST Qadesh (1012)
	var weapons = mission41_make_chain_request(1010, RESOURCE_WEAPONS, 20, 4, 6, 0, "Men-nefer")
	weapons.set_completed_action_tag(1012)
	weapons.set_refusal_action_tag(1012)
	weapons.set_too_late_action_tag(1012)

	// pak i=12 LOST Qadesh; ok→i=11 invasion no-op → JS chain on request_cleared
	mission41_make_leaf(1012, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Qadesh")

	// pak i=21 NEW_TRADE Knossos (display city — pak city_id=4)
	mission41_make_leaf(1021, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Knossos")

	// pak i=22 fish×9 chain from grain refuse (refuse KR via request_cleared — not ONLY_VIA)
	var fish = mission41_make_chain_request(1022, RESOURCE_FISH, 9, 5, 5, 0, "Qadesh")
	fish.set_completed_action_tag(1021)
	fish.set_too_late_action_tag(1021)

	// pak i=29 NEW_TRADE Men-nefer
	mission41_make_leaf(1029, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
}

[es=event_mission_start, mission=mission41]
function mission41_on_start(ev) {
	log_info("mission41: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_CANAANITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -1300
	__scenario_monuments.first = 22
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_sumur")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_2_CANAANITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission41_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission41]
function mission41_recurring_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_TIMBER, "timber6_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_OIL, "oil_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_TIMBER, "timber24_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_COPPER, "copper5_recurring", abs)
}

// pak i=0: gift grain×16 y0m2 → copper×8 (engine gift always completes; refuse N/A)
[es=event_advance_month, mission=mission41]
function mission41_event_i0_gift(ev) {
	if (mission.event0_gift_done) {
		return
	}
	if (ev.years_since_start > 0 || (ev.years_since_start == 0 && ev.month >= 2)) {
		mission.event0_gift_done = true
		mission41_ensure_chain_leaves()
		log_info("akhenaten: mission 41 gift grain×16 + copper×8", {ev:ev})
		mission41_fire_simple_event(2000, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_GRAIN, 16, "Men-nefer")
		// Unique once request — do not chain via ONLY_VIA copper (blocks i=5 recurring).
		mission41_fire_request(2001, RESOURCE_COPPER, 8, 12, 0, 0, 0, 0, 0, "Men-nefer")
	}
}

// pak i=5: gift grain×20 recurring y5m9+; ok→copper (gift refuse→KR−3 is dead — gifts auto-complete)
[es=event_advance_month, mission=mission41]
function mission41_event_i5_gift(ev) {
	if (!mission.event5_gift_armed) {
		if (ev.years_since_start > 5 || (ev.years_since_start == 5 && ev.month >= 9)) {
			mission.event5_gift_armed = true
		} else {
			return
		}
	}
	if (ev.month != 9) {
		return
	}
	if (mission.event5_gift_last_year == ev.years_since_start) {
		return
	}
	mission.event5_gift_last_year = ev.years_since_start
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 gift grain×20 recurring", {ev:ev})
	mission41_fire_simple_event(3000 + 5 * 100 + ev.years_since_start,
		EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_GRAIN, 20, "Pwenet")
	// Copper is the gift's ok-chain; skip if a copper request is already active.
	// Tag 7100+year — must NOT reuse 3500+year (gift tag above); execute_event finds first tag.
	var abs = ev.years_since_start * 12 + ev.month
	if (mission_recurring_request_may_fire(mission, RESOURCE_COPPER, "copper5_recurring", abs)) {
		mission41_fire_request(7100 + ev.years_since_start, RESOURCE_COPPER, 8, 12, 0, 0, 0, 0, 0, "Men-nefer")
	}
}

// pak i=6: timber×21/8mo recurring y7m2+ subtype=4 Qadesh — outcomes via request_cleared
// From y16 both i=6 and i=24 want month 2 / RESOURCE_TIMBER; may_fire would starve i=24.
// Handoff: i=6 owns m2 through y15; i=24 owns m2 from y16 (wiki soft deviation).
[es=event_advance_month, mission=mission41]
function mission41_event_i6_timber(ev) {
	if (!mission.event6_timber_armed) {
		if (ev.years_since_start > 7 || (ev.years_since_start == 7 && ev.month >= 2)) {
			mission.event6_timber_armed = true
		} else {
			return
		}
	}
	if (ev.years_since_start >= 16) {
		return
	}
	if (ev.month != 2) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber6_recurring", abs)) {
		return
	}
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 timber×21 recurring", {ev:ev})
	mission41_fire_request(3000 + 6 * 100 + ev.years_since_start, RESOURCE_TIMBER, 21, 8,
		0, 0, 0, 4, 0, "Qadesh")
}

// pak i=9: gems×9/4mo once y5m1 subtype=6 Pwenet → ok weapons; refuse/late LOST Qadesh
[es=event_advance_month, mission=mission41]
function mission41_event_i9_gems(ev) {
	if (mission.event9_gems_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 1)) {
		return
	}
	mission.event9_gems_done = true
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 gems×9", {ev:ev})
	mission41_fire_request(2009, RESOURCE_GEMS, 9, 4, 1010, 1012, 1012, 6, 0, "Pwenet")
}

// pak i=13: contaminated water recurring y14m7+
[es=event_advance_month, mission=mission41]
function mission41_event_i13_water(ev) {
	if (!mission.event13_water_armed) {
		if (ev.years_since_start > 14 || (ev.years_since_start == 14 && ev.month >= 7)) {
			mission.event13_water_armed = true
		} else {
			return
		}
	}
	if (ev.month != 7) {
		return
	}
	if (mission.event13_water_last_year == ev.years_since_start) {
		return
	}
	mission.event13_water_last_year = ev.years_since_start
	log_info("akhenaten: mission 41 contaminated water", {ev:ev})
	mission41_fire_simple_event(3000 + 13 * 100 + ev.years_since_start,
		EVENT_TYPE_CONTAMINATED_WATER, undefined, 7)
}

// pak i=14: demand+ copper×8 Rowarty (loc=2) y8m6 — engine only touches open cities
[es=event_advance_month, mission=mission41]
function mission41_event_i14_demand(ev) {
	if (mission.event14_demand_done) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 6)) {
		return
	}
	mission.event14_demand_done = true
	log_info("akhenaten: mission 41 demand+ copper Rowarty", {ev:ev})
	mission41_fire_simple_event(2014, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_COPPER, 8, "Rowarty")
}

// pak i=15: demand+ timber×8 Men-nefer y11m9
[es=event_advance_month, mission=mission41]
function mission41_event_i15_demand(ev) {
	if (mission.event15_demand_done) {
		return
	}
	if (ev.years_since_start < 11 || (ev.years_since_start == 11 && ev.month < 9)) {
		return
	}
	mission.event15_demand_done = true
	log_info("akhenaten: mission 41 demand+ timber Men-nefer", {ev:ev})
	mission41_fire_simple_event(2015, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 8, "Men-nefer")
}

// pak i=16: oil×7/9mo recurring y4m3+ Menat Khufu — outcomes via request_cleared
[es=event_advance_month, mission=mission41]
function mission41_event_i16_oil(ev) {
	if (!mission.event16_oil_armed) {
		if (ev.years_since_start > 4 || (ev.years_since_start == 4 && ev.month >= 3)) {
			mission.event16_oil_armed = true
		} else {
			return
		}
	}
	if (ev.month != 3) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_OIL, "oil_recurring", abs)) {
		return
	}
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 oil×7 recurring", {ev:ev})
	mission41_fire_request(3000 + 16 * 100 + ev.years_since_start, RESOURCE_OIL, 7, 9,
		0, 0, 0, 0, 0, "Menat Khufu")
}

// pak i=18: sea trade problem y12m5 amount=8 (engine duration fixed 48)
[es=event_advance_month, mission=mission41]
function mission41_event_i18_sea(ev) {
	if (mission.event18_sea_done) {
		return
	}
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 5)) {
		return
	}
	mission.event18_sea_done = true
	log_info("akhenaten: mission 41 sea trade problem", {ev:ev})
	mission41_fire_simple_event(2018, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 8)
}

// pak i=19: wage +4 y7m0 (engine raises one step; amount unused)
[es=event_advance_month, mission=mission41]
function mission41_event_i19_wage(ev) {
	if (mission.event19_wage_done) {
		return
	}
	if (ev.years_since_start != 7 || ev.month != 0) {
		return
	}
	mission.event19_wage_done = true
	log_info("akhenaten: mission 41 wage +4", {ev:ev})
	mission41_fire_simple_event(2019, EVENT_TYPE_WAGE_INCREASE, undefined, 4)
}

// pak i=20: grain×7/6mo once y3m6 subtype=5 Knossos
[es=event_advance_month, mission=mission41]
function mission41_event_i20_grain(ev) {
	if (mission.event20_grain_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 6)) {
		return
	}
	mission.event20_grain_done = true
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 grain×7", {ev:ev})
	mission41_fire_request(2020, RESOURCE_GRAIN, 7, 6, 1021, 1022, 1021, 5, 0, "Knossos")
}

// pak i=23: wage +4 y20m0
[es=event_advance_month, mission=mission41]
function mission41_event_i23_wage(ev) {
	if (mission.event23_wage_done) {
		return
	}
	if (ev.years_since_start != 20 || ev.month != 0) {
		return
	}
	mission.event23_wage_done = true
	log_info("akhenaten: mission 41 wage +4 (y20)", {ev:ev})
	mission41_fire_simple_event(2023, EVENT_TYPE_WAGE_INCREASE, undefined, 4)
}

// pak i=24: timber×14/10mo recurring y16m2+ Men-nefer — outcomes via request_cleared
[es=event_advance_month, mission=mission41]
function mission41_event_i24_timber(ev) {
	if (!mission.event24_timber_armed) {
		if (ev.years_since_start > 16 || (ev.years_since_start == 16 && ev.month >= 2)) {
			mission.event24_timber_armed = true
		} else {
			return
		}
	}
	if (ev.month != 2) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber24_recurring", abs)) {
		return
	}
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 timber×14 recurring", {ev:ev})
	mission41_fire_request(3000 + 24 * 100 + ev.years_since_start, RESOURCE_TIMBER, 14, 10,
		0, 0, 0, 0, 0, "Men-nefer")
}

// pak i=27: sea trade problem y13m8
[es=event_advance_month, mission=mission41]
function mission41_event_i27_sea(ev) {
	if (mission.event27_sea_done) {
		return
	}
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 8)) {
		return
	}
	mission.event27_sea_done = true
	log_info("akhenaten: mission 41 sea trade problem (y13)", {ev:ev})
	mission41_fire_simple_event(2027, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 8)
}

// pak i=28: timber×19/12mo once y8m0 subtype=4 Pwenet → NEW Men-nefer
[es=event_advance_month, mission=mission41]
function mission41_event_i28_timber(ev) {
	if (mission.event28_timber_done) {
		return
	}
	if (ev.years_since_start != 8 || ev.month != 0) {
		return
	}
	mission.event28_timber_done = true
	mission41_ensure_chain_leaves()
	log_info("akhenaten: mission 41 timber×19", {ev:ev})
	mission41_fire_request(2028, RESOURCE_TIMBER, 19, 12, 1029, 0, 1029, 4, 0, "Pwenet")
}

// pak i=30: by_favour egypt×23 attack=TROOPS loc=9 → entry fallback (KR≤0)
[es=event_advance_month, mission=mission41]
function mission41_event_i30_favour(ev) {
	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	log_info("akhenaten: mission 41 favour egypt×23", {ev:ev, kr: city.rating_kingdom})
	mission41_egypt_raid(30, 23, EVENT_ATTACK_TARGET_TROOPS, 9)
}

// pak i=31: canaanite×33 once y12m3 attack=BEST_BUILDINGS loc=5 → entry fallback
[es=event_advance_month, mission=mission41]
function mission41_event_i31_invasion(ev) {
	if (mission.event31_invasion_done) {
		return
	}
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 3)) {
		return
	}
	mission.event31_invasion_done = true
	log_info("akhenaten: mission 41 canaanite×33", {ev:ev})
	mission41_canaanite_raid(31, 33, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 5)
}

// Multi-fire outcomes + LOST Qadesh → canaanite×42 (pak i=11 loc=2)
[es=event_request_cleared, mission=mission41]
function mission41_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	var tag = ev.tag_id

	// Copper after gifts i=0 (2001) / i=5 (7100+year; not 3500 — that is the gift tag)
	if (tag == 2001 || (tag >= 7100 && tag < 7200)) {
		mission41_apply_copper_outcome(outcome)
		return
	}

	// pak i=6 timber recurring: ok→lettuce×21; refuse→KR−3; late→lettuce×14
	if (tag >= 3600 && tag < 3700) {
		if (outcome == "ok") {
			mission41_fire_gift(RESOURCE_LETTUCE, 21)
		} else if (outcome == "refuse") {
			mission41_fire_kr(-3)
		} else {
			mission41_fire_gift(RESOURCE_LETTUCE, 14)
		}
		return
	}

	// pak i=16 oil recurring: ok→granite×8; refuse→KR−3; late→KR+1
	if (tag >= 4600 && tag < 4700) {
		if (outcome == "ok") {
			mission41_fire_gift(RESOURCE_GRANITE, 8)
		} else if (outcome == "refuse") {
			mission41_fire_kr(-3)
		} else {
			mission41_fire_kr(1)
		}
		return
	}

	// pak i=24 timber recurring: ok→grain×15; refuse→KR−3; late→lettuce×12
	if (tag >= 5400 && tag < 5500) {
		if (outcome == "ok") {
			mission41_fire_gift(RESOURCE_GRAIN, 15)
		} else if (outcome == "refuse") {
			mission41_fire_kr(-3)
		} else {
			mission41_fire_gift(RESOURCE_LETTUCE, 12)
		}
		return
	}

	// pak i=28 timber refuse → KR−3 (ok/late already → NEW Men-nefer via 1029)
	if (tag == 2028 && outcome == "refuse") {
		mission41_fire_kr(-3)
		return
	}

	// pak i=22 fish refuse → KR−3
	if (tag == 1022 && outcome == "refuse") {
		mission41_fire_kr(-3)
		return
	}

	// gems refuse|late / weapons any → LOST leaf (via tags) + canaanite×42
	var lost_chain = (tag == 2009 && (outcome == "refuse" || outcome == "late"))
		|| (tag == 1010 && (outcome == "ok" || outcome == "refuse" || outcome == "late"))
	if (lost_chain && !mission.inv_lost_qadesh_done) {
		mission.inv_lost_qadesh_done = true
		log_info("akhenaten: mission 41 canaanite×42 after LOST Qadesh chain", {ev:ev, outcome:outcome})
		mission41_canaanite_raid(11, 42, EVENT_ATTACK_TARGET_RANDOM, 2)
	}
}
