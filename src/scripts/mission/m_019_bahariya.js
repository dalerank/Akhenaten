log_info("akhenaten: mission 19 bahariya started")

// Empire / invasions aligned with original campaign scenario 19 (2026-07-26 dump).
// Empire id=18. Enemy ENEMY_5_HYKSOS (scenario); timed enemy + beduin raids (Libyan sprites).
// Gods: Ra, Seth. Funds Normal 7500 / loan 2500 / debt 20.
// Win: pop 3000 / culture 15 / prosperity 25 / monuments 13 / kingdom 40 / housing 10.
// Monuments goal 13 (pak; Sun Temple weight 4). Burial empty.
// Trade: On(1) Iunet(2) Abu(3) Serabit(4). Display Dahshur(17). Men-nefer stub route 19.
// Triage: SKIP empty map_obj idx=10; SKIP orphan routes 5/6/7/25; omit river/disembark/inv points (pak 0).
// Events: no requests; invasions + economy + NEW_TRADE Dahshur (i=28) + favour×76 + gift after wipe i=26→27.
//
// Tag_id scheme:
//   1000 + i               chain-only leaves
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission19 { // Bahariya Oasis — The Western Desert
	map_file : "data/maps/m_019_bahariya.map"

	// Map points from data/maps/m_019_bahariya.map.
	herd_points_predator [ [92, 64] ]
	herd_points_prey [ [69, 70], [93, 97] ]

	start_message : "message_mission_bahariya_oasis"
	selection_title : "Bahariya"
	player_rank : 6

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 46]
	choice [
		{
			name : "Dunqul"
			id : 21
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 47]
			pos [620, 420]
		}
		{
			name : "Dakhla"
			id : 22
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 48]
			pos [640, 480]
		}
	]

	// pak Normal funds=7500 loan=2500 debt_interest=20 → int_dcy around Normal.
	initial_funds [15000, 10000, 7500, 5000, 4000]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/219_mission.mp3"
		victory : "Voice/Mission/219_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_CLAY_PIT,
		BUILDING_SUN_TEMPLE,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals vs pak; monuments 13 = Sun Temple weight 4.
	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 15 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : true, goal : 40 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [137, 67]
	exit_point [84, 14]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
