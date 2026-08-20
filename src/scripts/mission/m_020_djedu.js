log_info("akhenaten: mission 20 djedu started")

// Empire / requests aligned with original campaign scenario 20 (2026-07-26 dump).
// Empire id=19. Enemy ENEMY_5_HYKSOS. Gods: Osiris, Ra, Bast.
// Funds Normal 7500 / loan 2500 / debt 20. Rank 7.
// Win: pop 4500 / culture 45 / prosperity 40 / monuments 13 / kingdom 50 / housing 10.
// Monuments goal 13 (pak; Sun Temple weight 4). Burial empty.
// Trade: On(1 sea) Dunqul(3). Display Iunet(2) Saqqara(4) Dahshur(5) Abedju(6). Men-nefer stub 19.
// Triage: SKIP empty map_obj idx=12; SKIP orphan route 25.
// Events: oil×500 ok→KR+8→gamemeat×5 ladder (i=5…11);
// fish×6 ladder i=12…17 (NEW_TRADE Byblos→demand/price meat; refuse→gamemeat×5 re-arm);
// fish×7 ladder i=21…27 (NEW_TRADE Dahshur→demand/price beer→price barley; refuse→timber×12 re-arm);
// timber×10 ladder i=28…33 (NEW_TRADE Dahshur→demand/price timber; refuse→linen×10 re-arm);
// fish×12 i=34…37+46 chain_only (entry: water i=45 ok / KR i=46); ok→Dahshur→demand timber×2→price i=31 shared;
// timber×15 recurring i=18…20 (ok→KR+1→gift sandstone×13; refuse/late→shared KR−6 i=2);
// linen×9 recurring i=38…40 idle-gated (ok→KR+7; refuse→land trade; late→shared KR−6);
// favour i=41…44: Pharaoh 25→25→25→45 (attack=RANDOM);
// wage i=4 separate recurring.
// Gamemeat triage: i=9 NEW_TRADE pak city=7 (Djedu=ours) → remap Dunqul Oasis.
// i=7 LOST_TRADE pak city=6 Dahshur. Fish i=13 NEW_TRADE pak city=5 Byblos.
//
// Tag_id scheme:
//   1000 + i               chain-only leaves / chain requests
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

