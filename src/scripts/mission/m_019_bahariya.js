log_info("akhenaten: mission 19 bahariya started")

// Mission 19 — Bahariya Oasis, "The Western Desert". Rank 6 (Royal Governor).
//
// Goals:     population 3000, culture 15, prosperity 25, monuments 13, kingdom 40, housing level 10.
// Start:     funds 7500, rescue loan 2500, debt interest 20% (normal difficulty).
// Gods:      Ra, Seth.
// Monuments: Sun Temple.
// Trade:     nothing open at start; can open — On, Iunet, Abu, Serabit Khadim; opened by events —
//            Dahshur (y1m1); display only — Men-nefer, Buhen, Byblos, Dunqul Oasis, Henen-nesw,
//            Kharga Oasis, Nekhen, Saqqara.
// Enemies:   Hyksos raids and Bedouin raids, all by land and growing to 96 soldiers; Pharaoh's army
//            (76) if the kingdom rating falls to 0. No requests in this mission.
// Timeline:  raids are given by the month they are announced, attacking 2 months later unless noted: y1m1
//            Dahshur route opens; y2m0 Hyksos raid 8 (attacks y3m0, with a gift of 24 sandstone); y5m9
//            Hyksos 8 (attacks at once; 7 months later another Hyksos 16 is announced); y7m4 Hyksos 16;
//            y8m0 more timber demand (again as each Hyksos 16 and the Hyksos 32 attack); y8m10 Bedouin 16;
//            y9m2 Hyksos 32 (attacks y10m2); y11m6 Hyksos 64; y11m9 timber dearer; y12m3 Bedouin 32;
//            y13m7 less grain demand; y14m0 Bedouin 64; y14m11 land trade trouble; y17m4 Hyksos 80; y17m9
//            Bedouin 32; y21m2 Hyksos 96; y22m1 Hyksos 48; y22m6 Bedouin 32; y26m3 Hyksos 80; y26m10
//            Hyksos 48; y27m4 land trade trouble; y27m3 Bedouin 32; y31m1 Hyksos 64; y31m4 Hyksos 96;
//            y31m10 Bedouin 48; every m8 from y39 contaminated water; y46m5 Hyksos 64 (attacks y46m11).
//            The y26m10, y27m3, y31m10 and y46m5 raids come back each time their army is gone.
//
// Notes for developers:
// - The original's raids name a generic "enemy"; they use the scenario enemy (Hyksos). Bedouins use the
//   Libyan army sprites.
// - The map has no invasion, river or disembark points, so raids come in by the map exit.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields; a recurring
//   raid comes back its year plus the years since start later (OG scenario_events_rearm). OG invasion_attack
//   chains on_completed as the army attacks without the chain-only check: i=0 sends a copy of i=1 (Hyksos 16,
//   7 months on), i=1 and i=4 more timber demand (pak i=2), i=26 the sandstone gift.
// - tag_id: 1027 the sandstone gift, 2000 + i calendar events, 3000 + i*100 + year yearly events,
//   7000 + i Pharaoh's army (i = event index in the original scenario, also quoted as "pak i=" in
//   comments below).

