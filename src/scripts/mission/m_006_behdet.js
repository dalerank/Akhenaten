log_info("akhenaten: mission 6 behdet started")

// Empire / requests / invasions verified vs mission1.pak scenario 6 (2026-07-25 dump).

mission6 { // Behdet — The Royal Navy
	map_file : "data/maps/m_006_behdet.map"

	// Map points from data/maps/m_006_behdet.map.
	fishing_points [ [73, 38], [89, 61] ]

	start_message : "message_soldiers_and_forts"
	selection_title : "Behdet"
	player_rank : 2

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

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/206_mission.mp3"
		victory : "Voice/Mission/206_victory.mp3"
	}

	buildings [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_WORK_CAMP, BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_DOCK,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF,
					BUILDING_BRICKLAYERS_GUILD,
					BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
				]

	// Win ratings match mission1.pak scenario 6.
	win_criteria {
		population    {enabled : true, goal : 2500 }
		culture       {enabled : true, goal : 15 }
		prosperity    {enabled : true, goal : 20 }
		monuments     {enabled : true, goal : 11 }
		kingdom       {enabled : true, goal : 45 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 6.
	entry_point [21, 34]
	exit_point [79, 88]
	river_entry_point [96, 68]
	river_exit_point [41, 17]
	// pak slots 0 and 2; slot 1 empty → [-1, -1]
	disembark_points [ [59, 40], [-1, -1], [68, 42] ]
	invasion_points_sea [ [97, 67] ]

	// Empire from mission1.pak scenario 6 (empire id=1) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 0
			type : EMPIRE_CITY_OURS
			is_sea_trade : true
			sells [ RESOURCE_CHICKPEAS, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_REEDS ]
			buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
		}

		{
			name : "Perwadjyt"
			idx : 7
			pos : [494, 364]
			route : 1
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_REEDS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
			]
		}

		{
			name : "Nekhen"
			idx : 5
			pos : [797, 1011]
			route : 2
			is_open : false
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 3
			pos : [535, 491]
			route : 3
			is_open : false
			cost_to_open : 750
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
			name : "Timna"
			idx : 9
			pos : [906, 456]
			route : 4
			is_open : false
			cost_to_open : 750
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

		// Display-only cities on the empire map.
		{
			name : "Abedju"
			idx : 0
			pos : [696, 907]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Nubt"
			idx : 6
			pos : [800, 933]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Thinis"
			idx : 8
			pos : [687, 871]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Selima Oasis"
			idx : 27
			pos : [619, 1362]
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
				[879, 1107], [883, 1075], [876, 1061], [865, 1048], [862, 1034], [850, 1020],
				[833, 1014], [814, 985], [828, 941], [821, 919], [812, 909], [804, 918],
				[792, 919], [784, 929], [773, 934], [762, 923], [758, 914], [745, 917],
				[679, 863], [675, 850], [666, 849], [655, 837], [647, 826], [632, 820],
				[613, 811], [600, 798], [596, 775], [586, 762], [585, 738], [569, 728],
				[565, 716], [571, 705], [569, 677], [573, 663], [585, 644], [583, 630],
				[600, 609], [598, 596], [594, 589], [592, 580], [589, 562], [592, 552],
				[583, 533], [551, 473], [544, 461], [541, 432], [533, 417], [534, 406],
				[509, 381]
			]
		}
		{
			route : 2
			type : 1
			points [ [858, 1094], [812, 1027] ]
		}
		{
			route : 3
			type : 2
			points [
				[877, 1102], [881, 1081], [879, 1068], [867, 1048], [860, 1029], [842, 1018],
				[814, 986], [832, 943], [816, 908], [798, 917], [785, 929], [772, 934],
				[757, 916], [745, 916], [684, 866], [674, 852], [653, 840], [649, 826],
				[630, 821], [613, 814], [599, 799], [597, 781], [584, 760], [585, 741],
				[566, 721], [572, 711], [570, 664], [588, 646], [585, 629], [595, 619],
				[600, 607], [590, 580], [590, 553], [573, 513]
			]
		}
		{
			route : 4
			type : 1
			points [
				[922, 477], [882, 488], [833, 491], [738, 497], [697, 502], [679, 531],
				[681, 546], [689, 557], [706, 570], [717, 582], [720, 597], [729, 610],
				[754, 636], [776, 652], [781, 663], [782, 678], [780, 704], [773, 721],
				[771, 736], [786, 774], [812, 845], [824, 882], [824, 907], [815, 951],
				[806, 996], [813, 1029], [853, 1087]
			]
		}
		{
			route : 5
			type : 2
			points [
				[861, 1096], [879, 1096], [883, 1075], [868, 1048], [835, 1012], [816, 992],
				[834, 942], [812, 909], [777, 934], [741, 912], [676, 860], [652, 838],
				[652, 828], [602, 807], [597, 777], [585, 761], [586, 740], [568, 726],
				[568, 716], [571, 667], [585, 645], [584, 635], [603, 606], [588, 564],
				[593, 551], [559, 496], [560, 479], [544, 461], [546, 441], [550, 406],
				[558, 397], [549, 390], [553, 380], [549, 362], [520, 358], [529, 338],
				[552, 341], [571, 347], [584, 340], [604, 328], [635, 340], [678, 357],
				[748, 331], [807, 312], [839, 277], [843, 196], [845, 137], [855, 99],
				[870, 90], [906, 85]
			]
		}
		{
			route : 6
			type : 2
			points [
				[866, 1319], [883, 1295], [889, 1267], [898, 1251], [905, 1234], [901, 1217],
				[889, 1211], [889, 1204], [894, 1198], [892, 1193], [896, 1176], [879, 1159],
				[888, 1135], [879, 1117], [881, 1102], [884, 1099]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [523, 494], image : "pharaoh_general/empire_bits_00120" }
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
		pharaoh_pottery_requested : false
		pharaoh_fish_requested : false
		pharaoh_beer_requested : false
		pharaoh_beer_late_requested : false
		papyrus_demand_increased : false
		clay_pit_flood_done : false
		failed_flood_last_year : -1
		kushite_invasion_1 : false
		kushite_invasion_2 : false
		kushite_invasion_3 : false
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission6_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, ok_amt, fail_amt, late_amt) {
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

function mission6_kushite_raid(invasion_id, size, on_completed_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_6_KUSHITE,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM // pak attack=4
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

[es=event_mission_start, mission=mission6]
function mission6_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	mission_show_start_message(mission, "message_soldiers_and_forts")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=1 month=0 DEMAND_INCREASE papyrus amount=6 (once)
[es=event_advance_month, mission=mission6]
function mission6_papyrus_demand_increase(ev) {
	if (mission.papyrus_demand_increased) {
		return
	}
	if (ev.years_since_start < 1) {
		return
	}
	mission.papyrus_demand_increased = true
	city.create_chain_event({
		tag_id: 601,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_PAPYRUS,
		amount: 6,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=1 month=7 pottery 14 / 9mo; ok→+6, refuse→−6, late→−4
[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_pottery(ev) {
	if (mission.pharaoh_pottery_requested) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 7)) {
		return
	}
	mission.pharaoh_pottery_requested = true
	mission6_fire_request(1, RESOURCE_POTTERY, 14, 9, 101, 102, 103, 6, 6, 4)
}

// pak: year=2 month=0 beer 11 / 12mo; ok→GIFT bricks 28 (not KR), refuse/late→−3
[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_beer(ev) {
	if (mission.pharaoh_beer_requested) {
		return
	}
	if (ev.years_since_start < 2) {
		return
	}
	mission.pharaoh_beer_requested = true
	var request = city.create_good_request({ tag_id: 2, resource: RESOURCE_BEER, amount: 11, months_initial: 12 })
	city.create_chain_event({
		tag_id: 201,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_BRICKS,
		amount: 28
	})
	city.create_chain_event({ tag_id: 202, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 3 })
	request.set_completed_action_tag(201)
	request.set_refusal_action_tag(202)
	request.set_too_late_action_tag(202)
	request.execute()
}

// pak: year=3 month=3 fish 13 / 12mo; ok→+7, refuse→−10, late→−3
[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_fish(ev) {
	if (mission.pharaoh_fish_requested) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 3)) {
		return
	}
	mission.pharaoh_fish_requested = true
	mission6_fire_request(4, RESOURCE_FISH, 13, 12, 401, 402, 403, 7, 10, 3)
}

// pak: year=17 month=0 beer 21 / 16mo; ok→+12, refuse→−7, late→−3
[es=event_advance_month, mission=mission6]
function mission6_pharaoh_request_beer_late(ev) {
	if (mission.pharaoh_beer_late_requested) {
		return
	}
	if (ev.years_since_start < 17) {
		return
	}
	mission.pharaoh_beer_late_requested = true
	mission6_fire_request(5, RESOURCE_BEER, 21, 16, 501, 502, 503, 12, 7, 3)
}

// pak: year=8 month=6 CLAY_PIT_FLOOD once — rubble one clay pit
[es=event_advance_month, mission=mission6]
function mission6_clay_pit_flood(ev) {
	if (mission.clay_pit_flood_done) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 6)) {
		return
	}
	mission.clay_pit_flood_done = true
	city.create_chain_event({
		tag_id: 801,
		type: EVENT_TYPE_CLAY_PIT_FLOOD,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=10 month=0 FAILED_FLOOD recurring — force next inundation quality to 0.
// Calendar proxy: yearly at m0 from y10+ (amount=8 from pak; months_initial not dumped).
[es=event_advance_month, mission=mission6]
function mission6_failed_flood(ev) {
	if (ev.years_since_start < 10 || ev.month != 0) {
		return
	}
	if (mission.failed_flood_last_year == ev.years_since_start) {
		return
	}
	mission.failed_flood_last_year = ev.years_since_start
	log_info("akhenaten: mission 6 behdet failed flood y" + ev.years_since_start, {ev:ev})
	city.create_chain_event({
		tag_id: 3800 + ev.years_since_start,
		type: EVENT_TYPE_FAILED_FLOOD,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak invasions (scenario enemy = Kushite). Favour-KR Pharaoh army amount=45.
// y15 wipe → REPUTATION +8 via on_completed_tag bind (engine resolve).
[es=event_advance_month, mission=mission6]
function mission6_kushite_invasion_1(ev) {
	if (mission.kushite_invasion_1) { return }
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 1)) { return }
	mission.kushite_invasion_1 = true
	log_info("akhenaten: mission 6 behdet kushite invasion 1 size=5", {ev:ev})
	mission6_kushite_raid(0, 5)
}

[es=event_advance_month, mission=mission6]
function mission6_kushite_invasion_2(ev) {
	if (mission.kushite_invasion_2) { return }
	if (ev.years_since_start < 15) { return }
	mission.kushite_invasion_2 = true
	log_info("akhenaten: mission 6 behdet kushite invasion 2 size=16", {ev:ev})
	city.create_chain_event({ tag_id: 701, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 8 })
	mission6_kushite_raid(1, 16, 701)
}

[es=event_advance_month, mission=mission6]
function mission6_kushite_invasion_3(ev) {
	if (mission.kushite_invasion_3) { return }
	if (ev.years_since_start < 19 || (ev.years_since_start == 19 && ev.month < 4)) { return }
	mission.kushite_invasion_3 = true
	log_info("akhenaten: mission 6 behdet kushite invasion 3 size=4", {ev:ev})
	mission6_kushite_raid(2, 4)
}

[es=event_advance_month, mission=mission6]
function mission6_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 45)
}
