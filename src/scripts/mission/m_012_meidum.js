log_info("akhenaten: mission 12 meidum started")

// Empire / requests / events aligned with original campaign scenario 12 (2026-07-25 dump).
// Favour Pharaoh army size=25 (by_favour) → chain size=60; proxied in JS until B2
// (mission_pharaoh_favour_invasion_tick, same pattern as Saqqara/Serabit).
// Enemy is ENEMY_5_HYKSOS (pak_enemy_id=5) — NOT Libyan. Recurring raid y7m6 size=17.
// Invasion points: land [114,79] sea [31,7] (pak; previous placeholder values were wrong).
// Triage: SKIP route 47 (type=0, no city, orphan); SKIP map_obj idx=7 (empty stub, pos 0,0).
// SKIP events year>=98 junk (i=65 failed_flood y99; i=66 reeds y98; i=67 wage y101;
// i=68/69 papyrus y120 request + its gift chain).
// SKIP orphan chain_only leaves with no inbound: i=46 (KR+7), i=58 (price− papyrus).
// Shared ONLY_VIA leaves: i=27/28/29/30 (KR±, reused by most requests below).
// Resource chains (ONLY_VIA, wired once from on_start): clay i=5/8/9/10/11 (from pottery
// recurring i=7); timber i=20-25 (from i=19); grain i=42-45 (from i=41); papyrus i=54-57
// (from i=53); gifts i=50/61/64 (from i=49/60/63).
// Monuments goal: small(8)+complex(24) → trunc(2.25*32+4.5)=76.
// Complex weight = large (24) while on-land; rating clamp 100 forbids weight 44 alone.
// Pak original was 39. The causeway is not implemented.
//
// Tag_id scheme used throughout this file (documented once here, not repeated per call):
//   1000 + i               chain-only ONLY_VIA_EVENT leaves (i = pak event index,
//                          e.g. tag 1027 = pak i=27 "KR+8")
//   2000 + i               once (EVENT_TRIGGER_ONCE) calendar roots
//   3000 + i*100 + year    recurring calendar roots (fresh tag per qualifying year, same i)

