log_info("akhenaten: mission 27 itjtawy started")

// Mission 27 — Itjtawy, "A New Capital is Founded". Rank 10 (Pharaoh).
//
// Goals:     population 7500, culture 60, prosperity 60, monuments 33, kingdom 85,
//            housing: 6 houses of level 17.
// Start:     funds 8000, rescue loan 3000, debt interest 8% (normal difficulty).
// Gods:      Osiris, Ptah, Seth, Bast (patron).
// Monuments: sphinx, medium mudbrick pyramid, small mudbrick pyramid (burial goods: 10 grain,
//            25 pottery, 12 beer, 12 luxury goods, 15 papyrus).
// Trade:     nothing open at start; can open — Buhen (by sea), Byblos, Dakhla Oasis, Men-nefer,
//            Menat Khufu; opened by events — Kerma (7 pottery delivered); display only — Kharga Oasis,
//            Waset, Kebet.
// Enemies:   Egyptian raids only after a refused request; Egyptian army (50, then 50 more) if the
//            kingdom rating falls to 0. The scenario enemy is set to Libyan, but no Libyan army is sent.
// Timeline:  y2m2 request 7 pottery (delivered: Kerma route opens); y2m7 request 9 meat (refused:
//            raid 8 announced 5 months later, attacking 5 months after that, kingdom -10 as it attacks);
//            y2m10 request 2 meat; y5m4 request 13 bricks (refused: raid 9 announced 7 months later,
//            attacking 8 months after that, Menat Khufu route lost as it attacks); y6m4 request
//            6 limestone (delivered: gift from Pharaoh; refused: raid 6 announced 3 months later,
//            attacking 6 months after that, kingdom -7 as it attacks).
//            Yearly from the given year: contaminated water from y4m7, y30m7, y85m7; wage rise from
//            y7m10 and y22m6, wage cut from y13m2 and y35m9; land trade problems from y8m3, y28m4,
//            y45m3, y63m3, y90m3; request 15 linen from y14m2 (only while no linen request is open).
//            Other requests only move the kingdom rating.
//
// Notes for developers:
// - Next mission is a choice between Iken (28) and Sawu (29), so there is no next_mission.
// - The map has no invasion points: raids and the Egyptian army enter at the map exit point. Raids follow
//   the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month, the attack
//   months_initial months later.
// - The original gives Kerma no goods, so its unlock is cosmetic (same as Men-nefer/Khmun in Kebet).
// - Deeper nested request chains of the original are reduced to their kingdom-rating outcomes.
// - tag_id: 1000 + i chained events, 2000 + i one-time calendar events, 3000 + i*100 + year yearly
//   events, 7000 + i Egyptian army (i = event index in the original scenario, "pak i=" below).

