log_info("akhenaten: mission 21 dunqul started")

// Empire / events aligned with original campaign scenario 21 (2026-07-26 dump).
// Empire id=0. Enemy ENEMY_4_HITTITE (scenario); beduin raids (Libyan sprites); favour Pharaoh×66.
// Gods: Ra, Ptah, Seth. Funds Normal 6000 / loan 1500 / debt 15. Rank 8.
// Win: pop 3500 / culture 20 / prosperity 20 / monuments TEMP 9 (pak 6 small obelisk) / kingdom 80 / housing 14.
// Burial empty. Climate desert.
// Trade: Buhen(5) Byblos(4) Henen-nesw(10) Kerma(8) Men-nefer(7) On(2) Selima(6).
// Display: Djedu(1) Iunet(3) Nekhen(9) Saqqara(11) Dakhla(14). Kharga stub route 13.
// Triage: SKIP empty map_obj idx=10; SKIP orphan i=6 LOST_TRADE Djedu (chain_only, no inbound);
// omit river/disembark/inv points (pak 0).
// Events: gamemeat×12 + granite×12 KR via request_cleared (not shared ONLY_VIA — B14);
// siege→weapons×60; beduin/enemy raids (unique wipe KR tags); NEW_TRADE; favour×66.
// SKIP empty NEW_TRADE Djedu/Iunet (display, no sells/buys).
//
// Tag_id scheme:
//   1000 + i               chain-only leaves / chain requests (once structures)
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots
//   4100 + year / 4200+y   invasion wipe KR (unique ONCE leaves)
//   50000 + seq            fire_kr unique ONCE

