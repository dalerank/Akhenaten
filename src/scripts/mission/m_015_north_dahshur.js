log_info("akhenaten: mission 15 north dahshur started")

mission15 { // North Dahshur — The True Pyramid
	map_file : "data/maps/m_015_north_dahshur.map"
	start_message : "message_mission_north_dahshur"
	selection_title : "North Dahshur"
	player_rank : 6

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 37]

	// Convergence of Buhen/S. Dahshur fork → choice Iunet (16) / On (17) → Rostja (18).
	choice [
		{
			name : "Iunet"
			id : 16
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 38]
			pos [620, 420]
		}

		{
			name : "On"
			id : 17
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 39]
			pos [640, 480]
		}
	]

	// pak Normal funds=10000 loan=4000 debt_interest=20 → int_dcy row (verified).
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [8000, 5300, 4000, 2700, 2100]
	debt_interest [10, 15, 20, 25, 30]
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
		briefing : "Voice/Mission/215_mission.mp3"
		victory : "Voice/Mission/215_victory.mp3"
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
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_HENNA_FARM,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT, BUILDING_WOOD_CUTTERS,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID,
		BUILDING_LARGE_PYRAMID,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 20 }
		prosperity    {enabled : true, goal : 30 }
		monuments     {enabled : true, goal : 32 }
		kingdom       {enabled : true, goal : 55 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from original campaign scenario 15 (invasion points omitted — none on map).
	entry_point [53, 16]
	exit_point [96, 113]
	river_entry_point [120, 87]
	river_exit_point [89, 21]
	disembark_points [ [-1, -1], [-1, -1], [87, 36] ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Dahshur"
			idx : 4
			pos : [568, 521]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_GEMS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
		}

		{
			name : "Selima Oasis"
			idx : 13
			pos : [608, 1355]
			route : 1
			is_open : false
			cost_to_open : 1500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 2
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS ]
			buys [ RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 3
			is_open : false
			cost_to_open : 1200
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Meidum"
			idx : 8
			pos : [572, 592]
			route : 4
			is_open : false
			cost_to_open : 300
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_STONE ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_STONE, limit: 4000 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
			]
		}

		{
			name : "Serabit Khadim"
			idx : 14
			pos : [801, 552]
			route : 5
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 9
			pos : [558, 463]
			route : 6
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Enkomi"
			idx : 5
			pos : [679, 49]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 6
			pos : [732, 1491]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
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
			idx : 11
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 12
			pos : [523, 539]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]
	// SKIP map_obj idx=10 empty stub.

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Selima Oasis land
			type : 1
			points [
				[619, 1375], [490, 1238], [399, 1120], [365, 1046], [339, 899], [337, 830],
				[353, 741], [376, 728], [409, 677], [518, 604], [553, 585], [565, 576], [578, 555]
			]
		}
		{
			route : 2 // Abu sea
			type : 2
			points [
				[885, 1162], [882, 1155], [885, 1138], [878, 1109], [882, 1098], [877, 1091],
				[879, 1076], [875, 1059], [864, 1050], [864, 1034], [848, 1020], [835, 1015],
				[824, 997], [815, 992], [814, 987], [818, 972], [816, 960], [828, 945],
				[819, 914], [812, 905], [801, 920], [788, 922], [774, 935], [759, 923],
				[757, 914], [743, 919], [720, 897], [720, 888], [704, 884], [676, 863],
				[676, 853], [655, 840], [655, 836], [639, 824], [631, 824], [624, 815],
				[612, 813], [596, 794], [596, 776], [584, 761], [584, 737], [570, 728],
				[565, 720], [571, 710], [571, 685], [572, 663], [583, 650], [592, 589], [591, 557]
			]
		}
		{
			route : 3 // Byblos sea
			type : 2
			points [
				[888, 93], [867, 117], [869, 139], [855, 205], [843, 286], [832, 305],
				[804, 319], [776, 338], [725, 341], [697, 358], [680, 363], [668, 364],
				[642, 356], [623, 378], [613, 388], [602, 397], [589, 400], [589, 417],
				[586, 421], [580, 429], [573, 432], [568, 441], [563, 462], [582, 539]
			]
		}
		{
			route : 4 // Meidum sea
			type : 2
			points [
				[600, 605], [594, 550]
			]
		}
		{
			route : 5 // Serabit Khadim land
			type : 1
			points [
				[804, 554], [777, 527], [738, 501], [707, 492], [682, 499], [652, 509], [605, 533]
			]
		}
		{
			route : 6 // Men-nefer display
			type : 1
			points [
				[597, 536], [588, 497]
			]
		}
	]
	// SKIP routes 7/8: pak polylines exist but no map_obj references them.

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [525, 494], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [503, 535], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [563, 575], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [730, 921], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [842, 1094], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [783, 1328], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [619, 553], image : "pharaoh_general/empire_bits_00118" }
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
		grain_kr_leaves_wired : false
		limestone_leaves_wired : false
		grain2_leaves_wired : false
		henna_leaves_wired : false

		event7_hyksos_done : false
		event10_hyksos_done : false

		hyksos_chain_active : false
		hyksos_chain_enemies_seen : false
		hyksos_chain_alt : 0
		hyksos_chain_invasion_seq : 10

		event2_grain_last_year : -1
		event3_gift_last_year : -1
		event5_grain_last_year : -1
		event6_beduin_last_year : -1
		event11_henna_last_year : -1
		clay_pit_flood_last_year : -1
		grain_recurring_was_busy : false
		grain_recurring_idle_since_abs : -1
		grain2_recurring_was_busy : false
		grain2_recurring_idle_since_abs : -1
		henna_recurring_was_busy : false
		henna_recurring_idle_since_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false

		start_message_shown : false
	}
}

