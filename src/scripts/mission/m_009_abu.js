log_info("akhenaten: mission 9 abu started")

// Empire / requests / events aligned with original campaign scenario 9 (2026-07-25 dump).
// Favour: pak i=15 by_favour 40 FOOD → i=18×20 RANDOM → i=19×20 RANDOM (helper + bind wipe).
// pak CITY_STATUS subtype=1 Selima (FOREIGN_CITY_CONQUERED) ok→NEW_TRADE city=5=Kyrene.

mission9 { // Abu — The Nubian Border
	map_file : "data/maps/m_009_abu.map"

	// Map points from data/maps/m_009_abu.map.
	herd_points_predator [ [96, 104], [50, 90], [38, 50] ]

	start_message : "message_history_abu"
	selection_title : "Abu"
	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}
	player_rank : 6
	next_mission : 10
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		grain : { type:RESOURCE_GRAIN, allow: true}
		barley: { type:RESOURCE_BARLEY, allow: true}
		flax: { type:RESOURCE_FLAX, allow:true}
		lettuce: { type:RESOURCE_LETTUCE, allow:true}
		chickpeas: { type:RESOURCE_CHICKPEAS, allow:true}
	}

	sounds {
		briefing : "Voice/Mission/209_mission.mp3"
		victory : "Voice/Mission/209_victory.mp3"
	}

	buildings [
		         BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
				 BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
				 BUILDING_GRANITE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_GEMSTONE_MINE,
				 BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_FLAX_FARM, BUILDING_LETTUCE_FARM, BUILDING_WORK_CAMP,
				 BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
				 BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
				 BUILDING_WATER_SUPPLY,
				 BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
				 BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_DOCK,
				 BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
				 BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_FAMILY_MANSION, BUILDING_TOWN_PALACE,
				 BUILDING_FESTIVAL_SQUARE, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH,
				 BUILDING_IRRIGATION_DITCH, BUILDING_WATER_LIFT,
				]

	// Win ratings match original campaign scenario 9.
	win_criteria {
		population    {enabled : true, goal : 4000 }
		culture       {enabled : true, goal : 30 }
		prosperity    {enabled : true, goal : 30 }
		kingdom       {enabled : true, goal : 50 }
		housing_level {enabled : true, goal : 10 }
		monuments     {enabled : false }
	}

	// Map points from original campaign scenario 9.
	entry_point [119, 51]
	exit_point [129, 80]
	river_entry_point [41, 28]
	river_exit_point [42, 27]
	disembark_points [ [60, 62], [-1, -1], [80, 100] ]
	invasion_points_land [ [104, 103], [125, 82], [80, 127] ]
	invasion_points_sea [ [32, 39] ]

	enable_scenario_events : true

	// Empire from original campaign scenario 9 (empire id=1) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_LETTUCE, RESOURCE_CHICKPEAS, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
		}

		{
			name : "Men-nefer"
			idx : 5
			pos : [530, 486]
			route : 1
			is_open : false
			cost_to_open : 1100
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH_TRADING
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
			// pak: foreign display, empty sells/buys, cost=550, route=2.
			name : "Selima Oasis"
			idx : 8
			pos : [615, 1366]
			route : 2
			cost_to_open : 550
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Behdet"
			idx : 2
			pos : [836, 1069]
			route : 3
			is_open : false
			cost_to_open : 250
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Timna"
			idx : 9
			pos : [906, 456]
			route : 4
			is_open : false
			cost_to_open : 1450
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_COPPER ]
			buys [ RESOURCE_FISH, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Abedju"
			idx : 1
			pos : [696, 907]
			route : 5
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		// Display-only cities on the empire map (pak route ids; no trade).
		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 10
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kyrene"
			idx : 4
			pos : [22, 341]
			route : 8
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Nubt"
			idx : 7
			pos : [800, 933]
			route : 6
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer sea
			type : 2
			points [
				[895, 1188], [879, 1162], [886, 1136], [878, 1116], [880, 1100], [876, 1089],
				[880, 1075], [878, 1063], [865, 1051], [862, 1036], [855, 1026], [845, 1017],
				[832, 1014], [824, 1000], [811, 986], [833, 944], [813, 907], [804, 917],
				[793, 922], [784, 929], [774, 935], [758, 916], [744, 920], [723, 899],
				[717, 887], [704, 887], [693, 874], [678, 865], [675, 852], [652, 842],
				[653, 833], [641, 821], [631, 824], [626, 815], [613, 814], [594, 794],
				[596, 785], [595, 774], [586, 764], [586, 752], [584, 737], [569, 730],
				[567, 716], [569, 683], [571, 662], [584, 645], [584, 630], [599, 606],
				[589, 541], [574, 517]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [ [896, 1183], [630, 1384] ]
		}
		{
			route : 3 // Behdet sea
			type : 2
			points [
				[895, 1183], [885, 1153], [887, 1137], [879, 1117], [884, 1100], [876, 1088],
				[866, 1086]
			]
		}
		{
			route : 4 // Timna land
			type : 1
			points [
				[918, 1183], [1023, 1182], [1040, 1174], [1055, 1153], [1062, 1103], [1046, 1043],
				[1018, 966], [978, 919], [933, 861], [883, 857], [850, 849], [822, 832],
				[837, 805], [860, 800], [875, 789], [879, 771], [836, 723], [833, 702],
				[801, 685], [764, 644], [715, 605], [668, 548], [667, 519], [679, 492],
				[745, 468], [924, 472]
			]
		}
		{
			route : 5 // Abedju land
			type : 1
			points [ [893, 1182], [711, 924] ]
		}
		// Display routes 6/8/10: two-point stubs; improve_route + deviation bends the line.
		{
			route : 6 // Nubt
			type : 1
			deviation : 40
			points [ [893, 1182], [800, 933] ]
		}
		{
			route : 8 // Kyrene
			type : 1
			deviation : 60
			points [ [893, 1182], [22, 341] ]
		}
		{
			route : 10 // Byblos
			type : 1
			deviation : 50
			points [ [893, 1182], [891, 68] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// pak w/h 29x28 → mastaba bits; 37x34 → neighbouring ornament frame.
		{ pos : [515, 489], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [665, 887], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [842, 1095], image : "pharaoh_general/empire_bits_00119" }
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
		pharaoh_requested_granite : false
		pharaoh_requested_sandstone : false
		land_trade_problem_done : false
		flax_demand_done : false
		nubt_conquered_msg_done : false
		selima_trade_unlock_done : false
		contaminated_water_done : false
		sea_trade_problem_done : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		start_message_shown : false
	}
}

function mission9_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt, subtype) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (typeof subtype !== "undefined") {
		opts.subtype = subtype
	}
	var request = city.create_good_request(opts)
	city.create_chain_event({ tag_id: ok_tag, type: EVENT_TYPE_REPUTATION_INCREASE, amount: ok_amt })
	city.create_chain_event({ tag_id: fail_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: fail_amt })
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		city.create_chain_event({ tag_id: late_tag, type: EVENT_TYPE_REPUTATION_DECREASE, amount: late_amt })
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
}

