log_info("akhenaten: mission 11 serabit khadim started")

// Empire / requests / invasions aligned with original campaign scenario 11 (2026-07-25 dump).
// Favour Pharaoh army size=51 (by_favour, attack=RANDOM) via mission_pharaoh_favour_invasion_tick.
// Triage: skip year=100 CLAY_PIT_FLOOD junk; skip broken ok→99 after KR+6;
// omit invasion/disembark (pak count 0); routes 3/5/9/11 orphan skip.
// Clay floods i=16–20: copy (+ BUILDING_CLAY_PIT).
// Recurring copper/luxury: yearly slot + gate (no stack while active; ≥1 mo after clear).

mission11 { // Serabit Khadim — The Bedouin of the East
	map_file : "data/maps/m_011_serabit_khadim.map"

	// Map points from data/maps/m_011_serabit_khadim.map; fixed herd sizes.
	herd_points_predator [
		{ tile: [74, 25], type: FIGURE_HYENA, count: 5, radius: 16 }
	]
	herd_points_prey [
		{ tile: [28, 43], type: FIGURE_OSTRICH, count: 5, radius: 16 }
	]

	start_message : "message_mission_serabit_khadim"
	selection_title : "Serabit Khadim"
	player_rank : 5

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 31]

	choice [
		{
			name : "Buhen"
			id : 13
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 32]
			pos [620, 420]
		}

		{
			name : "Dahshur"
			id : 14
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 33]
			pos [640, 480]
		}
	]

	// pak Normal funds=15000 loan=3500 debt_interest=20 → int_dcy around Normal.
	initial_funds [30000, 20000, 15000, 10000, 8000]
	rescue_loans [7000, 4700, 3500, 2300, 1900]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		hide_nilometer : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/211_mission.mp3"
		victory : "Voice/Mission/211_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
		BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
		BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
	]

	// Goals match original campaign scenario 11 (housing_level 4; culture/prosperity/monuments off).
	win_criteria {
		population    {enabled : true, goal : 2000 }
		culture       {enabled : false }
		prosperity    {enabled : false }
		monuments     {enabled : false }
		kingdom       {enabled : true, goal : 80 }
		housing_level {enabled : true, goal : 4 }
	}

	// Map points from original campaign scenario 11 (no river / disembark / invasion points).
	entry_point [28, 84]
	exit_point [83, 84]

	enable_scenario_events : true

	// Empire from original campaign scenario 11 (empire id=8) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Serabit Khadim"
			idx : 10
			pos : [801, 552]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_CLAY ]
		}

		{
			name : "Men-nefer"
			idx : 5
			pos : [545, 487]
			route : 1
			is_open : false
			cost_to_open : 350
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BEER, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Selima Oasis"
			idx : 9
			pos : [614, 1359]
			route : 2
			is_open : false
			cost_to_open : 1100
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 4
			is_open : false
			cost_to_open : 540
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 1500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Nekhen"
			idx : 7
			pos : [797, 1011]
			route : 6
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 7
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		// Display-only.
		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 3
			pos : [732, 1491]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kyrene"
			idx : 4
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			// pak route=8 polyline junk (Byblos area) — 2-pt stub ours→Saqqara.
			name : "Saqqara"
			idx : 8
			pos : [512, 534]
			route : 8
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer land
			type : 1
			points [
				[585, 503], [612, 474], [634, 453], [666, 428], [690, 430], [706, 444],
				[713, 454], [736, 479], [780, 516], [800, 534], [812, 558]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [
				[625, 1378], [667, 1365], [706, 1358], [746, 1345], [785, 1328], [829, 1307],
				[846, 1297], [878, 1266], [896, 1227], [908, 1205], [1000, 1191], [1050, 1148],
				[1061, 1092], [1011, 978], [975, 908], [934, 853], [899, 811], [845, 740],
				[832, 710], [758, 650], [714, 610], [695, 579], [681, 531], [687, 499],
				[702, 496], [716, 500], [730, 524], [747, 549], [766, 561], [784, 571], [806, 581]
			]
		}
		{
			route : 4 // Abu land
			type : 1
			points [
				[890, 1159], [894, 1136], [886, 1115], [887, 1087], [881, 1051], [874, 1041],
				[862, 1017], [826, 986], [825, 960], [833, 935], [821, 902], [821, 873],
				[811, 859], [808, 835], [801, 825], [788, 780], [780, 750], [766, 721],
				[700, 617], [668, 513], [671, 498], [682, 491], [714, 489], [732, 506],
				[749, 526], [767, 548], [807, 569]
			]
		}
		{
			route : 6 // Nekhen land
			type : 1
			points [
				[815, 1019], [798, 979], [791, 972], [751, 927], [734, 918], [712, 900],
				[607, 819], [566, 774], [549, 691], [554, 644], [618, 494], [649, 457],
				[656, 446], [667, 439], [680, 437], [693, 447], [716, 470], [793, 541], [808, 558]
			]
		}
		{
			route : 7 // Behdet land
			type : 1
			points [
				[859, 1071], [851, 1032], [822, 1002], [811, 988], [811, 968], [814, 919],
				[799, 868], [764, 763], [707, 660], [655, 504], [655, 490], [662, 480],
				[676, 477], [699, 482], [723, 485], [756, 519], [783, 546], [807, 563]
			]
		}
		{
			route : 8 // Saqqara display (pak polyline junk → 2-pt + deviation)
			type : 1
			deviation : 40
			points [ [801, 552], [512, 534] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// pak: exp_img 5 → bits_119 (37×34); exp_img 6 → bits_120 (29×28); exp_img 3 → bits_117 (28×15).
		{ pos : [710, 921], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [841, 1097], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [519, 496], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [486, 535], image : "pharaoh_general/empire_bits_00117" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [611, 766] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [442, 451] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [739, 445] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		shared_request_leaves_wired : false
		pharaoh_gift_chickpeas_done : false
		pharaoh_copper_recurring_last_year : -1
		pharaoh_copper_recurring_was_busy : false
		pharaoh_copper_recurring_idle_since_abs : -1
		pharaoh_requested_copper2 : false
		land_trade_problem_done : false
		clay_pit_flood_last_year : -1
		pharaoh_requested_weapons1 : false
		pharaoh_luxury_recurring_last_year : -1
		pharaoh_luxury_recurring_was_busy : false
		pharaoh_luxury_recurring_idle_since_abs : -1
		pharaoh_requested_weapons2 : false
		libyan_invasion_1 : false
		beduin_raid_last_year : -1
		beduin_raid_active : false
		beduin_raid_enemies_seen : false
		beduin_raid_resolved : false
		libyan_invasion_3 : false
		libyan_invasion_4 : false
		libyan_invasion_5 : false
		libyan_invasion_6 : false
		libyan_invasion_7 : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false
		start_message_shown : false
	}
}

// Shared ONLY_VIA leaves from pak (copper1/luxury → 21/23/24; copper2/weapons1 → 26/28/25;
// weapons2 refuse → 27→29→30). city/subtype/months from dump (mostly message metadata).
function mission11_ensure_shared_request_leaves() {
	if (mission.shared_request_leaves_wired) {
		return
	}
	mission.shared_request_leaves_wired = true

	// i=21 city=6 Men-nefer; i=23 city=4 Kerma; i=24 city=5 Kyrene
	city.create_chain_event({
		tag_id: 21,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 5,
		city: "Men-nefer"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 23,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 10,
		city: "Kerma"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 24,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 5,
		city: "Kyrene"
	}).set_param("months_initial", 2)

	// i=26 city=7 Nekhen subtype=3; pak ok→99 broken — skip
	city.create_chain_event({
		tag_id: 26,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 6,
		subtype: 3,
		city: "Nekhen"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 25,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 8,
		city: "Nekhen"
	}).set_param("months_initial", 2)
	var demand_copper = city.create_chain_event({
		tag_id: 28,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_COPPER,
		amount: 7,
		city: "Men-nefer"
	})
	demand_copper.set_param("months_initial", 2)
	demand_copper.set_completed_action_tag(25)

	// i=27 city=4 Kerma under siege → i=29 KR−8 Nekhen → i=30 NEW_TRADE Nekhen
	var siege = city.create_chain_event({
		tag_id: 27,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 4, // EVENT_SUBTYPE_CITY_UNDER_SIEGE
		city: "Kerma",
		amount: 8
	})
	siege.set_param("months_initial", 2)
	var kr_after_siege = city.create_chain_event({
		tag_id: 29,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 8,
		city: "Nekhen"
	})
	kr_after_siege.set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 30,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE
		city: "Nekhen",
		amount: 5
	}).set_param("months_initial", 2)
	siege.set_completed_action_tag(29)
	kr_after_siege.set_completed_action_tag(30)
}

