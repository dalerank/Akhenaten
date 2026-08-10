log_info("akhenaten: mission 5 timna started")

// Trade / requests / invasions verified vs mission1.pak scenario 5 (2026-07-24 dump).
// Stub events/attacks/trade_routes removed — they were never wired (enable_scenario_events:false).

mission5 { // Timna
	map_file : "data/maps/m_005_timna.map"

	// Map points from data/maps/m_005_timna.map.
	herd_points_prey [ [82, 96] ]

	start_message : "message_history_military"
	selection_title : "Timna"
	env {
		has_animals : true
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
		hide_nilometer : true
	}

	sounds {
		briefing : "Voice/Mission/205_mission.mp3"
		victory : "Voice/Mission/205_victory.mp3"
	}

	player_rank : 2

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 19]

	choice [
		{
			name : "Behdet"
			id : 6
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 20]
			pos [640, 480]
		}

		{
			name : "Abydos"
			id : 7
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 21]
			pos [620, 420]
		}
	]

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
		         	BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
					BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL, BUILDING_CLAY_PIT, BUILDING_GEMSTONE_MINE, BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_POTTERY_WORKSHOP,
					BUILDING_WEAVER_WORKSHOP, BUILDING_HUNTING_LODGE, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_FESTIVAL_SQUARE,

					BUILDING_MORTUARY, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD
				]

	win_criteria {
		population    {enabled : true, goal : 2000 }
		prosperity    {enabled : true, goal : 15 }
		kingdom       {enabled : true, goal : 70 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 5 (no river / disembark / earthquake).
	entry_point [47, 117]
	exit_point [41, 28]
	invasion_points_land [ [62, 9], [105, 35], [21, 51], [41, 109] ]

	stages {
		tutorial_irrigation { buildings: [BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, ] }
		tutorial_guilds { buildings: [BUILDING_STORAGE_YARD, BUILDING_TAX_COLLECTOR, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL] }
	}

	// Empire from mission1.pak scenario 5 (empire id=1) — full map objects.
	// Trade partners: Nekhen / Nubt / Thinis (closed land). Men-nefer + Perwadjyt display-only.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Timna"
			idx : 6
			pos : [906, 456]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_WEAPONS, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_FISH, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
		}

		{
			name : "Nekhen"
			idx : 2
			pos : [797, 1011]
			route : 4
			is_open : false
			cost_to_open : 1020
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Nubt"
			idx : 3
			pos : [800, 933]
			route : 1
			is_open : false
			cost_to_open : 850
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 4000 }
			]
		}

		{
			name : "Thinis"
			idx : 5
			pos : [687, 871]
			route : 2
			is_open : false
			cost_to_open : 800
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_BEER ]
			buys [ RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "Men-nefer"
			idx : 0
			pos : [535, 486]
			route : 5
			is_open : false
			cost_to_open : 460
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_PHARAOH
			max_traders : 1
			trade_limits : default_trade_limits
			// Unlocked via CITY_STATUS_CHANGE (NEW_TRADE_ROUTE) after gems/weapons request success.
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_LETTUCE, limit: 1500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
			]
		}

		{
			name : "Perwadjyt"
			idx : 4
			pos : [494, 364]
			route : 0
			is_open : false
			cost_to_open : 5
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	// Trade + approach polylines from mission1.pak empire_map_routes (scenario 5).
	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 1
			points [
				[817, 943], [820, 899], [807, 844], [790, 811], [788, 790],
				[785, 777], [778, 749], [767, 733], [765, 692], [779, 656],
				[767, 646], [753, 629], [741, 622], [716, 589], [691, 556],
				[682, 548], [690, 504], [700, 498], [722, 497], [756, 503],
				[778, 503], [794, 495], [831, 496], [895, 499], [932, 478]
			]
		}
		{
			route : 2
			type : 1
			points [
				[709, 885], [758, 834], [779, 810], [757, 728], [779, 654],
				[759, 638], [739, 620], [721, 596], [717, 574], [701, 564],
				[683, 547], [683, 522], [688, 508], [728, 499], [774, 501],
				[790, 495], [845, 500], [856, 500], [904, 497], [934, 481]
			]
		}
		{
			route : 4
			type : 1
			points [
				[811, 1023], [816, 950], [761, 935], [736, 848], [759, 832],
				[777, 812], [771, 765], [765, 751], [759, 715], [771, 679],
				[779, 655], [759, 640], [752, 629], [716, 590], [683, 551],
				[682, 524], [705, 497], [744, 501], [765, 503], [784, 504],
				[816, 497], [840, 497], [853, 503], [930, 479]
			]
		}
		{
			route : 5
			type : 1
			points [
				[572, 514], [661, 502], [693, 501], [765, 506], [788, 496],
				[804, 495], [833, 495], [855, 503], [897, 499], [936, 477]
			]
		}
		// Approach paths (pak type=0 → land); kept for invasion / map fidelity.
		{
			route : 15
			type : 1
			points [ [1131, 629], [1068, 551], [1018, 520], [934, 479] ]
		}
		{
			route : 16
			type : 1
			points [ [992, 349], [946, 411], [934, 480] ]
		}
		{
			route : 17
			type : 1
			points [ [873, 343], [895, 418], [918, 443] ]
		}
		{
			route : 18
			type : 1
			points [ [894, 655], [918, 567], [877, 525] ]
		}
	]

	hide_pak_objects : true
	// Decorative mastaba west of Men-nefer (pak w/h 29x28 → empire_bits_00120).
	empire_ornaments [
		{ pos : [522, 492], image : "pharaoh_general/empire_bits_00120" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1002, 1557] }
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
		pharaoh_requested_copper : false
		pharaoh_requested_gems : false
		pharaoh_requested_deben : false
		pharaoh_requested_weapons : false
		libyan_invasion_1 : false
		libyan_invasion_2 : false
		libyan_invasion_3 : false
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission5_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt) {
	var request = city.create_good_request({ tag_id: tag, resource: resource, amount: amount, months_initial: months })
	var ok_ev = city.create_chain_event({ tag_id: ok_tag, type: EVENT_TYPE_REPUTATION_INCREASE, amount: ok_amt })
	city.create_chain_event({ tag_id: fail_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: fail_amt })
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		city.create_chain_event({ tag_id: late_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: late_amt })
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return ok_ev
}

