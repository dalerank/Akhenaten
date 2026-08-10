log_info("akhenaten: mission 18 rostja started")

// Empire / requests / events verified vs mission1.pak scenario 18 (2026-07-26 dump).
// Empire id=18. Enemy ENEMY_5_HYKSOS. Gods: Ra, Ptah.
// Trade: On (sea 500) / Byblos (sea 1250). Display routes 3/4 (Iunet/Dahshur).
// Favour Pharaoh 50→20→50. Timed Hyksos×6 y5m7; recurring×10 y26m10+.
// Triage: SKIP orphan routes 5/6/25; SKIP map_obj idx=6 empty;
// Kyrene route 7 / Men-nefer route 19 — no polyline → 2-pt stubs + deviation.
// NEW_TRADE i=20 copy Men-nefer; i=32/42/43 Nekhen→remap Iunet (route 3).
// EVENT_TYPE_INVASION chain leaves no-op → JS via event_request_cleared:
// gems crisis refuse/late → Hyksos×11; troops refuse/defeat → Hyksos×9 → re-arm ×47.
// Monuments goal 53 (Sphinx + complex + medium true pyramid).
//
// Tag_id scheme:
//   1000 + i               chain-only ONLY_VIA_EVENT leaves / chain requests
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission18 { // Rostja (Giza) — The Great Pyramid and Sphinx
	map_file : "data/maps/m_018_rostja.map"

	// Map points from data/maps/m_018_rostja.map.
	herd_points_prey [ [47, 86], [19, 80], [62, 110], [107, 49] ]

	start_message : "message_mission_giza"
	selection_title : "Rostja"
	player_rank : 6

	// Convergence of the Iunet/On fork; next choice Bahariya (19) / Djedu (20).
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 43]
	choice [
		{
			name : "Bahariya"
			id : 19
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 44]
			pos [620, 420]
		}
		{
			name : "Djedu"
			id : 20
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 45]
			pos [640, 480]
		}
	]

	// pak Normal funds=10000 loan=5000 debt_interest=20 → int_dcy around Normal.
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
		briefing : "Voice/Mission/218_mission.mp3"
		victory : "Voice/Mission/218_victory.mp3"
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
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_CLAY_PIT,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_MEDIUM_STEPPED_PYRAMID,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_PYRAMID_COMPLEX, BUILDING_MEDIUM_PYRAMID, BUILDING_SPHINX,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_PAVILLION,
		BUILDING_SCRIBAL_SCHOOL,
	]

	win_criteria {
		population    {enabled : false }
		culture       {enabled : false }
		prosperity    {enabled : false }
		monuments     {enabled : true, goal : 53 }
		kingdom       {enabled : true, goal : 50 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [133, 120]
	exit_point [9, 76]
	river_entry_point [152, 101]
	river_exit_point [88, 4]
	disembark_points [ [-1, -1], [-1, -1], [110, 43] ]
	invasion_points_land [ [138, 136] ]
	invasion_points_sea [ [115, 53] ]

	// pak burial_provisions (scenario 18 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_BEER, required: 6 }
		{ resource: RESOURCE_GEMS, required: 6 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 3 }
		{ resource: RESOURCE_TIMBER, required: 18 }
		{ resource: RESOURCE_GRANITE, required: 12 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Rostja"
			idx : 9
			pos : [494, 499]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_STONE ]
			buys [ RESOURCE_LIMESTONE ]
		}

		{
			name : "On"
			idx : 8
			pos : [572, 454]
			route : 1
			is_open : false
			cost_to_open : 500
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 2
			is_open : false
			cost_to_open : 1250
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
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			// Display egyptian; unlocked via NEW_TRADE (pak Nekhen→remap Iunet).
			name : "Iunet"
			idx : 3
			pos : [783, 892]
			route : 3
			is_open : false
			cost_to_open : 700
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Dahshur"
			idx : 2
			pos : [576, 540]
			route : 4
			is_open : false
			cost_to_open : 100
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Unlocked via gems ladder NEW_TRADE (pak i=20 copy).
			name : "Men-nefer"
			idx : 5
			pos : [545, 487]
			route : 19
			is_open : false
			cost_to_open : 0
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_PHARAOH
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STONE, RESOURCE_BEER ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Kyrene"
			idx : 4
			pos : [22, 341]
			route : 7
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Buhen"
			idx : 0
			pos : [766, 1345]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Nekhen"
			idx : 7
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 10
			pos : [523, 539]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Bahariya Oasis"
			idx : 28
			pos : [398, 648]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // On sea
			type : 2
			points [
				[586, 472], [571, 498], [577, 523], [588, 553], [592, 581], [599, 600],
				[599, 609], [588, 619], [576, 604], [560, 574], [558, 537], [524, 520]
			]
		}
		{
			route : 2 // Byblos sea
			type : 2
			points [
				[909, 84], [867, 132], [849, 222], [796, 331], [647, 348], [620, 387],
				[591, 400], [587, 422], [572, 436], [555, 480], [560, 495], [575, 524],
				[589, 576], [594, 610], [586, 613], [561, 570], [559, 538], [524, 517]
			]
		}
		{
			route : 3 // Iunet sea (display → NEW_TRADE unlock)
			type : 2
			points [
				[798, 916], [776, 934], [760, 925], [760, 914], [747, 919], [722, 900],
				[719, 887], [703, 885], [677, 863], [676, 853], [655, 842], [656, 833],
				[642, 823], [633, 823], [626, 816], [611, 814], [594, 793], [594, 776],
				[585, 759], [584, 742], [567, 725], [569, 711], [570, 667], [584, 646],
				[584, 630], [599, 611], [574, 545], [515, 518], [515, 517]
			]
		}
		{
			route : 4 // Dahshur land (display)
			type : 1
			points [
				[586, 559], [567, 558], [564, 548], [543, 536], [514, 521], [515, 520]
			]
		}
		{
			// Kyrene display — no pak polyline; 2-pt stub.
			route : 7
			type : 1
			deviation : 40
			points [ [22, 341], [494, 499] ]
		}
		{
			// Men-nefer display — no pak polyline; 2-pt stub.
			route : 19
			type : 1
			deviation : 40
			points [ [545, 487], [494, 499] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [527, 494], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [497, 542], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [609, 536], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [568, 589], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [722, 912], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [842, 1091], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [783, 1327], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [820, 888], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [594, 441], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [627, 551], image : "pharaoh_general/empire_bits_00118" }
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
		shared_kr_leaves_wired : false
		gems_ladder_leaves_wired : false
		troops_chain_leaves_wired : false
		pharaoh_gift_leaves_wired : false

		event4_sea_done : false
		event5_wage_done : false
		event6_price_done : false
		event7_price_done : false
		event8_demand_done : false
		event9_price_done : false
		event10_demand_done : false
		event11_price_done : false
		event12_gamemeat_done : false
		event14_gems_done : false
		event15_gift_done : false
		event19_gems_done : false
		event26_hyksos_done : false
		event27_gems_done : false
		event30_troops_done : false
		event42_trade_done : false
		event43_trade_done : false

		event0_gems_last_year : -1
		gems_recurring_was_busy : false
		gems_recurring_idle_since_abs : -1

		event16_gamemeat_last_year : -1
		gamemeat_pharaoh_recurring_was_busy : false
		gamemeat_pharaoh_recurring_idle_since_abs : -1

		event36_gamemeat_last_year : -1
		gamemeat_city_recurring_was_busy : false
		gamemeat_city_recurring_idle_since_abs : -1

		event38_timber_last_year : -1
		timber_recurring_was_busy : false
		timber_recurring_idle_since_abs : -1

		event37_hyksos_last_year : -1

		gems_crisis_raid_done : false
		troops_rearm_seq : 0
		troops_kr_seq : 0

		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		// Legacy mid-save (pre-B7 local poll):
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_wave2_enemies_seen : false
		pharaoh_favour_wave3_enemies_seen : false

		start_message_shown : false
	}
}