// sender_faction: 1=pharaoh (EVENT_FACTION_REQUEST_FROM_PHARAOH), 0=city
function mission11_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, sender_faction) {
	mission11_ensure_shared_request_leaves()
	var request = city.create_good_request({
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months
	})
	if (sender_faction !== undefined) {
		request.set_sender_faction(sender_faction)
	}
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return request
}

[es=event_mission_start, mission=mission11]
function mission11_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_serabit_khadim")
	empire.set_id(8)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=1 month=7 gift chickpeas 32 once (no ok/refuse chain).
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_gift_chickpeas(ev) {
	if (mission.pharaoh_gift_chickpeas_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 7)) {
		return
	}
	mission.pharaoh_gift_chickpeas_done = true
	log_info("akhenaten: mission 11 serabit gift chickpeas", {ev:ev})
	// pak i=3: city=8 Saqqara, sender=1, subtype=0, months=14 (metadata; gift pays out immediately)
	var gift = city.create_chain_event({
		tag_id: 200,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_CHICKPEAS,
		amount: 32,
		subtype: 0,
		city: "Saqqara",
		trigger: EVENT_TRIGGER_ONCE
	})
	gift.set_sender_faction(1)
	gift.set_param("months_initial", 14)
	gift.execute()
}

// Track request idle for recurring copper/luxury (pak: complete ≥1 mo before recur).
[es=event_advance_month, mission=mission11]
function mission11_recurring_request_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_COPPER, "pharaoh_copper_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_LUXURY_GOODS, "pharaoh_luxury_recurring", abs)
}

