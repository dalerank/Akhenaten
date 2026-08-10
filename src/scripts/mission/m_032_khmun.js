log_info("akhenaten: mission 32 khmun started")

// Empire id=21. Hyksos reclaim (ENEMY_5_HYKSOS; pak enemy_id BARBARIAN ignored). Gods Ra×2, Ptah, Seth.
// Funds Normal 9000 / loan 3500 / debt 20. Rank 10.
// Win: pop 6000 / culture 55 / prosperity 50 / monuments TEMP 0 (pak 18; small mudbrick W=4 → 13.5 under F3) / kingdom 75 / housing 14.
// Monuments pak first=3 Small Mudbrick — building allowed; restore goal 18 after F3 weight calibrate.
// Burial ×5: weapons 5, beer 20, linen 32, luxury 20, papyrus 10.
// SKIP empty map_obj idx=9. Orphan routes 5/10 — empire display only.
// i=0/1 CITY_STATUS subtype0 loc=7/8 → FELL Heh/Iken (Nubian beat); trade opens via cost_to_open.
// i=23 subtype2 → NEW_TRADE Kerma (cosmetic; route=0). Gift i=16 limestone×64; i=17 pottery×20.
//
// Tag_id: 1000+i chain leaves; 2000+i once roots; 3000+i*100+year recurring.

