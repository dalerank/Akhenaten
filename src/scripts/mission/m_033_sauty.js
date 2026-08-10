log_info("akhenaten: mission 33 sauty started")

// Empire id=21. HYKSOS (pak BARBARIAN ignored). Gods Osiris×2, Ra, Seth.
// Funds Normal 9000 / loan 0 / debt 20. Rank 10.
// Win: pop 6500 / culture 70 / prosperity 75 / monuments 40 (3× Medium Mudbrick W=8 → 58) / kingdom 60 / housing 14.
// Burial: pottery 32, linen 16, luxury 16, chariots 8.
// SKIP empty map_obj idx=7. Routes 1–10 copy. loan=0 → rescue_loans all 0.
// Calendar: i=0 FELL remap Heh (dump Pwenet); i=1 FELL remap Iken (dump Itjtawy) → pom chain;
//   i=10 oil×1000 y7m7; i=46 favour egypt×50 → i=47 chain×50.
// Loops 2↔4 / 13↔14 / 24↔25 / 40↔44↔45: one bounce then advance (once flags).
// DEMAND amounts from pak (38/47/17/7/6). i=43 meat DEMAND recurring. ok=996 = END.
// Tag_id: 1000+i leaves; 2000+i roots.

mission33 { // Sauty (Lykopolis) — Egypt Reclaimed
	map_file : "data/maps/m_033_sauty.map"

	// Map points from data/maps/m_033_sauty.map.
	herd_points_predator [ [71, 95], [62, 60], [73, 57], [67, 112] ]

	start_message : "message_mission_lykopolis"
	selection_title : "Sauty"
	player_rank : 10

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
	rescue_loans [0, 0, 0, 0, 0]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/233_mission.mp3"
		victory : "Voice/Mission/233_victory.mp3"
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
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MEDIUM_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	win_criteria {
		population    {enabled : true, goal : 6500 }
		culture       {enabled : true, goal : 70 }
		prosperity    {enabled : true, goal : 75 }
		monuments     {enabled : true, goal : 40 }
		kingdom       {enabled : true, goal : 60 }
		housing_level {enabled : true, goal : 14 }
	}

	entry_point [132, 62]
	exit_point [56, 126]
	river_entry_point [41, 108]
	river_exit_point [35, 103]
	disembark_points [ [-1, -1], [-1, -1], [80, 61] ]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_POTTERY, required: 32 }
		{ resource: RESOURCE_LINEN, required: 16 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 16 }
		{ resource: RESOURCE_CHARIOTS, required: 8 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:21}
	hide_pak_cities : true
	cities [
		{
			name : "Sauty"
			idx : 10
			pos : [627, 801]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_POMEGRANATES, RESOURCE_CLAY, RESOURCE_FLAX, RESOURCE_GEMS, RESOURCE_STONE, RESOURCE_LIMESTONE ]
		}
		{
			name : "Bubastis"
			idx : 0
			pos : [573, 416]
			route : 2
			is_open : false
			cost_to_open : 450
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BEER, RESOURCE_LUXURY_GOODS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Itjtawy"
			idx : 3
			pos : [575, 549]
			route : 1
			is_open : false
			cost_to_open : 425
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_STRAW, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 5
			pos : [545, 487]
			route : 5
			is_open : false
			cost_to_open : 350
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Menat Khufu"
			idx : 6
			pos : [578, 720]
			route : 3
			is_open : false
			cost_to_open : 150
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_STONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}
		{
			name : "Heh"
			idx : 1
			pos : [698, 1414]
			route : 7
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Iken"
			idx : 2
			pos : [735, 1380]
			route : 6
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Kerma"
			idx : 4
			pos : [732, 1491]
			route : 4
			cost_to_open : 1500
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Pwenet"
			idx : 8
			pos : [1133, 1325]
			route : 0
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Rowarty"
			idx : 9
			pos : [612, 389]
			route : 9
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sharuhen"
			idx : 11
			pos : [836, 359]
			route : 10
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Waset"
			idx : 12
			pos : [811, 968]
			route : 8
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	routes [
		{
			route : 1
			type : 2
			points [
				[589, 578], [594, 590], [599, 595], [599, 612], [583, 634], [584, 646],
				[571, 667], [570, 690], [570, 710], [567, 721], [571, 730], [576, 734],
				[581, 737], [587, 749], [585, 758], [591, 771], [596, 778], [598, 782],
				[596, 801], [614, 814], [627, 817], [652, 833]
			]
		}
		{
			route : 2
			type : 2
			points [
				[597, 441], [591, 456], [574, 463], [577, 473], [570, 483], [568, 499],
				[577, 514], [583, 522], [590, 532], [584, 546], [590, 558], [605, 592],
				[609, 611], [590, 639], [590, 652], [578, 668], [578, 693], [575, 714],
				[580, 726], [589, 738]
			]
		}
		{
			route : 3
			type : 1
			points [
				[594, 740], [607, 757], [614, 765], [618, 769], [623, 776], [627, 782],
				[631, 788], [635, 794], [639, 804], [645, 821], [650, 828], [650, 829]
			]
		}
		{
			route : 4
			type : 1
			points [
				[748, 1505], [718, 1491], [686, 1467], [705, 1447], [749, 1399], [776, 1377],
				[827, 1285], [864, 1297], [893, 1230], [871, 1201], [868, 1106], [861, 1061],
				[845, 1033], [821, 1011], [809, 1002], [796, 959], [720, 916], [666, 869],
				[657, 858], [652, 845], [651, 832], [649, 833]
			]
		}
		{
			route : 5
			type : 2
			points [
				[574, 504], [592, 518], [599, 537], [594, 547], [619, 612], [610, 627],
				[598, 642], [596, 649], [589, 666], [584, 680], [584, 701], [587, 717],
				[594, 734], [594, 740]
			]
		}
		{
			route : 6
			type : 1
			points [
				[646, 835], [656, 875], [712, 924], [784, 967], [798, 1012], [834, 1045],
				[847, 1083], [852, 1140], [852, 1172], [841, 1217], [824, 1265], [812, 1284],
				[802, 1305], [749, 1375], [751, 1395], [749, 1391]
			]
		}
		{
			route : 7
			type : 1
			points [
				[650, 831], [642, 844], [644, 876], [689, 925], [773, 975], [784, 1013],
				[827, 1051], [838, 1091], [839, 1170], [828, 1226], [811, 1248], [789, 1277],
				[765, 1324], [709, 1392], [706, 1412], [716, 1434], [715, 1434]
			]
		}
		{
			route : 8
			type : 2
			points [
				[651, 831], [677, 854], [681, 863], [696, 877], [703, 882], [714, 885],
				[721, 888], [722, 897], [729, 905], [738, 912], [746, 919], [760, 916],
				[762, 927], [773, 935], [788, 925], [793, 920], [803, 917], [812, 910],
				[813, 908], [821, 921], [826, 937], [829, 944], [829, 947], [822, 956],
				[817, 964], [820, 979], [822, 984], [823, 988]
			]
		}
		{
			route : 9
			type : 2
			points [
				[650, 831], [611, 820], [591, 799], [592, 778], [575, 741], [563, 719],
				[562, 690], [564, 655], [574, 634], [584, 613], [589, 602], [585, 587],
				[577, 560], [578, 535], [577, 525], [558, 497], [564, 469], [579, 451],
				[605, 414], [644, 411]
			]
		}
		{
			route : 10
			type : 1
			points [
				[648, 830], [740, 631], [688, 558], [680, 522], [685, 501], [707, 491],
				[757, 460], [828, 397], [853, 376]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [534, 435], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [418, 650], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [485, 512], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [565, 576], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [613, 714], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [633, 713], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [607, 423], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [600, 517], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [618, 737], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [578, 500], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [514, 528], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [859, 836], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [666, 1419], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [836, 979], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [868, 909], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [818, 1204], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [392, 1052], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [775, 1334], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [847, 909], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [712, 1381], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [844, 964], image : "pharaoh_general/empire_bits_00115" }
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
		{ name : "#upper_egypt", pos : [682, 1002] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		chain_leaves_wired : false
		event0_heh_fell_done : false
		event1_iken_fell_done : false
		event2_pom_done : false
		event10_oil_done : false
		hub15_done : false
		hub33_done : false
		oil_ladder_loop_done : false
		pom_bounce_done : false
		henna24_bounce_done : false
		henna48_bounce_done : false
		pharaoh_favour_invasion_done : false
		pharaoh_favour_chain_done : false
		pharaoh_favour_enemies_seen : false
		pharaoh_favour_wave_next : -1
		pharaoh_favour_wave_seq : 0
		start_message_shown : false
	}
}

function mission33_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount }
	if (resource !== undefined) { opts.resource = resource }
	if (subtype !== undefined) { opts.subtype = subtype }
	if (city_name !== undefined) { opts.city = city_name }
	var leaf = city.create_chain_event(opts)
	if (months !== undefined) { leaf.set_param("months_initial", months) }
	return leaf
}

