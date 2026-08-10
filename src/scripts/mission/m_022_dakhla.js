log_info("akhenaten: mission 22 dakhla started")

// Empire / events verified vs mission1.pak scenario 22 (2026-07-26 dump).
// Empire id=1. Enemy ENEMY_6_KUSHITE. Favour Pharaoh×90.
// Gods: Ra, Ptah, Bast. Funds Normal 6000 / loan 2500 / debt 8. Rank 8.
// Win: pop 5000 / culture 50 / prosperity 45 / monuments TEMP 9 (pak 6 small obelisk) / kingdom 65 / housing 11.
// Burial empty. Climate desert.
// Trade: Nekhen(9) On(2) Saqqara(8) Selima(6). Display Buhen/Byblos/Djedu/Dunqul/Henen/Iunet/Kharga(stub12)/Men-nefer.
// Triage: SKIP empty map_obj idx=9; omit river/disembark/inv points (pak 0).
// Events: early grain/timber/beer; timber×18 gift ladder (ONCE ONLY_VIA); bricks×25 Pepy;
// luxury/grain/pottery recurring — KR via request_cleared (B14 / Sumur); favour×90.
// late-game luxury ladders / pottery / clay floods simplified where noted.
// Ebony briefing → luxury_goods (RESOURCE_EBONY absent).
//
// Tag_id scheme:
//   1000 + i               chain-only leaves (timber gift once)
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots
//   50000 + seq            fire_kr / unique ONCE
//   9000 + seq             luxury i=39 refuse follow-up requests

