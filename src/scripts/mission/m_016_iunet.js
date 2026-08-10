log_info("akhenaten: mission 16 iunet started")

// Empire / requests / events verified vs mission1.pak scenario 16 (2026-07-26 dump).
// Empire id=1. Scenario enemy ENEMY_4_HITTITE (briefing text says Kushite — pak wins).
// Gods: Ra, Seth, Bast. Favour Pharaoh 15→45→30→30.
// Triage: SKIP invasion i=3 amount=0; NEW_TRADE i=1/6 remap Iunet→Men-nefer / Abu
// (pak city=ours + ok=999/99 junk; goods filled — pak sells/buys empty).
// Limestone refuse→KR−40→egypt×24: EVENT_TYPE_INVASION no-op → JS after KR−40 snap.
// SKIP map_obj idx=9 empty; SKIP orphan route 15; Saqqara/Nekhen route 5/8 no polyline.
// Clay flood i=9 y4m1 amount=7 → once, 7% of clay pits.
//
// Tag_id scheme:
//   1000 + i               chain-only ONLY_VIA_EVENT leaves
//   2000 + i               once calendar roots

mission16 { // Iunet (Dendera) — The Defense of Egypt
	map_file : "data/maps/m_016_iunet.map"

	// Map points from data/maps/m_016_iunet.map.
	herd_points_predator [ [39, 63], [113, 85] ]
	fishing_points [ [73, 41], [110, 53], [106, 80], [48, 62] ]

	start_message : "message_mission_dendera"
	selection_title : "Iunet"
	player_rank : 6

	// Iunet (16) and On (17) are a choice pair; both converge on Rostja (18).
	next_mission : 18

	// pak Normal funds=10000 loan=2500 debt_interest=8 → int_dcy around Normal.
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [4, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		bricks: { type:RESOURCE_BRICKS, allow: true},
	}

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/216_mission.mp3"
		victory : "Voice/Mission/216_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY,
		BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_BRICKS_WORKSHOP, BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP,
		BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_WEAVER_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM,
		BUILDING_FISHING_WHARF, BUILDING_CATTLE_RANCH,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_GOLD_MINE, BUILDING_CLAY_PIT,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals verified vs pak: pop 4000, culture 30, prosperity 30, monuments 9, kingdom 65,
	// housing_level 16. Monuments 9 = small mastaba (matches).
	win_criteria {
		population    {enabled : true, goal : 4000 }
		culture       {enabled : true, goal : 30 }
		prosperity    {enabled : true, goal : 30 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 65 }
		housing_level {enabled : true, goal : 16 }
	}

	entry_point [37, 32]
	exit_point [48, 21]
	river_entry_point [123, 53]
	river_exit_point [3, 71]
	disembark_points [ [32, 61], [94, 49], [50, 55] ]
	invasion_points_land [ [128, 119], [91, 4] ]
	invasion_points_sea [ [79, 49], [115, 72] ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Iunet"
			idx : 5
			pos : [783, 892]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_MEAT, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
		}

		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
			route : 1
			is_open : false
			cost_to_open : 480
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BARLEY, RESOURCE_BEER ]
			buys [ RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Selima Oasis"
			idx : 12
			pos : [612, 1356]
			route : 2
			is_open : false
			cost_to_open : 820
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Kerma"
			idx : 6
			pos : [732, 1491]
			route : 3
			is_open : false
			cost_to_open : 870
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			// Starts egyptian display; unlocked via meat ok → NEW_TRADE (pak i=6 remap).
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 4
			is_open : false
			cost_to_open : 390
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_CHICKPEAS ]
			buys [ RESOURCE_GRANITE, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Dahshur"
			idx : 4
			pos : [570, 530]
			route : 6
			is_open : false
			cost_to_open : 620
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_GEMS, RESOURCE_STONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			// Starts pharaoh display; unlocked via fish ok → NEW_TRADE (pak i=1 remap).
			name : "Men-nefer"
			idx : 8
			pos : [535, 467]
			route : 7
			is_open : false
			cost_to_open : 700
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_PHARAOH
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_BEER ]
			buys [ RESOURCE_GRANITE, RESOURCE_GOLD, RESOURCE_POTTERY ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_GOLD, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 10
			is_open : false
			cost_to_open : 1400
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kyrene"
			idx : 7
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Nekhen"
			idx : 10
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 11
			pos : [523, 539]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Buhen land
			type : 1
			points [
				[792, 1350], [839, 1298], [877, 1175], [808, 1020], [806, 916]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [
				[631, 1377], [658, 1372], [670, 1370], [684, 1366], [695, 1364], [715, 1357],
				[728, 1353], [740, 1354], [775, 1362], [776, 1363], [772, 1364], [778, 1365],
				[780, 1367], [778, 1357], [784, 1333], [788, 1321], [780, 1308], [780, 1299],
				[785, 1285], [785, 1279], [782, 1259], [784, 1253], [789, 1245], [789, 1232],
				[789, 1214], [786, 1196], [766, 1176], [763, 1159], [769, 1152], [782, 1135],
				[791, 1115], [792, 1112], [792, 1104], [790, 1094], [790, 1077], [795, 1070],
				[800, 1058], [802, 1048], [804, 1036], [804, 1034], [800, 989], [798, 947], [805, 919]
			]
		}
		{
			route : 3 // Kerma sea
			type : 2
			points [
				[741, 1497], [729, 1484], [710, 1481], [700, 1473], [694, 1464], [717, 1458],
				[729, 1438], [751, 1424], [761, 1409], [774, 1404], [781, 1397], [788, 1384],
				[800, 1350], [810, 1339], [827, 1315], [847, 1303], [864, 1320], [879, 1300],
				[898, 1249], [905, 1229], [897, 1214], [888, 1209], [895, 1198], [883, 1151],
				[887, 1133], [879, 1108], [882, 1098], [876, 1082], [880, 1066], [864, 1048],
				[862, 1033], [850, 1020], [833, 1012], [822, 996], [812, 986], [818, 968],
				[816, 957], [828, 943], [812, 917]
			]
		}
		{
			route : 4 // Abu sea (display egyptian)
			type : 2
			points [
				[885, 1169], [882, 1156], [886, 1138], [879, 1123], [879, 1122], [878, 1116],
				[877, 1111], [882, 1104], [882, 1098], [876, 1087], [877, 1080], [879, 1071],
				[876, 1064], [874, 1059], [870, 1055], [867, 1053], [866, 1050], [864, 1045],
				[864, 1037], [862, 1034], [851, 1023], [838, 1015], [827, 1003], [823, 997],
				[818, 994], [812, 984], [816, 976], [818, 968], [816, 964], [816, 958],
				[822, 951], [829, 945], [822, 924], [813, 917]
			]
		}
		{
			route : 6 // Dahshur sea
			type : 2
			points [
				[591, 548], [593, 579], [599, 599], [599, 612], [583, 631], [582, 648],
				[570, 666], [569, 711], [567, 723], [582, 740], [591, 769], [597, 782],
				[596, 795], [613, 813], [626, 818], [643, 825], [655, 836], [655, 845],
				[674, 853], [677, 861], [690, 871], [703, 885], [717, 888], [724, 901],
				[739, 912], [745, 918], [757, 914], [761, 924], [773, 934], [783, 932], [806, 916]
			]
		}
		{
			route : 7 // Men-nefer display
			type : 2
			points [
				[564, 497], [583, 523], [589, 545], [593, 599], [598, 595], [599, 614],
				[585, 629], [581, 644], [573, 661], [568, 687], [568, 712], [567, 724],
				[582, 738], [587, 763], [597, 778], [597, 798], [614, 814], [625, 817],
				[629, 824], [644, 824], [653, 833], [654, 842], [673, 853], [679, 866],
				[692, 874], [698, 882], [717, 887], [722, 901], [737, 910], [744, 919],
				[756, 914], [763, 926], [774, 936], [807, 917]
			]
		}
		{
			route : 10 // Byblos sea
			type : 2
			points [
				[898, 87], [874, 108], [868, 161], [841, 305], [754, 355], [727, 356],
				[698, 376], [674, 373], [638, 357], [634, 373], [651, 398], [652, 407],
				[628, 425], [597, 444], [590, 458], [573, 465], [576, 519], [587, 531],
				[592, 578], [600, 609], [584, 630], [583, 649], [570, 669], [570, 711],
				[565, 721], [573, 733], [583, 742], [590, 774], [596, 778], [596, 797],
				[612, 813], [624, 816], [627, 823], [640, 824], [654, 833], [656, 844],
				[675, 856], [680, 866], [701, 882], [718, 888], [723, 899], [737, 916],
				[754, 918], [757, 914], [765, 928], [775, 936], [806, 919]
			]
		}
	]
	// SKIP orphan route 15.

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [508, 485], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [503, 535], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [602, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [563, 579], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [729, 927], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [845, 1091], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [785, 1328], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [614, 545], image : "pharaoh_general/empire_bits_00118" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [407, 480] }
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
		shared_kr_leaves_wired : false
		fish_leaves_wired : false
		meat_leaves_wired : false
		pottery_leaves_wired : false
		limestone_leaves_wired : false

		event0_fish_done : false
		event4_meat_done : false
		event8_hittite_done : false
		event9_clay_done : false
		event10_pottery_done : false
		event12_hittite_done : false
		event13_hittite_done : false
		event14_limestone_done : false
		event17_hittite_done : false
		limestone_egypt_done : false

		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_wave4_done : false
		pharaoh_favour_wave2_enemies_seen : false
		pharaoh_favour_wave3_enemies_seen : false
		pharaoh_favour_wave4_enemies_seen : false

		start_message_shown : false
	}
}

