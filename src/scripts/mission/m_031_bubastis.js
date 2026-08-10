log_info("akhenaten: mission 31 bubastis started")

mission31 { // Bubastis — The City of Bast
	map_file : "data/maps/m_031_bubastis.map"
	start_message : "message_mission_bubastis"
	selection_title : "Bubastis"
	player_rank : 10

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 64]
	choice [
		{
			name : "Khmun"
			id : 32
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 65]
			pos [620, 420]
		}
		{
			name : "Sauty"
			id : 33
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 66]
			pos [640, 480]
		}
	]

	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [0, 0, 0, 0, 0]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		// pak animals=0; enable so prey/herd update after create_herds (hunting lodge).
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/231_mission.mp3"
		victory : "Voice/Mission/231_victory.mp3"
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
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
		BUILDING_LARGE_OBELISK,
	]

	win_criteria {
		population    {enabled : false, goal : 0 }
		culture       {enabled : true, goal : 85 }
		prosperity    {enabled : true, goal : 85 }
		monuments     {enabled : true, goal : 15 }
		kingdom       {enabled : true, goal : 65 }
		housing_count {enabled : true, goal : 4 }
		housing_level {enabled : true, goal : 19 }
	}

	entry_point [129, 80]
	exit_point [81, 128]
	river_entry_point [18, 86]
	river_exit_point [120, 50]
	// pak: sole valid disembark at sparse i=2; inv_land/sea empty.
	disembark_points [ [-1, -1], [-1, -1], [51, 72] ]
	// pak fish sparse i=3 empty; herd FIGURE_NONE; prey ×4. Config-only (omit → empty).
	fishing_points [
		[75, 55], [64, 54], [67, 48], [-1, -1], [19, 83]
	]
	herd_points_predator [
		[27, 87], [98, 43], [124, 58], [86, 34]
	]
	herd_points_prey [
		[91, 38], [127, 63], [26, 92], [80, 39]
	]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Bubastis"
			idx : 0
			pos : [573, 416]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_FISH, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_FLAX, RESOURCE_TIMBER, RESOURCE_REEDS ]
			buys [ RESOURCE_BEER, RESOURCE_LUXURY_GOODS, RESOURCE_GRANITE ]
		}
		{
			name : "Heh"
			idx : 3
			pos : [698, 1414]
			route : 6
			is_open : false
			cost_to_open : 1750
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_WEAPONS, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_WEAPONS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Iken"
			idx : 4
			pos : [735, 1380]
			route : 5
			is_open : false
			cost_to_open : 1750
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BEER ]
			buys [ RESOURCE_WEAPONS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 4000 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
			]
		}
		{
			name : "Pwenet"
			idx : 11
			pos : [1133, 1325]
			route : 1
			is_open : false
			cost_to_open : 1500
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
			]
		}
		{
			name : "Sawu"
			idx : 12
			pos : [907, 834]
			route : 3
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}
		{
			name : "Waset"
			idx : 14
			pos : [811, 968]
			route : 4
			is_open : false
			cost_to_open : 800
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}
		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 0
			type : EMPIRE_CITY_FOREIGN
		}
		{
			// Heaven: warships unlock; export papyrus/wood/linen; import beer/luxury elsewhere.
			// Pak sells/buys empty — Levant pattern (cf. Sharuhen): clay/copper sell;
			// buys linen/papyrus/timber as Bubastis export sink (not timber sell).
			name : "Gaza"
			idx : 2
			pos : [846, 280]
			route : 2
			is_open : false
			cost_to_open : 500
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_COPPER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}
		{
			name : "Itjtawy"
			idx : 5
			pos : [584, 560]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Kebet"
			idx : 6
			pos : [829, 900]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			// Unlocked via troops ok → NEW_TRADE (pak i=1). Pak sells/buys empty —
			// standard Kerma luxury/linen (Waset/Iken); +beer/timber/granite for demand leaves.
			// pak route=0 → remake route 7 (polyline from Kerma → Bubastis).
			name : "Kerma"
			idx : 7
			pos : [732, 1491]
			route : 7
			is_open : false
			cost_to_open : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_BEER, RESOURCE_TIMBER, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 8
			pos : [545, 487]
			route : 19
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Menat Khufu"
			idx : 9
			pos : [578, 720]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Toshka"
			idx : 13
			pos : [789, 1298]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	routes [
		{
			route : 1
			type : 1
			points [
				[1127, 1333], [1114, 1316], [1168, 1252], [1115, 1193], [1096, 1084], [1053, 986],
				[1024, 908], [1006, 905], [945, 842], [922, 840], [864, 786], [830, 702],
				[719, 606], [663, 514], [598, 448], [597, 448]
			]
		}
		{
			route : 2
			type : 2
			points [
				[862, 295], [776, 343], [744, 340], [701, 358], [681, 370], [644, 356],
				[632, 368], [649, 384], [652, 404], [635, 420], [621, 431], [607, 441],
				[601, 445], [601, 445]
			]
		}
		{
			route : 3
			type : 1
			points [
				[908, 841], [851, 793], [685, 619], [601, 470], [596, 443], [596, 443]
			]
		}
		{
			route : 4
			type : 1
			points [
				[832, 983], [839, 949], [826, 895], [829, 873], [778, 727], [666, 613],
				[598, 482], [597, 445], [597, 445]
			]
		}
		{
			route : 5
			type : 2
			points [
				[766, 1408], [786, 1387], [800, 1364], [802, 1345], [847, 1303], [865, 1321],
				[878, 1302], [900, 1245], [905, 1228], [890, 1209], [897, 1180], [883, 1159],
				[889, 1127], [881, 1099], [864, 1047], [847, 1019], [835, 1014], [826, 999],
				[816, 958], [830, 944], [813, 907], [775, 935], [755, 914], [742, 917],
				[736, 903], [637, 821], [611, 811], [598, 793], [576, 731], [567, 715],
				[573, 658], [599, 611], [588, 527], [567, 502], [576, 470], [599, 447],
				[599, 447]
			]
		}
		{
			route : 6
			type : 2
			points [
				[727, 1443], [711, 1319], [834, 1235], [776, 990], [584, 820], [541, 673],
				[586, 603], [561, 480], [596, 450], [596, 450]
			]
		}
		{
			// Remake: Kerma NEW_TRADE (pak route 0). Start at Kerma, then Heh-like sea path north.
			route : 7
			type : 2
			points [
				[732, 1491], [727, 1443], [711, 1319], [834, 1235], [776, 990], [584, 820],
				[541, 673], [586, 603], [561, 480], [596, 450], [596, 450]
			]
		}
		{
			route : 25
			type : 1
			points [
				[559, 505], [598, 458]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [534, 426], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [418, 650], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [485, 514], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [547, 566], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [615, 712], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [634, 714], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [511, 485], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [590, 457], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [600, 512], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [499, 557], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [569, 598], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [614, 739], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [511, 533], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [577, 495], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [847, 976], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [825, 1194], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [781, 1324], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [380, 1041], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [881, 901], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [861, 901], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [819, 883], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [670, 889], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 1089], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 961], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [725, 1386], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [877, 843], image : "pharaoh_general/empire_bits_00125" }
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
		{ name : "#upper_egypt", pos : [691, 997] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]
	vars {
		misc_leaves_wired : false
		event0_troops_done : false
		event6_timber_armed : false
		event9_weapons_done : false
		event13_fish_armed : false
		gaza_trade_done : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_enemies_seen2 : false
		pharaoh_favour_wave1_abs : -1
		pharaoh_favour_wave2_abs : -1
		timber_recurring_was_busy : false
		timber_recurring_idle_since_abs : -1
		fish_recurring_was_busy : false
		fish_recurring_idle_since_abs : -1
		start_message_shown : false
	}
}