mission22 { // Dakhla Oasis — The Caravan Trail
	map_file : "data/maps/m_022_dakhla.map"

	// Map points from data/maps/m_022_dakhla.map.
	herd_points_predator [ [41, 107], [85, 103], [63, 66] ]
	herd_points_prey [ [86, 45], [64, 87] ]

	start_message : "message_mission_dakhla"
	selection_title : "Dakhla"
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
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [0, 4, 8, 12, 16]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/222_mission.mp3"
		victory : "Voice/Mission/222_victory.mp3"
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
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_BAST,
	]

	// Monuments TEMP 9 (pak raw 6; one small obelisk → formula 9, same as Buhen).
	win_criteria {
		population    {enabled : true, goal : 5000 }
		culture       {enabled : true, goal : 50 }
		prosperity    {enabled : true, goal : 45 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 65 }
		housing_level {enabled : true, goal : 11 }
	}

	entry_point [84, 166]
	exit_point [92, 8]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
			{
				name : "Dakhla Oasis"
				idx : 2
				pos : [349, 1037]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [ RESOURCE_GRAIN, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_TIMBER ]
				buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			}
	
			{
				name : "Nekhen"
				idx : 10
				pos : [797, 1011]
				route : 9
				is_open : false
				cost_to_open : 600
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
				name : "On"
				idx : 11
				pos : [572, 454]
				route : 2
				is_open : false
				cost_to_open : 1070
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
				buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
				route_limits [
					{ resource: RESOURCE_MEAT, limit: 2500 }
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 1500 }
					{ resource: RESOURCE_TIMBER, limit: 1500 }
					{ resource: RESOURCE_REEDS, limit: 4000 }
					{ resource: RESOURCE_LIMESTONE, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_GEMS, limit: 1500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
					{ resource: RESOURCE_GRANITE, limit: 2500 }
				]
			}
	
			{
				name : "Saqqara"
				idx : 12
				pos : [523, 539]
				route : 8
				is_open : false
				cost_to_open : 1250
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS, RESOURCE_STONE ]
				buys [ RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 4000 }
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 4000 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_REEDS, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 1500 }
					{ resource: RESOURCE_STONE, limit: 2500 }
					{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				]
			}
	
			{
				name : "Selima Oasis"
				idx : 13
				pos : [616, 1353]
				route : 6
				is_open : false
				cost_to_open : 645
				is_sea_trade : false
				type : EMPIRE_CITY_FOREIGN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
				buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 1500 }
					{ resource: RESOURCE_BEER, limit: 4000 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 4000 }
					{ resource: RESOURCE_COPPER, limit: 4000 }
				]
			}
	
			{
				name : "Buhen"
				idx : 0
				pos : [766, 1345]
				route : 5
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Byblos"
				idx : 1
				pos : [891, 68]
				route : 4
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
	
			{
				name : "Djedu"
				idx : 3
				pos : [535, 389]
				route : 1
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Dunqul Oasis"
				idx : 4
				pos : [795, 1191]
				route : 11
				cost_to_open : 650
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Henen-nesw"
				idx : 5
				pos : [534, 626]
				route : 10
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Iunet"
				idx : 6
				pos : [783, 892]
				route : 3
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Kharga Oasis"
				idx : 7
				pos : [623, 1121]
				route : 12
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
	
			{
				name : "Men-nefer"
				idx : 8
				pos : [545, 487]
				route : 7
				trade : false
				type : EMPIRE_CITY_PHARAOH
			}
		]
	
		hide_pak_routes : true
		empire_routes [
			{
				route : 1
				type : 1
				points [
					[552, 405], [548, 464], [546, 513], [555, 560], [568, 608], [551, 670],
					[550, 706], [591, 817], [669, 881], [729, 926], [769, 941], [708, 959],
					[682, 1002], [657, 1037], [632, 1110], [511, 1072], [413, 1057], [371, 1060],
				]
			}
			{
				route : 2
				type : 1
				points [
					[586, 471], [589, 484], [583, 493], [578, 527], [586, 577], [587, 599],
					[575, 653], [554, 701], [576, 768], [610, 817], [664, 847], [726, 891],
					[755, 920], [779, 928], [690, 960], [621, 988], [557, 1003], [498, 1013],
					[458, 1020], [393, 1038], [367, 1055], [367, 1057]
				]
			}
			{
				route : 3
				type : 1
				points [
					[795, 916], [699, 936], [648, 962], [584, 989], [502, 1019], [426, 1043],
					[375, 1062]
				]
			}
			{
				route : 4
				type : 1
				points [
					[904, 89], [886, 144], [876, 201], [869, 254], [857, 303], [825, 330],
					[778, 360], [699, 495], [685, 512], [679, 546], [686, 562], [702, 571],
					[718, 584], [720, 599], [751, 632], [795, 672], [762, 727], [764, 747],
					[773, 757], [779, 784], [787, 808], [794, 832], [800, 846], [801, 861],
					[809, 870], [815, 891], [801, 895], [779, 892], [752, 908], [706, 927],
					[615, 957], [601, 960], [574, 963], [553, 969], [535, 978], [515, 985],
					[482, 997], [447, 1009], [431, 1025], [401, 1037], [388, 1043], [368, 1056],
				]
			}
			{
				route : 5
				type : 1
				points [
					[775, 1363], [793, 1309], [805, 1253], [806, 1208], [793, 1146], [758, 1111],
					[726, 1087], [700, 1079], [660, 1075], [630, 1074], [595, 1074], [581, 1073],
					[500, 1059], [470, 1055], [426, 1064], [388, 1071], [376, 1069]
				]
			}
			{
				route : 6
				type : 1
				points [
					[627, 1361], [605, 1283], [597, 1224], [576, 1167], [565, 1152], [540, 1133],
					[512, 1110], [483, 1096], [441, 1066], [375, 1062], [373, 1068]
				]
			}
			{
				route : 7
				type : 1
				points [
					[577, 529], [591, 556], [592, 574], [573, 582], [558, 599], [543, 618],
					[528, 629], [506, 637], [499, 642], [499, 662], [479, 676], [461, 692],
					[443, 705], [430, 721], [422, 730], [406, 739], [385, 742], [373, 754],
					[369, 766], [366, 780], [370, 795], [376, 812], [376, 838], [375, 858],
					[380, 883], [374, 904], [362, 923], [349, 939], [344, 964], [341, 975],
					[336, 989], [326, 1008], [327, 1021], [334, 1039], [341, 1047], [368, 1056],
				]
			}
			{
				route : 8
				type : 1
				points [
					[535, 566], [553, 610], [560, 646], [552, 694], [554, 748], [566, 774],
					[567, 778], [670, 880], [738, 898], [797, 904], [802, 910], [718, 965],
					[652, 1002], [619, 1047], [583, 1067], [516, 1052], [494, 1039], [433, 1038],
					[413, 1048], [374, 1067]
				]
			}
			{
				route : 9
				type : 1
				points [
					[809, 1034], [802, 1043], [791, 1052], [787, 1058], [777, 1065], [770, 1075],
					[761, 1086], [745, 1097], [741, 1105], [736, 1109], [722, 1117], [702, 1123],
					[671, 1121], [657, 1117], [645, 1116], [633, 1116], [618, 1118], [603, 1117],
					[582, 1113], [562, 1107], [540, 1102], [507, 1093], [482, 1085], [470, 1083],
					[455, 1083], [433, 1083], [409, 1083], [394, 1082], [371, 1079], [359, 1071],
					[359, 1057]
				]
			}
			{
				route : 10
				type : 1
				points [
					[554, 654], [580, 778], [642, 815], [657, 836], [686, 869], [710, 898],
					[725, 920], [734, 924], [768, 924], [784, 925], [702, 962], [666, 969],
					[631, 983], [616, 1004], [597, 1028], [580, 1070], [572, 1058], [514, 1043],
					[493, 1043], [469, 1043], [442, 1045], [402, 1057], [384, 1058], [382, 1058],
				]
			}
			{
				route : 11
				type : 1
				points [
					[810, 1203], [795, 1190], [788, 1182], [787, 1176], [756, 1157], [744, 1149],
					[720, 1137], [707, 1135], [686, 1132], [683, 1130], [661, 1125], [648, 1122],
					[642, 1122], [629, 1123], [612, 1122], [605, 1122], [586, 1122], [578, 1124],
					[564, 1126], [547, 1126], [527, 1125], [510, 1125], [497, 1126], [474, 1126],
					[469, 1126], [447, 1126], [431, 1126], [421, 1125], [397, 1117], [391, 1110],
					[370, 1098], [363, 1092], [346, 1075], [345, 1065], [363, 1057]
				]
			}
			{
				// Kharga display — no pak polyline; 2-pt stub.
				route : 12
				type : 1
				deviation : 40
				points [ [623, 1121], [349, 1037] ]
			}
		]
	
		hide_pak_objects : true
		empire_ornaments [
			{ pos : [417, 649], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [535, 422], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [783, 1326], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [819, 886], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [529, 494], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [604, 450], image : "pharaoh_general/empire_bits_00120" }
			{ pos : [688, 887], image : "pharaoh_general/empire_bits_00119" }
			{ pos : [844, 1088], image : "pharaoh_general/empire_bits_00119" }
			{ pos : [499, 545], image : "pharaoh_general/empire_bits_00117" }
			{ pos : [572, 596], image : "pharaoh_general/empire_bits_00116" }
			{ pos : [601, 549], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [504, 516], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [479, 501], image : "pharaoh_general/empire_bits_00123" }
			{ pos : [621, 568], image : "pharaoh_general/empire_bits_00118" }
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
		timber23_leaves_wired : false
		event2_done : false
		event3_done : false
		event5_done : false
		event6_done : false
		event7_done : false
		event9_done : false
		event11_done : false
		event22_done : false
		event36_done : false
		event37_done : false
		event45_done : false
		event50_done : false
		event52_done : false
		event53_done : false
		event54_done : false
		event4_wage_done : false
		event12_price_done : false
		event23_timber_done : false
		event29_water_done : false
		event30_demand_done : false
		event38_wage_done : false
		event49_grain_last_year : -1
		event16_bricks_last_year : -1
		event13_luxury_last_year : -1
		event31_luxury_last_year : -1
		event39_luxury_last_year : -1
		event48_pottery_last_year : -1
		event51_grain_last_year : -1
		event21_trade_last_year : -1
		event8_trade_last_year : -1
		event32_trade_last_year : -1
		event46_trade_last_year : -1
		event33_flood_last_year : -1
		event34_flood_last_year : -1
		event35_flood_last_year : -1
		event47_flood_last_year : -1
		kr_seq : 0
		lux_follow_seq : 0
		grain_recurring_was_busy : false
		grain_recurring_idle_since_abs : -1
		bricks_recurring_was_busy : false
		bricks_recurring_idle_since_abs : -1
		luxury_recurring_was_busy : false
		luxury_recurring_idle_since_abs : -1
		pottery_recurring_was_busy : false
		pottery_recurring_idle_since_abs : -1
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission22_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission22_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission22_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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
function mission22_fire_kr(delta) {
	var type = delta >= 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE
	var amount = delta >= 0 ? delta : -delta
	mission.kr_seq = (mission.kr_seq | 0) + 1
	mission22_fire_simple_event(50000 + mission.kr_seq, type, undefined, amount)
}

function mission22_apply_early_kr(outcome) {
	// pak i=0 KR+6 / i=1 KR−7 / i=55 KR−4
	if (outcome == "ok") {
		mission22_fire_kr(6)
	} else if (outcome == "refuse") {
		mission22_fire_kr(-7)
	} else {
		mission22_fire_kr(-4)
	}
}

function mission22_apply_luxury_kr(outcome) {
	// pak i=14 KR+17 / i=15 KR−14 / i=55 KR−4
	if (outcome == "ok") {
		mission22_fire_kr(17)
	} else if (outcome == "refuse") {
		mission22_fire_kr(-14)
	} else {
		mission22_fire_kr(-4)
	}
}

function mission22_start_luxury_refuse_followup() {
	// pak i=39 refuse → i=41 demand−8 → i=42 luxury×11
	mission.kr_seq = (mission.kr_seq | 0) + 1
	mission22_fire_simple_event(51000 + mission.kr_seq, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_LUXURY_GOODS, 8)
	mission.lux_follow_seq = (mission.lux_follow_seq | 0) + 1
	var ftag = 9000 + mission.lux_follow_seq
	mission22_fire_request(ftag, RESOURCE_LUXURY_GOODS, 11, 12, 0, 0, 0, 0, 0)
}

function mission22_ensure_timber_i23_leaves() {
	// pak i=23 timber×18: ok→i=24 gift meat×14→i=25 NEW_TRADE Selima;
	//   gift refuse/late→i=26 gems×5→i=27 oil×812→i=25; refuse→i=28 KR−28→i=57 bricks×17; late→i=25.
	// Once-only chain — ONLY_VIA leaves OK.
	if (mission.timber23_leaves_wired) {
		return
	}
	mission.timber23_leaves_wired = true
	var gift = mission22_make_leaf(1024, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_MEAT, 14, 2)
	mission22_make_leaf(1025, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Selima Oasis")
	var gift_gems = mission22_make_leaf(1026, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_GEMS, 5, 2)
	var gift_oil = mission22_make_leaf(1027, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_OIL, 812, 2)
	var kr_refuse = mission22_make_leaf(1028, EVENT_TYPE_REPUTATION_DECREASE, undefined, 28, 2)
	var bricks = city.create_good_request({
		tag_id: 1057,
		resource: RESOURCE_BRICKS,
		amount: 17,
		months_initial: 10,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	bricks.set_sender_faction(0)
	bricks.set_completed_action_tag(1024)
	bricks.set_refusal_action_tag(1028)
	bricks.set_too_late_action_tag(1025)
	gift.set_completed_action_tag(1025)
	gift.set_refusal_action_tag(1026)
	gift.set_too_late_action_tag(1026)
	gift_gems.set_completed_action_tag(1025)
	gift_gems.set_refusal_action_tag(1027)
	gift_gems.set_too_late_action_tag(1027)
	gift_oil.set_completed_action_tag(1025)
	gift_oil.set_refusal_action_tag(1025)
	gift_oil.set_too_late_action_tag(1025)
	kr_refuse.set_completed_action_tag(1057)
}

[es=event_mission_start, mission=mission22]
function mission22_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_dakhla")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission22_ensure_timber_i23_leaves()
}

[es=event_advance_month, mission=mission22]
function mission22_requests_and_economy(ev) {
	mission22_ensure_timber_i23_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_GRAIN, "grain_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_BRICKS, "bricks_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_LUXURY_GOODS, "luxury_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_POTTERY, "pottery_recurring", abs)

	// Early once requests — outcomes via request_cleared (ok→KR+6 refuse→KR−7 late→KR−4).
	var once = [
		[2, 7, 2, RESOURCE_GRAIN, 4, 10, 0, 0],
		[3, 10, 10, RESOURCE_TIMBER, 4, 10, 0, 1],
		[5, 16, 9, RESOURCE_BEER, 8, 8, 3, 0],
		[6, 12, 7, RESOURCE_GRAIN, 9, 10, 5, 0],
		[7, 14, 1, RESOURCE_LUXURY_GOODS, 5, 6, 0, 0],
		[11, 20, 0, RESOURCE_LUXURY_GOODS, 6, 8, 0, 0],
		[22, 30, 11, RESOURCE_BEER, 5, 8, 0, 0],
		[36, 55, 9, RESOURCE_GRAIN, 23, 8, 3, 0],
		[37, 57, 3, RESOURCE_BEER, 14, 8, 0, 1],
		[52, 25, 4, RESOURCE_GRAIN, 7, 6, 0, 0],
		[53, 35, 7, RESOURCE_GRAIN, 5, 8, 5, 0],
		[54, 47, 11, RESOURCE_GRAIN, 9, 10, 5, 0]
	]
	for (var i = 0; i < once.length; i++) {
		var row = once[i]
		var flag = "event" + row[0] + "_done"
		if (!mission[flag] && ev.years_since_start == row[1] && ev.month == row[2]) {
			mission[flag] = true
			log_info("akhenaten: mission 22 request i=" + row[0])
			mission22_fire_request(2000 + row[0], row[3], row[4], row[5], 0, 0, 0, row[6], row[7])
		}
	}

	if (!mission.event4_wage_done && ev.years_since_start == 11 && ev.month == 4) {
		mission.event4_wage_done = true
		mission22_fire_simple_event(2004, EVENT_TYPE_WAGE_DECREASE, undefined, 2)
	}
	if (!mission.event9_done && ev.years_since_start == 18 && ev.month == 7) {
		mission.event9_done = true
		log_info("akhenaten: mission 22 grain×11 (i=9) late→wage−4")
		mission22_fire_request(2009, RESOURCE_GRAIN, 11, 6, 0, 0, 0, 0, 0)
	}
	if (!mission.event12_price_done && ev.years_since_start == 21 && ev.month == 8) {
		mission.event12_price_done = true
		mission22_fire_simple_event(2012, EVENT_TYPE_PRICE_INCREASE, RESOURCE_STONE, 21)
	}
	if (!mission.event23_timber_done && ev.years_since_start == 3 && ev.month == 3) {
		mission.event23_timber_done = true
		log_info("akhenaten: mission 22 timber×18 (i=23)")
		mission22_fire_request(2023, RESOURCE_TIMBER, 18, 10, 1024, 1028, 1025, 0, 0)
	}
	if (!mission.event29_water_done && ev.years_since_start == 34 && ev.month == 8) {
		mission.event29_water_done = true
		mission22_fire_simple_event(2029, EVENT_TYPE_CONTAMINATED_WATER, undefined, 9)
	}
	if (!mission.event30_demand_done && ev.years_since_start == 35 && ev.month == 2) {
		mission.event30_demand_done = true
		mission22_fire_simple_event(2030, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 5)
	}
	if (!mission.event38_wage_done && ev.years_since_start == 60 && ev.month == 1) {
		mission.event38_wage_done = true
		mission22_fire_simple_event(2038, EVENT_TYPE_WAGE_INCREASE, undefined, 4)
	}
	if (!mission.event45_done && ev.years_since_start == 71 && ev.month == 10) {
		mission.event45_done = true
		log_info("akhenaten: mission 22 pottery×15 (i=45)")
		mission22_fire_request(2045, RESOURCE_POTTERY, 15, 10, 0, 0, 0, 0, 1)
	}
	if (!mission.event50_done && ev.years_since_start == 84 && ev.month == 9) {
		mission.event50_done = true
		log_info("akhenaten: mission 22 grain×27 (i=50)")
		mission22_fire_request(2050, RESOURCE_GRAIN, 27, 10, 0, 0, 0, 3, 0)
	}

	// pak i=49: grain×6 / 5mo recurring y4m0+ idle-gated.
	if (ev.years_since_start >= 4 && ev.month == 0
			&& mission.event49_grain_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		mission.event49_grain_last_year = ev.years_since_start
		log_info("akhenaten: mission 22 grain×6 recurring (i=49)")
		mission22_fire_request(3000 + 49 * 100 + ev.years_since_start,
			RESOURCE_GRAIN, 6, 5, 0, 0, 0, 5, 0)
	}

	// pak i=16: bricks×25 / 12mo recurring y25m5+ (Pepy construction).
	if (ev.years_since_start > 25 || (ev.years_since_start == 25 && ev.month >= 5)) {
		if (ev.month == 5 && mission.event16_bricks_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_BRICKS, "bricks_recurring", abs)) {
			mission.event16_bricks_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 bricks×25 recurring (i=16)")
			mission22_fire_request(3000 + 16 * 100 + ev.years_since_start,
				RESOURCE_BRICKS, 25, 12, 0, 0, 0, 4, 0)
		}
	}

	// pak i=13: luxury×18 / 12mo recurring y23m4+.
	if (ev.years_since_start > 23 || (ev.years_since_start == 23 && ev.month >= 4)) {
		if (ev.month == 4 && mission.event13_luxury_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_LUXURY_GOODS, "luxury_recurring", abs)) {
			mission.event13_luxury_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 luxury×18 recurring (i=13)")
			mission22_fire_request(3000 + 13 * 100 + ev.years_since_start,
				RESOURCE_LUXURY_GOODS, 18, 12, 0, 0, 0, 0, 1)
		}
	}

	// pak i=31: luxury×14 / 12mo recurring y36m7+.
	if (ev.years_since_start > 36 || (ev.years_since_start == 36 && ev.month >= 7)) {
		if (ev.month == 7 && mission.event31_luxury_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_LUXURY_GOODS, "luxury_recurring", abs)) {
			mission.event31_luxury_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 luxury×14 recurring (i=31)")
			mission22_fire_request(3000 + 31 * 100 + ev.years_since_start,
				RESOURCE_LUXURY_GOODS, 14, 12, 0, 0, 0, 0, 0)
		}
	}

	// pak i=39→44: luxury×25 / 10mo rec y65m8+ demand/price ladder (late=666 skip).
	if (ev.years_since_start > 65 || (ev.years_since_start == 65 && ev.month >= 8)) {
		if (ev.month == 8 && mission.event39_luxury_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_LUXURY_GOODS, "luxury_recurring", abs)) {
			mission.event39_luxury_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 luxury×25 ladder (i=39)")
			mission22_fire_request(3000 + 39 * 100 + ev.years_since_start,
				RESOURCE_LUXURY_GOODS, 25, 10, 0, 0, 0, 0, 0)
		}
	}

	// pak i=48: pottery×47 / 2mo recurring y80m7+.
	if (ev.years_since_start > 80 || (ev.years_since_start == 80 && ev.month >= 7)) {
		if (ev.month == 7 && mission.event48_pottery_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_POTTERY, "pottery_recurring", abs)) {
			mission.event48_pottery_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 pottery×47 recurring (i=48)")
			mission22_fire_request(3000 + 48 * 100 + ev.years_since_start,
				RESOURCE_POTTERY, 47, 2, 0, 0, 0, 0, 1)
		}
	}

	// pak i=51: grain×24 / 6mo recurring y88m8+.
	if (ev.years_since_start > 88 || (ev.years_since_start == 88 && ev.month >= 8)) {
		if (ev.month == 8 && mission.event51_grain_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
			mission.event51_grain_last_year = ev.years_since_start
			log_info("akhenaten: mission 22 grain×24 recurring (i=51)")
			mission22_fire_request(3000 + 51 * 100 + ev.years_since_start,
				RESOURCE_GRAIN, 24, 6, 0, 0, 0, 0, 0)
		}
	}

	// Economy nuisances (recurring).
	if (ev.years_since_start >= 17 && ev.month == 8
			&& mission.event8_trade_last_year != ev.years_since_start) {
		mission.event8_trade_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 8 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 6)
	}
	if (ev.years_since_start >= 28 && ev.month == 7
			&& mission.event21_trade_last_year != ev.years_since_start) {
		mission.event21_trade_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 21 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 8)
	}
	if (ev.years_since_start >= 42 && ev.month == 1
			&& mission.event32_trade_last_year != ev.years_since_start) {
		mission.event32_trade_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 32 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 5)
	}
	if (ev.years_since_start >= 72 && ev.month == 7
			&& mission.event46_trade_last_year != ev.years_since_start) {
		mission.event46_trade_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 46 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 6)
	}
	if (ev.years_since_start >= 25 && ev.month == 6
			&& mission.event33_flood_last_year != ev.years_since_start) {
		mission.event33_flood_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 33 * 100 + ev.years_since_start,
			EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 5)
	}
	if (ev.years_since_start >= 34 && ev.month == 5
			&& mission.event34_flood_last_year != ev.years_since_start) {
		mission.event34_flood_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 34 * 100 + ev.years_since_start,
			EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 9)
	}
	if (ev.years_since_start >= 53 && ev.month == 6
			&& mission.event35_flood_last_year != ev.years_since_start) {
		mission.event35_flood_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 35 * 100 + ev.years_since_start,
			EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 6)
	}
	if (ev.years_since_start >= 81 && ev.month == 5
			&& mission.event47_flood_last_year != ev.years_since_start) {
		mission.event47_flood_last_year = ev.years_since_start
		mission22_fire_simple_event(3000 + 47 * 100 + ev.years_since_start,
			EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 9)
	}
}