mission12 { // Meidum
	map_file : "data/maps/m_012_meidum.map"

	// Map points from data/maps/m_012_meidum.map.
	herd_points_predator [ [90, 11], [129, 109] ]

	start_message : "message_mission_meidum"
	selection_title : "Meidum"
	player_rank : 4

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 31]

	// Same post-victory fork as mission 11: both 11 and 12 lead to Buhen/Dahshur.
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

	// pak Normal funds=10000 loan=3000 debt_interest=8 → int_dcy around Normal.
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [6000, 4000, 3000, 2000, 1600]
	debt_interest [4, 6, 8, 10, 12]
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
		briefing : "Voice/Mission/212_mission.mp3"
		victory : "Voice/Mission/212_victory.mp3"
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
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_CHARIOTEERS, BUILDING_FORT_ARCHERS, BUILDING_FORT_INFANTRY,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_WOOD_CUTTERS,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_STEPPED_PYRAMID, BUILDING_STEPPED_PYRAMID_COMPLEX,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals aligned with original campaign scenario 12: pop 1/3000, culture 1/25, prosperity 1/25,
	// monuments 1/39 (pak), kingdom 1/40, housing_level 1/11.
	// Goal = trunc(2.25*(8+24)+4.5) = 76 (complex weight = large until the causeway lands).
	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 76 }
		kingdom       {enabled : true, goal : 40 }
		housing_level {enabled : true, goal : 11 }
	}

	// Map points from original campaign scenario 12 (disembark count=0 — omitted).
	entry_point [111, 141]
	exit_point [32, 54]
	river_entry_point [130, 122]
	river_exit_point [78, 8]
	invasion_points_land [ [114, 79] ]
	invasion_points_sea [ [31, 7] ]

	enable_scenario_events : true

	// Empire from original campaign scenario 12 (empire id=1) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Meidum"
			idx : 5
			pos : [572, 592]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_STONE ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LIMESTONE ]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 4
			is_open : false
			cost_to_open : 1050
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 9
			is_open : false
			cost_to_open : 700
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
			name : "Nekhen"
			idx : 8
			pos : [797, 1011]
			route : 6
			is_open : false
			cost_to_open : 650
			is_sea_trade : true
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
			name : "Saqqara"
			idx : 9
			pos : [523, 539]
			route : 5
			is_open : false
			cost_to_open : 200
			is_sea_trade : false
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
			name : "Serabit Khadim"
			idx : 11
			pos : [801, 552]
			route : 2
			is_open : false
			cost_to_open : 350
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_CLAY ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			// pak: type=pharaoh(2) trade=0 sells=- buys=- cost=0; route=1 land polyline only.
			name : "Men-nefer"
			idx : 6
			pos : [539, 472]
			route : 1
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		// Display-only (pak route=0; no polyline).
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
			name : "Selima Oasis"
			idx : 10
			pos : [614, 1363]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]
	// SKIP map_obj idx=7: empty stub, pos=0,0, no data.

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer land
			type : 1
			points [
				[569, 516], [591, 613]
			]
		}
		{
			route : 2 // Serabit Khadim land
			type : 1
			points [
				[820, 571], [760, 563], [741, 553], [725, 524], [724, 513], [704, 495],
				[686, 506], [684, 542], [694, 563], [711, 570], [597, 614]
			]
		}
		{
			route : 4 // Abu sea
			type : 2
			points [
				[892, 1179], [881, 1157], [886, 1137], [877, 1111], [877, 1095], [879, 1068],
				[863, 1036], [841, 1016], [812, 987], [815, 963], [828, 944], [824, 927],
				[814, 911], [775, 934], [758, 914], [732, 907], [718, 887], [700, 882],
				[673, 852], [654, 842], [643, 826], [631, 821], [612, 814], [597, 797],
				[595, 776], [584, 762], [582, 739], [568, 727], [566, 713], [571, 688],
				[576, 664], [587, 641], [587, 624]
			]
		}
		{
			route : 5 // Saqqara land
			type : 1
			points [
				[543, 562], [566, 576], [564, 589], [591, 617]
			]
		}
		{
			route : 6 // Nekhen sea
			type : 2
			points [
				[816, 1026], [834, 1013], [826, 997], [814, 984], [819, 969], [821, 957],
				[828, 941], [823, 924], [810, 908], [790, 922], [771, 931], [758, 914],
				[758, 915], [744, 918], [732, 908], [722, 898], [717, 887], [702, 875],
				[690, 869], [676, 860], [667, 852], [650, 838], [650, 828], [630, 824],
				[613, 813], [599, 797], [594, 769], [585, 757], [583, 738], [569, 726],
				[568, 710], [571, 667], [583, 644], [587, 617]
			]
		}
		{
			route : 9 // Behdet sea
			type : 2
			points [
				[859, 1088], [876, 1076], [870, 1056], [865, 1048], [861, 1027], [846, 1024],
				[850, 1021], [836, 1013], [812, 987], [819, 969], [817, 962], [829, 943],
				[822, 920], [814, 907], [801, 921], [793, 921], [773, 936], [759, 923],
				[759, 915], [748, 917], [718, 900], [722, 889], [703, 884], [678, 863],
				[674, 853], [663, 849], [654, 842], [654, 833], [639, 822], [627, 822],
				[620, 817], [611, 813], [596, 795], [597, 778], [584, 762], [586, 741],
				[565, 725], [568, 704], [571, 666], [587, 627], [593, 617]
			]
		}
	]
	// SKIP route 47: type=0 n=2 pts=[42,458],[595,626] — no city.route=47 (orphan).

	hide_pak_objects : true
	empire_ornaments [
		// pak: exp_img 6 → bits_120; exp_img 3 → bits_117; exp_img 5 → bits_119.
		{ pos : [514, 491], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [502, 536], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [724, 926], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [841, 1095], image : "pharaoh_general/empire_bits_00119" }
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
		// Chain-leaf wiring (idempotent, all wired once from on_start).
		shared_kr_leaves_wired : false
		clay_chain_leaves_wired : false
		timber_chain_leaves_wired : false
		grain_chain_leaves_wired : false
		papyrus_chain_leaves_wired : false
		gift_leaves_wired : false

		// Once-root done flags (pak event index in the name).
		event0_timber_done : false
		event1_reeds_done : false
		event3_stone_done : false
		event4_papyrus_done : false
		event6_pottery_bare_done : false
		event13_papyrus_done : false
		event14_wage_decrease_done : false
		event16_failed_flood_done : false
		event26_grain_done : false
		event32_pottery_done : false
		event33_stone_done : false
		event35_pottery_done : false
		event36_failed_flood_done : false
		event48_papyrus_done : false
		event49_stone_gift_done : false
		event51_price_increase_clay_done : false
		event52_clay_done : false
		event53_papyrus_done : false
		event62_pottery_done : false

		// Recurring-root last-fired-year gates (pak event index in the name).
		event2_pottery_last_year : -1
		event7_pottery_last_year : -1
		event12_grain_last_year : -1
		event15_price_stone_last_year : -1
		event17_clay_pit_flood_last_year : -1
		event18_wage_increase_last_year : -1
		event19_timber_last_year : -1
		event31_grain_last_year : -1
		event34_clay_pit_flood2_last_year : -1
		event37_price_decrease_clay_last_year : -1
		event38_grain_last_year : -1
		event39_perfect_flood_last_year : -1
		event40_pottery_last_year : -1
		event41_grain_last_year : -1
		event47_sea_trade_problem_last_year : -1
		event59_timber_last_year : -1
		event60_grain_last_year : -1
		event63_stone_last_year : -1
		event70_hyksos_last_year : -1

		// Shared resource-busy gates (pottery/grain/timber recurrings can overlap; see
		// mission_recurring_request_may_fire — Serabit copper pattern).
		pottery_recurring_was_busy : false
		pottery_recurring_idle_since_abs : -1
		grain_recurring_was_busy : false
		grain_recurring_idle_since_abs : -1
		timber_recurring_was_busy : false
		timber_recurring_idle_since_abs : -1

		hyksos_invasion_count : 0

		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0

		start_message_shown : false
	}
}