function mission16_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission16_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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
	request.execute()
	return request
}

function mission16_hittite_raid(invasion_id, size, attack_target, on_completed_tag, on_refusal_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_4_HITTITE,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	if (on_refusal_tag) {
		opts.on_refusal_tag = on_refusal_tag
	}
	city.start_foreign_army_invasion(opts)
}

function mission16_egypt_raid(invasion_id, size, attack_target) {
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

// Shared KR−10 leaf (pak i=2). Refuse/late only — do not chain to NEW_TRADE (pak did via junk i=1).
function mission16_ensure_shared_kr_leaves() {
	if (mission.shared_kr_leaves_wired) {
		return
	}
	mission.shared_kr_leaves_wired = true
	mission16_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
}

// pak i=1 NEW_TRADE city=Iunet junk → remap Men-nefer (pharaoh + route 7).
function mission16_ensure_fish_leaves() {
	if (mission.fish_leaves_wired) {
		return
	}
	mission.fish_leaves_wired = true
	mission16_make_leaf(1001, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 10, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
}

// pak i=4 meat: ok→5 KR+10 →6 NEW_TRADE; late→7 KR−5→8 hittite×10; refuse→2.
// pak i=6 city=Iunet junk → remap Abu (egyptian + route 4).
// i=7→i=8 INVASION no-op — JS hittite via event_request_cleared (late) + calendar i=8.
function mission16_ensure_meat_leaves() {
	if (mission.meat_leaves_wired) {
		return
	}
	mission.meat_leaves_wired = true
	mission16_ensure_shared_kr_leaves()
	var kr_ok = mission16_make_leaf(1005, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 18)
	mission16_make_leaf(1006, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 16, 8,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Abu")
	mission16_make_leaf(1007, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 18)
	kr_ok.set_completed_action_tag(1006)
}

// pak i=10 pottery: ok→11 KR+10; refuse→2; late→7.
function mission16_ensure_pottery_leaves() {
	if (mission.pottery_leaves_wired) {
		return
	}
	mission.pottery_leaves_wired = true
	mission16_ensure_shared_kr_leaves()
	mission16_ensure_meat_leaves()
	mission16_make_leaf(1011, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 2)
}

// pak i=14 limestone: ok→15 meat gift×15; refuse→18 KR−40→16 egypt×24; late→2.
// i=16 INVASION no-op — egypt raid via event_request_cleared (refuse).
function mission16_ensure_limestone_leaves() {
	if (mission.limestone_leaves_wired) {
		return
	}
	mission.limestone_leaves_wired = true
	mission16_ensure_shared_kr_leaves()
	mission16_make_leaf(1015, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_MEAT, 15, 2)
	mission16_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 40, 2)
}

[es=event_mission_start, mission=mission16]
function mission16_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HITTITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_TEMPLE_BAST)
	mission_show_start_message(mission, "message_mission_dendera")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_4_HITTITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	mission16_ensure_shared_kr_leaves()
	mission16_ensure_fish_leaves()
	mission16_ensure_meat_leaves()
	mission16_ensure_pottery_leaves()
	mission16_ensure_limestone_leaves()
}

