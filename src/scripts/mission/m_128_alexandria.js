log_info("akhenaten: mission 128 alexandria started")

// Custom mission 128 — Alexandria, "An Alexandrian Affair" (Cleopatra map Alexandria.map). Rank 10 (Pharaoh).
//
// Goals:     population 20000, culture 65, prosperity 75, monuments 66, kingdom 75, house count 5,
//            housing level 19.
// Start:     funds 12000, rescue loan 6000, debt interest 5% (normal difficulty).
// Gods:      Bast (patron), Osiris, Ra, Ptah — statuses come from the map.
// Monuments: the map's monument goal is a sun temple, a grand pyramid complex and a large pyramid;
//            every monument building is allowed.
// Trade:     none open at start; can open — Mycenae, Knossos, Enkomi, Kyrene, Men-nefer, Bubastis,
//            Rowarty, Meidum, Menat Khufu, Iunet, Qadesh, Byblos (all by sea), Rostja, Bahariya Oasis,
//            Pwenet; display only — Gaza, Tyre. Our city is Perwadjyt.
// Enemies:   Bedouin raids (Libyan sprites) at land point [93,210].
// Timeline:  y1m4 and every year after: request 11 bricks within 12 months (delivered: kingdom +5;
//            refused or late: -6); every year from y3m9 contaminated water, from y6m4 a gold mine
//            collapse, from y6m5 a clay pit flood; Bedouin raid 19 announced y8m0, attacks y9m6, and
//            again every time its army is gone (its year plus the years since start later).
//
// Notes for developers:
// - The map stores its invasion points interleaved, so the engine reads them as empty; they are
//   restored in invasion_points_land / invasion_points_sea below.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields.
// - Qadesh and Byblos point at route 19 in the map, which has no polyline; they use the nearby sea
//   routes 20 and 21 instead.
// - tag_id: 1001/1002 kingdom rating outcomes of the bricks request; 3000/3100/3200/3300/3400 + year for
//   the yearly bricks / clay flood / gold collapse / contaminated water / Bedouin warning;
//   3500 + year*12 + month Bedouin reminders.