function mission15_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission15_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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

function mission15_hyksos_raid(invasion_id, size, attack_target) {
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

function mission15_beduin_raid(invasion_id, size) {
	// pak invader=beduins; sprites match Serabit beduin pattern (Libyan pack).
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

// pak i=2 grain tails: ok→20→23 gift stone×48; refuse→21 KR−10; late→22 gift stone×24.
function mission15_ensure_grain_kr_leaves() {
	if (mission.grain_kr_leaves_wired) {
		return
	}
	mission.grain_kr_leaves_wired = true
	var kr_ok = mission15_make_leaf(1020, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission15_make_leaf(1021, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2)
	mission15_make_leaf(1022, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_STONE, 24, 2)
	mission15_make_leaf(1023, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_STONE, 48, 2)
	kr_ok.set_completed_action_tag(1023)
}

// pak i=3 gift stone×48 → i=4 limestone×24: ok→17 KR+6; refuse→18 KR−12→24 demand stone−8; late→19 KR−1.
function mission15_ensure_limestone_leaves() {
	if (mission.limestone_leaves_wired) {
		return
	}
	mission.limestone_leaves_wired = true
	mission15_make_leaf(1017, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2)
	var kr_refuse = mission15_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
	mission15_make_leaf(1019, EVENT_TYPE_REPUTATION_DECREASE, undefined, 1, 2)
	mission15_make_leaf(1024, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_STONE, 8, 2)
	kr_refuse.set_completed_action_tag(1024)

	var limestone = city.create_good_request({
		tag_id: 1004, resource: RESOURCE_LIMESTONE, amount: 24, months_initial: 24,
		subtype: 4, trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	limestone.set_sender_faction(0)
	limestone.set_completed_action_tag(1017)
	limestone.set_refusal_action_tag(1018)
	limestone.set_too_late_action_tag(1019)
}

// pak i=5 grain×18 tails: ok→25→28 copper gift; refuse→26→29 LOST_TRADE Kerma; late→27.
function mission15_ensure_grain2_leaves() {
	if (mission.grain2_leaves_wired) {
		return
	}
	mission.grain2_leaves_wired = true
	var kr_ok = mission15_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 3, 2)
	var kr_refuse = mission15_make_leaf(1026, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2)
	mission15_make_leaf(1027, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	mission15_make_leaf(1028, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 24, 2)
	mission15_make_leaf(1029, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Kerma")
	kr_ok.set_completed_action_tag(1028)
	kr_refuse.set_completed_action_tag(1029)
}

// pak i=11 henna tails (skip MESSAGE i=12/15): ok→KR+25 (i16); refuse→KR−40 (i13);
// late→KR−20 (i14). i=30 INVASION no-op → Hyksos×12 via event_request_cleared.
function mission15_ensure_henna_leaves() {
	if (mission.henna_leaves_wired) {
		return
	}
	mission.henna_leaves_wired = true
	mission15_make_leaf(1016, EVENT_TYPE_REPUTATION_INCREASE, undefined, 25, 2)
	mission15_make_leaf(1013, EVENT_TYPE_REPUTATION_DECREASE, undefined, 40, 2)
	mission15_make_leaf(1014, EVENT_TYPE_REPUTATION_DECREASE, undefined, 20, 2)
}

function mission15_is_henna_request_tag(tag) {
	return Math.floor((tag - 3000) / 100) == 11
}

[es=event_mission_start, mission=mission15]
function mission15_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_LIBIAN) // beduin sprites
	__image_request_pak(PACK_ENEMY_EGYPTIAN) // favour
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	__image_request_pak(PACK_PYRAMID)
	mission_show_start_message(mission, "message_mission_north_dahshur")
	empire.set_id(14)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	mission15_ensure_grain_kr_leaves()
	mission15_ensure_limestone_leaves()
	mission15_ensure_grain2_leaves()
	mission15_ensure_henna_leaves()
}

// pak i=0/1: CLAY_PIT_FLOOD amount=8 (reinterpret year=24 junk as annual from y1m0).
// Each event floods ceil(clay_pit_count * amount / 100) random VALID pits (amount = %).
[es=event_advance_month, mission=mission15]
function mission15_clay_pit_flood_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 0) {
		return
	}
	if (mission.clay_pit_flood_last_year == ev.years_since_start) {
		return
	}
	mission.clay_pit_flood_last_year = ev.years_since_start

	// Two pak events, both amount=8 → two 8% waves per year.
	var percents = [8, 8]
	var y = ev.years_since_start
	var fired = 0
	for (var w = 0; w < percents.length; w++) {
		var total = city.count_total_buildings(BUILDING_CLAY_PIT)
		if (total <= 0) {
			break
		}
		var n = Math.floor((total * percents[w] + 99) / 100) // ceil(total * pct / 100)
		for (var i = 0; i < n; i++) {
			city.create_chain_event({
				tag_id: 4000 + y * 20 + w * 10 + i,
				type: EVENT_TYPE_CLAY_PIT_FLOOD,
				amount: percents[w],
				trigger: EVENT_TRIGGER_ONCE
			}).execute()
			fired = fired + 1
		}
	}
	if (fired > 0) {
		log_info("akhenaten: mission 15 north dahshur clay pit floods y" + y + " n=" + fired, {ev:ev})
	}
}

// pak i=11: henna once y24m1 amount=8 → biennial from y2m1, amount=12 (player), 24mo.
[es=event_advance_month, mission=mission15]
function mission15_event_i11_henna_recurring(ev) {
	if (ev.years_since_start < 2 || (ev.years_since_start % 2) != 0 || ev.month != 1) {
		return
	}
	if (mission.event11_henna_last_year == ev.years_since_start) {
		return
	}
	var abs_month = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_HENNA, "henna_recurring", abs_month)) {
		return
	}
	mission.event11_henna_last_year = ev.years_since_start
	mission15_ensure_henna_leaves()
	log_info("akhenaten: mission 15 north dahshur henna×12 y" + ev.years_since_start, {ev:ev})
	mission15_fire_request(3000 + 11 * 100 + ev.years_since_start, RESOURCE_HENNA, 12, 24,
		1016, 1013, 1014, 2, 1)
}