function mission33_make_chain_request(tag, resource, amount, months, subtype, city_name) {
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

function mission33_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) { opts.resource = resource }
	if (city_name !== undefined) { opts.city = city_name }
	if (subtype !== undefined) { opts.subtype = subtype }
	var ev = city.create_chain_event(opts)
	if (ok_tag !== undefined && ok_tag > 0) { ev.set_completed_action_tag(ok_tag) }
	ev.event_is_active = true
	return ev
}

function mission33_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, city_name, defeat_tag) {
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

function mission33_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) { return }
	mission.chain_leaves_wired = true

	// Chain A: calendar 2002 pom×16 ok→1004 / refuse→1003; bounce 1004↔1002 once then 1003.
	var pom16b = mission33_make_chain_request(1002, RESOURCE_POMEGRANATES, 16, 6, 3, "Men-nefer")
	pom16b.set_completed_action_tag(1003)
	pom16b.set_refusal_action_tag(1003)
	pom16b.set_too_late_action_tag(1003)
	pom16b.set_defeat_action_tag(1003)

	var trade_mennefer = mission33_make_leaf(1003, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 33, 6,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	trade_mennefer.set_completed_action_tag(1005)

	var pom16c = mission33_make_chain_request(1004, RESOURCE_POMEGRANATES, 16, 6, 3, "Men-nefer")
	pom16c.set_completed_action_tag(1003)
	pom16c.set_refusal_action_tag(1002)
	pom16c.set_too_late_action_tag(1002)
	pom16c.set_defeat_action_tag(1002)

	var pom32 = mission33_make_chain_request(1005, RESOURCE_POMEGRANATES, 32, 12, 5, "Men-nefer")
	pom32.set_completed_action_tag(1006)
	pom32.set_refusal_action_tag(1007)
	pom32.set_too_late_action_tag(1007)
	pom32.set_defeat_action_tag(1007)

	var gift_oil = mission33_make_leaf(1006, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_OIL, 2500, 6, undefined, "Menat Khufu")
	gift_oil.set_completed_action_tag(1008)

	mission33_make_leaf(1007, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 38, 6,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Menat Khufu")

	var demand_linen = mission33_make_leaf(1008, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_LINEN, 38, 6, undefined, "Itjtawy")
	demand_linen.set_completed_action_tag(1009)
	mission33_make_leaf(1009, EVENT_TYPE_PRICE_INCREASE, RESOURCE_LINEN, 30, 6, undefined, "Kerma")

	// Chain B: oil ladder (13↔14 one ok-loop via cleared) → fail hub 1015 → troops/henna
	var oil1000b = mission33_make_chain_request(1011, RESOURCE_OIL, 1000, 6, 6, "Kerma")
	oil1000b.set_completed_action_tag(1012)
	oil1000b.set_refusal_action_tag(1015)
	oil1000b.set_too_late_action_tag(1015)
	oil1000b.set_defeat_action_tag(1015)

	var oil1500 = mission33_make_chain_request(1012, RESOURCE_OIL, 1500, 6, 0, "Kerma")
	oil1500.set_completed_action_tag(1013)
	oil1500.set_refusal_action_tag(1015)
	oil1500.set_too_late_action_tag(1015)
	oil1500.set_defeat_action_tag(1015)

	var oil2000 = mission33_make_chain_request(1013, RESOURCE_OIL, 2000, 3, 6, "Menat Khufu")
	oil2000.set_completed_action_tag(1014)
	oil2000.set_refusal_action_tag(1015)
	oil2000.set_too_late_action_tag(1015)
	oil2000.set_defeat_action_tag(1015)

	// ok→1013 once (cleared); refuse→1015
	var oil2500 = mission33_make_chain_request(1014, RESOURCE_OIL, 2500, 6, 0, "Pwenet")
	oil2500.set_refusal_action_tag(1015)
	oil2500.set_too_late_action_tag(1015)
	oil2500.set_defeat_action_tag(1015)

	var demand_timber = mission33_make_leaf(1015, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_TIMBER, 47, 6, undefined, "Itjtawy")
	demand_timber.set_completed_action_tag(1016)

	var troops32 = mission33_make_chain_request(1016, RESOURCE_TROOPS, 32, 6, 1, "Pwenet")
	troops32.set_completed_action_tag(1033)
	troops32.set_refusal_action_tag(1017)
	troops32.set_too_late_action_tag(1032)
	troops32.set_defeat_action_tag(1032)

	var fell_menat = mission33_make_leaf(1017, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 29, 6,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Menat Khufu")
	fell_menat.set_completed_action_tag(1018)

	var lost_mennefer = mission33_make_leaf(1018, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 16, 6,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Men-nefer")
	lost_mennefer.set_completed_action_tag(1019)

	var demand_bricks_dn = mission33_make_leaf(1019, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_BRICKS, 17, 6, undefined, "Itjtawy")
	demand_bricks_dn.set_completed_action_tag(1020)

	var troops24 = mission33_make_chain_request(1020, RESOURCE_TROOPS, 24, 9, 1, "Menat Khufu")
	troops24.set_completed_action_tag(1029)
	troops24.set_refusal_action_tag(1021)
	troops24.set_too_late_action_tag(1028)
	troops24.set_defeat_action_tag(1028)

	var fell_kerma = mission33_make_leaf(1021, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Kerma")
	fell_kerma.set_completed_action_tag(1022)

	var lost_pwenet = mission33_make_leaf(1022, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Pwenet")
	lost_pwenet.set_completed_action_tag(1023)

	var henna16a = mission33_make_chain_request(1023, RESOURCE_HENNA, 16, 12, 2, "Kerma")
	henna16a.set_completed_action_tag(1026)
	henna16a.set_refusal_action_tag(1024)
	henna16a.set_too_late_action_tag(1024)
	henna16a.set_defeat_action_tag(1024)

	var henna24a = mission33_make_chain_request(1024, RESOURCE_HENNA, 24, 12, 2, "Pwenet")
	henna24a.set_completed_action_tag(1026)
	henna24a.set_refusal_action_tag(1025)
	henna24a.set_too_late_action_tag(1025)
	henna24a.set_defeat_action_tag(1025)

	// i=25: ok→26; refuse→24 once then →26 (cleared gate on return)
	var henna24b = mission33_make_chain_request(1025, RESOURCE_HENNA, 24, 12, 2, "Pwenet")
	henna24b.set_completed_action_tag(1026)
	henna24b.set_refusal_action_tag(1024)
	henna24b.set_too_late_action_tag(1024)
	henna24b.set_defeat_action_tag(1024)

	var conquered_mennefer = mission33_make_leaf(1026, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Men-nefer")
	conquered_mennefer.set_completed_action_tag(1027)

	var trade_pwenet = mission33_make_leaf(1027, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Pwenet")
	trade_pwenet.set_completed_action_tag(1029)

	var henna16late = mission33_make_chain_request(1028, RESOURCE_HENNA, 16, 12, 2, "Kerma")
	henna16late.set_completed_action_tag(1029)
	henna16late.set_refusal_action_tag(1021)
	henna16late.set_too_late_action_tag(1021)
	henna16late.set_defeat_action_tag(1021)

	var demand_bricks_up = mission33_make_leaf(1029, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_BRICKS, 7, 2, undefined, "Kerma")
	demand_bricks_up.set_completed_action_tag(1030)

	var henna32a = mission33_make_chain_request(1030, RESOURCE_HENNA, 32, 12, 2, "Kerma")
	henna32a.set_completed_action_tag(1034)
	henna32a.set_refusal_action_tag(1019)
	henna32a.set_too_late_action_tag(1031)
	henna32a.set_defeat_action_tag(1031)

	var henna16b = mission33_make_chain_request(1031, RESOURCE_HENNA, 16, 6, 2, "Menat Khufu")
	henna16b.set_completed_action_tag(1034)
	henna16b.set_refusal_action_tag(1019)
	henna16b.set_too_late_action_tag(1019)
	henna16b.set_defeat_action_tag(1019)

	var troops20 = mission33_make_chain_request(1032, RESOURCE_TROOPS, 20, 9, 1, "Kerma")
	troops20.set_completed_action_tag(1033)
	troops20.set_refusal_action_tag(1017)
	troops20.set_too_late_action_tag(1017)
	troops20.set_defeat_action_tag(1017)

	var demand_papyrus = mission33_make_leaf(1033, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_PAPYRUS, 5, 2, undefined, "Pwenet")
	demand_papyrus.set_completed_action_tag(1036)

	var conquered_menat = mission33_make_leaf(1034, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Menat Khufu")
	conquered_menat.set_completed_action_tag(1035)

	var trade_kerma = mission33_make_leaf(1035, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
	trade_kerma.set_completed_action_tag(1033)

	var henna32b = mission33_make_chain_request(1036, RESOURCE_HENNA, 32, 12, 2, "Itjtawy")
	henna32b.set_completed_action_tag(1038)
	henna32b.set_too_late_action_tag(1037)
	henna32b.set_defeat_action_tag(1037)

	var henna16c = mission33_make_chain_request(1037, RESOURCE_HENNA, 16, 9, 2, "Men-nefer")
	henna16c.set_completed_action_tag(1038)

	var conquered_mennefer2 = mission33_make_leaf(1038, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Men-nefer")
	conquered_mennefer2.set_completed_action_tag(1039)

	var demand_papyrus2 = mission33_make_leaf(1039, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_PAPYRUS, 6, 2, undefined, "Kerma")
	demand_papyrus2.set_completed_action_tag(1040)

	var henna32c = mission33_make_chain_request(1040, RESOURCE_HENNA, 32, 12, 2, "Men-nefer")
	henna32c.set_completed_action_tag(1042)
	henna32c.set_refusal_action_tag(1044)
	henna32c.set_too_late_action_tag(1041)
	henna32c.set_defeat_action_tag(1041)

	var henna16d = mission33_make_chain_request(1041, RESOURCE_HENNA, 16, 6, 2, "Men-nefer")
	henna16d.set_completed_action_tag(1042)
	henna16d.set_refusal_action_tag(1044)
	henna16d.set_too_late_action_tag(1044)
	henna16d.set_defeat_action_tag(1044)

	var conquered_itjtawy = mission33_make_leaf(1042, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Itjtawy")
	conquered_itjtawy.set_completed_action_tag(1043)

	var meat_rec = city.create_chain_event({
		tag_id: 1043,
		type: EVENT_TYPE_DEMAND_INCREASE,
		resource: RESOURCE_MEAT,
		amount: 5,
		city: "Men-nefer",
		trigger: EVENT_TRIGGER_RECURRING
	})
	meat_rec.set_param("months_initial", 2)

	var henna48a = mission33_make_chain_request(1044, RESOURCE_HENNA, 48, 12, 2, "Menat Khufu")
	henna48a.set_completed_action_tag(1042)
	henna48a.set_refusal_action_tag(1045)
	henna48a.set_too_late_action_tag(1040)
	henna48a.set_defeat_action_tag(1040)

	var henna48b = mission33_make_chain_request(1045, RESOURCE_HENNA, 48, 12, 2, "Menat Khufu")
	henna48b.set_completed_action_tag(1042)
	henna48b.set_refusal_action_tag(1044)
	henna48b.set_too_late_action_tag(1040)
	henna48b.set_defeat_action_tag(1040)
}

[es=event_mission_start, mission=mission33]
function mission33_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_lykopolis")
	empire.set_id(21)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	__scenario_monuments.first = 4
	__scenario_monuments.second = 4
	__scenario_monuments.third = 4
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission33_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission33]
function mission33_requests_and_events(ev) {
	mission33_ensure_chain_leaves()

	if (!mission.event0_heh_fell_done && ev.years_since_start == 1 && ev.month == 0) {
		mission.event0_heh_fell_done = true
		log_info("akhenaten: mission 33 CITY_FELL Heh (i=0 remap; dump Pwenet)")
		mission33_fire_simple_event(2000, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, "Heh",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
	}
	if (!mission.event1_iken_fell_done && ev.years_since_start == 3 && ev.month == 0) {
		mission.event1_iken_fell_done = true
		mission.event2_pom_done = true
		log_info("akhenaten: mission 33 CITY_FELL Iken + pom×16 (i=1→2 remap; dump Itjtawy)")
		mission33_fire_simple_event(2001, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, "Iken",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
		// Dump i=2: ok→4, refuse/late/defeat→3.
		mission33_fire_request(2002, RESOURCE_POMEGRANATES, 16, 6, 1004, 1003, 1003, 3, "Men-nefer", 1003)
	}
	if (!mission.event10_oil_done && ev.years_since_start == 7 && ev.month == 7) {
		mission.event10_oil_done = true
		log_info("akhenaten: mission 33 oil×1000 Men-nefer (i=10)")
		mission33_fire_request(2010, RESOURCE_OIL, 1000, 6, 1011, 1015, 1015, 6, "Men-nefer", 1015)
	}

	mission_pharaoh_favour_invasion_tick(mission, 50, 50)
}

[es=event_request_cleared, mission=mission33]
function mission33_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)

	if (ev.tag_id == 2002) {
		log_info("akhenaten: mission 33 pom×16 " + outcome + " (i=2)")
		return
	}
	if (ev.tag_id == 1004 && outcome != "ok") {
		if (!mission.pom_bounce_done) {
			mission.pom_bounce_done = true
			log_info("akhenaten: mission 33 pom bounce → i=2 leaf (i=4 refuse)")
		} else {
			log_info("akhenaten: mission 33 pom bounce exhausted → force NEW_TRADE")
			__city_event_fire_chain(1003)
		}
		return
	}
	if (ev.tag_id == 1014 && outcome == "ok") {
		if (!mission.oil_ladder_loop_done) {
			mission.oil_ladder_loop_done = true
			log_info("akhenaten: mission 33 oil×2500 ok → one loop to ×2000 (i=14→13)")
			__city_event_fire_chain(1013)
		} else {
			log_info("akhenaten: mission 33 oil ladder loop done (i=14 terminal)")
		}
		return
	}
	if ((ev.tag_id == 2010 || ev.tag_id == 1011 || ev.tag_id == 1012 || ev.tag_id == 1013 || ev.tag_id == 1014)
		&& outcome != "ok" && !mission.hub15_done) {
		mission.hub15_done = true
		log_info("akhenaten: mission 33 oil fail → demand timber hub (i=15)")
		return
	}
	if ((ev.tag_id == 1036 || ev.tag_id == 1037) && outcome != "ok") {
		if (!mission.hub15_done) {
			mission.hub15_done = true
			log_info("akhenaten: mission 33 henna refuse → oil-fail hub (i=36/37→15)")
			__city_event_fire_chain(1015)
		} else {
			log_info("akhenaten: mission 33 henna refuse skip re-enter hub15")
		}
		return
	}
	if (ev.tag_id == 1024 && outcome != "ok" && mission.henna24_bounce_done) {
		log_info("akhenaten: mission 33 henna×24 re-refuse after bounce → CONQUERED")
		__city_event_fire_chain(1026)
		return
	}
	if (ev.tag_id == 1025 && outcome != "ok") {
		mission.henna24_bounce_done = true
		log_info("akhenaten: mission 33 henna×24 bounce (i=25→24)")
		return
	}
	if (ev.tag_id == 1044 && outcome != "ok" && mission.henna48_bounce_done) {
		log_info("akhenaten: mission 33 henna×48 re-refuse after bounce → CONQUERED Itjtawy")
		__city_event_fire_chain(1042)
		return
	}
	if (ev.tag_id == 1045 && outcome != "ok") {
		mission.henna48_bounce_done = true
		log_info("akhenaten: mission 33 henna×48 bounce (i=45→44)")
		return
	}
	if (ev.tag_id == 1033 && !mission.hub33_done) {
		mission.hub33_done = true
		log_info("akhenaten: mission 33 papyrus demand hub (i=33)")
	}
}