function mission18_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission18_fire_simple_event(tag, type, resource, amount, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	city.create_chain_event(opts).execute()
}

function mission18_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag, city_name) {
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

function mission18_hyksos_raid(invasion_id, size, attack_target, on_completed_tag) {
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	}
	if (on_completed_tag) {
		opts.on_completed_tag = on_completed_tag
	}
	city.start_foreign_army_invasion(opts)
}

// Shared KR leaves: i=1 (+4 ok), i=2 (−1 refuse), i=3 (+1 late; do NOT wire ok→sea i=4).
function mission18_ensure_shared_kr_leaves() {
	if (mission.shared_kr_leaves_wired) {
		return
	}
	mission.shared_kr_leaves_wired = true
	mission18_make_leaf(1001, EVENT_TYPE_REPUTATION_INCREASE, undefined, 4, 2)
	mission18_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 1, 2)
	mission18_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 1, 24)
}

// pak i=19 gems ladder: ok→20 NEW_TRADE Men-nefer→21 gems→22 copper;
// refuse→23 KR−5→24 luxury (ok→20; late→25 KR+1→24).
function mission18_ensure_gems_ladder_leaves() {
	if (mission.gems_ladder_leaves_wired) {
		return
	}
	mission.gems_ladder_leaves_wired = true
	var trade = mission18_make_leaf(1020, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	var gems2 = city.create_good_request({
		tag_id: 1021, resource: RESOURCE_GEMS, amount: 14, months_initial: 9,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gems2.set_sender_faction(0)
	gems2.set_completed_action_tag(1022)
	var copper = mission18_make_leaf(1022, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 23, 2)
	copper.set_refusal_action_tag(1021)
	copper.set_too_late_action_tag(1021)
	var kr_refuse = mission18_make_leaf(1023, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	var luxury = city.create_good_request({
		tag_id: 1024, resource: RESOURCE_LUXURY_GOODS, amount: 11, months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	luxury.set_sender_faction(0)
	luxury.set_completed_action_tag(1020)
	luxury.set_refusal_action_tag(1023)
	luxury.set_too_late_action_tag(1025)
	var kr_late = mission18_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 1, 2)
	trade.set_completed_action_tag(1021)
	kr_refuse.set_completed_action_tag(1024)
	kr_late.set_completed_action_tag(1024)
}

// Pharaoh gift / request chain leaves (i=13/17/39) + gems crisis MESSAGE (i=28).
function mission18_ensure_pharaoh_gift_leaves() {
	if (mission.pharaoh_gift_leaves_wired) {
		return
	}
	mission.pharaoh_gift_leaves_wired = true
	mission18_ensure_shared_kr_leaves()
	mission18_make_leaf(1013, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LIMESTONE, 14, 2)
	mission18_make_leaf(1017, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_TIMBER, 14, 2)
	mission18_make_leaf(1039, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_POTTERY, 7, 2)
	// i=28 MESSAGE ack; i=29 invasion no-op → JS raid via event_request_cleared; 1029 = KR−1.
	mission18_make_leaf(1028, EVENT_TYPE_MESSAGE, undefined, 7, 2,
		EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT, "Nekhen")
	mission18_make_leaf(1029, EVENT_TYPE_REPUTATION_DECREASE, undefined, 1, 2)
}

// Troops chain: ok→31 KR+3→32 NEW_TRADE Iunet; late→33 SEA→34 troops×47 (first re-arm only).
// Refuse/defeat → JS Hyksos×9 + unique KR−2 + fresh re-arm tag (unique tags remain hygiene; B14 allows shared).
// 1035: silent defeat-deferral stub (on_defeat_action >= 0); HAILSTORM is a no-op handler.
function mission18_ensure_troops_chain_leaves() {
	if (mission.troops_chain_leaves_wired) {
		return
	}
	mission.troops_chain_leaves_wired = true
	var kr_ok = mission18_make_leaf(1031, EVENT_TYPE_REPUTATION_INCREASE, undefined, 3, 2)
	mission18_make_leaf(1032, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Iunet")
	var sea = mission18_make_leaf(1033, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 5, 2)
	mission18_make_leaf(1035, EVENT_TYPE_HAILSTORM, undefined, 0, 2)
	var troops2 = city.create_good_request({
		tag_id: 1034, resource: RESOURCE_TROOPS, amount: 47, months_initial: 8, subtype: 1,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Men-nefer"
	})
	troops2.set_sender_faction(0)
	troops2.set_completed_action_tag(1032)
	troops2.set_too_late_action_tag(1033)
	troops2.set_defeat_action_tag(1035)
	kr_ok.set_completed_action_tag(1032)
	sea.set_completed_action_tag(1034)
}

function mission18_fire_unique_kr(delta) {
	mission.troops_kr_seq = (mission.troops_kr_seq | 0) + 1
	var type = delta >= 0 ? EVENT_TYPE_REPUTATION_INCREASE : EVENT_TYPE_REPUTATION_DECREASE
	var amount = delta >= 0 ? delta : -delta
	city.create_chain_event({
		tag_id: 4200 + mission.troops_kr_seq,
		type: type,
		amount: amount,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

function mission18_create_troops_rearm_request(tag) {
	var troops2 = city.create_good_request({
		tag_id: tag, resource: RESOURCE_TROOPS, amount: 47, months_initial: 8, subtype: 1,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Men-nefer"
	})
	troops2.set_sender_faction(0)
	troops2.set_completed_action_tag(1032)
	troops2.set_too_late_action_tag(1033)
	troops2.set_defeat_action_tag(1035)
	return troops2
}

function mission18_troops_refuse_raid(tag) {
	mission18_fire_unique_kr(-2)
	mission.troops_rearm_seq = (mission.troops_rearm_seq | 0) + 1
	var rearm_tag = 4100 + mission.troops_rearm_seq
	mission18_create_troops_rearm_request(rearm_tag)
	// High band: avoid colliding with calendar Hyksos (0 / 3+year%20) and favour (24+).
	var invasion_id = 60 + (mission.troops_rearm_seq % 20)
	log_info("akhenaten: mission 18 rostja hyksos×9 after troops refuse/defeat tag=" + tag + " rearm=" + rearm_tag)
	mission18_hyksos_raid(invasion_id, 9, EVENT_ATTACK_TARGET_FOOD, rearm_tag)
}

function mission18_is_troops_rearm_tag(tag) {
	return tag >= 4100 && tag < 4200
}

[es=event_mission_start, mission=mission18]
function mission18_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	__image_request_pak(PACK_PYRAMID)
	mission_show_start_message(mission, "message_mission_giza")
	empire.set_id(18)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	mission18_ensure_shared_kr_leaves()
	mission18_ensure_gems_ladder_leaves()
	mission18_ensure_pharaoh_gift_leaves()
	mission18_ensure_troops_chain_leaves()
}

[es=event_advance_month, mission=mission18]
function mission18_recurring_request_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_GEMS, "gems_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GAMEMEAT, "gamemeat_pharaoh_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GAMEMEAT, "gamemeat_city_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_TIMBER, "timber_recurring", abs)
}

// pak i=0: gems×5/9mo recurring y3m9+ sender=pharaoh; ok→1 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i0_gems_recurring(ev) {
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 9)) {
		return
	}
	if (mission.event0_gems_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GEMS, "gems_recurring", abs)) {
		return
	}
	mission.event0_gems_last_year = ev.years_since_start
	mission18_ensure_shared_kr_leaves()
	log_info("akhenaten: mission 18 rostja gems×5 recurring y" + ev.years_since_start, {ev:ev})
	mission18_fire_request(3000 + 0 * 100 + ev.years_since_start, RESOURCE_GEMS, 5, 9, 1001, 1002, 1003, 0, 1)
}

// pak i=4: SEA_TRADE_PROBLEM once y11m3 amount=32 (junk tags ignored).
[es=event_advance_month, mission=mission18]
function mission18_event_i4_sea_trade(ev) {
	if (mission.event4_sea_done) {
		return
	}
	if (ev.years_since_start < 11 || (ev.years_since_start == 11 && ev.month < 3)) {
		return
	}
	mission.event4_sea_done = true
	log_info("akhenaten: mission 18 rostja sea trade problem y11m3", {ev:ev})
	mission18_fire_simple_event(2004, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 32)
}

// pak i=5: WAGE_DECREASE ×2 once y11m0.
[es=event_advance_month, mission=mission18]
function mission18_event_i5_wage(ev) {
	if (mission.event5_wage_done) {
		return
	}
	if (ev.years_since_start < 11) {
		return
	}
	mission.event5_wage_done = true
	log_info("akhenaten: mission 18 rostja wage −2", {ev:ev})
	mission18_fire_simple_event(2005, EVENT_TYPE_WAGE_DECREASE, undefined, 2)
}

// pak i=6: PRICE_DECREASE stone −15 once y15m0 city=Iunet.
[es=event_advance_month, mission=mission18]
function mission18_event_i6_stone_price(ev) {
	if (mission.event6_price_done) {
		return
	}
	if (ev.years_since_start < 15) {
		return
	}
	mission.event6_price_done = true
	log_info("akhenaten: mission 18 rostja stone price −15", {ev:ev})
	mission18_fire_simple_event(2006, EVENT_TYPE_PRICE_DECREASE, RESOURCE_STONE, 15, "Iunet")
}

// pak i=7: PRICE_INCREASE limestone +7 once y17m0 city=On.
[es=event_advance_month, mission=mission18]
function mission18_event_i7_limestone_price(ev) {
	if (mission.event7_price_done) {
		return
	}
	if (ev.years_since_start < 17) {
		return
	}
	mission.event7_price_done = true
	log_info("akhenaten: mission 18 rostja limestone price +7", {ev:ev})
	mission18_fire_simple_event(2007, EVENT_TYPE_PRICE_INCREASE, RESOURCE_LIMESTONE, 7, "On")
}

// pak i=8: DEMAND_DECREASE timber −7 once y19m0 city=Kyrene.
[es=event_advance_month, mission=mission18]
function mission18_event_i8_timber_demand(ev) {
	if (mission.event8_demand_done) {
		return
	}
	if (ev.years_since_start < 19) {
		return
	}
	mission.event8_demand_done = true
	log_info("akhenaten: mission 18 rostja timber demand −7", {ev:ev})
	mission18_fire_simple_event(2008, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_TIMBER, 7, "Kyrene")
}

// pak i=9: PRICE_INCREASE timber +5 once y20m0.
[es=event_advance_month, mission=mission18]
function mission18_event_i9_timber_price(ev) {
	if (mission.event9_price_done) {
		return
	}
	if (ev.years_since_start < 20) {
		return
	}
	mission.event9_price_done = true
	log_info("akhenaten: mission 18 rostja timber price +5", {ev:ev})
	mission18_fire_simple_event(2009, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 5)
}

// pak i=10: DEMAND_DECREASE limestone −5 once y23m0.
[es=event_advance_month, mission=mission18]
function mission18_event_i10_limestone_demand(ev) {
	if (mission.event10_demand_done) {
		return
	}
	if (ev.years_since_start < 23) {
		return
	}
	mission.event10_demand_done = true
	log_info("akhenaten: mission 18 rostja limestone demand −5", {ev:ev})
	mission18_fire_simple_event(2010, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_LIMESTONE, 5)
}

// pak i=11: PRICE_INCREASE limestone +6 once y24m0 city=Iunet.
[es=event_advance_month, mission=mission18]
function mission18_event_i11_limestone_price(ev) {
	if (mission.event11_price_done) {
		return
	}
	if (ev.years_since_start < 24) {
		return
	}
	mission.event11_price_done = true
	log_info("akhenaten: mission 18 rostja limestone price +6", {ev:ev})
	mission18_fire_simple_event(2011, EVENT_TYPE_PRICE_INCREASE, RESOURCE_LIMESTONE, 6, "Iunet")
}

// pak i=12: gamemeat×12/18mo once y16m10 sender=pharaoh subtype=3; ok→13 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i12_gamemeat(ev) {
	if (mission.event12_gamemeat_done) {
		return
	}
	if (ev.years_since_start < 16 || (ev.years_since_start == 16 && ev.month < 10)) {
		return
	}
	mission.event12_gamemeat_done = true
	mission18_ensure_pharaoh_gift_leaves()
	log_info("akhenaten: mission 18 rostja gamemeat×12", {ev:ev})
	mission18_fire_request(2012, RESOURCE_GAMEMEAT, 12, 18, 1013, 1002, 1003, 3, 1)
}

// pak i=14: gems×16/2mo once y22m9 sender=pharaoh; ok→13 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i14_gems(ev) {
	if (mission.event14_gems_done) {
		return
	}
	if (ev.years_since_start < 22 || (ev.years_since_start == 22 && ev.month < 9)) {
		return
	}
	mission.event14_gems_done = true
	mission18_ensure_pharaoh_gift_leaves()
	log_info("akhenaten: mission 18 rostja gems×16", {ev:ev})
	mission18_fire_request(2014, RESOURCE_GEMS, 16, 2, 1013, 1002, 1003, 0, 1)
}

// pak i=15: GIFT limestone×19 once y35m11 sender=pharaoh.
[es=event_advance_month, mission=mission18]
function mission18_event_i15_limestone_gift(ev) {
	if (mission.event15_gift_done) {
		return
	}
	if (ev.years_since_start < 35 || (ev.years_since_start == 35 && ev.month < 11)) {
		return
	}
	mission.event15_gift_done = true
	log_info("akhenaten: mission 18 rostja limestone gift×19", {ev:ev})
	mission18_fire_simple_event(2015, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LIMESTONE, 19)
}

// pak i=16: gamemeat×15/9mo recurring y44m4+ sender=pharaoh subtype=3; ok→17 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i16_gamemeat_recurring(ev) {
	if (ev.years_since_start < 44 || (ev.years_since_start == 44 && ev.month < 4)) {
		return
	}
	if (mission.event16_gamemeat_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GAMEMEAT, "gamemeat_pharaoh_recurring", abs)) {
		return
	}
	mission.event16_gamemeat_last_year = ev.years_since_start
	mission18_ensure_pharaoh_gift_leaves()
	log_info("akhenaten: mission 18 rostja gamemeat×15 pharaoh rec y" + ev.years_since_start, {ev:ev})
	mission18_fire_request(3000 + 16 * 100 + ev.years_since_start, RESOURCE_GAMEMEAT, 15, 9, 1017, 1002, 1003, 3, 1)
}

