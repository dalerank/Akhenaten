log_info("akhenaten: mission 10 saqqara started")

// Empire / requests / events verified vs mission1.pak scenario 10 (2026-07-25 dump).
// Favour Pharaoh army size=69 (by_favour, attack=RANDOM) via mission_pharaoh_favour_invasion_tick.

mission10 { // Saqqara â€” The First Pyramid
	map_file : "data/maps/m_010_saqqara.map"

	// Map points from data/maps/m_010_saqqara.map; fixed counts for year-1 gamemeat request.
	herd_points_predator [
		{ tile: [81, 152], type: FIGURE_HYENA, count: 5, radius: 16 }
	]
	herd_points_prey [
		{ tile: [50, 73], type: FIGURE_OSTRICH, count: 5, radius: 16 }
		{ tile: [93, 116], type: FIGURE_OSTRICH, count: 5, radius: 16 }
		{ tile: [138, 96], type: FIGURE_OSTRICH, count: 5, radius: 16 }
		{ tile: [154, 77], type: FIGURE_OSTRICH, count: 5, radius: 16 }
	]

	start_message : "message_history_saqqara"
	selection_title : "Saqqara"
	player_rank : 1

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 28]

	choice [
		{
			name : "Serabit Khadim"
			id : 11
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 29]
			pos [620, 420]
		}

		{
			name : "Meidum"
			id : 12
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 30]
			pos [640, 480]
		}
	]

	// pak Normal funds=12000 loan=5200 debt_interest=8 â†’ int_dcy around Normal.
	initial_funds [24000, 16000, 12000, 8000, 6400]
	rescue_loans [10400, 7000, 5200, 3500, 2800]
	debt_interest [4, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		bricks: { type:RESOURCE_BRICKS, allow: true},
	}

	env {
		has_animals : true
		hide_nilometer : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/210_mission.mp3"
		victory : "Voice/Mission/210_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY,
		BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA, BUILDING_BRICKS_WORKSHOP,
		BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_WEAVER_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET,
		BUILDING_POMEGRANATES_FARM,
		BUILDING_STONE_QUARRY, BUILDING_GOLD_MINE,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_MEDIUM_STEPPED_PYRAMID, BUILDING_SMALL_MASTABA,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals match mission1.pak scenario 10.
	win_criteria {
		population    {enabled : true, goal : 3500 }
		culture       {enabled : false }
		prosperity    {enabled : true, goal : 15 }
		monuments     {enabled : true, goal : 19 }
		kingdom       {enabled : true, goal : 50 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 10 (no disembark / invasion points).
	entry_point [130, 123]
	exit_point [41, 44]
	river_entry_point [159, 94]
	river_exit_point [157, 96]

	enable_scenario_events : true

	// Empire from mission1.pak scenario 10 (empire id=1) â€” full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Saqqara"
			idx : 8
			pos : [523, 539]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_POMEGRANATES, RESOURCE_GAMEMEAT, RESOURCE_STONE ]
			buys [ RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE ]
		}

		{
			name : "Men-nefer"
			idx : 5
			pos : [552, 467]
			route : 1
			is_open : false
			cost_to_open : 150
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Selima Oasis"
			idx : 9
			pos : [618, 1362]
			route : 2
			is_open : false
			cost_to_open : 645
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
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "Kerma"
			idx : 3
			pos : [726, 1493]
			route : 3
			is_open : false
			cost_to_open : 780
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
			]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 4
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Abedju"
			idx : 1
			pos : [696, 907]
			route : 5
			is_open : false
			cost_to_open : 350
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_GAMEMEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 1500 }
			]
		}

		{
			name : "Behdet"
			idx : 2
			pos : [837, 1072]
			route : 6
			is_open : false
			cost_to_open : 400
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
			]
		}

		// Display-only (pak route=0; no polyline).
		{
			name : "Kyrene"
			idx : 4
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Nubt"
			idx : 7
			pos : [800, 933]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// pak city id=10, no map_obj â€” keep display stub at standard empire pos.
			name : "Byblos"
			idx : 10
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer land
			type : 1
			points [
				[568, 512], [585, 527], [587, 540], [590, 557], [583, 570], [573, 567], [546, 569]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [
				[634, 1382], [643, 1337], [638, 1253], [637, 1190], [438, 1090], [384, 1074],
				[361, 1015], [350, 848], [361, 779], [400, 704], [496, 587], [527, 571], [543, 570]
			]
		}
		{
			route : 3 // Kerma sea
			type : 2
			points [
				[750, 1509], [732, 1489], [732, 1485], [709, 1483], [704, 1471], [695, 1463],
				[718, 1455], [731, 1442], [790, 1385], [791, 1373], [802, 1351], [843, 1308],
				[863, 1319], [882, 1298], [890, 1262], [903, 1248], [905, 1227], [889, 1216],
				[889, 1187], [887, 1142], [875, 1117], [855, 1089], [867, 1052], [855, 1022],
				[830, 1008], [812, 989], [820, 954], [792, 924], [771, 934], [761, 922],
				[761, 912], [744, 914], [716, 900], [716, 888], [701, 884], [679, 860],
				[674, 851], [656, 841], [649, 828], [613, 816], [596, 791], [600, 777],
				[584, 757], [585, 740], [565, 719], [576, 662], [586, 644], [587, 630],
				[601, 609], [542, 558]
			]
		}
		{
			route : 4 // Abu land
			type : 1
			points [
				[889, 1177], [879, 1156], [887, 1140], [878, 1116], [880, 1103], [857, 1087],
				[861, 1051], [861, 1031], [845, 1017], [833, 1013], [821, 996], [818, 979],
				[817, 957], [786, 932], [773, 937], [759, 915], [752, 914], [717, 929],
				[722, 892], [714, 887], [677, 864], [669, 852], [648, 840], [640, 825],
				[592, 796], [595, 776], [587, 758], [564, 721], [559, 704], [566, 651],
				[571, 624], [569, 612], [581, 601], [563, 592], [544, 565]
			]
		}
		{
			route : 5 // Abedju sea
			type : 2
			points [
				[711, 927], [705, 888], [679, 867], [675, 856], [652, 842], [651, 833],
				[636, 826], [625, 823], [622, 820], [600, 805], [592, 795], [575, 767],
				[573, 752], [566, 736], [567, 712], [570, 686], [570, 663], [584, 643],
				[585, 626], [596, 609], [598, 598], [591, 588], [589, 573], [547, 566]
			]
		}
		{
			route : 6 // Behdet sea
			type : 2
			points [
				[856, 1089], [876, 1068], [863, 1051], [848, 1029], [835, 1014], [825, 994],
				[811, 987], [818, 964], [788, 928], [761, 934], [758, 918], [745, 916],
				[721, 898], [721, 891], [713, 886], [704, 886], [676, 851], [656, 839],
				[655, 831], [641, 821], [623, 816], [598, 797], [599, 777], [588, 759],
				[588, 738], [564, 719], [560, 707], [562, 697], [560, 668], [572, 630],
				[569, 616], [580, 602], [547, 569]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// pak: exp_img 6 â†’ bits_120 (34Ã—18); exp_img 5 â†’ bits_119 (37Ã—34).
		{ pos : [507, 492], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [669, 889], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [844, 1098], image : "pharaoh_general/empire_bits_00119" }
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
		{ name : "#canaan", pos : [853, 327] }
	]

	vars {
		pharaoh_requested_gamemeat : false
		pharaoh_gift_pomegranates_done : false
		pharaoh_requested_oil : false
		pharaoh_requested_stone_once : false
		pharaoh_stone_recurring_last_year : -1
		pharaoh_luxury_recurring_last_year : -1
		pharaoh_gamemeat_recurring_last_year : -1
		pharaoh_gamemeat_y33_last_year : -1
		pharaoh_luxury_y44_last_year : -1
		pharaoh_luxury_y46_last_year : -1
		gold_collapse_early_last_year : -1
		gold_collapse_late_last_year : -1
		wage_decrease_last_year : -1
		land_trade_problem_last_year : -1
		wage_increase_late_done : false
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission10_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt) {
	var request = city.create_good_request({ tag_id: tag, resource: resource, amount: amount, months_initial: months })
	city.create_chain_event({ tag_id: ok_tag, type: EVENT_TYPE_REPUTATION_INCREASE, amount: ok_amt })
	city.create_chain_event({ tag_id: fail_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: fail_amt })
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		city.create_chain_event({ tag_id: late_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: late_amt })
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return request
}

[es=event_mission_start, mission=mission10]
function mission10_on_start(ev) {
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	__image_request_pak(PACK_TEMPLE_SETH)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_history_saqqara")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=1 month=11 gamemeat 7 / 4mo once; okâ†’+5 refuseâ†’âˆ’5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_gamemeat(ev) {
	if (mission.pharaoh_requested_gamemeat) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 11)) {
		return
	}
	mission.pharaoh_requested_gamemeat = true
	log_info("akhenaten: mission 10 saqqara gamemeat request", {ev:ev})
	mission10_fire_request(1, RESOURCE_GAMEMEAT, 7, 4, 101, 102, 0, 5, 5, 0)
}