mission32 { // Khmun (Hermopolis) — Egypt Reclaimed
	map_file : "data/maps/m_032_khmun.map"

	// Map points from data/maps/m_032_khmun.map.
	herd_points_predator [ [50, 32], [79, 35], [30, 92], [38, 39] ]

	start_message : "message_mission_hermopolis"
	selection_title : "Khmun"
	player_rank : 10
	reset_personal_savings : true

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 67]
	choice [
		{
			name : "Byblos"
			id : 34
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 68]
			pos [620, 420]
		}
		{
			name : "Baki"
			id : 35
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 69]
			pos [640, 480]
		}
	]

	initial_funds [18000, 12000, 9000, 6000, 4800]
	rescue_loans [7000, 4700, 3500, 2300, 1800]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/232_mission.mp3"
		victory : "Voice/Mission/232_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_COPPER_MINE,
		BUILDING_SMALL_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// Small mudbrick W=4 → trunc(2.25·4+4.5)=13; pak 18 = soft weight calib.
	win_criteria {
		population    {enabled : true, goal : 6000 }
		culture       {enabled : true, goal : 55 }
		prosperity    {enabled : true, goal : 50 }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : true, goal : 75 }
		housing_level {enabled : true, goal : 14 }
	}

	entry_point [16, 53]
	exit_point [109, 39]
	river_entry_point [41, 30]
	river_exit_point [39, 32]
	disembark_points [ [-1, -1], [-1, -1], [75, 47] ]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 5 }
		{ resource: RESOURCE_BEER, required: 20 }
		{ resource: RESOURCE_LINEN, required: 32 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 20 }
		{ resource: RESOURCE_PAPYRUS, required: 10 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:21}
	hide_pak_cities : true
	cities [
		{
			name : "Khmun"
			idx : 6
			pos : [577, 758]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_BARLEY, RESOURCE_FLAX, RESOURCE_STONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
		}
		{
			name : "Itjtawy"
			idx : 4
			pos : [580, 549]
			route : 1
			is_open : false
			cost_to_open : 450
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_STRAW, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}
		{
			name : "Tyre"
			idx : 14
			pos : [877, 121]
			route : 2
			is_open : false
			cost_to_open : 1250
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Pwenet"
			idx : 10
			pos : [1133, 1325]
			route : 3
			is_open : false
			cost_to_open : 1250
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Sharuhen"
			idx : 13
			pos : [836, 359]
			route : 6
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_BARLEY, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 7
			pos : [551, 479]
			route : 19
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}
		{
			name : "Bubastis"
			idx : 0
			pos : [573, 416]
			route : 9
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Gaza"
			idx : 1
			pos : [846, 280]
			route : 0
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Heh"
			idx : 2
			pos : [698, 1414]
			route : 7
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Iken"
			idx : 3
			pos : [735, 1380]
			route : 8
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Kerma"
			idx : 5
			pos : [732, 1491]
			route : 0
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Menat Khufu"
			idx : 8
			pos : [578, 720]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Rowarty"
			idx : 11
			pos : [612, 389]
			route : 4
			cost_to_open : 500
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sawu"
			idx : 12
			pos : [907, 834]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Waset"
			idx : 15
			pos : [811, 968]
			route : 0
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	routes [
		{
			route : 1
			type : 2
			points [
				[587, 574], [594, 591], [598, 595], [600, 605], [598, 611], [593, 617],
				[586, 626], [586, 627], [584, 634], [583, 641], [583, 644], [582, 649],
				[579, 654], [577, 657], [574, 661], [571, 665], [571, 671], [570, 679],
				[570, 686], [570, 693], [570, 703], [570, 708], [570, 711], [567, 713],
				[566, 715], [567, 721], [569, 725], [573, 731], [575, 733], [578, 735],
				[583, 738], [586, 743], [586, 747], [586, 753], [586, 758], [586, 760],
				[586, 768], [593, 776], [594, 777], [596, 786], [598, 789], [601, 791],
				[602, 792], [602, 792]
			]
		}
		{
			route : 2
			type : 2
			points [
				[895, 139], [868, 138], [862, 166], [860, 198], [854, 225], [847, 276],
				[829, 307], [797, 334], [775, 344], [738, 342], [709, 352], [691, 364],
				[674, 369], [645, 355], [636, 358], [614, 390], [601, 396], [590, 400],
				[590, 407], [585, 418], [575, 433], [567, 443], [566, 450], [561, 466],
				[555, 475], [557, 485], [558, 487], [564, 498], [566, 507], [578, 518],
				[584, 525], [586, 530], [586, 541], [593, 554], [593, 575], [595, 582],
				[605, 596], [608, 612], [592, 637], [589, 649], [580, 672], [577, 700],
				[577, 704], [577, 717], [579, 725], [592, 737], [596, 756], [600, 780],
				[603, 793]
			]
		}
		{
			route : 3
			type : 1
			points [
				[1153, 1343], [1140, 1278], [1110, 1239], [1093, 1213], [1063, 1150], [1046, 1094],
				[1040, 1058], [1020, 993], [983, 916], [976, 898], [947, 875], [925, 852],
				[901, 876], [863, 874], [827, 861], [800, 847], [777, 840], [725, 829],
				[639, 813], [634, 812], [610, 806]
			]
		}
		{
			route : 4
			type : 1
			points [
				[602, 789], [661, 716], [673, 694], [683, 669], [682, 645], [681, 605],
				[671, 556], [665, 518], [651, 459], [638, 419], [634, 410], [633, 410]
			]
		}
		{
			route : 5
			type : 2
			points [
				[599, 789], [576, 769], [576, 743], [557, 718], [562, 700], [562, 661],
				[580, 630], [601, 611], [594, 575], [584, 549], [588, 537], [580, 523],
				[571, 493], [571, 477], [573, 470], [574, 467], [579, 459], [594, 454],
				[638, 420], [638, 415]
			]
		}
		{
			route : 6
			type : 1
			points [
				[604, 788], [734, 682], [739, 636], [676, 541], [689, 494], [721, 481],
				[855, 376], [854, 378]
			]
		}
		{
			route : 7
			type : 1
			points [
				[717, 1432], [604, 1007], [558, 826], [602, 787], [602, 787]
			]
		}
		{
			route : 8
			type : 1
			points [
				[754, 1393], [622, 1002], [566, 828], [602, 791], [602, 791]
			]
		}
		{
			route : 9
			type : 1
			points [
				[590, 435], [599, 461], [613, 485], [623, 502], [641, 528], [657, 550],
				[664, 572], [664, 590], [659, 612], [653, 634], [641, 676], [617, 705],
				[611, 725], [614, 748], [612, 794]
			]
		}
		{
			route : 10
			type : 1
			points [
				[906, 343], [836, 346], [773, 380], [747, 417], [716, 469], [704, 485],
				[687, 499], [679, 523], [679, 556], [690, 595], [707, 641], [711, 666],
				[704, 697], [689, 714], [673, 729], [656, 748], [636, 768], [630, 774],
				[620, 785], [611, 788], [606, 788]
			]
		}
		{
			route : 19
			type : 1
			points [
				[557, 510], [532, 508], [512, 505], [493, 514], [490, 531], [492, 559],
				[499, 585], [503, 607], [519, 657], [531, 691], [538, 723], [538, 752],
				[539, 786], [553, 814], [592, 802]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [519, 441], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [420, 649], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [498, 512], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [558, 574], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [615, 707], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [635, 711], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [599, 512], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [616, 733], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [524, 530], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [579, 494], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [873, 841], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [845, 975], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [813, 1204], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [852, 900], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [390, 1050], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [767, 1331], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [715, 1381], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [830, 900], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [840, 960], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [665, 1413], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [605, 422], image : "pharaoh_general/empire_bits_00121" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [417, 466] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [684, 996] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		chain_leaves_wired : false
		event0_heh_fell_done : false
		event1_iken_fell_done : false
		event2_henna_done : false
		event23_kerma_done : false
		inv4_done : false
		inv10_done : false
		inv13_done : false
		inv18_done : false
		inv19_done : false
		inv_loop_done : false
		pending_inv13 : false
		pending_inv4_after_demand : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		start_message_shown : false
	}
}

function mission32_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) { opts.resource = resource }
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) { leaf.set_param("months_initial", months) }
	return leaf
}

