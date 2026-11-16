log_info("akhenaten: mission 11 serabit khadim started")

// Mission 11 — Serabit Khadim, "The Bedouin of the East". Rank 5 (Royal Mayor).
//
// Goals:     population 2000, kingdom 80, housing level 4.
// Start:     funds 15000, rescue loan 3500, debt interest 20% (normal difficulty).
// Gods:      Seth, Ra.
// Monuments: none.
// Trade:     can open — Men-nefer, Selima Oasis, Abu, Nekhen, Behdet (all by land); Nekhen also opens if
//            the 21 weapons are refused; display only — Byblos, Kerma, Kyrene, Saqqara.
// Enemies:   Libyan raids by land, including a yearly Bedouin raid that uses Libyan soldiers; Pharaoh's
//            army (51, rolled 45-80) if the kingdom rating falls to 0.
// Timeline:  five clay pits flood every year in month 0 from y1; y1m7 Pharaoh gifts 32 chickpeas; request
//            8 copper every year in month 7 from y1; raid 8 (aimed at the treasury) announced y1m10, attacks
//            y3m10; y2m4 Bedouin raid 16 at once, and again every time its army is gone; raid 12 announced
//            y3m3, attacks y4m3; y3m4 request 11 copper and a land trade problem; raid 20 (aimed at food)
//            announced y4m8, attacks y6m8; y5m9 request 13 weapons; raid 28 announced y6m0, attacks y8m0;
//            request 16 luxury goods every year in month 0 from y7; y8m2 request 21 weapons (refused: Kerma
//            under siege, kingdom -8, then the Nekhen route opens); raid 28 announced y8m6, attacks y10m0;
//            raid 32 announced y10m1, attacks y12m1.
//
// Notes for developers:
// - Recurring copper and luxury requests never stack: a new one waits until the open one is cleared
//   plus a month (mission_recurring_request_may_fire).
// - Left out from the original: a clay pit flood dated year 100 and a follow-up of the +6 reward that
//   points at a missing event. The map has no invasion points, so raids come in by the map exit.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields; a recurring
//   raid comes back its year plus the years since start later (OG scenario_events_rearm).
// - tag_id: the shared outcome events 21..30 keep the original event index.