cities [
		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_TIMBER ]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 3
			is_open : false
			cost_to_open : 800
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}

		{
			name : "Iunet"
			idx : 7
			pos : [783, 892]
			route : 2
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "On"
			idx : 12
			pos : [572, 454]
			route : 1
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 4000 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Serabit Khadim"
			idx : 14
			pos : [801, 552]
			route : 4
			is_open : false
			cost_to_open : 950
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_CLAY ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Dahshur"
			idx : 4
			pos : [578, 525]
			route : 17
			cost_to_open : 290
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Men-nefer"
			idx : 9
			pos : [542, 477]
			route : 19
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Dunqul Oasis"
			idx : 5
			pos : [795, 1191]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Henen-nesw"
			idx : 6
			pos : [534, 626]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kharga Oasis"
			idx : 8
			pos : [626, 1119]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Nekhen"
			idx : 11
			pos : [797, 1011]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 13
			pos : [523, 539]
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
				[592, 478], [610, 519], [607, 562], [611, 591], [608, 620], [600, 637],
				[592, 656], [581, 674], [553, 677], [427, 680], [396, 681]
			]
		}
		{
			route : 2
			type : 1
			points [
				[802, 911], [775, 922], [764, 909], [730, 881], [691, 850], [663, 827],
				[634, 808], [619, 804], [603, 813], [589, 811], [579, 798], [553, 740],
				[537, 725], [526, 721], [503, 713], [396, 684]
			]
		}
		{
			route : 3
			type : 1
			points [
				[885, 1172], [871, 1141], [869, 1100], [858, 1066], [849, 1042], [837, 1028],
				[808, 998], [749, 934], [652, 858], [586, 818], [565, 790], [547, 747],
				[541, 738], [529, 734], [448, 704], [395, 686]
			]
		}
		{
			route : 4
			type : 1
			points [
				[813, 565], [784, 565], [763, 556], [742, 545], [729, 520], [722, 503],
				[711, 493], [699, 491], [686, 500], [677, 525], [677, 547], [693, 576],
				[715, 603], [718, 619], [717, 630], [707, 647], [695, 663], [676, 684],
				[656, 697], [638, 706], [611, 703], [583, 706], [546, 706], [502, 699],
				[394, 681]
			]
		}
		{
			route : 17
			type : 1
			points [
				[593, 545], [576, 551], [568, 559], [565, 575], [564, 589], [556, 602],
				[540, 609], [523, 617], [498, 627], [468, 629], [460, 632], [446, 640],
				[431, 651], [423, 655], [417, 659], [396, 668]
			]
		}
		{
			// Men-nefer display — no pak polyline; 2-pt stub.
			route : 19
			type : 1
			deviation : 40
			points [ [542, 477], [372, 654] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [519, 491], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [498, 551], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [602, 443], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [611, 527], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [571, 594], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [511, 520], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [482, 507], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [821, 886], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [844, 1087], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [720, 913], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [785, 1327], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [631, 544], image : "pharaoh_general/empire_bits_00118" }
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
		event2_demand_done : false
		event6_price_done : false
		event8_demand_done : false
		event10_trade_done : false
		event16_water_last_year : -1
		event20_trade_done : false
		event28_trade_done : false

		event0_enemy_done : false
		event1_enemy_done : false
		event3_beduin_done : false
		event4_enemy_done : false
		event5_enemy_done : false
		event7_beduin_done : false
		event9_beduin_done : false
		event11_enemy_done : false
		event12_beduin_done : false
		event13_enemy_done : false
		event14_enemy_done : false
		event15_beduin_done : false
		event17_enemy_done : false
		event21_enemy_done : false
		event22_enemy_done : false
		event26_enemy_done : false

		event18_enemy_last_year : -1
		event19_beduin_last_year : -1
		event23_beduin_last_year : -1
		event24_enemy_last_year : -1

		gift_sandstone_wired : false
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission19_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission19_fire_simple_event(tag, type, resource, amount, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	city.create_chain_event(opts).execute()
}

function mission19_enemy_raid(invasion_id, size, attack_target, on_completed_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

function mission19_beduin_raid(invasion_id, size) {
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
}

function mission19_ensure_gift_leaf() {
	if (mission.gift_sandstone_wired) {
		return
	}
	mission.gift_sandstone_wired = true
	// pak i=27: gift sandstone×24 after wipe i=26.
	mission19_make_leaf(1027, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_SANDSTONE, 24, 2)
}

[es=event_mission_start, mission=mission19]
function mission19_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_SUN_TEMPLE_1)
	__image_request_pak(PACK_SUN_TEMPLE_2)
	__image_request_pak(PACK_SUN_TEMPLE_3)
	__image_request_pak(PACK_SUN_TEMPLE_EXTRA)
	mission_show_start_message(mission, "message_mission_bahariya_oasis")
	empire.set_id(18)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission19_ensure_gift_leaf()
}

function mission19_maybe_year_month(ev, year, month) {
	return ev.years_since_start == year && ev.month == month
}