mission20 { // Djedu (Abusir) — The Temple of the Sun
	map_file : "data/maps/m_020_djedu.map"

	// Map points from data/maps/m_020_djedu.map.
	herd_points_predator [ [61, 106], [66, 110], [41, 32] ]
	herd_points_prey [ [73, 97] ]
	fishing_points [ [93, 102], [84, 39] ]

	start_message : "message_mission_abusir"
	selection_title : "Djedu"
	player_rank : 7

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 46]
	choice [
		{
			name : "Dunqul"
			id : 21
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 47]
			pos [620, 420]
		}
		{
			name : "Dakhla"
			id : 22
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 48]
			pos [640, 480]
		}
	]

	initial_funds [15000, 10000, 7500, 5000, 4000]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/220_mission.mp3"
		victory : "Voice/Mission/220_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE,
		BUILDING_HUNTING_LODGE, BUILDING_FISHING_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_FIGS_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
		BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_BOOTH,
		BUILDING_SUN_TEMPLE,
		BUILDING_FESTIVAL_SQUARE, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	win_criteria {
		population    {enabled : true, goal : 4500 }
		culture       {enabled : true, goal : 45 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : true, goal : 50 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [30, 98]
	exit_point [9, 62]
	river_entry_point [106, 101]
	river_exit_point [37, 34]
	disembark_points [ [69, 62], [83, 99] ]
	invasion_points_land [ [128, 104], [77, 33] ]
	invasion_points_sea [ [60, 103], [130, 38] ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
cities [
		{
			name : "Djedu"
			idx : 6
			pos : [527, 390]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_FISH, RESOURCE_GAMEMEAT, RESOURCE_TIMBER, RESOURCE_REEDS ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_SANDSTONE ]
		}

		{
			name : "Dunqul Oasis"
			idx : 7
			pos : [795, 1191]
			route : 3
			is_open : false
			cost_to_open : 1300
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "On"
			idx : 14
			pos : [572, 454]
			route : 1
			is_open : false
			cost_to_open : 300
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
			]
		}

		{
			name : "Iunet"
			idx : 9
			pos : [783, 892]
			route : 2
			cost_to_open : 1000
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 15
			pos : [523, 539]
			route : 4
			cost_to_open : 300
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Display; LOST_TRADE i=7 / NEW_TRADE tails elsewhere. Pak sells/buys empty.
			name : "Dahshur"
			idx : 5
			pos : [570, 526]
			route : 5
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name : "Abedju"
			idx : 0
			pos : [696, 907]
			route : 6
			cost_to_open : 800
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
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
			name : "Behdet"
			idx : 2
			pos : [836, 1069]
			route : 0
			cost_to_open : 1200
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Buhen"
			idx : 3
			pos : [766, 1345]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Display; NEW_TRADE i=13. Pak sells/buys empty. Stub route (pak route=0).
			name : "Byblos"
			idx : 4
			pos : [891, 68]
			route : 7
			is_open : false
			cost_to_open : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name : "Henen-nesw"
			idx : 8
			pos : [534, 626]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kharga Oasis"
			idx : 10
			pos : [623, 1129]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Men-nefer"
			idx : 11
			pos : [548, 475]
			route : 19
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Nekhen"
			idx : 13
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[592, 474], [578, 491], [577, 506], [564, 494], [560, 477], [550, 468],
				[547, 460], [544, 443], [544, 432], [543, 427], [535, 412]
			]
		}
		{
			route : 2
			type : 2
			points [
				[805, 910], [789, 926], [764, 928], [746, 919], [706, 885], [640, 825],
				[622, 810], [596, 795], [586, 761], [571, 714], [574, 672], [587, 647],
				[587, 627], [600, 609], [600, 593], [591, 576], [588, 529], [565, 495],
				[549, 470], [539, 453], [539, 438], [538, 411]
			]
		}
		{
			route : 3
			type : 1
			points [
				[812, 1210], [814, 1113], [774, 1053], [717, 1007], [642, 921], [584, 880],
				[522, 778], [515, 713], [499, 634], [474, 573], [485, 439], [542, 416],
			]
		}
		{
			route : 4
			type : 1
			points [
				[537, 556], [531, 523], [527, 497], [518, 470], [504, 448], [517, 434],
				[538, 417]
			]
		}
		{
			route : 5
			type : 1
			points [
				[593, 544], [615, 530], [615, 488], [616, 455], [595, 437], [558, 417],
			]
		}
		{
			route : 6
			type : 1
			points [
				[713, 930], [599, 845], [541, 762], [535, 700], [520, 630], [489, 579],
				[493, 536], [494, 492], [492, 439], [544, 415]
			]
		}
		{
			// Byblos display — pak route=0; stub for NEW_TRADE i=13.
			route : 7
			type : 2
			deviation : 40
			points [ [891, 68], [527, 390] ]
		}
		{
			// Men-nefer display — no pak polyline; 2-pt stub.
			route : 19
			type : 1
			deviation : 40
			points [ [548, 475], [527, 390] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [602, 529], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [569, 592], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [498, 546], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [522, 488], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [606, 447], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [483, 502], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [507, 516], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [840, 1093], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [681, 883], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [820, 889], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [783, 1327], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [622, 548], image : "pharaoh_general/empire_bits_00118" }
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
		oil_kr_leaves_wired : false
		event0_oil_done : false
		event5_gamemeat_done : false
		event12_fish_done : false
		fish12_leaves_wired : false
		event21_fish_done : false
		fish21_leaves_wired : false
		event28_timber_done : false
		timber28_leaves_wired : false
		fish34_leaves_wired : false
		event45_water_done : false

		event4_wage_last_year : -1
		event18_timber_last_year : -1
		timber_recurring_ok_wired : false
		event38_linen_last_year : -1
		linen_leaves_wired : false
		linen_recurring_was_busy : false
		linen_recurring_idle_since_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_wave4_done : false
		pharaoh_favour_wave2_enemies_seen : false
		pharaoh_favour_wave3_enemies_seen : false
		pharaoh_favour_wave4_enemies_seen : false
		start_message_shown : false
	}
}

