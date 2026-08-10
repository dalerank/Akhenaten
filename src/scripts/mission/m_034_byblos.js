log_info("akhenaten: mission 34 byblos started")

// Empire id=33. Climate desert (pak). Enemy ENEMY_2_CANAANITE (briefing Hittite ignored).
// Gods Bast×2, Ptah, Seth. Funds Normal 45000 / loan 5000 / debt 20. Rank 10.
// Win: pop 6000 / culture 60 / prosperity 40 / monuments 14 (Large+2×Small obelisk
//   W=4+2+2=8 → trunc(2.25·8+4.5)=22 ≥ 14 keep pak) / kingdom 75 / housing 10.
// Burial empty. SKIP empty map_obj idx=9. Routes 1–10 copy (5/6/8 display-only orphans).
// No warship requests in pak (briefing-only navy buildings). No Sea People events.
// Favour egypt×161 → chain×128. Tag_id: 1000+i leaves; 2000+i once; 3000+i recurring.
// Truncate: 1↔4; 6↔8; 27↔45↔44; 53↔54. SKIP orphan 49↔50. Terminalize i13 (ok=97 OOB).
// TEMP: goods defeat→chain_only raids i4/i12/i27 unwired (engine defeat = troops only).

mission34 { // Byblos — Expansion and Conquest
	map_file : "data/maps/m_034_byblos.map"

	// Map points from data/maps/m_034_byblos.map.
	herd_points_predator [ [79, 11] ]
	fishing_points [ [65, 143], [19, 96], [32, 100], [35, 111], [49, 116], [50, 128], [68, 138], [59, 136] ]

	start_message : "message_mission_byblos"
	selection_title : "Byblos"
	player_rank : 10
	reset_personal_savings : true

	next_mission : 36

	initial_funds [90000, 60000, 45000, 30000, 24000]
	rescue_loans [10000, 6700, 5000, 3300, 2700]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/234_mission.mp3"
		victory : "Voice/Mission/234_victory.mp3"
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
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_LARGE_OBELISK, BUILDING_SMALL_OBELISK,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	win_criteria {
		population    {enabled : true, goal : 6000 }
		culture       {enabled : true, goal : 60 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : true, goal : 14 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [139, 114]
	exit_point [26, 59]
	river_entry_point [10, 77]
	river_exit_point [86, 166]
	disembark_points [ [59, 129], [76, 149], [81, 155] ]
	invasion_points_land [ [33, 76], [50, 51], [70, 34], [103, 9], [124, 7] ]
	invasion_points_sea [ [54, 158], [37, 133], [17, 116], [19, 91], [40, 80] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:33}
	hide_pak_cities : true
	cities [
		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FISH, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
		}
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 2
			is_open : true
			cost_to_open : 1600
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}
		{
			name : "Qadesh"
			idx : 30
			pos : [924, 29]
			route : 1
			is_open : false
			cost_to_open : 200
			trade : false
			type : EMPIRE_CITY_FOREIGN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Gaza"
			idx : 2
			pos : [846, 280]
			route : 7
			is_open : false
			trade : false
			type : EMPIRE_CITY_FOREIGN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS, RESOURCE_TIMBER ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
			]
		}
		{
			name : "Iken"
			idx : 3
			pos : [735, 1380]
			route : 3
			is_open : false
			cost_to_open : 1750
			trade : false
			type : EMPIRE_CITY_FOREIGN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_GOLD ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_GOLD, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
			]
		}
		{
			name : "Heh"
			idx : 31
			pos : [691, 1427]
			route : 4
			is_open : false
			cost_to_open : 1825
			trade : false
			type : EMPIRE_CITY_FOREIGN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_GOLD ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_GOLD, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
			]
		}
		{
			name : "Itjtawy"
			idx : 4
			pos : [568, 557]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Kerma"
			idx : 5
			pos : [732, 1491]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Khmun"
			idx : 6
			pos : [577, 758]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Knossos"
			idx : 7
			pos : [175, 131]
			route : 9
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			// Dump route=0; assign orphan sea route 8 so NEW_TRADE (i=48) can open a polyline.
			name : "Men-nefer"
			idx : 8
			pos : [545, 487]
			route : 8
			is_open : false
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Rowarty"
			idx : 10
			pos : [612, 389]
			route : 10
			is_open : false
			cost_to_open : 500
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
		{
			name : "Sharuhen"
			idx : 11
			pos : [836, 359]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Waset"
			idx : 12
			pos : [811, 968]
			route : 0
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
				[931, 36], [914, 40], [908, 51], [907, 58], [907, 69], [907, 83],
				[906, 86]
			]
		}
		{
			route : 2
			type : 2
			points [
				[887, 1173], [883, 1161], [887, 1140], [879, 1117], [884, 1103], [877, 1093],
				[879, 1078], [875, 1059], [865, 1050], [862, 1038], [843, 1016], [835, 1016],
				[816, 965], [826, 945], [815, 911], [777, 936], [757, 914], [732, 909],
				[665, 865], [597, 798], [584, 741], [570, 724], [570, 669], [583, 646],
				[583, 631], [601, 610], [587, 541], [586, 526], [554, 479], [569, 437],
				[586, 423], [591, 400], [609, 393], [642, 359], [677, 367], [731, 338],
				[777, 337], [833, 298], [851, 208], [872, 102], [906, 91]
			]
		}
		{
			route : 3
			type : 1
			points [
				[755, 1394], [789, 1339], [896, 1228], [920, 1215], [1015, 1186], [1053, 1122],
				[1046, 1055], [1014, 972], [959, 899], [853, 842], [841, 828], [832, 754],
				[809, 693], [706, 608], [668, 550], [679, 502], [709, 483], [723, 435],
				[756, 372], [816, 348], [856, 324], [883, 254], [892, 193], [904, 128],
				[908, 90]
			]
		}
		{
			route : 4
			type : 1
			points [
				[712, 1451], [740, 1448], [786, 1416], [816, 1378], [885, 1324], [924, 1241],
				[1020, 1199], [1059, 1132], [1064, 1125], [1052, 1051], [1022, 971], [967, 892],
				[851, 829], [841, 752], [819, 694], [716, 603], [682, 548], [691, 503],
				[724, 483], [770, 384], [861, 330], [891, 256], [910, 137], [912, 98]
			]
		}
		{
			route : 5
			type : 1
			points [
				[1075, 25], [979, 38], [956, 69], [924, 95]
			]
		}
		{
			route : 6
			type : 1
			points [
				[990, 351], [930, 337], [893, 310], [885, 287], [903, 201], [922, 138],
				[921, 94]
			]
		}
		{
			route : 7
			type : 1
			points [
				[774, 1480], [1020, 1215], [1067, 1140], [990, 976], [906, 886], [835, 838],
				[798, 707], [691, 620], [648, 552], [672, 486], [701, 480], [736, 383],
				[826, 331], [851, 306], [881, 203], [904, 104]
			]
		}
		{
			route : 8
			type : 2
			points [
				[798, 0], [800, 39], [808, 54], [822, 67], [842, 79], [869, 88],
				[899, 93]
			]
		}
		{
			route : 9
			type : 2
			points [
				[200, 147], [221, 140], [249, 137], [264, 123], [275, 97], [286, 76],
				[335, 63], [355, 64], [377, 54], [397, 48], [425, 16], [465, 19],
				[521, 36], [576, 52], [632, 53], [689, 38], [723, 11], [736, 65534],
				[753, 65535], [767, 13], [789, 45], [809, 70], [827, 86], [840, 91],
				[866, 97], [905, 107]
			]
		}
		{
			route : 10
			type : 2
			points [
				[631, 406], [636, 377], [638, 367], [640, 352], [672, 359], [725, 331],
				[772, 330], [825, 293], [859, 121], [876, 107], [907, 106]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [425, 649], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [536, 435], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [482, 509], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [563, 585], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [606, 728], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [624, 730], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [611, 424], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [604, 516], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [607, 754], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [511, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [577, 501], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [844, 965], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [865, 840], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [660, 1432], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [844, 981], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [866, 897], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [384, 1047], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [827, 1203], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [763, 1330], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [847, 897], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [711, 1387], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [612, 772], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [661, 827], image : "pharaoh_general/empire_bits_00115" }
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
		{ name : "#upper_egypt", pos : [683, 996] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [881, 131] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		chain_leaves_wired : false

		event0_invasion_done : false
		event1_henna_done : false
		event5_invasion_done : false
		event9_henna_done : false
		event14_henna_done : false
		event25_henna_done : false
		event33_invasion_done : false
		event34_demand_done : false
		event35_demand_done : false
		event36_demand_done : false
		event47_timber_done : false
		event51_chariots_done : false

		event11_timber_last_abs : -1
		event24_beduin_last_abs : -1
		event29_invasion_last_abs : -1
		event30_price_last_abs : -1
		event31_price_last_abs : -1
		event32_price_last_abs : -1
		event37_invasion_last_abs : -1
		timber_recurring_was_busy : false
		timber_recurring_idle_since_abs : -1

		kr39_once_done : false

		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		start_message_shown : false
	}
}

function mission34_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) { opts.resource = resource }
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) { leaf.set_param("months_initial", months) }
	return leaf
}