mission27 { // Itjtawy - A New Capital is Founded
	map_file : "data/maps/m_027_itjtawy.map"
	start_message : "message_mission_itjtawy"
	selection_title : "Itjtawy"
	player_rank : 10

	// Convergence of Kebet (25) / Menat Khufu (26); next choice Iken (28) / Sawu (29).
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 58]
	choice [
		{
			name : "Iken"
			id : 28
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 59]
			pos [620, 420]
		}
		{
			name : "Sawu"
			id : 29
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 60]
			pos [640, 480]
		}
	]

	// pak Normal funds=8000 loan=3000 debt_interest=8 -> int_dcy around Normal.
	initial_funds [16000, 10600, 8000, 5400, 4200]
	rescue_loans [6000, 4000, 3000, 2000, 1500]
	debt_interest [4, 6, 8, 10, 12]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/227_mission.mp3"
		victory : "Voice/Mission/227_victory.mp3"
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
		BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_CATTLE_RANCH, BUILDING_REED_GATHERER,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_CLAY_PIT,
		BUILDING_SPHINX, BUILDING_SMALL_MUDBRICK_PYRAMID, BUILDING_MEDIUM_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH, BUILDING_TEMPLE_COMPLEX_BAST,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	// Monuments 33 = Sphinx (10) + Medium mudbrick (12) + Small mudbrick (4) + burial pottery 25/16 (1).
	win_criteria {
		population    {enabled : true, goal : 7500 }
		culture       {enabled : true, goal : 60 }
		prosperity    {enabled : true, goal : 60 }
		monuments     {enabled : true, goal : 33 }
		kingdom       {enabled : true, goal : 85 }
		housing_count {enabled : true, goal : 6 }
		housing_level {enabled : true, goal : 17 }
	}

	entry_point [125, 212]
	exit_point [23, 90]
	river_entry_point [164, 173]
	river_exit_point [49, 64]
	disembark_points [ [-1, -1], [-1, -1], [90, 99] ]

	// pak burial_provisions (scenario 27 dump).
	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_GRAIN, required: 10 }
		{ resource: RESOURCE_POTTERY, required: 25 }
		{ resource: RESOURCE_BEER, required: 12 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 12 }
		{ resource: RESOURCE_PAPYRUS, required: 15 }
	]

	enable_scenario_events : true

	events [
		{ // pak i=118
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 50 }
			months_initial : 6
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7118
			on_completed_action : 1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
		{ // pak i=119
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 50 }
			months_initial : 0
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7119
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
			name : "Itjtawy"
			idx : 3
			pos : [568, 557]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_LETTUCE, RESOURCE_POMEGRANATES, RESOURCE_CLAY, RESOURCE_FLAX, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER ]
		}

		{
			name : "Buhen"
			idx : 0
			pos : [766, 1345]
			route : 7
			is_open : false
			cost_to_open : 850
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_BARLEY, RESOURCE_BEER ]
			buys [ RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 2
			is_open : false
			cost_to_open : 900
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 4000 }
				{ resource: RESOURCE_TIMBER, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Dakhla Oasis"
			idx : 2
			pos : [349, 1037]
			route : 9
			is_open : false
			cost_to_open : 1250
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
			buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 6
			pos : [545, 487]
			route : 6
			is_open : false
			cost_to_open : 300
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_POMEGRANATES, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
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
			name : "Menat Khufu"
			idx : 7
			pos : [578, 720]
			route : 4
			is_open : false
			cost_to_open : 350
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_STONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
			]
		}

		{
			// Display foreign sea city; unlocked for trade by i=48->57 NEW_TRADE (pak sells/buys
			// empty - matches the pattern used for Men-nefer/Khmun in Kebet: cosmetic unlock only).
			name : "Kerma"
			idx : 4
			pos : [732, 1491]
			route : 5
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kharga Oasis"
			idx : 5
			pos : [642, 1136]
			route : 11
			cost_to_open : 680
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Waset"
			idx : 9
			pos : [811, 968]
			route : 1
			cost_to_open : 850
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kebet"
			idx : 27
			pos : [834, 904]
			route : 3
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
				[820, 981], [814, 963], [827, 946], [816, 912], [794, 919], [774, 935],
				[761, 921], [758, 914], [739, 915], [718, 899], [718, 891], [699, 886],
				[675, 858], [677, 848], [650, 841], [634, 822], [619, 818], [591, 795],
				[575, 756], [563, 732], [562, 714], [562, 699], [568, 630], [575, 612],
				[585, 589], [589, 591]
			]
		}
		{
			route : 2
			type : 1
			points [
				[901, 89], [882, 120], [882, 149], [870, 202], [862, 259], [856, 304],
				[837, 324], [807, 344], [749, 366], [701, 392], [666, 383], [657, 393],
				[646, 411], [627, 427], [599, 441], [592, 455], [581, 460], [574, 465],
				[570, 485], [568, 517], [588, 529], [581, 544], [591, 545], [589, 565],
				[590, 587]
			]
		}
		{
			route : 3
			type : 1
			points [
				[852, 918], [812, 909], [771, 935], [759, 915], [734, 916], [715, 896],
				[716, 891], [700, 887], [679, 860], [675, 851], [661, 845], [653, 828],
				[637, 822], [596, 796], [598, 775], [585, 760], [591, 732], [569, 719],
				[575, 660], [587, 642], [587, 624], [604, 604], [590, 585]
			]
		}
		{
			route : 4
			type : 1
			points [
				[599, 739], [569, 722], [573, 713], [577, 666], [588, 624], [602, 609],
				[588, 585]
			]
		}
		{
			route : 5
			type : 2
			points [
				[748, 1513], [735, 1489], [728, 1482], [715, 1482], [704, 1478], [698, 1460],
				[715, 1458], [724, 1443], [771, 1405], [786, 1391], [787, 1378], [780, 1367],
				[843, 1305], [870, 1319], [892, 1267], [901, 1255], [902, 1222], [897, 1215],
				[889, 1208], [895, 1197], [894, 1182], [884, 1160], [884, 1135], [877, 1120],
				[877, 1056], [857, 1027], [822, 1001], [824, 952], [815, 910], [767, 938],
				[698, 881], [621, 818], [600, 780], [586, 756], [591, 731], [572, 719],
				[581, 661], [589, 642], [586, 625], [594, 588]
			]
		}
		{
			route : 6
			type : 1
			points [
				[564, 505], [585, 527], [589, 546], [595, 592]
			]
		}
		{
			route : 7
			type : 2
			points [
				[785, 1369], [842, 1310], [872, 1317], [903, 1258], [906, 1234], [905, 1223],
				[896, 1214], [889, 1209], [896, 1198], [897, 1181], [889, 1172], [881, 1158],
				[885, 1144], [885, 1133], [875, 1093], [876, 1062], [860, 1032], [847, 1018],
				[832, 1013], [823, 988], [834, 941], [810, 916], [775, 932], [737, 911],
				[687, 866], [604, 801], [583, 779], [570, 720], [573, 665], [592, 631],
				[595, 585]
			]
		}
		{
			route : 9
			type : 1
			points [
				[368, 1054], [436, 1078], [508, 1095], [578, 1119], [651, 1138], [764, 1094],
				[808, 1043], [818, 989], [853, 922], [811, 910], [773, 940], [759, 917],
				[746, 912], [719, 898], [719, 889], [694, 889], [675, 862], [675, 849],
				[650, 844], [624, 818], [595, 798], [594, 739], [572, 695], [575, 666],
				[587, 635], [601, 607], [596, 589]
			]
		}
		{
			route : 11
			type : 1
			points [
				[656, 1153], [721, 1125], [778, 1098], [820, 1043], [825, 980], [816, 916],
				[765, 931], [758, 915], [739, 919], [721, 896], [715, 892], [693, 882],
				[678, 855], [659, 850], [651, 844], [651, 829], [618, 817], [571, 763],
				[559, 724], [562, 657], [574, 629], [571, 611], [599, 590]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [536, 428], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [427, 645], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [595, 456], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [517, 487], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [611, 537], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [500, 550], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [562, 561], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [610, 739], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [512, 522], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [585, 521], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [615, 711], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [631, 715], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [890, 906], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [381, 1035], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [808, 1196], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [778, 1327], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [871, 906], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [820, 883], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [679, 889], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [839, 1089], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [848, 965], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [845, 980], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [485, 507], image : "pharaoh_general/empire_bits_00123" }
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
		{ name : "#upper_egypt", pos : [687, 956] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		raids : ""
		i0_leaves_wired : false
		i17_leaves_wired : false
		i48_leaves_wired : false
		i67_leaves_wired : false
		i70_leaves_wired : false
		i43_leaves_wired : false

		event0_meat_done : false
		event17_bricks_done : false
		event48_pottery_done : false
		event67_meat_done : false
		event70_limestone_done : false

		event43_linen_last_year : -1
		event78_trade_last_year : -1
		event79_trade_last_year : -1
		event80_trade_last_year : -1
		event82_trade_last_year : -1
		event83_trade_last_year : -1
		event84_wage_last_year : -1
		event85_wage_last_year : -1
		event86_wage_last_year : -1
		event87_wage_last_year : -1
		event88_water_last_year : -1
		event89_water_last_year : -1
		event90_water_last_year : -1



		start_message_shown : false
	}
}

