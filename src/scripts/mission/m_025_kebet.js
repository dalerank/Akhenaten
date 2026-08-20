log_info("akhenaten: mission 25 kebet started")

// Empire / events aligned with original campaign scenario 25 (2026-07-26 dump).
// Empire id=24. Scenario enemy ENEMY_6_KUSHITE; every invasion in the pak is
// invader=egypt(2) (Khmun loyalists) or pharaoh(3) on the favour trigger.
// Gods: Osiris (patron x2), Ra, Seth. Funds Normal 20000 / loan 3500 / debt 20. Rank 9.
// Win: pop 7000 / culture 40 / prosperity 45 / monuments 14 / kingdom 85 / housing 13.
// Monuments: Large Obelisk (gr198 23) + Small Obelisk x2 (22/22) — all three implemented,
// so the pak goal 14 is kept as-is (Large 4 + Small 2 -> 2.25*6+4.5 = 18 >= 14).
// Burial: pak burial_count=0 — no provisions block (nothing to hide).
// Trade: Waset(1, open at start) Kharga(4) Buhen(6 sea).
// Display: Byblos(2) Kerma(3 sea) Men-nefer(5 sea) Dakhla(7) Khmun(8 sea) Thinis(9 sea)
//   Dunqul Henen-nesw Jericho. SKIP empty map_obj idx=11.
// Men-nefer / Khmun are display cities unlocked mid-game by CITY_STATUS NEW_TRADE
// (i=23 loc=5, i=21 loc=8) — pak leaves their goods empty, so standard goods are used
// to keep the unlock playable (same treatment as Kerma in mission 24).
// DEMAND_* / CITY_STATUS events address the trade route via loc (1=Waset .. 9=Thinis);
// their `city` field is editor junk (often points at Kebet itself).
// Triage SKIP: i=28 invasion amount=0 (orphan chain child of i=27).
// Invasion loc = 1-based land point index; the map only has land[0]=[15,43], so loc 2/3/4
// fall back to -1 (Egyptian spawns at the map entry point). Sea point [71,43] is water and
// no pak invasion is naval here, so it stays unused.
//
// Tag_id scheme:
//   1000 + i               chain-only leaves / chain requests
//   2000 + i               once calendar roots

