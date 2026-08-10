log_info("akhenaten: mission 13 buhen started")

mission13 { // Buhen — Expansion to Nubia
	map_file : "data/maps/m_013_buhen.map"

	// Map points from data/maps/m_013_buhen.map.
	herd_points_prey [ [76, 29], [93, 53] ]

	start_message : "message_mission_buhen"
	selection_title : "Buhen"
	player_rank : 5

	next_mission : 15

	// pak Normal funds=10000 loan=5000 debt_interest=20 → int_dcy row (verified).
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [10000, 6700, 5000, 3300, 2700]
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
		briefing : "Voice/Mission/213_mission.mp3"
		victory : "Voice/Mission/213_victory.mp3"
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
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_OBELISK,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals verified vs mission1.pak scenario 13: pop 1/3000, culture 1/25, prosperity
	// 1/25, monuments TEMP 9 (pak raw 6; one small obelisk → formula 9, see header),
	// kingdom 1/75, housing_level 1/10 (housing count goal 0 ignored).
	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 9 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 10 }
	}

	// Map points from mission1.pak scenario 13 (disembark slot i=2 only; invasion points
	// omitted — pak inv_land_count=0 inv_sea_count=0).
	entry_point [22, 33]
	exit_point [43, 12]
	river_entry_point [56, 3]
	river_exit_point [57, 3]
	disembark_points [ [-1, -1], [-1, -1], [71, 49] ]

	enable_scenario_events : true

	// Empire from mission1.pak scenario 13 (empire id=13) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_GAMEMEAT, RESOURCE_BARLEY, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
		}

		{
			name : "Abu"
			idx : 0
			pos : [860, 1161]
			route : 3
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
			]
		}

		{
			name : "Selima Oasis"
			idx : 13
			pos : [609, 1358]
			route : 2
			is_open : false
			cost_to_open : 300
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
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Meidum"
			idx : 8
			pos : [564, 582]
			route : 4
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 9
			pos : [545, 487]
			route : 1
			is_open : false
			cost_to_open : 800
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 4000 }
			]
		}

		{
			name : "Enkomi"
			idx : 5
			pos : [679, 49]
			route : 5
			is_open : false
			cost_to_open : 1580
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_COPPER ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			// pak: buys="-" (no buys array).
			name : "Serabit Khadim"
			idx : 14
			pos : [801, 552]
			route : 6
			is_open : false
			cost_to_open : 1250
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		// Display-only cities (pak trade=0; no polyline except Dahshur route 7 stub).
		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Dahshur"
			idx : 4
			pos : [591, 550]
			route : 7
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
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
	// SKIP map_obj idx=10: empty stub, pos=0,0, no data.

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer sea
			type : 2
			points [
				[582, 536], [591, 551], [598, 606], [575, 664], [568, 726], [598, 799],
				[776, 934], [815, 913], [830, 943], [813, 987], [857, 1033], [867, 1052],
				[880, 1093], [899, 1244], [878, 1300], [865, 1322], [845, 1305], [801, 1352]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [
				[621, 1379], [661, 1364], [690, 1357], [746, 1359], [769, 1362]
			]
		}
		{
			route : 3 // Abu land
			type : 1
			points [
				[793, 1357], [784, 1346], [798, 1328], [805, 1297], [834, 1255], [846, 1232], [868, 1186]
			]
		}
		{
			route : 4 // Meidum sea
			type : 2
			points [
				[795, 1350], [846, 1300], [865, 1320], [879, 1303], [881, 1279], [899, 1246],
				[908, 1232], [895, 1208], [892, 1182], [883, 1099], [877, 1063], [863, 1036],
				[817, 995], [827, 941], [806, 914], [793, 921], [778, 930], [775, 936],
				[603, 792], [576, 729], [575, 701], [583, 658], [588, 634], [584, 598]
			]
		}
		{
			route : 5 // Enkomi sea
			type : 2
			points [
				[706, 66], [749, 81], [769, 95], [807, 123], [850, 154], [856, 165],
				[858, 191], [848, 240], [842, 278], [820, 303], [771, 329], [703, 351],
				[676, 357], [654, 354], [605, 332], [586, 334], [571, 365], [561, 380],
				[564, 390], [558, 404], [556, 420], [567, 437], [560, 484], [591, 549],
				[598, 590], [576, 667], [569, 700], [568, 710], [571, 728], [603, 798],
				[775, 934], [814, 911], [827, 945], [824, 987], [867, 1050], [881, 1093],
				[898, 1186], [901, 1246], [875, 1305], [863, 1321], [846, 1304], [819, 1324], [802, 1365]
			]
		}
		{
			route : 6 // Serabit Khadim land
			type : 1
			points [
				[816, 565], [760, 549], [739, 532], [719, 502], [709, 495], [693, 491],
				[683, 499], [673, 525], [682, 573], [751, 734], [788, 858], [798, 882],
				[801, 984], [844, 1126], [844, 1142], [840, 1164], [833, 1181], [795, 1271],
				[786, 1298], [789, 1352]
			]
		}
		// Display route 7 (Dahshur): pak polyline is empty; two-point stub + deviation
		// bends the line (same pattern as Serabit/Selima's orphan display routes).
		{
			route : 7 // Dahshur
			type : 1
			deviation : 60
			points [ [766, 1345], [591, 550] ]
		}
	]
	// SKIP routes 8/9/10: pak polylines exist but no map_obj references them (orphan).

	hide_pak_objects : true
	empire_ornaments [
		// pak: exp_img=5 (37x34) → bits_119 ×2; exp_img=6 (29x28) → bits_120;
		// exp_img=3 (28x16) → bits_117; exp_img=2 (37x22) → bits_116.
		{ pos : [840, 1094], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [706, 914], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [521, 498], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [501, 536], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [556, 566], image : "pharaoh_general/empire_bits_00116" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [408, 458] }
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
		// Chain-leaf wiring (idempotent, all wired once from on_start).
		shared_kr_leaves_wired : false
		granite_gift_leaves_wired : false
		troops_chain_leaves_wired : false

		// Once-root done flags (pak event index in the name).
		event2_limestone_done : false
		event4_limestone_done : false
		event5_limestone_done : false
		event6_troops_done : false
		event7_granite_demand_done : false
		event8_oil_done : false
		event10_limestone_done : false
		event11_beer_done : false
		event12_limestone_done : false
		event13_granite_demand_done : false
		event15_limestone_done : false

		// Recurring-root last-fired-year gate + busy/idle guard (pak i=3, beer).
		event3_beer_last_year : -1
		beer_recurring_was_busy : false
		beer_recurring_idle_since_abs : -1

		// One-shot Kushite invasions (pak i=9/14/16/17/18/19/20/21).
		kushite_i9_done : false
		kushite_i14_done : false
		kushite_i16_done : false
		kushite_i17_done : false
		kushite_i18_done : false
		kushite_i19_done : false
		kushite_i20_done : false
		kushite_i21_done : false

		// Recurring clay pit floods (pak i=22-29), fired together every year from y1m0.
		clay_pit_flood_last_year : -1

		// Favour Pharaoh invasion — three waves (pak i=48→49→50: 22→21→28).
		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		pharaoh_favour_wave2_enemies_seen : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_enemies_seen : false
		pharaoh_favour_wave3_done : false

		start_message_shown : false
	}
}