mission19 { // Bahariya Oasis — The Western Desert
	map_file : "data/maps/m_019_bahariya.map"

	// Map points from data/maps/m_019_bahariya.map.
	herd_points_predator [ [92, 64] ]
	herd_points_prey [ [69, 70], [93, 97] ]

	start_message : "message_mission_bahariya_oasis"
	selection_title : "Bahariya"
	player_rank : 6

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 46]
	choice [
		{
			name : "Dunqul"
			id : 21
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 47]
			pos [620, 420]
		}
		{
			name : "Dakhla"
			id : 22
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 48]
			pos [640, 480]
		}
	]

	// pak Normal funds=7500 loan=2500 debt_interest=20 → int_dcy around Normal.
	initial_funds [15000, 10000, 7500, 5000, 4000]
	rescue_loans [5000, 3300, 2500, 1700, 1300]
	debt_interest [10, 15, 20, 25, 30]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/219_mission.mp3"
		victory : "Voice/Mission/219_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST,
		BUILDING_WELL, BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_CLAY_PIT,
		BUILDING_SUN_TEMPLE,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	// Goals vs pak; monuments 13 = Sun Temple (4).
	win_criteria {
		population    {enabled : true, goal : 3000 }
		culture       {enabled : true, goal : 15 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : true, goal : 40 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [137, 67]
	exit_point [84, 14]

	enable_scenario_events : true

	events [
		{ // pak i=25
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_PHARAOH }
			amount { value : 76, min : 60, max : 80 }
			months_initial : 2
			location_fields [ 1, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7025
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
			name : "Bahariya Oasis"
			idx : 1
			pos : [372, 654]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_TIMBER ]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 3
			is_open : false
			cost_to_open : 800
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_GRANITE, RESOURCE_SANDSTONE ]
			buys [ RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_SANDSTONE, limit: 4000 }
			]
		}

		{
			name : "Iunet"
			idx : 7
			pos : [783, 892]
			route : 2
			is_open : false
			cost_to_open : 600
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_LIMESTONE, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys [ RESOURCE_STRAW ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_LIMESTONE, limit: 4000 }
				{ resource: RESOURCE_GRANITE, limit: 4000 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "On"
			idx : 12
			pos : [572, 454]
			route : 1
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_MEAT, RESOURCE_CLAY, RESOURCE_REEDS, RESOURCE_LIMESTONE ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_GRANITE ]
			route_limits [
				{ resource: RESOURCE_MEAT, limit: 1500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 4000 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 4000 }
				{ resource: RESOURCE_LIMESTONE, limit: 2500 }
				{ resource: RESOURCE_GRANITE, limit: 2500 }
			]
		}

		{
			name : "Serabit Khadim"
			idx : 14
			pos : [801, 552]
			route : 4
			is_open : false
			cost_to_open : 950
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GEMS, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_CLAY ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 4000 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}

		{
			name : "Dahshur"
			idx : 4
			pos : [578, 525]
			route : 17
			cost_to_open : 290
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Men-nefer"
			idx : 9
			pos : [542, 477]
			route : 19
			trade : false
			type : EMPIRE_CITY_PHARAOH
		}

		{
			name : "Buhen"
			idx : 2
			pos : [766, 1345]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Byblos"
			idx : 3
			pos : [891, 68]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Dunqul Oasis"
			idx : 5
			pos : [795, 1191]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Henen-nesw"
			idx : 6
			pos : [534, 626]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Kharga Oasis"
			idx : 8
			pos : [626, 1119]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Nekhen"
			idx : 11
			pos : [797, 1011]
			route : 0
			is_sea_trade : true
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}

		{
			name : "Saqqara"
			idx : 13
			pos : [523, 539]
			route : 0
			is_sea_trade : true
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
				[592, 478], [610, 519], [607, 562], [611, 591], [608, 620], [600, 637],
				[592, 656], [581, 674], [553, 677], [427, 680], [396, 681]
			]
		}
		{
			route : 2
			type : 1
			points [
				[802, 911], [775, 922], [764, 909], [730, 881], [691, 850], [663, 827],
				[634, 808], [619, 804], [603, 813], [589, 811], [579, 798], [553, 740],
				[537, 725], [526, 721], [503, 713], [396, 684]
			]
		}
		{
			route : 3
			type : 1
			points [
				[885, 1172], [871, 1141], [869, 1100], [858, 1066], [849, 1042], [837, 1028],
				[808, 998], [749, 934], [652, 858], [586, 818], [565, 790], [547, 747],
				[541, 738], [529, 734], [448, 704], [395, 686]
			]
		}
		{
			route : 4
			type : 1
			points [
				[813, 565], [784, 565], [763, 556], [742, 545], [729, 520], [722, 503],
				[711, 493], [699, 491], [686, 500], [677, 525], [677, 547], [693, 576],
				[715, 603], [718, 619], [717, 630], [707, 647], [695, 663], [676, 684],
				[656, 697], [638, 706], [611, 703], [583, 706], [546, 706], [502, 699],
				[394, 681]
			]
		}
		{
			route : 17
			type : 1
			points [
				[593, 545], [576, 551], [568, 559], [565, 575], [564, 589], [556, 602],
				[540, 609], [523, 617], [498, 627], [468, 629], [460, 632], [446, 640],
				[431, 651], [423, 655], [417, 659], [396, 668]
			]
		}
		{
			// Men-nefer display — no pak polyline; 2-pt stub.
			route : 19
			type : 1
			deviation : 40
			points [ [542, 477], [372, 654] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [519, 491], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [498, 551], image : "pharaoh_general/empire_bits_00117" }
		{ pos : [602, 443], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [611, 527], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [571, 594], image : "pharaoh_general/empire_bits_00116" }
		{ pos : [511, 520], image : "pharaoh_general/empire_bits_00114" }
		{ pos : [482, 507], image : "pharaoh_general/empire_bits_00123" }
		{ pos : [821, 886], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [844, 1087], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [720, 913], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [785, 1327], image : "pharaoh_general/empire_bits_00122" }
		{ pos : [631, 544], image : "pharaoh_general/empire_bits_00118" }
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
		event2_demand_done : false
		event6_price_done : false
		event8_demand_done : false
		event10_trade_done : false
		event16_water_last_year : -1
		event20_trade_done : false
		event28_trade_done : false



		gift_sandstone_wired : false
		start_message_shown : false
	}
}