function mission27_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission27_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission27_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, city_name) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
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

// pak i=0: meatx9 ok->6 KR+6; refuse->1 KRx3 (+ chain egyptx8 via i=3); late->91 KRx3.
function mission27_ensure_i0_leaves() {
	if (mission.i0_leaves_wired) {
		return
	}
	mission.i0_leaves_wired = true
	mission27_make_leaf(1006, EVENT_TYPE_REPUTATION_INCREASE, undefined, 6, 2)
	mission27_make_leaf(1001, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission27_make_leaf(1091, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
}

// pak i=17: bricksx13 ok->47 KR+5; refuse/late->18 KRx3 (+ chain egyptx9 via i=22 on refuse).
function mission27_ensure_i17_leaves() {
	if (mission.i17_leaves_wired) {
		return
	}
	mission.i17_leaves_wired = true
	mission27_make_leaf(1047, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission27_make_leaf(1018, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
}

// pak i=48: potteryx7 ok->57 NEW_TRADE Kerma; refuse/late->51 KRx2.
function mission27_ensure_i48_leaves() {
	if (mission.i48_leaves_wired) {
		return
	}
	mission.i48_leaves_wired = true
	mission27_make_leaf(1057, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")
	mission27_make_leaf(1051, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 2)
}

// pak i=67: meatx2 ok->68 KR+1; refuse->69 KRx3; late->114 GIFTx168 (no-op deben, item=31).
function mission27_ensure_i67_leaves() {
	if (mission.i67_leaves_wired) {
		return
	}
	mission.i67_leaves_wired = true
	mission27_make_leaf(1068, EVENT_TYPE_REPUTATION_INCREASE, undefined, 1, 2)
	mission27_make_leaf(1069, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission27_make_leaf(1114, EVENT_TYPE_GIFT_FROM_PHARAOH, undefined, 168, 2)
}

// pak i=70: limestonex6 ok->71 KR+7->72 GIFTx1514; refuse->73 KRx5 (+ chain egyptx6 via i=76);
// late->115 KRx3->116 GIFTx135.
function mission27_ensure_i70_leaves() {
	if (mission.i70_leaves_wired) {
		return
	}
	mission.i70_leaves_wired = true
	var ok = mission27_make_leaf(1071, EVENT_TYPE_REPUTATION_INCREASE, undefined, 7, 2)
	mission27_make_leaf(1072, EVENT_TYPE_GIFT_FROM_PHARAOH, undefined, 1514, 2)
	ok.set_completed_action_tag(1072)
	mission27_make_leaf(1073, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	var late = mission27_make_leaf(1115, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission27_make_leaf(1116, EVENT_TYPE_GIFT_FROM_PHARAOH, undefined, 135, 2)
	late.set_completed_action_tag(1116)
}

// pak i=43: linenx15 ok->44 KR+3->46 GIFTx1385; refuse->45 KRx3; late->108 KRx3.
function mission27_ensure_i43_leaves() {
	if (mission.i43_leaves_wired) {
		return
	}
	mission.i43_leaves_wired = true
	var ok = mission27_make_leaf(1044, EVENT_TYPE_REPUTATION_INCREASE, undefined, 3, 2)
	mission27_make_leaf(1046, EVENT_TYPE_GIFT_FROM_PHARAOH, undefined, 1385, 2)
	ok.set_completed_action_tag(1046)
	mission27_make_leaf(1045, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
	mission27_make_leaf(1108, EVENT_TYPE_REPUTATION_DECREASE, undefined, 3, 2)
}

function mission27_ensure_all_leaves() {
	mission27_ensure_i0_leaves()
	mission27_ensure_i17_leaves()
	mission27_ensure_i48_leaves()
	mission27_ensure_i67_leaves()
	mission27_ensure_i70_leaves()
	mission27_ensure_i43_leaves()
}

[es=event_mission_start, mission=mission27]
function mission27_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_itjtawy")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_7_LIBIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission27_ensure_all_leaves()
}

[es=event_advance_month, mission=mission27]
function mission27_requests_and_events(ev) {
	mission27_ensure_all_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_LINEN, "linen_recurring", abs)

	// pak i=0: meatx9 /8mo y2m7 Men-nefer subtype=5 (famine opener).
	if (!mission.event0_meat_done && ev.years_since_start == 2 && ev.month == 7) {
		mission.event0_meat_done = true
		log_info("akhenaten: mission 27 meatx9 (i=0)")
		mission27_fire_request(2000, RESOURCE_MEAT, 9, 8, 1006, 1001, 1091, 5, "Men-nefer")
	}
	// pak i=67: meatx2 /6mo y2m10 Kerma (small early famine request).
	if (!mission.event67_meat_done && ev.years_since_start == 2 && ev.month == 10) {
		mission.event67_meat_done = true
		log_info("akhenaten: mission 27 meatx2 (i=67)")
		mission27_fire_request(2067, RESOURCE_MEAT, 2, 6, 1068, 1069, 1114, undefined, "Kerma")
	}
	// pak i=48: potteryx7 /8mo y2m2 Kerma -> ok opens Kerma for trade (NEW_TRADE).
	if (!mission.event48_pottery_done && ev.years_since_start == 2 && ev.month == 2) {
		mission.event48_pottery_done = true
		log_info("akhenaten: mission 27 potteryx7 (i=48)")
		mission27_fire_request(2048, RESOURCE_POTTERY, 7, 8, 1057, 1051, 1051, undefined, "Kerma")
	}
	// pak i=17: bricksx13 /10mo y5m4 Men-nefer subtype=4 (construction).
	if (!mission.event17_bricks_done && ev.years_since_start == 5 && ev.month == 4) {
		mission.event17_bricks_done = true
		log_info("akhenaten: mission 27 bricksx13 (i=17)")
		mission27_fire_request(2017, RESOURCE_BRICKS, 13, 10, 1047, 1018, 1018, 4, "Men-nefer")
	}
	// pak i=70: limestonex6 /10mo y6m4 Men-nefer subtype=4 (construction).
	if (!mission.event70_limestone_done && ev.years_since_start == 6 && ev.month == 4) {
		mission.event70_limestone_done = true
		log_info("akhenaten: mission 27 limestonex6 (i=70)")
		mission27_fire_request(2070, RESOURCE_LIMESTONE, 6, 10, 1071, 1073, 1115, 4, "Men-nefer")
	}

	// pak i=43: linenx15 /6mo recurring y14m2+ Menat Khufu subtype=3 (idle-gated, Rostja pattern).
	if (ev.years_since_start >= 14 && ev.month == 2
			&& mission.event43_linen_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_LINEN, "linen_recurring", abs)) {
		mission.event43_linen_last_year = ev.years_since_start
		log_info("akhenaten: mission 27 linenx15 recurring (i=43)")
		mission27_fire_request(3000 + 43 * 100 + ev.years_since_start,
			RESOURCE_LINEN, 15, 6, 1044, 1045, 1108, 3, "Menat Khufu")
	}

	// Recurring land-trade problems (pak i=78/79/80/82/83; ok/refuse are pak no-ops).
	if (ev.years_since_start >= 8 && ev.month == 3 && mission.event78_trade_last_year != ev.years_since_start) {
		mission.event78_trade_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 78 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 8)
	}
	if (ev.years_since_start >= 28 && ev.month == 4 && mission.event79_trade_last_year != ev.years_since_start) {
		mission.event79_trade_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 79 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 9)
	}
	if (ev.years_since_start >= 45 && ev.month == 3 && mission.event80_trade_last_year != ev.years_since_start) {
		mission.event80_trade_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 80 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 8)
	}
	if (ev.years_since_start >= 63 && ev.month == 3 && mission.event82_trade_last_year != ev.years_since_start) {
		mission.event82_trade_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 82 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 7)
	}
	if (ev.years_since_start >= 90 && ev.month == 3 && mission.event83_trade_last_year != ev.years_since_start) {
		mission.event83_trade_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 83 * 100 + ev.years_since_start,
			EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 5)
	}

	// Recurring wage changes (pak i=84/85/86/87).
	if (ev.years_since_start >= 7 && ev.month == 10 && mission.event84_wage_last_year != ev.years_since_start) {
		mission.event84_wage_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 84 * 100 + ev.years_since_start,
			EVENT_TYPE_WAGE_INCREASE, undefined, 2)
	}
	if (ev.years_since_start >= 13 && ev.month == 2 && mission.event85_wage_last_year != ev.years_since_start) {
		mission.event85_wage_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 85 * 100 + ev.years_since_start,
			EVENT_TYPE_WAGE_DECREASE, undefined, 2)
	}
	if (ev.years_since_start >= 22 && ev.month == 6 && mission.event86_wage_last_year != ev.years_since_start) {
		mission.event86_wage_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 86 * 100 + ev.years_since_start,
			EVENT_TYPE_WAGE_INCREASE, undefined, 7)
	}
	if (ev.years_since_start >= 35 && ev.month == 9 && mission.event87_wage_last_year != ev.years_since_start) {
		mission.event87_wage_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 87 * 100 + ev.years_since_start,
			EVENT_TYPE_WAGE_DECREASE, undefined, 5)
	}

	// Recurring contaminated water (pak i=88/89/90).
	if (ev.years_since_start >= 4 && ev.month == 7 && mission.event88_water_last_year != ev.years_since_start) {
		mission.event88_water_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 88 * 100 + ev.years_since_start,
			EVENT_TYPE_CONTAMINATED_WATER, undefined, 7)
	}
	if (ev.years_since_start >= 30 && ev.month == 7 && mission.event89_water_last_year != ev.years_since_start) {
		mission.event89_water_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 89 * 100 + ev.years_since_start,
			EVENT_TYPE_CONTAMINATED_WATER, undefined, 7)
	}
	if (ev.years_since_start >= 85 && ev.month == 7 && mission.event90_water_last_year != ev.years_since_start) {
		mission.event90_water_last_year = ev.years_since_start
		mission27_fire_simple_event(3000 + 90 * 100 + ev.years_since_start,
			EVENT_TYPE_CONTAMINATED_WATER, undefined, 6)
	}
}

