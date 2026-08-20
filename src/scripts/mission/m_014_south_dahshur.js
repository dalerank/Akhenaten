log_info("akhenaten: mission 14 south dahshur started")

// Empire / requests / events aligned with original campaign scenario 14 (2026-07-26 dump).
// Favour Pharaoh army size=49 (by_favour) → chain size=21; proxied via
// mission_pharaoh_favour_invasion_tick until B2-migrate. No timed enemy raids in pak.
// Scenario enemy is ENEMY_5_HYKSOS (pak_enemy_id=5) — used if invasions spawn; favour
// waves still use ENEMY_3_EGYPTIAN via the shared helper.
// Empire id=13 (same pak empire as Buhen fork partner).
// Triage: SKIP clay floods i=0/1/12/13 (all year=24 editor junk); SKIP map_obj idx=10
// (empty stub). Route 5 (Men-nefer display) has no pak polyline → 2-pt stub + deviation.
// Oil ladder i=2→…→i=8 is chain-only after the y1m6 root (amounts 500→8000).
// Monuments goal 21 matches pak; medium bent pyramid weight 8 → rating 22 (≥21).
//
// Tag_id scheme:
//   1000 + i               chain-only ONLY_VIA_EVENT leaves / chain requests
//   2000 + i               once (EVENT_TRIGGER_ONCE) calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission14 { // South Dahshur — Snofru's Bent Pyramid
	map_file : "data/maps/m_014_south_dahshur.map"
	start_message : "message_mission_south_dahshur"
	selection_title : "South Dahshur"
	player_rank : 5

	// Choice-pair partner of Buhen (13); both converge on North Dahshur (15).
	// NOTE: mission 15 is not scripted yet; until it exists the campaign ends after
	// this mission (mission_end_compute_next returns -1 for an invalid next id).
	next_mission : 15

	// pak Normal funds=10000 loan=3500 debt_interest=20 → int_dcy row (verified).
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [7000, 4700, 3500, 2300, 1900]
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
		briefing : "Voice/Mission/214_mission.mp3"
		victory : "Voice/Mission/214_victory.mp3"
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
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_SMALL_BENT_PYRAMID, BUILDING_MEDIUM_BENT_PYRAMID,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
		BUILDING_LIBRARY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals aligned with original campaign scenario 14: pop 1/3500, culture 0/15 (disabled),
	// prosperity 1/25, monuments 1/21, kingdom 1/50, housing_level 1/19 (count goal 0 ignored).
	// Medium bent pyramid (weight 8) → 2.25*8+4.5 = 22 under additive formula — meets 21.
	win_criteria {
		population    {enabled : true, goal : 3500 }
		culture       {enabled : false }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 21 }
		kingdom       {enabled : true, goal : 50 }
		housing_level {enabled : true, goal : 19 }
	}

	// Map points from original campaign scenario 14.
	entry_point [41, 28]
	exit_point [116, 93]
	river_entry_point [123, 84]
	river_exit_point [126, 80]
	disembark_points [ [81, 34] ]
	invasion_points_land [ [43, 54] ]
	invasion_points_sea [ [28, 17] ]

	enable_scenario_events : true

	// Empire from original campaign scenario 14 (empire id=13) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Dahshur"
			idx : 4
			pos : [568, 521]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_BARLEY, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_GEMS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
		}

		{
			name : "Selima Oasis"
			idx : 13
			pos : [611, 1358]
			route : 1
			is_open : false
			cost_to_open : 900
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
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Abu"
			idx : 0
			pos : [869, 1150]
			route : 2
			is_open : false
			cost_to_open : 650
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Meidum"
			idx : 8
			pos : [572, 592]
			route : 3
			is_open : false
			cost_to_open : 300
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_STONE ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_STONE, limit: 4000 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
			]
		}

		{
			name : "Serabit Khadim"
			idx : 14
			pos : [801, 552]
			route : 4
			is_open : false
			cost_to_open : 800
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		// Display-only (pak trade=0). Men-nefer has route=5 but no polyline in pak.
		{
			name : "Men-nefer"
			idx : 9
			pos : [524, 469]
			route : 5
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
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
			name : "Enkomi"
			idx : 5
			pos : [679, 49]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
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
	// SKIP map_obj idx=10: empty stub, pos=0,0.

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Selima Oasis land
			type : 1
			points [
				[579, 566], [551, 596], [510, 624], [422, 670], [410, 687], [401, 705],
				[393, 753], [387, 912], [406, 1062], [467, 1212], [623, 1377]
			]
		}
		{
			route : 2 // Abu sea
			type : 2
			points [
				[884, 1160], [888, 1138], [878, 1114], [882, 1099], [877, 1091], [876, 1063],
				[865, 1050], [864, 1035], [853, 1025], [843, 1018], [834, 1013], [826, 1001],
				[816, 991], [815, 983], [819, 970], [817, 962], [828, 942], [824, 924],
				[812, 908], [800, 919], [785, 930], [772, 935], [758, 924], [757, 913],
				[746, 916], [723, 900], [719, 888], [701, 884], [677, 859], [671, 851],
				[652, 838], [651, 830], [641, 821], [631, 821], [627, 817], [613, 812],
				[596, 795], [596, 777], [584, 759], [585, 749], [582, 736], [570, 730],
				[565, 720], [571, 709], [570, 677], [571, 667], [583, 644], [584, 632],
				[593, 589], [591, 555]
			]
		}
		{
			route : 3 // Meidum sea
			type : 2
			points [
				[596, 597], [597, 581], [596, 560]
			]
		}
		{
			route : 4 // Serabit Khadim land
			type : 1
			points [
				[805, 566], [773, 560], [759, 558], [746, 550], [739, 541], [721, 503],
				[704, 490], [689, 490], [658, 511], [647, 524], [631, 533], [611, 545]
			]
		}
		// Display route 5 (Men-nefer): pak polyline missing; two-point stub + deviation.
		{
			route : 5 // Men-nefer
			type : 1
			deviation : 60
			points [ [568, 521], [524, 469] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// Positions from pak; sprite names match nearby Meidum/Buhen ornament mapping.
		{ pos : [497, 486], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [500, 538], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [562, 577], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [715, 919], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [837, 1089], image : "pharaoh_general/empire_bits_00119" }
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
		oil_ladder_leaves_wired : false
		limestone_gift_leaves_wired : false
		grain_kr_leaves_wired : false

		event2_oil_done : false
		event10_limestone_done : false

		event9_grain_last_year : -1
		event11_wage_decrease_last_year : -1
		grain_recurring_was_busy : false
		grain_recurring_idle_since_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0

		start_message_shown : false
	}
}

function mission14_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission14_fire_simple_event(tag, type, resource, amount, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	city.create_chain_event(opts).execute()
}

function mission14_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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

// Shared grain KR leaves (pak i=17/18/19) for the recurring grain request.
function mission14_ensure_grain_kr_leaves() {
	if (mission.grain_kr_leaves_wired) {
		return
	}
	mission.grain_kr_leaves_wired = true
	mission14_make_leaf(1017, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2) // i17
	mission14_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 8, 2) // i18
	mission14_make_leaf(1019, EVENT_TYPE_REPUTATION_DECREASE, undefined, 4, 2) // i19
}

