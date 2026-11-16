log_info("akhenaten: mission 30 heh started")

// Mission 30 — Heh (Semna), "The Gauntlet". Rank 10 (Pharaoh).
//
// Goals:     population 6000, culture 50, prosperity 45, monuments 15, kingdom 60, housing level 10.
// Start:     funds 5500, no rescue loan, debt interest 20% (normal difficulty).
// Gods:      Osiris (patron), Ra, Seth.
// Monuments: mausoleum (burial goods: 16 weapons, 8 pottery, 8 beer, 16 gems).
// Trade:     nothing open at start; can open — Buhen (by sea), Byblos (by sea), Dakhla Oasis, Pwenet;
//            opened by events — Men-nefer, Itjtawy (troops delivered), Baki and Sawu (henna delivered);
//            display only — Iken, Kebet, Menat Khufu, Toshka, Waset.
// Enemies:   Kushite raids, mostly by sea; Egyptian army (60, then 60 more) if the kingdom rating
//            falls to 0.
// Timeline:  y0m7 gems price drops, then request 16 troops (sent: kingdom +2, Men-nefer route opens;
//            otherwise kingdom -2 and the request repeats); y2m0 timber price drops, then request
//            24 troops (same pattern, Itjtawy route opens); y3m4 request 27 troops (sent: gift of
//            32 chickpeas; otherwise kingdom -9); y5m0 timber demand rises; y5m10 timber price rises,
//            then request 40 henna (sent: Baki is conquered, Baki and Sawu routes open; otherwise
//            kingdom -5 and the request repeats); y10m6 request 13 chickpeas; y12m9 gift of
//            32 sandstone.
//            Kushite raids (announced, then attacking): 16 by sea with 2 warships y6m11, y7m5; 38 by sea
//            with 6 y8m4, y9m1; 40 by sea with 4 y10m0, y10m9; 40 by land y12m6, y13m3, and as it attacks
//            20 by sea with 2; 16 by land y14m0, y14m6, again every time its army is gone; 60 by sea with 6
//            y16m0, y16m9; 40 by land y19m6, y20m6; 24 by land y21m0, y21m3; 72 by land y40m0, y41m0;
//            72 by sea with 6 y50m7, y51m7; 72 by sea with 7 y60m10, y61m10.
//
// Notes for developers:
// - Raid locations follow OG: 1..8 = land points [80,123] / [112,71] (empty ones wrap round), 9+ = sea
//   point loc - 9 with the event's warships.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields; a recurring
//   raid comes back its year plus the years since start later (OG scenario_events_rearm).
// - The original gives Itjtawy, Men-nefer, Sawu and Baki no goods; goods are filled in so their
//   unlocks are playable (Baki sells sandstone, as the briefing says).
// - tag_id: 1000 + i chained events and requests, 2000 + i calendar events, 7000 + i Egyptian army
//   (i = event index in the original scenario, "pak i=" in comments below).