// Creates a single dormant (ONLY_VIA_EVENT) chain leaf. `resource`/`subtype` are optional.
// Callers chain `.set_completed_action_tag(...)` etc. off the returned object as needed.
function mission12_make_leaf(tag, type, resource, amount, months, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) {
		leaf.set_param("months_initial", months)
	}
	return leaf
}

// Fires a simple (non-request) calendar root — WAGE/PRICE/FLOOD/SEA_TRADE state changes.
function mission12_fire_simple_event(tag, type, resource, amount, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	city.create_chain_event(opts).execute()
}

// Fires a Pharaoh resource request wired to already-created ok/refuse/late chain leaves.
function mission12_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(1) // pak: these are all Pharaoh's requests for his necropolis
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

// Shared ONLY_VIA leaves reused by most calendar requests (pak i=27/28/29/30).
function mission12_ensure_shared_kr_leaves() {
	if (mission.shared_kr_leaves_wired) {
		return
	}
	mission.shared_kr_leaves_wired = true
	mission12_make_leaf(1027, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2) // i27 "ok" leaf
	mission12_make_leaf(1028, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2) // i28 "refuse" leaf
	mission12_make_leaf(1029, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2) // i29 small/late "ok" leaf
	mission12_make_leaf(1030, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 2) // i30 small/late "refuse" leaf
}

// Clay demand chain kicked off by the pottery recurring request (pak i=7).
function mission12_ensure_clay_chain_leaves() {
	if (mission.clay_chain_leaves_wired) {
		return
	}
	mission.clay_chain_leaves_wired = true
	mission12_ensure_shared_kr_leaves()

	mission12_make_leaf(1005, EVENT_TYPE_CONTAMINATED_WATER, undefined, 9, 2) // i5 ← i11.ok
	mission12_make_leaf(1008, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_CLAY, 6, 2) // i8 ← i7.ok, i10.ok
	mission12_make_leaf(1009, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_CLAY, 7, 2).set_completed_action_tag(1010) // i9 → i10

	var clay_request = city.create_good_request({ // i10: chain-only clay×6/6mo
		tag_id: 1010, resource: RESOURCE_CLAY, amount: 6, months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	clay_request.set_completed_action_tag(1008)
	clay_request.set_refusal_action_tag(1011)
	clay_request.set_too_late_action_tag(1030)

	mission12_make_leaf(1011, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_CLAY, 8, 2).set_completed_action_tag(1005) // i11 → i5
}

// Timber demand chain kicked off by the timber recurring request (pak i=19).
function mission12_ensure_timber_chain_leaves() {
	if (mission.timber_chain_leaves_wired) {
		return
	}
	mission.timber_chain_leaves_wired = true
	mission12_ensure_shared_kr_leaves()

	mission12_make_leaf(1020, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 9, 2) // i20 ← i19.ok
	mission12_make_leaf(1021, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_TIMBER, 8, 2).set_completed_action_tag(1022) // i21 → i22

	var timber_request = city.create_good_request({ // i22: chain-only timber×11/2mo
		tag_id: 1022, resource: RESOURCE_TIMBER, amount: 11, months_initial: 2,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	timber_request.set_completed_action_tag(1024)
	timber_request.set_refusal_action_tag(1025)
	timber_request.set_too_late_action_tag(1030)

	mission12_make_leaf(1023, EVENT_TYPE_WAGE_INCREASE, undefined, 10, 2) // i23 ← i25.ok
	mission12_make_leaf(1024, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 8, 2) // i24 ← i22.ok
	mission12_make_leaf(1025, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_TIMBER, 5, 2).set_completed_action_tag(1023) // i25 → i23
}

// Grain demand chain kicked off by the grain recurring request (pak i=41).
function mission12_ensure_grain_chain_leaves() {
	if (mission.grain_chain_leaves_wired) {
		return
	}
	mission.grain_chain_leaves_wired = true

	mission12_make_leaf(1042, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_GRAIN, 7, 2) // i42 ← i41.ok
	mission12_make_leaf(1043, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GRAIN, 5, 2).set_completed_action_tag(1044) // i43 → i44
	mission12_make_leaf(1044, EVENT_TYPE_PRICE_DECREASE, RESOURCE_GRAIN, 8, 2).set_completed_action_tag(1045) // i44 → i45
	mission12_make_leaf(1045, EVENT_TYPE_WAGE_INCREASE, undefined, 6, 2) // i45 ← i44.ok
}

// Papyrus demand chain kicked off by the papyrus request (pak i=53).
function mission12_ensure_papyrus_chain_leaves() {
	if (mission.papyrus_chain_leaves_wired) {
		return
	}
	mission.papyrus_chain_leaves_wired = true

	mission12_make_leaf(1054, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_PAPYRUS, 6, 2).set_completed_action_tag(1055) // i54 → i55
	mission12_make_leaf(1055, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_PAPYRUS, 8, 2) // i55 ← i54.ok, i57.ok
	mission12_make_leaf(1056, EVENT_TYPE_PRICE_DECREASE, RESOURCE_PAPYRUS, 22, 2).set_completed_action_tag(1057) // i56 → i57

	var papyrus_request = city.create_good_request({ // i57: chain-only papyrus×23/12mo
		tag_id: 1057, resource: RESOURCE_PAPYRUS, amount: 23, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	papyrus_request.set_completed_action_tag(1055)
}

// Pharaoh gift leaves (pak i=50/61/64), each the "ok" tail of one request root.
function mission12_ensure_gift_leaves() {
	if (mission.gift_leaves_wired) {
		return
	}
	mission.gift_leaves_wired = true

	mission12_make_leaf(1050, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LUXURY_GOODS, 25, 2) // i50 ← i49.ok
	mission12_make_leaf(1061, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LUXURY_GOODS, 28, 2) // i61 ← i60.ok
	mission12_make_leaf(1064, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_OIL, 21, 2) // i64 ← i63.ok
}

function mission12_hyksos_raid(invasion_id, size) {
	// pak enemy_id=5 ENEMY_5_HYKSOS; tilex/tiley -1 → engine picks from invasion_points_land.
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size
	})
}

[es=event_mission_start, mission=mission12]
function mission12_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_STEPPED_PYRAMID)
	mission_show_start_message(mission, "message_mission_meidum")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	// Wire all dormant ONLY_VIA_EVENT chain leaves up front — harmless, they stay inert
	// until a root's ok/refuse/late action tag references them.
	mission12_ensure_shared_kr_leaves()
	mission12_ensure_clay_chain_leaves()
	mission12_ensure_timber_chain_leaves()
	mission12_ensure_grain_chain_leaves()
	mission12_ensure_papyrus_chain_leaves()
	mission12_ensure_gift_leaves()
}

// Tracks resource-busy state every month so the pottery/grain/timber recurring roots below
// never stack a fresh request while one for the same resource is still active (Serabit copper
// pattern via mission_recurring_request_may_fire).
[es=event_advance_month, mission=mission12]
function mission12_recurring_request_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_POTTERY, "pottery_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GRAIN, "grain_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_TIMBER, "timber_recurring", abs)
}