mission21 { // Dunqul Oasis — The Kushite Threat
	map_file : "data/maps/m_021_dunqul.map"

	// Map points from data/maps/m_021_dunqul.map.
	herd_points_predator [ [104, 128], [158, 80], [52, 45], [80, 76] ]
	herd_points_prey [ [101, 106], [65, 80], [142, 98] ]

	start_message : "message_mission_dunqul"
	selection_title : "Dunqul"
	player_rank : 8

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 49]
	choice [
		{
			name : "Thinis"
			id : 23
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 50]
			pos [620, 420]
		}
		{
			name : "Waset"
			id : 24
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 51]
			pos [640, 480]
		}
	]

	initial_funds [12000, 8000, 6000, 4000, 3000]
	rescue_loans [3000, 2000, 1500, 1000, 800]
	debt_interest [5, 10, 15, 20, 25]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/221_mission.mp3"
		victory : "Voice/Mission/221_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_CLAY_PIT, BUILDING_SANDSTONE_QUARRY, BUILDING_GRANITE_QUARRY,
		BUILDING_SMALL_OBELISK,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,

		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,
	]

	// Monuments TEMP 9 (pak raw 6; one small obelisk → formula 9, same as Buhen).
	win_criteria {
		population    {enabled : true, goal : 3500 }
		culture       {enabled : true, goal : 20 }
		prosperity    {enabled : true, goal : 20 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 80 }
		housing_level {enabled : true, goal : 14 }
	}

	entry_point [69, 16]
	exit_point [132, 121]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
			{
				name : "Dunqul Oasis"
				idx : 4
				pos : [795, 1191]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
				buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			}
	
			{
				name : "Buhen"
				idx : 1
				pos : [766, 1345]
				route : 5
				is_open : false
				cost_to_open : 200
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
					{ resource: RESOURCE_GRANITE, limit: 2500 }
					{ resource: RESOURCE_COPPER, limit: 2500 }
				]
			}
	
			{
				name : "Byblos"
				idx : 2
				pos : [891, 68]
				route : 4
				is_open : false
				cost_to_open : 1500
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_TIMBER, RESOURCE_COPPER ]
				buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
				route_limits [
					{ resource: RESOURCE_GEMS, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_COPPER, limit: 2500 }
				]
			}
	
			{
				name : "Henen-nesw"
				idx : 5
				pos : [534, 626]
				route : 10
				is_open : false
				cost_to_open : 805
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BEER, RESOURCE_FLAX ]
				route_limits [
					{ resource: RESOURCE_FIGS, limit: 2500 }
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_FLAX, limit: 2500 }
				]
			}
	
			{
				name : "Kerma"
				idx : 7
				pos : [732, 1491]
				route : 8
				is_open : false
				cost_to_open : 375
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS ]
				buys [ RESOURCE_LINEN ]
				route_limits [
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				]
			}
	
			{
				name : "Men-nefer"
				idx : 9
				pos : [541, 477]
				route : 7
				is_open : false
				cost_to_open : 870
				is_sea_trade : false
				type : EMPIRE_CITY_PHARAOH_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
				buys [ RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
				route_limits [
					{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
					{ resource: RESOURCE_BARLEY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				]
			}
	
			{
				name : "On"
				idx : 12
				pos : [572, 454]
				route : 2
				is_open : false
				cost_to_open : 960
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
				buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_REEDS, limit: 2500 }
					{ resource: RESOURCE_LIMESTONE, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_GEMS, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_GRANITE, limit: 2500 }
				]
			}
	
			{
				name : "Selima Oasis"
				idx : 14
				pos : [613, 1353]
				route : 6
				is_open : false
				cost_to_open : 375
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
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
				name : "Djedu"
				idx : 3
				pos : [535, 389]
				route : 1
				cost_to_open : 1070
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Iunet"
				idx : 6
				pos : [779, 881]
				route : 3
				cost_to_open : 370
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Nekhen"
				idx : 11
				pos : [797, 1011]
				route : 9
				cost_to_open : 260
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Saqqara"
				idx : 13
				pos : [523, 539]
				route : 11
				cost_to_open : 975
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Dakhla Oasis"
				idx : 46
				pos : [335, 1040]
				route : 14
				cost_to_open : 500
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
	
			{
				name : "Bahariya Oasis"
				idx : 0
				pos : [372, 654]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Kharga Oasis"
				idx : 8
				pos : [621, 1128]
				route : 13
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
					[551, 411], [544, 443], [544, 455], [557, 484], [565, 507], [541, 555],
					[515, 577], [496, 589], [509, 601], [525, 603], [550, 643], [547, 654],
					[551, 729], [553, 740], [553, 797], [545, 821], [544, 829], [542, 832],
					[538, 850], [542, 861], [557, 913], [557, 976], [564, 1007], [577, 1060],
					[621, 1100], [660, 1134], [698, 1149], [812, 1218]
				]
			}
			{
				route : 2
				type : 1
				points [
					[587, 474], [602, 502], [640, 539], [652, 558], [704, 666], [762, 724],
					[769, 749], [776, 762], [780, 784], [789, 810], [804, 851], [806, 863],
					[815, 876], [815, 910], [825, 926], [827, 946], [817, 961], [819, 972],
					[815, 989], [825, 1000], [834, 1014], [850, 1021], [863, 1036], [865, 1051],
					[877, 1064], [878, 1084], [882, 1100], [880, 1118], [886, 1136], [884, 1161],
					[893, 1178], [871, 1190], [858, 1199], [843, 1199], [814, 1210]
				]
			}
			{
				route : 3
				type : 1
				points [
					[800, 899], [794, 930], [795, 964], [799, 998], [815, 1034], [827, 1083],
					[832, 1112], [841, 1121], [842, 1133], [840, 1144], [815, 1209]
				]
			}
			{
				route : 4
				type : 1
				points [
					[906, 90], [890, 148], [915, 220], [921, 278], [923, 304], [890, 307],
					[859, 316], [789, 358], [768, 361], [697, 498], [681, 536], [692, 565],
					[732, 617], [829, 702], [851, 759], [854, 826], [821, 885], [818, 904],
					[803, 991], [820, 1005], [840, 1025], [856, 1041], [864, 1062], [871, 1090],
					[872, 1117], [871, 1143], [856, 1159], [836, 1167], [827, 1185], [817, 1210],
				]
			}
			{
				route : 5
				type : 1
				points [
					[781, 1358], [786, 1340], [782, 1334], [782, 1327], [784, 1321], [804, 1312],
					[809, 1306], [811, 1301], [814, 1295], [819, 1280], [817, 1257], [817, 1250],
					[819, 1244], [818, 1225]
				]
			}
			{
				route : 6
				type : 1
				points [
					[630, 1374], [663, 1369], [680, 1359], [690, 1351], [694, 1347], [698, 1343],
					[708, 1341], [709, 1339], [716, 1337], [724, 1330], [735, 1322], [749, 1314],
					[762, 1302], [770, 1295], [779, 1285], [782, 1278], [786, 1266], [792, 1251],
					[798, 1243], [801, 1239], [816, 1224]
				]
			}
			{
				route : 7
				type : 1
				points [
					[572, 519], [587, 544], [591, 569], [595, 589], [601, 595], [598, 613],
					[584, 632], [584, 646], [573, 667], [571, 682], [569, 713], [565, 718],
					[569, 730], [584, 741], [584, 758], [593, 774], [597, 789], [596, 795],
					[607, 863], [610, 956], [613, 983], [621, 1009], [624, 1026], [625, 1052],
					[624, 1073], [624, 1085], [629, 1099], [631, 1118], [635, 1152], [645, 1169],
					[660, 1186], [688, 1203], [715, 1214], [753, 1218], [766, 1220], [785, 1219],
					[810, 1211]
				]
			}
			{
				route : 8
				type : 1
				points [
					[741, 1506], [743, 1491], [750, 1480], [754, 1478], [763, 1456], [769, 1441],
					[782, 1421], [785, 1412], [787, 1404], [790, 1395], [792, 1388], [790, 1381],
					[788, 1374], [785, 1362], [784, 1336], [784, 1327], [784, 1323], [792, 1315],
					[801, 1310], [812, 1305], [817, 1291], [817, 1285], [819, 1274], [816, 1258],
					[817, 1245], [820, 1232], [819, 1226]
				]
			}
			{
				route : 9
				type : 1
				points [
					[816, 1033], [826, 1080], [836, 1115], [842, 1124], [841, 1140], [831, 1163],
					[814, 1213], [814, 1213]
				]
			}
			{
				route : 10
				type : 1
				points [
					[547, 650], [549, 695], [552, 731], [552, 798], [546, 821], [539, 848],
					[539, 851], [543, 859], [548, 879], [552, 900], [554, 907], [556, 917],
					[557, 942], [557, 962], [558, 978], [560, 994], [564, 1006], [570, 1031],
					[574, 1047], [580, 1061], [584, 1068], [614, 1094], [647, 1124], [661, 1133],
					[682, 1143], [698, 1148], [716, 1159], [736, 1172], [765, 1189], [799, 1215],
					[810, 1221]
				]
			}
			{
				route : 11
				type : 1
				points [
					[539, 557], [517, 576], [497, 589], [509, 602], [462, 622], [426, 642],
					[410, 674], [412, 698], [425, 761], [433, 802], [446, 867], [471, 941],
					[492, 980], [500, 992], [526, 1047], [560, 1072], [610, 1101], [663, 1142],
					[712, 1164], [818, 1212]
				]
			}
			{
				route : 14
				type : 1
				points [
					[371, 1067], [420, 1068], [476, 1062], [513, 1066], [549, 1078], [579, 1090],
					[598, 1108], [633, 1143], [677, 1157], [707, 1167], [742, 1184], [769, 1199],
					[810, 1217]
				]
			}
			{
				// Kharga display — no pak polyline; 2-pt stub.
				route : 13
				type : 1
				deviation : 40
				points [ [621, 1128], [795, 1191] ]
			}
		]
	
		hide_pak_objects : true
		empire_ornaments [
			{ pos : [513, 485], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [599, 439], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [538, 421], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [414, 643], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [470, 501], image : "pharaoh_general/empire_bits_00123" }
			{ pos : [611, 548], image : "pharaoh_general/empire_bits_00118" }
			{ pos : [498, 540], image : "pharaoh_general/empire_bits_00117" }
			{ pos : [560, 583], image : "pharaoh_general/empire_bits_00116" }
			{ pos : [497, 515], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [596, 531], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [719, 915], image : "pharaoh_general/empire_bits_00119" }
			{ pos : [828, 881], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [836, 1089], image : "pharaoh_general/empire_bits_00119" }
			{ pos : [786, 1322], image : "pharaoh_general/empire_bits_00122" }
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
		weapons_leaves_wired : false
		event7_siege_done : false
		event10_troops_done : false
		event11_beduin_done : false
		event20_trade_done : false
		event21_demand_done : false
		event0_gamemeat_last_year : -1
		event4_granite_last_year : -1
		event12_beduin_last_year : -1
		event14_enemy_last_year : -1
		event18_trade_last_year : -1
		kr_seq : 0
		gamemeat_recurring_was_busy : false
		gamemeat_recurring_idle_since_abs : -1
		granite_recurring_was_busy : false
		granite_recurring_idle_since_abs : -1
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission21_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission21_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission21_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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

// Multi-fire KR must NOT use shared ONLY_VIA leaves (B14 / Sumur pattern).
function mission21_fire_kr(delta) {
	var type = delta >= 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE
	var amount = delta >= 0 ? delta : -delta
	mission.kr_seq = (mission.kr_seq | 0) + 1
	mission21_fire_simple_event(50000 + mission.kr_seq, type, undefined, amount)
}

function mission21_apply_shared_request_outcome(outcome) {
	// pak i=0/i=4 share: ok→KR+5; refuse→KR−36; late→KR−5.
	if (outcome == "ok") {
		mission21_fire_kr(5)
	} else if (outcome == "refuse") {
		mission21_fire_kr(-36)
	} else {
		mission21_fire_kr(-5)
	}
}

function mission21_ensure_weapons_leaves() {
	// pak i=7 LOST_TRADE Henen-nesw → i=8 UNDER_SIEGE → i=5 weapons×60 → i=9 CITY_FELL Djedu.
	// SKIP orphan i=6 LOST_TRADE Djedu (chain_only → i=9, but no parent ok/refuse/late).
	// set_*_action_tag looks up slave by tag — create 1009 before wiring weapons.
	if (mission.weapons_leaves_wired) {
		return
	}
	mission.weapons_leaves_wired = true
	var siege = mission21_make_leaf(1008, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_CITY_UNDER_SIEGE, "Henen-nesw")
	mission21_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Djedu")
	var weapons = city.create_good_request({
		tag_id: 1005,
		resource: RESOURCE_WEAPONS,
		amount: 60,
		months_initial: 3,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	weapons.set_sender_faction(0)
	weapons.set_completed_action_tag(1009)
	weapons.set_refusal_action_tag(1009)
	weapons.set_too_late_action_tag(1009)
	siege.set_completed_action_tag(1005)
}

function mission21_beduin_raid(invasion_id, size, on_completed_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

function mission21_enemy_raid(invasion_id, size, on_completed_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_4_HITTITE,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

[es=event_mission_start, mission=mission21]
function mission21_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HITTITE)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_dunqul")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_4_HITTITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission21_ensure_weapons_leaves()
}

[es=event_advance_month, mission=mission21]
function mission21_requests_and_raids(ev) {
	mission21_ensure_weapons_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_GAMEMEAT, "gamemeat_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GRANITE, "granite_recurring", abs)

	if (!mission.event7_siege_done && ev.years_since_start == 1 && ev.month == 1) {
		mission.event7_siege_done = true
		log_info("akhenaten: mission 21 LOST_TRADE Henen-nesw → siege → weapons")
		var lost = city.create_chain_event({
			tag_id: 2007,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 12,
			subtype: EVENT_SUBTYPE_LOST_TRADE_ROUTE,
			city: "Henen-nesw",
			trigger: EVENT_TRIGGER_ONCE
		})
		lost.set_param("months_initial", 2)
		lost.set_completed_action_tag(1008)
		lost.execute()
	}

	if (!mission.event11_beduin_done && ev.years_since_start == 1 && ev.month == 0) {
		mission.event11_beduin_done = true
		log_info("akhenaten: mission 21 beduin×5")
		mission21_beduin_raid(11, 5)
	}

	if (!mission.event10_troops_done && ev.years_since_start == 3 && ev.month == 0) {
		mission.event10_troops_done = true
		// pak CITY_STATUS subtype=1 ≡ FOREIGN_CITY_CONQUERED (alias CITY_ASKS_FOR_TROOPS).
		log_info("akhenaten: mission 21 Iunet conquered status → NEW_TRADE Kerma")
		mission21_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
			EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
		var ask = city.create_chain_event({
			tag_id: 2010,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 7,
			subtype: EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED,
			city: "Iunet",
			trigger: EVENT_TRIGGER_ONCE
		})
		ask.set_param("months_initial", 2)
		ask.set_completed_action_tag(1013)
		ask.execute()
	}

	if (ev.years_since_start > 2 || (ev.years_since_start == 2 && ev.month >= 8)) {
		if (ev.month == 8 && mission.event0_gamemeat_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_GAMEMEAT, "gamemeat_recurring", abs)) {
			mission.event0_gamemeat_last_year = ev.years_since_start
			log_info("akhenaten: mission 21 gamemeat×12 recurring")
			// Outcomes via event_request_cleared (shared ONLY_VIA would burn — B14).
			mission21_fire_request(3000 + 0 * 100 + ev.years_since_start,
				RESOURCE_GAMEMEAT, 12, 7, 0, 0, 0, 5, 0)
		}
	}

	if (ev.years_since_start > 2 || (ev.years_since_start == 2 && ev.month >= 10)) {
		if (ev.month == 10 && mission.event4_granite_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_GRANITE, "granite_recurring", abs)) {
			mission.event4_granite_last_year = ev.years_since_start
			log_info("akhenaten: mission 21 granite×12 recurring")
			mission21_fire_request(3000 + 4 * 100 + ev.years_since_start,
				RESOURCE_GRANITE, 12, 12, 0, 0, 0, 4, 1)
		}
	}

	if (ev.years_since_start >= 3 && ev.month == 0
			&& mission.event12_beduin_last_year != ev.years_since_start) {
		mission.event12_beduin_last_year = ev.years_since_start
		var beduin_kr = 4100 + ev.years_since_start
		mission21_make_leaf(beduin_kr, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
		log_info("akhenaten: mission 21 beduin×12 recurring")
		mission21_beduin_raid(12, 12, beduin_kr)
	}

	if (ev.years_since_start > 4 || (ev.years_since_start == 4 && ev.month >= 4)) {
		if (ev.month == 4 && mission.event14_enemy_last_year != ev.years_since_start) {
			mission.event14_enemy_last_year = ev.years_since_start
			var enemy_kr = 4200 + ev.years_since_start
			mission21_make_leaf(enemy_kr, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2)
			log_info("akhenaten: mission 21 enemy×43 recurring")
			mission21_enemy_raid(14, 43, enemy_kr)
		}
	}

	// SKIP pak i=16/17 NEW_TRADE Iunet/Djedu — display cities with no sells/buys (empty unlock).
	if (!mission.event20_trade_done && ev.years_since_start == 1 && ev.month == 9) {
		mission.event20_trade_done = true
		mission21_fire_simple_event(2020, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, "Henen-nesw",
			EVENT_SUBTYPE_NEW_TRADE_ROUTE)
	}

	// pak i=18 NEW_TRADE Kerma recurring — fire once (already-open spam is useless).
	// Tag 2018 (once band) — NOT 3018 (collides with gamemeat 3000+year at y18).
	if (ev.years_since_start == 10 && ev.month == 11
			&& mission.event18_trade_last_year != ev.years_since_start) {
		mission.event18_trade_last_year = ev.years_since_start
		mission21_fire_simple_event(2018, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, "Kerma",
			EVENT_SUBTYPE_NEW_TRADE_ROUTE)
	}

	if (!mission.event21_demand_done && ev.years_since_start == 3 && ev.month == 9) {
		mission.event21_demand_done = true
		mission21_fire_simple_event(2021, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 5)
	}
}

[es=event_request_cleared, mission=mission21]
function mission21_on_request_cleared(ev) {
	var tag = ev.tag_id
	var outcome = mission_request_outcome(ev)
	// gamemeat i=0: 3000..3099; granite i=4: 3400..3499
	if ((tag >= 3000 && tag < 3100) || (tag >= 3400 && tag < 3500)) {
		mission21_apply_shared_request_outcome(outcome)
	}
}

[es=event_advance_month, mission=mission21]
function mission21_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 66)
}

