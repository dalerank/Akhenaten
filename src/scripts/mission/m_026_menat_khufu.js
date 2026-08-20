log_info("akhenaten: mission 26 menat khufu started")

// Empire / events aligned with original campaign scenario 26 (2026-07-26 dump).
// Empire id=1. Scenario enemy ENEMY_6_KUSHITE. Favour invasions invader=pharaoh(3) → ENEMY_3_EGYPTIAN.
// Gods: Osiris(2), Ra(1), Bast(1) — no JS override. Funds Normal 10000 / loan 2500 / debt 20. Rank 9.
// Win: pop 7000 / culture 60 / prosperity 50 / monuments 21 (2×small obelisk 2+2 + Small
//   mudbrick 4 → trunc(2.25·8+4.5)=22 ≥ pak 21) / kingdom 75 / housing 10.
// Monuments pak: first=22 Small Obelisk ×2, third=3 Small Mudbrick Pyramid.
// Burial: pottery×8 beer×32 linen×32 papyrus×8 granite×32. Climate northern (map).
// Trade: Waset(1 sea) Men-nefer(2 sea) Dakhla(3). Display: Buhen Byblos Dunqul Henen-nesw Jericho Kebet Kerma Kharga.
// Triage: SKIP empty map_obj idx=11; SKIP orphan msgs i=1,4,8,11,14,17,21,24,27,30,33,36; SKIP DEMAND chain_only i=6.
// No pak inv_land/sea — omit invasion_points_*; favour tile entry fallback.
// Events: food requests (pomegranates/figs); linen DEMAND +7 Dakhla y12m0; favour egypt×40→×40.
//
// Tag_id scheme:
//   1000 + i               chain-only leaves
//   2000 + i               once calendar roots