// pak: year=3 month=0 GIFT pomegranates 11 subtype=3 once;
// okâ†’DEMAND timber +8; refuseâ†’DEMAND timber âˆ’9; lateâ†’KR âˆ’5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_gift_pomegranates(ev) {
	if (mission.pharaoh_gift_pomegranates_done) {
		return
	}
	if (ev.years_since_start < 3) {
		return
	}
	mission.pharaoh_gift_pomegranates_done = true
	log_info("akhenaten: mission 10 saqqara gift pomegranates", {ev:ev})
	var gift = city.create_chain_event({
		tag_id: 300,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_POMEGRANATES,
		amount: 11,
		subtype: 3, // EVENT_SUBTYPE_REQ_FOR_FESTIVAL / msg ack slot
		trigger: EVENT_TRIGGER_ONCE
	})
	city.create_chain_event({
		tag_id: 301,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_TIMBER,
		amount: 8
	})
	city.create_chain_event({
		tag_id: 302,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_TIMBER,
		amount: 9
	})
	city.create_chain_event({ tag_id: 303, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 5 })
	gift.set_completed_action_tag(301)
	gift.set_refusal_action_tag(302)
	gift.set_too_late_action_tag(303)
	gift.execute()
}

// pak: year=4 month=10 item=31 (oil) amount=501 / 2mo once; ok→+5 refuse→−5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_oil(ev) {
	if (mission.pharaoh_requested_oil) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 10)) {
		return
	}
	mission.pharaoh_requested_oil = true
	log_info("akhenaten: mission 10 saqqara oil request", {ev:ev})
	mission10_fire_request(2, RESOURCE_OIL, 501, 2, 201, 202, 0, 5, 5, 0)
}