mission25 { // Kebet (Coptos) — Reunification; briefing key = coptos
	map_file : "data/maps/m_025_kebet.map"

	// Map points from data/maps/m_025_kebet.map.
	herd_points_predator [ [123, 115], [56, 60], [70, 52] ]
	herd_points_prey [ [87, 8] ]
	fishing_points [ [54, 47], [75, 66], [87, 90], [129, 111], [100, 97] ]

	start_message : "message_mission_coptos"
	selection_title : "Kebet"
	player_rank : 9
	reset_personal_savings : true

	// Kebet (25) and Menat (26) are a choice pair; both converge on Itjtawy (27).
	next_mission : 27

	// pak Normal funds=20000 loan=3500 debt_interest=20 -> int_dcy around Normal.
	initial_funds [40000, 26600, 20000, 13400, 10600]
	rescue_loans [7000, 4700, 3500, 2300, 1800]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/225_mission.mp3"
		victory : "Voice/Mission/225_victory.mp3"
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
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY,
		BUILDING_GRANITE_QUARRY, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_LARGE_OBELISK, BUILDING_SMALL_OBELISK,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// pak housing count enabled with goal 0 (no-op) -> only housing_level is kept.
	win_criteria {
		population    {enabled : true, goal : 7000 }
		culture       {enabled : true, goal : 40 }
		prosperity    {enabled : true, goal : 45 }
		monuments     {enabled : true, goal : 14 }
		kingdom       {enabled : true, goal : 85 }
		housing_level {enabled : true, goal : 13 }
	}

	entry_point [123, 130]
	exit_point [30, 55]
	river_entry_point [133, 118]
	river_exit_point [46, 40]
	disembark_points [ [88, 76], [79, 90], [94, 89] ]
	invasion_points_land [ [15, 43] ]
	invasion_points_sea [ [71, 43] ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Kebet"
			idx : 6
			pos : [829, 900]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FIGS, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_FLAX, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_COPPER ]
		}

		{
			name : "Waset"
			idx : 13
			pos : [811, 968]
			route : 1
			is_open : true
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_FIGS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_STONE, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Kharga Oasis"
			idx : 8
			pos : [624, 1121]
			route : 4
			is_open : false
			cost_to_open : 700
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BARLEY, RESOURCE_TIMBER ]
			buys [ RESOURCE_FISH ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}

		{
			name : "Buhen"
			idx : 0
			pos : [766, 1345]
			route : 6
			is_open : false
			cost_to_open : 520
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BARLEY, RESOURCE_BEER ]
			buys [ RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 2
			cost_to_open : 1250
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 7
			pos : [732, 1491]
			route : 3
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			// Display Egyptian; unlocked by i=23 NEW_TRADE (pak city=Jericho junk, loc=5=route).
			// Pak sells/buys are empty — standard Men-nefer goods keep the unlock playable.
			name : "Men-nefer"
			idx : 10
			pos : [545, 487]
			route : 5
			is_open : false
			cost_to_open : 650
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
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
			route : 7
			cost_to_open : 1000
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Display foreign; the loyalist city from the briefing. Conquered by i=16 and
			// opened for trade by i=21 NEW_TRADE (pak city=Kebet junk, loc=8=route).
			name : "Khmun"
			idx : 9
			pos : [577, 758]
			route : 8
			is_open : false
			cost_to_open : 100
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
			]
		}

		{
			name : "Thinis"
			idx : 12
			pos : [687, 871]
			route : 9
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
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
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Jericho"
			idx : 5
			pos : [896, 233]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 1
			points [
				[844, 1002], [850, 921]
			]
		}
		{
			route : 2
			type : 1
			points [
				[896, 89], [869, 116], [866, 126], [861, 148], [833, 292], [825, 304],
				[800, 318], [677, 357], [639, 358], [628, 368], [616, 389], [599, 399],
				[591, 399], [587, 422], [569, 440], [557, 478], [583, 526], [600, 609],
				[586, 626], [583, 648], [569, 670], [570, 710], [568, 727], [585, 738],
				[585, 755], [595, 792], [614, 814], [645, 823], [660, 844], [743, 917],
				[757, 915], [776, 933], [812, 908], [824, 922], [833, 936]
			]
		}
		{
			route : 3
			type : 2
			points [
				[742, 1498], [908, 1313]
			]
		}
		{
			route : 4
			type : 1
			points [
				[639, 1136], [684, 1037], [744, 989], [784, 965], [832, 924]
			]
		}
		{
			route : 5
			type : 2
			points [
				[570, 510], [587, 530], [595, 590], [598, 611], [582, 640], [585, 647],
				[574, 668], [574, 726], [586, 739], [588, 755], [598, 793], [618, 811],
				[641, 817], [688, 865], [742, 912], [757, 911], [776, 927], [809, 904],
				[825, 915], [834, 930]
			]
		}
		{
			route : 6
			type : 2
			points [
				[790, 1365], [811, 1340], [820, 1322], [848, 1304], [863, 1321], [878, 1302],
				[898, 1251], [907, 1228], [890, 1211], [893, 1204], [896, 1200], [893, 1195],
				[895, 1181], [881, 1160], [886, 1137], [878, 1115], [883, 1104], [878, 1096],
				[879, 1081], [876, 1063], [865, 1052], [865, 1037], [826, 993], [817, 963],
				[826, 947], [844, 933]
			]
		}
		{
			route : 7
			type : 1
			points [
				[372, 1058], [399, 1059], [474, 1046], [576, 1044], [627, 1029], [674, 995],
				[711, 975], [765, 957], [835, 933]
			]
		}
		{
			route : 8
			type : 2
			points [
				[596, 785], [614, 808], [625, 819], [635, 825], [650, 835], [654, 845],
				[669, 859], [743, 919], [753, 916], [776, 937], [811, 910], [825, 927],
				[838, 938]
			]
		}
		{
			route : 9
			type : 2
			points [
				[724, 889], [747, 911], [758, 909], [789, 930], [810, 914], [837, 934]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [538, 420], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [414, 643], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [381, 1037], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [518, 489], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [595, 452], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [623, 564], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [506, 554], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [571, 594], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [526, 529], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [603, 547], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [815, 892], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [709, 910], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 1087], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [769, 1197], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [784, 1328], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [866, 999], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [853, 985], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [494, 517], image : "pharaoh_general/empire_bits_00123" }
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
		flood_leaves_wired : false
		food_leaves_wired : false
		henna_leaves_wired : false
		fish_i22_leaves_wired : false

		event0_flood_done : false
		event3_flood_done : false
		event6_demand_done : false
		event7_figs_done : false
		event12_weapons_done : false
		event15_henna_done : false
		event22_fish_done : false
		event33_demand_done : false
		event35_flood_done : false

		event24_invasion_done : false
		event25_invasion_done : false
		event26_invasion_done : false
		event27_invasion_done : false

		henna_raid_done : false
		henna_raid_wave2_done : false
		henna_raid_enemies_seen : false

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_enemies_seen : false

		start_message_shown : false
	}
}

