log_info("akhenaten: mission 23 thinis civil-war started")

// Mission 23 — Thinis, "Civil War". Rank 9 (Vizier).
//
// Goals:     population 4500, culture 25, prosperity 35, kingdom 90, housing count 10, housing level 10.
// Start:     funds 13350, rescue loan 4200, debt interest 20% (normal difficulty).
// Gods:      Osiris, Ra, Ptah.
// Monuments: none. The Temple Complex of Osiris and the family mansion stand on the map and must be
//            protected: they are not in the buildings list, so they cannot be rebuilt (losing them does
//            not fail the mission). The altar and oracle stay buildable to upgrade the complex.
// Trade:     nothing open at start; can open — Waset, Dunqul Oasis, Nekhen, Sauty, Khmun, Men-nefer
//            (by sea), Henen-nesw (by sea); display only — Kharga Oasis, Dakhla Oasis, Kerma, Jericho.
//            Several routes are closed and reopened by the oil request (see the timeline).
// Enemies:   Egyptian loyalist raids and Kushite raids, by land and by sea; an Egyptian army (50, then
//            50) if the kingdom rating falls to 0.
// Timeline:  raids are announced months_initial months before they attack. y1m7 request 120 henna within
//            2 months (whatever the outcome, Henen-nesw falls and loses its route); y2m1 gift of 10 copper;
//            y2m4 gift of 8 beer; y3m0 Sauty falls; y3m7 more pottery demand; y5m0 Kushite raid 21
//            (attacks y5m5, and again every time its army is gone); y5m1 request 10 game meat (refused or
//            late: a gift of 16 copper follows); y6m0 request 142 oil within 2 months (refused: kingdom +7,
//            Henen-nesw, Sauty and Khmun lose their routes, then Egyptian raid 38 a month later, attacking
//            4 months after that; delivered or late: kingdom -10, Waset, Men-nefer and Dunqul Oasis lose
//            their routes, then a request for 23 pottery, repeated until delivered, which reopens them and
//            brings the Egyptian raid 38; as that raid attacks: kingdom +10 and a request for 39 pottery);
//            y7m0 Kushite raid 24 by sea with 1 warship (attacks y7m10, kingdom +5); y10m3 Khmun is
//            besieged and asks for 48 troops (sent: Men-nefer route opens, then Kushite raid 29 by sea with
//            2 warships and as it attacks Egyptian raid 33 by sea with 4 warships; refused: kingdom -20,
//            Egyptian raid 72 by sea with 4 warships, which brings a request for 30 copper as it attacks —
//            delivered: another raid 72, refused: raids 29 and 33, late: raid 33; late or lost: kingdom
//            -10 and the ask repeats); y14m4 request 60 henna within 3 months (delivered: Egyptian raid 32
//            by land, then Kushite raid 48 by sea with 3 warships, then the yearly troops asks start early;
//            refused: kingdom -25, Egyptian raid 72 by sea with 5 warships, then Kushite raid 48 by sea with
//            3 warships; late: kingdom -12 and the yearly troops asks start early); every January from y17
//            a request for 48 troops (not while the last one is open).
//
// Notes for developers:
// - Briefing key is message_mission_thinis; not thinis_2 and not mission 1's gold_and_crime.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, each chained raid due its time.year months after its parent
//   attacks or its request clears; locations 1 / 2 = land points [10,22] / [54,212], 9+ = sea point
//   (number - 9; 13 wraps round to sea point 0) with the event's warships.
// - tag_id: 1000 + i chained events and requests, 2000 + i calendar events, 3000 + i*100 + year yearly
//   troops asks, 204200 + n copper requests, 7000 + i the favour army (i = event index in the original
//   scenario, also quoted as "pak i=" in comments below).