mission128 { // Alexandria.map — An Alexandrian Affair
	selection_title : "Alexandria"
	selection_subtitle : "An Alexandrian Affair"
	selection_text : "Brief description of this map, for players. History, aims and tips etc."
	player_rank : 10

	// pak Normal funds=12000 loan=6000 debt_interest=5 → int_dcy around Normal.
	initial_funds [24000, 16000, 12000, 8000, 6400]
	rescue_loans [12000, 8000, 6000, 4000, 3200]
	debt_interest [1, 3, 5, 8, 10]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}
	religion_enabled : true
	hide_won_screen : false

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_WELL, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD, BUILDING_ARTISANS_GUILD,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP, BUILDING_HUNTING_LODGE,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_BRICKS_WORKSHOP, BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP,
		BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_WEAPONSMITH,
		BUILDING_CHARIOTS_WORKSHOP, BUILDING_LAMP_WORKSHOP, BUILDING_PAINT_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_DYNASTY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_DOCK,
		BUILDING_RECRUITER, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_TOWER, BUILDING_MUD_GATEHOUSE,
		BUILDING_BRICK_WALL, BUILDING_BRICK_TOWER, BUILDING_GATEHOUSE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FIGS_FARM, BUILDING_FLAX_FARM,
		BUILDING_LETTUCE_FARM, BUILDING_POMEGRANATES_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_HENNA_FARM,
		BUILDING_CATTLE_RANCH, BUILDING_REED_GATHERER, BUILDING_WOOD_CUTTERS,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_GRANITE_QUARRY,
		BUILDING_CLAY_PIT, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_COPPER_MINE,
		BUILDING_FERRY, BUILDING_LOW_BRIDGE, BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF,
		BUILDING_LIBRARY, BUILDING_SCRIBAL_SCHOOL, BUILDING_ZOO,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SUN_TEMPLE, BUILDING_LARGE_PYRAMID, BUILDING_GRAND_PYRAMID_COMPLEX,
		BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA, BUILDING_LARGE_MASTABA,
		BUILDING_SMALL_OBELISK, BUILDING_LARGE_OBELISK, BUILDING_SPHINX,
		BUILDING_MAUSOLEUM, BUILDING_ALEXANDRIA_LIBRARY, BUILDING_PHAROS_LIGHTHOUSE, BUILDING_CAESAREUM,
	]

	// Goals verified vs Alexandria.map scenario_info.
	win_criteria {
		population    {enabled : true, goal : 20000 }
		culture       {enabled : true, goal : 65 }
		prosperity    {enabled : true, goal : 75 }
		monuments     {enabled : true, goal : 66 }
		kingdom       {enabled : true, goal : 75 }
		housing_count {enabled : true, goal : 5 }
		housing_level {enabled : true, goal : 19 }
	}

	entry_point [154, 42]
	exit_point [156, 44]
	river_entry_point [24, 90]
	river_exit_point [37, 77]
	// File stores land/sea as interleaved xy; engine SoA bind drops them — restore here.
	invasion_points_land [ [93, 210] ]
	invasion_points_sea [ [203, 125] ]
	// Map dump: 6 fish + 4 herd points (herd types FIGURE_NONE; animals=0).
	fishing_points [
		[41, 98], [83, 47], [145, 90], [157, 139], [133, 150], [49, 157]
	]
	herd_points_predator [
		[113, 159], [142, 146], [143, 122], [149, 80]
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:0}
	hide_pak_cities : true
	cities [
		{
			name : "Perwadjyt"
			idx : 12
			pos : [406, 396]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_GEMS, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys []
		}

		{
			name : "Mycenae"
			idx : 10
			pos : [15, 11]
			route : 1
			is_open : false
			cost_to_open : 760
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			buys []
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Knossos"
			idx : 5
			pos : [175, 131]
			route : 2
			is_open : false
			cost_to_open : 525
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_FISH, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			buys []
			route_limits [
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Enkomi"
			idx : 2
			pos : [679, 49]
			route : 3
			is_open : false
			cost_to_open : 805
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_POMEGRANATES, RESOURCE_FISH, RESOURCE_COPPER ]
			buys [ RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Kyrene"
			idx : 6
			pos : [22, 341]
			route : 4
			is_open : false
			cost_to_open : 440
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_WEAPONS, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			buys []
			route_limits [
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Rostja"
			idx : 15
			pos : [504, 504]
			route : 5
			is_open : false
			cost_to_open : 135
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GEMS, RESOURCE_STONE ]
			buys [ RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}

		{
			name : "Men-nefer"
			idx : 8
			pos : [545, 487]
			route : 6
			is_open : false
			cost_to_open : 185
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Bubastis"
			idx : 1
			pos : [573, 416]
			route : 7
			is_open : false
			cost_to_open : 280
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_POTTERY, RESOURCE_FLAX, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BEER, RESOURCE_LUXURY_GOODS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Rowarty"
			idx : 16
			pos : [612, 389]
			route : 8
			is_open : false
			cost_to_open : 330
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_BRICKS, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}

		{
			name : "Meidum"
			idx : 7
			pos : [572, 592]
			route : 9
			is_open : false
			cost_to_open : 325
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_TIMBER, RESOURCE_REEDS, RESOURCE_PAPYRUS, RESOURCE_STONE ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_LIMESTONE ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
			]
		}

		{
			name : "Menat Khufu"
			idx : 9
			pos : [578, 720]
			route : 10
			is_open : false
			cost_to_open : 465
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_STONE ]
			buys [ RESOURCE_BRICKS, RESOURCE_LIMESTONE, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_STONE, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Bahariya Oasis"
			idx : 0
			pos : [372, 654]
			route : 11
			is_open : false
			cost_to_open : 445
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_TIMBER, RESOURCE_SANDSTONE ]
			buys []
			route_limits [
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}

		{
			name : "Iunet"
			idx : 4
			pos : [783, 892]
			route : 12
			is_open : false
			cost_to_open : 875
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Pwenet"
			idx : 13
			pos : [1133, 1325]
			route : 13
			is_open : false
			cost_to_open : 1255
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS ]
			buys []
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			// Remap: pak sea=0 + route=19 (no polyline). Nearby polyline 20 is
			// sea type=2 at Qadesh — keep is_sea_trade true (triage A).
			name : "Qadesh"
			idx : 14
			pos : [962, 10]
			route : 20
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
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
			// Remap: pak sea=0 + route=19 (no polyline). Nearby polyline 21 is
			// sea type=2 at Byblos — keep is_sea_trade true (triage A).
			name : "Byblos"
			idx : 35
			pos : [873, 72]
			route : 21
			is_open : false
			cost_to_open : 900
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_STRAW, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_LINEN, RESOURCE_GEMS ]
			route_limits [
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}

		{
			name : "Gaza"
			idx : 3
			pos : [846, 280]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Tyre"
			idx : 17
			pos : [877, 121]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Mycenae sea
			type : 2
			points [
				[42, 34], [53, 75], [63, 99], [65, 118], [58, 126], [57, 148], [62, 169], [62, 345],
				[77, 360], [90, 386], [107, 395], [168, 408], [318, 441], [378, 433], [393, 443], [431, 431]
			]
		}
		{
			route : 2 // Knossos sea
			type : 2
			points [
				[198, 139], [226, 137], [266, 141], [273, 156], [306, 438], [336, 439], [381, 430], [389, 441], [432, 436]
			]
		}
		{
			route : 3 // Enkomi sea
			type : 2
			points [
				[707, 72], [725, 81], [731, 90], [856, 198], [849, 207], [852, 217], [833, 269], [836, 295],
				[806, 327], [734, 340], [665, 358], [607, 335], [532, 339], [470, 362], [438, 387], [429, 425]
			]
		}
		{
			route : 4 // Kyrene sea
			type : 2
			points [
				[41, 360], [62, 347], [83, 357], [106, 386], [168, 397], [313, 438], [334, 441], [379, 429], [399, 441], [425, 431]
			]
		}
		{
			route : 5 // Rostja land
			type : 1
			points [ [516, 522], [494, 506], [467, 484], [461, 471], [432, 425] ]
		}
		{
			route : 6 // Men-nefer sea
			type : 2
			points [
				[564, 502], [536, 488], [525, 475], [518, 460], [514, 455], [507, 442], [494, 435], [487, 430], [471, 425], [436, 419]
			]
		}
		{
			route : 7 // Bubastis sea
			type : 2
			points [
				[593, 439], [594, 455], [574, 463], [574, 470], [568, 483], [564, 501], [535, 491], [525, 472],
				[516, 460], [512, 454], [510, 440], [490, 434], [474, 428], [466, 422], [445, 420]
			]
		}
		{
			route : 8 // Rowarty sea
			type : 2
			points [
				[631, 404], [633, 381], [636, 364], [634, 352], [633, 345], [610, 336], [577, 336], [531, 339],
				[497, 352], [475, 360], [438, 387], [431, 420]
			]
		}
		{
			route : 9 // Meidum sea
			type : 2
			points [
				[590, 609], [596, 591], [591, 580], [592, 555], [592, 552], [586, 537], [586, 528], [573, 512],
				[551, 496], [535, 489], [523, 468], [512, 452], [504, 440], [478, 428], [474, 425], [457, 424], [432, 424]
			]
		}
		{
			route : 10 // Menat Khufu sea
			type : 2
			points [
				[583, 738], [568, 719], [568, 715], [571, 669], [586, 647], [585, 629], [593, 613], [597, 591],
				[588, 554], [588, 539], [583, 526], [559, 498], [537, 489], [520, 467], [513, 452], [513, 444],
				[489, 433], [468, 425], [434, 423]
			]
		}
		{
			route : 11 // Bahariya land
			type : 1
			points [
				[396, 669], [401, 650], [403, 640], [400, 608], [395, 593], [388, 581], [390, 559], [393, 553],
				[397, 539], [402, 527], [403, 523], [405, 521], [409, 516], [413, 515], [420, 513], [431, 512],
				[444, 514], [465, 524], [472, 527], [482, 527], [491, 525], [498, 520], [504, 515], [504, 512],
				[494, 503], [486, 501], [465, 481], [463, 478], [444, 450], [437, 422]
			]
		}
		{
			route : 12 // Iunet sea
			type : 2
			points [
				[801, 908], [787, 931], [770, 934], [763, 926], [759, 922], [757, 915], [743, 918], [720, 897],
				[718, 888], [700, 882], [691, 871], [676, 861], [673, 850], [651, 839], [653, 832], [642, 824],
				[631, 824], [613, 815], [597, 798], [596, 779], [588, 739], [567, 718], [570, 691], [574, 657],
				[584, 648], [585, 625], [593, 609], [594, 588], [588, 543], [586, 527], [562, 504], [531, 486],
				[510, 445], [464, 427], [441, 420]
			]
		}
		{
			route : 13 // Pwenet land
			type : 1
			points [
				[1147, 1342], [1103, 1318], [902, 1120], [762, 1036], [620, 895], [558, 765], [500, 598],
				[488, 555], [516, 524], [463, 483], [440, 433]
			]
		}
		{
			route : 20 // Qadesh sea (remap)
			type : 2
			points [
				[969, 27], [880, 61], [877, 90], [851, 235], [811, 315], [763, 338], [660, 356], [607, 336],
				[515, 336], [434, 389], [434, 423]
			]
		}
		{
			route : 21 // Byblos sea (remap)
			type : 2
			points [
				[887, 89], [869, 115], [854, 202], [789, 311], [633, 324], [515, 332], [435, 389], [435, 429]
			]
		}
	]

	hide_pak_objects : true
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
		bricks_leaves_wired : false
		bricks_recurring_last_year : -1
		clay_flood_last_year : -1
		gold_collapse_last_year : -1
		contaminated_last_year : -1
		start_message_shown : false
	}
}