function mission34_make_chain_request(tag, resource, amount, months, subtype, city_name) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	}
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	return request
}

function mission34_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) { opts.resource = resource }
	if (city_name !== undefined) { opts.city = city_name }
	if (subtype !== undefined) { opts.subtype = subtype }
	var ev = city.create_chain_event(opts)
	if (ok_tag !== undefined && ok_tag > 0) { ev.set_completed_action_tag(ok_tag) }
	ev.event_is_active = true
	return ev
}

function mission34_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, city_name, defeat_tag) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONCE
	}
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	if (ok_tag !== undefined && ok_tag > 0) { request.set_completed_action_tag(ok_tag) }
	if (refuse_tag !== undefined && refuse_tag > 0) { request.set_refusal_action_tag(refuse_tag) }
	if (late_tag !== undefined && late_tag > 0) { request.set_too_late_action_tag(late_tag) }
	if (defeat_tag !== undefined && defeat_tag > 0) { request.set_defeat_action_tag(defeat_tag) }
	request.event_is_active = true
	return request
}

function mission34_loc_tile(loc) {
	if (loc == 1) { return [33, 76] }
	if (loc == 2) { return [50, 51] }
	if (loc == 3) { return [70, 34] }
	if (loc == 4) { return [103, 9] }
	if (loc == 5) { return [124, 7] }
	return [-1, -1]
}