// pak i=19: gems×10/6mo once y2m5; ok→20 ladder; refuse→23; late junk.
[es=event_advance_month, mission=mission18]
function mission18_event_i19_gems_ladder(ev) {
	if (mission.event19_gems_done) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 5)) {
		return
	}
	mission.event19_gems_done = true
	mission18_ensure_gems_ladder_leaves()
	log_info("akhenaten: mission 18 rostja gems×10 ladder", {ev:ev})
	mission18_fire_request(2019, RESOURCE_GEMS, 10, 6, 1020, 1023, 0, 0, 0)
}

// pak i=26: Hyksos×6 once y5m7 attack=BEST_BUILDINGS.
[es=event_advance_month, mission=mission18]
function mission18_event_i26_hyksos(ev) {
	if (mission.event26_hyksos_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 7)) {
		return
	}
	mission.event26_hyksos_done = true
	log_info("akhenaten: mission 18 rostja hyksos×6", {ev:ev})
	mission18_hyksos_raid(0, 6, EVENT_ATTACK_TARGET_BEST_BUILDINGS)
}

// pak i=27: gems×13/3mo once y7m0 subtype=6; ok→28 MESSAGE; refuse/late→29 invasion (JS).
[es=event_advance_month, mission=mission18]
function mission18_event_i27_gems_crisis(ev) {
	if (mission.event27_gems_done) {
		return
	}
	if (ev.years_since_start < 7) {
		return
	}
	mission.event27_gems_done = true
	mission18_ensure_pharaoh_gift_leaves()
	log_info("akhenaten: mission 18 rostja gems×13 crisis", {ev:ev})
	mission18_fire_request(2027, RESOURCE_GEMS, 13, 3, 1028, 1029, 1029, 6, 0)
}