function mission128_ensure_bricks_leaves() {
	if (mission.bricks_leaves_wired) {
		return
	}
	mission.bricks_leaves_wired = true
	city.create_chain_event({
		tag_id: 1001,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 5
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 1002,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 6
	}).set_param("months_initial", 2)
}

function mission128_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag) {
	mission128_ensure_bricks_leaves()
	var request = city.create_good_request({
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months
	})
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return request
}

[es=event_mission_start, mission=mission128]
function mission128_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_0_BARBARIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	// Gods come from Alexandria.map (Osiris/Ra/Ptah known, Bast patron, Seth unknown).
}

// pak i=0: bricks×11 / 12mo recurring from y1m4; ok→KR+5 refuse/late→KR−6
[es=event_advance_month, mission=mission128]
function mission128_bricks_request_recurring(ev) {
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 4)) {
		return
	}
	if (ev.month != 4) {
		return
	}
	if (mission.bricks_recurring_last_year == ev.years_since_start) {
		return
	}
	mission.bricks_recurring_last_year = ev.years_since_start
	var tag = 3000 + ev.years_since_start
	log_info("akhenaten: mission 128 bricks request y" + ev.years_since_start, {ev:ev})
	mission128_fire_request(tag, RESOURCE_BRICKS, 11, 12, 1001, 1002, 1002)
}