// pak i=0: year=3 month=4 timber×10/6mo once; ok→KR+8 refuse→KR−2(!) late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i0_timber_request(ev) {
	if (mission.event0_timber_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 4)) {
		return
	}
	mission.event0_timber_done = true
	log_info("akhenaten: mission 12 meidum i0 timber request y3m4", {ev:ev})
	mission12_fire_request(2000, RESOURCE_TIMBER, 10, 6, 1027, 1030, 1029) // pak refuse routes to i30, not i28
}

// pak i=1: year=5 month=7 reeds×8/4mo once; ok→KR+8 refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i1_reeds_request(ev) {
	if (mission.event1_reeds_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 7)) {
		return
	}
	mission.event1_reeds_done = true
	log_info("akhenaten: mission 12 meidum i1 reeds request y5m7", {ev:ev})
	mission12_fire_request(2001, RESOURCE_REEDS, 8, 4, 1027, 1028, 1029)
}

// pak i=2: year=11+ month=9 pottery×4/5mo recurring; ok→KR+8 refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i2_pottery_recurring(ev) {
	if (ev.years_since_start < 11 || ev.month != 9) {
		return
	}
	if (mission.event2_pottery_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_POTTERY, "pottery_recurring", abs)) {
		return
	}
	mission.event2_pottery_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i2 pottery recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 2 * 100 + ev.years_since_start, RESOURCE_POTTERY, 4, 5, 1027, 1028, 1029)
}

// pak i=3: year=13 month=3 stone×10/6mo once; ok→KR+8 refuse→KR−5 late→KR+2 (defeat=666 ignored).
[es=event_advance_month, mission=mission12]
function mission12_event_i3_stone_request(ev) {
	if (mission.event3_stone_done) {
		return
	}
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 3)) {
		return
	}
	mission.event3_stone_done = true
	log_info("akhenaten: mission 12 meidum i3 stone request y13m3", {ev:ev})
	mission12_fire_request(2003, RESOURCE_STONE, 10, 6, 1027, 1028, 1029)
}

// pak i=4: year=12 month=11 papyrus×13/12mo once; ok→KR+8 refuse→KR−5 late→KR−2 (defeat=666 ignored).
[es=event_advance_month, mission=mission12]
function mission12_event_i4_papyrus_request(ev) {
	if (mission.event4_papyrus_done) {
		return
	}
	if (ev.years_since_start < 12 || (ev.years_since_start == 12 && ev.month < 11)) {
		return
	}
	mission.event4_papyrus_done = true
	log_info("akhenaten: mission 12 meidum i4 papyrus request y12m11", {ev:ev})
	mission12_fire_request(2004, RESOURCE_PAPYRUS, 13, 12, 1027, 1028, 1030)
}

