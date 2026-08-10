log_info("akhenaten: mission 29 sawu started")

mission29 { // Sawu (Mersa Gawasis) — Shores of the Red Sea; briefing key = mersa_gawasis
	map_file : "data/maps/m_029_sawu.map"

	// Map points from data/maps/m_029_sawu.map.
	herd_points_predator [ [64, 86], [126, 112] ]
	fishing_points [ [82, 15], [151, 80], [25, 97] ]

	start_message : "message_mission_mersa_gawasis"
	selection_title : "Sawu"
	player_rank : 10

	// Choice pair with Iken; next is Heh (30) / Bubastis (31).
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 61]
	choice [
		{
			name : "Heh"
			id : 30
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 62]
			pos [620, 420]
		}
		{
			name : "Bubastis"
			id : 31
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 63]
			pos [640, 480]
		}
	]

	// pak Normal funds=8000 loan=3000 debt_interest=20 -> int_dcy around Normal.
	initial_funds [16000, 10600, 8000, 5400, 4200]
	rescue_loans [6000, 4000, 3000, 2000, 1500]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/229_mission.mp3"
		victory : "Voice/Mission/229_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_GRANITE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_COPPER_MINE,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_MAUSOLEUM, BUILDING_SMALL_MUDBRICK_PYRAMID,
	]

	// Monuments: Mausoleum (W=5) + Small Mudbrick (W=4) → trunc(2.25·9+4.5)=24 ≥ goal 20.
	// pak goal 21 = soft weight calib (same pattern as Heh pak 15 → goal 11).
	// pak housing count enabled with goal 0 (no-op) -> only housing_level is kept.
	win_criteria {
		population    {enabled : true, goal : 8000 }
		culture       {enabled : true, goal : 65 }
		prosperity    {enabled : true, goal : 65 }
		monuments     {enabled : true, goal : 20 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 17 }
	}

	entry_point [44, 128]
	exit_point [98, 155]
	river_entry_point [103, 19]
	river_exit_point [99, 15]
	disembark_points [ [126, 54], [95, 50], [43, 85] ]
	invasion_points_land [ [13, 100] ]
	// pak inv_sea [74,16] (water). Packed loc2=sea[0] → via_sea (E3c).
	invasion_points_sea [ [74, 16] ]

	// pak burial_provisions (scenario 29 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 12 }
		{ resource: RESOURCE_POTTERY, required: 4 }
		{ resource: RESOURCE_LINEN, required: 16 }
		{ resource: RESOURCE_PAPYRUS, required: 16 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Sawu"
			idx : 13
			pos : [907, 834]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_GRANITE, RESOURCE_COPPER ]
		}

		{
			name : "Dakhla Oasis"
			idx : 2
			pos : [349, 1037]
			route : 9
			is_open : false
			cost_to_open : 725
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_TIMBER ]
			buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 4000 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Itjtawy"
			idx : 4
			pos : [586, 555]
			route : 1
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_STRAW, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 9
			pos : [545, 487]
			route : 10
			is_open : false
			cost_to_open : 700
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_REEDS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 4000 }
			]
		}

		{
			name : "Menat Khufu"
			idx : 10
			pos : [578, 720]
			route : 6
			is_open : false
			cost_to_open : 430
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Pwenet"
			idx : 12
			pos : [1133, 1325]
			route : 4
			is_open : false
			cost_to_open : 660
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Waset"
			idx : 14
			pos : [811, 968]
			route : 8
			is_open : false
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Dunqul Oasis"
			idx : 32
			pos : [784, 1186]
			route : 14
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}

		{
			// Display egyptian; unlocked by pottery i=13 NEW_TRADE (loc=7). Pak sells/buys empty.
			name : "Buhen"
			idx : 0
			pos : [766, 1345]
			route : 7
			cost_to_open : 900
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Display foreign; unlocked by henna i=19 NEW_TRADE (loc=5). Pak sells/buys empty.
			name : "Kerma"
			idx : 7
			pos : [732, 1491]
			route : 5
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Iken"
			idx : 3
			pos : [735, 1380]
			route : 3
			cost_to_open : 1000
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Jericho"
			idx : 5
			pos : [896, 233]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kebet"
			idx : 6
			pos : [829, 900]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kharga Oasis"
			idx : 8
			pos : [644, 1135]
			route : 0
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
				[590, 577], [636, 588], [728, 610], [737, 619], [748, 628], [771, 647],
				[789, 665], [801, 677], [811, 686], [822, 696], [835, 702], [839, 712],
				[843, 725], [852, 736], [876, 767], [885, 776], [905, 797], [910, 816],
				[893, 835], [898, 857], [930, 861]
			]
		}
		{
			route : 3
			type : 1
			points [
				[754, 1394], [776, 1400], [784, 1397], [789, 1382], [809, 1340], [810, 1339],
				[826, 1317], [849, 1306], [865, 1316], [878, 1302], [905, 1233], [894, 1213],
				[889, 1209], [894, 1196], [891, 1192], [895, 1179], [888, 1167], [886, 1136],
				[879, 1127], [877, 1107], [883, 1099], [875, 1086], [879, 1071], [874, 1056],
				[866, 1051], [864, 1035], [849, 1021], [831, 1011], [823, 998], [817, 966],
				[817, 956], [830, 941], [813, 906], [816, 888], [801, 856], [800, 837],
				[862, 833], [890, 843], [897, 843], [924, 852]
			]
		}
		{
			route : 4
			type : 2
			points [
				[1145, 1341], [1171, 1328], [1167, 1311], [1165, 1290], [1160, 1283], [1157, 1263],
				[1161, 1253], [1157, 1248], [1144, 1242], [1115, 1209], [1104, 1198], [1081, 1121],
				[1091, 1083], [1084, 1071], [1072, 1059], [1058, 1037], [1059, 1017], [1045, 985],
				[1036, 949], [1020, 919], [1007, 906], [993, 899], [974, 876], [965, 861],
				[936, 862]
			]
		}
		{
			route : 5
			type : 2
			points [
				[734, 1497], [728, 1483], [709, 1481], [694, 1464], [719, 1457], [720, 1447],
				[726, 1444], [730, 1439], [762, 1414], [775, 1400], [783, 1396], [793, 1369],
				[809, 1339], [824, 1318], [846, 1304], [868, 1321], [894, 1261], [907, 1232],
				[897, 1214], [887, 1208], [890, 1200], [895, 1194], [892, 1179], [882, 1160],
				[886, 1135], [876, 1111], [883, 1099], [874, 1090], [878, 1073], [871, 1056],
				[862, 1047], [862, 1033], [848, 1019], [829, 1009], [817, 968], [817, 957],
				[828, 943], [817, 910], [813, 907], [815, 887], [811, 872], [801, 854],
				[798, 838], [862, 831], [877, 840], [904, 843], [935, 850]
			]
		}
		{
			route : 6
			type : 1
			points [
				[606, 743], [623, 747], [644, 757], [658, 763], [681, 781], [698, 794],
				[702, 806], [710, 819], [729, 824], [738, 829], [747, 833], [756, 833],
				[767, 834], [794, 837], [796, 837], [809, 834], [813, 833], [833, 833],
				[840, 834], [850, 834], [859, 838], [865, 843], [872, 846], [884, 848],
				[892, 849], [914, 857], [925, 858], [926, 858]
			]
		}
		{
			route : 7
			type : 2
			points [
				[796, 1354], [806, 1343], [812, 1336], [816, 1330], [833, 1314], [847, 1304],
				[862, 1319], [874, 1307], [882, 1294], [891, 1262], [900, 1250], [901, 1242],
				[907, 1228], [900, 1216], [889, 1210], [888, 1202], [898, 1196], [890, 1191],
				[896, 1179], [881, 1160], [886, 1134], [878, 1107], [884, 1100], [874, 1088],
				[879, 1070], [866, 1051], [864, 1049], [848, 1019], [832, 1010], [824, 993],
				[817, 962], [830, 943], [823, 923], [812, 907], [817, 887], [802, 858],
				[797, 834], [856, 833], [879, 839], [898, 842], [933, 851]
			]
		}
		{
			route : 8
			type : 1
			points [
				[837, 980], [845, 958], [849, 945], [849, 912], [876, 898], [893, 892],
				[922, 880], [929, 863]
			]
		}
		{
			route : 9
			type : 1
			points [
				[367, 1055], [409, 1049], [416, 1056], [451, 1068], [484, 1076], [510, 1099],
				[542, 1117], [591, 1131], [640, 1144], [659, 1146], [684, 1123], [692, 1080],
				[689, 1054], [691, 1035], [703, 1027], [717, 1022], [728, 1019], [736, 1012],
				[763, 1004], [779, 998], [804, 991], [812, 989], [837, 980], [848, 952],
				[848, 928], [848, 914], [854, 907], [920, 882], [921, 877], [924, 871],
			]
		}
		{
			route : 10
			type : 2
			points [
				[571, 503], [591, 510], [617, 511], [637, 507], [654, 511], [672, 522],
				[692, 521], [698, 542], [712, 555], [730, 574], [732, 596], [744, 611],
				[762, 624], [785, 640], [814, 669], [827, 686], [850, 698], [865, 718],
				[868, 743], [885, 762], [907, 785], [918, 799], [925, 817], [932, 831],
				[937, 855]
			]
		}
		{
			route : 14
			type : 1
			points [
				[805, 1201], [811, 1175], [818, 1147], [807, 1133], [809, 1127], [816, 1111],
				[816, 1098], [814, 1089], [813, 1056], [816, 1049], [817, 1033], [810, 1017],
				[808, 983], [810, 983], [838, 981], [843, 961], [849, 943], [849, 920],
				[857, 907], [894, 886], [900, 887], [929, 863]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [539, 424], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [421, 650], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [492, 517], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [615, 710], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [633, 706], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [593, 455], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [510, 485], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [595, 519], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [504, 554], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [566, 590], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [623, 733], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [519, 535], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [574, 503], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [552, 558], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [815, 890], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [685, 885], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [841, 1086], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [846, 965], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [843, 980], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [385, 1036], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [778, 1325], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [816, 1191], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [880, 900], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [862, 900], image : "pharaoh_general/empire_bits_00121" }
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
		{ name : "#upper_egypt", pos : [680, 997] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]
	vars {
		shared_leaves_wired : false
		kerma_chain_leaves_wired : false

		event0_weapons_done : false
		event4_gold_mine_done : false
		event6_linen_done : false
		event12_pottery_done : false
		event15_clay_pit_done : false

		event16_troops_last_year : -1
		event18_henna_last_year : -1
		event21_beer_last_year : -1
		event22_beer_last_year : -1

		troops_recurring_was_busy : false
		troops_recurring_idle_since_abs : -1
		henna_recurring_was_busy : false
		henna_recurring_idle_since_abs : -1
		beer_recurring_was_busy : false
		beer_recurring_idle_since_abs : -1

		event23_invasion_done : false
		event24_invasion_done : false
		event25_invasion_done : false
		event26_invasion_done : false
		event27_invasion_last_abs : -1
		event28_invasion_last_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_enemies_seen : false

		start_message_shown : false
	}
}