// pak i=3 / i=22 / i=76: the Egyptian raids of the refused meat / bricks / limestone requests (tags 2000 / 2017 /
// 2070), due their time.year months on; as they attack, pak i=5 / i=23 / i=77.
function mission27_raid_list() {
	var G = ENEMY_3_EGYPTIAN
	var E = EVENT_INVADER_EGYPT
	return [
		{ key: "i3", invasion_id: 3, invader: E, enemy: G, amount: 8, months_initial: 5, location: [2, -1, 1, 5],
			attack_target: EVENT_ATTACK_TARGET_RANDOM,
			chain_event: { tag_id: 1005, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 10 } },
		{ key: "i22", invasion_id: 22, invader: E, enemy: G, amount: 9, months_initial: 8, location: [2, -1, 1, 5],
			attack_target: EVENT_ATTACK_TARGET_RANDOM,
			chain_event: { tag_id: 1023, type: EVENT_TYPE_CITY_STATUS_CHANGE, amount: 5,
				subtype: EVENT_SUBTYPE_LOST_TRADE_ROUTE, city: "Menat Khufu" } },
		{ key: "i76", invasion_id: 76, invader: E, enemy: G, amount: 6, months_initial: 6, location: [1, -1, 1, 5],
			attack_target: EVENT_ATTACK_TARGET_FOOD,
			chain_event: { tag_id: 1077, type: EVENT_TYPE_REPUTATION_DECREASE, amount: 7 } }
	]
}

[es=event_advance_month, mission=mission27]
function mission27_raids(ev) {
	mission_raids_month(mission, mission27, ev, mission27_raid_list())
}

[es=event_request_cleared, mission=mission27]
function mission27_on_request_cleared(ev) {
	if (mission_request_outcome(ev) != "refuse") {
		return
	}
	if (ev.tag_id == 2000) {
		mission_raid_schedule(mission, mission27_raid_list(), "i3", 5)
	} else if (ev.tag_id == 2017) {
		mission_raid_schedule(mission, mission27_raid_list(), "i22", 7)
	} else if (ev.tag_id == 2070) {
		mission_raid_schedule(mission, mission27_raid_list(), "i76", 3)
	}
}
