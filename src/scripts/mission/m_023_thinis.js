log_info("akhenaten: mission 23 thinis civil-war started")

// Empire / events verified vs mission1.pak scenario 23 (2026-07-26 dump).
// Empire id=23. Scenario enemy ENEMY_6_KUSHITE (Nubian opportunism); Egyptian = loyalist/favour.
// Gods: Osiris, Ra, Ptah. Funds Normal 13350 / loan 4200 / debt 20. Rank 9. Climate northern.
// Win: pop 4500 / culture 25 / prosperity 35 / monuments 0 / kingdom 90 / housing count 10 + level 10.
// Burial empty. No monument slots.
// Trade: Waset(1) Men-nefer(2) Dunqul(3) Henen-nesw(4) Nekhen(5) Sauty(8) Khmun(9).
// Display: Kharga(6) Dakhla(7) Kerma(10) Jericho(11). SKIP orphan routes 12/13/14; empty map_obj idx=8.
// Protect (briefing): Temple Complex of Osiris + family mansion are pre-placed on the map
// and omitted from buildings[] — cannot rebuild if destroyed (original; not mission-fail).
// Altar/oracle stay allowed so the existing complex can still be upgraded.
// Keys: message_mission_thinis (423) — NOT thinis_2 / NOT gold_and_crime (mission 1).
// Oil i=7: ok/late → KR−10 → LOST×3 → pottery×23 → NEW×3 → (i=17) egypt×38;
//          refuse → KR+7 → LOST×3 → (i=10) egypt×38. Egypt armed by leaf 1019, spawned next month tick.
// Troops i=35–44: ok NEW→KR+5→enemy×29 wipe→egypt×33→KR+5; refuse KR−20→egypt×72 wipe→copper×30.
// Copper outcomes: ok→egypt×72; refuse→enemy×29→egypt×33; late→egypt×33.
// Henna×60 i=46–54: ok→egypt×32 wipe→enemy×48→KR+5→unlock troops rec; refuse→KR−25→egypt×72→enemy×48→KR+5;
//   late→KR−12→unlock troops rec (also calendar y17).
//
// Tag_id scheme:
//   1000 + i               chain-only leaves / chain requests
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission23 { // Thinis — Civil War FIP; != mission1 Dawn
	map_file : "data/maps/m_023_thinis.map"

	// Map points from data/maps/m_023_thinis.map.
	herd_points_prey [ [162, 169], [198, 96] ]

	start_message : "message_mission_thinis"
	selection_title : "Thinis"
	player_rank : 9
	reset_personal_savings : true

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 52]
	choice [
		{
			name : "Kebet"
			id : 25
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 53]
			pos [620, 420]
		}
		{
			name : "Menat Khufu"
			id : 26
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 54]
			pos [640, 480]
		}
	]

	// pak Normal funds=13350 loan=4200 debt_interest=20 → int_dcy around Normal.
	initial_funds [26700, 17800, 13350, 8900, 7080]
	rescue_loans [8400, 5600, 4200, 2800, 2200]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/223_mission.mp3"
		victory : "Voice/Mission/223_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY, BUILDING_DENTIST,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE,
		// no mansions — family mansion is map-only / non-rebuildable (protect)
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
		BUILDING_CLAY_PIT, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_GOLD_MINE,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM,
		BUILDING_FISHING_WHARF, BUILDING_CATTLE_RANCH, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS,
		// no BUILDING_TEMPLE_COMPLEX_OSIRIS — map-only / non-rebuildable (protect)
		BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
	]

	// pak monuments=0. Housing count+level both enabled.
	win_criteria {
		population    {enabled : true, goal : 4500 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 35 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 90 }
		housing_count {enabled : true, goal : 10 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [204, 131]
	exit_point [8, 105]
	river_entry_point [211, 124]
	river_exit_point [23, 90]
	disembark_points [ [30, 102], [71, 71], [177, 108] ]
	invasion_points_land [ [10, 22], [54, 212] ]
	invasion_points_sea [ [103, 91], [59, 123] ]

	enable_scenario_events : true

	hide_pak_cities : true
	cities [
		{
			name : "Thinis"
			idx : 11
			pos : [687, 871]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_STONE ]
			buys [ RESOURCE_COPPER ]
		}

		{
			name : "Waset"
			idx : 12
			pos : [811, 968]
			route : 1
			is_open : false
			cost_to_open : 240
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 7
			pos : [545, 487]
			route : 2
			is_open : false
			cost_to_open : 840
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Dunqul Oasis"
			idx : 1
			pos : [795, 1191]
			route : 3
			is_open : false
			cost_to_open : 475
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Henen-nesw"
			idx : 2
			pos : [534, 626]
			route : 4
			is_open : false
			cost_to_open : 580
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BEER, RESOURCE_FLAX ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
			]
		}

		{
			name : "Nekhen"
			idx : 9
			pos : [792, 1018]
			route : 5
			is_open : false
			cost_to_open : 280
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Sauty"
			idx : 10
			pos : [627, 801]
			route : 8
			is_open : false
			cost_to_open : 140
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POMEGRANATES ]
			buys [ RESOURCE_CHICKPEAS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
			]
		}

		{
			name : "Khmun"
			idx : 6
			pos : [577, 758]
			route : 9
			is_open : false
			cost_to_open : 180
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
			]
		}

		{
			name : "Kharga Oasis"
			idx : 5
			pos : [628, 1116]
			route : 6
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Dakhla Oasis"
			idx : 0
			pos : [349, 1037]
			route : 7
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 4
			pos : [732, 1491]
			route : 10
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Jericho"
			idx : 3
			pos : [896, 233]
			route : 11
			is_sea_trade : true
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
				[804, 961], [779, 947], [769, 945], [754, 935], [744, 929], [730, 924],
				[721, 919], [708, 898], [710, 890]
			]
		}
		{
			route : 2
			type : 2
			points [
				[568, 508], [584, 523], [587, 532], [589, 543], [593, 556], [590, 559],
				[592, 578], [594, 589], [601, 595], [601, 611], [586, 630], [584, 645],
				[572, 669], [570, 682], [570, 709], [565, 718], [573, 731], [584, 738],
				[587, 754], [595, 795], [613, 813], [624, 814], [655, 835], [656, 842],
				[676, 853], [678, 863], [710, 889]
			]
		}
		{
			route : 3
			type : 1
			points [
				[817, 1206], [839, 1197], [855, 1188], [866, 1178], [874, 1164], [877, 1142],
				[870, 1119], [870, 1108], [874, 1102], [869, 1094], [868, 1086], [870, 1070],
				[866, 1062], [860, 1056], [854, 1050], [855, 1040], [849, 1031], [846, 1026],
				[844, 1016], [828, 1002], [809, 966], [796, 958], [778, 947], [769, 946],
				[750, 932], [734, 926], [726, 924], [722, 919], [707, 897], [708, 891],
			]
		}
		{
			route : 4
			type : 2
			points [
				[554, 645], [562, 661], [558, 671], [558, 685], [559, 696], [561, 705],
				[556, 716], [559, 725], [567, 734], [573, 753], [583, 772], [591, 783],
				[596, 796], [607, 807], [623, 813], [642, 819], [656, 845], [670, 852],
				[682, 864], [688, 885], [708, 892]
			]
		}
		{
			route : 5
			type : 1
			points [
				[810, 1036], [803, 1004], [801, 976], [794, 957], [781, 948], [770, 946],
				[745, 930], [726, 925], [717, 913], [704, 896]
			]
		}
		{
			route : 6
			type : 1
			points [
				[128, 844], [127, 920]
			]
		}
		{
			route : 7
			type : 1
			points [
				[153, 846], [152, 916], [152, 916]
			]
		}
		{
			route : 8
			type : 1
			points [
				[645, 820], [659, 836], [665, 842], [675, 847], [677, 857], [688, 870],
				[704, 884], [711, 894]
			]
		}
		{
			route : 9
			type : 1
			points [
				[603, 780], [620, 798], [626, 814], [639, 824], [654, 834], [657, 844],
				[674, 853], [683, 864], [700, 881], [711, 894]
			]
		}
		{
			route : 10
			type : 1
			points [
				[865, 1357], [868, 1323], [869, 1306], [877, 1289], [881, 1275], [894, 1248],
				[897, 1235], [899, 1223], [885, 1212], [885, 1203], [889, 1196], [888, 1181],
				[879, 1165], [873, 1158], [877, 1141], [871, 1117], [870, 1108], [874, 1102],
				[868, 1088], [868, 1068], [861, 1057], [844, 1047], [810, 1037]
			]
		}
		{
			route : 11
			type : 2
			points [
				[893, 1351], [872, 1307], [882, 1275], [895, 1246], [899, 1224], [885, 1213],
				[887, 1203], [890, 1194], [877, 1162], [878, 1137], [872, 1109], [874, 1106],
				[875, 1103], [870, 1093], [870, 1068], [855, 1042], [845, 1027], [832, 1003],
				[826, 984]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [534, 423], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [414, 645], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [483, 512], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [777, 1338], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [519, 489], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [596, 441], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [825, 889], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [723, 912], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 1086], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [507, 553], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [571, 595], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [514, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [597, 531], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [777, 1198], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [381, 1037], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [621, 546], image : "pharaoh_general/empire_bits_00118" }
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
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		gift_copper_done : false
		gift_beer_done : false
		gamemeat_done : false
		oil_done : false
		enemy24_done : false
		henna120_done : false
		siege_khmun_done : false
		henna60_done : false
		city_fell_y3_done : false
		demand_pottery_done : false
		shared_leaves_wired : false
		troops_leaves_wired : false
		henna60_leaves_wired : false
		egypt38_done : false
		egypt38_pending : false
		egypt72_done : false
		egypt32_done : false
		enemy29_done : false
		enemy48_a_done : false
		enemy48_b_done : false
		egypt33_done : false
		// Wipe polls: after wave seen+cleared, spawn next.
		await_egypt33_after_enemy29 : false
		enemy29_enemies_seen : false
		await_copper_after_egypt72 : false
		egypt72_enemies_seen : false
		copper_seq : 0
		// Henna×60 wipe chain: egypt32→enemy48→KR+unlock | egypt72→enemy48→KR
		henna60_chain : ""
		henna60_enemies_seen : false
		troops_recurring_unlocked : false
		recurring_enemy_last_year : -1
		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
	}
}

