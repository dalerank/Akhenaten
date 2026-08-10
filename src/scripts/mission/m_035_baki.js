log_info("akhenaten: mission 35 baki started")

// Empire id=1. HITTITE (pak). Gods Ra×2, Osiris, Ptah, Seth.
// Funds 7000/2500/20. Rank 10.
// Win: pop 10000 / culture 70 / prosperity 70 / monuments 35 (Mausoleum+Med+Small mudbrick W=5+8+4→42) / kingdom 85 / housing 19.
// Burial ×5 all 32. SKIP map_obj idx=11. Orphan routes 25/26.
// Truncate i=18→0. Remap i=1 ok=85. Favour egypt 60→5→15→20→20.
// Inv: land×1 + sea×1 packed → loc2=sea[0] via_sea (E3c); loc3/4/8 OOB navy→sea0.
// Tag_id: 1000+i leaves; 2000+i roots; 3000+i*100+year recurring.

mission35 { // Baki (Kuban) — The Glory of Egypt
	map_file : "data/maps/m_035_baki.map"
	start_message : "message_mission_kuban"
	selection_title : "Baki"
	player_rank : 10

	next_mission : 37

	// pak Normal funds=7000 loan=2500 debt_interest=20 → int_dcy around Normal.
	initial_funds [14000, 9300, 7000, 4700, 3700]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [10, 15, 20, 25, 30]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		// pak animals=0; enable so prey update after create_herds (hunting lodge).
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/235_mission.mp3"
		victory : "Voice/Mission/235_victory.mp3"
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
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER, BUILDING_CLAY_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FISHING_WHARF,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MAUSOLEUM, BUILDING_MEDIUM_MUDBRICK_PYRAMID, BUILDING_SMALL_MUDBRICK_PYRAMID,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	// Soft goal 35; engine weights Mausoleum+Med+Small mudbrick W=5+8+4 → ~42.
	win_criteria {
		population    {enabled : true, goal : 10000 }
		culture       {enabled : true, goal : 70 }
		prosperity    {enabled : true, goal : 70 }
		monuments     {enabled : true, goal : 35 }
		kingdom       {enabled : true, goal : 85 }
		housing_level {enabled : true, goal : 19 }
	}

	entry_point [87, 26]
	exit_point [186, 74]
	river_entry_point [36, 77]
	river_exit_point [37, 76]
	disembark_points [ [-1, -1], [-1, -1], [53, 111] ]
	invasion_points_land [ [187, 137] ]
	// pak inv_sea [75,198] (water). Packed loc2=sea[0] → via_sea (E3c).
	invasion_points_sea [ [75, 198] ]

	herd_points_predator [
		[55, 129], [72, 180], [156, 84]
	]
	herd_points_prey [
		[202, 115], [177, 103], [114, 182], [34, 125]
	]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 32 }
		{ resource: RESOURCE_POTTERY, required: 32 }
		{ resource: RESOURCE_LINEN, required: 32 }
		{ resource: RESOURCE_LUXURY_GOODS, required: 32 }
		{ resource: RESOURCE_CHARIOTS, required: 32 }
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Baki"
			idx : 1
			pos : [902, 1218]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FIGS, RESOURCE_GAMEMEAT, RESOURCE_CLAY, RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
		}
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 9
			is_open : false
			cost_to_open : 200
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
				{ resource: RESOURCE_SANDSTONE, limit: 1500 }
			]
		}
		{
			name : "Itjtawy"
			idx : 6
			pos : [568, 557]
			route : 1
			is_open : false
			cost_to_open : 1015
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_MEAT, RESOURCE_STRAW, RESOURCE_POTTERY, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 9
			pos : [545, 487]
			route : 10
			is_open : false
			cost_to_open : 1085
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Pwenet"
			idx : 12
			pos : [1133, 1325]
			route : 8
			is_open : false
			cost_to_open : 300
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
			name : "Qadesh"
			idx : 13
			pos : [962, 10]
			route : 2
			is_open : false
			cost_to_open : 1845
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Rowarty"
			idx : 14
			pos : [612, 389]
			route : 5
			is_open : false
			cost_to_open : 1230
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 4000 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
		{
			name : "Waset"
			idx : 16
			pos : [811, 968]
			route : 6
			is_open : false
			cost_to_open : 325
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
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
			name : "Menat Khufu"
			idx : 10
			pos : [578, 720]
			route : 7
			cost_to_open : 860
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 11
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Gaza"
			idx : 3
			pos : [846, 280]
			route : 3
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Heh"
			idx : 4
			pos : [698, 1414]
			route : 13
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Iken"
			idx : 5
			pos : [735, 1380]
			route : 12
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			// Display foreign; unlocked by henna chain NEW_TRADE (cosmetic; no polyline).
			name : "Kerma"
			idx : 7
			pos : [732, 1491]
			route : 14
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Knossos"
			idx : 8
			pos : [175, 131]
			route : 15
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 15
			pos : [877, 121]
			route : 4
			cost_to_open : 1665
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	routes [
		{
			route : 1
			type : 2
			points [
				[592, 581], [600, 596], [599, 616], [583, 633], [583, 650], [568, 668],
				[571, 677], [569, 711], [565, 719], [570, 727], [582, 740], [586, 760],
				[596, 776], [598, 798], [610, 813], [627, 817], [630, 824], [644, 826],
				[667, 849], [678, 863], [702, 883], [720, 888], [723, 899], [743, 917],
				[758, 915], [775, 936], [813, 908], [824, 924], [827, 941], [823, 952],
				[816, 965], [832, 1013], [850, 1021], [876, 1068], [876, 1094], [881, 1101],
				[878, 1121], [886, 1137], [882, 1183], [894, 1196], [890, 1211], [930, 1238]
			]
		}
		{
			route : 2
			type : 2
			points [
				[981, 26], [872, 39], [613, 392], [652, 402], [627, 427], [598, 443],
				[590, 456], [576, 463], [564, 505], [586, 525], [591, 570], [603, 612],
				[583, 630], [580, 652], [570, 669], [568, 712], [566, 721], [589, 751],
				[585, 761], [597, 780], [597, 797], [618, 816], [628, 818], [634, 824],
				[645, 824], [653, 834], [655, 844], [674, 855], [685, 870], [703, 885],
				[719, 889], [722, 901], [745, 918], [758, 915], [781, 935], [812, 910],
				[824, 924], [828, 944], [816, 960], [833, 1014], [852, 1023], [864, 1040],
				[873, 1057], [879, 1084], [881, 1097], [878, 1122], [887, 1139], [883, 1183],
				[895, 1198], [918, 1239]
			]
		}
		{
			route : 4
			type : 2
			points [
				[892, 138], [612, 388], [650, 405], [623, 431], [596, 445], [593, 457],
				[573, 464], [577, 519], [587, 534], [590, 557], [595, 590], [598, 612],
				[584, 628], [583, 649], [569, 669], [569, 709], [565, 721], [588, 747],
				[585, 759], [595, 781], [599, 800], [617, 816], [652, 832], [651, 830],
				[661, 849], [675, 853], [678, 864], [703, 884], [718, 889], [726, 903],
				[745, 919], [757, 916], [772, 934], [814, 909], [829, 945], [816, 963],
				[832, 1014], [853, 1029], [865, 1042], [866, 1054], [877, 1064], [880, 1123],
				[885, 1144], [885, 1167], [898, 1200], [889, 1213], [924, 1235]
			]
		}
		{
			route : 5
			type : 2
			points [
				[637, 415], [625, 430], [597, 445], [590, 458], [572, 464], [568, 513],
				[587, 528], [599, 611], [583, 631], [582, 648], [568, 667], [571, 679],
				[568, 711], [566, 719], [587, 746], [584, 763], [596, 777], [598, 799],
				[627, 818], [632, 823], [647, 828], [657, 845], [675, 853], [683, 870],
				[702, 883], [721, 888], [722, 900], [742, 915], [759, 916], [763, 925],
				[775, 936], [815, 908], [822, 925], [828, 943], [816, 959], [830, 1015],
				[851, 1020], [864, 1035], [864, 1053], [875, 1061], [876, 1094], [882, 1106],
				[878, 1116], [887, 1138], [883, 1168], [896, 1201], [889, 1212], [921, 1237]
			]
		}
		{
			route : 6
			type : 2
			points [
				[827, 998], [832, 1013], [851, 1022], [864, 1037], [866, 1052], [876, 1061],
				[880, 1075], [875, 1100], [880, 1107], [878, 1122], [887, 1136], [882, 1163],
				[895, 1198], [888, 1211], [925, 1236]
			]
		}
		{
			route : 7
			type : 2
			points [
				[588, 748], [585, 764], [594, 772], [599, 792], [600, 807], [615, 814],
				[625, 814], [627, 822], [643, 825], [652, 834], [655, 843], [674, 853],
				[676, 864], [688, 870], [701, 883], [718, 889], [721, 900], [745, 919],
				[759, 916], [761, 923], [773, 936], [788, 929], [793, 920], [800, 920],
				[812, 907], [820, 913], [823, 924], [828, 944], [816, 962], [831, 1014],
				[846, 1019], [861, 1032], [865, 1049], [875, 1061], [879, 1073], [876, 1095],
				[882, 1100], [877, 1114], [886, 1135], [884, 1147], [880, 1161], [894, 1196],
				[890, 1210], [925, 1237]
			]
		}
		{
			route : 8
			type : 1
			points [
				[1154, 1344], [1116, 1332], [1114, 1323], [1105, 1306], [1089, 1301], [1081, 1298],
				[1067, 1295], [1058, 1291], [1038, 1279], [1035, 1276], [1020, 1270], [1003, 1271],
				[1000, 1272], [992, 1272], [979, 1271], [968, 1269], [961, 1265], [958, 1263],
				[923, 1241]
			]
		}
		{
			route : 9
			type : 1
			points [
				[899, 1176], [908, 1192], [907, 1203], [923, 1233]
			]
		}
		{
			route : 10
			type : 2
			points [
				[569, 505], [584, 528], [588, 547], [593, 588], [598, 598], [599, 614],
				[583, 632], [580, 650], [567, 669], [571, 679], [568, 713], [565, 721],
				[586, 746], [588, 763], [594, 776], [601, 803], [630, 822], [644, 825],
				[652, 832], [656, 846], [676, 852], [678, 866], [706, 886], [719, 887],
				[725, 903], [747, 918], [759, 915], [761, 923], [767, 933], [780, 934],
				[795, 922], [803, 918], [813, 908], [820, 916], [825, 932], [828, 944],
				[817, 960], [832, 1015], [849, 1020], [864, 1038], [866, 1053], [876, 1063],
				[879, 1085], [879, 1098], [883, 1103], [878, 1123], [885, 1135], [883, 1150],
				[885, 1177], [903, 1226]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [536, 437], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [420, 656], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [484, 511], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [563, 587], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [612, 712], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [632, 712], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [615, 417], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [602, 505], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [616, 737], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [623, 761], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [643, 802], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [515, 526], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [582, 487], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [863, 839], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [669, 1417], image : "pharaoh_general/empire_bits_00125" }
		{ pos : [843, 977], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [861, 895], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [392, 1049], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [815, 1205], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [774, 1337], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [711, 1384], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [844, 894], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [840, 961], image : "pharaoh_general/empire_bits_00115" }
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
		{ name : "#palestine", pos : [889, 174] }
		{ name : "#sinai", pos : [787, 478] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [688, 998] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		shared_leaves_wired : false
		henna_iken_leaves_wired : false
		heh_gems_leaves_wired : false

		event0_gems_done : false
		event4_henna_done : false
		event9_luxury_done : false
		event10_gamemeat_done : false
		event11_gems_done : false
		event19_copper_done : false

		event21_sandstone_last_year : -1
		event22_gems_last_year : -1
		sandstone_recurring_was_busy : false
		sandstone_recurring_idle_since_abs : -1
		gems_recurring_was_busy : false
		gems_recurring_idle_since_abs : -1

		pharaoh_favour_invasion_done : false
		pharaoh_favour_wave2_done : false
		pharaoh_favour_wave3_done : false
		pharaoh_favour_wave4_done : false
		pharaoh_favour_wave5_done : false
		pharaoh_favour_enemies_seen : false

		start_message_shown : false
	}
}

function mission35_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission35_make_chain_request(tag, resource, amount, months, subtype, city_name) {
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
	request.set_sender_faction(0)
	return request
}

function mission35_fire_simple_event(tag, type, resource, amount, city_name, subtype) {
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

function mission35_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, city_name, defeat_tag) {
	var opts = { tag_id: tag, resource: resource, amount: amount, months_initial: months }
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(0)
	if (ok_tag) {
		request.set_completed_action_tag(ok_tag)
	}
	if (refuse_tag) {
		request.set_refusal_action_tag(refuse_tag)
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

// Shared KR leaves + gems-recurring outcomes.
// Remap i=1 ok=85 → no completed tag (orphan).
function mission35_ensure_shared_leaves() {
	if (mission.shared_leaves_wired) {
		return
	}
	mission.shared_leaves_wired = true
	mission35_make_leaf(1001, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 24, 4)
	mission35_make_leaf(1002, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 2, 4)
	mission35_make_leaf(1003, EVENT_TYPE_REPUTATION_DECREASE, undefined, 15, 2)
	mission35_make_leaf(1024, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 2)
	mission35_make_leaf(1025, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 2)
	mission35_make_leaf(1026, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 2)
}

// Henna/Iken chain: calendar henna Gaza ok/late → 1005.
function mission35_ensure_henna_iken_leaves() {
	if (mission.henna_iken_leaves_wired) {
		return
	}
	mission.henna_iken_leaves_wired = true

	var henna16 = mission35_make_chain_request(1005, RESOURCE_HENNA, 16, 12, 2, "Iken")
	var conquered = mission35_make_leaf(1006, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 7, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Iken")
	var henna32 = mission35_make_chain_request(1007, RESOURCE_HENNA, 32, 2, 2, "Iken")
	mission35_make_leaf(1008, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kerma")

	henna16.set_completed_action_tag(1006)
	henna16.set_refusal_action_tag(1003)
	henna16.set_too_late_action_tag(1007)
	conquered.set_completed_action_tag(1008)
	henna32.set_completed_action_tag(1006)
	henna32.set_refusal_action_tag(1003)
	henna32.set_too_late_action_tag(1006)
}

// Heh gems refuse chain: calendar gems×64 refuse → 1012.
// Truncate i=18 CITY_SAVED: dump ok→0 (do not re-arm gems).
function mission35_ensure_heh_gems_leaves() {
	if (mission.heh_gems_leaves_wired) {
		return
	}
	mission.heh_gems_leaves_wired = true

	var kr10 = mission35_make_leaf(1012, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 2)
	var henna24 = mission35_make_chain_request(1013, RESOURCE_HENNA, 24, 9, 2, "Gaza")
	var msg_conquered = mission35_make_leaf(1014, EVENT_TYPE_MESSAGE, undefined, 6, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Kerma")
	var conquered_itj = mission35_make_leaf(1015, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 5, 2,
		EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED, "Itjtawy")
	var trade_itj = mission35_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 2,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Itjtawy")
	var msg_lost = mission35_make_leaf(1017, EVENT_TYPE_MESSAGE, undefined, 7, 2,
		EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, "Heh")
	mission35_make_leaf(1018, EVENT_TYPE_MESSAGE, undefined, 5, 2,
		EVENT_SUBTYPE_MSG_CITY_SAVED, "Iken")
	mission35_make_leaf(1020, EVENT_TYPE_REPUTATION_INCREASE, undefined, 12, 2)

	kr10.set_completed_action_tag(1013)
	henna24.set_completed_action_tag(1014)
	henna24.set_refusal_action_tag(1017)
	henna24.set_too_late_action_tag(1018)
	henna24.set_defeat_action_tag(1017)
	msg_conquered.set_completed_action_tag(1015)
	conquered_itj.set_completed_action_tag(1016)
	trade_itj.set_completed_action_tag(1020)
	msg_lost.set_completed_action_tag(1003)
}

function mission35_ensure_all_leaves() {
	mission35_ensure_shared_leaves()
	mission35_ensure_henna_iken_leaves()
	mission35_ensure_heh_gems_leaves()
}

// pak location_fields = 1-based packed (land first, then sea).
// land[0]=[187,137] → loc1; sea[0]=[75,198] → loc2. Loc 3/4/8 = OOB navy → sea0.
function mission35_favour_wave(size, invasion_id, loc) {
	if (loc === undefined) {
		loc = 1
	}
	var opts = {
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_3_EGYPTIAN,
		kind: INVASION_KIND_KINGDOME,
		size: size,
		invasion_id: invasion_id,
		want_destroy_buildings: 0,
		invasion_attack_target: EVENT_ATTACK_TARGET_RANDOM
	}
	var via_sea = loc != 1
	if (via_sea) {
		opts.via_sea = 1
		opts.sea_point = 0
		opts.tilex = 75
		opts.tiley = 198
	} else {
		opts.tilex = 187
		opts.tiley = 137
	}
	log_info("akhenaten: mission 35 favour wave size=" + size + " kr=" + city.rating_kingdom
		+ " id=" + invasion_id + " loc=" + loc + " sea=" + via_sea
		+ " tile=" + opts.tilex + "," + opts.tiley)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	return city.start_foreign_army_invasion(opts)
}

[es=event_mission_start, mission=mission35]
function mission35_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HITTITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_kuban")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_4_HITTITE)
	__scenario_monuments.first = 25
	__scenario_monuments.second = 4
	__scenario_monuments.third = 3
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission35_ensure_all_leaves()
}

[es=event_advance_month, mission=mission35]
function mission35_requests_and_events(ev) {
	mission35_ensure_all_leaves()
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_SANDSTONE, "sandstone_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_GEMS, "gems_recurring", abs)

	// pak i=0: gems×12 /12mo y1m4 Kerma -> ok 1001; refuse 1003; late 1002.
	if (!mission.event0_gems_done && ev.years_since_start == 1 && ev.month == 4) {
		mission.event0_gems_done = true
		log_info("akhenaten: mission 35 gems×12 (i=0)")
		mission35_fire_request(2000, RESOURCE_GEMS, 12, 12, 1001, 1003, 1002, 0, "Kerma")
	}
	// pak i=4: henna×16 /12mo y2m1 Gaza subtype2 -> ok/late 1005; refuse 1003.
	if (!mission.event4_henna_done && ev.years_since_start == 2 && ev.month == 1) {
		mission.event4_henna_done = true
		log_info("akhenaten: mission 35 henna×16 Gaza (i=4)")
		mission35_fire_request(2004, RESOURCE_HENNA, 16, 12, 1005, 1003, 1005, 2, "Gaza")
	}
	// pak i=9: luxury×10 /9mo y4m0 Gaza -> ok 1001; refuse 1003; late 1002.
	if (!mission.event9_luxury_done && ev.years_since_start == 4 && ev.month == 0) {
		mission.event9_luxury_done = true
		log_info("akhenaten: mission 35 luxury×10 (i=9)")
		mission35_fire_request(2009, RESOURCE_LUXURY_GOODS, 10, 9, 1001, 1003, 1002, 0, "Gaza")
	}
	// pak i=10: gamemeat×24 /6mo y4m5 Itjtawy subtype5 -> ok 1001; refuse/late 1003.
	if (!mission.event10_gamemeat_done && ev.years_since_start == 4 && ev.month == 5) {
		mission.event10_gamemeat_done = true
		log_info("akhenaten: mission 35 gamemeat×24 (i=10)")
		mission35_fire_request(2010, RESOURCE_GAMEMEAT, 24, 6, 1001, 1003, 1003, 5, "Itjtawy")
	}
	// pak i=11: gems×64 /5mo y5m11 Heh subtype6 -> ok/late 1003; refuse 1012 (quirky as-pak).
	if (!mission.event11_gems_done && ev.years_since_start == 5 && ev.month == 11) {
		mission.event11_gems_done = true
		log_info("akhenaten: mission 35 gems×64 Heh (i=11)")
		mission35_fire_request(2011, RESOURCE_GEMS, 64, 5, 1003, 1012, 1003, 6, "Heh")
	}
	// pak i=19: copper×31 /12mo y7m1 Itjtawy -> ok 1001; refuse 1003; late 1002.
	if (!mission.event19_copper_done && ev.years_since_start == 7 && ev.month == 1) {
		mission.event19_copper_done = true
		log_info("akhenaten: mission 35 copper×31 (i=19)")
		mission35_fire_request(2019, RESOURCE_COPPER, 31, 12, 1001, 1003, 1002, 0, "Itjtawy")
	}

	// pak i=21: sandstone×24 /12mo recurring y9m6+ Itjtawy.
	if (ev.years_since_start >= 9 && ev.month == 6
			&& mission.event21_sandstone_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_SANDSTONE, "sandstone_recurring", abs)) {
		mission.event21_sandstone_last_year = ev.years_since_start
		log_info("akhenaten: mission 35 sandstone×24 recurring (i=21)")
		mission35_fire_request(3000 + 21 * 100 + ev.years_since_start,
			RESOURCE_SANDSTONE, 24, 12, 1001, 1003, 1002, 0, "Itjtawy")
	}
	// pak i=22: gems×20 /10mo recurring y10m0+ Heh (own idle gate; calendar gems are once).
	if (ev.years_since_start >= 10 && ev.month == 0
			&& mission.event22_gems_last_year != ev.years_since_start
			&& mission_recurring_request_may_fire(mission, RESOURCE_GEMS, "gems_recurring", abs)) {
		mission.event22_gems_last_year = ev.years_since_start
		log_info("akhenaten: mission 35 gems×20 recurring (i=22)")
		mission35_fire_request(3000 + 22 * 100 + ev.years_since_start,
			RESOURCE_GEMS, 20, 10, 1024, 1026, 1025, 0, "Heh")
	}
}

// pak i=23→27→28→29→30: by_favour egypt×60 loc1, then ×5×15×20×20 at loc 2/3/4/8.
[es=event_advance_month, mission=mission35]
function mission35_pharaoh_favour_invasion(ev) {
	if (mission.pharaoh_favour_invasion_done && !mission.pharaoh_favour_wave5_done) {
		if (city.num_enemy_formations > 0) {
			mission.pharaoh_favour_enemies_seen = true
			return
		}
		if (!mission.pharaoh_favour_enemies_seen) {
			return
		}
		mission.pharaoh_favour_enemies_seen = false
		if (!mission.pharaoh_favour_wave2_done) {
			mission.pharaoh_favour_wave2_done = true
			mission35_favour_wave(5, 27, 2)
			return
		}
		if (!mission.pharaoh_favour_wave3_done) {
			mission.pharaoh_favour_wave3_done = true
			mission35_favour_wave(15, 28, 3)
			return
		}
		if (!mission.pharaoh_favour_wave4_done) {
			mission.pharaoh_favour_wave4_done = true
			mission35_favour_wave(20, 29, 4)
			return
		}
		mission.pharaoh_favour_wave5_done = true
		mission35_favour_wave(20, 30, 8)
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
	log_info("akhenaten: mission 35 favour egypt×60 (i=23)")
	mission35_favour_wave(60, 23, 1)
}