// pak i=6: year=13 month=8 pottery×10/6mo once — bare request, no ok/refuse/late chain.
[es=event_advance_month, mission=mission12]
function mission12_event_i6_pottery_bare(ev) {
	if (mission.event6_pottery_bare_done) {
		return
	}
	if (ev.years_since_start < 13 || (ev.years_since_start == 13 && ev.month < 8)) {
		return
	}
	mission.event6_pottery_bare_done = true
	log_info("akhenaten: mission 12 meidum i6 pottery bare request y13m8 (no chain)", {ev:ev})
	mission12_fire_request(2006, RESOURCE_POTTERY, 10, 6)
}

// pak i=7: year=8+ month=1 pottery×7/2mo recurring — kicks off the clay demand chain
// (ok/refuse/late → i8/i9/i9).
[es=event_advance_month, mission=mission12]
function mission12_event_i7_pottery_recurring_clay_chain(ev) {
	if (ev.years_since_start < 8 || ev.month != 1) {
		return
	}
	if (mission.event7_pottery_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_POTTERY, "pottery_recurring", abs)) {
		return
	}
	mission.event7_pottery_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i7 pottery recurring y" + ev.years_since_start + " (clay chain)", {ev:ev})
	mission12_fire_request(3000 + 7 * 100 + ev.years_since_start, RESOURCE_POTTERY, 7, 2, 1008, 1009, 1009)
}

// pak i=12: year=13+ month=5 grain×10/4mo recurring; ok→KR+8 refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i12_grain_recurring(ev) {
	if (ev.years_since_start < 13 || ev.month != 5) {
		return
	}
	if (mission.event12_grain_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		return
	}
	mission.event12_grain_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i12 grain recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 12 * 100 + ev.years_since_start, RESOURCE_GRAIN, 10, 4, 1027, 1028, 1029)
}

// pak i=13: year=15 month=10 papyrus×13/4mo once; ok→KR+8 refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i13_papyrus_request(ev) {
	if (mission.event13_papyrus_done) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 10)) {
		return
	}
	mission.event13_papyrus_done = true
	log_info("akhenaten: mission 12 meidum i13 papyrus request y15m10", {ev:ev})
	mission12_fire_request(2013, RESOURCE_PAPYRUS, 13, 4, 1027, 1028, 1029)
}

// pak i=14: year=5 month=3 WAGE_DECREASE amount=5 once.
[es=event_advance_month, mission=mission12]
function mission12_event_i14_wage_decrease(ev) {
	if (mission.event14_wage_decrease_done) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 3)) {
		return
	}
	mission.event14_wage_decrease_done = true
	log_info("akhenaten: mission 12 meidum i14 wage decrease y5m3", {ev:ev})
	mission12_fire_simple_event(2014, EVENT_TYPE_WAGE_DECREASE, undefined, 5)
}

// pak i=15: year=14+ month=4 PRICE_INCREASE stone amount=9/2mo recurring, subtype=2.
[es=event_advance_month, mission=mission12]
function mission12_event_i15_price_increase_stone_recurring(ev) {
	if (ev.years_since_start < 14 || ev.month != 4) {
		return
	}
	if (mission.event15_price_stone_last_year == ev.years_since_start) {
		return
	}
	mission.event15_price_stone_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i15 price increase stone y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 15 * 100 + ev.years_since_start, EVENT_TYPE_PRICE_INCREASE, RESOURCE_STONE, 9, 2)
}

// pak i=16: year=16 month=9 FAILED_FLOOD amount=8/2mo once, subtype=4.
[es=event_advance_month, mission=mission12]
function mission12_event_i16_failed_flood(ev) {
	if (mission.event16_failed_flood_done) {
		return
	}
	if (ev.years_since_start < 16 || (ev.years_since_start == 16 && ev.month < 9)) {
		return
	}
	mission.event16_failed_flood_done = true
	log_info("akhenaten: mission 12 meidum i16 failed flood y16m9", {ev:ev})
	mission12_fire_simple_event(2016, EVENT_TYPE_FAILED_FLOOD, undefined, 8, 4)
}

// pak i=17: year=18+ month=4 CLAY_PIT_FLOOD amount=9/2mo recurring (needs a working clay pit).
[es=event_advance_month, mission=mission12]
function mission12_event_i17_clay_pit_flood_recurring(ev) {
	if (ev.years_since_start < 18 || ev.month != 4) {
		return
	}
	if (mission.event17_clay_pit_flood_last_year == ev.years_since_start) {
		return
	}
	mission.event17_clay_pit_flood_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i17 clay pit flood y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 17 * 100 + ev.years_since_start, EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 9)
}

// pak i=18: year=15+ month=7 WAGE_INCREASE amount=6/2mo recurring.
[es=event_advance_month, mission=mission12]
function mission12_event_i18_wage_increase_recurring(ev) {
	if (ev.years_since_start < 15 || ev.month != 7) {
		return
	}
	if (mission.event18_wage_increase_last_year == ev.years_since_start) {
		return
	}
	mission.event18_wage_increase_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i18 wage increase y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 18 * 100 + ev.years_since_start, EVENT_TYPE_WAGE_INCREASE, undefined, 6)
}