// Creates a single dormant (ONLY_VIA_EVENT) chain leaf. `resource`/`subtype`/`city_name`
// are optional. Callers chain `.set_completed_action_tag(...)` etc. off the result.
function mission13_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

// Fires a simple (non-request) calendar root — DEMAND/PRICE state changes.
function mission13_fire_simple_event(tag, type, resource, amount, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	city.create_chain_event(opts).execute()
}

// Fires a Pharaoh/city resource request wired to already-created ok/refuse/late(/defeat)
// chain leaves. `sender_faction` mirrors the pak `sender` field exactly (0=city, 1=pharaoh)
// — most Buhen requests are sender=0 except the beer recurring root (i=3, sender=1).
// Optional `defeat_tag` + `city_name` are for RESOURCE_TROOPS asks: dispatch defers to a
// distant battle and fires ok/defeat from fight_distant_battle.
function mission13_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag, city_name) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name) {
		opts.city = city_name
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
	if (defeat_tag) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.execute()
	return request
}

// Shared ONLY_VIA leaves reused by most calendar requests (pak i=30/31/32).
function mission13_ensure_shared_kr_leaves() {
	if (mission.shared_kr_leaves_wired) {
		return
	}
	mission.shared_kr_leaves_wired = true
	mission13_make_leaf(1030, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2) // i30 "ok" leaf
	mission13_make_leaf(1031, EVENT_TYPE_REPUTATION_DECREASE, undefined, 4, 2) // i31 "late" leaf
	mission13_make_leaf(1032, EVENT_TYPE_REPUTATION_DECREASE, undefined, 8, 2) // i32 "refuse" leaf
}