function mission31_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) { opts.resource = resource }
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) { leaf.set_param("months_initial", months) }
	return leaf
}

function mission31_make_chain_request(tag, resource, amount, months, subtype, sender_faction, city_name) {
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
	request.set_sender_faction(sender_faction === undefined ? 0 : sender_faction)
	return request
}

function mission31_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, sender_faction, city_name, defeat_tag) {
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
	request.set_sender_faction(sender_faction === undefined ? 0 : sender_faction)
	if (ok_tag !== undefined && ok_tag > 0) { request.set_completed_action_tag(ok_tag) }
	if (refuse_tag !== undefined && refuse_tag > 0) { request.set_refusal_action_tag(refuse_tag) }
	if (late_tag !== undefined && late_tag > 0) { request.set_too_late_action_tag(late_tag) }
	if (defeat_tag !== undefined && defeat_tag > 0) { request.set_defeat_action_tag(defeat_tag) }
	request.event_is_active = true
	return request
}

function mission31_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) { opts.resource = resource }
	if (city_name !== undefined) { opts.city = city_name }
	if (subtype !== undefined) { opts.subtype = subtype }
	var ev = city.create_chain_event(opts)
	ev.event_is_active = true
	return ev
}

// pak location_fields = 1-based land invasion index (MAX 8).
// inv_land/sea empty; favour i=17/18/19 use loc 1/2/3 — distinct landfalls via
// entry / disembark[2] / exit (Egyptian unset → map entry).
function mission31_loc_tile(loc) {
	if (loc == 1) {
		return [129, 80] // entry_point (east)
	}
	if (loc == 2) {
		return [51, 72] // disembark sparse i=2
	}
	if (loc == 3) {
		return [81, 128] // exit_point
	}
	return [-1, -1]
}