function mission32_make_chain_request(tag, resource, amount, months, subtype, city_name) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	}
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	return request
}

function mission32_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) { opts.resource = resource }
	if (city_name !== undefined) { opts.city = city_name }
	if (subtype !== undefined) { opts.subtype = subtype }
	var ev = city.create_chain_event(opts)
	if (ok_tag !== undefined && ok_tag > 0) { ev.set_completed_action_tag(ok_tag) }
	ev.event_is_active = true
	return ev
}

function mission32_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, city_name, defeat_tag) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONCE
	}
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	if (ok_tag !== undefined && ok_tag > 0) { request.set_completed_action_tag(ok_tag) }
	if (refuse_tag !== undefined && refuse_tag > 0) { request.set_refusal_action_tag(refuse_tag) }
	if (late_tag !== undefined && late_tag > 0) { request.set_too_late_action_tag(late_tag) }
	if (defeat_tag !== undefined && defeat_tag > 0) { request.set_defeat_action_tag(defeat_tag) }
	request.event_is_active = true
	return request
}

function mission32_loc_tile(loc, prefer_sea) {
	if (loc == 1) { return [16, 53] }
	if (loc == 2) { return [75, 47] }
	if (prefer_sea && loc == 2) { return [75, 47] }
	return [-1, -1]
}

function mission32_hyksos_raid(invasion_id, size, attack_target, on_completed_tag, loc) {
	var tile = mission32_loc_tile(loc === undefined ? 1 : loc, false)
	log_info("akhenaten: mission 32 hyksos raid id=" + invasion_id + " size=" + size
		+ " loc=" + loc + " tile=" + tile[0] + "," + tile[1])
	__image_request_pak(PACK_ENEMY_HYKSOS)
	var opts = {
		invasion_id: invasion_id,
		enemy: ENEMY_5_HYKSOS,
		size: size,
		tilex: tile[0],
		tiley: tile[1],
		want_destroy_buildings: size,
		invasion_attack_target: attack_target === undefined ? EVENT_ATTACK_TARGET_RANDOM : attack_target
	}
	if (on_completed_tag) { opts.on_completed_tag = on_completed_tag }
	return city.start_foreign_army_invasion(opts)
}