// pak: year=1+ month=7 copper 8 / 18mo recurring; ok→+5 refuse→−10 late→−5
// Gate: no stack while copper request active (incl. copper2); ≥1 month after clear.
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_copper_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 7) {
		return
	}
	if (mission.pharaoh_copper_recurring_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_COPPER, "pharaoh_copper_recurring", abs)) {
		return
	}
	mission.pharaoh_copper_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 1000 + y * 10
	log_info("akhenaten: mission 11 serabit copper recurring y" + y, {ev:ev})
	mission11_fire_request(base, RESOURCE_COPPER, 8, 18, 21, 23, 24, 1) // pak sender=1 pharaoh
}

// pak: year=3 month=4 copper 11 / 18mo once; ok→+6 refuse→DEMAND copper−7→KR−8 late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_copper2(ev) {
	if (mission.pharaoh_requested_copper2) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 4)) {
		return
	}
	mission.pharaoh_requested_copper2 = true
	log_info("akhenaten: mission 11 serabit copper2 request", {ev:ev})
	mission11_fire_request(2, RESOURCE_COPPER, 11, 18, 26, 28, 25, 0) // pak sender=0 city
}

// pak: year=3 month=4 LAND_TRADE_PROBLEM once amount=8
[es=event_advance_month, mission=mission11]
function mission11_land_trade_problem(ev) {
	if (mission.land_trade_problem_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 4)) {
		return
	}
	mission.land_trade_problem_done = true
	log_info("akhenaten: mission 11 serabit land trade problem", {ev:ev})
	// pak i=4: city=8 Saqqara, sender=0, months=14 (handler always uses fixed 48mo)
	var trade = city.create_chain_event({
		tag_id: 300,
		type: EVENT_TYPE_LAND_TRADE_PROBLEM,
		amount: 8,
		subtype: 0,
		city: "Saqqara",
		trigger: EVENT_TRIGGER_ONCE
	})
	trade.set_sender_faction(0)
	trade.set_param("months_initial", 14)
	trade.execute()
}

