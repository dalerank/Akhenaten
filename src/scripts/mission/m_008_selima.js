log_info("akhenaten: mission 8 selima started")

// Empire / requests / invasions aligned with original campaign scenario 8 (2026-07-25 dump).
// Favour Pharaoh army size=63 (trigger=by_favour) via mission_pharaoh_favour_invasion_tick.
// Hyksos wipe/refuse → chain tags on start_foreign_army_invasion (engine bind resolve).
// No EVENT_TYPE_DISTANT_BATTLE in pak — Kerma pressure is CITY_UNDER_SIEGE (+ troop request chain).

mission8 { // Selima — The Road to Africa
	map_file : "data/maps/m_008_selima.map"

	// Map points from data/maps/m_008_selima.map.
	herd_points_prey [ [70, 49], [53, 87] ]

	start_message : "message_the_finer_things_tutorial"
	selection_title : "Selima"
	player_rank : 3
	next_mission : 10
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		hide_nilometer : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/208_mission.mp3"
		victory : "Voice/Mission/20_victory.mp3"
	}

	buildings [
                BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
				BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
                BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
				BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
                BUILDING_WOOD_CUTTERS, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP,
				BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
                BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
                BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
				BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_ALTAR_ANUBIS, BUILDING_TEMPLE_COMPLEX_ORACLE_SEKHMET,
				BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
                BUILDING_SCRIBAL_SCHOOL,
			  ]

	// Win ratings match original campaign scenario 8.
	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 20 }
		prosperity    {enabled : true, goal : 20 }
		kingdom       {enabled : true, goal : 55 }
		housing_level {enabled : true, goal : 10 }
		monuments     {enabled : false }
	}

	// Map points from original campaign scenario 8 (desert oasis — no river / disembark).
	entry_point [35, 20]
	exit_point [90, 77]
	invasion_points_land [ [99, 65], [8, 62], [69, 13] ]

	enable_scenario_events : true

	// Empire from original campaign scenario 8 (empire id=0) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Selima Oasis"
			idx : 9
			pos : [615, 1354]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_TIMBER ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
		}

		{
			name : "Men-nefer"
			idx : 5
			pos : [530, 485]
			route : 1
			is_open : false
			cost_to_open : 1100
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
			name : "Timna"
			idx : 10
			pos : [906, 456]
			route : 2
			is_open : false
			cost_to_open : 1650
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
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 3
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
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
			name : "Abedju"
			idx : 0
			pos : [696, 907]
			route : 4
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_BRICKS, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
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
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Kerma"
			idx : 3
			pos : [729, 1489]
			route : 9
			is_open : false
			cost_to_open : 450
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
			]
		}

		// Display-only cities on the empire map (pak route ids; no trade).
		{
			name : "Byblos"
			idx : 2
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
			name : "Nekhen"
			idx : 7
			pos : [797, 1011]
			route : 6
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Nubt"
			idx : 8
			pos : [800, 933]
			route : 7
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
				[631, 1376], [458, 804], [404, 622], [394, 578], [395, 551], [409, 527],
				[432, 515], [465, 509], [561, 505]
			]
		}
		{
			route : 2
			type : 1
			points [
				[647, 1370], [894, 1182], [1020, 1205], [1056, 1206], [1074, 1187], [1074, 1167],
				[1061, 1110], [1058, 1065], [1043, 1041], [1041, 1013], [1007, 930], [926, 850],
				[915, 848], [883, 859], [869, 862], [854, 855], [837, 837], [831, 813],
				[846, 799], [861, 798], [871, 789], [871, 773], [841, 738], [827, 712],
				[788, 673], [720, 624], [677, 562], [666, 512], [681, 486], [733, 473],
				[921, 472]
			]
		}
		{
			route : 3
			type : 1
			points [ [636, 1367], [689, 1296], [852, 1083] ]
		}
		{
			route : 4
			type : 1
			points [ [633, 1375], [708, 924] ]
		}
		{
			route : 9
			type : 1
			points [
				[746, 1511], [733, 1532], [722, 1546], [706, 1544], [686, 1536], [669, 1531],
				[671, 1518], [669, 1505], [667, 1498], [662, 1479], [657, 1462], [648, 1448],
				[638, 1418], [634, 1391], [633, 1375]
			]
		}
		// Display Nekhen (pak route=6). Geography is the west approach (near Kyrene).
		{
			route : 6
			type : 1
			points [ [56, 427], [357, 975], [622, 1372] ]
		}
		// Display routes 7/8/10: two-point stubs; improve_route + deviation bends the line.
		{
			route : 7 // Nubt
			type : 1
			deviation : 40
			points [ [633, 1375], [800, 933] ]
		}
		{
			route : 8 // Kyrene
			type : 1
			deviation : 60
			points [ [633, 1375], [22, 341] ]
		}
		{
			route : 10 // Byblos
			type : 1
			deviation : 50
			points [ [633, 1375], [891, 68] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// pak w/h 29x28 → mastaba bits; 37x34 → neighbouring ornament frame.
		{ pos : [510, 490], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [839, 1095], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [666, 891], image : "pharaoh_general/empire_bits_00119" }
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
		pharaoh_luxury_request_count : 0
		pharaoh_troops_requested_1 : false
		pharaoh_troops_requested_2 : false
		troops4_wired : false
		kerma_siege_done : false
		luxury_price_decreased : false
		reeds_price_increased : false
		wage_increase_done : false
		hyksos_raid_small_last_year : -1
		hyksos_raid_small_seq : 0
		hyksos_invasion_2 : false
		pharaoh_favour_invasion_done : false
		start_message_shown : false
	}
}