// Granite gift chain kicked off by the beer request (pak i=11 ok→35→39; late→40).
function mission13_ensure_granite_gift_leaves() {
	if (mission.granite_gift_leaves_wired) {
		return
	}
	mission.granite_gift_leaves_wired = true
	mission13_ensure_shared_kr_leaves()

	mission13_make_leaf(1039, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 2) // i39 ← i35.ok
	mission13_make_leaf(1040, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_GRANITE, 6, 2) // i40 ← i11.late (leaf)

	var gift = mission13_make_leaf(1035, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_GRANITE, 12, 2) // i35 ← i11.ok
	gift.set_completed_action_tag(1039)
}

// Troops chain kicked off by the troops×60 request (pak i=6). Sequence:
// i6 ok → 33 (MESSAGE saved) → 37 (KR+30) → 38 (chain-only troops×400, re-arms using
// i6's own ok/refuse/late/defeat tags). i6/i38 refuse+late → 34 → 41 → price/demand
// cascade 43→44→45→46; i6/i38 defeat → 36 → 47 → same price cascade.
// Fulfill with defeat wired defers to distant battle (equal strength → win / ok chain;
// lose → 1036). Refuse/late still fire 1034 without a battle.
function mission13_ensure_troops_chain_leaves() {
	if (mission.troops_chain_leaves_wired) {
		return
	}
	mission.troops_chain_leaves_wired = true
	mission13_ensure_shared_kr_leaves()

	// i33 MESSAGE subtype=0 = MSG_CITY_SAVED; i34/i36 CITY_STATUS subtype=0 = CITY_FELL_TO_ENEMY.
	var msg_saved = mission13_make_leaf(1033, EVENT_TYPE_MESSAGE, undefined, 5, 2, EVENT_SUBTYPE_MSG_CITY_SAVED, "Enkomi") // i33, ok→37
	var status_dahshur = mission13_make_leaf(1034, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2, EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Dahshur") // i34, ok→41
	var status_enkomi = mission13_make_leaf(1036, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2, EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Enkomi") // i36, ok→47 (defeat)
	var kr_kerma_up = mission13_make_leaf(1037, EVENT_TYPE_REPUTATION_INCREASE, undefined, 30, 2) // i37, ok→38
	var kr_kerma_down = mission13_make_leaf(1041, EVENT_TYPE_REPUTATION_DECREASE, undefined, 35, 2) // i41, ok→43
	var price_copper = mission13_make_leaf(1043, EVENT_TYPE_PRICE_INCREASE, RESOURCE_COPPER, 201, 2) // i43, ok→44
	var price_gems = mission13_make_leaf(1044, EVENT_TYPE_PRICE_INCREASE, RESOURCE_GEMS, 80, 2) // i44, ok→45
	var demand_copper = mission13_make_leaf(1045, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_COPPER, 9, 2) // i45, ok→46
	mission13_make_leaf(1046, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GEMS, 7, 2) // i46 (leaf, no ok)
	var kr_byblos_down = mission13_make_leaf(1047, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2) // i47, ok→43

	msg_saved.set_completed_action_tag(1037)
	status_dahshur.set_completed_action_tag(1041)
	status_enkomi.set_completed_action_tag(1047)
	kr_kerma_up.set_completed_action_tag(1038)
	kr_kerma_down.set_completed_action_tag(1043)
	price_copper.set_completed_action_tag(1044)
	price_gems.set_completed_action_tag(1045)
	demand_copper.set_completed_action_tag(1046)
	kr_byblos_down.set_completed_action_tag(1043)

	var troops2 = city.create_good_request({ // i38: chain-only troops×400/12mo (re-arm)
		tag_id: 1038, resource: RESOURCE_TROOPS, amount: 400, months_initial: 12, subtype: 1,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Kyrene"
	})
	troops2.set_sender_faction(0)
	troops2.set_completed_action_tag(1033)
	troops2.set_refusal_action_tag(1034)
	troops2.set_too_late_action_tag(1034)
	troops2.set_defeat_action_tag(1036)
}

// pak enemy_id=6 ENEMY_6_KUSHITE. No invasion land points in pak → auto tile (falls
// back to the map exit point, see scenario_start_invasion_impl).
function mission13_kushite_raid(invasion_id, size, attack_target) {
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_6_KUSHITE,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

[es=event_mission_start, mission=mission13]
function mission13_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN) // favour Pharaoh army (i48-50)
	__image_request_pak(PACK_OBELISK_EXTRA)
	__image_request_pak(PACK_OBELISK_X3_A)
	__image_request_pak(PACK_OBELISK_X3_B)
	__image_request_pak(PACK_OBELISK_X3_C)
	__image_request_pak(PACK_OBELISK_X3_D)
	mission_show_start_message(mission, "message_mission_buhen")
	empire.set_id(13)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	// Wire all dormant ONLY_VIA_EVENT chain leaves up front — harmless, they stay inert
	// until a root's ok/refuse/late action tag references them.
	mission13_ensure_shared_kr_leaves()
	mission13_ensure_granite_gift_leaves()
	mission13_ensure_troops_chain_leaves()
}

// Tracks resource-busy state every month so the beer recurring root below never stacks a
// fresh request while one is still active (Serabit copper / Meidum pottery pattern).
[es=event_advance_month, mission=mission13]
function mission13_recurring_request_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_BEER, "beer_recurring", abs)
}