mission30 { // Heh (Semna) — The Gauntlet
	map_file : "data/maps/m_030_heh.map"

	// Map points from data/maps/m_030_heh.map.
	herd_points_predator [ [12, 72], [100, 33], [100, 40] ]

	start_message : "message_mission_semna"
	selection_title : "Heh"
	player_rank : 10

	// Sibling Bubastis (31); both host choice -> Khmun/Sauty (hidden until scripted).
	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 64]
	choice [
		{
			name : "Khmun"
			id : 32
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 65]
			pos [620, 420]
		}
		{
			name : "Sauty"
			id : 33
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 66]
			pos [640, 480]
		}
	]

	// pak Normal funds=5500 loan=0 debt_interest=20 → int_dcy around Normal.
	initial_funds [11000, 7300, 5500, 3700, 2900]
	rescue_loans [0, 0, 0, 0, 0]
	debt_interest [10, 15, 20, 25, 30]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/230_mission.mp3"
		victory : "Voice/Mission/230_victory.mp3"
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
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM,
		BUILDING_STONE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
		BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
		BUILDING_MAUSOLEUM,
	]

	// Monuments goal 15 = pak; Mausoleum (5) + burial weapons 16/16 (1) → trunc(6.32·√6+0.5)=15.
	win_criteria {
		population    {enabled : true, goal : 6000 }
		culture       {enabled : true, goal : 50 }
		prosperity    {enabled : true, goal : 45 }
		monuments     {enabled : true, goal : 15 }
		kingdom       {enabled : true, goal : 60 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [45, 24]
	exit_point [44, 25]
	river_entry_point [68, 3]
	river_exit_point [75, 7]
	disembark_points [ [80, 84], [54, 67], [61, 46] ]
	invasion_points_land [ [80, 123], [112, 71] ]
	// pak inv_sea water; packed loc3/4 = sea[0]/sea[1] → via_sea (E3c).
	invasion_points_sea [ [127, 84], [95, 4] ]

	hide_pak_burial : true
	burial_provisions [
		{ resource: RESOURCE_WEAPONS, required: 16 }
		{ resource: RESOURCE_POTTERY, required: 8 }
		{ resource: RESOURCE_BEER, required: 8 }
		{ resource: RESOURCE_GEMS, required: 16 }
	]

	enable_scenario_events : true

	events [
		{ // pak i=35
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 60 }
			months_initial : 9
			location_fields [ 4, -1, 4, 5 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7035
			on_completed_action : 1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
		{ // pak i=36
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_EGYPT }
			amount { value : 60 }
			months_initial : 0
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 7036
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
	]

	map_background : {pack:PACK_EMPIRE, id:20}
	hide_pak_cities : true
	cities [
		{
			name : "Heh"
			idx : 3
			pos : [689, 1416]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POMEGRANATES, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_WEAPONS, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_TIMBER, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
		}

		{
			name : "Buhen"
			idx : 0
			pos : [766, 1345]
			route : 5
			is_open : false
			cost_to_open : 150
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_BARLEY, RESOURCE_BEER ]
			buys [ RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 1
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
			]
		}

		{
			name : "Dakhla Oasis"
			idx : 2
			pos : [349, 1037]
			route : 2
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_BRICKS, RESOURCE_TIMBER ]
			buys [ RESOURCE_MEAT, RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 1500 }
			]
		}

		{
			name : "Pwenet"
			idx : 10
			pos : [1133, 1325]
			route : 4
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
			]
		}

		{
			name : "Iken"
			idx : 4
			pos : [735, 1380]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Pak egyptian sells/buys empty; goods for NEW_TRADE (loc=6).
			name : "Itjtawy"
			idx : 5
			pos : [584, 555]
			route : 6
			is_open : false
			cost_to_open : 1400
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_POMEGRANATES, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}

		{
			name : "Kebet"
			idx : 6
			pos : [829, 900]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Pak egyptian sells/buys empty; goods for NEW_TRADE (loc=15).
			name : "Men-nefer"
			idx : 7
			pos : [545, 487]
			route : 15
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LETTUCE, RESOURCE_BRICKS, RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_LETTUCE, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
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
			idx : 8
			pos : [578, 720]
			route : 9
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Pak egyptian sells/buys empty; goods for NEW_TRADE (loc=3).
			name : "Sawu"
			idx : 11
			pos : [907, 834]
			route : 3
			is_open : false
			cost_to_open : 1250
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_WEAPONS ]
			route_limits [
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 1500 }
			]
		}

		{
			name : "Toshka"
			idx : 12
			pos : [789, 1298]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Waset"
			idx : 13
			pos : [811, 968]
			route : 8
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			// Pak foreign sells/buys empty; sandstone from briefing (import after conquer).
			name : "Baki"
			idx : 31
			pos : [914, 1215]
			route : 7
			is_open : false
			cost_to_open : 500
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
			sells [ RESOURCE_SANDSTONE ]
			route_limits [
				{ resource: RESOURCE_SANDSTONE, limit: 2500 }
			]
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [
				[909, 87], [868, 104], [831, 203], [803, 296], [696, 354], [640, 358],
				[592, 402], [556, 476], [583, 526], [586, 546], [592, 562], [596, 600],
				[568, 711], [571, 731], [588, 763], [599, 798], [778, 936], [816, 909],
				[829, 941], [816, 963], [832, 1011], [843, 1022], [858, 1031], [865, 1046],
				[876, 1067], [893, 1195], [905, 1232], [900, 1250], [857, 1328], [848, 1306],
				[819, 1323], [774, 1405], [715, 1446], [663, 1399]
			]
		}
		{
			route : 2
			type : 1
			points [
				[364, 1055], [664, 1400], [713, 1446], [702, 1444]
			]
		}
		{
			route : 3
			type : 2
			points [
				[924, 851], [883, 842], [856, 833], [801, 841], [802, 860], [816, 908],
				[829, 942], [815, 968], [833, 1013], [861, 1035], [877, 1067], [896, 1201],
				[905, 1236], [864, 1318], [848, 1307], [817, 1326], [779, 1397], [743, 1431],
				[715, 1446], [725, 1424]
			]
		}
		{
			route : 4
			type : 1
			points [
				[1153, 1342], [1014, 1480], [844, 1469], [715, 1447], [714, 1447]
			]
		}
		{
			route : 5
			type : 2
			points [
				[789, 1364], [782, 1398], [745, 1430], [715, 1448], [710, 1453]
			]
		}
		{
			route : 6
			type : 2
			points [
				[589, 576], [601, 608], [582, 644], [567, 711], [595, 798], [776, 936],
				[816, 908], [829, 945], [817, 967], [833, 1012], [862, 1037], [864, 1051],
				[879, 1068], [905, 1233], [865, 1320], [849, 1307], [818, 1324], [781, 1398],
				[746, 1430], [714, 1448], [716, 1448]
			]
		}
		{
			route : 7
			type : 2
			points [
				[926, 1229], [906, 1232], [865, 1319], [850, 1306], [816, 1327], [781, 1398],
				[715, 1447], [714, 1448]
			]
		}
		{
			route : 8
			type : 2
			points [
				[689, 1416], [811, 968]
			]
		}
		{
			route : 9
			type : 2
			points [
				[593, 741], [595, 776], [600, 804], [661, 840], [775, 925], [821, 900],
				[832, 928], [837, 944], [827, 986], [840, 1010], [867, 1041], [879, 1080],
				[905, 1234], [868, 1315], [839, 1308], [819, 1326], [781, 1392], [714, 1452],
			]
		}
		{
			route : 12
			type : 2
			points [
				[885, 1281], [879, 1302], [863, 1319], [862, 1319], [849, 1305], [827, 1320],
				[811, 1338], [803, 1345], [792, 1359], [789, 1373], [784, 1387], [781, 1394],
				[775, 1403], [767, 1412], [762, 1417], [755, 1424], [750, 1425], [740, 1431],
				[735, 1435], [727, 1441], [722, 1444], [716, 1445], [715, 1446]
			]
		}
		{
			route : 13
			type : 2
			points [
				[715, 1446], [781, 1397], [823, 1322], [849, 1307], [865, 1321], [905, 1229],
				[878, 1067], [836, 1012], [817, 963], [830, 946], [817, 910], [817, 910],
			]
		}
		{
			route : 14
			type : 1
			points [
				[716, 1446], [670, 1240], [645, 1037], [620, 853], [617, 824], [604, 811],
				[595, 803], [593, 800], [597, 794], [597, 795]
			]
		}
		{
			route : 15
			type : 2
			points [
				[716, 1445], [781, 1392], [834, 1312], [851, 1307], [864, 1320], [908, 1236],
				[874, 1061], [835, 1013], [817, 964], [830, 941], [814, 907], [778, 936],
				[595, 795], [566, 711], [581, 641], [602, 609], [585, 526], [585, 526],
			]
		}
		{
			route : 25
			type : 2
			points [
				[903, 1221], [901, 1246], [887, 1278], [880, 1294], [874, 1311], [858, 1319],
				[851, 1311], [841, 1306], [828, 1316], [812, 1335], [801, 1350], [794, 1364],
				[786, 1379], [780, 1396], [763, 1413], [743, 1430], [710, 1453]
			]
		}
		{
			route : 26
			type : 2
			points [
				[901, 1568], [889, 1577], [870, 1582], [869, 1583], [861, 1586], [855, 1590],
				[835, 1587], [815, 1583], [811, 1580], [794, 1576], [785, 1566], [778, 1562],
				[765, 1556], [759, 1550], [752, 1539], [743, 1532], [736, 1526], [732, 1524],
				[728, 1521], [713, 1505], [715, 1502], [731, 1503], [732, 1485], [717, 1479],
				[712, 1481], [701, 1473], [714, 1453]
			]
		}
		{
			route : 27
			type : 1
			points [
				[920, 1594], [859, 1594], [797, 1587], [798, 1558], [797, 1538], [796, 1519],
				[793, 1508], [790, 1498], [784, 1486], [772, 1478], [739, 1483], [734, 1472],
				[722, 1457]
			]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [534, 426], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [418, 650], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [485, 514], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [547, 566], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [615, 712], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [634, 714], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [511, 485], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [590, 457], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [600, 512], image : "pharaoh_general/empire_bits_00118" }
		{ pos : [499, 557], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [569, 598], image : "pharaoh_general/empire_bits_00128" }
		{ pos : [614, 739], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [511, 533], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [577, 495], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [847, 976], image : "pharaoh_general/empire_bits_00124" }
		{ pos : [825, 1194], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [781, 1324], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [380, 1041], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [881, 901], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [861, 901], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [819, 883], image : "pharaoh_general/empire_bits_00126" }
		{ pos : [670, 889], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 1089], image : "pharaoh_general/empire_bits_00127" }
		{ pos : [842, 961], image : "pharaoh_general/empire_bits_00115" }
		{ pos : [725, 1386], image : "pharaoh_general/empire_bits_00121" }
		{ pos : [877, 843], image : "pharaoh_general/empire_bits_00125" }
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
		{ name : "#upper_egypt", pos : [691, 997] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]
	vars {
		raids : ""
		misc_leaves_wired : false
		troops_i6_leaves_wired : false
		troops_i1_leaves_wired : false
		henna_leaves_wired : false
		chickpeas_leaves_wired : false

		event0_gems_price_done : false
		event5_price_done : false
		event10_troops_done : false
		event14_price_done : false
		event26_sandstone_gift_done : false
		event32_chickpeas_done : false
		event37_demand_done : false


		start_message_shown : false
	}
}

