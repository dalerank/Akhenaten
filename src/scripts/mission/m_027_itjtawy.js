log_info("akhenaten: mission 27 itjtawy started")

// Empire / events aligned with original campaign scenario 27 (2026-07-26 dump); see
// tmp/mission27_clean.txt (triage) and tmp/mission27_key.txt (raw dump).
// Empire id=1. Scenario enemy ENEMY_7_LIBIAN (briefing sprites only - every timed
// invasion in the pak is invader=egypt(2) -> ENEMY_3_EGYPTIAN, incl. the by_favour pair).
// Gods: Osirisx1, Ptahx1, Sethx1, Bastx2 - no JS override. Funds Normal 8000 / loan 3000 /
// debt_interest 8 (low). Rank 10 (Pharaoh era, matches Iken/Heh).
// Convergence: Kebet (25) and Menat Khufu (26) both funnel into this scenario. No
// next_mission here - a choice[] host to Iken (28, already scripted) / Sawu (29, not yet;
// its button stays hidden until that mission is scripted).
// Win: pop 7500 / culture 60 / prosperity 60 / monuments 33 (Sphinx 1 + Medium mudbrick 8
//   + Small mudbrick 4 → trunc(2.25·13+4.5)=33) / kingdom 85 / housing_count 6 +
//   housing_level 17 (six BUILDING_HOUSE_STATELY_MANOR).
// Burial: pak burial_count=5 - grainx10 potteryx25 beerx12 luxury_goodsx12 papyrusx15.
// Trade: Buhen(7 sea) Byblos(2) Dakhla Oasis(9) Men-nefer(6) Menat Khufu(4).
// Display: Kerma(5 sea) Kharga Oasis(11) Waset(1) Kebet(3). SKIP empty map_obj idx=8.
// No pak river/inv_land/inv_sea points beyond the single disembark slot i=2 - omit
// invasion_points_*; chain / favour invasions fall back to the map entry tile (-1,-1).
// Events (pragmatic depth, Menat-style - KR leaves + key side effects, not every nested
// grain/pomegranates/papyrus chain request):
//   i=0  meatx9      y2m7  /8mo  Men-nefer  ok KR+6 / refuse KRx3 + chain egyptx8 (i=3) / late KRx3
//   i=67 meatx2      y2m10 /6mo  Kerma      ok KR+1 / refuse KRx3 / late GIFTx168 (no-op deben)
//   i=48 potteryx7   y2m2  /8mo  Kerma      ok NEW_TRADE Kerma / refuse KRx2 / late = refuse
//   i=17 bricksx13   y5m4  /10mo Men-nefer  ok KR+5 / refuse KRx3 + chain egyptx9 (i=22) / late = refuse
//   i=70 limestonex6 y6m4  /10mo Men-nefer  ok KR+7->GIFTx1514 / refuse KRx5 + chain egyptx6 (i=76) / late KRx3->GIFTx135
//   Favour i=118->119: egyptx50->x50 when kingdom rating x 0 (Menat pattern, size 50 not 40).
//   Recurring idle-gate (fire once/year from the pak start year, month match):
//     i=43 linenx15 y14m2+ Menat Khufu (ok KR+3->GIFTx1385 / refuse KRx3 / late KRx3)
//     i=78/79/80/82/83 LAND_TRADE_PROBLEM y8/28/45/63/90
//     i=84/85/86/87 WAGE_INCREASE/DECREASE y7/13/22/35
//     i=88/89/90 CONTAMINATED_WATER y4/30/85
// SKIP: orphan KR/MSG chain_only i=5,31,41,92,95,101,103 (no inbound reference); i=81 clay
//   pit flood (editor year=31073 junk, not a real landslide); NEW_TRADE i=14/i=37 and LOST
//   i=23 (deep chain-only, unreachable from the wired roots at this depth); pak_allowed dump
//   (editor artifact - only ROAD/CLEAR_LAND/CRUDE_HUT).
// Tag_id scheme:
//   1000 + i               chain-only leaves
//   2000 + i               once calendar roots
//   3000 + i*100 + year    recurring calendar roots

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
	house_tax_multipliers [300, 200, 150, 100, 75]

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

	// Monuments 33 = Sphinx(1) + Medium mudbrick(8) + Small mudbrick(4).
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
			max_traders : 1
			trade_limits : default_trade_limits
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
			max_traders : 1
			trade_limits : default_trade_limits
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
			max_traders : 1
			trade_limits : default_trade_limits
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
			max_traders : 1
			trade_limits : default_trade_limits
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
			max_traders : 1
			trade_limits : default_trade_limits
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

		b12_i0_done : false
		b12_i17_done : false
		b12_i70_done : false

		egypt_favour_invasion_done : false
		egypt_favour_wave2_done : false
		egypt_favour_wave2_enemies_seen : false

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

// No pak inv_land/sea points - chain / favour Egyptian raids use the map entry fallback (-1,-1).
function mission27_egypt_raid(invasion_id, size, attack_target) {
	log_info("akhenaten: mission 27 itjtawy egypt raid id=" + invasion_id + " size=" + size)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	city.start_foreign_army_invasion({
		invasion_id: invasion_id,
		enemy: ENEMY_3_EGYPTIAN,
		size: size,
		tilex: -1,
		tiley: -1,
		want_destroy_buildings: size,
		invasion_attack_target: attack_target
	})
}

function mission27_favour_wave(size, invasion_id) {
	log_info("akhenaten: mission 27 itjtawy favour wave size=" + size + " kr=" + city.rating_kingdom
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

// Chain invasions from JS after a request refuse (EVENT_TYPE_INVASION chain nodes are
// no-ops in this engine). Only the three once-request roots have a pak invasion child.
[es=event_request_cleared, mission=mission27]
function mission27_on_request_cleared(ev) {
	if (mission_request_outcome(ev) != "refuse") {
		return
	}
	if (ev.tag_id == 2000 && !mission.b12_i0_done) {
		mission.b12_i0_done = true
		log_info("akhenaten: mission 27 egyptx8 after meat refuse (i=3)", {ev:ev})
		mission27_egypt_raid(3, 8, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (ev.tag_id == 2017 && !mission.b12_i17_done) {
		mission.b12_i17_done = true
		log_info("akhenaten: mission 27 egyptx9 after bricks refuse (i=22)", {ev:ev})
		mission27_egypt_raid(22, 9, EVENT_ATTACK_TARGET_RANDOM)
		return
	}
	if (ev.tag_id == 2070 && !mission.b12_i70_done) {
		mission.b12_i70_done = true
		log_info("akhenaten: mission 27 egyptx6 after limestone refuse (i=76)", {ev:ev})
		mission27_egypt_raid(76, 6, EVENT_ATTACK_TARGET_RANDOM)
	}
}

// pak i=118->119: by_favour egyptx50 -> after wipe, chain egyptx50 (attack=4 RANDOM).
[es=event_advance_month, mission=mission27]
function mission27_egypt_favour_invasion(ev) {
	if (mission.egypt_favour_invasion_done && !mission.egypt_favour_wave2_done) {
		if (city.num_enemy_formations > 0) {
			mission.egypt_favour_wave2_enemies_seen = true
			return
		}
		if (!mission.egypt_favour_wave2_enemies_seen) {
			return
		}
		mission.egypt_favour_wave2_done = true
		mission27_favour_wave(50, 119)
		return
	}

	if (mission.egypt_favour_invasion_done) {
		return
	}
	if (city.rating_kingdom > 0) {
		return
	}
	mission.egypt_favour_invasion_done = true
	mission.egypt_favour_wave2_enemies_seen = false
	mission27_favour_wave(50, 118)
}