// pak i=19: year=16+ month=7 timber×10/5mo recurring — kicks off the timber demand chain
// (ok/refuse → i20/i21; late → shared KR−2).
[es=event_advance_month, mission=mission12]
function mission12_event_i19_timber_recurring(ev) {
	if (ev.years_since_start < 16 || ev.month != 7) {
		return
	}
	if (mission.event19_timber_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber_recurring", abs)) {
		return
	}
	mission.event19_timber_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i19 timber recurring y" + ev.years_since_start + " (timber chain)", {ev:ev})
	mission12_fire_request(3000 + 19 * 100 + ev.years_since_start, RESOURCE_TIMBER, 10, 5, 1020, 1021, 1030)
}

// pak i=26: year=18 month=3 grain×22/2mo once, subtype=3; ok→KR+8 refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i26_grain_request(ev) {
	if (mission.event26_grain_done) {
		return
	}
	if (ev.years_since_start < 18 || (ev.years_since_start == 18 && ev.month < 3)) {
		return
	}
	mission.event26_grain_done = true
	log_info("akhenaten: mission 12 meidum i26 grain request y18m3", {ev:ev})
	mission12_fire_request(2026, RESOURCE_GRAIN, 22, 2, 1027, 1028, 1029, 3)
}

// pak i=31: year=23+ month=4 grain×12/6mo recurring; ok→KR+2 refuse→KR−2 late→KR−2 (small KR leaves).
[es=event_advance_month, mission=mission12]
function mission12_event_i31_grain_recurring(ev) {
	if (ev.years_since_start < 23 || ev.month != 4) {
		return
	}
	if (mission.event31_grain_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		return
	}
	mission.event31_grain_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i31 grain recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 31 * 100 + ev.years_since_start, RESOURCE_GRAIN, 12, 6, 1029, 1030, 1030)
}

// pak i=32: year=23 month=4 pottery×11/5mo once; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i32_pottery_request(ev) {
	if (mission.event32_pottery_done) {
		return
	}
	if (ev.years_since_start < 23 || (ev.years_since_start == 23 && ev.month < 4)) {
		return
	}
	mission.event32_pottery_done = true
	log_info("akhenaten: mission 12 meidum i32 pottery request y23m4", {ev:ev})
	mission12_fire_request(2032, RESOURCE_POTTERY, 11, 5, 1027, 1028, 1030)
}

// pak i=33: year=29 month=8 stone×29/12mo once; ok→KR+8 refuse→KR−5 late→KR−2 (defeat=665 ignored).
[es=event_advance_month, mission=mission12]
function mission12_event_i33_stone_request(ev) {
	if (mission.event33_stone_done) {
		return
	}
	if (ev.years_since_start < 29 || (ev.years_since_start == 29 && ev.month < 8)) {
		return
	}
	mission.event33_stone_done = true
	log_info("akhenaten: mission 12 meidum i33 stone request y29m8", {ev:ev})
	mission12_fire_request(2033, RESOURCE_STONE, 29, 12, 1027, 1028, 1030)
}

// pak i=34: year=33+ month=0 CLAY_PIT_FLOOD amount=5/2mo recurring, subtype=2.
[es=event_advance_month, mission=mission12]
function mission12_event_i34_clay_pit_flood2_recurring(ev) {
	if (ev.years_since_start < 33 || ev.month != 0) {
		return
	}
	if (mission.event34_clay_pit_flood2_last_year == ev.years_since_start) {
		return
	}
	mission.event34_clay_pit_flood2_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i34 clay pit flood y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 34 * 100 + ev.years_since_start, EVENT_TYPE_CLAY_PIT_FLOOD, undefined, 5, 2)
}

// pak i=35: year=39 month=5 pottery×10/8mo once; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i35_pottery_request(ev) {
	if (mission.event35_pottery_done) {
		return
	}
	if (ev.years_since_start < 39 || (ev.years_since_start == 39 && ev.month < 5)) {
		return
	}
	mission.event35_pottery_done = true
	log_info("akhenaten: mission 12 meidum i35 pottery request y39m5", {ev:ev})
	mission12_fire_request(2035, RESOURCE_POTTERY, 10, 8, 1027, 1028, 1030)
}

// pak i=36: year=33 month=8 FAILED_FLOOD amount=9/2mo once.
[es=event_advance_month, mission=mission12]
function mission12_event_i36_failed_flood(ev) {
	if (mission.event36_failed_flood_done) {
		return
	}
	if (ev.years_since_start < 33 || (ev.years_since_start == 33 && ev.month < 8)) {
		return
	}
	mission.event36_failed_flood_done = true
	log_info("akhenaten: mission 12 meidum i36 failed flood y33m8", {ev:ev})
	mission12_fire_simple_event(2036, EVENT_TYPE_FAILED_FLOOD, undefined, 9)
}