// pak i=2: year=1 month=6 limestone×8/24mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i2_limestone_request(ev) {
	if (mission.event2_limestone_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 6)) {
		return
	}
	mission.event2_limestone_done = true
	log_info("akhenaten: mission 13 buhen i2 limestone request y1m6", {ev:ev})
	mission13_fire_request(2002, RESOURCE_LIMESTONE, 8, 24, 1030, 1032, 1031, 4, 0)
}

// pak i=3: year=2+ month=9 beer×9/24mo recurring, sender=pharaoh(1); ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i3_beer_recurring(ev) {
	if (ev.years_since_start < 2 || ev.month != 9) {
		return
	}
	if (mission.event3_beer_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_BEER, "beer_recurring", abs)) {
		return
	}
	mission.event3_beer_last_year = ev.years_since_start
	log_info("akhenaten: mission 13 buhen i3 beer recurring y" + ev.years_since_start, {ev:ev})
	mission13_fire_request(3000 + 3 * 100 + ev.years_since_start, RESOURCE_BEER, 9, 24, 1030, 1032, 1031, 0, 1)
}

// pak i=4: year=3 month=2 limestone×16/20mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i4_limestone_request(ev) {
	if (mission.event4_limestone_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 2)) {
		return
	}
	mission.event4_limestone_done = true
	log_info("akhenaten: mission 13 buhen i4 limestone request y3m2", {ev:ev})
	mission13_fire_request(2004, RESOURCE_LIMESTONE, 16, 20, 1030, 1032, 1031, 4, 0)
}

// pak i=5: year=4 month=10 limestone×25/24mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i5_limestone_request(ev) {
	if (mission.event5_limestone_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 10)) {
		return
	}
	mission.event5_limestone_done = true
	log_info("akhenaten: mission 13 buhen i5 limestone request y4m10", {ev:ev})
	mission13_fire_request(2005, RESOURCE_LIMESTONE, 25, 24, 1030, 1032, 1031, 4, 0)
}

// pak i=6: year=4 month=7 troops×60/12mo once, subtype=1 (CITY_ASKS_FOR_TROOPS);
// ok→33 (MESSAGE saved→KR+30→troops×400 re-arm) refuse/late→34 (price/demand cascade)
// pak i=6: city=Kyrene; ok→33 refuse/late→34 defeat→36. Fulfill starts a linked
// distant battle (see scenario_request_dispatch); refuse/late skip the battle.
[es=event_advance_month, mission=mission13]
function mission13_event_i6_troops_request(ev) {
	if (mission.event6_troops_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 7)) {
		return
	}
	mission.event6_troops_done = true
	log_info("akhenaten: mission 13 buhen i6 troops request y4m7", {ev:ev})
	mission13_fire_request(2006, RESOURCE_TROOPS, 60, 12, 1033, 1034, 1034, 1, 0, 1036, "Kyrene")
}

// pak i=7: year=5 month=1 DEMAND_INCREASE granite amount=6 once.
[es=event_advance_month, mission=mission13]
function mission13_event_i7_granite_demand(ev) {
	if (mission.event7_granite_demand_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 1)) {
		return
	}
	mission.event7_granite_demand_done = true
	log_info("akhenaten: mission 13 buhen i7 granite demand increase y5m1", {ev:ev})
	mission13_fire_simple_event(2007, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_GRANITE, 6)
}

