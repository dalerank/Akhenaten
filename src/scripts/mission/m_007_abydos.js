log_info("akhenaten: mission 7 abydos started")

// Empire / requests / invasions verified vs mission1.pak scenario 7 (2026-07-25 dump).

mission7 { // Abydos / Abedju — The Challenge of the Sea
	map_file : "data/maps/m_007_abydos.map"

	// Map points from data/maps/m_007_abydos.map.
	herd_points_predator [ [88, 57], [74, 71], [92, 35] ]
	fishing_points [ [95, 66], [76, 65], [110, 71] ]

	start_message : "message_soldiers_and_forts"
	selection_title : "Abydos"
	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}
	player_rank : 3

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 22]

	choice [
		{
			name : "Selima"
			id : 8
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 23]
			pos [620, 420]
		}

		{
			name : "Abu"
			id : 9
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 24]
			pos [640, 480]
		}
	]

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	init_resources : {
		barley: { type:RESOURCE_BARLEY, allow: true},
		flax: { type:RESOURCE_FLAX, allow:true},
	}

	sounds {
		briefing : "Voice/Mission/207_mission.mp3"
		victory : "Voice/Mission/207_victory.mp3"
	}

	buildings [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST,
					BUILDING_WORK_CAMP, BUILDING_FLAX_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_DOCK,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS,
					BUILDING_BRICKLAYERS_GUILD,
					BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE
				]

	// Win ratings match mission1.pak scenario 7.
	win_criteria {
		population    {enabled : true, goal : 2500 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 17 }
		kingdom       {enabled : true, goal : 60 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 7.
	entry_point [3, 66]
	exit_point [83, 126]
	river_entry_point [129, 61]
	river_exit_point [15, 56]
	disembark_points [ [50, 59], [-1, -1], [44, 59] ]
	invasion_points_land [ [66, 5], [2, 69] ]
	invasion_points_sea [ [127, 59] ]

	// Empire from mission1.pak scenario 7 (empire id=0) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Abedju"
			idx : 0
			pos : [696, 907]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FISH, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_REEDS ]
			buys [ RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
		}

		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 2
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
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 5
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 3
			pos : [545, 487]
			route : 3
			is_open : false
			cost_to_open : 700
			is_sea_trade : false
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
			name : "Nubt"
			idx : 6
			pos : [800, 933]
			route : 6
			is_open : false
			cost_to_open : 270
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT, RESOURCE_STRAW, RESOURCE_CLAY, RESOURCE_BRICKS ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
			]
		}

		{
			name : "Perwadjyt"
			idx : 7
			pos : [494, 364]
			route : 1
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_STRAW, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_REEDS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
			]
		}

		{
			name : "Timna"
			idx : 10
			pos : [906, 456]
			route : 4
			is_open : false
			cost_to_open : 900
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_COPPER ]
			buys [ RESOURCE_FISH, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		// Display-only cities on the empire map.
		{
			name : "Nekhen"
			idx : 5
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Thinis"
			idx : 9
			pos : [687, 871]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Selima Oasis"
			idx : 8
			pos : [613, 1363]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[734, 916], [725, 901], [679, 864], [675, 853], [654, 844], [653, 831],
				[642, 823], [630, 823], [625, 814], [610, 810], [595, 795], [595, 777],
				[585, 756], [584, 739], [567, 727], [570, 709], [570, 683], [572, 662],
				[585, 643], [585, 626], [600, 608], [600, 593], [592, 586], [592, 550],
				[571, 510], [557, 488], [556, 476], [546, 467], [545, 444], [543, 432],
				[533, 417], [527, 400], [511, 379]
			]
		}
		{
			route : 2
			type : 2
			points [
				[735, 924], [758, 913], [762, 923], [775, 933], [788, 930], [793, 921],
				[804, 918], [818, 909], [829, 942], [829, 955], [817, 968], [813, 989],
				[824, 999], [833, 1011], [854, 1023], [864, 1037], [864, 1049], [871, 1058],
				[877, 1068], [875, 1083], [855, 1081]
			]
		}
		{
			route : 3
			type : 1
			points [
				[709, 931], [693, 958], [661, 964], [615, 945], [579, 903], [552, 850],
				[532, 799], [522, 745], [499, 680], [469, 631], [458, 572], [488, 521],
				[560, 517]
			]
		}
		{
			route : 4
			type : 1
			points [
				[721, 925], [757, 890], [764, 808], [734, 723], [722, 700], [720, 677],
				[726, 660], [728, 639], [718, 606], [700, 578], [653, 545], [644, 514],
				[663, 481], [745, 453], [844, 456], [920, 473]
			]
		}
		{
			route : 5
			type : 2
			points [
				[737, 916], [727, 899], [679, 866], [676, 853], [652, 842], [643, 823],
				[630, 823], [613, 813], [597, 796], [598, 774], [584, 760], [582, 735],
				[566, 718], [570, 697], [568, 678], [584, 647], [584, 627], [601, 610],
				[600, 597], [592, 583], [589, 562], [594, 550], [567, 511], [552, 474],
				[542, 463], [546, 430], [547, 410], [561, 401], [567, 389], [560, 378],
				[595, 333], [675, 345], [770, 322], [821, 278], [856, 118], [906, 84]
			]
		}
		{
			route : 6
			type : 2
			points [
				[824, 954], [829, 938], [823, 923], [819, 911], [812, 910], [802, 918],
				[794, 921], [792, 923], [789, 927], [780, 933], [775, 933], [765, 926],
				[761, 922], [759, 915], [750, 918], [720, 933]
			]
		}
		// Sea approach path (not tied to a trade city route id).
		{
			route : 7
			type : 2
			points [
				[863, 1320], [876, 1306], [886, 1273], [906, 1232], [896, 1214], [889, 1211],
				[891, 1204], [898, 1198], [891, 1191], [895, 1179], [882, 1161], [882, 1158],
				[889, 1137], [878, 1111], [881, 1099], [876, 1091], [878, 1066], [869, 1054],
				[865, 1051], [864, 1036], [856, 1027], [847, 1018], [832, 1011], [828, 1000],
				[816, 992], [812, 984], [819, 966], [832, 947], [814, 906], [801, 919],
				[784, 931], [774, 935], [762, 925], [761, 923], [759, 913], [747, 918],
				[739, 923]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [525, 494], image : "pharaoh_general/empire_bits_00120" }
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
		pharaoh_beer_requested : false
		pharaoh_fish_requested : false
		contaminated_water_1 : false
		sea_trade_problem_done : false
		wage_increase_1 : false
		linen_demand_increased : false
		beer_demand_increased : false
		wage_increase_2 : false
		fish_demand_decreased : false
		contaminated_water_2 : false
		kushite_invasion_1 : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		start_message_shown : false
	}
}