function mission20_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission20_fire_simple_event(tag, type, resource, amount, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	city.create_chain_event(opts).execute()
}

function mission20_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction) {
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

function mission20_ensure_oil_kr_and_gamemeat_i5() {
	// pak i=0 oil: ok→i=1 KR+8→i=5; refuse→i=2 KR−6; late→i=3 KR+2.
	// pak i=5 gamemeat×5 (calendar y4m0 + oil ok): ok→i=6 demand sandstone+6;
	//   refuse→i=7 LOST_TRADE Dahshur→i=8; late→i=8 gamemeat×13.
	// i=8 gamemeat×13: ok→i=9 NEW_TRADE→i=11; refuse/late→i=10 KR−6→i=8 re-arm.
	// i=9 NEW_TRADE: pak city=7 Djedu(ours) → remap Dunqul Oasis; ok→i=11.
	// i=11 gamemeat×8: ok→i=6; refuse/late→i=7.
	// Wage i=4 is a separate recurring calendar root (not oil ok tail).
	if (mission.oil_kr_leaves_wired) {
		return
	}
	mission.oil_kr_leaves_wired = true

	var kr_ok = mission20_make_leaf(1001, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2)
	mission20_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 2)
	mission20_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2)

	// i=6 demand sandstone +6 (shared leaf: i=5 ok and i=11 ok).
	mission20_make_leaf(1006, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_SANDSTONE, 6, 2)

	// i=7 LOST_TRADE Dahshur → i=8.
	var lost = mission20_make_leaf(1007, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Dahshur")

	// i=10 KR−6 → re-arm i=8.
	var kr_fail = mission20_make_leaf(1010, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 2)

	// i=9 NEW_TRADE Dunqul (remap) → i=11.
	var trade = mission20_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dunqul Oasis")

	// i=8 gamemeat×13 ONLY_VIA.
	var gamemeat13 = city.create_good_request({
		tag_id: 1008,
		resource: RESOURCE_GAMEMEAT,
		amount: 13,
		months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gamemeat13.set_sender_faction(0)
	gamemeat13.set_completed_action_tag(1009)
	gamemeat13.set_refusal_action_tag(1010)
	gamemeat13.set_too_late_action_tag(1010)

	// i=11 gamemeat×8 ONLY_VIA.
	var gamemeat8 = city.create_good_request({
		tag_id: 1011,
		resource: RESOURCE_GAMEMEAT,
		amount: 8,
		months_initial: 3,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gamemeat8.set_sender_faction(0)
	gamemeat8.set_completed_action_tag(1006)
	gamemeat8.set_refusal_action_tag(1007)
	gamemeat8.set_too_late_action_tag(1007)

	// i=5 gamemeat×5 ONLY_VIA (oil ok + calendar).
	var gamemeat5 = city.create_good_request({
		tag_id: 1005,
		resource: RESOURCE_GAMEMEAT,
		amount: 5,
		months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gamemeat5.set_sender_faction(0)
	gamemeat5.set_completed_action_tag(1006)
	gamemeat5.set_refusal_action_tag(1007)
	gamemeat5.set_too_late_action_tag(1008)

	lost.set_completed_action_tag(1008)
	trade.set_completed_action_tag(1011)
	kr_fail.set_completed_action_tag(1008)
	kr_ok.set_completed_action_tag(1005)
}

function mission20_ensure_fish_i12_leaves() {
	// pak i=12 fish×6 y6m1: ok→i=13 NEW_TRADE Byblos→i=14 demand meat+6→i=15 price meat+10;
	// refuse/late→i=16 gamemeat×5 (ok→i=13; refuse/late→i=17 KR−8→i=16 re-arm).
	if (mission.fish12_leaves_wired) {
		return
	}
	mission.fish12_leaves_wired = true

	var trade = mission20_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Byblos")
	var demand = mission20_make_leaf(1014, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_MEAT, 6, 2)
	mission20_make_leaf(1015, EVENT_TYPE_PRICE_INCREASE, RESOURCE_MEAT, 10, 2)
	var kr_fail = mission20_make_leaf(1017, EVENT_TYPE_REPUTATION_DECREASE, undefined, 8, 2)

	var gamemeat = city.create_good_request({
		tag_id: 1016,
		resource: RESOURCE_GAMEMEAT,
		amount: 5,
		months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	gamemeat.set_sender_faction(0)
	gamemeat.set_completed_action_tag(1013)
	gamemeat.set_refusal_action_tag(1017)
	gamemeat.set_too_late_action_tag(1017)

	trade.set_completed_action_tag(1014)
	demand.set_completed_action_tag(1015)
	kr_fail.set_completed_action_tag(1016)
}

function mission20_ensure_fish_i21_leaves() {
	// pak i=21 fish×7 y4m3: ok→i=22 NEW_TRADE Dahshur→i=23 demand beer+5→i=24 price beer+11→i=25 price barley+4;
	// refuse/late→i=26 timber×12 (ok→i=22; refuse/late→i=27 KR−6→i=26 re-arm).
	if (mission.fish21_leaves_wired) {
		return
	}
	mission.fish21_leaves_wired = true

	var trade = mission20_make_leaf(1022, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dahshur")
	var demand = mission20_make_leaf(1023, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BEER, 5, 2)
	var price_beer = mission20_make_leaf(1024, EVENT_TYPE_PRICE_INCREASE, RESOURCE_BEER, 11, 2)
	mission20_make_leaf(1025, EVENT_TYPE_PRICE_INCREASE, RESOURCE_BARLEY, 4, 2)
	var kr_fail = mission20_make_leaf(1027, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 2)

	var timber = city.create_good_request({
		tag_id: 1026,
		resource: RESOURCE_TIMBER,
		amount: 12,
		months_initial: 8,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	timber.set_sender_faction(0)
	timber.set_completed_action_tag(1022)
	timber.set_refusal_action_tag(1027)
	timber.set_too_late_action_tag(1027)

	trade.set_completed_action_tag(1023)
	demand.set_completed_action_tag(1024)
	price_beer.set_completed_action_tag(1025)
	kr_fail.set_completed_action_tag(1026)
}

function mission20_ensure_timber_i28_leaves() {
	// pak i=28 timber×10 y5m4: ok→i=29 NEW_TRADE Dahshur→i=30 demand timber+9→i=31 price timber+8;
	// refuse/late→i=32 linen×10 (ok→i=29; refuse/late→i=33 KR−2→i=32 re-arm). defeat=999 → omit.
	if (mission.timber28_leaves_wired) {
		return
	}
	mission.timber28_leaves_wired = true

	var trade = mission20_make_leaf(1029, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dahshur")
	var demand = mission20_make_leaf(1030, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 9, 2)
	mission20_make_leaf(1031, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 8, 2)
	var kr_fail = mission20_make_leaf(1033, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 2)

	var linen = city.create_good_request({
		tag_id: 1032,
		resource: RESOURCE_LINEN,
		amount: 10,
		months_initial: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	linen.set_sender_faction(0)
	linen.set_completed_action_tag(1029)
	linen.set_refusal_action_tag(1033)
	linen.set_too_late_action_tag(1033)

	trade.set_completed_action_tag(1030)
	demand.set_completed_action_tag(1031)
	kr_fail.set_completed_action_tag(1032)
}

function mission20_ensure_fish_i34_leaves() {
	// pak i=34 fish×12 chain_only (NOT calendar y4m5): ok→i=35 NEW_TRADE Dahshur→i=36 demand timber+5
	// →i=37 demand timber+7→i=31 price timber (shared with timber ladder);
	// refuse/late→i=46 KR−5→i=34 re-arm. Entry: i=45 contaminated water ok→34.
	mission20_ensure_timber_i28_leaves()
	if (mission.fish34_leaves_wired) {
		return
	}
	mission.fish34_leaves_wired = true

	var trade = mission20_make_leaf(1035, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dahshur")
	var demand1 = mission20_make_leaf(1036, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 5, 2)
	var demand2 = mission20_make_leaf(1037, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 7, 2)
	var kr_fail = mission20_make_leaf(1046, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)

	var fish = city.create_good_request({
		tag_id: 1034,
		resource: RESOURCE_FISH,
		amount: 12,
		months_initial: 9,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	fish.set_sender_faction(0)
	fish.set_completed_action_tag(1035)
	fish.set_refusal_action_tag(1046)
	fish.set_too_late_action_tag(1046)

	trade.set_completed_action_tag(1036)
	demand1.set_completed_action_tag(1037)
	demand2.set_completed_action_tag(1031) // shared i=31 price timber
	kr_fail.set_completed_action_tag(1034)
}

function mission20_ensure_timber_i18_leaves() {
	// pak i=18 timber×15 recurring y43m2+: ok→i=19 KR+1→i=20 gift sandstone×13;
	// refuse/late→shared i=2 KR−6 (tag 1002 from oil).
	mission20_ensure_oil_kr_and_gamemeat_i5()
	if (mission.timber_recurring_ok_wired) {
		return
	}
	mission.timber_recurring_ok_wired = true

	var kr_ok = mission20_make_leaf(1019, EVENT_TYPE_REPUTATION_INCREASE, undefined, 1, 2)
	mission20_make_leaf(1020, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_SANDSTONE, 13, 2)
	kr_ok.set_completed_action_tag(1020)
}

function mission20_ensure_linen_i38_leaves() {
	// pak i=38 linen×9 recurring y31m6+: ok→i=39 KR+7; refuse→i=40 land trade;
	// late→shared i=2 KR−6 (tag 1002).
	mission20_ensure_oil_kr_and_gamemeat_i5()
	if (mission.linen_leaves_wired) {
		return
	}
	mission.linen_leaves_wired = true
	mission20_make_leaf(1039, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
	mission20_make_leaf(1040, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 6, 2)
}

function mission20_fire_gamemeat_i5() {
	if (mission.event5_gamemeat_done) {
		return
	}
	mission.event5_gamemeat_done = true
	mission20_ensure_oil_kr_and_gamemeat_i5()
	log_info("akhenaten: mission 20 gamemeat×5 (i=5)")
	__city_event_fire_chain(1005)
}

[es=event_mission_start, mission=mission20]
function mission20_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_SUN_TEMPLE_1)
	__image_request_pak(PACK_SUN_TEMPLE_2)
	__image_request_pak(PACK_SUN_TEMPLE_3)
	__image_request_pak(PACK_SUN_TEMPLE_EXTRA)
	mission_show_start_message(mission, "message_mission_abusir")
	empire.set_id(19)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission20_ensure_oil_kr_and_gamemeat_i5()
	mission20_ensure_fish_i12_leaves()
	mission20_ensure_fish_i21_leaves()
	mission20_ensure_timber_i28_leaves()
	mission20_ensure_fish_i34_leaves()
	mission20_ensure_timber_i18_leaves()
	mission20_ensure_linen_i38_leaves()
}

[es=event_advance_month, mission=mission20]
function mission20_requests_and_economy(ev) {
	mission20_ensure_oil_kr_and_gamemeat_i5()
	mission20_ensure_fish_i12_leaves()
	mission20_ensure_fish_i21_leaves()
	mission20_ensure_timber_i28_leaves()
	mission20_ensure_fish_i34_leaves()
	mission20_ensure_timber_i18_leaves()
	mission20_ensure_linen_i38_leaves()

	var abs_month = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_LINEN, "linen_recurring", abs_month)

	if (!mission.event0_oil_done && ev.years_since_start == 2 && ev.month == 0) {
		mission.event0_oil_done = true
		log_info("akhenaten: mission 20 oil request×500")
		// ok→1001 KR+8→1005 gamemeat; refuse→1002; late→1003
		mission20_fire_request(2000, RESOURCE_OIL, 500, 6, 1001, 1002, 1003, 3, 1)
	}
	if (!mission.event5_gamemeat_done && ev.years_since_start == 4 && ev.month == 0) {
		// Calendar root; no-op if oil ok already fired tag 1005.
		mission20_fire_gamemeat_i5()
	}
	if (!mission.event12_fish_done && ev.years_since_start == 6 && ev.month == 1) {
		mission.event12_fish_done = true
		log_info("akhenaten: mission 20 fish×6 (i=12)")
		// ok→1013 Byblos→demand/price meat; refuse/late→1016 gamemeat×5 ladder
		mission20_fire_request(2012, RESOURCE_FISH, 6, 6, 1013, 1016, 1016, 0, 0)
	}
	if (!mission.event21_fish_done && ev.years_since_start == 4 && ev.month == 3) {
		mission.event21_fish_done = true
		log_info("akhenaten: mission 20 fish×7 (i=21)")
		// ok→1022 Dahshur→beer/barley; refuse/late→1026 timber×12 ladder
		mission20_fire_request(2021, RESOURCE_FISH, 7, 12, 1022, 1026, 1026, 0, 0)
	}
	if (!mission.event28_timber_done && ev.years_since_start == 5 && ev.month == 4) {
		mission.event28_timber_done = true
		log_info("akhenaten: mission 20 timber×10 (i=28)")
		// ok→1029 Dahshur→demand/price timber; refuse/late→1032 linen×10 ladder
		mission20_fire_request(2028, RESOURCE_TIMBER, 10, 12, 1029, 1032, 1032, 0, 0)
	}
	if (!mission.event45_water_done && ev.years_since_start == 16 && ev.month == 4) {
		mission.event45_water_done = true
		log_info("akhenaten: mission 20 contaminated water → fish×12 (i=45→34)")
		// pak i=45 ok→i=34 fish×12 chain_only (year/month on i=34 are not a calendar root).
		var water = city.create_chain_event({
			tag_id: 2045,
			type: EVENT_TYPE_CONTAMINATED_WATER,
			amount: 5,
			trigger: EVENT_TRIGGER_ONCE
		})
		water.set_completed_action_tag(1034)
		water.execute()
	}

	if (ev.years_since_start >= 10 && ev.month == 8
			&& mission.event4_wage_last_year != ev.years_since_start) {
		mission.event4_wage_last_year = ev.years_since_start
		mission20_fire_simple_event(3000 + 4 * 100 + ev.years_since_start,
			EVENT_TYPE_WAGE_INCREASE, undefined, 2)
	}
	if (ev.years_since_start >= 43 && ev.month == 2
			&& mission.event18_timber_last_year != ev.years_since_start) {
		mission.event18_timber_last_year = ev.years_since_start
		log_info("akhenaten: mission 20 timber×15 recurring (i=18)")
		// ok→1019 KR+1→1020 gift sandstone×13; refuse/late→1002 shared KR−6
		mission20_fire_request(3000 + 18 * 100 + ev.years_since_start,
			RESOURCE_TIMBER, 15, 6, 1019, 1002, 1002, 0, 0)
	}
	if (ev.years_since_start >= 31 && ev.month == 6
			&& mission.event38_linen_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_LINEN, "linen_recurring", abs_month)) {
		mission.event38_linen_last_year = ev.years_since_start
		log_info("akhenaten: mission 20 linen×9 recurring (i=38)")
		// ok→1039 KR+7; refuse→1040 land trade; late→1002 shared KR−6
		mission20_fire_request(3000 + 38 * 100 + ev.years_since_start,
			RESOURCE_LINEN, 9, 6, 1039, 1040, 1002, 0, 0)
	}
}

function mission20_favour_wave(size, invasion_id) {
	log_info("akhenaten: mission 20 favour wave size=" + size + " kr=" + city.rating_kingdom)
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

// pak i=41→42→43→44: favour Pharaoh 25→25→25→45 (helper only supports two waves).
[es=event_advance_month, mission=mission20]
function mission20_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_wave3_done && !mission.pharaoh_favour_wave4_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_wave4_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_wave4_enemies_seen) {
			return
		}
		mission.pharaoh_favour_wave4_done = true
		mission20_favour_wave(45, 28)
		return
	}

	if (mission.pharaoh_favour_wave2_done && !mission.pharaoh_favour_wave3_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_wave3_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_wave3_enemies_seen) {
			return
		}
		mission.pharaoh_favour_wave3_done = true
		mission20_favour_wave(25, 27)
		return
	}

	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave2_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_wave2_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_wave2_enemies_seen) {
			return
		}
		mission.pharaoh_favour_wave2_done = true
		mission20_favour_wave(25, 26)
		return
	}

	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	mission20_favour_wave(25, 25)
}