// pak i=0: fish×4 / 12mo once y1m0. ok→NEW_TRADE Men-nefer; refuse/late→KR−10.
[es=event_advance_month, mission=mission16]
function mission16_event_i0_fish(ev) {
	if (mission.event0_fish_done) {
		return
	}
	if (ev.years_since_start < 1) {
		return
	}
	mission.event0_fish_done = true
	mission16_ensure_shared_kr_leaves()
	mission16_ensure_fish_leaves()
	log_info("akhenaten: mission 16 iunet fish×4", {ev:ev})
	mission16_fire_request(2000, RESOURCE_FISH, 4, 12, 1001, 1002, 1002, 3, 1)
}

// pak i=4: meat×2 / 12mo once y3m2. ok→KR+10; refuse→KR−10; late→KR−5→hittite×10.
[es=event_advance_month, mission=mission16]
function mission16_event_i4_meat(ev) {
	if (mission.event4_meat_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 2)) {
		return
	}
	mission.event4_meat_done = true
	mission16_ensure_meat_leaves()
	log_info("akhenaten: mission 16 iunet meat×2", {ev:ev})
	mission16_fire_request(2004, RESOURCE_MEAT, 2, 12, 1005, 1002, 1007, 0, 0)
}

// pak i=8: Hittite×10 once y4m0 (also meat/pottery late chain target via i=7).
[es=event_advance_month, mission=mission16]
function mission16_event_i8_hittite(ev) {
	if (mission.event8_hittite_done) {
		return
	}
	if (ev.years_since_start < 4) {
		return
	}
	mission.event8_hittite_done = true
	log_info("akhenaten: mission 16 iunet hittite×10", {ev:ev})
	mission16_hittite_raid(0, 10, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=9: clay flood once y4m1 amount=7 → 7% of clay pits.
[es=event_advance_month, mission=mission16]
function mission16_event_i9_clay_flood(ev) {
	if (mission.event9_clay_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 1)) {
		return
	}
	mission.event9_clay_done = true
	var total = city.count_total_buildings(BUILDING_CLAY_PIT)
	var n = Math.floor((total * 7 + 99) / 100)
	log_info("akhenaten: mission 16 iunet clay flood n=" + n + " of " + total, {ev:ev})
	for (var i = 0; i < n; i++) {
		city.create_chain_event({
			tag_id: 2009 + i,
			type: EVENT_TYPE_CLAY_PIT_FLOOD,
			amount: 7,
			trigger: EVENT_TRIGGER_ONCE
		}).execute()
	}
}

// pak i=10: pottery×15 / 12mo once y5m2.
[es=event_advance_month, mission=mission16]
function mission16_event_i10_pottery(ev) {
	if (mission.event10_pottery_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 2)) {
		return
	}
	mission.event10_pottery_done = true
	mission16_ensure_pottery_leaves()
	log_info("akhenaten: mission 16 iunet pottery×15", {ev:ev})
	mission16_fire_request(2010, RESOURCE_POTTERY, 15, 12, 1011, 1002, 1007, 0, 0)
}