mission11 { // Serabit Khadim — The Bedouin of the East
	map_file : "data/maps/m_011_serabit_khadim.map"

	// Map points from data/maps/m_011_serabit_khadim.map; fixed herd sizes.
	herd_points_predator [
		{ tile: [74, 25], type: FIGURE_HYENA, count: 5, radius: 16 }
	]
	herd_points_prey [
		{ tile: [28, 43], type: FIGURE_OSTRICH, count: 5, radius: 16 }
	]

	start_message : "message_mission_serabit_khadim"
	selection_title : "Serabit Khadim"
	player_rank : 5

	choice_background {pack:PACK_UNLOADED, id:12}
	choice_image1 {pack:PACK_UNLOADED, id:13}
	choice_image1_pos [192, 144]
	choice_title [144, 31]

	choice [
		{
			name : "Buhen"
			id : 13
			image {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip [144, 32]
			pos [620, 420]
		}

		{
			name : "Dahshur"
			id : 14
			image {pack:PACK_UNLOADED, id:20}
			tooltip [144, 33]
			pos [640, 480]
		}
	]

	// pak Normal funds=15000 loan=3500 debt_interest=20 → int_dcy around Normal.
	initial_funds [30000, 20000, 15000, 10000, 8000]
	rescue_loans [7000, 4700, 3500, 2300, 1900]
	debt_interest [10, 15, 20, 25, 30]

	env {
		has_animals : true
		hide_nilometer : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/211_mission.mp3"
		victory : "Voice/Mission/211_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
		BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE, BUILDING_WORK_CAMP,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
		BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
	]

	// Goals match original campaign scenario 11 (housing_level 4; culture/prosperity/monuments off).
	win_criteria {
		population    {enabled : true, goal : 2000 }
		culture       {enabled : false }
		prosperity    {enabled : false }
		monuments     {enabled : false }
		kingdom       {enabled : true, goal : 80 }
		housing_level {enabled : true, goal : 4 }
	}

	// Map points from original campaign scenario 11 (no river / disembark / invasion points).
	entry_point [28, 84]
	exit_point [83, 84]

	enable_scenario_events : true

	events [
		{ // pak i=31
			type : EVENT_TYPE_INVASION
			time { year : 0, month : 0 }
			item { value : EVENT_INVADER_PHARAOH }
			amount { value : 51, min : 45, max : 80 }
			months_initial : 8
			location_fields [ 2, -1, 1, 8 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			tag_id : 7031
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			invasion_attack_target : EVENT_ATTACK_TARGET_RANDOM
		}
	]

	// Empire from original campaign scenario 11 (empire id=8) — full map objects.
	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Serabit Khadim"
			idx : 10
			pos : [801, 552]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GAMEMEAT, RESOURCE_GEMS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_CLAY ]
		}

		{
			name : "Men-nefer"
			idx : 5
			pos : [545, 487]
			route : 1
			is_open : false
			cost_to_open : 350
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_BEER, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Selima Oasis"
			idx : 9
			pos : [614, 1359]
			route : 2
			is_open : false
			cost_to_open : 1100
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}

		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 4
			is_open : false
			cost_to_open : 540
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_STRAW, RESOURCE_FLAX, RESOURCE_LINEN, RESOURCE_GEMS ]
			buys [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 1500 }
				{ resource: RESOURCE_STRAW, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_FLAX, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_GEMS, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}

		{
			name : "Nekhen"
			idx : 7
			pos : [797, 1011]
			route : 6
			is_open : false
			cost_to_open : 400
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_FLAX, RESOURCE_LINEN ]
			buys [ RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_FLAX, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		{
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 7
			is_open : false
			cost_to_open : 500
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_REEDS, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_BRICKS, RESOURCE_LINEN, RESOURCE_GEMS, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 4000 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 1500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_BEER, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 1500 }
				{ resource: RESOURCE_GEMS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 1500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 1500 }
			]
		}

		// Display-only.
		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kerma"
			idx : 3
			pos : [732, 1491]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			name : "Kyrene"
			idx : 4
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}

		{
			// pak route=8 polyline junk (Byblos area) — 2-pt stub ours→Saqqara.
			name : "Saqqara"
			idx : 8
			pos : [512, 534]
			route : 8
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1 // Men-nefer land
			type : 1
			points [
				[585, 503], [612, 474], [634, 453], [666, 428], [690, 430], [706, 444],
				[713, 454], [736, 479], [780, 516], [800, 534], [812, 558]
			]
		}
		{
			route : 2 // Selima Oasis land
			type : 1
			points [
				[625, 1378], [667, 1365], [706, 1358], [746, 1345], [785, 1328], [829, 1307],
				[846, 1297], [878, 1266], [896, 1227], [908, 1205], [1000, 1191], [1050, 1148],
				[1061, 1092], [1011, 978], [975, 908], [934, 853], [899, 811], [845, 740],
				[832, 710], [758, 650], [714, 610], [695, 579], [681, 531], [687, 499],
				[702, 496], [716, 500], [730, 524], [747, 549], [766, 561], [784, 571], [806, 581]
			]
		}
		{
			route : 4 // Abu land
			type : 1
			points [
				[890, 1159], [894, 1136], [886, 1115], [887, 1087], [881, 1051], [874, 1041],
				[862, 1017], [826, 986], [825, 960], [833, 935], [821, 902], [821, 873],
				[811, 859], [808, 835], [801, 825], [788, 780], [780, 750], [766, 721],
				[700, 617], [668, 513], [671, 498], [682, 491], [714, 489], [732, 506],
				[749, 526], [767, 548], [807, 569]
			]
		}
		{
			route : 6 // Nekhen land
			type : 1
			points [
				[815, 1019], [798, 979], [791, 972], [751, 927], [734, 918], [712, 900],
				[607, 819], [566, 774], [549, 691], [554, 644], [618, 494], [649, 457],
				[656, 446], [667, 439], [680, 437], [693, 447], [716, 470], [793, 541], [808, 558]
			]
		}
		{
			route : 7 // Behdet land
			type : 1
			points [
				[859, 1071], [851, 1032], [822, 1002], [811, 988], [811, 968], [814, 919],
				[799, 868], [764, 763], [707, 660], [655, 504], [655, 490], [662, 480],
				[676, 477], [699, 482], [723, 485], [756, 519], [783, 546], [807, 563]
			]
		}
		{
			route : 8 // Saqqara display (pak polyline junk → 2-pt + deviation)
			type : 1
			deviation : 40
			points [ [801, 552], [512, 534] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		// pak: exp_img 5 → bits_119 (37×34); exp_img 6 → bits_120 (29×28); exp_img 3 → bits_117 (28×15).
		{ pos : [710, 921], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [841, 1097], image : "pharaoh_general/empire_bits_00119" }
		{ pos : [519, 496], image : "pharaoh_general/empire_bits_00120" }
		{ pos : [486, 535], image : "pharaoh_general/empire_bits_00117" }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [611, 766] }
		{ name : "#greece", pos : [1, 67] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [442, 451] }
		{ name : "#delta", pos : [518, 362] }
		{ name : "#fayuum", pos : [428, 580] }
		{ name : "#nubia", pos : [806, 1445] }
		{ name : "#palestine", pos : [833, 182] }
		{ name : "#sinai", pos : [739, 445] }
		{ name : "#syria", pos : [1003, 46] }
		{ name : "#upper_egypt", pos : [696, 993] }
		{ name : "#western_desert", pos : [230, 774] }
		{ name : "#lebanon", pos : [877, 109] }
		{ name : "#canaan", pos : [850, 271] }
	]

	vars {
		raids : ""
		shared_request_leaves_wired : false
		pharaoh_gift_chickpeas_done : false
		pharaoh_copper_recurring_last_year : -1
		pharaoh_copper_recurring_was_busy : false
		pharaoh_copper_recurring_idle_since_abs : -1
		pharaoh_requested_copper2 : false
		land_trade_problem_done : false
		clay_pit_flood_last_year : -1
		pharaoh_requested_weapons1 : false
		pharaoh_luxury_recurring_last_year : -1
		pharaoh_luxury_recurring_was_busy : false
		pharaoh_luxury_recurring_idle_since_abs : -1
		pharaoh_requested_weapons2 : false
		start_message_shown : false
	}
}