// pak i=37: year=41+ month=0 PRICE_DECREASE clay amount=15/2mo recurring.
[es=event_advance_month, mission=mission12]
function mission12_event_i37_price_decrease_clay_recurring(ev) {
	if (ev.years_since_start < 41 || ev.month != 0) {
		return
	}
	if (mission.event37_price_decrease_clay_last_year == ev.years_since_start) {
		return
	}
	mission.event37_price_decrease_clay_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i37 price decrease clay y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 37 * 100 + ev.years_since_start, EVENT_TYPE_PRICE_DECREASE, RESOURCE_CLAY, 15)
}

// pak i=38: year=44+ month=3 grain×12/8mo recurring, subtype=3; ok→KR+2 refuse→KR−2 (no late).
[es=event_advance_month, mission=mission12]
function mission12_event_i38_grain_recurring(ev) {
	if (ev.years_since_start < 44 || ev.month != 3) {
		return
	}
	if (mission.event38_grain_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		return
	}
	mission.event38_grain_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i38 grain recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 38 * 100 + ev.years_since_start, RESOURCE_GRAIN, 12, 8, 1029, 1030, undefined, 3)
}

// pak i=39: year=48+ month=8 PERFECT_FLOOD amount=5/2mo recurring.
[es=event_advance_month, mission=mission12]
function mission12_event_i39_perfect_flood_recurring(ev) {
	if (ev.years_since_start < 48 || ev.month != 8) {
		return
	}
	if (mission.event39_perfect_flood_last_year == ev.years_since_start) {
		return
	}
	mission.event39_perfect_flood_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i39 perfect flood y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 39 * 100 + ev.years_since_start, EVENT_TYPE_PERFECT_FLOOD, undefined, 5)
}

// pak i=40: year=52+ month=4 pottery×10/8mo recurring; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i40_pottery_recurring(ev) {
	if (ev.years_since_start < 52 || ev.month != 4) {
		return
	}
	if (mission.event40_pottery_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_POTTERY, "pottery_recurring", abs)) {
		return
	}
	mission.event40_pottery_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i40 pottery recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 40 * 100 + ev.years_since_start, RESOURCE_POTTERY, 10, 8, 1027, 1028, 1030)
}

// pak i=41: year=56+ month=11 grain×15/6mo recurring — kicks off the grain demand chain
// (ok/refuse → i42/i43; no late).
[es=event_advance_month, mission=mission12]
function mission12_event_i41_grain_recurring(ev) {
	if (ev.years_since_start < 56 || ev.month != 11) {
		return
	}
	if (mission.event41_grain_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		return
	}
	mission.event41_grain_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i41 grain recurring y" + ev.years_since_start + " (grain chain)", {ev:ev})
	mission12_fire_request(3000 + 41 * 100 + ev.years_since_start, RESOURCE_GRAIN, 15, 6, 1042, 1043)
}

// pak i=47: year=61+ month=5 SEA_TRADE_PROBLEM amount=5/2mo recurring, subtype=3.
[es=event_advance_month, mission=mission12]
function mission12_event_i47_sea_trade_problem_recurring(ev) {
	if (ev.years_since_start < 61 || ev.month != 5) {
		return
	}
	if (mission.event47_sea_trade_problem_last_year == ev.years_since_start) {
		return
	}
	mission.event47_sea_trade_problem_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i47 sea trade problem y" + ev.years_since_start, {ev:ev})
	mission12_fire_simple_event(3000 + 47 * 100 + ev.years_since_start, EVENT_TYPE_SEA_TRADE_PROBLEM, undefined, 5, 3)
}

// pak i=48: year=63 month=2 papyrus×29/12mo once; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i48_papyrus_request(ev) {
	if (mission.event48_papyrus_done) {
		return
	}
	if (ev.years_since_start < 63 || (ev.years_since_start == 63 && ev.month < 2)) {
		return
	}
	mission.event48_papyrus_done = true
	log_info("akhenaten: mission 12 meidum i48 papyrus request y63m2", {ev:ev})
	mission12_fire_request(2048, RESOURCE_PAPYRUS, 29, 12, 1027, 1028, 1030)
}

// pak i=49: year=69 month=7 stone×10/2mo once, subtype=4; ok→gift luxury×25 (i50)
// refuse→KR−5 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i49_stone_gift_request(ev) {
	if (mission.event49_stone_gift_done) {
		return
	}
	if (ev.years_since_start < 69 || (ev.years_since_start == 69 && ev.month < 7)) {
		return
	}
	mission.event49_stone_gift_done = true
	log_info("akhenaten: mission 12 meidum i49 stone request y69m7 (gift chain)", {ev:ev})
	mission12_fire_request(2049, RESOURCE_STONE, 10, 2, 1050, 1028, 1029, 4)
}

// pak i=51: year=72 month=8 PRICE_INCREASE clay amount=31/2mo once, subtype=4.
[es=event_advance_month, mission=mission12]
function mission12_event_i51_price_increase_clay(ev) {
	if (mission.event51_price_increase_clay_done) {
		return
	}
	if (ev.years_since_start < 72 || (ev.years_since_start == 72 && ev.month < 8)) {
		return
	}
	mission.event51_price_increase_clay_done = true
	log_info("akhenaten: mission 12 meidum i51 price increase clay y72m8", {ev:ev})
	mission12_fire_simple_event(2051, EVENT_TYPE_PRICE_INCREASE, RESOURCE_CLAY, 31, 4)
}