function mission30_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission30_make_chain_request(tag, resource, amount, months, subtype, sender_faction, city_name) {
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

function mission30_fire_simple_event(tag, type, resource, amount, city_name, subtype, ok_tag) {
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
	var ev = city.create_chain_event(opts)
	if (ok_tag !== undefined && ok_tag >= 0) {
		ev.set_completed_action_tag(ok_tag)
	}
	ev.event_is_active = true
	return ev
}

function mission30_fire_request(tag, resource, amount, months, ok_tag, refuse_tag, late_tag, subtype, sender_faction, city_name, defeat_tag) {
	var opts = {
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months,
		trigger: EVENT_TRIGGER_ONCE
	}
	if (subtype !== undefined) {
		opts.subtype = subtype
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	var request = city.create_good_request(opts)
	request.set_sender_faction(sender_faction === undefined ? 0 : sender_faction)
	if (ok_tag !== undefined && ok_tag > 0) {
		request.set_completed_action_tag(ok_tag)
	}
	if (refuse_tag !== undefined && refuse_tag > 0) {
		request.set_refusal_action_tag(refuse_tag)
	}
	if (late_tag !== undefined && late_tag > 0) {
		request.set_too_late_action_tag(late_tag)
	}
	if (defeat_tag !== undefined && defeat_tag > 0) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.event_is_active = true
	return request
}

function mission30_ensure_troops_i1_leaves() {
	if (mission.troops_i1_leaves_wired) {
		return
	}
	mission.troops_i1_leaves_wired = true
	// i=1 troops×16: ok→3 KR+2 →2 NEW_TRADE Men-nefer; refuse/late/defeat→4 KR-2 → re-arm i=1
	var kr = mission30_make_leaf(1003, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 0)
	kr.set_completed_action_tag(1002)
	mission30_make_leaf(1002, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 60, 0, 2, "Men-nefer")
	var kr_down = mission30_make_leaf(1004, EVENT_TYPE_REPUTATION_DECREASE, undefined, 2, 0)
	var troops = mission30_make_chain_request(1001, RESOURCE_TROOPS, 16, 9, 1, 0)
	troops.set_completed_action_tag(1003)
	troops.set_refusal_action_tag(1004)
	troops.set_too_late_action_tag(1004)
	troops.set_defeat_action_tag(1004)
	kr_down.set_completed_action_tag(1001) // pak i=4 ok→1 re-arm
}

function mission30_ensure_troops_i6_leaves() {
	if (mission.troops_i6_leaves_wired) {
		return
	}
	mission.troops_i6_leaves_wired = true
	// i=6 troops×24: ok→7 KR+4 →9 NEW_TRADE Itjtawy; refuse/late/defeat→8 KR-4 → re-arm i=6
	var kr = mission30_make_leaf(1007, EVENT_TYPE_REPUTATION_INCREASE, undefined, 4, 0)
	kr.set_completed_action_tag(1009)
	mission30_make_leaf(1009, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 60, 0, 2, "Itjtawy")
	var kr_down = mission30_make_leaf(1008, EVENT_TYPE_REPUTATION_DECREASE, undefined, 4, 0)
	var troops = mission30_make_chain_request(1006, RESOURCE_TROOPS, 24, 9, 1, 0)
	troops.set_completed_action_tag(1007)
	troops.set_refusal_action_tag(1008)
	troops.set_too_late_action_tag(1008)
	troops.set_defeat_action_tag(1008)
	kr_down.set_completed_action_tag(1006) // pak i=8 ok→6 re-arm
}

function mission30_ensure_henna_leaves() {
	if (mission.henna_leaves_wired) {
		return
	}
	mission.henna_leaves_wired = true
	// i=13 henna×40: ok→16 CONQUERED Baki →17 NEW_TRADE Baki →19 NEW_TRADE Sawu
	// refuse/late/defeat→15 KR-5 → re-arm i=13
	var conquered = mission30_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 60, 0, 1, "Baki")
	conquered.set_completed_action_tag(1017)
	var trade_baki = mission30_make_leaf(1017, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 60, 0, 2, "Baki")
	trade_baki.set_completed_action_tag(1019)
	mission30_make_leaf(1019, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 60, 0, 2, "Sawu")
	var kr_down = mission30_make_leaf(1015, EVENT_TYPE_REPUTATION_DECREASE, undefined, 5, 0)
	var henna = mission30_make_chain_request(1013, RESOURCE_HENNA, 40, 12, 2, 0)
	henna.set_completed_action_tag(1016)
	henna.set_refusal_action_tag(1015)
	henna.set_too_late_action_tag(1015)
	henna.set_defeat_action_tag(1015)
	kr_down.set_completed_action_tag(1013) // pak i=15 ok→13 re-arm
}

function mission30_ensure_chickpeas_leaves() {
	if (mission.chickpeas_leaves_wired) {
		return
	}
	mission.chickpeas_leaves_wired = true
	mission30_make_leaf(1033, EVENT_TYPE_REPUTATION_INCREASE, undefined, 10, 0)
	mission30_make_leaf(1034, EVENT_TYPE_REPUTATION_DECREASE, undefined, 7, 0)
}

function mission30_ensure_misc_leaves() {
	if (mission.misc_leaves_wired) {
		return
	}
	mission.misc_leaves_wired = true
	// i=11 KR-9 after troops i=10 refuse/late/defeat
	mission30_make_leaf(1011, EVENT_TYPE_REPUTATION_DECREASE, undefined, 9, 0)
	// i=12 gift chickpeas×32 after troops i=10 ok
	mission30_make_leaf(1012, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_CHICKPEAS, 32, 0)
	// i=23 / i=36 invasions: JS day-update with loc_tile (not EVENT_TYPE_INVASION leaves)
}

function mission30_ensure_all_leaves() {
	mission30_ensure_misc_leaves()
	mission30_ensure_troops_i1_leaves()
	mission30_ensure_troops_i6_leaves()
	mission30_ensure_henna_leaves()
	mission30_ensure_chickpeas_leaves()
}

[es=event_mission_start, mission=mission30]
function mission30_on_start(ev) {
	__image_request_pak(PACK_ENEMY_KUSHITE)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_semna")
	empire.set_id(20)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_6_KUSHITE)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission30_ensure_all_leaves()
}