function mission32_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) { return }
	mission.chain_leaves_wired = true

	// pak i=3 demand beer+5 → ok i=4 invasion (JS proxy on demand clear / henna refuse)
	var demand_beer = mission32_make_leaf(1003, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BEER, 5, 2, undefined, "Iken")
	demand_beer.set_completed_action_tag(1004)
	mission32_make_leaf(1004, EVENT_TYPE_INVASION, undefined, 16, 9)
	mission32_make_leaf(1007, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_BEER, 5, 2, undefined, "Kerma")

	var troops = mission32_make_chain_request(1005, RESOURCE_TROOPS, 32, 6, 1, "Itjtawy")
	troops.set_completed_action_tag(1021)
	troops.set_refusal_action_tag(1007)
	troops.set_too_late_action_tag(1007)
	troops.set_defeat_action_tag(1007)

	var gift_papyrus = mission32_make_leaf(1006, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_PAPYRUS, 16, 2, undefined, "Iken")
	gift_papyrus.set_completed_action_tag(1008)

	var henna32 = mission32_make_chain_request(1008, RESOURCE_HENNA, 32, 9, 2, "Iken")
	henna32.set_completed_action_tag(1009)
	henna32.set_refusal_action_tag(1010)
	henna32.set_too_late_action_tag(1011)
	henna32.set_defeat_action_tag(1011)

	var conquered_itjtawy = mission32_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Itjtawy")
	conquered_itjtawy.set_completed_action_tag(1012)

	mission32_make_leaf(1010, EVENT_TYPE_INVASION, undefined, 32, 3)

	var henna16 = mission32_make_chain_request(1011, RESOURCE_HENNA, 16, 6, 2, "Iken")
	henna16.set_completed_action_tag(1009)
	henna16.set_refusal_action_tag(1008)
	henna16.set_too_late_action_tag(1008)
	henna16.set_defeat_action_tag(1008)

	var kerma_trade = mission32_make_leaf(1012, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
	kerma_trade.set_completed_action_tag(1013)
	mission32_make_leaf(1013, EVENT_TYPE_INVASION, undefined, 48, 6)

	var henna48 = mission32_make_chain_request(1014, RESOURCE_HENNA, 48, 12, 2, "Khmun")
	henna48.set_completed_action_tag(1015)
	henna48.set_refusal_action_tag(1016)
	henna48.set_too_late_action_tag(1017)
	henna48.set_defeat_action_tag(1017)

	var conquered_iken = mission32_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Iken")
	conquered_iken.set_completed_action_tag(1016)

	var gift_limestone = mission32_make_leaf(1016, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LIMESTONE, 64, 2, 2, "Khmun")
	gift_limestone.set_completed_action_tag(1017)

	var gift_pottery = mission32_make_leaf(1017, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_POTTERY, 20, 2, undefined, "Men-nefer")
	gift_pottery.set_completed_action_tag(1018)
	mission32_make_leaf(1018, EVENT_TYPE_INVASION, undefined, 29, 6, 2)
	mission32_make_leaf(1019, EVENT_TYPE_INVASION, undefined, 39, 6)

	var message = mission32_make_leaf(1021, EVENT_TYPE_MESSAGE, undefined, 8, 2, undefined, "Itjtawy")
	message.set_completed_action_tag(1006)

	mission32_make_leaf(1022, EVENT_TYPE_INVASION, undefined, 35, 0)
}