[es=event_mission_start, mission=mission9]
function mission9_on_start(ev) {
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_ENEMY_HYKSOS)
	mission_show_start_message(mission, "message_history_abu")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=2 month=4 LAND_TRADE_PROBLEM once amount=8
[es=event_advance_month, mission=mission9]
function mission9_land_trade_problem(ev) {
	if (mission.land_trade_problem_done) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 4)) {
		return
	}
	mission.land_trade_problem_done = true
	city.create_chain_event({
		tag_id: 500,
		type: EVENT_TYPE_LAND_TRADE_PROBLEM,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=4 month=7 granite 13 / 12mo; ok→+6 refuse→−7 late→−3
[es=event_advance_month, mission=mission9]
function mission9_pharaoh_request_granite(ev) {
	if (mission.pharaoh_requested_granite) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 7)) {
		return
	}
	mission.pharaoh_requested_granite = true
	log_info("akhenaten: mission 9 abu granite request", {ev:ev})
	mission9_fire_request(1, RESOURCE_GRANITE, 13, 12, 101, 102, 103, 6, 7, 3)
}

// pak: year=6 month=9 DEMAND_INCREASE flax amount=8 once; ok→i=1 granite REQUEST.
// Granite is already ONCE/ALREADY_FIRED by y6 → chain is a no-op (pak graph preserved).
[es=event_advance_month, mission=mission9]
function mission9_flax_demand_increase(ev) {
	if (mission.flax_demand_done) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 9)) {
		return
	}
	mission.flax_demand_done = true
	var demand = city.create_chain_event({
		tag_id: 600,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_FLAX,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	})
	demand.set_completed_action_tag(1) // pak ok=1 → granite REQUEST
	demand.execute()
}