[es=event_request_cleared, mission=mission22]
function mission22_on_request_cleared(ev) {
	var tag = ev.tag_id
	var outcome = mission_request_outcome(ev)

	// Timber gift chain request (1057) — keep ONLY_VIA tails; no KR here beyond chain.
	if (tag == 2023 || tag == 1057) {
		return
	}

	// Luxury i=39 refuse follow-up (9001+)
	if (tag >= 9000 && tag < 9100) {
		if (outcome == "ok") {
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(52000 + mission.kr_seq, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LUXURY_GOODS, 9)
		} else if (outcome == "refuse") {
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(53000 + mission.kr_seq, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_LUXURY_GOODS, 5)
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(54000 + mission.kr_seq, EVENT_TYPE_PRICE_DECREASE, RESOURCE_LUXURY_GOODS, 45)
		} else {
			mission22_fire_kr(-4)
		}
		return
	}

	// Luxury i=39 root (6900+year)
	if (tag >= 6900 && tag < 7000) {
		if (outcome == "ok") {
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(52000 + mission.kr_seq, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LUXURY_GOODS, 9)
		} else if (outcome == "refuse") {
			mission22_start_luxury_refuse_followup()
		}
		// late = pak 666 junk — skip
		return
	}

	// Bricks i=16 (4600+year): ok→KR+18→wage+5; refuse→KR−27; late→KR−4
	if (tag >= 4600 && tag < 4700) {
		if (outcome == "ok") {
			mission22_fire_kr(18)
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(55000 + mission.kr_seq, EVENT_TYPE_WAGE_INCREASE, undefined, 5)
		} else if (outcome == "refuse") {
			mission22_fire_kr(-27)
		} else {
			mission22_fire_kr(-4)
		}
		return
	}

	// Luxury i=13 (4300+) / i=31 (6100+) / pottery i=48 (7800+) / pottery once 2045 /
	// grain once 2050 / grain i=51 (8100+)
	if ((tag >= 4300 && tag < 4400) || (tag >= 6100 && tag < 6200)
			|| (tag >= 7800 && tag < 7900) || (tag >= 8100 && tag < 8200)
			|| tag == 2045 || tag == 2050) {
		mission22_apply_luxury_kr(outcome)
		return
	}

	// Grain i=9: ok/refuse early KR; late → wage−4 (pak i=10)
	if (tag == 2009) {
		if (outcome == "ok") {
			mission22_fire_kr(6)
		} else if (outcome == "refuse") {
			mission22_fire_kr(-7)
		} else {
			mission.kr_seq = (mission.kr_seq | 0) + 1
			mission22_fire_simple_event(56000 + mission.kr_seq, EVENT_TYPE_WAGE_DECREASE, undefined, 4)
		}
		return
	}

	// Early once + grain i=49 (7900+): shared early KR
	var early_once = {
		2002: 1, 2003: 1, 2005: 1, 2006: 1, 2007: 1, 2011: 1,
		2022: 1, 2036: 1, 2037: 1, 2052: 1, 2053: 1, 2054: 1
	}
	if (early_once[tag] || (tag >= 7900 && tag < 8000)) {
		mission22_apply_early_kr(outcome)
	}
}

[es=event_advance_month, mission=mission22]
function mission22_pharaoh_favour_invasion(ev) {
	// pak i=56: favour Pharaoh ×90 (no chain).
	mission_pharaoh_favour_invasion_tick(mission, 90)
}