mission23 { // Thinis — Civil War FIP; != mission1 Dawn
	map_file : "data/maps/m_023_thinis.map"

	// Map points from data/maps/m_023_thinis.map.
	herd_points_prey [ [162, 169], [198, 96] ]

	start_message : "message_mission_thinis"
	selection_title : "Thinis"
	player_rank : 9
	reset_personal_savings : true

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 52]
	choice [
		{
			name : "Kebet"
			id : 25
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 53]
			pos [620, 420]
		}
		{
			name : "Menat Khufu"
			id : 26
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 54]
			pos [640, 480]
		}
	]

	// pak Normal funds=13350 loan=4200 debt_interest=20 → int_dcy around Normal.
	initial_funds [26700, 17800, 13350, 8900, 7080]
	rescue_loans [8400, 5600, 4200, 2800, 2200]
	debt_interest [10, 15, 20, 25, 30]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/223_mission.mp3"
		victory : "Voice/Mission/223_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_MORTUARY, BUILDING_DENTIST,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE,
		// no mansions — family mansion is map-only / non-rebuildable (protect)
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT,
		BUILDING_CLAY_PIT, BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_GOLD_MINE,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM,
		BUILDING_FISHING_WHARF, BUILDING_CATTLE_RANCH, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS,
		// no BUILDING_TEMPLE_COMPLEX_OSIRIS — map-only / non-rebuildable (protect)
		BUILDING_TEMPLE_COMPLEX_ALTAR_AMON, BUILDING_TEMPLE_COMPLEX_ORACLE_THOTH,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
	]

	// pak monuments=0. Housing count+level both enabled.
	win_criteria {
		population    {enabled : true, goal : 4500 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 35 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 90 }
		housing_count {enabled : true, goal : 10 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [204, 131]
	exit_point [8, 105]
	river_entry_point [211, 124]
	river_exit_point [23, 90]
	disembark_points [ [30, 102], [71, 71], [177, 108] ]
	invasion_points_land [ [10, 22], [54, 212] ]
	invasion_points_sea [ [103, 91], [59, 123] ]

	enable_scenario_events : true

	events [
		{ // pak i=62
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 50 }
			months_initial : 9
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7062
			on_completed_action : 1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
		{ // pak i=63
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 50 }
			months_initial : 0
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7063
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
	]

	hide_pak_cities : true
	cities [
		{
			name : "Thinis"
			idx : 11
			pos : [687, 871]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_STONE ]
			buys [ RESOURCE_COPPER ]
		}

		{
			name : "Waset"
			idx : 12
			pos : [811, 968]
			route : 1
			is_open : false
			cost_to_open : 240
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 7
			pos : [545, 487]
			route : 2
			is_open : false
			cost_to_open : 840
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Dunqul Oasis"
			idx : 1
			pos : [795, 1191]
			route : 3
			is_open : false
			cost_to_open : 475
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GAMEMEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Henen-nesw"
			idx : 2
			pos : [534, 626]
			route : 4
			is_open : false
			cost_to_open : 580
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_FIGS, RESOURCE_CLAY, RESOURCE_BEER, RESOURCE_FLAX ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
			]
		}

		{
			name : "Nekhen"
			idx : 9
			pos : [792, 1018]
			route : 5
			is_open : false
			cost_to_open : 280
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
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
			name : "Sauty"
			idx : 10
			pos : [627, 801]
			route : 8
			is_open : false
			cost_to_open : 140
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_POMEGRANATES ]
			buys [ RESOURCE_CHICKPEAS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
			]
		}

		{
			name : "Khmun"
			idx : 6
			pos : [577, 758]
			route : 9
			is_open : false
			cost_to_open : 180
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_LINEN, RESOURCE_STONE ]
			buys [ RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
			]
		}

		{
			name : "Kharga Oasis"
			idx : 5
			pos : [628, 1116]
			route : 6
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Dakhla Oasis"
			idx : 0
			pos : [349, 1037]
			route : 7
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 4
			pos : [732, 1491]
			route : 10
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Jericho"
			idx : 3
			pos : [896, 233]
			route : 11
			is_sea_trade : true
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
				[804, 961], [779, 947], [769, 945], [754, 935], [744, 929], [730, 924],
				[721, 919], [708, 898], [710, 890]
			]
		}
		{
			route : 2
			type : 2
			points [
				[568, 508], [584, 523], [587, 532], [589, 543], [593, 556], [590, 559],
				[592, 578], [594, 589], [601, 595], [601, 611], [586, 630], [584, 645],
				[572, 669], [570, 682], [570, 709], [565, 718], [573, 731], [584, 738],
				[587, 754], [595, 795], [613, 813], [624, 814], [655, 835], [656, 842],
				[676, 853], [678, 863], [710, 889]
			]
		}
		{
			route : 3
			type : 1
			points [
				[817, 1206], [839, 1197], [855, 1188], [866, 1178], [874, 1164], [877, 1142],
				[870, 1119], [870, 1108], [874, 1102], [869, 1094], [868, 1086], [870, 1070],
				[866, 1062], [860, 1056], [854, 1050], [855, 1040], [849, 1031], [846, 1026],
				[844, 1016], [828, 1002], [809, 966], [796, 958], [778, 947], [769, 946],
				[750, 932], [734, 926], [726, 924], [722, 919], [707, 897], [708, 891],
			]
		}
		{
			route : 4
			type : 2
			points [
				[554, 645], [562, 661], [558, 671], [558, 685], [559, 696], [561, 705],
				[556, 716], [559, 725], [567, 734], [573, 753], [583, 772], [591, 783],
				[596, 796], [607, 807], [623, 813], [642, 819], [656, 845], [670, 852],
				[682, 864], [688, 885], [708, 892]
			]
		}
		{
			route : 5
			type : 1
			points [
				[810, 1036], [803, 1004], [801, 976], [794, 957], [781, 948], [770, 946],
				[745, 930], [726, 925], [717, 913], [704, 896]
			]
		}
		{
			route : 6
			type : 1
			points [
				[128, 844], [127, 920]
			]
		}
		{
			route : 7
			type : 1
			points [
				[153, 846], [152, 916], [152, 916]
			]
		}
		{
			route : 8
			type : 1
			points [
				[645, 820], [659, 836], [665, 842], [675, 847], [677, 857], [688, 870],
				[704, 884], [711, 894]
			]
		}
		{
			route : 9
			type : 1
			points [
				[603, 780], [620, 798], [626, 814], [639, 824], [654, 834], [657, 844],
				[674, 853], [683, 864], [700, 881], [711, 894]
			]
		}
		{
			route : 10
			type : 1
			points [
				[865, 1357], [868, 1323], [869, 1306], [877, 1289], [881, 1275], [894, 1248],
				[897, 1235], [899, 1223], [885, 1212], [885, 1203], [889, 1196], [888, 1181],
				[879, 1165], [873, 1158], [877, 1141], [871, 1117], [870, 1108], [874, 1102],
				[868, 1088], [868, 1068], [861, 1057], [844, 1047], [810, 1037]
			]
		}
		{
			route : 11
			type : 2
			points [
				[893, 1351], [872, 1307], [882, 1275], [895, 1246], [899, 1224], [885, 1213],
				[887, 1203], [890, 1194], [877, 1162], [878, 1137], [872, 1109], [874, 1106],
				[875, 1103], [870, 1093], [870, 1068], [855, 1042], [845, 1027], [832, 1003],
				[826, 984]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [534, 423], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [414, 645], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [483, 512], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [777, 1338], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [519, 489], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [596, 441], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [825, 889], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [723, 912], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 1086], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [507, 553], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [571, 595], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [514, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [597, 531], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [777, 1198], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [381, 1037], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [621, 546], image : "pharaoh_general/empire_bits_00118" }
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
		raids : ""
		gift_copper_done : false
		gift_beer_done : false
		gamemeat_done : false
		oil_done : false
		henna120_done : false
		siege_khmun_done : false
		henna60_done : false
		city_fell_y3_done : false
		demand_pottery_done : false
		shared_leaves_wired : false
		troops_leaves_wired : false
		henna60_leaves_wired : false
		copper_seq : 0
		troops_recurring_unlocked : false
	}
}