function mission19_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission19_fire_simple_event(tag, type, resource, amount, city_name) {
	var opts = { tag_id: tag, type: type, amount: amount, trigger: EVENT_TRIGGER_ONCE }
	if (resource !== undefined) {
		opts.resource = resource
	}
	if (city_name !== undefined) {
		opts.city = city_name
	}
	city.create_chain_event(opts).execute()
}

function mission19_ensure_gift_leaf() {
	if (mission.gift_sandstone_wired) {
		return
	}
	mission.gift_sandstone_wired = true
	// pak i=27: gift sandstone×24 after wipe i=26.
	mission19_make_leaf(1027, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_SANDSTONE, 24, 2)
}

[es=event_mission_start, mission=mission19]
function mission19_on_start(ev) {
	__image_request_pak(PACK_ENEMY_HYKSOS)
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	__image_request_pak(PACK_SUN_TEMPLE_1)
	__image_request_pak(PACK_SUN_TEMPLE_2)
	__image_request_pak(PACK_SUN_TEMPLE_3)
	__image_request_pak(PACK_SUN_TEMPLE_EXTRA)
	mission_show_start_message(mission, "message_mission_bahariya_oasis")
	empire.set_id(18)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_5_HYKSOS)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission19_ensure_gift_leaf()
}

function mission19_maybe_year_month(ev, year, month) {
	return ev.years_since_start == year && ev.month == month
}

[es=event_advance_month, mission=mission19]
function mission19_economy(ev) {
	// Economy once
	if (!mission.event2_demand_done && mission19_maybe_year_month(ev, 8, 0)) {
		mission.event2_demand_done = true
		mission19_fire_simple_event(2002, EVENT_TYPE_DEMAND_INCREASE, RESOURCE_TIMBER, 10)
	}
	if (!mission.event6_price_done && mission19_maybe_year_month(ev, 11, 9)) {
		mission.event6_price_done = true
		mission19_fire_simple_event(2006, EVENT_TYPE_PRICE_INCREASE, RESOURCE_TIMBER, 5)
	}
	if (!mission.event8_demand_done && mission19_maybe_year_month(ev, 13, 7)) {
		mission.event8_demand_done = true
		mission19_fire_simple_event(2008, EVENT_TYPE_DEMAND_DECREASE, RESOURCE_GRAIN, 8)
	}
	if (!mission.event10_trade_done && mission19_maybe_year_month(ev, 14, 11)) {
		mission.event10_trade_done = true
		mission19_fire_simple_event(2010, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 9)
	}
	if (!mission.event20_trade_done && mission19_maybe_year_month(ev, 27, 4)) {
		mission.event20_trade_done = true
		mission19_fire_simple_event(2020, EVENT_TYPE_LAND_TRADE_PROBLEM, undefined, 9)
	}
	if (!mission.event28_trade_done && mission19_maybe_year_month(ev, 1, 1)) {
		mission.event28_trade_done = true
		city.create_chain_event({
			tag_id: 2028,
			type: EVENT_TYPE_CITY_STATUS_CHANGE,
			amount: 8,
			trigger: EVENT_TRIGGER_ONCE,
			subtype: EVENT_SUBTYPE_NEW_TRADE_ROUTE,
			city: "Dahshur"
		}).execute()
	}
	if (mission.event16_water_last_year != ev.years_since_start
			&& ev.years_since_start >= 39 && ev.month == 8) {
		mission.event16_water_last_year = ev.years_since_start
		mission19_fire_simple_event(3000 + 16 * 100 + ev.years_since_start,
			EVENT_TYPE_CONTAMINATED_WATER, undefined, 7)
	}
}

function mission19_timber_demand() {
	return { tag_id: 1002, type: EVENT_TYPE_DEMAND_INCREASE, resource: RESOURCE_TIMBER, amount: 10 }
}

function mission19_raid_i26_chain() {
	mission19_ensure_gift_leaf()
	__city_event_fire_chain(1027)
}