function mission7_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt) {
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

[es=event_mission_start, mission=mission7]
function mission7_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	mission_show_start_message(mission, "message_soldiers_and_forts")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=2 month=8 PERFECT_FLOOD recurring — fire every year in month 8 from year 2
[es=event_advance_month, mission=mission7]
function mission7_perfect_flood(ev) {
	if (ev.years_since_start < 2 || ev.month != 8) {
		return
	}
	city.create_chain_event({
		tag_id: 1800 + ev.years_since_start,
		type: EVENT_TYPE_PERFECT_FLOOD,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=2 month=2 beer 9 / 12mo; ok→+13→GIFT bricks 21; refuse→−14; late→−6
[es=event_advance_month, mission=mission7]
function mission7_pharaoh_request_beer(ev) {
	if (mission.pharaoh_beer_requested) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 2)) {
		return
	}
	mission.pharaoh_beer_requested = true
	var ok_ev = mission7_fire_request(1, RESOURCE_BEER, 9, 12, 101, 102, 103, 13, 14, 6)
	city.create_chain_event({
		tag_id: 1701,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_BRICKS,
		amount: 21
	})
	ok_ev.set_completed_action_tag(1701)
}

// pak: year=5 month=3 CONTAMINATED_WATER once
[es=event_advance_month, mission=mission7]
function mission7_contaminated_water_1(ev) {
	if (mission.contaminated_water_1) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 3)) {
		return
	}
	mission.contaminated_water_1 = true
	city.create_chain_event({
		tag_id: 401,
		type: EVENT_TYPE_CONTAMINATED_WATER,
		amount: 22,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=7 month=7 SEA_TRADE_PROBLEM once
[es=event_advance_month, mission=mission7]
function mission7_sea_trade_problem(ev) {
	if (mission.sea_trade_problem_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 7)) {
		return
	}
	mission.sea_trade_problem_done = true
	city.create_chain_event({
		tag_id: 501,
		type: EVENT_TYPE_SEA_TRADE_PROBLEM,
		amount: 19,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=8 month=0 WAGE_INCREASE once
[es=event_advance_month, mission=mission7]
function mission7_wage_increase_1(ev) {
	if (mission.wage_increase_1) {
		return
	}
	if (ev.years_since_start < 8) {
		return
	}
	mission.wage_increase_1 = true
	city.create_chain_event({
		tag_id: 601,
		type: EVENT_TYPE_WAGE_INCREASE,
		amount: 5,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=9 month=7 DEMAND_INCREASE linen amount=19
[es=event_advance_month, mission=mission7]
function mission7_linen_demand_increase(ev) {
	if (mission.linen_demand_increased) {
		return
	}
	if (ev.years_since_start < 9 || (ev.years_since_start == 9 && ev.month < 7)) {
		return
	}
	mission.linen_demand_increased = true
	city.create_chain_event({
		tag_id: 701,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LINEN,
		amount: 19,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=10 month=11 DEMAND_INCREASE beer amount=24
[es=event_advance_month, mission=mission7]
function mission7_beer_demand_increase(ev) {
	if (mission.beer_demand_increased) {
		return
	}
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 11)) {
		return
	}
	mission.beer_demand_increased = true
	city.create_chain_event({
		tag_id: 801,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_BEER,
		amount: 24,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=12 month=1 fish 18 / 12mo; ok→+10→same gift bricks 21; refuse→−10; late→−9
[es=event_advance_month, mission=mission7]
function mission7_pharaoh_request_fish(ev) {
	if (mission.pharaoh_fish_requested) {
		return
	}
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 1)) {
		return
	}
	mission.pharaoh_fish_requested = true
	var ok_ev = mission7_fire_request(3, RESOURCE_FISH, 18, 12, 301, 302, 303, 10, 10, 9)
	// pak ok child also chains to the same bricks gift (event 17); beer handler already created tag 1701.
	ok_ev.set_completed_action_tag(1701)
}

// pak: y14 m9 size=3 Kushite (timed). Favour-KR Pharaoh army amount=40 via JS helper.
[es=event_advance_month, mission=mission7]
function mission7_kushite_invasion_1(ev) {
	if (mission.kushite_invasion_1) {
		return
	}
	if (ev.years_since_start < 14 || (ev.years_since_start == 14 && ev.month < 9)) {
		return
	}
	mission.kushite_invasion_1 = true
	log_info("akhenaten: mission 7 abydos kushite invasion size=3", {ev:ev})
	city.start_foreign_army_invasion({
		invasion_id: 0,
		enemy: ENEMY_6_KUSHITE,
		size: 3,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 3,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM // pak attack=4
	})
}

// pak: year=15 month=4 WAGE_INCREASE once
[es=event_advance_month, mission=mission7]
function mission7_wage_increase_2(ev) {
	if (mission.wage_increase_2) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 4)) {
		return
	}
	mission.wage_increase_2 = true
	city.create_chain_event({
		tag_id: 1401,
		type: EVENT_TYPE_WAGE_INCREASE,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=18 month=6 DEMAND_DECREASE fish amount=9
[es=event_advance_month, mission=mission7]
function mission7_fish_demand_decrease(ev) {
	if (mission.fish_demand_decreased) {
		return
	}
	if (ev.years_since_start < 18 || (ev.years_since_start == 18 && ev.month < 6)) {
		return
	}
	mission.fish_demand_decreased = true
	city.create_chain_event({
		tag_id: 1501,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_FISH,
		amount: 9,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=19 month=8 CONTAMINATED_WATER once
[es=event_advance_month, mission=mission7]
function mission7_contaminated_water_2(ev) {
	if (mission.contaminated_water_2) {
		return
	}
	if (ev.years_since_start < 19 || (ev.years_since_start == 19 && ev.month < 8)) {
		return
	}
	mission.contaminated_water_2 = true
	city.create_chain_event({
		tag_id: 1601,
		type: EVENT_TYPE_CONTAMINATED_WATER,
		amount: 2,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

[es=event_advance_month, mission=mission7]
function mission7_pharaoh_favour_invasion(ev) {
	// pak: by_favour amount=40 → ok→chain_only Pharaoh army amount=40
	mission_pharaoh_favour_invasion_tick(mission, 40, 40)
}