[es=event_advance_month, mission=mission19]
function mission19_economy_and_invasions(ev) {
	// Economy once
	if (!mission.event2_demand_done && mission19_maybe_year_month(ev, 8, 0)) {
		mission.event2_demand_done = true
		mission19_fire_simple_event(2002, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 10)
	}
	if (!mission.event6_price_done && mission19_maybe_year_month(ev, 11, 9)) {
		mission.event6_price_done = true
		mission19_fire_simple_event(2006, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 5)
	}
	if (!mission.event8_demand_done && mission19_maybe_year_month(ev, 13, 7)) {
		mission.event8_demand_done = true
		mission19_fire_simple_event(2008, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GRAIN, 8)
	}
	if (!mission.event10_trade_done && mission19_maybe_year_month(ev, 14, 11)) {
		mission.event10_trade_done = true
		mission19_fire_simple_event(2010, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 9)
	}
	if (!mission.event20_trade_done && mission19_maybe_year_month(ev, 27, 4)) {
		mission.event20_trade_done = true
		mission19_fire_simple_event(2020, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 9)
	}
	if (!mission.event28_trade_done && mission19_maybe_year_month(ev, 1, 1)) {
		mission.event28_trade_done = true
		city.create_chain_event({
			tag_id: 2028,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 8,
			trigger: EVENT_TRIGGER_ONCE,
			subtype: EVENT_SUBTYPE_NEW_TRADE_ROUTE,
			city: "Dahshur"
		}).execute()
	}
	if (mission.event16_water_last_year != ev.years_since_start
			&& ev.years_since_start >= 39 && ev.month == 8) {
		mission.event16_water_last_year = ev.years_since_start
		mission19_fire_simple_event(3000 + 16 * 100 + ev.years_since_start,
			EVENT_TYPE_CONTAMINATED_WATER, undefined, 7)
	}

	// Timed enemy invasions (Hyksos pack = scenario enemy)
	// [pak_i, year, month, size, attack_target, gift_on_wipe]
	var enemy_once = [
		[0, 5, 9, 8, EVENT_ATTACK_TARGET_RANDOM, false],
		[1, 7, 4, 16, EVENT_ATTACK_TARGET_FOOD, false],
		[4, 9, 2, 32, EVENT_ATTACK_TARGET_VAULTS, false],
		[5, 11, 6, 64, EVENT_ATTACK_TARGET_BEST_BUILDINGS, false],
		[11, 17, 4, 80, EVENT_ATTACK_TARGET_TROOPS, false],
		[13, 21, 2, 96, EVENT_ATTACK_TARGET_VAULTS, false],
		[14, 22, 1, 48, EVENT_ATTACK_TARGET_BEST_BUILDINGS, false],
		[17, 26, 3, 80, EVENT_ATTACK_TARGET_TROOPS, false],
		[21, 31, 1, 64, EVENT_ATTACK_TARGET_VAULTS, false],
		[22, 31, 4, 96, EVENT_ATTACK_TARGET_BEST_BUILDINGS, false],
		[26, 2, 0, 8, EVENT_ATTACK_TARGET_BEST_BUILDINGS, true],
	]
	for (var i = 0; i < enemy_once.length; i++) {
		var e = enemy_once[i]
		var flag = "event" + e[0] + "_enemy_done"
		if (!mission[flag] && mission19_maybe_year_month(ev, e[1], e[2])) {
			mission[flag] = true
			var on_ok = e[5] ? 1027 : undefined
			if (on_ok) {
				mission19_ensure_gift_leaf()
			}
			log_info("akhenaten: mission 19 enemy raid i=" + e[0] + " size=" + e[3])
			mission19_enemy_raid(100 + e[0], e[3], e[4], on_ok)
		}
	}

	var beduin_once = [
		[3, 8, 10, 16],
		[7, 12, 3, 32],
		[9, 14, 0, 64],
		[12, 17, 9, 32],
		[15, 22, 6, 32],
	]
	for (var j = 0; j < beduin_once.length; j++) {
		var b = beduin_once[j]
		var bflag = "event" + b[0] + "_beduin_done"
		if (!mission[bflag] && mission19_maybe_year_month(ev, b[1], b[2])) {
			mission[bflag] = true
			log_info("akhenaten: mission 19 beduin raid i=" + b[0] + " size=" + b[3])
			mission19_beduin_raid(200 + b[0], b[3])
		}
	}

	// Recurring
	if (ev.years_since_start >= 26 && ev.month == 10
			&& mission.event18_enemy_last_year != ev.years_since_start) {
		mission.event18_enemy_last_year = ev.years_since_start
		mission19_enemy_raid(300 + ev.years_since_start, 48, EVENT_ATTACK_TARGET_RANDOM)
	}
	if (ev.years_since_start >= 27 && ev.month == 3
			&& mission.event19_beduin_last_year != ev.years_since_start) {
		mission.event19_beduin_last_year = ev.years_since_start
		mission19_beduin_raid(400 + ev.years_since_start, 32)
	}
	if (ev.years_since_start >= 31 && ev.month == 10
			&& mission.event23_beduin_last_year != ev.years_since_start) {
		mission.event23_beduin_last_year = ev.years_since_start
		mission19_beduin_raid(500 + ev.years_since_start, 48)
	}
	if (ev.years_since_start >= 46 && ev.month == 5
			&& mission.event24_enemy_last_year != ev.years_since_start) {
		mission.event24_enemy_last_year = ev.years_since_start
		mission19_enemy_raid(600 + ev.years_since_start, 64, EVENT_ATTACK_TARGET_RANDOM)
	}

	mission_pharaoh_favour_invasion_tick(mission, 76)
}