// pak i=12: Hittite×20 once y5m10.
[es=event_advance_month, mission=mission16]
function mission16_event_i12_hittite(ev) {
	if (mission.event12_hittite_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 10)) {
		return
	}
	mission.event12_hittite_done = true
	log_info("akhenaten: mission 16 iunet hittite×20", {ev:ev})
	mission16_hittite_raid(1, 20, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=13: Hittite×32 once y8m0.
[es=event_advance_month, mission=mission16]
function mission16_event_i13_hittite(ev) {
	if (mission.event13_hittite_done) {
		return
	}
	if (ev.years_since_start < 8) {
		return
	}
	mission.event13_hittite_done = true
	log_info("akhenaten: mission 16 iunet hittite×32", {ev:ev})
	mission16_hittite_raid(2, 32, EVENT_ATTACK_TARGET_FOOD)
}

// pak i=14: limestone×15 / 12mo once y10m5. ok→meat gift; refuse→KR−40→egypt×24; late→KR−10.
[es=event_advance_month, mission=mission16]
function mission16_event_i14_limestone(ev) {
	if (mission.event14_limestone_done) {
		return
	}
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 5)) {
		return
	}
	mission.event14_limestone_done = true
	mission16_ensure_limestone_leaves()
	log_info("akhenaten: mission 16 iunet limestone×15", {ev:ev})
	mission16_fire_request(2014, RESOURCE_LIMESTONE, 15, 12, 1015, 1018, 1002, 4, 1)
}