// pak i=16–20: year=1+ month=0 CLAY_PIT_FLOOD recurring ×5 (amounts 6/6/8/9/7).
// Each event rubble one random working clay pit (handler ignores amount).
[es=event_advance_month, mission=mission11]
function mission11_clay_pit_flood_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 0) {
		return
	}
	if (mission.clay_pit_flood_last_year == ev.years_since_start) {
		return
	}
	mission.clay_pit_flood_last_year = ev.years_since_start
	var y = ev.years_since_start
	var amounts = [6, 6, 8, 9, 7]
	log_info("akhenaten: mission 11 serabit clay pit floods y" + y, {ev:ev})
	for (var i = 0; i < amounts.length; i++) {
		city.create_chain_event({
			tag_id: 800 + y * 10 + i,
			type: EVENT_TYPE_CLAY_PIT_FLOOD,
			amount: amounts[i],
			trigger: EVENT_TRIGGER_ONCE
		}).execute()
	}
}

// pak: year=5 month=9 weapons 13 / 18mo once; ok→+6 refuse→DEMAND copper−7→KR−8 late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_weapons1(ev) {
	if (mission.pharaoh_requested_weapons1) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 9)) {
		return
	}
	mission.pharaoh_requested_weapons1 = true
	log_info("akhenaten: mission 11 serabit weapons1 request", {ev:ev})
	mission11_fire_request(3, RESOURCE_WEAPONS, 13, 18, 26, 28, 25, 0) // pak sender=0 city
}

// pak: year=7+ month=0 luxury 16 / 24mo recurring; ok→+5 refuse→−10 late→−5
// Gate: no stack while luxury request active; ≥1 month after clear.
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_luxury_recurring(ev) {
	if (ev.years_since_start < 7 || ev.month != 0) {
		return
	}
	if (mission.pharaoh_luxury_recurring_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_LUXURY_GOODS, "pharaoh_luxury_recurring", abs)) {
		return
	}
	mission.pharaoh_luxury_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 2000 + y * 10
	log_info("akhenaten: mission 11 serabit luxury recurring y" + y, {ev:ev})
	mission11_fire_request(base, RESOURCE_LUXURY_GOODS, 16, 24, 21, 23, 24, 1) // pak sender=1 pharaoh
}

// pak: year=8 month=2 weapons 21 / 12mo once;
// ok→+6 refuse→Kerma siege→KR−8→NEW_TRADE Nekhen late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_weapons2(ev) {
	if (mission.pharaoh_requested_weapons2) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 2)) {
		return
	}
	mission.pharaoh_requested_weapons2 = true
	log_info("akhenaten: mission 11 serabit weapons2 request", {ev:ev})
	mission11_fire_request(5, RESOURCE_WEAPONS, 21, 12, 26, 27, 25, 0) // pak sender=0 city
}

function mission11_libyan_raid(invasion_id, size, attack_target) {
	// Scenario enemy_id in pak is ENEMY_7_LIBIAN. No invasion land points in pak → auto tile.
	if (typeof attack_target === "undefined") {
		attack_target = EVENT_ATTACK_TARGET_RANDOM
	}
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

// pak i=6: year=1 month=10 enemy size=8 once attack=VAULTS(1)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_1(ev) {
	if (mission.libyan_invasion_1) { return }
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 10)) { return }
	mission.libyan_invasion_1 = true
	log_info("akhenaten: mission 11 libyan invasion 1 size=8 attack=VAULTS", {ev:ev})
	mission11_libyan_raid(0, 8, EVENT_ATTACK_TARGET_VAULTS)
}