// pak i=30: troops×40/12mo once y8m3 subtype=1 city=Men-nefer;
// ok→31; late→33; refuse/defeat→1035 → JS Hyksos×9 → 1034 re-arm.
[es=event_advance_month, mission=mission18]
function mission18_event_i30_troops(ev) {
	if (mission.event30_troops_done) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 3)) {
		return
	}
	mission.event30_troops_done = true
	mission18_ensure_troops_chain_leaves()
	log_info("akhenaten: mission 18 rostja troops×40", {ev:ev})
	// refuse_tag 0: KR from cleared (unique). defeat_tag 1035: defer-to-battle gate only.
	mission18_fire_request(2030, RESOURCE_TROOPS, 40, 12, 1031, 0, 1033, 1, 0, 1035, "Men-nefer")
}

// Factual request close — invasions from JS (no KR-snap).
// Defeat of deferred troop asks also emits event_request_cleared (fulfilled=0) → "refuse".
[es=event_request_cleared, mission=mission18]
function mission18_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	var tag = ev.tag_id

	// pak i=29 Hyksos×11 after gems crisis refuse/late (EVENT_TYPE_INVASION no-op).
	if (tag == 2027 && outcome != "ok" && !mission.gems_crisis_raid_done) {
		mission.gems_crisis_raid_done = true
		log_info("akhenaten: mission 18 rostja hyksos×11 after gems crisis (" + outcome + ")", {ev:ev})
		mission18_hyksos_raid(1, 11, EVENT_ATTACK_TARGET_VAULTS)
		return
	}

	// pak i=35 Hyksos×9 after troops refuse/defeat (not late→SEA).
	// 2030 / SEA-armed 1034 / fresh re-arm tags 4100+.
	if ((tag == 2030 || tag == 1034 || mission18_is_troops_rearm_tag(tag)) && outcome == "refuse") {
		mission18_troops_refuse_raid(tag)
	}
}