[es=event_advance_month, mission=mission30]
function mission30_requests_and_events(ev) {
	mission30_ensure_all_leaves()

	// pak i=0: gems price −2 y0m7 once → chain troops i=1
	if (!mission.event0_gems_price_done && ev.years_since_start == 0 && ev.month == 7) {
		mission.event0_gems_price_done = true
		log_info("akhenaten: mission 30 gems price−2 (i=0) → troops×16")
		mission30_fire_simple_event(2000, EVENT_TYPE_PRICE_DECREASE, RESOURCE_GEMS, 2, undefined, 1, 1001)
	}
	// pak i=5: timber price− ×10 y2m0 → troops i=6
	if (!mission.event5_price_done && ev.years_since_start == 2 && ev.month == 0) {
		mission.event5_price_done = true
		log_info("akhenaten: mission 30 timber price− (i=5) → troops×24")
		mission30_fire_simple_event(2005, EVENT_TYPE_PRICE_DECREASE, RESOURCE_TIMBER, 10, undefined, 0, 1006)
	}
	// pak i=10: troops×27 /9mo y3m4 once
	if (!mission.event10_troops_done && ev.years_since_start == 3 && ev.month == 4) {
		mission.event10_troops_done = true
		log_info("akhenaten: mission 30 troops×27 (i=10)")
		mission30_fire_request(2010, RESOURCE_TROOPS, 27, 9, 1012, 1011, 1011, 1, 0, undefined, 1011)
	}
	// pak i=14: timber price+ ×10 → henna i=13 (Baki conquer chain)
	if (!mission.event14_price_done && ev.years_since_start == 5 && ev.month == 10) {
		mission.event14_price_done = true
		log_info("akhenaten: mission 30 timber price+ (i=14) → henna → conquer Baki")
		mission30_fire_simple_event(2014, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 10, undefined, 0, 1013)
	}
	// pak i=37: timber demand +60 y5m0
	if (!mission.event37_demand_done && ev.years_since_start == 5 && ev.month == 0) {
		mission.event37_demand_done = true
		log_info("akhenaten: mission 30 timber demand +60 (i=37)")
		mission30_fire_simple_event(2037, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 60)
	}
	// pak i=26: gift sandstone×32 once y12m9 (ok=999 terminal)
	if (!mission.event26_sandstone_gift_done && ev.years_since_start == 12 && ev.month == 9) {
		mission.event26_sandstone_gift_done = true
		log_info("akhenaten: mission 30 gift sandstone×32 (i=26)")
		mission30_fire_simple_event(2026, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_SANDSTONE, 32)
	}
	// pak i=32 chickpeas×13 /12mo y10m6
	if (!mission.event32_chickpeas_done && ev.years_since_start == 10 && ev.month == 6) {
		mission.event32_chickpeas_done = true
		log_info("akhenaten: mission 30 chickpeas×13 (i=32)")
		mission30_fire_request(2032, RESOURCE_CHICKPEAS, 13, 12, 1033, 1034, 1034, 5, 0)
	}
}