function mission34_attack_target(attack) {
	if (attack == 0) { return EVENT_ATTACK_TARGET_FOOD }
	if (attack == 1) { return EVENT_ATTACK_TARGET_VAULTS }
	if (attack == 2) { return EVENT_ATTACK_TARGET_BEST_BUILDINGS }
	if (attack == 3) { return EVENT_ATTACK_TARGET_TROOPS }
	return EVENT_ATTACK_TARGET_RANDOM
}

function mission34_enemy_raid(invasion_id, size, loc, attack) {
	var tile = mission34_loc_tile(loc)
	__image_request_pak(PACK_ENEMY_CANAANITE)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_2_CANAANITE,
		size: size,
		invasion_id: invasion_id,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: 0,
		invasion_attack_target: mission34_attack_target(attack)
	})
}

function mission34_beduin_raid(invasion_id, size, loc) {
	var tile = mission34_loc_tile(loc)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		invasion_id: invasion_id,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
}

function mission34_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) { return }
	mission.chain_leaves_wired = true

	// i1 henna×44: ok→CONQUERED Abu→fish; refuse→KR-9→fish; defeat→raid×64 (JS)
	var conquered_abu = mission34_make_leaf(1002, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 10, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Abu")
	conquered_abu.set_completed_action_tag(1006)

	var kr_m9 = mission34_make_leaf(1003, EVENT_TYPE_REPUTATION_DECREASE, undefined, 9, 2)
	kr_m9.set_completed_action_tag(1006)

	var fish11 = mission34_make_chain_request(1006, RESOURCE_FISH, 11, 9, 0, "Abu")
	fish11.set_completed_action_tag(1007)
	fish11.set_refusal_action_tag(1008)
	fish11.set_too_late_action_tag(1008)

	mission34_make_leaf(1007, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Qadesh")

	// Truncate 6↔8: one fish×5 retry; refuse terminal
	var fish5 = mission34_make_chain_request(1008, RESOURCE_FISH, 5, 6, 0, "Abu")
	fish5.set_completed_action_tag(1007)

	// i9 henna×34 ok→CONQUERED Khmun terminal; defeat→raid×62 (JS)
	mission34_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Khmun")

	// i14 henna×52: ok→CONQUERED Gaza→KR+6 terminal; refuse→sea problem; defeat→LOST→troops
	var conquered_gaza = mission34_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Gaza")
	conquered_gaza.set_completed_action_tag(1013)

	mission34_make_leaf(1013, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2)

	mission34_make_leaf(1016, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 7, 2)

	var lost_gaza = mission34_make_leaf(1017, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Gaza")
	lost_gaza.set_completed_action_tag(1018)

	var troops83 = mission34_make_chain_request(1018, RESOURCE_TROOPS, 83, 2, 1, "Gaza")
	troops83.set_completed_action_tag(1019)
	troops83.set_refusal_action_tag(1020)
	troops83.set_too_late_action_tag(1020)
	troops83.set_defeat_action_tag(1020)

	mission34_make_leaf(1019, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Abu")

	var fell_byblos = mission34_make_leaf(1020, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Byblos")
	fell_byblos.set_completed_action_tag(1039)

	var kr_m10 = mission34_make_leaf(1039, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2)
	kr_m10.set_completed_action_tag(1021)

	var weapons11 = mission34_make_chain_request(1021, RESOURCE_WEAPONS, 11, 18, 0, "Gaza")
	weapons11.set_completed_action_tag(1022)
	weapons11.set_refusal_action_tag(1023)
	weapons11.set_too_late_action_tag(1039)
	weapons11.set_defeat_action_tag(1023)

	var trade_iken = mission34_make_leaf(1022, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Iken")
	trade_iken.set_completed_action_tag(1013)

	var grain83 = mission34_make_chain_request(1023, RESOURCE_GRAIN, 83, 18, 6, "Gaza")
	grain83.set_completed_action_tag(1022)
	grain83.set_refusal_action_tag(1043)
	grain83.set_too_late_action_tag(1043)

	mission34_make_leaf(1043, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)

	// i25 henna×64: ok→CONQUERED Iken→NEW_TRADE Heh→KR+6; refuse→LOST path; defeat→raid×135 (JS)
	var conquered_iken = mission34_make_leaf(1026, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Iken")
	conquered_iken.set_completed_action_tag(1028)

	var trade_heh = mission34_make_leaf(1028, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Heh")
	trade_heh.set_completed_action_tag(1013)

	// Truncate 27↔45↔44: one escalation henna/weapons
	var henna64b = mission34_make_chain_request(1045, RESOURCE_HENNA, 64, 9, 2, "Iken")
	henna64b.set_completed_action_tag(1026)
	henna64b.set_refusal_action_tag(1044)
	henna64b.set_too_late_action_tag(1044)

	var weapons12 = mission34_make_chain_request(1044, RESOURCE_WEAPONS, 12, 2, 6, "Iken")
	weapons12.set_completed_action_tag(1028)

	// i11 recurring timber outcomes
	mission34_make_leaf(1041, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 2)
	mission34_make_leaf(1042, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2)

	// i47 timber→NEW_TRADE Men-nefer→KR+6
	var trade_mennefer = mission34_make_leaf(1048, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	trade_mennefer.set_completed_action_tag(1013)

	// i51 chariots: ok→NEW_TRADE Rowarty→KR+9; refuse→KR-3→chariots×8 once
	var trade_rowarty = mission34_make_leaf(1052, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Rowarty")
	trade_rowarty.set_completed_action_tag(1041)

	var kr_m3 = mission34_make_leaf(1053, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	kr_m3.set_completed_action_tag(1054)

	var chariots8 = mission34_make_chain_request(1054, RESOURCE_CHARIOTS, 8, 9, 0, "Rowarty")
	chariots8.set_completed_action_tag(1052)
}

[es=event_mission_start, mission=mission34]
function mission34_on_start(ev) {
	__image_request_pak(PACK_ENEMY_CANAANITE)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_byblos")
	empire.set_id(33)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_2_CANAANITE)
	__scenario_monuments.first = 23
	__scenario_monuments.second = 22
	__scenario_monuments.third = 22
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission34_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission34]
function mission34_requests_and_events(ev) {
	mission34_ensure_chain_leaves()
	var abs = ev.years_since_start * 12 + ev.month

	if (!mission.event0_invasion_done && ev.years_since_start == 2 && ev.month == 0) {
		mission.event0_invasion_done = true
		log_info("akhenaten: mission 34 canaanite×28 (i=0)")
		mission34_enemy_raid(2000, 28, 3, 2)
	}
	if (!mission.event1_henna_done && ev.years_since_start == 4 && ev.month == 0) {
		mission.event1_henna_done = true
		log_info("akhenaten: mission 34 henna×44 (i=1)")
		mission34_fire_request(2001, RESOURCE_HENNA, 44, 12, 1002, 1003, 1003, 2, "Abu")
	}
	if (!mission.event5_invasion_done && ev.years_since_start == 6 && ev.month == 4) {
		mission.event5_invasion_done = true
		log_info("akhenaten: mission 34 canaanite×64 (i=5)")
		mission34_enemy_raid(2005, 64, 5, 0)
	}
	if (!mission.event9_henna_done && ev.years_since_start == 7 && ev.month == 1) {
		mission.event9_henna_done = true
		log_info("akhenaten: mission 34 henna×34 (i=9)")
		mission34_fire_request(2009, RESOURCE_HENNA, 34, 9, 1010, 1003, 1003, 2, "Khmun")
	}
	if (!mission.event14_henna_done && ev.years_since_start == 8 && ev.month == 10) {
		mission.event14_henna_done = true
		log_info("akhenaten: mission 34 henna×52 (i=14)")
		mission34_fire_request(2014, RESOURCE_HENNA, 52, 18, 1015, 1016, 1016, 2, "Gaza", 1017)
	}
	if (!mission.event47_timber_done && ev.years_since_start == 2 && ev.month == 2) {
		mission.event47_timber_done = true
		log_info("akhenaten: mission 34 timber×17 (i=47)")
		mission34_fire_request(2047, RESOURCE_TIMBER, 17, 9, 1048, 0, 0, 0, "Men-nefer")
	}
	if (!mission.event51_chariots_done && ev.years_since_start == 9 && ev.month == 8) {
		mission.event51_chariots_done = true
		log_info("akhenaten: mission 34 chariots×11 (i=51)")
		mission34_fire_request(2051, RESOURCE_CHARIOTS, 11, 8, 1052, 1053, 1053, 0, "Rowarty")
	}
	if (!mission.event25_henna_done && ev.years_since_start == 13 && ev.month == 7) {
		mission.event25_henna_done = true
		log_info("akhenaten: mission 34 henna×64 (i=25)")
		mission34_fire_request(2025, RESOURCE_HENNA, 64, 18, 1026, 1017, 1017, 2, "Iken")
	}
	if (!mission.event33_invasion_done && ev.years_since_start == 22 && ev.month == 8) {
		mission.event33_invasion_done = true
		log_info("akhenaten: mission 34 canaanite×119 (i=33)")
		mission34_enemy_raid(2033, 119, 3, 1)
	}
	if (!mission.event34_demand_done && ev.years_since_start == 23 && ev.month == 0) {
		mission.event34_demand_done = true
		log_info("akhenaten: mission 34 timber demand +8 (i=34)")
		mission34_fire_simple_event(2034, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 8, "Abu")
	}
	if (!mission.event35_demand_done && ev.years_since_start == 24 && ev.month == 0) {
		mission.event35_demand_done = true
		log_info("akhenaten: mission 34 copper demand +8 (i=35)")
		mission34_fire_simple_event(2035, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_COPPER, 8, "Abu")
	}
	if (!mission.event36_demand_done && ev.years_since_start == 25 && ev.month == 0) {
		mission.event36_demand_done = true
		log_info("akhenaten: mission 34 weapons demand +6 (i=36)")
		mission34_fire_simple_event(2036, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_WEAPONS, 6, "Abu")
	}

	// i11 recurring timber×9 / 6mo from y9m0
	if (abs >= 9 * 12 + 0 && (abs - (9 * 12 + 0)) % 6 == 0 && mission.event11_timber_last_abs != abs) {
		if (mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber_recurring", abs)) {
			mission.event11_timber_last_abs = abs
			log_info("akhenaten: mission 34 timber×9 recurring (i=11) abs=" + abs)
			mission34_fire_request(3011 + ev.years_since_start, RESOURCE_TIMBER, 9, 6, 1041, 1042, 0, 0, "Abu")
		}
	}

	// i24 beduin×96 / 6mo from y12m3
	if (abs >= 12 * 12 + 3 && (abs - (12 * 12 + 3)) % 6 == 0 && mission.event24_beduin_last_abs != abs) {
		if (city.num_enemy_formations == 0) {
			mission.event24_beduin_last_abs = abs
			log_info("akhenaten: mission 34 beduin×96 recurring (i=24) abs=" + abs)
			mission34_beduin_raid(3024, 96, 1)
		}
	}

	// i29 canaanite×125 / 6mo from y16m0 (loc 11 → entry fallback)
	if (abs >= 16 * 12 + 0 && (abs - (16 * 12 + 0)) % 6 == 0 && mission.event29_invasion_last_abs != abs) {
		if (city.num_enemy_formations == 0) {
			mission.event29_invasion_last_abs = abs
			log_info("akhenaten: mission 34 canaanite×125 recurring (i=29) abs=" + abs)
			mission34_enemy_raid(3029, 125, 11, 4)
		}
	}

	// i30/31/32 recurring prices months=2
	if (abs >= 19 * 12 + 2 && (abs - (19 * 12 + 2)) % 2 == 0 && mission.event30_price_last_abs != abs) {
		mission.event30_price_last_abs = abs
		mission34_fire_simple_event(3030 + ev.years_since_start, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 8, "Abu")
	}
	if (abs >= 21 * 12 + 4 && (abs - (21 * 12 + 4)) % 2 == 0 && mission.event31_price_last_abs != abs) {
		mission.event31_price_last_abs = abs
		mission34_fire_simple_event(3031 + ev.years_since_start, EVENT_TYPE_PRICE_INCREASE, RESOURCE_COPPER, 6, "Abu")
	}
	if (abs >= 22 * 12 + 6 && (abs - (22 * 12 + 6)) % 2 == 0 && mission.event32_price_last_abs != abs) {
		mission.event32_price_last_abs = abs
		mission34_fire_simple_event(3032 + ev.years_since_start, EVENT_TYPE_PRICE_INCREASE, RESOURCE_WEAPONS, 24, "Abu")
	}

	// i37 canaanite×141 / 6mo from y28m8
	if (abs >= 28 * 12 + 8 && (abs - (28 * 12 + 8)) % 6 == 0 && mission.event37_invasion_last_abs != abs) {
		if (city.num_enemy_formations == 0) {
			mission.event37_invasion_last_abs = abs
			log_info("akhenaten: mission 34 canaanite×141 recurring (i=37) abs=" + abs)
			mission34_enemy_raid(3037, 141, 12, 0)
		}
	}

	mission_pharaoh_favour_invasion_tick(mission, 161, 128)
}

[es=event_request_cleared, mission=mission34]
function mission34_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)

	// TEMP: pak defeat→chain_only invasion (i4/i12/i27) on goods requests does not emit
	// via request_cleared (engine defeat path is troops/distant-battle). Troops i18 defeat
	// is wired via leaf 1020. Goods defeat→raid left unwired until B12 goods-defeat exists.

	if (ev.tag_id == 1023 && outcome != "ok" && !mission.kr39_once_done) {
		mission.kr39_once_done = true
		log_info("akhenaten: mission 34 grain refuse → KR once (truncate)")
	}
}