function mission8_hyksos_raid(invasion_id, size, on_completed_tag, on_refusal_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_TROOPS // pak attack=3
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	if (on_refusal_tag) {
		opts.on_refusal_tag = on_refusal_tag
	}
	return city.start_foreign_army_invasion(opts)
}

[es=event_mission_start, mission=mission8]
function mission8_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_TEMPLE_SETH)
	mission_show_start_message(mission, "message_the_finer_things_tutorial")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=0 month=2 PRICE_DECREASE luxury_goods amount=10 once (buy/sell table via trade_price_change).
[es=event_advance_month, mission=mission8]
function mission8_luxury_price_decrease(ev) {
	if (mission.luxury_price_decreased) {
		return
	}
	if (ev.years_since_start > 0 || ev.month < 2) {
		return
	}
	mission.luxury_price_decreased = true
	city.create_chain_event({
		tag_id: 901,
		type: EVENT_TYPE_PRICE_DECREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 10,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: luxury_goods 2 / 4mo from y1m0, trigger=recurring — re-request every 2 years.
// ok→+10; refuse→−19; late→KR+2→Kerma siege→troops×4 (pak late=i=9→i=1→i=19, same as Hyksos×22 wipe).
[es=event_advance_month, mission=mission8]
function mission8_pharaoh_request_luxury(ev) {
	var next_year = 1 + mission.pharaoh_luxury_request_count * 2
	if (ev.years_since_start < next_year) {
		return
	}
	mission.pharaoh_luxury_request_count = mission.pharaoh_luxury_request_count + 1
	var n = mission.pharaoh_luxury_request_count
	var base = n * 10
	log_info("akhenaten: mission 8 selima luxury request #" + n, {ev:ev})
	var request = city.create_good_request({
		tag_id: base,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 2,
		months_initial: 4
	})
	city.create_chain_event({ tag_id: base + 1, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 10 })
	city.create_chain_event({ tag_id: base + 2, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 19 })
	var late_kr = city.create_chain_event({ tag_id: base + 3, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 2 })
	var late_siege = city.create_chain_event({
		tag_id: base + 4,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 4, // EVENT_SUBTYPE_CITY_UNDER_SIEGE
		city: "Kerma",
		amount: 3
	})
	late_kr.set_completed_action_tag(base + 4)
	mission8_ensure_troops_request_4(true)
	late_siege.set_completed_action_tag(4)
	request.set_completed_action_tag(base + 1)
	request.set_refusal_action_tag(base + 2)
	request.set_too_late_action_tag(base + 3)
	request.execute()
}

// pak: year=2 month=4 enemy size=9 recurring (months=12 → yearly m4). ok→KR+2.
// Bind on_completed_tag; skip while prior small-raid seq still NONE (B2-migrate).
[es=event_advance_month, mission=mission8]
function mission8_hyksos_invasion_1(ev) {
	if (ev.years_since_start < 2 || ev.month != 4) {
		return
	}
	if (mission.hyksos_raid_small_last_year == ev.years_since_start) {
		return
	}
	var prev = mission.hyksos_raid_small_seq | 0
	if (prev > 0) {
		var prev_out = mission_pharaoh_favour_invasion_outcome(prev)
		if (prev_out < 0 || prev_out == 0) {
			return
		}
	}
	mission.hyksos_raid_small_last_year = ev.years_since_start
	var ok_tag = 1000 + ev.years_since_start
	city.create_chain_event({
		tag_id: ok_tag,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 2
	})
	log_info("akhenaten: mission 8 selima hyksos raid size=9 year=" + ev.years_since_start + " ok_tag=" + ok_tag, {ev:ev})
	mission.hyksos_raid_small_seq = mission8_hyksos_raid(0, 9, ok_tag, 0)
}

// pak: year=7 month=0 enemy size=22 once.
// ok→KR+2→CITY_UNDER_SIEGE Kerma→troops×4; refuse→KR−2→troops×4.
[es=event_advance_month, mission=mission8]
function mission8_hyksos_invasion_2(ev) {
	if (mission.hyksos_invasion_2) {
		return
	}
	if (ev.years_since_start < 7) {
		return
	}
	mission.hyksos_invasion_2 = true
	log_info("akhenaten: mission 8 selima hyksos invasion 2 size=22", {ev:ev})

	var ok = city.create_chain_event({
		tag_id: 801,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 2
	})
	var siege = city.create_chain_event({
		tag_id: 710,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 4, // EVENT_SUBTYPE_CITY_UNDER_SIEGE (pak i=1)
		city: "Kerma",
		amount: 3
	})
	var refuse = city.create_chain_event({
		tag_id: 802,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 2
	})
	ok.set_completed_action_tag(710)
	// Troops×4 fires after wipe (via siege) or refuse; luxury late may already wire tag 4.
	mission8_ensure_troops_request_4(true)
	siege.set_completed_action_tag(4)
	refuse.set_completed_action_tag(4)

	mission8_hyksos_raid(1, 22, 801, 802)
}

// pak: year=7 month=8 CITY_UNDER_SIEGE Kerma once → ok→troops×7 / 12mo (chain_only).
// create_good_request is ONCE (cannot be chain child); fire siege + request same month.
// Troops×7 tails (pak i=8): ok/late→MESSAGE city_saved (Nubt)→NEW_TRADE_ROUTE;
// refuse/defeat→MESSAGE battle_lost (Nubt)→KR −10. No KR on success.
// pak NEW_TRADE city_id=5 is Kyrene (display); open Men-nefer (playable trade unlock).
[es=event_advance_month, mission=mission8]
function mission8_kerma_siege_and_troops(ev) {
	if (mission.kerma_siege_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 8)) {
		return
	}
	mission.kerma_siege_done = true
	mission.pharaoh_troops_requested_1 = true
	log_info("akhenaten: mission 8 selima Kerma under siege → troops request 7", {ev:ev})

	city.create_chain_event({
		tag_id: 700,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 4, // EVENT_SUBTYPE_CITY_UNDER_SIEGE
		city: "Kerma",
		amount: 12, // months under siege (months_initial unset on chain events)
		trigger: EVENT_TRIGGER_ONCE
	}).execute()

	var request = city.create_good_request({
		tag_id: 3,
		resource: RESOURCE_TROOPS,
		amount: 7,
		months_initial: 12,
		subtype: 1 // EVENT_SUBTYPE_CITY_ASKS_FOR_TROOPS (pak i=8)
	})
	var ok_msg = city.create_chain_event({
		tag_id: 310,
		type: EVENT_TYPE_MESSAGE,
		subtype: EVENT_SUBTYPE_MSG_CITY_SAVED
		city: "Nubt",
		amount: 2
	})
	city.create_chain_event({
		tag_id: 311,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE — pak city_id=5=Kyrene; open Men-nefer
		city: "Men-nefer",
		amount: 4
	})
	ok_msg.set_completed_action_tag(311)

	var fail_msg = city.create_chain_event({
		tag_id: 312,
		type: EVENT_TYPE_MESSAGE,
		subtype: 2, // EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST
		city: "Nubt",
		amount: 3
	})
	city.create_chain_event({ tag_id: 313, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 10 })
	fail_msg.set_completed_action_tag(313)

	request.set_completed_action_tag(310)
	request.set_too_late_action_tag(310)
	request.set_refusal_action_tag(312)
	request.execute()
}

// pak: year=8 month=0 PRICE_INCREASE reeds amount=7 once.
[es=event_advance_month, mission=mission8]
function mission8_reeds_price_increase(ev) {
	if (mission.reeds_price_increased) {
		return
	}
	if (ev.years_since_start < 8) {
		return
	}
	mission.reeds_price_increased = true
	city.create_chain_event({
		tag_id: 902,
		type: EVENT_TYPE_PRICE_INCREASE,
		resource: RESOURCE_REEDS,
		amount: 7,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=8 month=8 DEMAND_INCREASE timber amount=2 recurring — yearly m8 from year 8.
[es=event_advance_month, mission=mission8]
function mission8_timber_demand_increase(ev) {
	if (ev.years_since_start < 8 || ev.month != 8) {
		return
	}
	city.create_chain_event({
		tag_id: 910 + ev.years_since_start,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_TIMBER,
		amount: 2,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak: year=10 month=4 WAGE_INCREASE once
[es=event_advance_month, mission=mission8]
function mission8_wage_increase(ev) {
	if (mission.wage_increase_done) {
		return
	}
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 4)) {
		return
	}
	mission.wage_increase_done = true
	city.create_chain_event({
		tag_id: 904,
		type: EVENT_TYPE_WAGE_INCREASE,
		amount: 4,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=19: troops×4 / 16mo. From Hyksos×22 wipe / luxury late (i=9→i=1→i=19).
// subtype=2 distant_battle. ok→MESSAGE→NEW_TRADE(Men-nefer)→KR+2; refuse→lost→KR−2; late→lost.
// as_chain_child=true → ONLY_VIA_EVENT template (luxury late siege); else ONCE+execute.
function mission8_ensure_troops_request_4(as_chain_child) {
	if (mission.troops4_wired) {
		return null
	}
	mission.troops4_wired = true
	log_info("akhenaten: mission 8 selima troops request 4" + (as_chain_child ? " (chain)" : ""))

	var opts = {
		tag_id: 4,
		resource: RESOURCE_TROOPS,
		amount: 4,
		months_initial: 16,
		subtype: 2 // EVENT_SUBTYPE_DISTANT_BATTLE (pak i=19)
	}
	if (as_chain_child) {
		opts.trigger = EVENT_TRIGGER_ONLY_VIA_EVENT
	}
	var request = city.create_good_request(opts)
	var ok_msg = city.create_chain_event({
		tag_id: 410,
		type: EVENT_TYPE_MESSAGE,
		subtype: 1, // EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED
		city: "Men-nefer",
		amount: 5
	})
	var ok_trade = city.create_chain_event({
		tag_id: 411,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE
		city: "Men-nefer",
		amount: 2
	})
	city.create_chain_event({ tag_id: 412, type: EVENT_TYPE_REPUTATION_INCREASE, amount: 2 })
	ok_msg.set_completed_action_tag(411)
	ok_trade.set_completed_action_tag(412)

	var fail_msg = city.create_chain_event({
		tag_id: 413,
		type: EVENT_TYPE_MESSAGE,
		subtype: 2, // EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST
		city: "Kyrene",
		amount: 7
	})
	city.create_chain_event({ tag_id: 414, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 2 })
	fail_msg.set_completed_action_tag(414)

	city.create_chain_event({
		tag_id: 415,
		type: EVENT_TYPE_MESSAGE,
		subtype: 2, // late = battle_lost (Men-nefer); skip pak ok→re-request
		city: "Men-nefer",
		amount: 5
	})

	request.set_completed_action_tag(410)
	request.set_refusal_action_tag(413)
	request.set_too_late_action_tag(415)
	return request
}

function mission8_fire_troops_request_4() {
	if (mission.pharaoh_troops_requested_2) {
		return
	}
	mission.pharaoh_troops_requested_2 = true
	if (mission.troops4_wired) {
		// Luxury prepared ONLY_VIA template — activate if late never did (one-shot master).
		__city_event_fire_chain(4)
		return
	}
	var request = mission8_ensure_troops_request_4(false)
	if (request) {
		request.execute()
	}
}

// pak: year=19 month=2 DEMAND_INCREASE luxury_goods amount=3 recurring — yearly m2 from year 19.
[es=event_advance_month, mission=mission8]
function mission8_luxury_demand_increase(ev) {
	if (ev.years_since_start < 19 || ev.month != 2) {
		return
	}
	city.create_chain_event({
		tag_id: 930 + ev.years_since_start,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_LUXURY_GOODS,
		amount: 3,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

[es=event_advance_month, mission=mission8]
function mission8_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 63)
}
