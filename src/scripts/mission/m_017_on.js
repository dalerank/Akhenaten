log_info("akhenaten: mission 17 on started")

// Empire / requests / events verified vs mission1.pak scenario 17 (2026-07-26 dump).
// Empire id=1. Scenario enemy ENEMY_4_HITTITE (no timed raids — only favour Pharaoh).
// Gods: Osiris, Ra, Bast. Favour Pharaoh 20→20→20→20→20 (five waves).
// Triage: SKIP MESSAGE i=6 (orphan chain_only, no inbound); SKIP map_obj idx=9 empty;
// Men-nefer route 7 has no pak polyline → 2-pt stub + deviation.
// Perfect flood y4m7+ recurring ok→ gamemeat×9 chain request.
// Limestone×25/36mo recurring y3m5+; refuse→KR−18→LOST_TRADE Kyrene (display foreign).
// Monuments 18 = 3 small mastabas (2.25*6+4.5=18).
//
// Tag_id scheme:
//   1000 + i               chain-only ONLY_VIA_EVENT leaves / chain requests
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission17 { // On (Heliopolis) — Ivory from the East
	map_file : "data/maps/m_017_on.map"

	// Map points from data/maps/m_017_on.map.
	herd_points_predator [ [84, 108], [72, 52], [69, 11] ]
	herd_points_prey [ [72, 116], [96, 107] ]

	start_message : "message_mission_heliopolis"
	selection_title : "On"
	player_rank : 6

	// On (17) and Iunet (16) are a choice pair; both converge on Rostja (18).
	next_mission : 18

	// pak Normal funds=6000 loan=3000 debt_interest=20 → int_dcy around Normal.
	initial_funds [12000, 8000, 6000, 4000, 3200]
	rescue_loans [6000, 4000, 3000, 2000, 1600]
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
		briefing : "Voice/Mission/217_mission.mp3"
		victory : "Voice/Mission/217_victory.mp3"
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
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_FLAX_FARM,
		BUILDING_CATTLE_RANCH, BUILDING_REED_GATHERER,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_CLAY_PIT,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals verified vs pak: pop 4000, culture 40, prosperity 35, monuments 18, kingdom 60,
	// housing_level 10. Monuments 18 = 3 small mastabas under additive formula.
	win_criteria {
		population    {enabled : true, goal : 4000 }
		culture       {enabled : true, goal : 40 }
		prosperity    {enabled : true, goal : 35 }
		monuments     {enabled : true, goal : 18 }
		kingdom       {enabled : true, goal : 60 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [127, 82]
	exit_point [96, 26]
	river_entry_point [107, 102]
	river_exit_point [37, 32]
	disembark_points [ [49, 82], [-1, -1], [65, 79] ]
	invasion_points_land [ [112, 106] ]
	invasion_points_sea [ [97, 103] ]

	// pak burial_provisions (scenario 17 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_LINEN, required: 8 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 8 }
		{ resource: RESOURCE_TIMBER, required: 8 }
		{ resource: RESOURCE_LIMESTONE, required: 32 }
		{ resource: RESOURCE_GRANITE, required: 32 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "On"
			idx : 11
			pos : [572, 444]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_FLAX, RESOURCE_REEDS, RESOURCE_LIMESTONE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
		}

		{
			name : "Iunet"
			idx : 4
			pos : [783, 892]
			route : 1
			is_open : false
			cost_to_open : 1500
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Saqqara"
			idx : 12
			pos : [523, 539]
			route : 2
			is_open : false
			cost_to_open : 400
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_STONE ]
			buys [ RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}

		{
			name : "Dahshur"
			idx : 3
			pos : [560, 541]
			route : 3
			is_open : false
			cost_to_open : 200
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_STONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_GEMS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}

		{
			name : "Meidum"
			idx : 7
			pos : [568, 606]
			route : 4
			is_open : false
			cost_to_open : 450
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_STONE ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 8
			pos : [537, 474]
			route : 7
			is_open : false
			cost_to_open : 0
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Buhen"
			idx : 1
			pos : [766, 1345]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

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
			idx : 5
			pos : [732, 1491]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kyrene"
			idx : 6
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Nekhen"
			idx : 10
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Selima Oasis"
			idx : 13
			pos : [613, 1353]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Iunet sea
			type : 2
			points [
				[798, 909], [786, 931], [769, 933], [759, 921], [756, 914], [747, 919],
				[732, 908], [717, 895], [717, 888], [700, 883], [690, 871], [674, 862],
				[667, 851], [652, 839], [651, 831], [638, 823], [628, 822], [622, 815],
				[610, 814], [595, 794], [595, 776], [584, 754], [579, 736], [571, 729],
				[565, 718], [570, 711], [570, 680], [571, 662], [583, 648], [584, 638],
				[599, 610], [598, 598], [590, 579], [592, 564], [587, 545], [585, 527],
				[575, 517], [572, 506], [569, 495], [570, 483], [585, 461]
			]
		}
		{
			route : 2 // Saqqara sea
			type : 2
			points [
				[548, 563], [559, 586], [571, 603], [569, 622], [570, 646], [561, 665],
				[571, 672], [579, 657], [585, 642], [585, 631], [597, 614], [599, 599],
				[591, 581], [590, 558], [586, 542], [586, 528], [571, 509], [566, 493],
				[566, 478], [586, 460]
			]
		}
		{
			route : 3 // Dahshur sea
			type : 2
			points [
				[588, 467], [577, 477], [571, 489], [575, 515], [588, 541]
			]
		}
		{
			route : 4 // Meidum sea
			type : 2
			points [
				[584, 470], [570, 490], [581, 526], [592, 554], [593, 591], [589, 611]
			]
		}
		{
			// Men-nefer display — no pak polyline; 2-pt stub.
			route : 7
			type : 1
			deviation : 40
			points [ [537, 474], [572, 444] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [509, 488], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [486, 533], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [594, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [564, 580], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [718, 917], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [843, 1094], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [783, 1328], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [615, 539], image : "pharaoh_general/empire_bits_00118" }
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
		limestone_leaves_wired : false
		gamemeat_leaves_wired : false

		event0_demand_done : false
		event2_clay_done : false
		event3_demand_done : false
		event4_wage_done : false

		event5_limestone_last_year : -1
		limestone_recurring_was_busy : false
		limestone_recurring_idle_since_abs : -1

		event1_perfect_flood_last_year : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_wave4_done : false
		pharaoh_favour_wave5_done : false
		pharaoh_favour_wave2_enemies_seen : false
		pharaoh_favour_wave3_enemies_seen : false
		pharaoh_favour_wave4_enemies_seen : false
		pharaoh_favour_wave5_enemies_seen : false

		start_message_shown : false
	}
}

function mission17_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission17_fire_simple_event(tag, type, resource, amount, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	city.create_chain_event(opts).execute()
}

function mission17_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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

// pak i=5 limestone tails: ok→9 KR+26; refuse→7 KR−18→10 LOST_TRADE Kyrene; late→8 KR−9.
function mission17_ensure_limestone_leaves() {
	if (mission.limestone_leaves_wired) {
		return
	}
	mission.limestone_leaves_wired = true
	mission17_make_leaf(1009, EVENT_TYPE_REPUTATION_INCREASE, undefined, 26, 2)
	var kr_refuse = mission17_make_leaf(1007, EVENT_TYPE_REPUTATION_DECREASE, undefined, 18, 2)
	mission17_make_leaf(1008, EVENT_TYPE_REPUTATION_DECREASE, undefined, 9, 2)
	mission17_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Kyrene")
	kr_refuse.set_completed_action_tag(1010)
}

// pak i=11 gamemeat (perfect-flood chain): ok→12 KR+7; refuse→14 KR−25; late→13 KR−3.
function mission17_ensure_gamemeat_leaves() {
	if (mission.gamemeat_leaves_wired) {
		return
	}
	mission.gamemeat_leaves_wired = true
	mission17_make_leaf(1012, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
	mission17_make_leaf(1013, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission17_make_leaf(1014, EVENT_TYPE_REPUTATION_DECREASE, undefined, 25, 2)

	var gamemeat = city.create_good_request({
		tag_id: 1011, resource: RESOURCE_GAMEMEAT, amount: 9, months_initial: 9,
		subtype: 3, trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gamemeat.set_sender_faction(1)
	gamemeat.set_completed_action_tag(1012)
	gamemeat.set_refusal_action_tag(1014)
	gamemeat.set_too_late_action_tag(1013)
}

[es=event_mission_start, mission=mission17]
function mission17_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HITTITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_TEMPLE_BAST)
	mission_show_start_message(mission, "message_mission_heliopolis")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_4_HITTITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	mission17_ensure_limestone_leaves()
	mission17_ensure_gamemeat_leaves()
}

// pak i=0: DEMAND_INCREASE limestone×6 once y3m2 city=Dahshur.
[es=event_advance_month, mission=mission17]
function mission17_event_i0_limestone_demand(ev) {
	if (mission.event0_demand_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 2)) {
		return
	}
	mission.event0_demand_done = true
	log_info("akhenaten: mission 17 on limestone demand +6 Dahshur", {ev:ev})
	mission17_fire_simple_event(2000, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LIMESTONE, 6, "Dahshur")
}

// pak i=1: PERFECT_FLOOD amount=5 recurring y4m7+ → ok→gamemeat×9 chain.
[es=event_advance_month, mission=mission17]
function mission17_event_i1_perfect_flood(ev) {
	if (ev.years_since_start < 4 || ev.month != 7) {
		return
	}
	if (mission.event1_perfect_flood_last_year == ev.years_since_start) {
		return
	}
	mission.event1_perfect_flood_last_year = ev.years_since_start
	mission17_ensure_gamemeat_leaves()
	log_info("akhenaten: mission 17 on perfect flood y" + ev.years_since_start, {ev:ev})
	var flood = city.create_chain_event({
		tag_id: 3000 + 1 * 100 + ev.years_since_start,
		type: EVENT_TYPE_PERFECT_FLOOD,
		amount: 5,
		trigger: EVENT_TRIGGER_ONCE
	})
	flood.set_param("months_initial", 2)
	flood.set_completed_action_tag(1011)
	flood.execute()
}

// pak i=2: CLAY_PIT_FLOOD once y7m9 amount=8 → 8% of clay pits.
[es=event_advance_month, mission=mission17]
function mission17_event_i2_clay_flood(ev) {
	if (mission.event2_clay_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 9)) {
		return
	}
	mission.event2_clay_done = true
	var total = city.count_total_buildings(BUILDING_CLAY_PIT)
	var n = Math.floor((total * 8 + 99) / 100)
	log_info("akhenaten: mission 17 on clay flood n=" + n + " of " + total, {ev:ev})
	for (var i = 0; i < n; i++) {
		city.create_chain_event({
			tag_id: 2002 + i,
			type: EVENT_TYPE_CLAY_PIT_FLOOD,
			amount: 8,
			trigger: EVENT_TRIGGER_ONCE
		}).execute()
	}
}

// pak i=3: DEMAND_INCREASE limestone×9 once y8m0 city=Iunet.
[es=event_advance_month, mission=mission17]
function mission17_event_i3_limestone_demand(ev) {
	if (mission.event3_demand_done) {
		return
	}
	if (ev.years_since_start < 8) {
		return
	}
	mission.event3_demand_done = true
	log_info("akhenaten: mission 17 on limestone demand +9 Iunet", {ev:ev})
	mission17_fire_simple_event(2003, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LIMESTONE, 9, "Iunet")
}

// pak i=4: WAGE_INCREASE ×7 once y9m0.
[es=event_advance_month, mission=mission17]
function mission17_event_i4_wage_increase(ev) {
	if (mission.event4_wage_done) {
		return
	}
	if (ev.years_since_start < 9) {
		return
	}
	mission.event4_wage_done = true
	log_info("akhenaten: mission 17 on wage +7", {ev:ev})
	mission17_fire_simple_event(2004, EVENT_TYPE_WAGE_INCREASE, undefined, 7)
}

// pak i=5: limestone×25 / 36mo recurring from y3m5, sender=city(0), subtype=4.
[es=event_advance_month, mission=mission17]
function mission17_event_i5_limestone_recurring(ev) {
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 5)) {
		return
	}
	if (mission.event5_limestone_last_year == ev.years_since_start) {
		return
	}
	var abs_month = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_LIMESTONE, "limestone_recurring", abs_month)) {
		return
	}
	mission.event5_limestone_last_year = ev.years_since_start
	mission17_ensure_limestone_leaves()
	log_info("akhenaten: mission 17 on limestone×25 recurring y" + ev.years_since_start, {ev:ev})
	mission17_fire_request(3000 + 5 * 100 + ev.years_since_start, RESOURCE_LIMESTONE, 25, 36, 1009, 1007, 1008, 4, 0)
}

// pak i=15→16→17→18→19: favour 20×5; last wave attack=FOOD.
[es=event_advance_month, mission=mission17]
function mission17_pharaoh_favour_invasion(ev) {
	var on_targets = []
	on_targets[4] = EVENT_ATTACK_TARGET_FOOD
	mission_pharaoh_favour_invasion_tick(mission, [20, 20, 20, 20, 20], { targets: on_targets })
}