// pak i=8: year=6 month=1 oil×2000/6mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i8_oil_request(ev) {
	if (mission.event8_oil_done) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 1)) {
		return
	}
	mission.event8_oil_done = true
	log_info("akhenaten: mission 13 buhen i8 oil request y6m1", {ev:ev})
	mission13_fire_request(2008, RESOURCE_OIL, 2000, 6, 1030, 1032, 1031, 4, 0)
}

// pak i=9: year=6 month=5 Kushite invasion size=8 once, attack=BEST_BUILDINGS(2).
[es=event_advance_month, mission=mission13]
function mission13_event_i9_kushite_invasion(ev) {
	if (mission.kushite_i9_done) {
		return
	}
	if (ev.years_since_start < 6 || (ev.years_since_start == 6 && ev.month < 5)) {
		return
	}
	mission.kushite_i9_done = true
	log_info("akhenaten: mission 13 buhen i9 kushite invasion size=8 y6m5", {ev:ev})
	mission13_kushite_raid(0, 8, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=10: year=7 month=2 limestone×32/24mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i10_limestone_request(ev) {
	if (mission.event10_limestone_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 2)) {
		return
	}
	mission.event10_limestone_done = true
	log_info("akhenaten: mission 13 buhen i10 limestone request y7m2", {ev:ev})
	mission13_fire_request(2010, RESOURCE_LIMESTONE, 32, 24, 1030, 1032, 1031, 4, 0)
}

// pak i=11: year=7 month=4 beer×13/8mo once, subtype=3 (REQ_FOR_FESTIVAL); ok→35 (gift
// granite×12→KR+9) refuse→32 (shared refuse) late→40 (gift granite×6, leaf).
[es=event_advance_month, mission=mission13]
function mission13_event_i11_beer_request(ev) {
	if (mission.event11_beer_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 4)) {
		return
	}
	mission.event11_beer_done = true
	log_info("akhenaten: mission 13 buhen i11 beer request y7m4 (gift chain)", {ev:ev})
	mission13_fire_request(2011, RESOURCE_BEER, 13, 8, 1035, 1032, 1040, 3, 0)
}

// pak i=12: year=9 month=11 limestone×20/12mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i12_limestone_request(ev) {
	if (mission.event12_limestone_done) {
		return
	}
	if (ev.years_since_start < 9 || (ev.years_since_start == 9 && ev.month < 11)) {
		return
	}
	mission.event12_limestone_done = true
	log_info("akhenaten: mission 13 buhen i12 limestone request y9m11", {ev:ev})
	mission13_fire_request(2012, RESOURCE_LIMESTONE, 20, 12, 1030, 1032, 1031, 4, 0)
}

// pak i=13: year=10 month=0 DEMAND_INCREASE granite amount=5 once.
[es=event_advance_month, mission=mission13]
function mission13_event_i13_granite_demand(ev) {
	if (mission.event13_granite_demand_done) {
		return
	}
	if (ev.years_since_start < 10) {
		return
	}
	mission.event13_granite_demand_done = true
	log_info("akhenaten: mission 13 buhen i13 granite demand increase y10m0", {ev:ev})
	mission13_fire_simple_event(2013, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_GRANITE, 5)
}

// pak i=14: year=10 month=6 Kushite invasion size=16 once, attack=BEST_BUILDINGS(2).
[es=event_advance_month, mission=mission13]
function mission13_event_i14_kushite_invasion(ev) {
	if (mission.kushite_i14_done) {
		return
	}
	if (ev.years_since_start < 10 || (ev.years_since_start == 10 && ev.month < 6)) {
		return
	}
	mission.kushite_i14_done = true
	log_info("akhenaten: mission 13 buhen i14 kushite invasion size=16 y10m6", {ev:ev})
	mission13_kushite_raid(1, 16, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=15: year=11 month=7 limestone×11/18mo once; ok→KR+6 refuse→KR−8 late→KR−4.
[es=event_advance_month, mission=mission13]
function mission13_event_i15_limestone_request(ev) {
	if (mission.event15_limestone_done) {
		return
	}
	if (ev.years_since_start < 11 || (ev.years_since_start == 11 && ev.month < 7)) {
		return
	}
	mission.event15_limestone_done = true
	log_info("akhenaten: mission 13 buhen i15 limestone request y11m7", {ev:ev})
	mission13_fire_request(2015, RESOURCE_LIMESTONE, 11, 18, 1030, 1032, 1031, 4, 0)
}

// pak i=16: year=12 month=8 Kushite invasion size=16 once, attack=RANDOM(4).
[es=event_advance_month, mission=mission13]
function mission13_event_i16_kushite_invasion(ev) {
	if (mission.kushite_i16_done) {
		return
	}
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 8)) {
		return
	}
	mission.kushite_i16_done = true
	log_info("akhenaten: mission 13 buhen i16 kushite invasion size=16 y12m8", {ev:ev})
	mission13_kushite_raid(2, 16, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=17: year=13 month=3 Kushite invasion size=24 once, attack=RANDOM(4).
[es=event_advance_month, mission=mission13]
function mission13_event_i17_kushite_invasion(ev) {
	if (mission.kushite_i17_done) {
		return
	}
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 3)) {
		return
	}
	mission.kushite_i17_done = true
	log_info("akhenaten: mission 13 buhen i17 kushite invasion size=24 y13m3", {ev:ev})
	mission13_kushite_raid(3, 24, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=18: year=15 month=5 Kushite invasion size=24 once, attack=VAULTS(1).
[es=event_advance_month, mission=mission13]
function mission13_event_i18_kushite_invasion(ev) {
	if (mission.kushite_i18_done) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 5)) {
		return
	}
	mission.kushite_i18_done = true
	log_info("akhenaten: mission 13 buhen i18 kushite invasion size=24 y15m5", {ev:ev})
	mission13_kushite_raid(4, 24, EVENT_ATTACK_TARGET_VAULTS)
}