function mission29_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission29_make_chain_request(tag, resource, amount, months, subtype, city_name) {
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
	request.set_sender_faction(0)
	return request
}

function mission29_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission29_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, city_name, defeat_tag) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	if (ok_tag) {
		request.set_completed_action_tag(ok_tag)
	}
	if (refuse_tag) {
		request.set_refusal_action_tag(refuse_tag)
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

// Shared KR / NEW_TRADE leaves: i=1 KR+10, i=2 KR−1, i=7 KR+5, i=8 KR−15,
// i=13 NEW_TRADE Buhen (loc=7), i=19 NEW_TRADE Kerma (loc=5).
function mission29_ensure_shared_leaves() {
	if (mission.shared_leaves_wired) {
		return
	}
	mission.shared_leaves_wired = true
	mission29_make_leaf(1001, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 2)
	mission29_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 1, 2)
	mission29_make_leaf(1007, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission29_make_leaf(1008, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2)
	mission29_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Buhen")
	mission29_make_leaf(1019, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
}

// Kerma-fell chain, reached from the refuse of i=0 weapons and i=16 troops:
//   i=3 Kerma FELL -> i=5 KR−18 -> i=9 weapons×17 (Iken)
//     ok    -> i=10 Iken CONQUERED -> i=1 KR+10
//     refuse-> i=8 KR−15
//     late  -> i=11 KR+5 -> i=10
// Leaves are created before any set_*_action_tag so every tag target already exists.
function mission29_ensure_kerma_chain_leaves() {
	if (mission.kerma_chain_leaves_wired) {
		return
	}
	mission.kerma_chain_leaves_wired = true

	var conquered = mission29_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Iken")
	var kr_late = mission29_make_leaf(1011, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	var weapons = mission29_make_chain_request(1009, RESOURCE_WEAPONS, 17, 12, undefined, "Iken")
	var kr_down = mission29_make_leaf(1005, EVENT_TYPE_REPUTATION_DECREASE, undefined, 18, 2)
	var fell = mission29_make_leaf(1003, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 10, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Kerma")

	conquered.set_completed_action_tag(1001)
	kr_late.set_completed_action_tag(1010)
	weapons.set_completed_action_tag(1010)
	weapons.set_refusal_action_tag(1008)
	weapons.set_too_late_action_tag(1011)
	kr_down.set_completed_action_tag(1009)
	fell.set_completed_action_tag(1005)
}

function mission29_ensure_all_leaves() {
	mission29_ensure_shared_leaves()
	mission29_ensure_kerma_chain_leaves()
}

// pak location_fields = 1-based packed (land first, then sea).
// land[0]=[13,100] → loc1; sea[0]=[74,16] → loc2.
// Libyan OOB navy (3/5/8/9) → via_sea sea0. Egyptian favour OOB → map entry.
function mission29_apply_invasion_loc(opts, loc, prefer_sea) {
	if (loc == 1) {
		opts.tilex = 13
		opts.tiley = 100
		return false
	}
	if (loc == 2) {
		opts.via_sea = 1
		opts.sea_point = 0
		opts.tilex = 74
		opts.tiley = 16
		return true
	}
	if (prefer_sea) {
		opts.via_sea = 1
		opts.sea_point = 0
		opts.tilex = 74
		opts.tiley = 16
		return true
	}
	opts.tilex = -1
	opts.tiley = -1
	return false
}

// pak beduins(4) and the scenario enemy(1) both resolve to ENEMY_7_LIBIAN in this scenario.
function mission29_libyan_raid(invasion_id, size, loc, attack_target) {
	if (loc === undefined) {
		loc = 9
	}
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	}
	var via_sea = mission29_apply_invasion_loc(opts, loc, true)
	log_info("akhenaten: mission 29 libyan raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " sea=" + via_sea + " tile=" + opts.tilex + "," + opts.tiley)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	return city.start_foreign_army_invasion(opts)
}

function mission29_favour_wave(size, invasion_id, loc, attack_target) {
	if (loc === undefined) {
		loc = 1
	}
	var opts = {
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		invasion_id: invasion_id,
		want_destroy_buildings: 0,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	}
	var via_sea = mission29_apply_invasion_loc(opts, loc, false)
	log_info("akhenaten: mission 29 favour wave size=" + size + " kr=" + city.rating_kingdom
		+ " id=" + invasion_id + " loc=" + loc + " sea=" + via_sea
		+ " tile=" + opts.tilex + "," + opts.tiley)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	return city.start_foreign_army_invasion(opts)
}

[es=event_mission_start, mission=mission29]
function mission29_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_mersa_gawasis")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_7_LIBIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission29_ensure_all_leaves()
}

[es=event_advance_month, mission=mission29]
function mission29_requests_and_events(ev) {
	mission29_ensure_all_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_TROOPS, "troops_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_HENNA, "henna_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_BEER, "beer_recurring", abs)

	// pak i=0: weapons×2 /9mo y1m1 Kebet -> ok 1001 KR+10; refuse 1003 Kerma-fell; late 1002.
	if (!mission.event0_weapons_done && ev.years_since_start == 1 && ev.month == 1) {
		mission.event0_weapons_done = true
		log_info("akhenaten: mission 29 weapons×2 (i=0)")
		mission29_fire_request(2000, RESOURCE_WEAPONS, 2, 9, 1001, 1003, 1002, 0, "Kebet")
	}
	// pak i=12: pottery×22 /12mo y2m2 Iken -> ok/late 1013 NEW_TRADE Buhen; refuse 1008.
	if (!mission.event12_pottery_done && ev.years_since_start == 2 && ev.month == 2) {
		mission.event12_pottery_done = true
		log_info("akhenaten: mission 29 pottery×22 (i=12)")
		mission29_fire_request(2012, RESOURCE_POTTERY, 22, 12, 1013, 1008, 1013, 0, "Iken")
	}
	// pak i=4: gold mine collapse y2m8.
	if (!mission.event4_gold_mine_done && ev.years_since_start == 2 && ev.month == 8) {
		mission.event4_gold_mine_done = true
		log_info("akhenaten: mission 29 gold mine collapse (i=4)")
		mission29_fire_simple_event(2004, EVENT_TYPE_GOLD_MINE_COLLAPSE, undefined, 11)
	}
	// pak i=15: clay pit flood y3m3.
	if (!mission.event15_clay_pit_done && ev.years_since_start == 3 && ev.month == 3) {
		mission.event15_clay_pit_done = true
		log_info("akhenaten: mission 29 clay pit flood (i=15)")
		mission29_fire_simple_event(2015, EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 7)
	}
	// pak i=6: linen×11 /10mo y3m5 Itjtawy -> ok 1007 KR+5; refuse 1008 KR−15; late 1002.
	if (!mission.event6_linen_done && ev.years_since_start == 3 && ev.month == 5) {
		mission.event6_linen_done = true
		log_info("akhenaten: mission 29 linen×11 (i=6)")
		mission29_fire_request(2006, RESOURCE_LINEN, 11, 10, 1007, 1008, 1002, 0, "Itjtawy")
	}

	// pak i=16: troops×16 /18mo recurring y4m0+ Iken subtype=1 (city asks for troops).
	if (ev.years_since_start >= 4 && ev.month == 0
			&& mission.event16_troops_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_TROOPS, "troops_recurring", abs)) {
		mission.event16_troops_last_year = ev.years_since_start
		log_info("akhenaten: mission 29 troops×16 recurring (i=16)")
		mission29_fire_request(3000 + 16 * 100 + ev.years_since_start,
			RESOURCE_TROOPS, 16, 18, 1001, 1003, 1002, 1, "Iken", 1008)
	}
	// pak i=18: henna×24 /18mo recurring y7m9+ Iken -> ok 1019 NEW_TRADE Kerma.
	if (ev.years_since_start >= 7 && ev.month == 9
			&& mission.event18_henna_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_HENNA, "henna_recurring", abs)) {
		mission.event18_henna_last_year = ev.years_since_start
		log_info("akhenaten: mission 29 henna×24 recurring (i=18)")
		mission29_fire_request(3000 + 18 * 100 + ev.years_since_start,
			RESOURCE_HENNA, 24, 18, 1019, 1008, 1008, 2, "Iken", 1008)
	}
	// pak i=21: beer×21 /18mo recurring y9m0+ Jericho subtype=3 (festival).
	if (ev.years_since_start >= 9 && ev.month == 0
			&& mission.event21_beer_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_BEER, "beer_recurring", abs)) {
		mission.event21_beer_last_year = ev.years_since_start
		log_info("akhenaten: mission 29 beer×21 recurring (i=21)")
		mission29_fire_request(3000 + 21 * 100 + ev.years_since_start,
			RESOURCE_BEER, 21, 18, 1007, 1008, 1002, 3, "Jericho")
	}
	// pak i=22: beer×15 /12mo recurring y11m4+ Jericho (shares the beer idle gate with i=21).
	if (ev.years_since_start >= 11 && ev.month == 4
			&& mission.event22_beer_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_BEER, "beer_recurring", abs)) {
		mission.event22_beer_last_year = ev.years_since_start
		log_info("akhenaten: mission 29 beer×15 recurring (i=22)")
		mission29_fire_request(3000 + 22 * 100 + ev.years_since_start,
			RESOURCE_BEER, 15, 12, 1007, 1008, 1002, 0, "Jericho")
	}
}