// Shared ONLY_VIA leaves from pak (copper1/luxury → 21/23/24; copper2/weapons1 → 26/28/25;
// weapons2 refuse → 27→29→30). city/subtype/months from dump (mostly message metadata).
function mission11_ensure_shared_request_leaves() {
	if (mission.shared_request_leaves_wired) {
		return
	}
	mission.shared_request_leaves_wired = true

	// i=21 city=6 Men-nefer; i=23 city=4 Kerma; i=24 city=5 Kyrene
	city.create_chain_event({
		tag_id: 21,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 5,
		city: "Men-nefer"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 23,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 10,
		city: "Kerma"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 24,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 5,
		city: "Kyrene"
	}).set_param("months_initial", 2)

	// i=26 city=7 Nekhen subtype=3; pak ok→99 broken — skip
	city.create_chain_event({
		tag_id: 26,
		type: EVENT_TYPE_REPUTATION_INCREASE,
		amount: 6,
		subtype: 3,
		city: "Nekhen"
	}).set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 25,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 8,
		city: "Nekhen"
	}).set_param("months_initial", 2)
	var demand_copper = city.create_chain_event({
		tag_id: 28,
		type: EVENT_TYPE_DEMAND_DECREASE,
		resource: RESOURCE_COPPER,
		amount: 7,
		city: "Men-nefer"
	})
	demand_copper.set_param("months_initial", 2)
	demand_copper.set_completed_action_tag(25)

	// i=27 city=4 Kerma under siege → i=29 KR−8 Nekhen → i=30 NEW_TRADE Nekhen
	var siege = city.create_chain_event({
		tag_id: 27,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 4, // EVENT_SUBTYPE_CITY_UNDER_SIEGE
		city: "Kerma",
		amount: 8
	})
	siege.set_param("months_initial", 2)
	var kr_after_siege = city.create_chain_event({
		tag_id: 29,
		type: EVENT_TYPE_REPUTATION_DECREASE,
		amount: 8,
		city: "Nekhen"
	})
	kr_after_siege.set_param("months_initial", 2)
	city.create_chain_event({
		tag_id: 30,
		type: EVENT_TYPE_CITY_STATUS_CHANGE,
		subtype: 2, // EVENT_SUBTYPE_NEW_TRADE_ROUTE
		city: "Nekhen",
		amount: 5
	}).set_param("months_initial", 2)
	siege.set_completed_action_tag(29)
	kr_after_siege.set_completed_action_tag(30)
}

// sender_faction: 1=pharaoh (EVENT_FACTION_REQUEST_FROM_PHARAOH), 0=city
function mission11_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, sender_faction) {
	mission11_ensure_shared_request_leaves()
	var request = city.create_good_request({
		tag_id: tag,
		resource: resource,
		amount: amount,
		months_initial: months
	})
	if (sender_faction !== undefined) {
		request.set_sender_faction(sender_faction)
	}
	request.set_completed_action_tag(ok_tag)
	request.set_refusal_action_tag(fail_tag)
	if (late_tag) {
		request.set_too_late_action_tag(late_tag)
	}
	request.execute()
	return request
}