[es=event_mission_start, mission=mission32]
function mission32_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_hermopolis")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission32_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission32]
function mission32_requests_and_events(ev) {
	mission32_ensure_chain_leaves()

	if (!mission.event0_heh_fell_done && ev.years_since_start == 1 && ev.month == 0) {
		mission.event0_heh_fell_done = true
		log_info("akhenaten: mission 32 CITY_FELL Heh (i=0 loc=7)")
		mission32_fire_simple_event(2000, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, "Heh",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
	}
	if (!mission.event1_iken_fell_done && ev.years_since_start == 3 && ev.month == 3) {
		mission.event1_iken_fell_done = true
		log_info("akhenaten: mission 32 CITY_FELL Iken (i=1 loc=8)")
		mission32_fire_simple_event(2001, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, "Iken",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
	}
	if (!mission.event2_henna_done && ev.years_since_start == 2 && ev.month == 0) {
		mission.event2_henna_done = true
		log_info("akhenaten: mission 32 henna×16 Men-nefer (i=2)")
		// ok→1003 demand; refuse/late/defeat→1004 invasion (JS proxy in cleared handler)
		mission32_fire_request(2002, RESOURCE_HENNA, 16, 12, 1003, 1004, 1004, 2, "Men-nefer", 1004)
	}
	if (!mission.event23_kerma_done && ev.years_since_start == 5 && ev.month == 0) {
		mission.event23_kerma_done = true
		log_info("akhenaten: mission 32 NEW_TRADE Kerma (i=23; cosmetic route=0)")
		mission32_fire_simple_event(2023, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, "Kerma",
			EVENT_SUBTYPE_NEW_TRADE_ROUTE)
	}

	mission_pharaoh_favour_invasion_tick(mission, 70, 35)
}

[es=event_request_cleared, mission=mission32]
function mission32_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)

	if (ev.tag_id == 2002 && !mission.inv4_done) {
		if (outcome == "ok") {
			log_info("akhenaten: mission 32 henna ok → demand beer (i=2→3); hyksos×16 next day")
			__city_event_fire_chain(1003)
			mission.pending_inv4_after_demand = true
		} else {
			mission.inv4_done = true
			log_info("akhenaten: mission 32 henna refuse/late → hyksos×16 (i=2→4)")
			mission32_hyksos_raid(4, 16, EVENT_ATTACK_TARGET_TROOPS, 1005, 1)
		}
		return
	}
	if (ev.tag_id == 1008 && outcome == "refuse" && !mission.inv10_done) {
		mission.inv10_done = true
		log_info("akhenaten: mission 32 henna×32 refuse → hyksos×32 (i=10)")
		mission32_hyksos_raid(10, 32, EVENT_ATTACK_TARGET_TROOPS, 1008, 2)
		return
	}
	if (ev.tag_id == 1008 && outcome == "ok" && !mission.inv13_done) {
		mission.pending_inv13 = true
		log_info("akhenaten: mission 32 henna×32 ok → Itjtawy/Kerma chain (i=8→9→12), hyksos×48 pending")
		return
	}
	if (ev.tag_id == 1017 && outcome == "ok" && !mission.inv18_done) {
		mission.inv18_done = true
		log_info("akhenaten: mission 32 gift gems ok → hyksos×29 (i=18)")
		mission32_hyksos_raid(18, 29, EVENT_ATTACK_TARGET_RANDOM, 1019, 2)
		return
	}
}

[es=event_update_day, mission=mission32]
function mission32_invasion_followups(ev) {
	if (mission.pending_inv4_after_demand && !mission.inv4_done) {
		mission.pending_inv4_after_demand = false
		mission.inv4_done = true
		log_info("akhenaten: mission 32 hyksos×16 after demand beer (i=3→4)")
		mission32_hyksos_raid(4, 16, EVENT_ATTACK_TARGET_TROOPS, 1005, 1)
	}
	if (mission.pending_inv13 && !mission.inv13_done) {
		mission.inv13_done = true
		mission.pending_inv13 = false
		log_info("akhenaten: mission 32 hyksos×48 after henna chain (i=13)")
		mission32_hyksos_raid(13, 48, EVENT_ATTACK_TARGET_TROOPS, 1014, 2)
	}
	if (mission.inv18_done && !mission.inv19_done && !mission.inv_loop_done) {
		if (city.num_enemy_formations > 0) { return }
		mission.inv19_done = true
		log_info("akhenaten: mission 32 hyksos×39 after wave1 (i=19)")
		mission32_hyksos_raid(19, 39, EVENT_ATTACK_TARGET_RANDOM, 0, 2)
		mission.inv_loop_done = true
	}
}