[es=event_advance_month, mission=mission29]
function mission29_timed_invasions(ev) {
	// pak i=23: beduin×9 y4m10 loc=3 attack=4.
	if (!mission.event23_invasion_done && ev.years_since_start == 4 && ev.month == 10) {
		mission.event23_invasion_done = true
		log_info("akhenaten: mission 29 beduin×9 (i=23)")
		mission29_libyan_raid(23, 9, 3, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	// pak i=24: enemy×5 y12m0 loc=9 attack=3 (troops).
	if (!mission.event24_invasion_done && ev.years_since_start == 12 && ev.month == 0) {
		mission.event24_invasion_done = true
		log_info("akhenaten: mission 29 enemy×5 (i=24)")
		mission29_libyan_raid(24, 5, 9, EVENT_ATTACK_TARGET_TROOPS)
		return
	}
	// pak i=25: beduin×8 y20m0 loc=1 attack=4.
	if (!mission.event25_invasion_done && ev.years_since_start == 20 && ev.month == 0) {
		mission.event25_invasion_done = true
		log_info("akhenaten: mission 29 beduin×8 (i=25)")
		mission29_libyan_raid(25, 8, 1, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	// pak i=26: enemy×8 y23m11 loc=9 attack=0 (food).
	if (!mission.event26_invasion_done && ev.years_since_start == 23 && ev.month == 11) {
		mission.event26_invasion_done = true
		log_info("akhenaten: mission 29 enemy×8 (i=26)")
		mission29_libyan_raid(26, 8, 9, EVENT_ATTACK_TARGET_FOOD)
		return
	}
	// pak i=27: beduin×9 recurring from y30m0; months=8 → every 8 calendar months.
	// Idle-gate while enemies remain (Selima pattern).
	var abs = ev.years_since_start * 12 + ev.month
	if (abs >= 30 * 12 + 0
			&& (abs - (30 * 12 + 0)) % 8 == 0
			&& mission.event27_invasion_last_abs != abs) {
		if (city.num_enemy_formations > 0) {
			return
		}
		mission.event27_invasion_last_abs = abs
		log_info("akhenaten: mission 29 beduin×9 recurring (i=27) abs=" + abs)
		mission29_libyan_raid(27, 9, 1, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	// pak i=28: enemy×9 recurring from y45m4; months=12 → yearly at month 4.
	if (abs >= 45 * 12 + 4
			&& (abs - (45 * 12 + 4)) % 12 == 0
			&& mission.event28_invasion_last_abs != abs) {
		if (city.num_enemy_formations > 0) {
			return
		}
		mission.event28_invasion_last_abs = abs
		log_info("akhenaten: mission 29 enemy×9 recurring (i=28) abs=" + abs)
		mission29_libyan_raid(28, 9, 9, EVENT_ATTACK_TARGET_TROOPS)
	}
}

// pak i=32 -> i=33 -> i=34: by_favour egypt×40 loc=5, then ×40 loc=3, then ×40 loc=8.
[es=event_advance_month, mission=mission29]
function mission29_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave3_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_enemies_seen) {
			return
		}
		mission.pharaoh_favour_enemies_seen = false
		if (!mission.pharaoh_favour_wave2_done) {
			mission.pharaoh_favour_wave2_done = true
			mission29_favour_wave(40, 33, 3, EVENT_ATTACK_TARGET_RANDOM)
			return
		}
		mission.pharaoh_favour_wave3_done = true
		mission29_favour_wave(40, 34, 8, EVENT_ATTACK_TARGET_RANDOM)
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
	log_info("akhenaten: mission 29 favour egypt×40 (i=32)")
	mission29_favour_wave(40, 32, 5, EVENT_ATTACK_TARGET_RANDOM)
}