function mission25_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission25_make_chain_request(tag, resource, amount, months, subtype, sender_faction, city_name) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(sender_faction === undefined ? 0 : sender_faction)
	return request
}

function mission25_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
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
	var event = city.create_chain_event(opts)
	if (ok_tag) {
		event.set_completed_action_tag(ok_tag)
	}
	event.execute()
	return event
}

function mission25_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, city_name, defeat_tag) {
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
	if (defeat_tag) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.execute()
	return request
}

// pak location_fields after randomize = 1-based land invasion point index (MAX 8).
// Map 25 only has land[0]=[15,43]; loc 2/3/4 have no point -> -1 (Egyptian falls back
// to the map entry point). Sea point [71,43] is water and unused (no naval pak invasion).
function mission25_loc_tile(loc) {
	if (loc == 1) {
		return [15, 43]
	}
	return [-1, -1]
}

function mission25_egypt_raid(invasion_id, size, attack_target, loc) {
	var tile = mission25_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 25 egypt raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

function mission25_favour_wave(size, invasion_id, loc) {
	var tile = mission25_loc_tile(loc === undefined ? 0 : loc)
	log_info("akhenaten: mission 25 kebet favour wave size=" + size + " kr=" + city.rating_kingdom
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		invasion_id: invasion_id,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	})
}

function mission25_ensure_flood_leaves() {
	// pak i=0 failed flood → i=1 barley demand− (loc 6 = Buhen) → i=2 barley price+ (ok=96 OOB).
	// pak i=3 failed flood → i=4 beer demand− → i=5 beer price+ (ok=99 OOB).
	// pak i=35 perfect flood → i=31 barley demand+ → i=32 barley price−.
	// pak i=33 beer demand+ → i=34 beer price−.
	if (mission.flood_leaves_wired) {
		return
	}
	mission.flood_leaves_wired = true
	var barley_down = mission25_make_leaf(1001, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_BARLEY, 88, 9,
		undefined, "Buhen")
	mission25_make_leaf(1002, EVENT_TYPE_PRICE_INCREASE, RESOURCE_BARLEY, 26, 9)
	barley_down.set_completed_action_tag(1002)

	var beer_down = mission25_make_leaf(1004, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_BEER, 82, 9,
		undefined, "Buhen")
	mission25_make_leaf(1005, EVENT_TYPE_PRICE_INCREASE, RESOURCE_BEER, 74, 9)
	beer_down.set_completed_action_tag(1005)

	var barley_up = mission25_make_leaf(1031, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BARLEY, 9, 2,
		undefined, "Buhen")
	mission25_make_leaf(1032, EVENT_TYPE_PRICE_DECREASE, RESOURCE_BARLEY, 20, 2)
	barley_up.set_completed_action_tag(1032)

	mission25_make_leaf(1034, EVENT_TYPE_PRICE_DECREASE, RESOURCE_BEER, 71, 2)
}