mission26 { // Menat Khufu (Beni Hasan) — Reunification
	map_file : "data/maps/m_026_menat_khufu.map"
	start_message : "message_mission_beni_hasan"
	selection_title : "Menat Khufu"
	player_rank : 9

	// Kebet (25) and Menat (26) are a choice pair; both converge on Itjtawy (27).
	next_mission : 27

	// pak Normal funds=10000 loan=2500 debt_interest=20 → int_dcy around Normal.
	initial_funds [20000, 13300, 10000, 6700, 5300]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/226_mission.mp3"
		victory : "Voice/Mission/226_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
		BUILDING_SMALL_OBELISK, BUILDING_SMALL_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// Monuments 21: 2×Small Obelisk(2) + Small mudbrick(4) → trunc(22.5)=22 ≥ 21.
	win_criteria {
		population    {enabled : true, goal : 7000 }
		culture       {enabled : true, goal : 60 }
		prosperity    {enabled : true, goal : 50 }
		monuments     {enabled : true, goal : 21 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [128, 125]
	exit_point [30, 55]
	river_entry_point [117, 134]
	river_exit_point [20, 66]
	disembark_points [ [-1, -1], [-1, -1], [53, 70] ]

	// pak burial_provisions (scenario 26 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_POTTERY, required: 8 }
		{ resource: RESOURCE_BEER, required: 32 }
		{ resource: RESOURCE_LINEN, required: 32 }
		{ resource: RESOURCE_PAPYRUS, required: 8 }
		{ resource: RESOURCE_GRANITE, required: 32 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
			{
				name : "Menat Khufu"
				idx : 10
				pos : [578, 720]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [ RESOURCE_POMEGRANATES, RESOURCE_FIGS, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_STONE ]
				buys [ RESOURCE_BRICKS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			}

			{
				name : "Waset"
				idx : 12
				pos : [811, 968]
				route : 1
				is_open : false
				cost_to_open : 600
				is_sea_trade : true
				type : EMPIRE_CITY_PHARAOH_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
					{ resource: RESOURCE_STONE, limit: 2500 }
					{ resource: RESOURCE_LIMESTONE, limit: 2500 }
					{ resource: RESOURCE_GRANITE, limit: 2500 }
					{ resource: RESOURCE_COPPER, limit: 2500 }
				]
			}

			{
				name : "Men-nefer"
				idx : 9
				pos : [545, 487]
				route : 2
				is_open : false
				cost_to_open : 400
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
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
				name : "Dakhla Oasis"
				idx : 2
				pos : [349, 1037]
				route : 3
				is_open : false
				cost_to_open : 400
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				max_traders : 1
				trade_limits : default_trade_limits
				sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
				buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
				route_limits [
					{ resource: RESOURCE_MEAT, limit: 2500 }
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 1500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				]
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
				name : "Byblos"
				idx : 1
				pos : [891, 68]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}

			{
				name : "Dunqul Oasis"
				idx : 3
				pos : [795, 1191]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}

			{
				name : "Henen-nesw"
				idx : 4
				pos : [534, 626]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}

			{
				name : "Jericho"
				idx : 5
				pos : [896, 233]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}

			{
				name : "Kebet"
				idx : 6
				pos : [829, 900]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}

			{
				name : "Kerma"
				idx : 7
				pos : [732, 1491]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}

			{
				name : "Kharga Oasis"
				idx : 8
				pos : [630, 1130]
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
					[587, 745], [585, 756], [597, 776], [597, 793], [598, 800], [612, 813],
					[625, 816], [630, 822], [638, 822], [653, 833], [653, 841], [662, 849],
					[675, 852], [676, 863], [692, 872], [699, 884], [719, 888], [722, 898],
					[732, 907], [743, 915], [745, 916], [756, 914], [759, 922], [768, 927],
					[773, 934], [787, 928], [792, 921], [800, 919], [807, 915], [812, 905],
					[819, 912], [823, 923], [830, 943], [821, 950], [815, 963], [823, 991],
					[838, 1002]
				]
			}
			{
				route : 2
				type : 2
				points [
					[594, 729], [570, 729], [569, 712], [571, 682], [571, 664], [583, 651],
					[585, 629], [598, 611], [601, 594], [592, 587], [591, 560], [586, 542],
					[588, 526], [565, 504]
				]
			}
			{
				route : 3
				type : 1
				points [
					[368, 1055], [411, 1053], [429, 1054], [445, 1044], [457, 1032], [460, 997],
					[446, 931], [442, 854], [452, 823], [466, 808], [477, 797], [480, 795],
					[493, 787], [505, 784], [516, 778], [530, 774], [544, 770], [551, 767],
					[559, 766], [565, 765], [566, 765], [568, 765], [569, 765], [582, 757],
					[594, 742]
				]
			}
		]

		hide_pak_objects : true
		empire_ornaments [
			{ pos : [533, 417], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [419, 639], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [498, 516], image : "pharaoh_general/empire_bits_00123" }
			{ pos : [382, 1042], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [783, 1328], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [595, 450], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [518, 486], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [819, 886], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [775, 1196], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [695, 900], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [844, 1085], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [615, 548], image : "pharaoh_general/empire_bits_00118" }
			{ pos : [497, 554], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [567, 604], image : "pharaoh_general/empire_bits_00128" }
			{ pos : [853, 983], image : "pharaoh_general/empire_bits_00115" }
			{ pos : [861, 997], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [523, 534], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [593, 532], image : "pharaoh_general/empire_bits_00114" }
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
		figs_i7_leaves_wired : false
		pome_i13_leaves_wired : false
		pome_i20_leaves_wired : false
		pome_i26_leaves_wired : false
		pome_i32_leaves_wired : false

		event0_pome_done : false
		event7_figs_done : false
		event13_pome_done : false
		event19_linen_demand_done : false
		event20_pome_done : false
		event26_pome_done : false
		event32_pome_done : false
		event40_figs_done : false
		event41_pome_done : false

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave2_enemies_seen : false

		start_message_shown : false
	}
}

function mission26_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission26_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	city.create_chain_event(opts).execute()
}

function mission26_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, city_name) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
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
	request.execute()
	return request
}

