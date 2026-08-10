log_info("akhenaten: mission 28 iken started")

mission28 { // Iken (Mirgissa) — Into Nubia; briefing key = mirgissa
	map_file : "data/maps/m_028_iken.map"

	// Map points from data/maps/m_028_iken.map.
	herd_points_predator [ [93, 187], [152, 165], [154, 50] ]
	herd_points_prey [ [125, 20], [205, 101] ]

	start_message : "message_mission_mirgissa"
	selection_title : "Iken"
	player_rank : 10

	// Choice pair with Sawu; next is Heh (30) / Bubastis (31).
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

	// pak Normal funds=7000 loan=3000 debt_interest=0 → int_dcy around Normal.
	initial_funds [14000, 9300, 7000, 4700, 3700]
	rescue_loans [6000, 4000, 3000, 2000, 1600]
	debt_interest [0, 0, 0, 0, 0]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/228_mission.mp3"
		victory : "Voice/Mission/228_victory.mp3"
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
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_GRANITE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_COPPER_MINE,
		BUILDING_LARGE_OBELISK,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// Large Obelisk weight 4 → rating 13.5 ≥ pak goal 11 — keep 11.
	win_criteria {
		population    {enabled : true, goal : 6000 }
		culture       {enabled : true, goal : 45 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : true, goal : 11 }
		kingdom       {enabled : true, goal : 80 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [70, 43]
	exit_point [71, 42]
	river_entry_point [98, 17]
	river_exit_point [103, 12]
	disembark_points [ [98, 23], [177, 100], [123, 67] ]
	invasion_points_land [ [221, 187], [152, 100] ]
	invasion_points_sea [ [109, 148], [183, 15] ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
			{
				name : "Iken"
				idx : 4
				pos : [735, 1380]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [ RESOURCE_FIGS, RESOURCE_GAMEMEAT, RESOURCE_BARLEY, RESOURCE_FLAX ]
				buys [ RESOURCE_WEAPONS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			}

			{
				name : "Buhen"
				idx : 0
				pos : [780, 1332]
				route : 7
				is_open : false
				cost_to_open : 100
				is_sea_trade : true
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
				name : "Dakhla Oasis"
				idx : 2
				pos : [349, 1037]
				route : 9
				is_open : false
				cost_to_open : 685
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
				buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
				route_limits [
					{ resource: RESOURCE_MEAT, limit: 2500 }
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
					{ resource: RESOURCE_GRANITE, limit: 1500 }
				]
			}

			{
				name : "Farafra Oasis"
				idx : 3
				pos : [327, 831]
				route : 1
				is_open : false
				cost_to_open : 815
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CLAY, RESOURCE_TIMBER ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
				]
			}

			{
				name : "Kebet"
				idx : 5
				pos : [829, 900]
				route : 10
				is_open : false
				cost_to_open : 675
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_GRANITE, RESOURCE_COPPER ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 1500 }
					{ resource: RESOURCE_POTTERY, limit: 1500 }
					{ resource: RESOURCE_GRANITE, limit: 4000 }
					{ resource: RESOURCE_COPPER, limit: 1500 }
				]
			}

			{
				name : "Men-nefer"
				idx : 8
				pos : [545, 487]
				route : 6
				is_open : false
				cost_to_open : 1335
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
				buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
				route_limits [
					{ resource: RESOURCE_LETTUCE, limit: 2500 }
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
				// Display foreign; unlocked via i=26 NEW_TRADE (loc=2 = route 2).
				// Pak sells/buys empty — timber/luxury so unlock is playable (Byblos pattern).
				name : "Byblos"
				idx : 1
				pos : [891, 68]
				route : 2
				is_open : false
				cost_to_open : 2000
				is_sea_trade : false
				trade : false
				type : EMPIRE_CITY_FOREIGN
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_TIMBER ]
				buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS ]
				route_limits [
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				]
			}

			{
				// Display foreign; unlocked via copper-ladder i=24 NEW_TRADE (loc=5 = route 5).
				name : "Kerma"
				idx : 6
				pos : [732, 1491]
				route : 5
				is_open : false
				cost_to_open : 150
				is_sea_trade : false
				trade : false
				type : EMPIRE_CITY_FOREIGN
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
				name : "Kharga Oasis"
				idx : 7
				pos : [635, 1130]
				route : 11
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}

			{
				name : "Menat Khufu"
				idx : 9
				pos : [578, 720]
				route : 4
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}

			{
				name : "Sawu"
				idx : 11
				pos : [907, 834]
				route : 3
				is_open : false
				cost_to_open : 890
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
				buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_WEAPONS ]
				route_limits [
					{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
					{ resource: RESOURCE_COPPER, limit: 1500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_WEAPONS, limit: 1500 }
				]
			}

			{
				name : "Waset"
				idx : 12
				pos : [811, 968]
				route : 8
				is_open : false
				cost_to_open : 570
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN ]
				buys [ RESOURCE_FIGS, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_GAMEMEAT ]
				route_limits [
					{ resource: RESOURCE_POTTERY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_FIGS, limit: 2500 }
					{ resource: RESOURCE_BARLEY, limit: 2500 }
					{ resource: RESOURCE_FLAX, limit: 2500 }
					{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				]
			}
		]

		hide_pak_routes : true
		empire_routes [
			{
				route : 1
				type : 1
				points [
					[344, 849], [342, 882], [355, 930], [351, 998], [385, 1086], [433, 1087],
					[438, 1071], [455, 1071], [474, 1079], [511, 1073], [553, 1081], [646, 1136],
					[656, 1217], [646, 1225], [645, 1257], [664, 1299], [674, 1305], [690, 1358],
					[718, 1376], [762, 1405]
				]
			}
			{
				route : 2
				type : 1
				points [
					[905, 92], [875, 236], [850, 318], [701, 497], [682, 523], [682, 549],
					[726, 609], [829, 704], [881, 773], [905, 816], [925, 850], [878, 882],
					[861, 899], [843, 920], [834, 959], [828, 998], [807, 1021], [753, 1063],
					[737, 1076], [719, 1083], [696, 1089], [679, 1099], [663, 1110], [658, 1124],
					[652, 1149], [660, 1174], [674, 1214], [683, 1229], [698, 1265], [705, 1279],
					[718, 1299], [733, 1333], [742, 1352], [746, 1362], [757, 1388], [761, 1420],
				]
			}
			{
				route : 3
				type : 2
				points [
					[920, 849], [914, 839], [889, 844], [865, 833], [853, 832], [802, 843],
					[801, 861], [816, 886], [812, 908], [823, 926], [828, 945], [816, 967],
					[832, 1016], [850, 1024], [860, 1036], [866, 1047], [878, 1076], [879, 1095],
					[881, 1120], [888, 1140], [883, 1159], [894, 1180], [893, 1195], [888, 1208],
					[904, 1227], [903, 1243], [874, 1309], [866, 1321], [841, 1303], [838, 1308],
					[815, 1330], [821, 1341], [794, 1373], [764, 1405]
				]
			}
			{
				route : 4
				type : 1
				points [
					[735, 1380], [578, 720]
				]
			}
			{
				route : 5
				type : 1
				points [
					[747, 1506], [732, 1488], [730, 1483], [724, 1481], [719, 1483], [711, 1481],
					[706, 1476], [699, 1475], [704, 1467], [692, 1464], [706, 1459], [713, 1459],
					[718, 1456], [720, 1448], [728, 1441], [733, 1436], [757, 1412]
				]
			}
			{
				route : 6
				type : 2
				points [
					[576, 514], [587, 528], [589, 546], [592, 568], [594, 587], [600, 612],
					[584, 632], [583, 648], [569, 678], [570, 714], [567, 720], [577, 736],
					[596, 777], [597, 798], [615, 815], [645, 827], [663, 847], [702, 884],
					[720, 895], [746, 917], [759, 917], [774, 933], [788, 929], [798, 920],
					[814, 907], [829, 944], [817, 966], [832, 1014], [851, 1026], [870, 1053],
					[879, 1080], [881, 1104], [886, 1140], [881, 1167], [897, 1182], [893, 1198],
					[890, 1210], [905, 1224], [904, 1239], [881, 1295], [870, 1312], [861, 1321],
					[842, 1306], [814, 1328], [799, 1369], [757, 1406]
				]
			}
			{
				route : 7
				type : 2
				points [
					[804, 1357], [766, 1405]
				]
			}
			{
				route : 8
				type : 2
				points [
					[823, 981], [836, 1015], [852, 1023], [866, 1040], [867, 1055], [878, 1066],
					[883, 1129], [883, 1165], [896, 1181], [890, 1214], [905, 1226], [897, 1257],
					[878, 1304], [855, 1322], [846, 1306], [814, 1325], [801, 1357], [765, 1406],
				]
			}
			{
				route : 9
				type : 1
				points [
					[369, 1059], [384, 1087], [434, 1086], [438, 1074], [455, 1073], [481, 1080],
					[518, 1071], [554, 1077], [647, 1132], [653, 1219], [646, 1226], [646, 1266],
					[665, 1303], [676, 1313], [692, 1361], [756, 1401]
				]
			}
			{
				route : 10
				type : 2
				points [
					[836, 924], [826, 930], [829, 946], [817, 963], [831, 1011], [853, 1026],
					[864, 1044], [880, 1088], [880, 1100], [880, 1126], [886, 1138], [881, 1163],
					[897, 1178], [889, 1214], [905, 1226], [904, 1245], [875, 1305], [863, 1319],
					[848, 1307], [822, 1320], [797, 1371], [762, 1408]
				]
			}
			{
				route : 11
				type : 1
				points [
					[735, 1380], [635, 1130]
				]
			}
		]

		hide_pak_objects : true
		empire_ornaments [
			{ pos : [539, 426], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [423, 651], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [487, 506], image : "pharaoh_general/empire_bits_00123" }
			{ pos : [614, 714], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [631, 715], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [588, 459], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [515, 488], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [607, 526], image : "pharaoh_general/empire_bits_00118" }
			{ pos : [499, 552], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [569, 595], image : "pharaoh_general/empire_bits_00128" }
			{ pos : [615, 739], image : "pharaoh_general/empire_bits_00115" }
			{ pos : [513, 525], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [581, 512], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [839, 984], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [793, 1309], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [812, 1194], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [382, 1031], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [881, 904], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [861, 903], image : "pharaoh_general/empire_bits_00121" }
			{ pos : [817, 885], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [682, 882], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [838, 1091], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [848, 967], image : "pharaoh_general/empire_bits_00115" }
			{ pos : [562, 563], image : "pharaoh_general/empire_bits_00123" }
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
			{ name : "#upper_egypt", pos : [688, 995] }
			{ name : "#western_desert", pos : [230, 774] }
			{ name : "#lebanon", pos : [877, 109] }
			{ name : "#canaan", pos : [850, 271] }
		]
	vars {
		shared_leaves_wired : false
		copper_ladder_active : false
		copper_ladder_pending : false
		copper_ladder_step : 0
		copper_ladder_enemies_seen : false

		event0_gamemeat_done : false
		event3_oil_done : false
		event8_barley_done : false
		event12_weapons_done : false
		event16_copper_done : false
		event26_newtrade_done : false
		event34_demand_done : false

		event6_beduin_done : false
		event7_enemy_done : false
		event36_beduin_done : false
		event37_beduin_done : false
		event38_beduin_done : false
		event39_beduin_done : false
		event40_beduin_done : false

		oil_egypt_raid_done : false

		linen_recurring_was_busy : false
		linen_recurring_idle_since_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_enemies_seen : false

		start_message_shown : false
	}
}