// pak i=18..31: the Kushite raids; i=22 chains i=23 (delay 0) as it attacks, i=28 recurs.
function mission30_raid_list() {
	var E = EVENT_INVADER_ENEMY
	var K = ENEMY_6_KUSHITE
	return [
		{ key: "i18", invasion_id: 18, year: 6, month: 11, invader: E, enemy: K, amount: 16, months_initial: 6,
			location: [10, 10, -1, -1], warships: 2, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i20", invasion_id: 20, year: 8, month: 4, invader: E, enemy: K, amount: 38, months_initial: 9,
			location: [9, 9, -1, -1], warships: 6, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i21", invasion_id: 21, year: 10, month: 0, invader: E, enemy: K, amount: 40, months_initial: 9,
			location: [9, 9, -1, -1], warships: 4, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i22", invasion_id: 22, year: 12, month: 6, invader: E, enemy: K, amount: 40, months_initial: 9,
			location: [1, -1, 1, 3], attack_target: EVENT_ATTACK_TARGET_RANDOM, then: [{ key: "i23", delay: 0 }] },
		{ key: "i23", invasion_id: 23, invader: E, enemy: K, amount: 20, months_initial: 0,
			location: [9, 9, -1, -1], warships: 2, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i24", invasion_id: 24, year: 16, month: 0, invader: E, enemy: K, amount: 60, months_initial: 9,
			location: [9, 9, -1, -1], warships: 6, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i25", invasion_id: 25, year: 19, month: 6, invader: E, enemy: K, amount: 40, months_initial: 12,
			location: [2, -1, 1, 8], attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i27", invasion_id: 27, year: 21, month: 0, invader: E, enemy: K, amount: 24, months_initial: 3,
			location: [8, 8, -1, -1], attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i28", invasion_id: 28, year: 14, month: 0, invader: E, enemy: K, amount: 16, months_initial: 6,
			location: [6, -1, 1, 8], attack_target: EVENT_ATTACK_TARGET_RANDOM, recurring: true },
		{ key: "i29", invasion_id: 29, year: 40, month: 0, invader: E, enemy: K, amount: 72, months_initial: 12,
			location: [3, -1, 1, 8], attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i30", invasion_id: 30, year: 50, month: 7, invader: E, enemy: K, amount: 72, months_initial: 12,
			location: [9, 9, -1, -1], warships: 6, attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i31", invasion_id: 31, year: 60, month: 10, invader: E, enemy: K, amount: 72, months_initial: 12,
			location: [9, 9, -1, -1], warships: 7, attack_target: EVENT_ATTACK_TARGET_RANDOM }
	]
}

[es=event_advance_month, mission=mission30]
function mission30_raids(ev) {
	mission_raids_month(mission, mission30, ev, mission30_raid_list())
}