function mission5_libyan_raid(invasion_id, size) {
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_7_LIBIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size
	})
}

[es=event_mission_start, mission=mission5]
function mission5_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	mission_show_start_message(mission, "message_history_military")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=0 month=8 copper 5 / 9mo; ok→rep+4, refuse→rep-2, late→rep-1
[es=event_advance_month, mission=mission5]
function mission5_pharaoh_request_copper(ev) {
	if (mission.pharaoh_requested_copper) {
		return
	}
	if (ev.years_since_start == 0 && ev.month < 8) {
		return
	}
	mission.pharaoh_requested_copper = true
	mission5_fire_request(1, RESOURCE_COPPER, 5, 9, 101, 102, 103, 4, 2, 1)
}

// pak: year=2 month=4 gems 15 / 12mo; ok→rep+4→CITY_STATUS NEW_TRADE_ROUTE (Men-nefer)
[es=event_advance_month, mission=mission5]
function mission5_pharaoh_request_gems(ev) {
	if (mission.pharaoh_requested_gems) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 4)) {
		return
	}
	mission.pharaoh_requested_gems = true
	var ok_ev = mission5_fire_request(2, RESOURCE_GEMS, 15, 12, 201, 202, 203, 4, 2, 1)
	city.create_chain_event({
		tag_id: 204,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE
		city: "Men-nefer",
		amount: 0
	})
	ok_ev.set_completed_action_tag(204)
}

[es=event_advance_month, mission=mission5]
function mission5_pharaoh_request_deben(ev) {
	if (mission.pharaoh_requested_deben) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 8)) {
		return
	}
	mission.pharaoh_requested_deben = true
	var ok_ev = mission5_fire_request(3, RESOURCE_DEBEN, 885, 12, 301, 302, 303, 4, 2, 3)
	city.create_chain_event({
		tag_id: 304,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_CHICKPEAS,
		amount: 16
	})
	ok_ev.set_completed_action_tag(304)
}

// pak: year=7 month=3 weapons 11 / 12mo; ok→rep+4→same Men-nefer trade unlock
[es=event_advance_month, mission=mission5]
function mission5_pharaoh_request_weapons(ev) {
	if (mission.pharaoh_requested_weapons) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 3)) {
		return
	}
	mission.pharaoh_requested_weapons = true
	var ok_ev = mission5_fire_request(4, RESOURCE_WEAPONS, 11, 12, 401, 402, 0, 4, 2, 0)
	city.create_chain_event({
		tag_id: 404,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE
		city: "Men-nefer",
		amount: 0
	})
	ok_ev.set_completed_action_tag(404)
}

// pak invasions: EVENT_INVADER_BEDUINS field, but scenario enemy_id = ENEMY_7_LIBIAN (sprites).
// Favour-KR Pharaoh army amount=45 via JS helper.
[es=event_advance_month, mission=mission5]
function mission5_libyan_invasion_1(ev) {
	if (mission.libyan_invasion_1) { return }
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 7)) { return }
	mission.libyan_invasion_1 = true
	log_info("akhenaten: mission 5 timna libyan invasion 1 size=9", {ev:ev})
	mission5_libyan_raid(0, 9)
}

[es=event_advance_month, mission=mission5]
function mission5_libyan_invasion_2(ev) {
	if (mission.libyan_invasion_2) { return }
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 9)) { return }
	mission.libyan_invasion_2 = true
	log_info("akhenaten: mission 5 timna libyan invasion 2 size=16", {ev:ev})
	mission5_libyan_raid(1, 16)
}

[es=event_advance_month, mission=mission5]
function mission5_libyan_invasion_3(ev) {
	if (mission.libyan_invasion_3) { return }
	if (ev.years_since_start < 5) { return }
	mission.libyan_invasion_3 = true
	log_info("akhenaten: mission 5 timna libyan invasion 3 size=24", {ev:ev})
	mission5_libyan_raid(2, 24)
}

[es=event_advance_month, mission=mission5]
function mission5_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 45)
}