// Limestone once (i=10): ok→KR+8→stone gift×64; refuse→KR−15→stone demand−8; late→KR−5→stone gift×32.
function mission14_ensure_limestone_gift_leaves() {
	if (mission.limestone_gift_leaves_wired) {
		return
	}
	mission.limestone_gift_leaves_wired = true

	var kr_ok = mission14_make_leaf(1014, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2) // i14 → 34
	var kr_refuse = mission14_make_leaf(1015, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2) // i15 → 35
	var kr_late = mission14_make_leaf(1016, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2) // i16 → 36
	mission14_make_leaf(1034, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_STONE, 64, 2) // i34
	mission14_make_leaf(1035, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_STONE, 8, 2) // i35
	mission14_make_leaf(1036, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_STONE, 32, 2) // i36

	kr_ok.set_completed_action_tag(1034)
	kr_refuse.set_completed_action_tag(1035)
	kr_late.set_completed_action_tag(1036)
}

// Oil ladder + refuse/late cascade (pak i=2…8, 20…33).
// Success KR steps chain the next oil ask; every refuse KR and the final late land on
// CITY_UNDER_SIEGE Dahshur → CITY_FELL Byblos → copper/gems price+demand cascade.
function mission14_ensure_oil_ladder_leaves() {
	if (mission.oil_ladder_leaves_wired) {
		return
	}
	mission.oil_ladder_leaves_wired = true

	var kr20 = mission14_make_leaf(1020, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2) // i20 → i3
	var kr21 = mission14_make_leaf(1021, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 2) // i21 → i4
	var kr22 = mission14_make_leaf(1022, EVENT_TYPE_REPUTATION_INCREASE, undefined, 12, 2) // i22 → i5
	var kr23 = mission14_make_leaf(1023, EVENT_TYPE_REPUTATION_INCREASE, undefined, 16, 2) // i23 → i28
	var kr24 = mission14_make_leaf(1024, EVENT_TYPE_REPUTATION_DECREASE, undefined, 20, 2) // i24 → i28
	var kr25 = mission14_make_leaf(1025, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2) // i25 → i28
	var kr26 = mission14_make_leaf(1026, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2) // i26 → i28
	var kr27 = mission14_make_leaf(1027, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2) // i27 → i28

	var siege = mission14_make_leaf(1028, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_CITY_UNDER_SIEGE, "Dahshur") // i28 → i29
	var fell = mission14_make_leaf(1029, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Byblos") // i29 → i30
	var price_copper = mission14_make_leaf(1030, EVENT_TYPE_PRICE_INCREASE, RESOURCE_COPPER, 100, 2) // i30 → i31
	var price_gems = mission14_make_leaf(1031, EVENT_TYPE_PRICE_INCREASE, RESOURCE_GEMS, 87, 2) // i31 → i32
	var demand_copper = mission14_make_leaf(1032, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_COPPER, 5, 2) // i32 → i33
	mission14_make_leaf(1033, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GEMS, 7, 2) // i33

	siege.set_completed_action_tag(1029)
	fell.set_completed_action_tag(1030)
	price_copper.set_completed_action_tag(1031)
	price_gems.set_completed_action_tag(1032)
	demand_copper.set_completed_action_tag(1033)

	kr20.set_completed_action_tag(1003)
	kr21.set_completed_action_tag(1004)
	kr22.set_completed_action_tag(1005)
	kr23.set_completed_action_tag(1028)
	kr24.set_completed_action_tag(1028)
	kr25.set_completed_action_tag(1028)
	kr26.set_completed_action_tag(1028)
	kr27.set_completed_action_tag(1028)

	// Chain-only oil requests (dormant until a KR/late leaf fires them).
	var oil3 = city.create_good_request({ // i3 oil×1000
		tag_id: 1003, resource: RESOURCE_OIL, amount: 1000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil3.set_sender_faction(0)
	oil3.set_completed_action_tag(1021)
	oil3.set_refusal_action_tag(1025)
	oil3.set_too_late_action_tag(1007)

	var oil4 = city.create_good_request({ // i4 oil×2000
		tag_id: 1004, resource: RESOURCE_OIL, amount: 2000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil4.set_sender_faction(0)
	oil4.set_completed_action_tag(1022)
	oil4.set_refusal_action_tag(1026)
	oil4.set_too_late_action_tag(1008)

	var oil5 = city.create_good_request({ // i5 oil×4000
		tag_id: 1005, resource: RESOURCE_OIL, amount: 4000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil5.set_sender_faction(0)
	oil5.set_completed_action_tag(1023)
	oil5.set_refusal_action_tag(1027)
	oil5.set_too_late_action_tag(1028)

	var oil6 = city.create_good_request({ // i6 late-branch oil×2000
		tag_id: 1006, resource: RESOURCE_OIL, amount: 2000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil6.set_sender_faction(0)
	oil6.set_completed_action_tag(1004)
	oil6.set_refusal_action_tag(1025)
	oil6.set_too_late_action_tag(1007)

	var oil7 = city.create_good_request({ // i7 late-branch oil×4000
		tag_id: 1007, resource: RESOURCE_OIL, amount: 4000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil7.set_sender_faction(0)
	oil7.set_completed_action_tag(1005)
	oil7.set_refusal_action_tag(1026)
	oil7.set_too_late_action_tag(1008)

	var oil8 = city.create_good_request({ // i8 late-branch oil×8000
		tag_id: 1008, resource: RESOURCE_OIL, amount: 8000, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	oil8.set_sender_faction(0)
	oil8.set_completed_action_tag(1023)
	oil8.set_refusal_action_tag(1027)
	oil8.set_too_late_action_tag(1028)
}

[es=event_mission_start, mission=mission14]
function mission14_on_start(ev) {
	__image_request_pak(PACK_MASTABA)
	__image_request_pak(PACK_BENT_PYRAMID)
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN) // favour Pharaoh army (i37→38)
	mission_show_start_message(mission, "message_mission_south_dahshur")
	empire.set_id(13)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}

	mission14_ensure_grain_kr_leaves()
	mission14_ensure_limestone_gift_leaves()
	mission14_ensure_oil_ladder_leaves()
}

// pak i=2: oil×500 / 12mo once at y1m6 → ok KR+6→ladder / refuse KR−20→siege / late oil×2000.
[es=event_advance_month, mission=mission14]
function mission14_event_i2_oil_request(ev) {
	if (mission.event2_oil_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 6)) {
		return
	}
	mission.event2_oil_done = true
	mission14_ensure_oil_ladder_leaves()
	mission14_fire_request(2002, RESOURCE_OIL, 500, 12, 1020, 1024, 1006, 0, 0)
}

// pak i=9: grain×10 / 24mo recurring from y2m10, sender=pharaoh.
[es=event_advance_month, mission=mission14]
function mission14_event_i9_grain_recurring(ev) {
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 10)) {
		return
	}
	if (mission.event9_grain_last_year == ev.years_since_start) {
		return
	}
	var abs_month = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_GRAIN, "grain_recurring", abs_month)) {
		return
	}
	mission.event9_grain_last_year = ev.years_since_start
	mission14_ensure_grain_kr_leaves()
	mission14_fire_request(3000 + 9 * 100 + ev.years_since_start, RESOURCE_GRAIN, 10, 24, 1017, 1018, 1019, 0, 1)
}

// pak i=10: limestone×32 / 24mo once at y4m8 (subtype=4 as in pak).
[es=event_advance_month, mission=mission14]
function mission14_event_i10_limestone_request(ev) {
	if (mission.event10_limestone_done) {
		return
	}
	if (ev.years_since_start < 4 || (ev.years_since_start == 4 && ev.month < 8)) {
		return
	}
	mission.event10_limestone_done = true
	mission14_ensure_limestone_gift_leaves()
	mission14_fire_request(2010, RESOURCE_LIMESTONE, 32, 24, 1014, 1015, 1016, 4, 0)
}

// pak i=11: wage decrease amount=1 recurring from y5m0.
[es=event_advance_month, mission=mission14]
function mission14_event_i11_wage_decrease(ev) {
	if (ev.years_since_start < 5) {
		return
	}
	if (mission.event11_wage_decrease_last_year == ev.years_since_start) {
		return
	}
	mission.event11_wage_decrease_last_year = ev.years_since_start
	mission14_fire_simple_event(3000 + 11 * 100 + ev.years_since_start, EVENT_TYPE_WAGE_DECREASE, undefined, 1)
}

// Favour: pak i=37 size=49 by_favour → chain i=38 size=21 (attack=RANDOM).
[es=event_advance_month, mission=mission14]
function mission14_pharaoh_favour_invasion(ev) {
	mission_pharaoh_favour_invasion_tick(mission, 49, 21)
}