[es=event_mission_start, mission=mission11]
function mission11_on_start(ev) {
	__image_request_pak(PACK_ENEMY_LIBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	mission_show_start_message(mission, "message_mission_serabit_khadim")
	empire.set_id(8)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak: year=1 month=7 gift chickpeas 32 once (no ok/refuse chain).
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_gift_chickpeas(ev) {
	if (mission.pharaoh_gift_chickpeas_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 7)) {
		return
	}
	mission.pharaoh_gift_chickpeas_done = true
	log_info("akhenaten: mission 11 serabit gift chickpeas", {ev:ev})
	// pak i=3: city=8 Saqqara, sender=1, subtype=0, months=14 (metadata; gift pays out immediately)
	var gift = city.create_chain_event({
		tag_id: 200,
		type: EVENT_TYPE_GIFT_FROM_PHARAOH,
		resource: RESOURCE_CHICKPEAS,
		amount: 32,
		subtype: 0,
		city: "Saqqara",
		trigger: EVENT_TRIGGER_ONCE
	})
	gift.set_sender_faction(1)
	gift.set_param("months_initial", 14)
	gift.execute()
}

// Track request idle for recurring copper/luxury (pak: complete ≥1 mo before recur).
[es=event_advance_month, mission=mission11]
function mission11_recurring_request_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_COPPER, "pharaoh_copper_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_LUXURY_GOODS, "pharaoh_luxury_recurring", abs)
}

// pak: year=1+ month=7 copper 8 / 18mo recurring; ok→+5 refuse→−10 late→−5
// Gate: no stack while copper request active (incl. copper2); ≥1 month after clear.
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_copper_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 7) {
		return
	}
	if (mission.pharaoh_copper_recurring_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_COPPER, "pharaoh_copper_recurring", abs)) {
		return
	}
	mission.pharaoh_copper_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 1000 + y * 10
	log_info("akhenaten: mission 11 serabit copper recurring y" + y, {ev:ev})
	mission11_fire_request(base, RESOURCE_COPPER, 8, 18, 21, 23, 24, 1) // pak sender=1 pharaoh
}

// pak: year=3 month=4 copper 11 / 18mo once; ok→+6 refuse→DEMAND copper−7→KR−8 late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_copper2(ev) {
	if (mission.pharaoh_requested_copper2) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 4)) {
		return
	}
	mission.pharaoh_requested_copper2 = true
	log_info("akhenaten: mission 11 serabit copper2 request", {ev:ev})
	mission11_fire_request(2, RESOURCE_COPPER, 11, 18, 26, 28, 25, 0) // pak sender=0 city
}

// pak: year=3 month=4 LAND_TRADE_PROBLEM once amount=8
[es=event_advance_month, mission=mission11]
function mission11_land_trade_problem(ev) {
	if (mission.land_trade_problem_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 4)) {
		return
	}
	mission.land_trade_problem_done = true
	log_info("akhenaten: mission 11 serabit land trade problem", {ev:ev})
	// pak i=4: city=8 Saqqara, sender=0, months=14 (handler always uses fixed 48mo)
	var trade = city.create_chain_event({
		tag_id: 300,
		type: EVENT_TYPE_LAND_TRADE_PROBLEM,
		amount: 8,
		subtype: 0,
		city: "Saqqara",
		trigger: EVENT_TRIGGER_ONCE
	})
	trade.set_sender_faction(0)
	trade.set_param("months_initial", 14)
	trade.execute()
}

// pak i=16–20: year=1+ month=0 CLAY_PIT_FLOOD recurring ×5 (amounts 6/6/8/9/7).
// Each event rubble one random working clay pit (handler ignores amount).
[es=event_advance_month, mission=mission11]
function mission11_clay_pit_flood_recurring(ev) {
	if (ev.years_since_start < 1 || ev.month != 0) {
		return
	}
	if (mission.clay_pit_flood_last_year == ev.years_since_start) {
		return
	}
	mission.clay_pit_flood_last_year = ev.years_since_start
	var y = ev.years_since_start
	var amounts = [6, 6, 8, 9, 7]
	log_info("akhenaten: mission 11 serabit clay pit floods y" + y, {ev:ev})
	for (var i = 0; i < amounts.length; i++) {
		city.create_chain_event({
			tag_id: 800 + y * 10 + i,
			type: EVENT_TYPE_CLAY_PIT_FLOOD,
			amount: amounts[i],
			trigger: EVENT_TRIGGER_ONCE
		}).execute()
	}
}

