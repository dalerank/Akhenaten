log_info("akhenaten: mission 24 waset started")

// Mission 24 — Waset (Thebes), "Civil War". Rank 8 (Chancellor).
//
// Goals:     population 6000, culture 55, prosperity 45, monuments 20, kingdom 70, housing level 10.
// Start:     funds 9000, rescue loan 4000, debt interest 20% (normal difficulty).
// Gods:      Osiris, Ra, Bast.
// Monuments: Sun Temple and small pyramid; burial provisions 16 weapons, 16 pottery, 10 luxury goods.
// Trade:     nothing open at start; can open — Thinis, Dunqul Oasis, Dakhla Oasis, Men-nefer (by sea),
//            Khmun (by sea); opened by events — Kerma (y3m1); display only — Henen-nesw, Kharga Oasis,
//            Nekhen, Sauty.
// Enemies:   no timed raids; small Egyptian raids by sea if an oil request is refused; an Egyptian army
//            (66, then 40, then 40 by sea with 9 warships) if the kingdom rating falls to 0. The scenario
//            enemy is set to Kushite, but no Kushite army is sent.
// Timeline:  every m3 from y2 Nekhen asks for 11 fish (not while the last ask is open); y3m1 Kerma route
//            opens; y4m10 Nekhen demands 884 oil (refused: Egyptian raid 6 by sea with 1 warship
//            announced 4 months later, attacking 2 months after that; delivered: kingdom -6); y7m2 Nekhen asks for 8 troops; y9m1 Sauty asks for 7 copper;
//            y10m4 Sauty demands 238 oil (refused: Egyptian raid 4 by sea with 1 warship announced
//            4 months later, attacking 3 months after that; delivered: kingdom -15); y11m5 failed flood; y12m1 Kharga Oasis asks for 16 weapons; y15m1 Men-nefer
//            asks for 20 troops (refused: Kharga Oasis falls, kingdom -34); every m4 from y19 Men-nefer
//            asks for 20 granite (not while the last ask is open).
//
// Notes for developers:
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later; location 9 = sea point [63,37] with the event's warships.
// - The original's Kerma route event names Kharga Oasis (with Kerma's route number); it is pointed at
//   Kerma, whose goods are filled in because the original leaves them empty.
// - tag_id: 1000 + i chained events, 2000 + i calendar events, 3000 + i*100 + year yearly requests,
//   7000 + i the favour army (i = event index in the original scenario, also quoted as "pak i=" in
//   comments below).