function mission31_egypt_raid(invasion_id, size, attack_target, loc) {
	var tile = mission31_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 31 egypt raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		amount: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: 0,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	})
}

function mission31_ensure_shared_leaves() {
	if (mission.misc_leaves_wired) { return }
	mission.misc_leaves_wired = true

	// pak i=7/8: timber ok → demand+ beer×18 Kerma; refuse/late → demand− beer×8 Kerma (item=15)
	mission31_make_leaf(1007, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BEER, 18, 2, undefined, "Kerma")
	mission31_make_leaf(1008, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_BEER, 8, 2, undefined, "Kerma")
	// pak i=10/11: weapons ok/refuse → demand+ luxury×7 Kebet; late → demand− timber×8 Kerma
	mission31_make_leaf(1010, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LUXURY_GOODS, 7, 2, undefined, "Kebet")
	mission31_make_leaf(1011, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_TIMBER, 8, 2, undefined, "Kerma")
	// pak i=14/15/16: fish ok → demand+ granite×5 Heh; refuse → demand− granite×7 Kerma; late → KR−3
	mission31_make_leaf(1014, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_GRANITE, 5, 2, undefined, "Heh")
	mission31_make_leaf(1015, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GRANITE, 7, 2, undefined, "Kerma")
	mission31_make_leaf(1016, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)

	// Troops ladder (pak i=0..5):
	// i=0 troops×32 once: ok→1 NEW Kerma; refuse→2; late/defeat→3
	// i=1 NEW_TRADE Kerma
	// i=2 troops×48: ok→1; refuse→5 MESSAGE; late/defeat→3
	// i=3 troops×16 Heh: ok→1; refuse→2; late/defeat→4
	// i=4 troops×8: ok→1; refuse→2; late/defeat→3
	// i=5 MESSAGE amount=17 subtype=2 (distant_battle_lost) → Iken
	// Orphan i=12 MESSAGE skipped (no parent ok/refuse/late).
	mission31_make_leaf(1001, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 12, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
	mission31_make_leaf(1005, EVENT_TYPE_MESSAGE, undefined, 17, 2,
		EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, "Iken")
	var t2 = mission31_make_chain_request(1002, RESOURCE_TROOPS, 48, 12, 1, 0, "Itjtawy")
	var t3 = mission31_make_chain_request(1003, RESOURCE_TROOPS, 16, 12, 1, 0, "Heh")
	var t4 = mission31_make_chain_request(1004, RESOURCE_TROOPS, 8, 12, 1, 0, "Itjtawy")
	t2.set_completed_action_tag(1001)
	t2.set_refusal_action_tag(1005)
	t2.set_too_late_action_tag(1003)
	t2.set_defeat_action_tag(1003)
	t3.set_completed_action_tag(1001)
	t3.set_refusal_action_tag(1002)
	t3.set_too_late_action_tag(1004)
	t3.set_defeat_action_tag(1004)
	t4.set_completed_action_tag(1001)
	t4.set_refusal_action_tag(1002)
	t4.set_too_late_action_tag(1003)
	t4.set_defeat_action_tag(1003)
}

[es=event_mission_start, mission=mission31]
function mission31_on_start(ev) {
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_OBELISK_EXTRA)
	__image_request_pak(PACK_OBELISK_X5_A)
	__image_request_pak(PACK_OBELISK_X5_B)
	__image_request_pak(PACK_OBELISK_X5_C)
	__image_request_pak(PACK_OBELISK_X5_D)
	__image_request_pak(PACK_OBELISK_X5_E)
	__image_request_pak(PACK_OBELISK_X5_F)
	mission_show_start_message(mission, "message_mission_bubastis")
	empire.set_id(20)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_0_BARBARIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission31_ensure_shared_leaves()
}