// pak: year=5 month=9 weapons 13 / 18mo once; ok→+6 refuse→DEMAND copper−7→KR−8 late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_weapons1(ev) {
	if (mission.pharaoh_requested_weapons1) {
		return
	}
	if (ev.years_since_start < 5 || (ev.years_since_start == 5 && ev.month < 9)) {
		return
	}
	mission.pharaoh_requested_weapons1 = true
	log_info("akhenaten: mission 11 serabit weapons1 request", {ev:ev})
	mission11_fire_request(3, RESOURCE_WEAPONS, 13, 18, 26, 28, 25, 0) // pak sender=0 city
}

// pak: year=7+ month=0 luxury 16 / 24mo recurring; ok→+5 refuse→−10 late→−5
// Gate: no stack while luxury request active; ≥1 month after clear.
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_luxury_recurring(ev) {
	if (ev.years_since_start < 7 || ev.month != 0) {
		return
	}
	if (mission.pharaoh_luxury_recurring_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_LUXURY_GOODS, "pharaoh_luxury_recurring", abs)) {
		return
	}
	mission.pharaoh_luxury_recurring_last_year = ev.years_since_start
	var y = ev.years_since_start
	var base = 2000 + y * 10
	log_info("akhenaten: mission 11 serabit luxury recurring y" + y, {ev:ev})
	mission11_fire_request(base, RESOURCE_LUXURY_GOODS, 16, 24, 21, 23, 24, 1) // pak sender=1 pharaoh
}

// pak: year=8 month=2 weapons 21 / 12mo once;
// ok→+6 refuse→Kerma siege→KR−8→NEW_TRADE Nekhen late→KR−8
[es=event_advance_month, mission=mission11]
function mission11_pharaoh_request_weapons2(ev) {
	if (mission.pharaoh_requested_weapons2) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 2)) {
		return
	}
	mission.pharaoh_requested_weapons2 = true
	log_info("akhenaten: mission 11 serabit weapons2 request", {ev:ev})
	mission11_fire_request(5, RESOURCE_WEAPONS, 21, 12, 26, 27, 25, 0) // pak sender=0 city
}

// pak i=5 (the recurring Bedouin event, Libyan soldiers), 6, 8, 9, 12, 14, 15: raids of the scenario enemy.
function mission11_raid_list() {
	var L = ENEMY_7_LIBIAN
	var E = EVENT_INVADER_ENEMY
	return [
		{ key: "i5", invasion_id: 5, year: 2, month: 4, invader: EVENT_INVADER_BEDUINS, enemy: L, amount: 16,
			months_initial: 0, location: [1, -1, 1, 4], attack_target: EVENT_ATTACK_TARGET_RANDOM, recurring: true },
		{ key: "i6", invasion_id: 6, year: 1, month: 10, invader: E, enemy: L, amount: 8, months_initial: 24,
			location: [4, 4, -1, -1], attack_target: EVENT_ATTACK_TARGET_VAULTS },
		{ key: "i8", invasion_id: 8, year: 3, month: 3, invader: E, enemy: L, amount: 12, months_initial: 12,
			location: [3, 3, -1, -1], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
		{ key: "i9", invasion_id: 9, year: 4, month: 8, invader: E, enemy: L, amount: 20, months_initial: 24,
			location: [4, 4, -1, -1], attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i12", invasion_id: 12, year: 6, month: 0, invader: E, enemy: L, amount: 28, months_initial: 24,
			location: [1, 1, -1, -1], attack_target: EVENT_ATTACK_TARGET_VAULTS },
		{ key: "i14", invasion_id: 14, year: 8, month: 6, invader: E, enemy: L, amount: 28, months_initial: 18,
			location: [2, 2, -1, -1], attack_target: EVENT_ATTACK_TARGET_RANDOM },
		{ key: "i15", invasion_id: 15, year: 10, month: 1, invader: E, enemy: L, amount: 32, months_initial: 24,
			location: [3, -1, 3, 4], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS }
	]
}

[es=event_advance_month, mission=mission11]
function mission11_raids(ev) {
	mission_raids_month(mission, mission11, ev, mission11_raid_list())
}