// pak: year=6 month=4 CITY_STATUS subtype=1 city=Selima ok→NEW_TRADE city=5=Kyrene.
[es=event_advance_month, mission=mission9]
function mission9_selima_secured_trade(ev) {
	if (mission.selima_trade_unlock_done) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 4)) {
		return
	}
	mission.selima_trade_unlock_done = true
	log_info("akhenaten: mission 9 abu CITY_STATUS Selima conquered → NEW_TRADE Kyrene", {ev:ev})
	var status = city.create_chain_event({
		tag_id: 610,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 1, // EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED
		city: "Selima Oasis",
		amount: 7,
		trigger: EVENT_TRIGGER_ONCE
	})
	city.create_chain_event({
		tag_id: 611,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE — pak city_id=5
		city: "Kyrene",
		amount: 7
	})
	status.set_completed_action_tag(611)
	status.execute()
}

// pak: year=7 month=1 MESSAGE FOREIGN_CITY_CONQUERED city=Nubt → DEMAND linen amount=9
[es=event_advance_month, mission=mission9]
function mission9_nubt_conquered_linen_demand(ev) {
	if (mission.nubt_conquered_msg_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 1)) {
		return
	}
	mission.nubt_conquered_msg_done = true
	log_info("akhenaten: mission 9 abu Nubt conquered → linen demand", {ev:ev})
	var msg = city.create_chain_event({
		tag_id: 700,
		type: EVENT_TYPE_MESSAGE,
		subtype: 1, // EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED
		city: "Nubt",
		amount: 9,
		trigger: EVENT_TRIGGER_ONCE
	})
	city.create_chain_event({
		tag_id: 701,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LINEN,
		amount: 9
	})
	msg.set_completed_action_tag(701)
	msg.execute()
}

// pak: year=10 month=0 sandstone 22 / 16mo subtype=4 construction; ok→+6 refuse→−11 late→−5
[es=event_advance_month, mission=mission9]
function mission9_pharaoh_request_sandstone(ev) {
	if (mission.pharaoh_requested_sandstone) {
		return
	}
	if (ev.years_since_start < 10) {
		return
	}
	mission.pharaoh_requested_sandstone = true
	log_info("akhenaten: mission 9 abu sandstone construction request", {ev:ev})
	mission9_fire_request(2, RESOURCE_SANDSTONE, 22, 16, 201, 202, 203, 6, 11, 5, 4)
}

// pak: year=13 month=7 CONTAMINATED_WATER once amount=6
[es=event_advance_month, mission=mission9]
function mission9_contaminated_water(ev) {
	if (mission.contaminated_water_done) {
		return
	}
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 7)) {
		return
	}
	mission.contaminated_water_done = true
	city.create_chain_event({
		tag_id: 800,
		type: EVENT_TYPE_CONTAMINATED_WATER,
		amount: 6,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=15 month=10 SEA_TRADE_PROBLEM once amount=7
[es=event_advance_month, mission=mission9]
function mission9_sea_trade_problem(ev) {
	if (mission.sea_trade_problem_done) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 10)) {
		return
	}
	mission.sea_trade_problem_done = true
	city.create_chain_event({
		tag_id: 801,
		type: EVENT_TYPE_SEA_TRADE_PROBLEM,
		amount: 7,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=17+ month=0 DEMAND_INCREASE gems amount=7 recurring yearly
[es=event_advance_month, mission=mission9]
function mission9_gems_demand_increase(ev) {
	if (ev.years_since_start < 17 || ev.month != 0) {
		return
	}
	city.create_chain_event({
		tag_id: 900 + ev.years_since_start,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_GEMS,
		amount: 7,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=15/18/19: by_favour 40 FOOD → 20 RANDOM → 20 RANDOM (bind wipe advances waves).
[es=event_advance_month, mission=mission9]
function mission9_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, [40, 20, 20], {
		targets: [
			EVENT_ATTACK_TARGET_FOOD,
			EVENT_ATTACK_TARGET_RANDOM,
			EVENT_ATTACK_TARGET_RANDOM
		]
	})
}