// pak i=5: year=2+ month=4 beduins size=16 recurring attack=RANDOM(4) (sprites = Libyan)
[es=event_advance_month, mission=mission11]
function mission11_beduin_raid_recurring(ev) {
	if (ev.years_since_start < 2 || ev.month != 4) {
		return
	}
	if (mission.beduin_raid_last_year == ev.years_since_start) {
		return
	}
	if (city.num_enemy_formations > 0) {
		return
	}
	if (mission.beduin_raid_active && !mission.beduin_raid_resolved) {
		return
	}
	mission.beduin_raid_last_year = ev.years_since_start
	mission.beduin_raid_enemies_seen = false
	mission.beduin_raid_resolved = false
	mission.beduin_raid_active = true
	log_info("akhenaten: mission 11 beduin raid size=16 year=" + ev.years_since_start, {ev:ev})
	mission11_libyan_raid(1, 16, EVENT_ATTACK_TARGET_RANDOM)
}

[es=event_advance_month, mission=mission11]
function mission11_beduin_raid_resolve(ev) {
	if (!mission.beduin_raid_active || mission.beduin_raid_resolved) {
		return
	}
	var enemies = city.num_enemy_formations
	if (enemies > 0) {
		mission.beduin_raid_enemies_seen = true
		return
	}
	if (!mission.beduin_raid_enemies_seen) {
		return
	}
	mission.beduin_raid_resolved = true
	mission.beduin_raid_active = false
}

// pak i=8: year=3 month=3 enemy size=12 once attack=BEST_BUILDINGS(2)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_3(ev) {
	if (mission.libyan_invasion_3) { return }
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 3)) { return }
	mission.libyan_invasion_3 = true
	log_info("akhenaten: mission 11 libyan invasion 3 size=12 attack=BEST_BUILDINGS", {ev:ev})
	mission11_libyan_raid(2, 12, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=9: year=4 month=8 enemy size=20 once attack=FOOD(0)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_4(ev) {
	if (mission.libyan_invasion_4) { return }
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 8)) { return }
	mission.libyan_invasion_4 = true
	log_info("akhenaten: mission 11 libyan invasion 4 size=20 attack=FOOD", {ev:ev})
	mission11_libyan_raid(3, 20, EVENT_ATTACK_TARGET_FOOD)
}

// pak i=12: year=6 month=0 enemy size=28 once attack=VAULTS(1)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_5(ev) {
	if (mission.libyan_invasion_5) { return }
	if (ev.years_since_start < 6) { return }
	mission.libyan_invasion_5 = true
	log_info("akhenaten: mission 11 libyan invasion 5 size=28 attack=VAULTS", {ev:ev})
	mission11_libyan_raid(4, 28, EVENT_ATTACK_TARGET_VAULTS)
}

// pak i=14: year=8 month=6 enemy size=28 once attack=RANDOM(4)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_6(ev) {
	if (mission.libyan_invasion_6) { return }
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 6)) { return }
	mission.libyan_invasion_6 = true
	log_info("akhenaten: mission 11 libyan invasion 6 size=28 attack=RANDOM", {ev:ev})
	mission11_libyan_raid(5, 28, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=15: year=10 month=1 enemy size=32 once attack=BEST_BUILDINGS(2)
[es=event_advance_month, mission=mission11]
function mission11_libyan_invasion_7(ev) {
	if (mission.libyan_invasion_7) { return }
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 1)) { return }
	mission.libyan_invasion_7 = true
	log_info("akhenaten: mission 11 libyan invasion 7 size=32 attack=BEST_BUILDINGS", {ev:ev})
	mission11_libyan_raid(6, 32, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=31: by_favour amount=51 invader=pharaoh attack=RANDOM(4) ok=-1
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 51)
}