// pak i=52: year=74 month=7 clay×30/10mo once; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i52_clay_request(ev) {
	if (mission.event52_clay_done) {
		return
	}
	if (ev.years_since_start < 74 || (ev.years_since_start == 74 && ev.month < 7)) {
		return
	}
	mission.event52_clay_done = true
	log_info("akhenaten: mission 12 meidum i52 clay request y74m7", {ev:ev})
	mission12_fire_request(2052, RESOURCE_CLAY, 30, 10, 1027, 1028, 1030)
}

// pak i=53: year=78 month=2 papyrus×35/10mo once — kicks off the papyrus demand chain
// (ok/refuse → i54/i56; no late).
[es=event_advance_month, mission=mission12]
function mission12_event_i53_papyrus_request(ev) {
	if (mission.event53_papyrus_done) {
		return
	}
	if (ev.years_since_start < 78 || (ev.years_since_start == 78 && ev.month < 2)) {
		return
	}
	mission.event53_papyrus_done = true
	log_info("akhenaten: mission 12 meidum i53 papyrus request y78m2 (papyrus chain)", {ev:ev})
	mission12_fire_request(2053, RESOURCE_PAPYRUS, 35, 10, 1054, 1056)
}

// pak i=59: year=82+ month=1 timber×29/2mo recurring; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i59_timber_recurring(ev) {
	if (ev.years_since_start < 82 || ev.month != 1) {
		return
	}
	if (mission.event59_timber_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_TIMBER, "timber_recurring", abs)) {
		return
	}
	mission.event59_timber_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i59 timber recurring y" + ev.years_since_start, {ev:ev})
	mission12_fire_request(3000 + 59 * 100 + ev.years_since_start, RESOURCE_TIMBER, 29, 2, 1027, 1028, 1030)
}

// pak i=60: year=85+ month=9 grain×33/2mo recurring, subtype=3; ok→gift luxury×28 (i61)
// refuse→KR−2 late→KR+2.
[es=event_advance_month, mission=mission12]
function mission12_event_i60_grain_gift_recurring(ev) {
	if (ev.years_since_start < 85 || ev.month != 9) {
		return
	}
	if (mission.event60_grain_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs)) {
		return
	}
	mission.event60_grain_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i60 grain recurring y" + ev.years_since_start + " (gift chain)", {ev:ev})
	mission12_fire_request(3000 + 60 * 100 + ev.years_since_start, RESOURCE_GRAIN, 33, 2, 1061, 1030, 1029, 3)
}

// pak i=62: year=90 month=8 pottery×16/10mo once; ok→KR+8 refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i62_pottery_request(ev) {
	if (mission.event62_pottery_done) {
		return
	}
	if (ev.years_since_start < 90 || (ev.years_since_start == 90 && ev.month < 8)) {
		return
	}
	mission.event62_pottery_done = true
	log_info("akhenaten: mission 12 meidum i62 pottery request y90m8", {ev:ev})
	mission12_fire_request(2062, RESOURCE_POTTERY, 16, 10, 1027, 1028, 1030)
}

// pak i=63: year=95+ month=7 stone×12/12mo recurring, subtype=4; ok→gift oil×21 (i64)
// refuse→KR−5 late→KR−2.
[es=event_advance_month, mission=mission12]
function mission12_event_i63_stone_gift_recurring(ev) {
	if (ev.years_since_start < 95 || ev.month != 7) {
		return
	}
	if (mission.event63_stone_last_year == ev.years_since_start) {
		return
	}
	mission.event63_stone_last_year = ev.years_since_start
	log_info("akhenaten: mission 12 meidum i63 stone recurring y" + ev.years_since_start + " (gift chain)", {ev:ev})
	mission12_fire_request(3000 + 63 * 100 + ev.years_since_start, RESOURCE_STONE, 12, 12, 1064, 1028, 1030, 4)
}

// pak i=70: year=7+ month=6 Hyksos invasion size=17, recurring ~every 12 months.
[es=event_advance_month, mission=mission12]
function mission12_event_i70_hyksos_invasion_recurring(ev) {
	if (ev.years_since_start < 7 || ev.month != 6) {
		return
	}
	if (mission.event70_hyksos_last_year == ev.years_since_start) {
		return
	}
	if (city.num_enemy_formations > 0) {
		return
	}
	mission.event70_hyksos_last_year = ev.years_since_start
	mission.hyksos_invasion_count = mission.hyksos_invasion_count + 1
	log_info("akhenaten: mission 12 meidum i70 hyksos invasion size=17 y" + ev.years_since_start, {ev:ev})
	mission12_hyksos_raid(mission.hyksos_invasion_count, 17)
}

// pak i=71/72: by_favour Pharaoh army size=25 → ok chains to a size=60 second wave.
[es=event_advance_month, mission=mission12]
function mission12_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 25, 60)
}