function mission28_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission28_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
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
	event.execute()
	return event
}

function mission28_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, city_name) {
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

// pak inv_land[0]=[221,187] [1]=[152,100]; loc is 1-based; out of range → entry fallback.
function mission28_loc_tile(loc) {
	if (loc == 1) {
		return [221, 187]
	}
	if (loc == 2) {
		return [152, 100]
	}
	return [-1, -1]
}

function mission28_egypt_raid(invasion_id, size, attack_target, loc) {
	var tile = mission28_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 28 egypt raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

function mission28_beduin_raid(invasion_id, size, loc, attack_target) {
	var tile = mission28_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 28 beduin raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_LIBIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	})
}

function mission28_hittite_raid(invasion_id, size, loc, attack_target) {
	var tile = mission28_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 28 hittite raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_HITTITE)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_4_HITTITE,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	})
}

function mission28_favour_wave(size, invasion_id, loc, attack_target) {
	var tile = mission28_loc_tile(loc === undefined ? 1 : loc)
	log_info("akhenaten: mission 28 favour wave size=" + size + " kr=" + city.rating_kingdom
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

function mission28_start_copper_ladder() {
	// pak i=18→19→21→22→23 enemy sizes 32/64/72/24/96 then i=25 KR+ → i=24 NEW_TRADE.
	mission.copper_ladder_active = true
	mission.copper_ladder_step = 0
	mission.copper_ladder_enemies_seen = false
	mission28_hittite_raid(18, 32, 9, EVENT_ATTACK_TARGET_RANDOM)
}

function mission28_ensure_shared_leaves() {
	if (mission.shared_leaves_wired) {
		return
	}
	mission.shared_leaves_wired = true

	// i=1 gift copper×8 subtype=2 (ok/late of gamemeat i=0 and oil i=3); ok=994 OOB — no further chain.
	mission28_make_leaf(1001, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 8, 2, 2)
	// i=2 PRICE+ granite (gamemeat refuse)
	mission28_make_leaf(1002, EVENT_TYPE_PRICE_INCREASE, RESOURCE_GRANITE, 55, 2)

	// barley/linen shared KR: late→31 KR−3; refuse→32 KR−10
	mission28_make_leaf(1031, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission28_make_leaf(1032, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2)

	// barley ok → i=9 gift copper×16 subtype=2
	mission28_make_leaf(1009, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 16, 2, 2)

	// linen ok → i=33 gift copper×8 → i=4 NEW_TRADE Sawu → i=35 copper demand+
	var gift33 = mission28_make_leaf(1033, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 8, 2)
	// i=4 NEW_TRADE Sawu (loc=3); i=35 copper demand+ also loc=3 → Sawu (not city=7 Kerma junk).
	var nt4 = mission28_make_leaf(1004, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Sawu")
	mission28_make_leaf(1035, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_COPPER, 9, 2, undefined, "Sawu")
	gift33.set_completed_action_tag(1004)
	nt4.set_completed_action_tag(1035)

	// weapons: ok→13 NEW_TRADE Waset; late→15 NEW_TRADE Waset;
	// refuse→14 siege →10 LOST_TRADE →11 NEW_TRADE
	mission28_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Waset")
	mission28_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Waset")
	var siege14 = mission28_make_leaf(1014, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_CITY_UNDER_SIEGE, "Sawu")
	var lost10 = mission28_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Sawu")
	mission28_make_leaf(1011, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Sawu")
	siege14.set_completed_action_tag(1010)
	lost10.set_completed_action_tag(1011)

	// copper: ok/late→17 KR−35; refuse→20 KR+15. Invasion ladder via pending+poll (KR leaf first).
	mission28_make_leaf(1017, EVENT_TYPE_REPUTATION_DECREASE, undefined, 35, 2)
	mission28_make_leaf(1020, EVENT_TYPE_REPUTATION_INCREASE, undefined, 15, 2)
	// wipe reward: i=25 KR+25 → i=24 NEW_TRADE Kerma (pak loc=5 = route 5; city=4 Farafra junk).
	var kr25 = mission28_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 25, 2)
	mission28_make_leaf(1024, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
	kr25.set_completed_action_tag(1024)
}

[es=event_mission_start, mission=mission28]
function mission28_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HITTITE)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_OBELISK_EXTRA)
	__image_request_pak(PACK_OBELISK_X5_A)
	__image_request_pak(PACK_OBELISK_X5_B)
	__image_request_pak(PACK_OBELISK_X5_C)
	__image_request_pak(PACK_OBELISK_X5_D)
	__image_request_pak(PACK_OBELISK_X5_E)
	__image_request_pak(PACK_OBELISK_X5_F)
	mission_show_start_message(mission, "message_mission_mirgissa")
	empire.set_id(13)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_4_HITTITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission28_ensure_shared_leaves()
}

[es=event_advance_month, mission=mission28]
function mission28_requests_and_events(ev) {
	mission28_ensure_shared_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_LINEN, "linen_recurring", abs)

	// pak i=0: gamemeat×6 /12mo y0m2 → ok/late 1001 gift; refuse 1002 price+.
	if (!mission.event0_gamemeat_done && ev.years_since_start == 0 && ev.month == 2) {
		mission.event0_gamemeat_done = true
		log_info("akhenaten: mission 28 gamemeat×6 (i=0)")
		mission28_fire_request(2000, RESOURCE_GAMEMEAT, 6, 12, 1001, 1002, 1001, 0, 0, "Farafra Oasis")
	}

	// pak i=34: DEMAND− copper×5 y0m9 loc=10 Kebet.
	if (!mission.event34_demand_done && ev.years_since_start == 0 && ev.month == 9) {
		mission.event34_demand_done = true
		log_info("akhenaten: mission 28 copper demand −5 Kebet (i=34)")
		mission28_fire_simple_event(2034, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_COPPER, 5, "Kebet")
	}

	// pak i=16: copper×200 /1mo y1m1 subtype=6 → ok/late 1017; refuse 1020 + ladder.
	if (!mission.event16_copper_done && ev.years_since_start == 1 && ev.month == 1) {
		mission.event16_copper_done = true
		log_info("akhenaten: mission 28 copper×200 (i=16)")
		mission28_fire_request(2016, RESOURCE_COPPER, 200, 1, 1017, 1020, 1017, 6, 0, "Kharga Oasis")
	}

	// pak i=3: oil×1168 /6mo y1m8 subtype=4 → ok/late 1001; refuse → egypt×64 via JS chain.
	if (!mission.event3_oil_done && ev.years_since_start == 1 && ev.month == 8) {
		mission.event3_oil_done = true
		log_info("akhenaten: mission 28 oil×1168 (i=3)")
		mission28_fire_request(2003, RESOURCE_OIL, 1168, 6, 1001, 0, 1001, 4, 0, "Farafra Oasis")
	}

	// pak i=8: barley×7 /12mo y2m3 → ok 1009; refuse 1032; late 1031.
	if (!mission.event8_barley_done && ev.years_since_start == 2 && ev.month == 3) {
		mission.event8_barley_done = true
		log_info("akhenaten: mission 28 barley×7 (i=8)")
		mission28_fire_request(2008, RESOURCE_BARLEY, 7, 12, 1009, 1032, 1031, 0, 0, "Kerma")
	}

	// pak i=30: linen×10 /9mo y2m8+ recurring → ok 1033; refuse 1032; late 1031.
	if (ev.years_since_start > 2 || (ev.years_since_start == 2 && ev.month >= 8)) {
		if (ev.month == 8
				&& mission_recurring_request_may_fire(mission, RESOURCE_LINEN, "linen_recurring", abs)) {
			log_info("akhenaten: mission 28 linen×10 recurring (i=30)")
			mission28_fire_request(2030, RESOURCE_LINEN, 10, 9, 1033, 1032, 1031, 0, 0, "Kebet")
		}
	}

	// pak i=26: CITY_STATUS NEW_TRADE once y3m0 loc=2 → Byblos (amount=90 junk).
	if (!mission.event26_newtrade_done && ev.years_since_start == 3 && ev.month == 0) {
		mission.event26_newtrade_done = true
		log_info("akhenaten: mission 28 NEW_TRADE Byblos (i=26)")
		mission28_fire_simple_event(2026, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 90, "Byblos",
			EVENT_SUBTYPE_NEW_TRADE_ROUTE)
	}

	// pak i=12: weapons×15 /14mo y7m7 → ok 1013; refuse 1014; late 1015.
	if (!mission.event12_weapons_done && ev.years_since_start == 7 && ev.month == 7) {
		mission.event12_weapons_done = true
		log_info("akhenaten: mission 28 weapons×15 (i=12)")
		mission28_fire_request(2012, RESOURCE_WEAPONS, 15, 14, 1013, 1014, 1015, 0, 0, "Farafra Oasis")
	}
}

[es=event_advance_month, mission=mission28]
function mission28_timed_invasions(ev) {
	if (!mission.event6_beduin_done && ev.years_since_start == 2 && ev.month == 8) {
		mission.event6_beduin_done = true
		mission28_beduin_raid(6, 12, 3, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event7_enemy_done && ev.years_since_start == 10 && ev.month == 7) {
		mission.event7_enemy_done = true
		mission28_hittite_raid(7, 12, 9, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event36_beduin_done && ev.years_since_start == 12 && ev.month == 9) {
		mission.event36_beduin_done = true
		mission28_beduin_raid(36, 64, 7, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event37_beduin_done && ev.years_since_start == 15 && ev.month == 3) {
		mission.event37_beduin_done = true
		mission28_beduin_raid(37, 64, 2, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event38_beduin_done && ev.years_since_start == 20 && ev.month == 10) {
		mission.event38_beduin_done = true
		mission28_beduin_raid(38, 64, 7, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event39_beduin_done && ev.years_since_start == 23 && ev.month == 7) {
		mission.event39_beduin_done = true
		mission28_beduin_raid(39, 96, 6, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (!mission.event40_beduin_done && ev.years_since_start == 27 && ev.month == 0) {
		mission.event40_beduin_done = true
		mission28_beduin_raid(40, 96, 4, EVENT_ATTACK_TARGET_RANDOM)
	}
}

// Oil refuse → egypt×64 (pak i=5).
// Copper: KR leaf fires via request tags first; ladder starts next month (pak 17/20 → 18).
[es=event_request_cleared, mission=mission28]
function mission28_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	if (ev.tag_id == 2003 && outcome == "refuse" && !mission.oil_egypt_raid_done) {
		mission.oil_egypt_raid_done = true
		log_info("akhenaten: mission 28 egypt×64 after oil refuse (i=5)", {ev:ev})
		mission28_egypt_raid(5, 64, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 4)
		return
	}
	if (ev.tag_id == 2016 && !mission.copper_ladder_active && !mission.copper_ladder_pending) {
		mission.copper_ladder_pending = true
		log_info("akhenaten: mission 28 copper cleared → ladder pending after KR", {ev:ev, outcome:outcome})
	}
}

// Copper invasion ladder wipe poll: 32→64→72→24→96 then fire KR+25 leaf.
[es=event_advance_month, mission=mission28]
function mission28_copper_ladder_poll(ev) {
	if (mission.copper_ladder_pending && !mission.copper_ladder_active) {
		mission.copper_ladder_pending = false
		log_info("akhenaten: mission 28 copper ladder start (after KR leaf)")
		mission28_start_copper_ladder()
		return
	}
	if (!mission.copper_ladder_active) {
		return
	}
	if (city.num_enemy_formations > 0) {
		mission.copper_ladder_enemies_seen = true
		return
	}
	if (!mission.copper_ladder_enemies_seen) {
		return
	}
	mission.copper_ladder_enemies_seen = false
	mission.copper_ladder_step = mission.copper_ladder_step + 1
	var step = mission.copper_ladder_step
	if (step == 1) {
		mission28_hittite_raid(19, 64, 2, EVENT_ATTACK_TARGET_FOOD)
	} else if (step == 2) {
		mission28_hittite_raid(21, 72, 3, EVENT_ATTACK_TARGET_TROOPS)
	} else if (step == 3) {
		mission28_hittite_raid(22, 24, 9, EVENT_ATTACK_TARGET_FOOD)
	} else if (step == 4) {
		mission28_hittite_raid(23, 96, 3, EVENT_ATTACK_TARGET_RANDOM)
	} else {
		mission.copper_ladder_active = false
		log_info("akhenaten: mission 28 copper ladder complete → KR+25 (i=25)")
		__city_event_fire_chain(1025)
	}
}

// pak i=27→28→29: favour egypt×40 loc=1 → ×40 loc=2 → ×40 loc=8.
[es=event_advance_month, mission=mission28]
function mission28_pharaoh_favour_invasion(ev) {
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
			mission28_favour_wave(40, 28, 2, EVENT_ATTACK_TARGET_RANDOM)
			return
		}
		mission.pharaoh_favour_wave3_done = true
		// pak i=29 attack=0 FOOD
		mission28_favour_wave(40, 29, 8, EVENT_ATTACK_TARGET_FOOD)
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
	log_info("akhenaten: mission 28 favour egypt×40 (i=27)")
	mission28_favour_wave(40, 27, 1, EVENT_ATTACK_TARGET_RANDOM)
}