// Factual request close — invasions from JS (no KR-snap).
// Leaf KR still via wired on_* tags in C++ storage path.
[es=event_request_cleared, mission=mission16]
function mission16_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	// pak i=16 egypt×24 after limestone refuse (tag 2014 → KR−40 leaf 1018).
	if (ev.tag_id == 2014 && outcome == "refuse" && !mission.limestone_egypt_done) {
		mission.limestone_egypt_done = true
		log_info("akhenaten: mission 16 iunet egypt×24 after limestone refuse", {ev:ev})
		mission16_egypt_raid(10, 24, EVENT_ATTACK_TARGET_FOOD)
		return
	}
	// pak i=7→i=8 hittite×10 after meat (2004) or pottery (2010) late; share calendar once-flag.
	if ((ev.tag_id == 2004 || ev.tag_id == 2010) && outcome == "late" && !mission.event8_hittite_done) {
		mission.event8_hittite_done = true
		log_info("akhenaten: mission 16 iunet hittite×10 after request late tag=" + ev.tag_id, {ev:ev})
		mission16_hittite_raid(0, 10, EVENT_ATTACK_TARGET_RANDOM)
	}
}

// pak i=17: Hittite×48 once y16m10. ok→11 KR+10; refuse→2 KR−10 (shared leaves).
[es=event_advance_month, mission=mission16]
function mission16_event_i17_hittite(ev) {
	if (mission.event17_hittite_done) {
		return
	}
	if (ev.years_since_start < 16 || (ev.years_since_start == 16 && ev.month < 10)) {
		return
	}
	mission.event17_hittite_done = true
	mission16_ensure_shared_kr_leaves()
	mission16_ensure_pottery_leaves()
	log_info("akhenaten: mission 16 iunet hittite×48", {ev:ev})
	mission16_hittite_raid(3, 48, EVENT_ATTACK_TARGET_FOOD, 1011, 1002)
}

// pak i=19→20→21→22: favour 15→45→30→30.
[es=event_advance_month, mission=mission16]
function mission16_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, [15, 45, 30, 30])
}