// pak i=2: grain×8 / 18mo recurring from y4m0, sender=pharaoh.
[es=event_advance_month, mission=mission15]
function mission15_event_i2_grain_recurring(ev) {
	if (ev.years_since_start < 4) {
		return
	}
	if (mission.event2_grain_last_year == ev.years_since_start) {
		return
	}
	var abs_month = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs_month)) {
		return
	}
	mission.event2_grain_last_year = ev.years_since_start
	mission15_ensure_grain_kr_leaves()
	mission15_fire_request(3000 + 2 * 100 + ev.years_since_start, RESOURCE_GRAIN, 8, 18, 1020, 1021, 1022, 0, 1)
}

// pak i=3: stone gift×48 recurring from y13m3 → chains limestone×24 (i=4).
[es=event_advance_month, mission=mission15]
function mission15_event_i3_stone_gift_recurring(ev) {
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 3)) {
		return
	}
	if (mission.event3_gift_last_year == ev.years_since_start) {
		return
	}
	mission.event3_gift_last_year = ev.years_since_start
	mission15_ensure_limestone_leaves()
	var gift = city.create_chain_event({
		tag_id: 3000 + 3 * 100 + ev.years_since_start,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_STONE,
		amount: 48,
		trigger: EVENT_TRIGGER_ONCE
	})
	gift.set_param("months_initial", 2)
	gift.set_completed_action_tag(1004)
	gift.execute()
}