// pak i=19: year=17 month=1 Kushite invasion size=32 once, attack=FOOD(0).
[es=event_advance_month, mission=mission13]
function mission13_event_i19_kushite_invasion(ev) {
	if (mission.kushite_i19_done) {
		return
	}
	if (ev.years_since_start < 17 || (ev.years_since_start == 17 && ev.month < 1)) {
		return
	}
	mission.kushite_i19_done = true
	log_info("akhenaten: mission 13 buhen i19 kushite invasion size=32 y17m1", {ev:ev})
	mission13_kushite_raid(5, 32, EVENT_ATTACK_TARGET_FOOD)
}

// pak i=20: year=18 month=1 Kushite invasion size=32 once, attack=BEST_BUILDINGS(2).
[es=event_advance_month, mission=mission13]
function mission13_event_i20_kushite_invasion(ev) {
	if (mission.kushite_i20_done) {
		return
	}
	if (ev.years_since_start < 18 || (ev.years_since_start == 18 && ev.month < 1)) {
		return
	}
	mission.kushite_i20_done = true
	log_info("akhenaten: mission 13 buhen i20 kushite invasion size=32 y18m1", {ev:ev})
	mission13_kushite_raid(6, 32, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=21: year=20 month=8 Kushite invasion size=36 once, attack=RANDOM(4).
[es=event_advance_month, mission=mission13]
function mission13_event_i21_kushite_invasion(ev) {
	if (mission.kushite_i21_done) {
		return
	}
	if (ev.years_since_start < 20 || (ev.years_since_start == 20 && ev.month < 8)) {
		return
	}
	mission.kushite_i21_done = true
	log_info("akhenaten: mission 13 buhen i21 kushite invasion size=36 y20m8", {ev:ev})
	mission13_kushite_raid(7, 36, EVENT_ATTACK_TARGET_RANDOM)
}

// pak i=22-29: year=1+ month=0 CLAY_PIT_FLOOD recurring ×8 (amounts 8,8,9,5,8,6,9,5).
// Fires every year from y1 onward (needs a working clay pit; handler ignores amount and
// hits one random working pit, same as Serabit's i=16-20 pattern).
[es=event_advance_month, mission=mission13]
function mission13_clay_pit_flood_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 0) {
		return
	}
	if (mission.clay_pit_flood_last_year == ev.years_since_start) {
		return
	}
	mission.clay_pit_flood_last_year = ev.years_since_start
	var y = ev.years_since_start
	var amounts = [8, 8, 9, 5, 8, 6, 9, 5]
	log_info("akhenaten: mission 13 buhen clay pit floods y" + y, {ev:ev})
	for (var i = 0; i < amounts.length; i++) {
		city.create_chain_event({
			tag_id: 4000 + y * 10 + i,
			type: EVENT_TYPE_CLAY_PIT_FLOOD,
			amount: amounts[i],
			trigger: EVENT_TRIGGER_ONCE
		}).execute()
	}
}

// pak i=48/49/50: by_favour Pharaoh army size=22 → 21 → 28.
[es=event_advance_month, mission=mission13]
function mission13_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, [22, 21, 28])
}