// The Hyksos (scenario enemy) and Bedouin (Libyan soldiers) events of the original, by pak index.
function mission19_raid_list() {
	var H = ENEMY_5_HYKSOS
	var L = ENEMY_7_LIBIAN
	var E = EVENT_INVADER_ENEMY
	var B = EVENT_INVADER_BEDUINS
	return [
		{ key: "i0", invasion_id: 0, year: 5, month: 9, enemy: H, invader: E, amount: 8, months_initial: 0,
			location: [1, 1, -1, -1], attack_target: EVENT_ATTACK_TARGET_RANDOM,
			then: [{ key: "i1_copy", delay: 7 }] },
		{ key: "i1", invasion_id: 1, year: 7, month: 4, enemy: H, invader: E, amount: 16, months_initial: 2,
			location: [1, 1, -1, -1], attack_target: EVENT_ATTACK_TARGET_FOOD,
			chain_event: mission19_timber_demand() },
		{ key: "i3", invasion_id: 3, year: 8, month: 10, enemy: L, invader: B, amount: 16, months_initial: 2,
			location: [8, 8, -1, -1], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i4", invasion_id: 4, year: 9, month: 2, enemy: H, invader: E, amount: 32, months_initial: 12,
			location: [3, 3, -1, -1], attack_target: EVENT_ATTACK_TARGET_VAULTS,
			chain_event: mission19_timber_demand() },
		{ key: "i5", invasion_id: 5, year: 11, month: 6, enemy: H, invader: E, amount: 64, months_initial: 2,
			location: [2, 2, -1, -1], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
		{ key: "i7", invasion_id: 7, year: 12, month: 3, enemy: L, invader: B, amount: 32, months_initial: 2,
			location: [7, 7, -1, -1], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i9", invasion_id: 9, year: 14, month: 0, enemy: L, invader: B, amount: 64, months_initial: 2,
			location: [7, -1, 6, 8], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i11", invasion_id: 11, year: 17, month: 4, enemy: H, invader: E, amount: 80, months_initial: 2,
			location: [1, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_TROOPS },
		{ key: "i12", invasion_id: 12, year: 17, month: 9, enemy: L, invader: B, amount: 32, months_initial: 2,
			location: [7, -1, 4, 8], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i13", invasion_id: 13, year: 21, month: 2, enemy: H, invader: E, amount: 96, months_initial: 2,
			location: [1, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_VAULTS },
		{ key: "i14", invasion_id: 14, year: 22, month: 1, enemy: H, invader: E, amount: 48, months_initial: 2,
			location: [3, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
		{ key: "i15", invasion_id: 15, year: 22, month: 6, enemy: L, invader: B, amount: 32, months_initial: 2,
			location: [5, -1, 4, 8], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i17", invasion_id: 17, year: 26, month: 3, enemy: H, invader: E, amount: 80, months_initial: 2,
			location: [3, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_TROOPS },
		{ key: "i18", invasion_id: 18, year: 26, month: 10, enemy: H, invader: E, amount: 48, months_initial: 2,
			location: [2, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_FOOD, recurring: true },
		{ key: "i19", invasion_id: 19, year: 27, month: 3, enemy: L, invader: B, amount: 32, months_initial: 2,
			location: [5, -1, 4, 8], attack_target: EVENT_ATTACK_TARGET_FOOD, recurring: true },
		{ key: "i21", invasion_id: 21, year: 31, month: 1, enemy: H, invader: E, amount: 64, months_initial: 2,
			location: [3, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_VAULTS },
		{ key: "i22", invasion_id: 22, year: 31, month: 4, enemy: H, invader: E, amount: 96, months_initial: 2,
			location: [3, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
		{ key: "i23", invasion_id: 23, year: 31, month: 10, enemy: L, invader: B, amount: 48, months_initial: 2,
			location: [4, -1, 4, 8], attack_target: EVENT_ATTACK_TARGET_FOOD, recurring: true },
		{ key: "i24", invasion_id: 24, year: 46, month: 5, enemy: H, invader: E, amount: 64, months_initial: 6,
			location: [2, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_FOOD, recurring: true },
		{ key: "i26", invasion_id: 26, year: 2, month: 0, enemy: H, invader: E, amount: 8, months_initial: 12,
			location: [2, -1, 1, 8], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS,
			on_attack: mission19_raid_i26_chain },
		{ key: "i1_copy", invasion_id: 41, enemy: H, invader: E, amount: 16, months_initial: 2,
			location: [1, 1, -1, -1], attack_target: EVENT_ATTACK_TARGET_FOOD, chain_event: mission19_timber_demand() }
	]
}

[es=event_advance_month, mission=mission19]
function mission19_raids(ev) {
	mission_raids_month(mission, mission19, ev, mission19_raid_list())
}