// pak i=5: grain×18 / 18mo recurring from y17m4.
[es=event_advance_month, mission=mission15]
function mission15_event_i5_grain_recurring(ev) {
	if (ev.years_since_start < 17 || (ev.years_since_start == 17 && ev.month < 4)) {
		return
	}
	if (mission.event5_grain_last_year == ev.years_since_start) {
		return
	}
	var abs_month = ev.years_since_start * 12 + ev.month
	// Separate idle gate from i=2 so late-game grain does not block early grain.
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain2_recurring", abs_month)) {
		return
	}
	mission.event5_grain_last_year = ev.years_since_start
	mission15_ensure_grain2_leaves()
	mission15_fire_request(3000 + 5 * 100 + ev.years_since_start, RESOURCE_GRAIN, 18, 18, 1025, 1026, 1027, 5, 0)
}

// pak i=7: Hyksos size=5 once y3m11 → activates size6↔6 chain (i=8/i=9).
[es=event_advance_month, mission=mission15]
function mission15_event_i7_hyksos_invasion(ev) {
	if (mission.event7_hyksos_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 11)) {
		return
	}
	mission.event7_hyksos_done = true
	mission.hyksos_chain_active = true
	mission.hyksos_chain_enemies_seen = false
	mission.hyksos_chain_alt = 0
	log_info("akhenaten: mission 15 hyksos invasion size=5 year=3", {ev:ev})
	mission15_hyksos_raid(0, 5, EVENT_ATTACK_TARGET_FOOD)
}

// After i=7 wipe: keep spawning size=6 alternating attack FOOD ↔ BEST_BUILDINGS (pak i=9/i=8).
[es=event_advance_month, mission=mission15]
function mission15_hyksos_chain_tick(ev) {
	if (!mission.hyksos_chain_active) {
		return
	}
	var enemies = city.num_enemy_formations
	if (enemies > 0) {
		mission.hyksos_chain_enemies_seen = true
		return
	}
	if (!mission.hyksos_chain_enemies_seen) {
		return
	}
	mission.hyksos_chain_enemies_seen = false
	var attack = (mission.hyksos_chain_alt % 2 == 0)
		? EVENT_ATTACK_TARGET_BEST_BUILDINGS
		: EVENT_ATTACK_TARGET_FOOD
	mission.hyksos_chain_alt = mission.hyksos_chain_alt + 1
	mission.hyksos_chain_invasion_seq = mission.hyksos_chain_invasion_seq + 1
	log_info("akhenaten: mission 15 hyksos chain size=6 alt=" + mission.hyksos_chain_alt, {ev:ev})
	mission15_hyksos_raid(mission.hyksos_chain_invasion_seq, 6, attack)
}

// pak i=6: beduin size=10 recurring from y6m8, attack=RANDOM.
[es=event_advance_month, mission=mission15]
function mission15_event_i6_beduin_recurring(ev) {
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 8)) {
		return
	}
	if (mission.event6_beduin_last_year == ev.years_since_start) {
		return
	}
	mission.event6_beduin_last_year = ev.years_since_start
	log_info("akhenaten: mission 15 beduin raid size=10 year=" + ev.years_since_start, {ev:ev})
	mission15_beduin_raid(2 + ev.years_since_start, 10)
}

// pak i=10: Hyksos size=11 once y20m7, attack=VAULTS.
[es=event_advance_month, mission=mission15]
function mission15_event_i10_hyksos_invasion(ev) {
	if (mission.event10_hyksos_done) {
		return
	}
	if (ev.years_since_start < 20 || (ev.years_since_start == 20 && ev.month < 7)) {
		return
	}
	mission.event10_hyksos_done = true
	log_info("akhenaten: mission 15 hyksos invasion size=11 year=20", {ev:ev})
	mission15_hyksos_raid(3, 11, EVENT_ATTACK_TARGET_VAULTS)
}

// Factual request close — pak i=30 Hyksos×12 after henna refuse/late (INVASION no-op).
// Leaf KR still via wired on_* tags. Tags = 3000+11*100+year (biennial).
[es=event_request_cleared, mission=mission15]
function mission15_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	if (!mission15_is_henna_request_tag(ev.tag_id)) {
		return
	}
	if (outcome != "refuse" && outcome != "late") {
		return
	}
	log_info("akhenaten: mission 15 henna " + outcome + " → hyksos×12 tag=" + ev.tag_id, {ev:ev})
	mission15_hyksos_raid(30, 12, EVENT_ATTACK_TARGET_FOOD)
}

// Favour: pak i=31 size=75 by_favour (no chain child).
[es=event_advance_month, mission=mission15]
function mission15_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 75)
}