function mission23_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission23_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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
	city.create_chain_event(opts).execute()
}

function mission23_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
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

// pak location_fields after randomize = 1-based land invasion point index.
// Map: land[0]=[10,22] land[1]=[54,212]; sea unused (all invasions subtype=0).
// Missing/OOB → -1 (engine entry fallback).
function mission23_loc_tile(loc) {
	if (loc == 1) {
		return [10, 22]
	}
	if (loc == 2) {
		return [54, 212]
	}
	return [-1, -1]
}

function mission23_egypt_raid(invasion_id, size, attack_target, on_completed_tag, loc) {
	var tile = mission23_loc_tile(loc === undefined ? 0 : loc)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target !== undefined ? attack_target : EVENT_ATTACK_TARGET_RANDOM
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

function mission23_kushite_raid(invasion_id, size, on_completed_tag, loc) {
	var tile = mission23_loc_tile(loc === undefined ? 0 : loc)
	__image_request_pak(PACK_ENEMY_KUSHITE)
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_6_KUSHITE,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

// pak i=38 wipe → i=43 egypt×33 → i=44 KR+5.
function mission23_start_enemy29_then_egypt33() {
	mission.await_egypt33_after_enemy29 = true
	mission.enemy29_enemies_seen = false
	log_info("akhenaten: mission 23 enemy x29 (then egypt x33 after wipe)")
	mission23_kushite_raid(38, 29, undefined, 10) // pak loc=10 OOB
}

// pak i=40 wipe → i=42 copper×30 (fire after wipe; re-arm uses new tag).
function mission23_start_egypt72_then_copper() {
	mission.await_copper_after_egypt72 = true
	mission.egypt72_enemies_seen = false
	log_info("akhenaten: mission 23 egypt x72 (then copper x30 after wipe)")
	mission23_egypt_raid(40, 72, undefined, undefined, 10) // pak loc=10 OOB
}

// pak i=10 / i=17 → i=19: leaf 1019 arms egypt×38; spawn on next month tick (not on oil/pottery cleared).
function mission23_arm_egypt38() {
	if (mission.egypt38_done || mission.egypt38_pending) {
		return
	}
	mission.egypt38_pending = true
	log_info("akhenaten: mission 23 egypt x38 armed (after LOST/NEW leaf)")
}

function mission23_spawn_egypt38_if_pending() {
	if (!mission.egypt38_pending || mission.egypt38_done) {
		return false
	}
	mission.egypt38_pending = false
	mission.egypt38_done = true
	log_info("akhenaten: mission 23 egypt x38 after LOST/NEW cascade")
	mission23_egypt_raid(19, 38, undefined, 1027, 1) // pak i=19 loc=1 → land[0]
	return true
}

function mission23_fire_copper30() {
	mission.copper_seq = mission.copper_seq + 1
	var tag = 2042 * 100 + mission.copper_seq
	log_info("akhenaten: mission 23 copper x30", { tag: tag })
	mission23_fire_request(tag, RESOURCE_COPPER, 30, 4, 0, 0, 0, 6, 0)
}

// pak i=49 / i=54 → i=55: unlock recurring troops×48 (also calendar y17).
function mission23_unlock_troops_recurring() {
	if (mission.troops_recurring_unlocked) {
		return
	}
	mission.troops_recurring_unlocked = true
	log_info("akhenaten: mission 23 troops recurring unlocked (henna×60 chain)")
}

// pak henna ok: egypt×32 → enemy×48 → KR+5 → unlock troops.
function mission23_start_henna60_ok_chain() {
	mission.henna60_chain = "await_enemy48_after_egypt32"
	mission.henna60_enemies_seen = false
	log_info("akhenaten: mission 23 egypt x32 after henna60 ok")
	mission23_egypt_raid(47, 32, undefined, undefined, 2) // pak i=47 loc=2 → land[1]
}

// pak henna refuse: KR−25 already; egypt×72 → enemy×48 → KR+5 (no troops unlock).
function mission23_start_henna60_refuse_chain() {
	mission.henna60_chain = "await_enemy48_after_egypt72"
	mission.henna60_enemies_seen = false
	log_info("akhenaten: mission 23 egypt x72 after henna60 refuse")
	mission23_egypt_raid(51, 72, undefined, undefined, 9) // pak i=51 loc=9 OOB
}

// Month tick: resolve wipe → next chain step.
function mission23_invasion_chain_tick() {
	// pak i=19 after i=10 LOST / i=17 NEW (armed via leaf 1019).
	if (mission23_spawn_egypt38_if_pending()) {
		return
	}

	if (mission.await_egypt33_after_enemy29) {
		if (city.num_enemy_formations > 0) {
			mission.enemy29_enemies_seen = true
			return
		}
		if (!mission.enemy29_enemies_seen) {
			return
		}
		mission.await_egypt33_after_enemy29 = false
		mission.enemy29_enemies_seen = false
		mission.egypt33_done = true
		log_info("akhenaten: mission 23 egypt x33 after enemy x29 wipe")
		mission23_egypt_raid(43, 33, undefined, 1044, 9) // pak i=43 loc=9 OOB
		return
	}

	if (mission.await_copper_after_egypt72) {
		if (city.num_enemy_formations > 0) {
			mission.egypt72_enemies_seen = true
			return
		}
		if (!mission.egypt72_enemies_seen) {
			return
		}
		mission.await_copper_after_egypt72 = false
		mission.egypt72_enemies_seen = false
		mission23_fire_copper30()
		return
	}

	if (mission.henna60_chain == "await_enemy48_after_egypt32") {
		if (city.num_enemy_formations > 0) {
			mission.henna60_enemies_seen = true
			return
		}
		if (!mission.henna60_enemies_seen) {
			return
		}
		mission.henna60_enemies_seen = false
		mission.henna60_chain = "await_kr_unlock_after_enemy48"
		mission.enemy48_a_done = true
		log_info("akhenaten: mission 23 enemy x48 after egypt x32 wipe")
		mission23_kushite_raid(48, 48, undefined, 10) // pak i=48 loc=10 OOB
		return
	}

	if (mission.henna60_chain == "await_kr_unlock_after_enemy48") {
		if (city.num_enemy_formations > 0) {
			mission.henna60_enemies_seen = true
			return
		}
		if (!mission.henna60_enemies_seen) {
			return
		}
		mission.henna60_chain = ""
		mission.henna60_enemies_seen = false
		log_info("akhenaten: mission 23 KR+5 + unlock troops after enemy x48 wipe")
		__city_event_fire_chain(1049)
		mission23_unlock_troops_recurring()
		return
	}

	if (mission.henna60_chain == "await_enemy48_after_egypt72") {
		if (city.num_enemy_formations > 0) {
			mission.henna60_enemies_seen = true
			return
		}
		if (!mission.henna60_enemies_seen) {
			return
		}
		mission.henna60_enemies_seen = false
		mission.henna60_chain = "await_kr_after_enemy48b"
		mission.enemy48_b_done = true
		log_info("akhenaten: mission 23 enemy x48 after henna refuse egypt x72 wipe")
		mission23_kushite_raid(52, 48, undefined, 13) // pak i=52 loc=13 OOB
		return
	}

	if (mission.henna60_chain == "await_kr_after_enemy48b") {
		if (city.num_enemy_formations > 0) {
			mission.henna60_enemies_seen = true
			return
		}
		if (!mission.henna60_enemies_seen) {
			return
		}
		mission.henna60_chain = ""
		mission.henna60_enemies_seen = false
		log_info("akhenaten: mission 23 KR+5 after henna refuse enemy x48 wipe")
		__city_event_fire_chain(1053)
	}
}

function mission23_ensure_shared_leaves() {
	if (mission.shared_leaves_wired) {
		return
	}
	mission.shared_leaves_wired = true
	mission23_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2)
	var kr5 = mission23_make_leaf(1004, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	var kr2 = mission23_make_leaf(1005, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 6)
	mission23_make_leaf(1006, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 16, 2)
	kr5.set_completed_action_tag(1006)
	kr2.set_completed_action_tag(1006)

	var kr10_oil = mission23_make_leaf(1026, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	var kr7 = mission23_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 4)

	// pak oil i=7 refuse → i=25 KR+7 → LOST×3 (loc route 4/8/9) → egypt×38 (JS chain).
	var lost_r1 = mission23_make_leaf(1008, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Henen-nesw")
	var lost_r2 = mission23_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Sauty")
	var lost_r3 = mission23_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Khmun")

	// pak oil ok/late → i=26 KR−10 → LOST×3 (loc route 1/2/3) → pottery×23.
	var lost_o1 = mission23_make_leaf(1011, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 37, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Waset")
	var lost_o2 = mission23_make_leaf(1012, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 35, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Men-nefer")
	var lost_o3 = mission23_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 21, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Dunqul Oasis")

	// pottery ok → NEW_TRADE×3 → arm egypt×38 (pak i=17 → i=19).
	var new1 = mission23_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 24, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Waset")
	var new2 = mission23_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 20, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	var new3 = mission23_make_leaf(1017, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 23, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dunqul Oasis")

	// pak i=19 attachment: chain-only arm leaf (no-op status); JS spawns egypt next month tick.
	mission23_make_leaf(1019, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 1, 1, 99)

	var kr10_pot = mission23_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	var kr5_pot = mission23_make_leaf(1064, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)

	// Create requests before wiring tags (set_*_action_tag looks up slave by tag).
	var pottery23 = city.create_good_request({
		tag_id: 1014, resource: RESOURCE_POTTERY, amount: 23, months_initial: 10,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	pottery23.set_sender_faction(0)

	// pak i=30–33: pottery×39 after egypt×38 wipe (i=27 KR+10). SKIP orphan i=29 (no inbound).
	var kr10_wipe = mission23_make_leaf(1027, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 4)
	mission23_make_leaf(1031, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)
	mission23_make_leaf(1032, EVENT_TYPE_REPUTATION_DECREASE, undefined, 21, 4)
	mission23_make_leaf(1033, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 4)
	var pottery39 = city.create_good_request({
		tag_id: 1030, resource: RESOURCE_POTTERY, amount: 39, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	pottery39.set_sender_faction(0)

	// Wire after all tags exist.
	kr7.set_completed_action_tag(1008)
	lost_r1.set_completed_action_tag(1009)
	lost_r2.set_completed_action_tag(1010)
	lost_r3.set_completed_action_tag(1019) // pak i=10 → i=19 egypt×38
	kr10_oil.set_completed_action_tag(1011)
	lost_o1.set_completed_action_tag(1012)
	lost_o2.set_completed_action_tag(1013)
	lost_o3.set_completed_action_tag(1014)
	pottery23.set_completed_action_tag(1015)
	pottery23.set_refusal_action_tag(1018)
	pottery23.set_too_late_action_tag(1064)
	new1.set_completed_action_tag(1016)
	new2.set_completed_action_tag(1017)
	new3.set_completed_action_tag(1019) // pak i=17 → i=19 egypt×38
	kr10_pot.set_completed_action_tag(1014)
	kr5_pot.set_completed_action_tag(1014)
	kr10_wipe.set_completed_action_tag(1030)
	pottery39.set_completed_action_tag(1031)
	pottery39.set_refusal_action_tag(1032)
	pottery39.set_too_late_action_tag(1033)

	mission23_make_leaf(1028, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)

	var fell = mission23_make_leaf(1022, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 38, 4,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Henen-nesw")
	mission23_make_leaf(1023, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 25, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Henen-nesw")
	fell.set_completed_action_tag(1023)
}

function mission23_ensure_troops_leaves() {
	if (mission.troops_leaves_wired) {
		return
	}
	mission.troops_leaves_wired = true
	mission23_ensure_shared_leaves()

	var troops = city.create_good_request({
		tag_id: 1035, resource: RESOURCE_TROOPS, amount: 48, months_initial: 6,
		subtype: 1, trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Khmun"
	})
	troops.set_sender_faction(0)

	// Create leaves before wiring (set_*_action_tag requires slave to exist).
	var nt = mission23_make_leaf(1036, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 20, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	var kr5 = mission23_make_leaf(1037, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 1)
	mission23_make_leaf(1039, EVENT_TYPE_REPUTATION_DECREASE, undefined, 20, 4)
	var kr10t = mission23_make_leaf(1041, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	mission23_make_leaf(1044, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)

	// pak: troops ok → NEW → KR+5; then JS enemy×29 (i=38). refuse → KR−20; then JS egypt×72.
	// late/defeat → KR−10 → re-ask troops. Copper×30 fired after egypt×72 wipe (JS).
	troops.set_completed_action_tag(1036)
	troops.set_refusal_action_tag(1039)
	troops.set_too_late_action_tag(1041)
	troops.set_defeat_action_tag(1041)
	nt.set_completed_action_tag(1037)
	kr10t.set_completed_action_tag(1035)
}

function mission23_ensure_henna60_leaves() {
	if (mission.henna60_leaves_wired) {
		return
	}
	mission.henna60_leaves_wired = true
	// pak i=49 KR+5 (after enemy×48 ok path) → unlock troops via JS after fire.
	mission23_make_leaf(1049, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	// pak i=50 KR−25 (henna refuse); i=53 KR+5 (refuse path end); i=54 KR−12 (late→unlock).
	mission23_make_leaf(1050, EVENT_TYPE_REPUTATION_DECREASE, undefined, 25, 2)
	mission23_make_leaf(1053, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission23_make_leaf(1054, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
	// pak i=56–58 recurring troops outcomes.
	mission23_make_leaf(1056, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission23_make_leaf(1057, EVENT_TYPE_REPUTATION_DECREASE, undefined, 22, 2)
	mission23_make_leaf(1058, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
}

[es=event_mission_start, mission=mission23]
function mission23_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_thinis")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission23_ensure_shared_leaves()
	mission23_ensure_troops_leaves()
	mission23_ensure_henna60_leaves()
}

[es=event_request_cleared, mission=mission23]
function mission23_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)

	// pak oil refuse → LOST×3 → leaf 1019 (arm). Spawn egypt next month tick, not here.
	// ok/late → LOST×3 → pottery×23 (egypt after NEW×3 → 1019).
	if (ev.tag_id == 2007 && outcome == "refuse") {
		mission23_arm_egypt38()
	}

	// pak pottery×23 ok → NEW×3 → leaf 1019 (arm). Spawn next month tick.
	if (ev.tag_id == 1014 && outcome == "ok") {
		mission23_arm_egypt38()
	}

	// pak i=30 pottery×39 outcomes (KR leaves already wired).
	if (ev.tag_id == 1030) {
		log_info("akhenaten: mission 23 pottery x39 cleared", { outcome: outcome })
	}

	// pak i=35 troops×48: ok → NEW→KR already cascaded; then enemy×29 wipe→egypt×33→KR+5.
	// refuse → KR−20 cascaded; then egypt×72 wipe→copper×30.
	if (ev.tag_id == 1035) {
		if (outcome == "ok") {
			mission.enemy29_done = true
			mission23_start_enemy29_then_egypt33()
		}
		if (outcome == "refuse") {
			mission.egypt72_done = true
			mission23_start_egypt72_then_copper()
		}
	}

	// pak i=42 copper×30: ok→egypt×72; refuse→enemy×29→egypt×33; late→egypt×33→KR+5.
	if (ev.resource == RESOURCE_COPPER) {
		log_info("akhenaten: mission 23 copper x30 cleared", { outcome: outcome, tag: ev.tag_id })
		if (outcome == "ok") {
			mission.egypt72_done = true
			mission23_start_egypt72_then_copper()
		} else if (outcome == "refuse") {
			mission.enemy29_done = true
			mission23_start_enemy29_then_egypt33()
		} else if (outcome == "late") {
			mission.egypt33_done = true
			log_info("akhenaten: mission 23 egypt x33 after copper late")
			mission23_egypt_raid(43, 33, undefined, 1044, 9) // pak i=43 loc=9 OOB
		}
	}

	// pak i=46 henna×60: ok→egypt×32→enemy×48→KR+5→unlock; refuse→KR−25→egypt×72→enemy×48→KR+5;
	// late/defeat→KR−12→unlock. Invasions via wipe poll (not parallel).
	if (ev.tag_id == 2046) {
		if (outcome == "ok") {
			mission.egypt32_done = true
			mission23_start_henna60_ok_chain()
		} else if (outcome == "refuse") {
			mission23_start_henna60_refuse_chain()
		} else if (outcome == "late") {
			mission23_unlock_troops_recurring()
		}
	}
}

[es=event_advance_month, mission=mission23]
function mission23_calendar(ev) {
	mission23_ensure_shared_leaves()
	mission23_ensure_troops_leaves()
	mission23_ensure_henna60_leaves()
	mission23_invasion_chain_tick()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_TROOPS, "troops_recurring", abs)

	if (!mission.gift_copper_done && ev.years_since_start == 2 && ev.month == 1) {
		mission.gift_copper_done = true
		log_info("akhenaten: mission 23 gift copper x10")
		mission23_fire_simple_event(2000, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 10)
	}
	if (!mission.gift_beer_done && ev.years_since_start == 2 && ev.month == 4) {
		mission.gift_beer_done = true
		log_info("akhenaten: mission 23 gift beer x8")
		mission23_fire_simple_event(2001, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_BEER, 8)
	}
	if (!mission.gamemeat_done && ev.years_since_start == 5 && ev.month == 1) {
		mission.gamemeat_done = true
		log_info("akhenaten: mission 23 gamemeat x10")
		mission23_fire_request(2002, RESOURCE_GAMEMEAT, 10, 10, 1003, 1004, 1005, 5, 0)
	}
	if (!mission.oil_done && ev.years_since_start == 6 && ev.month == 0) {
		mission.oil_done = true
		log_info("akhenaten: mission 23 oil x142")
		mission23_fire_request(2007, RESOURCE_OIL, 142, 2, 1026, 1025, 1026, 6, 0)
	}
	if (!mission.enemy24_done && ev.years_since_start == 7 && ev.month == 0) {
		mission.enemy24_done = true
		log_info("akhenaten: mission 23 kushite x24")
		mission23_kushite_raid(20, 24, 1028, 10) // pak i=20 loc=10 OOB
	}
	if (!mission.henna120_done && ev.years_since_start == 1 && ev.month == 7) {
		mission.henna120_done = true
		log_info("akhenaten: mission 23 henna x120 tribute")
		mission23_fire_request(2021, RESOURCE_HENNA, 120, 2, 1022, 1022, 1022, 2, 0, 1022)
	}
	if (!mission.siege_khmun_done && ev.years_since_start == 10 && ev.month == 3) {
		mission.siege_khmun_done = true
		log_info("akhenaten: mission 23 siege Khmun -> troops x48")
		var siege = city.create_chain_event({
			tag_id: 2034,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 32,
			subtype: EVENT_SUBTYPE_CITY_UNDER_SIEGE,
			city: "Khmun",
			trigger: EVENT_TRIGGER_ONCE
		})
		siege.set_param("months_initial", 4)
		siege.set_completed_action_tag(1035)
		siege.execute()
	}
	if (!mission.henna60_done && ev.years_since_start == 14 && ev.month == 4) {
		mission.henna60_done = true
		log_info("akhenaten: mission 23 henna x60")
		// ok=0 (JS egypt×32); refuse→KR−25; late/defeat→KR−12 (unlock in cleared / leaf).
		mission23_fire_request(2046, RESOURCE_HENNA, 60, 3, 0, 1050, 1054, 2, 0, 1054)
	}
	if (!mission.city_fell_y3_done && ev.years_since_start == 3 && ev.month == 0) {
		mission.city_fell_y3_done = true
		log_info("akhenaten: mission 23 CITY_FELL Sauty y3")
		mission23_fire_simple_event(2059, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, "Sauty",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
	}
	if (!mission.demand_pottery_done && ev.years_since_start == 3 && ev.month == 7) {
		mission.demand_pottery_done = true
		log_info("akhenaten: mission 23 demand pottery +6")
		mission23_fire_simple_event(2060, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_POTTERY, 6)
	}

	// pak i=55 troops×48 recurring: calendar y17, or earlier after henna×60 ok/late unlock (i=49/54).
	if ((mission.troops_recurring_unlocked || ev.years_since_start >= 17) && ev.month == 0
			&& mission_recurring_request_may_fire(mission, RESOURCE_TROOPS, "troops_recurring", abs)) {
		log_info("akhenaten: mission 23 recurring troops x48")
		mission23_fire_request(3000 + 55 * 100 + ev.years_since_start, RESOURCE_TROOPS, 48, 6,
			1056, 1057, 1058, 1, 0, 1058)
	}

	if (ev.years_since_start >= 5 && ev.month == 0
			&& mission.recurring_enemy_last_year != ev.years_since_start) {
		mission.recurring_enemy_last_year = ev.years_since_start
		log_info("akhenaten: mission 23 recurring kushite x21")
		mission23_kushite_raid(61, 21, undefined, 3) // pak i=61 loc=3 OOB (only land 1–2)
	}
}

// pak i=62 favour egypt×50 loc=2 → i=63 chain×50 loc=3 (want_destroy=0 like shared favour helper).
[es=event_advance_month, mission=mission23]
function mission23_favour(ev) {
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_chain_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_enemies_seen) {
			return
		}
		mission.pharaoh_favour_chain_done = true
		log_info("akhenaten: mission 23 pharaoh favour chain x50")
		var tile2 = mission23_loc_tile(3)
		__image_request_pak(PACK_ENEMY_EGYPTIAN)
		city.start_foreign_army_invasion({
			mode: ATTACK_TYPE_ENEMIES,
			enemy: ENEMY_3_EGYPTIAN,
			kind: INVASION_KIND_KINGDOME,
			size: 50,
			invasion_id: 25,
			tilex: tile2[0],
			tiley: tile2[1],
			want_destroy_buildings: 0,
			invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
		})
		return
	}
	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	mission.pharaoh_favour_enemies_seen = false
	mission.pharaoh_favour_chain_done = false
	log_info("akhenaten: mission 23 pharaoh favour x50")
	var tile = mission23_loc_tile(2)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: 50,
		invasion_id: 24,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
}