function mission23_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission23_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission23_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag) {
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
	if (defeat_tag) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.execute()
	return request
}

function mission23_fire_copper30() {
	mission.copper_seq = mission.copper_seq + 1
	var tag = 2042 * 100 + mission.copper_seq
	log_info("akhenaten: mission 23 copper x30", { tag: tag })
	mission23_fire_request(tag, RESOURCE_COPPER, 30, 4, 0, 0, 0, 6, 0)
}

// pak i=49 / i=54 → i=55: unlock recurring troops×48 (also calendar y17).
function mission23_unlock_troops_recurring() {
	if (mission.troops_recurring_unlocked) {
		return
	}
	mission.troops_recurring_unlocked = true
	log_info("akhenaten: mission 23 troops recurring unlocked (henna×60 chain)")
}

function mission23_ensure_shared_leaves() {
	if (mission.shared_leaves_wired) {
		return
	}
	mission.shared_leaves_wired = true
	mission23_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2)
	var kr5 = mission23_make_leaf(1004, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	var kr2 = mission23_make_leaf(1005, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 6)
	mission23_make_leaf(1006, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 16, 2)
	kr5.set_completed_action_tag(1006)
	kr2.set_completed_action_tag(1006)

	var kr10_oil = mission23_make_leaf(1026, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	var kr7 = mission23_make_leaf(1025, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 4)

	// pak oil i=7 refuse → i=25 KR+7 → LOST×3 (loc route 4/8/9) → egypt×38 (JS chain).
	var lost_r1 = mission23_make_leaf(1008, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Henen-nesw")
	var lost_r2 = mission23_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 9, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Sauty")
	var lost_r3 = mission23_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Khmun")

	// pak oil ok/late → i=26 KR−10 → LOST×3 (loc route 1/2/3) → pottery×23.
	var lost_o1 = mission23_make_leaf(1011, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 37, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Waset")
	var lost_o2 = mission23_make_leaf(1012, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 35, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Men-nefer")
	var lost_o3 = mission23_make_leaf(1013, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 21, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Dunqul Oasis")

	// pottery ok → NEW_TRADE×3 → arm egypt×38 (pak i=17 → i=19).
	var new1 = mission23_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 24, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Waset")
	var new2 = mission23_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 20, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	var new3 = mission23_make_leaf(1017, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 23, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Dunqul Oasis")

	// pak i=19 attachment: chain-only arm leaf (no-op status); JS spawns egypt next month tick.
	mission23_make_leaf(1019, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 1, 1, 99)

	var kr10_pot = mission23_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	var kr5_pot = mission23_make_leaf(1064, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)

	// Create requests before wiring tags (set_*_action_tag looks up slave by tag).
	var pottery23 = city.create_good_request({
		tag_id: 1014, resource: RESOURCE_POTTERY, amount: 23, months_initial: 10,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	pottery23.set_sender_faction(0)

	// pak i=30–33: pottery×39 after egypt×38 wipe (i=27 KR+10). SKIP orphan i=29 (no inbound).
	var kr10_wipe = mission23_make_leaf(1027, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 4)
	mission23_make_leaf(1031, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)
	mission23_make_leaf(1032, EVENT_TYPE_REPUTATION_DECREASE, undefined, 21, 4)
	mission23_make_leaf(1033, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 4)
	var pottery39 = city.create_good_request({
		tag_id: 1030, resource: RESOURCE_POTTERY, amount: 39, months_initial: 12,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT
	})
	pottery39.set_sender_faction(0)

	// Wire after all tags exist.
	kr7.set_completed_action_tag(1008)
	lost_r1.set_completed_action_tag(1009)
	lost_r2.set_completed_action_tag(1010)
	lost_r3.set_completed_action_tag(1019) // pak i=10 → i=19 egypt×38
	kr10_oil.set_completed_action_tag(1011)
	lost_o1.set_completed_action_tag(1012)
	lost_o2.set_completed_action_tag(1013)
	lost_o3.set_completed_action_tag(1014)
	pottery23.set_completed_action_tag(1015)
	pottery23.set_refusal_action_tag(1018)
	pottery23.set_too_late_action_tag(1064)
	new1.set_completed_action_tag(1016)
	new2.set_completed_action_tag(1017)
	new3.set_completed_action_tag(1019) // pak i=17 → i=19 egypt×38
	kr10_pot.set_completed_action_tag(1014)
	kr5_pot.set_completed_action_tag(1014)
	kr10_wipe.set_completed_action_tag(1030)
	pottery39.set_completed_action_tag(1031)
	pottery39.set_refusal_action_tag(1032)
	pottery39.set_too_late_action_tag(1033)

	mission23_make_leaf(1028, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)

	var fell = mission23_make_leaf(1022, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 38, 4,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Henen-nesw")
	mission23_make_leaf(1023, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 25, 4,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Henen-nesw")
	fell.set_completed_action_tag(1023)
}

function mission23_ensure_troops_leaves() {
	if (mission.troops_leaves_wired) {
		return
	}
	mission.troops_leaves_wired = true
	mission23_ensure_shared_leaves()

	var troops = city.create_good_request({
		tag_id: 1035, resource: RESOURCE_TROOPS, amount: 48, months_initial: 6,
		subtype: 1, trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Khmun"
	})
	troops.set_sender_faction(0)

	// Create leaves before wiring (set_*_action_tag requires slave to exist).
	var nt = mission23_make_leaf(1036, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 20, 4,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Men-nefer")
	var kr5 = mission23_make_leaf(1037, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 1)
	mission23_make_leaf(1039, EVENT_TYPE_REPUTATION_DECREASE, undefined, 20, 4)
	var kr10t = mission23_make_leaf(1041, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 4)
	mission23_make_leaf(1044, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 4)

	// pak: troops ok → NEW → KR+5; then JS enemy×29 (i=38). refuse → KR−20; then JS egypt×72.
	// late/defeat → KR−10 → re-ask troops. Copper×30 fired after egypt×72 wipe (JS).
	troops.set_completed_action_tag(1036)
	troops.set_refusal_action_tag(1039)
	troops.set_too_late_action_tag(1041)
	troops.set_defeat_action_tag(1041)
	nt.set_completed_action_tag(1037)
	kr10t.set_completed_action_tag(1035)
}

function mission23_ensure_henna60_leaves() {
	if (mission.henna60_leaves_wired) {
		return
	}
	mission.henna60_leaves_wired = true
	// pak i=49 KR+5 (after enemy×48 ok path) → unlock troops via JS after fire.
	mission23_make_leaf(1049, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	// pak i=50 KR−25 (henna refuse); i=53 KR+5 (refuse path end); i=54 KR−12 (late→unlock).
	mission23_make_leaf(1050, EVENT_TYPE_REPUTATION_DECREASE, undefined, 25, 2)
	mission23_make_leaf(1053, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission23_make_leaf(1054, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
	// pak i=56–58 recurring troops outcomes.
	mission23_make_leaf(1056, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission23_make_leaf(1057, EVENT_TYPE_REPUTATION_DECREASE, undefined, 22, 2)
	mission23_make_leaf(1058, EVENT_TYPE_REPUTATION_DECREASE, undefined, 12, 2)
}

[es=event_mission_start, mission=mission23]
function mission23_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_thinis")
	empire.set_id(23)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission23_ensure_shared_leaves()
	mission23_ensure_troops_leaves()
	mission23_ensure_henna60_leaves()
}

[es=event_advance_month, mission=mission23]
function mission23_calendar(ev) {
	mission23_ensure_shared_leaves()
	mission23_ensure_troops_leaves()
	mission23_ensure_henna60_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_TROOPS, "troops_recurring", abs)

	if (!mission.gift_copper_done && ev.years_since_start == 2 && ev.month == 1) {
		mission.gift_copper_done = true
		log_info("akhenaten: mission 23 gift copper x10")
		mission23_fire_simple_event(2000, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 10)
	}
	if (!mission.gift_beer_done && ev.years_since_start == 2 && ev.month == 4) {
		mission.gift_beer_done = true
		log_info("akhenaten: mission 23 gift beer x8")
		mission23_fire_simple_event(2001, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_BEER, 8)
	}
	if (!mission.gamemeat_done && ev.years_since_start == 5 && ev.month == 1) {
		mission.gamemeat_done = true
		log_info("akhenaten: mission 23 gamemeat x10")
		mission23_fire_request(2002, RESOURCE_GAMEMEAT, 10, 10, 1003, 1004, 1005, 5, 0)
	}
	if (!mission.oil_done && ev.years_since_start == 6 && ev.month == 0) {
		mission.oil_done = true
		log_info("akhenaten: mission 23 oil x142")
		mission23_fire_request(2007, RESOURCE_OIL, 142, 2, 1026, 1025, 1026, 6, 0)
	}
	if (!mission.henna120_done && ev.years_since_start == 1 && ev.month == 7) {
		mission.henna120_done = true
		log_info("akhenaten: mission 23 henna x120 tribute")
		mission23_fire_request(2021, RESOURCE_HENNA, 120, 2, 1022, 1022, 1022, 2, 0, 1022)
	}
	if (!mission.siege_khmun_done && ev.years_since_start == 10 && ev.month == 3) {
		mission.siege_khmun_done = true
		log_info("akhenaten: mission 23 siege Khmun -> troops x48")
		var siege = city.create_chain_event({
			tag_id: 2034,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 32,
			subtype: EVENT_SUBTYPE_CITY_UNDER_SIEGE,
			city: "Khmun",
			trigger: EVENT_TRIGGER_ONCE
		})
		siege.set_param("months_initial", 4)
		siege.set_completed_action_tag(1035)
		siege.execute()
	}
	if (!mission.henna60_done && ev.years_since_start == 14 && ev.month == 4) {
		mission.henna60_done = true
		log_info("akhenaten: mission 23 henna x60")
		// ok=0 (JS egypt×32); refuse→KR−25; late/defeat→KR−12 (unlock in cleared / leaf).
		mission23_fire_request(2046, RESOURCE_HENNA, 60, 3, 0, 1050, 1054, 2, 0, 1054)
	}
	if (!mission.city_fell_y3_done && ev.years_since_start == 3 && ev.month == 0) {
		mission.city_fell_y3_done = true
		log_info("akhenaten: mission 23 CITY_FELL Sauty y3")
		mission23_fire_simple_event(2059, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, "Sauty",
			EVENT_SUBTYPE_CITY_FELL_TO_ENEMY)
	}
	if (!mission.demand_pottery_done && ev.years_since_start == 3 && ev.month == 7) {
		mission.demand_pottery_done = true
		log_info("akhenaten: mission 23 demand pottery +6")
		mission23_fire_simple_event(2060, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_POTTERY, 6)
	}

	// pak i=55 troops×48 recurring: calendar y17, or earlier after henna×60 ok/late unlock (i=49/54).
	if ((mission.troops_recurring_unlocked || ev.years_since_start >= 17) && ev.month == 0
			&& mission_recurring_request_may_fire(mission, RESOURCE_TROOPS, "troops_recurring", abs)) {
		log_info("akhenaten: mission 23 recurring troops x48")
		mission23_fire_request(3000 + 55 * 100 + ev.years_since_start, RESOURCE_TROOPS, 48, 6,
			1056, 1057, 1058, 1, 0, 1058)
	}
}

// pak i=20, i=61 (recurring) on the calendar; the others chained from the requests in mission23_on_request_cleared or
// from the raid before them as it attacks.
function mission23_raid_list() {
	var K = ENEMY_6_KUSHITE
	var G = ENEMY_3_EGYPTIAN
	var E = EVENT_INVADER_ENEMY
	var EG = EVENT_INVADER_EGYPT
	return [
		{ key: "i20", invasion_id: 20, year: 7, month: 0, invader: E, enemy: K, amount: 24, months_initial: 10,
			location: [10, 10, -1, -1], warships: 1, attack_target: EVENT_ATTACK_TARGET_RANDOM, chain_tag: 1028 },
		{ key: "i61", invasion_id: 61, year: 5, month: 0, invader: E, enemy: K, amount: 21, months_initial: 5,
			location: [3, -1, 3, 4], attack_target: EVENT_ATTACK_TARGET_RANDOM, recurring: true },
		{ key: "i19", invasion_id: 19, invader: EG, enemy: G, amount: 38, months_initial: 4, location: [1, 1, -1, -1],
			attack_target: EVENT_ATTACK_TARGET_RANDOM, chain_tag: 1027 },
		{ key: "i38", invasion_id: 38, invader: E, enemy: K, amount: 29, months_initial: 4, location: [10, 10, -1, -1],
			warships: 2, attack_target: EVENT_ATTACK_TARGET_RANDOM, then: [{ key: "i43", delay: 1 }] },
		{ key: "i43", invasion_id: 43, invader: EG, enemy: G, amount: 33, months_initial: 4, location: [9, 9, -1, -1],
			warships: 4, attack_target: EVENT_ATTACK_TARGET_RANDOM, chain_tag: 1044 },
		{ key: "i40", invasion_id: 40, invader: EG, enemy: G, amount: 72, months_initial: 2, location: [10, 10, -1, -1],
			warships: 4, attack_target: EVENT_ATTACK_TARGET_RANDOM, on_attack: mission23_fire_copper30 },
		{ key: "i47", invasion_id: 47, invader: EG, enemy: G, amount: 32, months_initial: 1, location: [2, 2, -1, -1],
			attack_target: EVENT_ATTACK_TARGET_RANDOM, then: [{ key: "i48", delay: 1 }] },
		{ key: "i48", invasion_id: 48, invader: E, enemy: K, amount: 48, months_initial: 2, location: [10, 10, -1, -1],
			warships: 3, attack_target: EVENT_ATTACK_TARGET_RANDOM, on_attack: mission23_raid_i48_chain },
		{ key: "i51", invasion_id: 51, invader: EG, enemy: G, amount: 72, months_initial: 2, location: [9, 9, -1, -1],
			warships: 5, attack_target: EVENT_ATTACK_TARGET_RANDOM, then: [{ key: "i52", delay: 1 }] },
		{ key: "i52", invasion_id: 52, invader: E, enemy: K, amount: 48, months_initial: 2, location: [13, 13, -1, -1],
			warships: 3, attack_target: EVENT_ATTACK_TARGET_RANDOM, chain_tag: 1053 }
	]
}

function mission23_raid_i48_chain() {
	__city_event_fire_chain(1049)
	mission23_unlock_troops_recurring()
}

[es=event_advance_month, mission=mission23]
function mission23_raids(ev) {
	mission_raids_month(mission, mission23, ev, mission23_raid_list())
}

[es=event_request_cleared, mission=mission23]
function mission23_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)
	var raids = mission23_raid_list()
	// pak oil i=7 refused, or pottery i=14 delivered: the route cascade ends in i=19.
	if ((ev.tag_id == 2007 && outcome == "refuse") || (ev.tag_id == 1014 && outcome == "ok")) {
		mission_raid_schedule(mission, raids, "i19", 1)
	}
	// pak troops i=35: sent -> i=36 -> i=37 -> i=38; refused -> i=39 -> i=40.
	if (ev.tag_id == 1035 && outcome == "ok") {
		mission_raid_schedule(mission, raids, "i38", 1)
	} else if (ev.tag_id == 1035 && outcome == "refuse") {
		mission_raid_schedule(mission, raids, "i40", 3)
	}
	// pak copper i=42: ok -> i=40, refused -> i=38, late -> i=43.
	if (ev.resource == RESOURCE_COPPER) {
		if (outcome == "ok") {
			mission_raid_schedule(mission, raids, "i40", 3)
		} else if (outcome == "refuse") {
			mission_raid_schedule(mission, raids, "i38", 1)
		} else {
			mission_raid_schedule(mission, raids, "i43", 1)
		}
	}
	// pak henna i=46: ok -> i=47; refused -> i=50 kingdom -25 -> i=51; late -> kingdom -12, troops asks early.
	if (ev.tag_id == 2046) {
		if (outcome == "ok") {
			mission_raid_schedule(mission, raids, "i47", 4)
		} else if (outcome == "refuse") {
			mission_raid_schedule(mission, raids, "i51", 1)
		} else {
			mission23_unlock_troops_recurring()
		}
	}
}