// pak i=3: CLAY_PIT_FLOOD amount=5 recurring y6m5+
[es=event_advance_month, mission=mission128]
function mission128_clay_flood_recurring(ev) {
	if (ev.years_since_start < 6 || ev.month != 5) {
		return
	}
	if (mission.clay_flood_last_year == ev.years_since_start) {
		return
	}
	mission.clay_flood_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 3100 + ev.years_since_start,
		type: EVENT_TYPE_CLAY_PIT_FLOOD,
		amount: 5,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=4: GOLD_MINE_COLLAPSE amount=6 recurring y6m4+
[es=event_advance_month, mission=mission128]
function mission128_gold_collapse_recurring(ev) {
	if (ev.years_since_start < 6 || ev.month != 4) {
		return
	}
	if (mission.gold_collapse_last_year == ev.years_since_start) {
		return
	}
	mission.gold_collapse_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 3200 + ev.years_since_start,
		type: EVENT_TYPE_GOLD_MINE_COLLAPSE,
		amount: 6,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// pak i=5: CONTAMINATED_WATER amount=8 recurring y3m9+.
// Triage: omit pak subtype=1 / city / months — unused for this type (editor has
// no Contaminated subtype; engine effect is fixed health drop). amount dump-only.
[es=event_advance_month, mission=mission128]
function mission128_contaminated_water_recurring(ev) {
	if (ev.years_since_start < 3 || ev.month != 9) {
		return
	}
	if (mission.contaminated_last_year == ev.years_since_start) {
		return
	}
	mission.contaminated_last_year = ev.years_since_start
	city.create_chain_event({
		tag_id: 3300 + ev.years_since_start,
		type: EVENT_TYPE_CONTAMINATED_WATER,
		amount: 8,
		trigger: EVENT_TRIGGER_ONCE
	}).execute()
}

// map i=6: the recurring Bedouin raid (Libyan soldiers).
function mission128_raid_list() {
	return [
		{ key: "i6", invasion_id: 6, year: 8, month: 0, invader: EVENT_INVADER_BEDUINS, enemy: ENEMY_7_LIBIAN, amount: 19,
			months_initial: 18, location: [1, -1, 1, 2], attack_target: EVENT_ATTACK_TARGET_RANDOM, recurring: true }
	]
}

[es=event_advance_month, mission=mission128]
function mission128_raids(ev) {
	mission_raids_month(mission, mission128, ev, mission128_raid_list())
}