// pak i=36: gamemeat×15/8mo recurring y12m8+ sender=city; ok→1 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i36_gamemeat_recurring(ev) {
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 8)) {
		return
	}
	if (mission.event36_gamemeat_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GAMEMEAT, "gamemeat_city_recurring", abs)) {
		return
	}
	mission.event36_gamemeat_last_year = ev.years_since_start
	mission18_ensure_shared_kr_leaves()
	log_info("akhenaten: mission 18 rostja gamemeat×15 city rec y" + ev.years_since_start, {ev:ev})
	mission18_fire_request(3000 + 36 * 100 + ev.years_since_start, RESOURCE_GAMEMEAT, 15, 8, 1001, 1002, 1003, 0, 0)
}

// pak i=37: Hyksos×10 recurring y26m10+ attack=FOOD; ok→3 KR+1.
[es=event_advance_month, mission=mission18]
function mission18_event_i37_hyksos_recurring(ev) {
	if (ev.years_since_start < 26 || ev.month != 10) {
		return
	}
	if (mission.event37_hyksos_last_year == ev.years_since_start) {
		return
	}
	mission.event37_hyksos_last_year = ev.years_since_start
	mission18_ensure_shared_kr_leaves()
	log_info("akhenaten: mission 18 rostja hyksos×10 recurring y" + ev.years_since_start, {ev:ev})
	mission18_hyksos_raid(3 + (ev.years_since_start % 20), 10, EVENT_ATTACK_TARGET_FOOD, 1003)
}