// pak: year=5+ month=0 GOLD_MINE_COLLAPSE recurring
[es=event_advance_month, mission=mission10]
function mission10_gold_mine_collapse_early(ev) {
	if (ev.years_since_start < 5 || ev.month != 0) {
		return
	}
	if (mission.gold_collapse_early_last_year == ev.years_since_start) {
		return
	}
	mission.gold_collapse_early_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 500 + ev.years_since_start,
		type: EVENT_TYPE_GOLD_MINE_COLLAPSE,
		amount: 9,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=7+ month=0 WAGE_DECREASE recurring amount=4
[es=event_advance_month, mission=mission10]
function mission10_wage_decrease(ev) {
	if (ev.years_since_start < 7 || ev.month != 0) {
		return
	}
	if (mission.wage_decrease_last_year == ev.years_since_start) {
		return
	}
	mission.wage_decrease_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 600 + ev.years_since_start,
		type: EVENT_TYPE_WAGE_DECREASE,
		amount: 4,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=7+ month=0 LAND_TRADE_PROBLEM recurring amount=8
[es=event_advance_month, mission=mission10]
function mission10_land_trade_problem(ev) {
	if (ev.years_since_start < 7 || ev.month != 0) {
		return
	}
	if (mission.land_trade_problem_last_year == ev.years_since_start) {
		return
	}
	mission.land_trade_problem_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 700 + ev.years_since_start,
		type: EVENT_TYPE_LAND_TRADE_PROBLEM,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=10+ month=6 stone 10 / 6mo recurring; okâ†’+5 refuseâ†’âˆ’5 lateâ†’+5 (pak late=i=0)
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_stone_recurring(ev) {
	if (ev.years_since_start < 10 || ev.month != 6) {
		return
	}
	if (mission.pharaoh_stone_recurring_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_stone_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 1000 + y * 10
	log_info("akhenaten: mission 10 saqqara stone recurring y" + y, {ev:ev})
	var request = city.create_good_request({ tag_id: base, resource: RESOURCE_STONE, amount: 10, months_initial: 6 })
	city.create_chain_event({ tag_id: base + 1, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 5 })
	city.create_chain_event({ tag_id: base + 2, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 5 })
	request.set_completed_action_tag(base + 1)
	request.set_refusal_action_tag(base + 2)
	request.set_too_late_action_tag(base + 1)
	request.execute()
}

// pak: year=12+ month=4 luxury 3 / 9mo recurring;
// okâ†’DEMAND luxury +6; refuse/lateâ†’DEMAND luxury âˆ’5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_luxury_recurring(ev) {
	if (ev.years_since_start < 12 || ev.month != 4) {
		return
	}
	if (mission.pharaoh_luxury_recurring_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_luxury_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 1200 + y * 10
	log_info("akhenaten: mission 10 saqqara luxury recurring y" + y, {ev:ev})
	var request = city.create_good_request({ tag_id: base, resource: RESOURCE_LUXURY_GOODS, amount: 3, months_initial: 9 })
	city.create_chain_event({
		tag_id: base + 1,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 6
	})
	city.create_chain_event({
		tag_id: base + 2,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 5
	})
	request.set_completed_action_tag(base + 1)
	request.set_refusal_action_tag(base + 2)
	request.set_too_late_action_tag(base + 2)
	request.execute()
}

// pak: year=16+ month=10 GOLD_MINE_COLLAPSE recurring; okâ†’CONTAMINATED_WATER amount=8
[es=event_advance_month, mission=mission10]
function mission10_gold_mine_collapse_late(ev) {
	if (ev.years_since_start < 16 || ev.month != 10) {
		return
	}
	if (mission.gold_collapse_late_last_year == ev.years_since_start) {
		return
	}
	mission.gold_collapse_late_last_year = ev.years_since_start
	var y = ev.years_since_start
	var collapse = city.create_chain_event({
		tag_id: 1600 + y,
		type: EVENT_TYPE_GOLD_MINE_COLLAPSE,
		amount: 5,
		trigger: EVENT_TRIGGER_ONCE
	})
	city.create_chain_event({
		tag_id: 1650 + y,
		type: EVENT_TYPE_CONTAMINATED_WATER,
		amount: 8
	})
	collapse.set_completed_action_tag(1650 + y)
	collapse.execute()
}

// pak: year=18+ month=9 gamemeat 5 / 3mo recurring; okâ†’+5 refuseâ†’âˆ’5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_gamemeat_recurring(ev) {
	if (ev.years_since_start < 18 || ev.month != 9) {
		return
	}
	if (mission.pharaoh_gamemeat_recurring_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_gamemeat_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 1800 + y * 10
	log_info("akhenaten: mission 10 saqqara gamemeat recurring y" + y, {ev:ev})
	mission10_fire_request(base, RESOURCE_GAMEMEAT, 5, 3, base + 1, base + 2, 0, 5, 5, 0)
}

// pak: year=20 month=1 stone 8 / 5mo once; okâ†’+5 refuseâ†’âˆ’5 lateâ†’âˆ’5
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_stone_once(ev) {
	if (mission.pharaoh_requested_stone_once) {
		return
	}
	if (ev.years_since_start < 20 || (ev.years_since_start == 20 && ev.month < 1)) {
		return
	}
	mission.pharaoh_requested_stone_once = true
	log_info("akhenaten: mission 10 saqqara stone once y20", {ev:ev})
	mission10_fire_request(3, RESOURCE_STONE, 8, 5, 3010, 3011, 3012, 5, 5, 5)
}

// pak: year=26 month=5 WAGE_INCREASE once amount=9
[es=event_advance_month, mission=mission10]
function mission10_wage_increase_late(ev) {
	if (mission.wage_increase_late_done) {
		return
	}
	if (ev.years_since_start < 26 || (ev.years_since_start == 26 && ev.month < 5)) {
		return
	}
	mission.wage_increase_late_done = true
	city.create_chain_event({
		tag_id: 2600,
		type: EVENT_TYPE_WAGE_INCREASE,
		amount: 9,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=33+ month=0 gamemeat 5 / 3mo recurring; ok→+5 refuse/late→−5 (defeat=666 ignored)
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_gamemeat_y33(ev) {
	if (ev.years_since_start < 33 || ev.month != 0) {
		return
	}
	if (mission.pharaoh_gamemeat_y33_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_gamemeat_y33_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 3300 + y * 10
	log_info("akhenaten: mission 10 saqqara gamemeat y33+ y" + y, {ev:ev})
	mission10_fire_request(base, RESOURCE_GAMEMEAT, 5, 3, base + 1, base + 2, base + 2, 5, 5, 5)
}

// pak: year=44+ month=8 luxury 7 / 6mo recurring;
// ok→DEMAND luxury +11; refuse→DEMAND luxury −6; late→KR −5 (defeat=666 ignored)
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_luxury_y44(ev) {
	if (ev.years_since_start < 44 || ev.month != 8) {
		return
	}
	if (mission.pharaoh_luxury_y44_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_luxury_y44_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 4400 + y * 10
	log_info("akhenaten: mission 10 saqqara luxury y44+ y" + y, {ev:ev})
	var request = city.create_good_request({ tag_id: base, resource: RESOURCE_LUXURY_GOODS, amount: 7, months_initial: 6 })
	city.create_chain_event({
		tag_id: base + 1,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 11
	})
	city.create_chain_event({
		tag_id: base + 2,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 6
	})
	city.create_chain_event({ tag_id: base + 3, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 5 })
	request.set_completed_action_tag(base + 1)
	request.set_refusal_action_tag(base + 2)
	request.set_too_late_action_tag(base + 3)
	request.execute()
}

// pak: year=46+ month=4 luxury 6 / 6mo recurring;
// ok→DEMAND luxury +5; refuse→DEMAND luxury −9; late→KR −5 (defeat=666 ignored)
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_request_luxury_y46(ev) {
	if (ev.years_since_start < 46 || ev.month != 4) {
		return
	}
	if (mission.pharaoh_luxury_y46_last_year == ev.years_since_start) {
		return
	}
	mission.pharaoh_luxury_y46_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 4600 + y * 10
	log_info("akhenaten: mission 10 saqqara luxury y46+ y" + y, {ev:ev})
	var request = city.create_good_request({ tag_id: base, resource: RESOURCE_LUXURY_GOODS, amount: 6, months_initial: 6 })
	city.create_chain_event({
		tag_id: base + 1,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 5
	})
	city.create_chain_event({
		tag_id: base + 2,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 9
	})
	city.create_chain_event({ tag_id: base + 3, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 5 })
	request.set_completed_action_tag(base + 1)
	request.set_refusal_action_tag(base + 2)
	request.set_too_late_action_tag(base + 3)
	request.execute()
}

// pak i=30: by_favour amount=69 invader=pharaoh attack=RANDOM(4) ok=-1 (no chain).
[es=event_advance_month, mission=mission10]
function mission10_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 69)
}