mission24 { // Waset (Thebes) — Civil War
	map_file : "data/maps/m_024_waset.map"

	// Map points from data/maps/m_024_waset.map.
	herd_points_predator [ [94, 93], [32, 107] ]
	fishing_points [ [96, 118], [58, 50] ]

	start_message : "message_mission_thebes"
	selection_title : "Waset"
	player_rank : 8

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

	// pak Normal funds=9000 loan=4000 debt_interest=20 → int_dcy around Normal.
	initial_funds [18000, 12000, 9000, 6000, 4500]
	rescue_loans [8000, 5300, 4000, 2700, 2000]
	debt_interest [10, 15, 20, 25, 30]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/224_mission.mp3"
		victory : "Voice/Mission/224_victory.mp3"
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
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_FIGS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_COPPER_MINE, BUILDING_CLAY_PIT,
		BUILDING_SUN_TEMPLE, BUILDING_SMALL_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// Monuments goal 20 = pak: Sun Temple (4) + small pyramid (4) + burial weapons 16/16, pottery 16/16 (2) → trunc(6.32·√10+0.5)=20.
	win_criteria {
		population    {enabled : true, goal : 6000 }
		culture       {enabled : true, goal : 55 }
		prosperity    {enabled : true, goal : 45 }
		monuments     {enabled : true, goal : 20 }
		kingdom       {enabled : true, goal : 70 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [139, 114]
	exit_point [104, 20]
	river_entry_point [110, 141]
	river_exit_point [47, 38]
	disembark_points [ [77, 73], [74, 86], [86, 125] ]
	invasion_points_land [ [23, 48] ]
	invasion_points_sea [ [63, 37] ]

	// pak burial_provisions (scenario 24 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 16 }
		{ resource: RESOURCE_POTTERY, required: 16 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 10 }
	]

	enable_scenario_events : true

	events [
		{ // pak i=41
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 66, min : 60, max : 90 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7041
			on_completed_action : 1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
		{ // pak i=43
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7043
			on_completed_action : 2
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
		{ // pak i=44
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 40 }
			months_initial : 0
			location_fields [ 9, 9, -1, -1 ]
			warships : 9
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7044
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
	]

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
			{
				name : "Waset"
				idx : 10
				pos : [811, 968]
				route : 0
				type : EMPIRE_CITY_OURS
				sells [ RESOURCE_GRAIN, RESOURCE_FIGS, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			}
	
			{
				name : "Dakhla Oasis"
				idx : 0
				pos : [349, 1037]
				route : 4
				is_open : false
				cost_to_open : 800
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
				buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
				route_limits [
					{ resource: RESOURCE_MEAT, limit: 2500 }
					{ resource: RESOURCE_BRICKS, limit: 2500 }
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				]
			}
	
			{
				name : "Thinis"
				idx : 9
				pos : [687, 871]
				route : 1
				is_open : false
				cost_to_open : 375
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_BEER ]
				buys [ RESOURCE_COPPER ]
				route_limits [
					{ resource: RESOURCE_POTTERY, limit: 1500 }
					{ resource: RESOURCE_BEER, limit: 4000 }
					{ resource: RESOURCE_COPPER, limit: 1500 }
				]
			}
	
			{
				name : "Dunqul Oasis"
				idx : 44
				pos : [795, 1202]
				route : 3
				is_open : false
				cost_to_open : 400
				is_sea_trade : false
				type : EMPIRE_CITY_EGYPTIAN_TRADING
				sells [ RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
				buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
				route_limits [
					{ resource: RESOURCE_CLAY, limit: 2500 }
					{ resource: RESOURCE_POTTERY, limit: 2500 }
					{ resource: RESOURCE_BEER, limit: 2500 }
					{ resource: RESOURCE_GEMS, limit: 2500 }
					{ resource: RESOURCE_TIMBER, limit: 2500 }
					{ resource: RESOURCE_REEDS, limit: 2500 }
					{ resource: RESOURCE_PAPYRUS, limit: 2500 }
					{ resource: RESOURCE_GRANITE, limit: 4000 }
					{ resource: RESOURCE_SANDSTONE, limit: 4000 }
				]
			}
	
			{
				name : "Men-nefer"
				idx : 5
				pos : [545, 487]
				route : 5
				is_open : false
				cost_to_open : 1250
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
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
				name : "Khmun"
				idx : 4
				pos : [577, 758]
				route : 6
				is_open : false
				cost_to_open : 700
				is_sea_trade : true
				type : EMPIRE_CITY_EGYPTIAN_TRADING
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
				name : "Henen-nesw"
				idx : 1
				pos : [529, 635]
				route : 2
				is_sea_trade : true
				trade : false
				type : EMPIRE_CITY_FOREIGN
			}
	
			{
				// Display foreign; unlocked via i=42 NEW_TRADE (pak city=Kharga junk, loc=23=route).
				// Pak sells/buys empty — use standard Kerma goods (luxury/linen) so unlock is playable.
				name : "Kerma"
				idx : 2
				pos : [732, 1491]
				route : 23
				is_open : false
				cost_to_open : 1000
				is_sea_trade : false
				trade : false
				type : EMPIRE_CITY_FOREIGN
				sells [ RESOURCE_LUXURY_GOODS ]
				buys [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS ]
				route_limits [
					{ resource: RESOURCE_LINEN, limit: 2500 }
					{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				]
			}
	
			{
				name : "Kharga Oasis"
				idx : 3
				pos : [627, 1123]
				route : 0
				trade : false
				type : EMPIRE_CITY_FOREIGN
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
				name : "Sauty"
				idx : 8
				pos : [627, 801]
				route : 0
				trade : false
				type : EMPIRE_CITY_EGYPTIAN
			}
		]
	
		hide_pak_routes : true
		empire_routes [
			{
				route : 1
				type : 1
				points [
					[699, 898], [707, 923], [733, 948], [772, 971], [818, 983]
				]
			}
			{
				route : 2
				type : 2
				points [
					[559, 659], [562, 693], [563, 705], [557, 711], [565, 733], [573, 757],
					[593, 790], [611, 812], [640, 818], [652, 831], [653, 843], [678, 853],
					[679, 865], [704, 880], [712, 882], [719, 897], [744, 916], [756, 914],
					[759, 923], [775, 936], [786, 930], [789, 922], [801, 919], [807, 913],
					[811, 907], [821, 914], [825, 929], [825, 944], [815, 957], [818, 977],
					[828, 992]
				]
			}
			{
				route : 3
				type : 1
				points [
					[811, 1207], [836, 1182], [858, 1158], [861, 1143], [868, 1130], [871, 1113],
					[872, 1107], [870, 1096], [865, 1083], [860, 1074], [850, 1061], [845, 1055],
					[837, 1046], [827, 1040], [819, 1035], [810, 1025], [809, 1009], [813, 1000],
					[829, 988]
				]
			}
			{
				route : 4
				type : 1
				points [
					[367, 1053], [372, 1026], [392, 1009], [408, 1004], [423, 999], [432, 998],
					[437, 998], [444, 1001], [455, 1008], [469, 1016], [472, 1025], [480, 1036],
					[492, 1046], [504, 1055], [515, 1062], [534, 1072], [557, 1081], [562, 1083],
					[578, 1090], [588, 1095], [599, 1107], [630, 1133], [632, 1135], [642, 1142],
					[659, 1150], [676, 1157], [712, 1147], [728, 1138], [745, 1126], [752, 1115],
					[760, 1102], [770, 1095], [779, 1079], [800, 1061], [808, 1029], [812, 1021],
					[827, 987]
				]
			}
			{
				route : 5
				type : 2
				points [
					[563, 502], [573, 517], [588, 526], [598, 606], [580, 634], [572, 661],
					[570, 708], [560, 713], [567, 727], [583, 736], [608, 811], [648, 821],
					[662, 848], [679, 856], [742, 916], [759, 916], [773, 932], [812, 907],
					[824, 925], [828, 939], [817, 958], [813, 974], [820, 988]
				]
			}
			{
				route : 6
				type : 2
				points [
					[590, 781], [611, 812], [648, 825], [662, 847], [740, 913], [761, 918],
					[774, 934], [813, 907], [826, 926], [823, 944], [815, 970], [826, 985],
				]
			}
			{
				route : 23
				type : 1
				points [
					[752, 1508], [731, 1486], [727, 1483], [713, 1482], [702, 1474], [700, 1470],
					[695, 1464], [717, 1459], [723, 1447], [730, 1438], [750, 1422], [777, 1399],
					[789, 1376], [796, 1369], [803, 1350], [803, 1345], [811, 1337], [820, 1320],
					[844, 1306], [857, 1313], [863, 1320], [870, 1311], [878, 1301], [887, 1267],
					[898, 1255], [904, 1235], [904, 1224], [900, 1217], [891, 1210], [891, 1203],
					[894, 1197], [894, 1178], [880, 1158], [886, 1137], [879, 1111], [882, 1102],
					[877, 1092], [878, 1079], [878, 1067], [870, 1056], [866, 1049], [862, 1036],
					[852, 1025], [845, 1019], [834, 1014], [822, 992]
				]
			}
		]
	
		hide_pak_objects : true
		empire_ornaments [
			{ pos : [515, 531], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [601, 537], image : "pharaoh_general/empire_bits_00114" }
			{ pos : [571, 598], image : "pharaoh_general/empire_bits_00128" }
			{ pos : [514, 551], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [618, 555], image : "pharaoh_general/empire_bits_00118" }
			{ pos : [717, 912], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [841, 1087], image : "pharaoh_general/empire_bits_00127" }
			{ pos : [817, 890], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [592, 449], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [518, 489], image : "pharaoh_general/empire_bits_00126" }
			{ pos : [771, 1354], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [775, 1194], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [379, 1042], image : "pharaoh_general/empire_bits_00122" }
			{ pos : [484, 518], image : "pharaoh_general/empire_bits_00123" }
			{ pos : [534, 423], image : "pharaoh_general/empire_bits_00124" }
			{ pos : [418, 649], image : "pharaoh_general/empire_bits_00124" }
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
		fish_leaves_wired : false
		oil_i4_leaves_wired : false
		troops_i10_leaves_wired : false
		copper_i14_leaves_wired : false
		oil_i18_leaves_wired : false
		weapons_i25_leaves_wired : false
		troops_i29_leaves_wired : false
		granite_leaves_wired : false

		event4_oil_done : false
		event10_troops_done : false
		event14_copper_done : false
		event18_oil_done : false
		event24_flood_done : false
		event25_weapons_done : false
		event29_troops_done : false
		event42_trade_done : false


		event0_fish_last_year : -1
		event37_granite_last_year : -1
		fish_recurring_was_busy : false
		fish_recurring_idle_since_abs : -1
		granite_recurring_was_busy : false
		granite_recurring_idle_since_abs : -1


		start_message_shown : false
	}
}

function mission24_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission24_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission24_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, city_name) {
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

function mission24_ensure_fish_leaves() {
	// pak i=0 fish recurring: ok→1 KR+9; refuse→2 KR−8; late→3 KR+4.
	if (mission.fish_leaves_wired) {
		return
	}
	mission.fish_leaves_wired = true
	mission24_make_leaf(1001, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 2)
	mission24_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 8, 2)
	mission24_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 4, 2)
}

function mission24_ensure_oil_i4_leaves() {
	// pak i=4 oil×884: ok→5 MESSAGE→6 KR−6; refuse→7 egypt×6; late→8 MESSAGE→9 KR−1.
	if (mission.oil_i4_leaves_wired) {
		return
	}
	mission.oil_i4_leaves_wired = true
	var msg_ok = mission24_make_leaf(1005, EVENT_TYPE_MESSAGE, undefined, 9, 2,
		EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT, "Nekhen")
	mission24_make_leaf(1006, EVENT_TYPE_REPUTATION_DECREASE, undefined, 6, 2)
	var msg_late = mission24_make_leaf(1008, EVENT_TYPE_MESSAGE, undefined, 7, 2,
		EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT, "Nekhen")
	mission24_make_leaf(1009, EVENT_TYPE_REPUTATION_DECREASE, undefined, 1, 2)
	msg_ok.set_completed_action_tag(1006)
	msg_late.set_completed_action_tag(1009)
}

function mission24_ensure_troops_i10_leaves() {
	// pak i=10 troops×8: ok→11 KR+7; refuse→12 KR−7; late→13 KR+4.
	if (mission.troops_i10_leaves_wired) {
		return
	}
	mission.troops_i10_leaves_wired = true
	mission24_make_leaf(1011, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
	mission24_make_leaf(1012, EVENT_TYPE_REPUTATION_DECREASE, undefined, 7, 2)
	mission24_make_leaf(1013, EVENT_TYPE_REPUTATION_INCREASE, undefined, 4, 2)
}

function mission24_ensure_copper_i14_leaves() {
	// pak i=14 copper×7: ok→15 KR+8; refuse→16 KR−9; late→17 KR+2.
	if (mission.copper_i14_leaves_wired) {
		return
	}
	mission.copper_i14_leaves_wired = true
	mission24_make_leaf(1015, EVENT_TYPE_REPUTATION_INCREASE, undefined, 8, 2)
	mission24_make_leaf(1016, EVENT_TYPE_REPUTATION_DECREASE, undefined, 9, 2)
	mission24_make_leaf(1017, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 2)
}

function mission24_ensure_oil_i18_leaves() {
	// pak i=18 oil×238: ok→19 MESSAGE→20 KR−15; refuse→21 egypt×4; late→22 MESSAGE→23 KR−7.
	if (mission.oil_i18_leaves_wired) {
		return
	}
	mission.oil_i18_leaves_wired = true
	var msg_ok = mission24_make_leaf(1019, EVENT_TYPE_MESSAGE, undefined, 6, 2,
		EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT, "Nekhen")
	mission24_make_leaf(1020, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2)
	var msg_late = mission24_make_leaf(1022, EVENT_TYPE_MESSAGE, undefined, 7, 2,
		EVENT_SUBTYPE_MSG_ACKNOWLEDGEMENT, "Nekhen")
	mission24_make_leaf(1023, EVENT_TYPE_REPUTATION_DECREASE, undefined, 7, 2)
	msg_ok.set_completed_action_tag(1020)
	msg_late.set_completed_action_tag(1023)
}

function mission24_ensure_weapons_i25_leaves() {
	// pak i=25 weapons×16: ok→26 KR+15; refuse→27 KR−15; late→28 KR+9.
	if (mission.weapons_i25_leaves_wired) {
		return
	}
	mission.weapons_i25_leaves_wired = true
	mission24_make_leaf(1026, EVENT_TYPE_REPUTATION_INCREASE, undefined, 15, 2)
	mission24_make_leaf(1027, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2)
	mission24_make_leaf(1028, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 2)
}

function mission24_ensure_troops_i29_leaves() {
	// pak i=29 troops×20 (city=Men-nefer): ok→30 MESSAGE city=Kharga→31 KR+25;
	// refuse→32 MESSAGE city=Khmun→33 CITY_FELL Kharga→34 KR−34;
	// late→35 MESSAGE city=Nekhen→36 KR+16.
	if (mission.troops_i29_leaves_wired) {
		return
	}
	mission.troops_i29_leaves_wired = true
	var msg_ok = mission24_make_leaf(1030, EVENT_TYPE_MESSAGE, undefined, 5, 2,
		EVENT_SUBTYPE_MSG_CITY_SAVED, "Kharga Oasis")
	mission24_make_leaf(1031, EVENT_TYPE_REPUTATION_INCREASE, undefined, 25, 2)
	var msg_refuse = mission24_make_leaf(1032, EVENT_TYPE_MESSAGE, undefined, 5, 2,
		EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, "Khmun")
	var fell = mission24_make_leaf(1033, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 6, 2,
		EVENT_SUBTYPE_CITY_FELL_TO_ENEMY, "Kharga Oasis")
	mission24_make_leaf(1034, EVENT_TYPE_REPUTATION_DECREASE, undefined, 34, 2)
	var msg_late = mission24_make_leaf(1035, EVENT_TYPE_MESSAGE, undefined, 5, 2,
		EVENT_SUBTYPE_MSG_CITY_SAVED, "Nekhen")
	mission24_make_leaf(1036, EVENT_TYPE_REPUTATION_INCREASE, undefined, 16, 2)
	msg_ok.set_completed_action_tag(1031)
	msg_refuse.set_completed_action_tag(1033)
	fell.set_completed_action_tag(1034)
	msg_late.set_completed_action_tag(1036)
}

function mission24_ensure_granite_leaves() {
	// pak i=37 granite recurring: ok→38 KR+16; refuse→39 KR−11; late→40 KR+7.
	if (mission.granite_leaves_wired) {
		return
	}
	mission.granite_leaves_wired = true
	mission24_make_leaf(1038, EVENT_TYPE_REPUTATION_INCREASE, undefined, 16, 2)
	mission24_make_leaf(1039, EVENT_TYPE_REPUTATION_DECREASE, undefined, 11, 2)
	mission24_make_leaf(1040, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
}

[es=event_mission_start, mission=mission24]
function mission24_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_SUN_TEMPLE_1)
	__image_request_pak(PACK_SUN_TEMPLE_2)
	__image_request_pak(PACK_SUN_TEMPLE_3)
	__image_request_pak(PACK_SUN_TEMPLE_EXTRA)
	mission_show_start_message(mission, "message_mission_thebes")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission24_ensure_fish_leaves()
	mission24_ensure_oil_i4_leaves()
	mission24_ensure_troops_i10_leaves()
	mission24_ensure_copper_i14_leaves()
	mission24_ensure_oil_i18_leaves()
	mission24_ensure_weapons_i25_leaves()
	mission24_ensure_troops_i29_leaves()
	mission24_ensure_granite_leaves()
}

[es=event_advance_month, mission=mission24]
function mission24_requests_and_events(ev) {
	mission24_ensure_fish_leaves()
	mission24_ensure_oil_i4_leaves()
	mission24_ensure_troops_i10_leaves()
	mission24_ensure_copper_i14_leaves()
	mission24_ensure_oil_i18_leaves()
	mission24_ensure_weapons_i25_leaves()
	mission24_ensure_troops_i29_leaves()
	mission24_ensure_granite_leaves()

	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_FISH, "fish_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GRANITE, "granite_recurring", abs)

	// pak i=0: fish×11 /12mo recurring y2m3+ subtype=5 city=Nekhen.
	if (ev.years_since_start > 2 || (ev.years_since_start == 2 && ev.month >= 3)) {
		if (ev.month == 3 && mission.event0_fish_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_FISH, "fish_recurring", abs)) {
			mission.event0_fish_last_year = ev.years_since_start
			log_info("akhenaten: mission 24 fish×11 recurring (i=0)")
			mission24_fire_request(3000 + 0 * 100 + ev.years_since_start,
				RESOURCE_FISH, 11, 12, 1001, 1002, 1003, 5, 0, "Nekhen")
		}
	}

	// pak i=37: granite×20 /24mo recurring y19m4+ city=Men-nefer.
	if (ev.years_since_start > 19 || (ev.years_since_start == 19 && ev.month >= 4)) {
		if (ev.month == 4 && mission.event37_granite_last_year != ev.years_since_start
				&& mission_recurring_request_may_fire(mission, RESOURCE_GRANITE, "granite_recurring", abs)) {
			mission.event37_granite_last_year = ev.years_since_start
			log_info("akhenaten: mission 24 granite×20 recurring (i=37)")
			mission24_fire_request(3000 + 37 * 100 + ev.years_since_start,
				RESOURCE_GRANITE, 20, 24, 1038, 1039, 1040, 0, 0, "Men-nefer")
		}
	}

	// Once requests / calendar events.
	if (!mission.event4_oil_done && ev.years_since_start == 4 && ev.month == 10) {
		mission.event4_oil_done = true
		log_info("akhenaten: mission 24 oil×884 extortion (i=4)")
		// refuse→egypt×6 via event_request_cleared (JS chain); no leaf 1007.
		mission24_fire_request(2004, RESOURCE_OIL, 884, 18, 1005, 0, 1008, 6, 0, "Nekhen")
	}
	if (!mission.event10_troops_done && ev.years_since_start == 7 && ev.month == 2) {
		mission.event10_troops_done = true
		log_info("akhenaten: mission 24 troops×8 (i=10)")
		mission24_fire_request(2010, RESOURCE_TROOPS, 8, 12, 1011, 1012, 1013, 1, 0, "Nekhen")
	}
	if (!mission.event14_copper_done && ev.years_since_start == 9 && ev.month == 1) {
		mission.event14_copper_done = true
		log_info("akhenaten: mission 24 copper×7 (i=14)")
		mission24_fire_request(2014, RESOURCE_COPPER, 7, 18, 1015, 1016, 1017, 0, 0, "Sauty")
	}
	if (!mission.event18_oil_done && ev.years_since_start == 10 && ev.month == 4) {
		mission.event18_oil_done = true
		log_info("akhenaten: mission 24 oil×238 extortion (i=18)")
		// refuse→egypt×4 via event_request_cleared (JS chain); no leaf 1021.
		mission24_fire_request(2018, RESOURCE_OIL, 238, 18, 1019, 0, 1022, 6, 0, "Sauty")
	}
	if (!mission.event24_flood_done && ev.years_since_start == 11 && ev.month == 5) {
		mission.event24_flood_done = true
		log_info("akhenaten: mission 24 failed flood (i=24)")
		mission24_fire_simple_event(2024, EVENT_TYPE_FAILED_FLOOD, undefined, 8)
	}
	if (!mission.event25_weapons_done && ev.years_since_start == 12 && ev.month == 1) {
		mission.event25_weapons_done = true
		log_info("akhenaten: mission 24 weapons×16 (i=25)")
		mission24_fire_request(2025, RESOURCE_WEAPONS, 16, 24, 1026, 1027, 1028, 0, 0, "Kharga Oasis")
	}
	if (!mission.event29_troops_done && ev.years_since_start == 15 && ev.month == 1) {
		mission.event29_troops_done = true
		log_info("akhenaten: mission 24 troops×20 (i=29)")
		mission24_fire_request(2029, RESOURCE_TROOPS, 20, 24, 1030, 1032, 1035, 1, 0, "Men-nefer")
	}
}

// pak i=42: CITY_STATUS subtype=2 y3m1 city=4 Kharga + loc=23 → NEW_TRADE Kerma (route 23).
[es=event_advance_month, mission=mission24]
function mission24_event_i42_new_trade_kerma(ev) {
	if (mission.event42_trade_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 1)) {
		return
	}
	mission.event42_trade_done = true
	log_info("akhenaten: mission 24 NEW_TRADE Kerma (i=42 remap Kharga+loc23)", {ev:ev})
	city.create_chain_event({
		tag_id: 2042,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		amount: 7,
		subtype: EVENT_SUBTYPE_NEW_TRADE_ROUTE,
		city: "Kerma",
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=7 / i=21: Egyptian raids after the oil requests i=4 / i=18 are refused, due 4 months on (time.year).
function mission24_raid_list() {
	var G = ENEMY_3_EGYPTIAN
	var E = EVENT_INVADER_EGYPT
	return [
		{ key: "i7", invasion_id: 7, invader: E, enemy: G, amount: 6, months_initial: 2, location: [9, 9, -1, -1],
			warships: 1, attack_target: EVENT_ATTACK_TARGET_VAULTS },
		{ key: "i21", invasion_id: 21, invader: E, enemy: G, amount: 4, months_initial: 3, location: [9, 9, -1, -1],
			warships: 1, attack_target: EVENT_ATTACK_TARGET_VAULTS }
	]
}

[es=event_advance_month, mission=mission24]
function mission24_raids(ev) {
	mission_raids_month(mission, mission24, ev, mission24_raid_list())
}

[es=event_request_cleared, mission=mission24]
function mission24_on_request_cleared(ev) {
	if (mission_request_outcome(ev) != "refuse") {
		return
	}
	if (ev.tag_id == 2004) {
		mission_raid_schedule(mission, mission24_raid_list(), "i7", 4)
	} else if (ev.tag_id == 2018) {
		mission_raid_schedule(mission, mission24_raid_list(), "i21", 4)
	}
}