function mission25_ensure_food_leaves() {
	// Shared outcomes of the famine requests i=7/9/10/12/22:
	//   i=8  DEMAND_INCREASE barley (loc 4 = Kharga) — ok leaf of i=7/9/10.
	//   i=11 KR−18 — refuse leaf of i=7/9/10/12/22.
	//   i=13 DEMAND_INCREASE figs (loc 1 = Waset) — ok leaf of i=12.
	//   i=14 KR−5 — late leaf of i=12/22.
	// i=9 (fish×11) is the late leaf of i=7, i=10 (figs×12) the late leaf of i=9.
	if (mission.food_leaves_wired) {
		return
	}
	mission.food_leaves_wired = true
	mission25_make_leaf(1008, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BARLEY, 24, 2,
		undefined, "Kharga Oasis")
	mission25_make_leaf(1011, EVENT_TYPE_REPUTATION_DECREASE, undefined, 18, 2)
	mission25_make_leaf(1013, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_FIGS, 9, 2, undefined, "Waset")
	mission25_make_leaf(1014, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)

	var fish = mission25_make_chain_request(1009, RESOURCE_FISH, 11, 6, 5, 0, "Henen-nesw")
	var figs = mission25_make_chain_request(1010, RESOURCE_FIGS, 12, 6, 5, 0, "Dunqul Oasis")
	fish.set_completed_action_tag(1008)
	fish.set_refusal_action_tag(1011)
	fish.set_too_late_action_tag(1010)
	figs.set_completed_action_tag(1008)
	figs.set_refusal_action_tag(1011)
	figs.set_too_late_action_tag(1011)
}