// pak i=38: timber×10/9mo recurring y35m4+ sender=pharaoh; ok→39 refuse→2 late→3.
[es=event_advance_month, mission=mission18]
function mission18_event_i38_timber_recurring(ev) {
	if (ev.years_since_start < 35 || (ev.years_since_start == 35 && ev.month < 4)) {
		return
	}
	if (mission.event38_timber_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber_recurring", abs)) {
		return
	}
	mission.event38_timber_last_year = ev.years_since_start
	mission18_ensure_pharaoh_gift_leaves()
	log_info("akhenaten: mission 18 rostja timber×10 recurring y" + ev.years_since_start, {ev:ev})
	mission18_fire_request(3000 + 38 * 100 + ev.years_since_start, RESOURCE_TIMBER, 10, 9, 1039, 1002, 1003, 0, 1)
}

// pak i=42: NEW_TRADE once y5m4 city=Nekhen → remap Iunet.
[es=event_advance_month, mission=mission18]
function mission18_event_i42_new_trade_route(ev) {
	if (mission.event42_trade_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 4)) {
		return
	}
	mission.event42_trade_done = true
	log_info("akhenaten: mission 18 rostja NEW_TRADE Iunet y5m4", {ev:ev})
	city.create_chain_event({
		tag_id: 2042,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 7,
		subtype: EVENT_SUBTYPE_NEW_TRADE_ROUTE,
		city: "Iunet",
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

[es=event_advance_month, mission=mission18]
function mission18_event_i43_new_trade_route(ev) {
	if (mission.event43_trade_done) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 5)) {
		return
	}
	mission.event43_trade_done = true
	log_info("akhenaten: mission 18 rostja NEW_TRADE Iunet y15m5", {ev:ev})
	city.create_chain_event({
		tag_id: 2043,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 6,
		subtype: EVENT_SUBTYPE_NEW_TRADE_ROUTE,
		city: "Iunet",
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=18→40→41: favour Pharaoh 50→20→50.
[es=event_advance_month, mission=mission18]
function mission18_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, [50, 20, 50])
}