function mission26_ensure_shared_kr_leaves() {
	// pak i=0/40/41 share: ok→2 KR+5; refuse→3 KR−13; late→5 KR+5.
	// SKIP orphan msgs i=1,4; SKIP DEMAND chain_only i=6.
	if (mission.shared_kr_leaves_wired) {
		return
	}
	mission.shared_kr_leaves_wired = true
	mission26_make_leaf(1002, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission26_make_leaf(1003, EVENT_TYPE_REPUTATION_DECREASE, undefined, 13, 2)
	mission26_make_leaf(1005, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
}

function mission26_ensure_figs_i7_leaves() {
	// pak i=7 figs×24: ok→9 KR+5; refuse→10 KR−18; late→12 KR+9. SKIP orphan msgs 8,11.
	if (mission.figs_i7_leaves_wired) {
		return
	}
	mission.figs_i7_leaves_wired = true
	mission26_make_leaf(1009, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission26_make_leaf(1010, EVENT_TYPE_REPUTATION_DECREASE, undefined, 18, 2)
	mission26_make_leaf(1012, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 2)
}

function mission26_ensure_pome_i13_leaves() {
	// pak i=13 pomegranates×7: ok→15 KR+5; refuse→16 KR−13; late→18 KR+2. SKIP msgs 14,17.
	if (mission.pome_i13_leaves_wired) {
		return
	}
	mission.pome_i13_leaves_wired = true
	mission26_make_leaf(1015, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission26_make_leaf(1016, EVENT_TYPE_REPUTATION_DECREASE, undefined, 13, 2)
	mission26_make_leaf(1018, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2)
}

function mission26_ensure_pome_i20_leaves() {
	// pak i=20 pomegranates×19: ok→22 KR+5; refuse→23 KR−12; late→25 KR+5. SKIP msgs 21,24.
	if (mission.pome_i20_leaves_wired) {
		return
	}
	mission.pome_i20_leaves_wired = true
	mission26_make_leaf(1022, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission26_make_leaf(1023, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
	mission26_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
}

function mission26_ensure_pome_i26_leaves() {
	// pak i=26 pomegranates×11: ok→28 KR+5; refuse→29 KR−11; late→31 KR+6. SKIP msgs 27,30.
	if (mission.pome_i26_leaves_wired) {
		return
	}
	mission.pome_i26_leaves_wired = true
	mission26_make_leaf(1028, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission26_make_leaf(1029, EVENT_TYPE_REPUTATION_DECREASE, undefined, 11, 2)
	mission26_make_leaf(1031, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2)
}

function mission26_ensure_pome_i32_leaves() {
	// pak i=32 pomegranates×24 sender=1: ok→34 KR+7; refuse→35 KR−22; late→37 KR+5. SKIP msgs 33,36.
	if (mission.pome_i32_leaves_wired) {
		return
	}
	mission.pome_i32_leaves_wired = true
	mission26_make_leaf(1034, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
	mission26_make_leaf(1035, EVENT_TYPE_REPUTATION_DECREASE, undefined, 22, 2)
	mission26_make_leaf(1037, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
}

function mission26_ensure_all_leaves() {
	mission26_ensure_shared_kr_leaves()
	mission26_ensure_figs_i7_leaves()
	mission26_ensure_pome_i13_leaves()
	mission26_ensure_pome_i20_leaves()
	mission26_ensure_pome_i26_leaves()
	mission26_ensure_pome_i32_leaves()
}

// No pak inv_land/sea points — Egyptian favour uses map entry fallback (tile −1,−1).
function mission26_favour_wave(size, invasion_id) {
	log_info("akhenaten: mission 26 menat khufu favour wave size=" + size + " kr=" + city.rating_kingdom
		+ " id=" + invasion_id)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		invasion_id: invasion_id,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
}

[es=event_mission_start, mission=mission26]
function mission26_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_OBELISK_EXTRA)
	__image_request_pak(PACK_OBELISK_X3_A)
	__image_request_pak(PACK_OBELISK_X3_B)
	__image_request_pak(PACK_OBELISK_X3_C)
	__image_request_pak(PACK_OBELISK_X3_D)
	mission_show_start_message(mission, "message_mission_beni_hasan")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission26_ensure_all_leaves()
}

[es=event_advance_month, mission=mission26]
function mission26_requests_and_events(ev) {
	mission26_ensure_all_leaves()

	// pak i=0: pomegranates×11 /7mo y1m2 subtype=5 city=Jericho → shared 1002/1003/1005.
	if (!mission.event0_pome_done && ev.years_since_start == 1 && ev.month == 2) {
		mission.event0_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×11 (i=0)")
		mission26_fire_request(2000, RESOURCE_POMEGRANATES, 11, 7, 1002, 1003, 1005, 5, 0, "Jericho")
	}
	// pak i=40: figs×20 /7mo y2m9 subtype=5 city=Kebet → shared leaves.
	if (!mission.event40_figs_done && ev.years_since_start == 2 && ev.month == 9) {
		mission.event40_figs_done = true
		log_info("akhenaten: mission 26 figs×20 (i=40)")
		mission26_fire_request(2040, RESOURCE_FIGS, 20, 7, 1002, 1003, 1005, 5, 0, "Kebet")
	}
	// pak i=41: pomegranates×20 /9mo y4m0 subtype=5 city=Dunqul Oasis → shared leaves.
	if (!mission.event41_pome_done && ev.years_since_start == 4 && ev.month == 0) {
		mission.event41_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×20 (i=41)")
		mission26_fire_request(2041, RESOURCE_POMEGRANATES, 20, 9, 1002, 1003, 1005, 5, 0, "Dunqul Oasis")
	}
	// pak i=7: figs×24 /24mo y6m6 subtype=5 city=Jericho.
	if (!mission.event7_figs_done && ev.years_since_start == 6 && ev.month == 6) {
		mission.event7_figs_done = true
		log_info("akhenaten: mission 26 figs×24 (i=7)")
		mission26_fire_request(2007, RESOURCE_FIGS, 24, 24, 1009, 1010, 1012, 5, 0, "Jericho")
	}
	// pak i=13: pomegranates×7 /12mo y11m11 subtype=5 city=Kerma.
	if (!mission.event13_pome_done && ev.years_since_start == 11 && ev.month == 11) {
		mission.event13_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×7 (i=13)")
		mission26_fire_request(2013, RESOURCE_POMEGRANATES, 7, 12, 1015, 1016, 1018, 5, 0, "Kerma")
	}
	// pak i=19: DEMAND_INCREASE linen×7 once y12m0 loc=3 → Dakhla route.
	if (!mission.event19_linen_demand_done && ev.years_since_start == 12 && ev.month == 0) {
		mission.event19_linen_demand_done = true
		log_info("akhenaten: mission 26 linen demand +7 Dakhla (i=19)")
		mission26_fire_simple_event(2019, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LINEN, 7, "Dakhla Oasis")
	}
	// pak i=20: pomegranates×19 /18mo y14m2 subtype=5 city=Henen-nesw.
	if (!mission.event20_pome_done && ev.years_since_start == 14 && ev.month == 2) {
		mission.event20_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×19 (i=20)")
		mission26_fire_request(2020, RESOURCE_POMEGRANATES, 19, 18, 1022, 1023, 1025, 5, 0, "Henen-nesw")
	}
	// pak i=26: pomegranates×11 /12mo y18m6 subtype=5 city=Jericho.
	if (!mission.event26_pome_done && ev.years_since_start == 18 && ev.month == 6) {
		mission.event26_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×11 (i=26)")
		mission26_fire_request(2026, RESOURCE_POMEGRANATES, 11, 12, 1028, 1029, 1031, 5, 0, "Jericho")
	}
	// pak i=32: pomegranates×24 /24mo y21m9 subtype=5 sender_faction=1 city=Jericho.
	if (!mission.event32_pome_done && ev.years_since_start == 21 && ev.month == 9) {
		mission.event32_pome_done = true
		log_info("akhenaten: mission 26 pomegranates×24 (i=32)")
		mission26_fire_request(2032, RESOURCE_POMEGRANATES, 24, 24, 1034, 1035, 1037, 5, 1, "Jericho")
	}
}

// pak i=38→39: by_favour egypt/pharaoh ×40 → after wipe ×40 (attack=4 RANDOM). No refuse-chain invasions.
[es=event_advance_month, mission=mission26]
function mission26_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave2_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_wave2_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_wave2_enemies_seen) {
			return
		}
		mission.pharaoh_favour_wave2_done = true
		mission26_favour_wave(40, 39)
		return
	}

	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	mission.pharaoh_favour_wave2_enemies_seen = false
	mission26_favour_wave(40, 38)
}