function mission25_ensure_henna_leaves() {
	// pak i=15 henna×56: ok→i=18 MESSAGE conquered→i=16 CITY_STATUS conquered (loc 8 = Khmun)
	//   →i=21 NEW_TRADE Khmun; refuse→i=19 egypt×60 (JS chain); late/defeat→i=17 henna×25.
	// pak i=17 henna×25 repeats the same outcomes; every non-ok branch ends in i=19.
	if (mission.henna_leaves_wired) {
		return
	}
	mission.henna_leaves_wired = true
	var message = mission25_make_leaf(1018, EVENT_TYPE_MESSAGE, undefined, 8, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Henen-nesw")
	var conquered = mission25_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Khmun")
	mission25_make_leaf(1021, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Khmun")
	var henna = mission25_make_chain_request(1017, RESOURCE_HENNA, 25, 6, 2, 1, "Henen-nesw")
	message.set_completed_action_tag(1016)
	conquered.set_completed_action_tag(1021)
	henna.set_completed_action_tag(1018)
	// refuse / late / defeat of i=17 → i=19 egypt×60, fired from event_request_cleared.
}

function mission25_ensure_fish_i22_leaves() {
	// pak i=22 fish×13 ok → i=23 NEW_TRADE (loc 5 = Men-nefer).
	if (mission.fish_i22_leaves_wired) {
		return
	}
	mission.fish_i22_leaves_wired = true
	mission25_make_leaf(1023, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
}

function mission25_ensure_leaves() {
	mission25_ensure_flood_leaves()
	mission25_ensure_food_leaves()
	mission25_ensure_henna_leaves()
	mission25_ensure_fish_i22_leaves()
}

[es=event_mission_start, mission=mission25]
function mission25_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_OBELISK_EXTRA)
	__image_request_pak(PACK_OBELISK_X3_A)
	__image_request_pak(PACK_OBELISK_X3_B)
	__image_request_pak(PACK_OBELISK_X3_C)
	__image_request_pak(PACK_OBELISK_X3_D)
	__image_request_pak(PACK_OBELISK_X5_A)
	__image_request_pak(PACK_OBELISK_X5_B)
	__image_request_pak(PACK_OBELISK_X5_C)
	__image_request_pak(PACK_OBELISK_X5_D)
	__image_request_pak(PACK_OBELISK_X5_E)
	__image_request_pak(PACK_OBELISK_X5_F)
	mission_show_start_message(mission, "message_mission_coptos")
	empire.set_id(24)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission25_ensure_leaves()
}

[es=event_advance_month, mission=mission25]
function mission25_requests_and_events(ev) {
	mission25_ensure_leaves()

	// pak i=0: failed flood y7m3 → i=1 barley demand− → i=2 barley price+.
	if (!mission.event0_flood_done && ev.years_since_start == 7 && ev.month == 3) {
		mission.event0_flood_done = true
		log_info("akhenaten: mission 25 failed flood (i=0)")
		mission25_fire_simple_event(2000, EVENT_TYPE_FAILED_FLOOD, undefined, 60,
			undefined, undefined, 1001)
	}

	// pak i=3: failed flood y9m3 → i=4 beer demand− → i=5 beer price+.
	if (!mission.event3_flood_done && ev.years_since_start == 9 && ev.month == 3) {
		mission.event3_flood_done = true
		log_info("akhenaten: mission 25 failed flood (i=3)")
		mission25_fire_simple_event(2003, EVENT_TYPE_FAILED_FLOOD, undefined, 83,
			undefined, undefined, 1004)
	}

	// pak i=6: DEMAND_INCREASE figs×9 y7m11 (loc 1 = Waset).
	if (!mission.event6_demand_done && ev.years_since_start == 7 && ev.month == 11) {
		mission.event6_demand_done = true
		log_info("akhenaten: mission 25 figs demand +9 Waset (i=6)")
		mission25_fire_simple_event(2006, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_FIGS, 9, "Waset")
	}

	// pak i=22: fish×13 /9mo y9m0 subtype=5 → ok i=23 NEW_TRADE Men-nefer.
	if (!mission.event22_fish_done && ev.years_since_start == 9 && ev.month == 0) {
		mission.event22_fish_done = true
		log_info("akhenaten: mission 25 fish×13 (i=22)")
		mission25_fire_request(2022, RESOURCE_FISH, 13, 9, 1023, 1011, 1014, 5, 0, "Dunqul Oasis")
	}

	// pak i=7: figs×28 /9mo y9m11 subtype=5 → late i=9 fish×11 → late i=10 figs×12.
	if (!mission.event7_figs_done && ev.years_since_start == 9 && ev.month == 11) {
		mission.event7_figs_done = true
		log_info("akhenaten: mission 25 figs×28 (i=7)")
		mission25_fire_request(2007, RESOURCE_FIGS, 28, 9, 1008, 1011, 1009, 5, 0, "Kerma")
	}

	// pak i=12: weapons×21 /9mo y10m2 sender=1 → ok i=13 figs demand+ Waset.
	if (!mission.event12_weapons_done && ev.years_since_start == 10 && ev.month == 2) {
		mission.event12_weapons_done = true
		log_info("akhenaten: mission 25 weapons×21 (i=12)")
		mission25_fire_request(2012, RESOURCE_WEAPONS, 21, 9, 1013, 1011, 1014, 0, 1, "Dunqul Oasis")
	}

	// pak i=15: henna×56 /12mo y11m2 subtype=2 sender=1.
	// refuse→egypt×60 via event_request_cleared (JS chain); no leaf 1019.
	if (!mission.event15_henna_done && ev.years_since_start == 11 && ev.month == 2) {
		mission.event15_henna_done = true
		log_info("akhenaten: mission 25 henna×56 (i=15)")
		mission25_fire_request(2015, RESOURCE_HENNA, 56, 12, 1018, 0, 1017, 2, 1, "Kerma", 1017)
	}

	// pak i=35: perfect flood y13m3 → i=31 barley demand+ → i=32 barley price−.
	if (!mission.event35_flood_done && ev.years_since_start == 13 && ev.month == 3) {
		mission.event35_flood_done = true
		log_info("akhenaten: mission 25 perfect flood (i=35)")
		mission25_fire_simple_event(2035, EVENT_TYPE_PERFECT_FLOOD, undefined, 9,
			undefined, undefined, 1031)
	}

	// pak i=33: DEMAND_INCREASE beer×6 y13m8 (loc 6 = Buhen) → i=34 beer price−.
	if (!mission.event33_demand_done && ev.years_since_start == 13 && ev.month == 8) {
		mission.event33_demand_done = true
		log_info("akhenaten: mission 25 beer demand +6 Buhen (i=33)")
		mission25_fire_simple_event(2033, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BEER, 6, "Buhen",
			undefined, 1034)
	}
}

// pak i=24/25/26/27: timed Khmun-loyalist egypt raids. i=27 ok→i=28 is SKIPped (amount=0).
[es=event_advance_month, mission=mission25]
function mission25_timed_invasions(ev) {
	if (!mission.event24_invasion_done && ev.years_since_start == 2 && ev.month == 4) {
		mission.event24_invasion_done = true
		mission25_egypt_raid(24, 17, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 1)
		return
	}
	if (!mission.event25_invasion_done && ev.years_since_start == 5 && ev.month == 1) {
		mission.event25_invasion_done = true
		mission25_egypt_raid(25, 33, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 1)
		return
	}
	if (!mission.event26_invasion_done && ev.years_since_start == 7 && ev.month == 9) {
		mission.event26_invasion_done = true
		mission25_egypt_raid(26, 55, EVENT_ATTACK_TARGET_RANDOM, 3)
		return
	}
	if (!mission.event27_invasion_done && ev.years_since_start == 10 && ev.month == 0) {
		mission.event27_invasion_done = true
		mission25_egypt_raid(27, 70, EVENT_ATTACK_TARGET_RANDOM, 2)
	}
}

// Chain invasions from JS after a request refuse (EVENT_TYPE_INVASION is a no-op).
[es=event_request_cleared, mission=mission25]
function mission25_on_request_cleared(ev) {
	if (mission.henna_raid_done) {
		return
	}
	var outcome = mission_request_outcome(ev)
	// i=15 refuse and every non-ok outcome of the i=17 follow-up land on i=19 egypt×60.
	var from_i15 = (ev.tag_id == 2015 && outcome == "refuse")
	var from_i17 = (ev.tag_id == 1017 && outcome != "ok")
	if (!from_i15 && !from_i17) {
		return
	}
	mission.henna_raid_done = true
	mission.henna_raid_enemies_seen = false
	log_info("akhenaten: mission 25 egypt×60 after henna refuse (i=19)", {ev:ev})
	mission25_egypt_raid(19, 60, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 1)
}

// pak i=19 ok→i=20: a second egypt×60 wave once the first one is wiped (loc 8 → entry).
[es=event_advance_month, mission=mission25]
function mission25_henna_raid_second_wave(ev) {
	if (!mission.henna_raid_done || mission.henna_raid_wave2_done) {
		return
	}
	if (city.num_enemy_formations > 0) {
		mission.henna_raid_enemies_seen = true
		return
	}
	if (!mission.henna_raid_enemies_seen) {
		return
	}
	mission.henna_raid_wave2_done = true
	mission25_egypt_raid(20, 60, EVENT_ATTACK_TARGET_BEST_BUILDINGS, 8)
}

// pak i=29→30: favour pharaoh×60 loc=2 → chain ×60 loc=4 (attack=RANDOM).
[es=event_advance_month, mission=mission25]
function mission25_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave2_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_enemies_seen) {
			return
		}
		mission.pharaoh_favour_wave2_done = true
		mission25_favour_wave(60, 30, 4)
		return
	}

	if (mission.pharaoh_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.pharaoh_favour_invasion_done = true
	mission.pharaoh_favour_enemies_seen = false
	mission25_favour_wave(60, 29, 2)
}