[es=event_advance_month, mission=mission31]
function mission31_requests_and_events(ev) {
	mission31_ensure_shared_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_TIMBER, "timber_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_FISH, "fish_recurring", abs)

	// pak i=0: troops×32 /12mo y5 → Itjtawy; ok→1001 Kerma; refuse→1002; late/defeat→1003
	if (!mission.event0_troops_done && ev.years_since_start == 5 && ev.month == 0) {
		mission.event0_troops_done = true
		log_info("akhenaten: mission 31 troops x32 Itjtawy")
		mission31_fire_request(2000, RESOURCE_TROOPS, 32, 12, 1001, 1002, 1003, 1, 0, "Itjtawy", 1003)
	}

	// pak i=6: timber×24 recurring from y8m8 — unique tag per year (Sawu pattern)
	// pak i=6: timber×24 recurring from y8m8 — unique tag per year (Sawu pattern)
	if (!mission.event6_timber_armed && ev.years_since_start == 8 && ev.month == 8) {
		mission.event6_timber_armed = true
	}
	if (mission.event6_timber_armed && ev.month == 8
		&& mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber_recurring", abs)) {
		log_info("akhenaten: mission 31 timber x24 recurring")
		mission31_fire_request(3000 + 6 * 100 + ev.years_since_start,
			RESOURCE_TIMBER, 24, 12, 1007, 1008, 1008, 0, 0, "Itjtawy")
	}

	// pak i=9: weapons×8 /18mo y10m7
	if (!mission.event9_weapons_done && ev.years_since_start == 10 && ev.month == 7) {
		mission.event9_weapons_done = true
		log_info("akhenaten: mission 31 weapons x8")
		mission31_fire_request(2009, RESOURCE_WEAPONS, 8, 18, 1010, 1010, 1011, 0, 0, "Kebet")
	}

	// pak i=13: fish×12 recurring from y6m2 — unique tag per year
	if (!mission.event13_fish_armed && ev.years_since_start == 6 && ev.month == 2) {
		mission.event13_fish_armed = true
	}
	if (mission.event13_fish_armed && ev.month == 2
		&& mission_recurring_request_may_fire(mission, RESOURCE_FISH, "fish_recurring", abs)) {
		log_info("akhenaten: mission 31 fish x12 recurring")
		mission31_fire_request(3000 + 13 * 100 + ev.years_since_start,
			RESOURCE_FISH, 12, 12, 1014, 1015, 1016, 0, 0, "Kerma")
	}

	// Heaven TEMP: ≥2 active warship wharves → NEW_TRADE Gaza (no distant_battle in pak)
	if (!mission.gaza_trade_done && city.count_active_buildings(BUILDING_WARSHIP_WHARF) >= 2) {
		mission.gaza_trade_done = true
		log_info("akhenaten: mission 31 NEW_TRADE Gaza (warship wharves)")
		mission31_fire_simple_event(2020, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 1, "Gaza",
			EVENT_SUBTYPE_NEW_TRADE_ROUTE)
	}

	// pak i=17-19: favour egypt×50 → ×50 → ×20; loc 1 / 2 / 3 (KR < 30 like Heh)
	// Timeout 3 months if spawn fails (enemies never seen) so chain does not stall.
	if (!mission.pharaoh_favour_invasion_done && city.rating_kingdom < 30) {
		mission.pharaoh_favour_invasion_done = true
		mission.pharaoh_favour_wave1_abs = abs
		log_info("akhenaten: mission 31 favour egypt x50")
		mission31_egypt_raid(17, 50, EVENT_ATTACK_TARGET_RANDOM, 1)
	}
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave2_done) {
		if (!mission.pharaoh_favour_enemies_seen) {
			if (city.num_enemy_formations > 0) {
				mission.pharaoh_favour_enemies_seen = true
			} else if (mission.pharaoh_favour_wave1_abs >= 0
					&& abs - mission.pharaoh_favour_wave1_abs >= 3) {
				mission.pharaoh_favour_wave2_done = true
				mission.pharaoh_favour_wave2_abs = abs
				log_info("akhenaten: mission 31 favour egypt x50 wave2 (spawn timeout)")
				mission31_egypt_raid(18, 50, EVENT_ATTACK_TARGET_FOOD, 2)
			}
		} else if (city.num_enemy_formations == 0) {
			mission.pharaoh_favour_wave2_done = true
			mission.pharaoh_favour_wave2_abs = abs
			log_info("akhenaten: mission 31 favour egypt x50 wave2")
			mission31_egypt_raid(18, 50, EVENT_ATTACK_TARGET_FOOD, 2)
		}
	}
	if (mission.pharaoh_favour_wave2_done && !mission.pharaoh_favour_wave3_done) {
		if (!mission.pharaoh_favour_enemies_seen2) {
			if (city.num_enemy_formations > 0) {
				mission.pharaoh_favour_enemies_seen2 = true
			} else if (mission.pharaoh_favour_wave2_abs >= 0
					&& abs - mission.pharaoh_favour_wave2_abs >= 3) {
				mission.pharaoh_favour_wave3_done = true
				log_info("akhenaten: mission 31 favour egypt x20 wave3 (spawn timeout)")
				mission31_egypt_raid(19, 20, EVENT_ATTACK_TARGET_FOOD, 3)
			}
		} else if (city.num_enemy_formations == 0) {
			mission.pharaoh_favour_wave3_done = true
			log_info("akhenaten: mission 31 favour egypt x20 wave3")
			mission31_egypt_raid(19, 20, EVENT_ATTACK_TARGET_FOOD, 3)
		}
	}
}
