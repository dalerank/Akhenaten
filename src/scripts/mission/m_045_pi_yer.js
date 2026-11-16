log_info("akhenaten: mission 45 pi-yer started")

// Mission 45 — Pi-Yer, "The Sea People Land". Rank 4 (Royal Judge).
//
// Goals:     population 2500, culture 25, prosperity 30, kingdom 45, 5 houses at housing level 8.
// Start:     funds 10080, rescue loan 3000, debt interest 7% (normal difficulty).
// Gods:      Osiris, Seth.
// Monuments: none.
// Trade:     can open — Enkomi, Byblos, Tyre, Men-nefer, Waset, Kyrene (by sea), Bahariya Oasis,
//            Siwi Oasis, Farafra Oasis; events open Kyrene and close the Kyrene, Farafra and Jericho routes;
//            display only — Djedu, Gaza, Jericho, Menat Khufu, On, Qadesh, Sauty, Sawu, Serabit Khadim,
//            Timna, Buhen, Abu.
// Enemies:   Assyrian raids (the briefing speaks of sea-borne tribes allied with the Libyans), two of them
//            by sea with 3 warships each; one Egyptian raid if Pharaoh's second troop request is refused.
// Timeline:  y1m2 Gaza asks 9 copper, then Kyrene 9 weapons, then Gaza 23 weapons — every path ends with
//            the Farafra Oasis route lost and an Assyrian raid 17 by sea announced a month later, attacking
//            8 months after that, and a month after that attack raid 13 by land is announced (attacks
//            2 months later); y2m6 Pharaoh asks 11 troops for Men-nefer (won: kingdom +14 and a gift of
//            11 weapons; late: kingdom +9 and 7 luxury goods; lost or refused: Jericho route lost); from
//            y3m2 Farafra asks 6 chickpeas every year (delivered: gift of 6 weapons; refused: luxury goods
//            cost more; late: gift of 3 timber); y3m7 battle lost at Farafra, Kyrene route lost; y7m10
//            Farafra asks 8 bricks (delivered or late: Kyrene route opens; refused: Assyrian raid 27 by
//            sea announced 11 months later, attacking 6 months after that); y8m3 Jericho asks 8 papyrus; y11m8 Gaza asks 11 grain (delivered: gift of 9 copper;
//            refused: Kyrene route lost; late: gift of 7 timber); y13m0 Pharaoh asks 12 troops for Gaza
//            (refused: kingdom −10 and Pharaoh's army 12 announced 4 months later, attacking a year after
//            that); from y14m0 Men-nefer asks 6 papyrus every
//            year (gifts of pottery); y15m4 wages rise; y21m2 Pharaoh asks 19 bricks; y24m10 Farafra
//            asks 9 grain.
//
// Notes for developers:
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later; land raids come at the land point [21,27], the sea raids sail
//   from sea point 0 (original location 9).
// - The original allows almost no buildings; the list here follows the briefing (warships, copper and
//   timber imports).
// - tag_id: 1000 + i chain-only events, 2000 + i calendar events, 3000 + i*100 + year repeating requests
//   (i = event index in the original scenario, quoted as "pak i=" below).

mission45 { // Pi-Yer — The Sea People Land
	map_file : "data/maps/m_045_pi_yer.map"

	// Map points from data/maps/m_045_pi_yer.map.
	herd_points_predator [ [21, 46] ]

	start_message : "message_mission_pi_yer"
	selection_title : "Pi-Yer"
	player_rank : 4

	next_mission : 46

	// pak Normal funds=10080 loan=3000 debt_interest=7 → int_dcy around Normal.
	initial_funds [20160, 13400, 10080, 6750, 5340]
	rescue_loans [6000, 4000, 3000, 2000, 1600]
	debt_interest [4, 5, 7, 9, 11]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C45_mission.mp3"
		victory : "Voice/Mission/C45_victory.mp3"
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
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM, BUILDING_CHICKPEAS_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_STONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY,
	]

	win_criteria {
		population    {enabled : true, goal : 2500 }
		culture       {enabled : true, goal : 25 }
		prosperity    {enabled : true, goal : 30 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 45 }
		housing_count {enabled : true, goal : 5 }
		housing_level {enabled : true, goal : 8 }
	}

	entry_point [65, 11]
	exit_point [94, 72]
	river_entry_point [25, 30]
	river_exit_point [84, 81]
	disembark_points [ [46, 59], [51, 63], [56, 67] ]
	invasion_points_land [ [21, 27] ]
	invasion_points_sea [ [75, 28] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:24}
	hide_pak_cities : true
	cities [
		{
			name : "Pi-Yer"
			idx : 12
			pos : [496, 444]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_GRAIN, RESOURCE_CHICKPEAS, RESOURCE_CLAY, RESOURCE_REEDS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
		}
		{
			name : "Enkomi"
			idx : 2
			pos : [679, 49]
			route : 1
			is_open : false
			cost_to_open : 970
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_FISH, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_FIGS, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}
		{
			name : "Byblos"
			idx : 0
			pos : [888, 65]
			route : 2
			is_open : false
			cost_to_open : 880
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_FIGS ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Tyre"
			idx : 17
			pos : [877, 121]
			route : 3
			is_open : false
			cost_to_open : 810
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			buys [ RESOURCE_GRAIN, RESOURCE_LINEN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 7
			pos : [540, 497]
			route : 4
			is_open : false
			cost_to_open : 150
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_CHICKPEAS, RESOURCE_POTTERY ]
			buys [ RESOURCE_BARLEY, RESOURCE_BEER, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Bahariya Oasis"
			idx : 42
			pos : [426, 653]
			route : 5
			is_open : false
			cost_to_open : 215
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_FIGS, RESOURCE_BRICKS ]
			buys [ RESOURCE_FISH, RESOURCE_LUXURY_GOODS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
			]
		}
		{
			name : "Siwi Oasis"
			idx : 40
			pos : [84, 551]
			route : 6
			is_open : false
			cost_to_open : 440
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_FIGS, RESOURCE_BARLEY ]
			buys [ RESOURCE_BRICKS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_BRICKS, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}
		{
			name : "Farafra Oasis"
			idx : 3
			pos : [324, 828]
			route : 7
			is_open : false
			cost_to_open : 475
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_FIGS, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_POTTERY, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 1500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}
		{
			name : "Waset"
			idx : 18
			pos : [816, 958]
			route : 8
			is_open : false
			cost_to_open : 950
			is_sea_trade : true
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_CLAY, RESOURCE_BARLEY ]
			buys [ RESOURCE_FIGS, RESOURCE_POTTERY ]
			route_limits [
				{ resource: RESOURCE_FIGS, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
			]
		}
		{
			name : "Kyrene"
			idx : 6
			pos : [19, 339]
			route : 9
			is_open : false
			cost_to_open : 590
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_STRAW, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_STRAW, limit: 2500 }
				{ resource: RESOURCE_CLAY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Djedu"
			idx : 1
			pos : [535, 389]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Gaza"
			idx : 4
			pos : [846, 280]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Jericho"
			idx : 5
			pos : [896, 233]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Menat Khufu"
			idx : 8
			pos : [587, 721]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "On"
			idx : 10
			pos : [572, 454]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Qadesh"
			idx : 11
			pos : [962, 10]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sauty"
			idx : 13
			pos : [636, 790]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Sawu"
			idx : 14
			pos : [907, 834]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Serabit Khadim"
			idx : 15
			pos : [796, 563]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Timna"
			idx : 16
			pos : [912, 459]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Buhen"
			idx : 38
			pos : [785, 1298]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Abu"
			idx : 39
			pos : [893, 1160]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes [
			{
				route : 1
				type : 2
				points [
					[713, 72], [739, 89], [857, 192], [849, 277], [824, 310], [731, 340],
					[604, 333], [512, 343], [458, 369], [475, 399], [497, 419], [506, 438],
					[516, 448]
				]
			}
			{
				route : 2
				type : 2
				points [
					[885, 89], [867, 122], [854, 177], [841, 270], [816, 304], [730, 334],
					[603, 326], [511, 338], [462, 360], [460, 376], [479, 407], [501, 424],
					[513, 447]
				]
			}
			{
				route : 3
				type : 2
				points [
					[878, 144], [865, 165], [862, 192], [854, 277], [828, 312], [730, 345],
					[604, 337], [512, 348], [465, 371], [470, 395], [497, 420], [513, 447]
				]
			}
			{
				route : 4
				type : 2
				points [
					[587, 528], [575, 518], [571, 505], [556, 498], [535, 489], [526, 477],
					[521, 469]
				]
			}
			{
				route : 5
				type : 1
				points [
					[451, 661], [458, 616], [488, 588], [506, 529], [512, 473]
				]
			}
			{
				route : 6
				type : 1
				points [
					[122, 570], [250, 575], [312, 548], [361, 486], [395, 451], [453, 447],
					[500, 459]
				]
			}
			{
				route : 7
				type : 1
				points [
					[354, 835], [357, 781], [343, 744], [358, 681], [409, 647], [408, 599],
					[443, 562], [496, 523], [505, 473]
				]
			}
			{
				route : 8
				type : 2
				points [
					[819, 971], [826, 943], [812, 906], [774, 937], [757, 916], [748, 919],
					[719, 897], [719, 887], [703, 883], [670, 851], [651, 832], [615, 813],
					[597, 793], [594, 771], [585, 760], [582, 737], [571, 726], [571, 677],
					[584, 642], [584, 629], [598, 610], [598, 595], [593, 585], [585, 527],
					[570, 506], [533, 488], [523, 472]
				]
			}
			{
				route : 9
				type : 2
				points [
					[60, 346], [80, 347], [83, 375], [163, 398], [308, 437], [378, 435],
					[406, 403], [430, 394], [445, 417], [479, 425], [506, 445]
				]
			}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [561, 552], image : "pharaoh_general/empire_bits_00114", expanded_image : 4 }
		{ pos : [507, 490], image : "pharaoh_general/empire_bits_00119", expanded_image : 9 }
		{ pos : [405, 636], image : "pharaoh_general/empire_bits_00120", expanded_image : 10 }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [5, 44] }
		{ name : "#libya", pos : [17, 425] }
		{ name : "#lower_egypt", pos : [426, 481] }
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
		chain_leaves_wired : false

		event0_chickpeas_last_year : -1
		chickpeas_recurring_was_busy : false
		chickpeas_recurring_idle_since_abs : -1

		event5_copper_done : false
		event8_message_done : false
		event12_troops_done : false
		event19_papyrus_done : false
		event23_grain_done : false
		event27_troops_done : false

		event30_papyrus_last_year : -1
		papyrus_recurring_was_busy : false
		papyrus_recurring_idle_since_abs : -1

		event33_wage_done : false
		event34_bricks_done : false
		event36_grain_done : false
		event37_bricks_done : false


		start_message_shown : false
	}
}

function mission45_make_leaf(tag, type, resource, amount, months, subtype, city_name) {
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

function mission45_fire_request(tag, resource, amount, months, ok_tag, fail_tag, late_tag, subtype, sender_faction, defeat_tag, city_name) {
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
	if (defeat_tag) {
		request.set_defeat_action_tag(defeat_tag)
	}
	request.execute()
	return request
}

function mission45_ensure_chain_leaves() {
	if (mission.chain_leaves_wired) {
		return
	}
	mission.chain_leaves_wired = true

	// Chickpeas i=0: ok→1 weapons gift; refuse→2 luxury price+5; late→3 timber gift×3.
	mission45_make_leaf(1001, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_WEAPONS, 6, 12)
	mission45_make_leaf(1002, EVENT_TYPE_PRICE_INCREASE, RESOURCE_LUXURY_GOODS, 5, 12)
	mission45_make_leaf(1003, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_TIMBER, 3, 12)

	// Copper i=5: ok/late→6 weapons×9 (Kyrene); refuse→11 LOST Farafra (ok→invasion×17).
	// weapons×23 ok/refuse/late → 11 LOST Farafra → invasion×17 (pak i=7 city=5 Gaza).
	var weapons9 = city.create_good_request({
		tag_id: 1006, resource: RESOURCE_WEAPONS, amount: 9, months_initial: 5, subtype: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Kyrene"
	})
	weapons9.set_sender_faction(0)
	weapons9.set_completed_action_tag(1007)
	weapons9.set_refusal_action_tag(1011)
	weapons9.set_too_late_action_tag(1011)

	var weapons23 = city.create_good_request({
		tag_id: 1007, resource: RESOURCE_WEAPONS, amount: 23, months_initial: 4, subtype: 6,
		trigger: EVENT_TRIGGER_ONLY_VIA_EVENT, city: "Gaza"
	})
	weapons23.set_sender_faction(0)
	weapons23.set_completed_action_tag(1011)
	weapons23.set_refusal_action_tag(1011)
	weapons23.set_too_late_action_tag(1011)

	// pak i=11 LOST Farafra; ok→i=4 invasion is EVENT_TYPE_INVASION no-op → JS chain on request_cleared.
	mission45_make_leaf(1011, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Farafra Oasis")

	mission45_make_leaf(1010, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 9,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Kyrene")

	// Troops i=12 chain.
	var kr14 = mission45_make_leaf(1013, EVENT_TYPE_REPUTATION_INCREASE, undefined, 14, 12)
	kr14.set_completed_action_tag(1017)
	mission45_make_leaf(1017, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_WEAPONS, 11, 12)
	var msg_lost = mission45_make_leaf(1014, EVENT_TYPE_MESSAGE, undefined, 6, 12,
		EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, "Gaza")
	msg_lost.set_completed_action_tag(1016)
	var kr9 = mission45_make_leaf(1015, EVENT_TYPE_REPUTATION_INCREASE, undefined, 9, 12)
	kr9.set_completed_action_tag(1018)
	mission45_make_leaf(1018, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_LUXURY_GOODS, 7, 12)
	mission45_make_leaf(1016, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Jericho")

	// Papyrus i=19.
	var timber9 = mission45_make_leaf(1020, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_TIMBER, 9, 12)
	timber9.set_completed_action_tag(1022)
	mission45_make_leaf(1021, EVENT_TYPE_REPUTATION_DECREASE, undefined, 7, 12)
	mission45_make_leaf(1022, EVENT_TYPE_REPUTATION_INCREASE, undefined, 5, 12)

	// Grain i=23.
	mission45_make_leaf(1024, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_COPPER, 9, 12)
	mission45_make_leaf(1025, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_LOST_TRADE_ROUTE, "Kyrene")
	mission45_make_leaf(1026, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_TIMBER, 7, 12)

	// Troops i=27 refuse KR−10; pak i=28 ok→29 egypt×12 (INVASION no-op → JS chain).
	mission45_make_leaf(1028, EVENT_TYPE_REPUTATION_DECREASE, undefined, 10, 12)

	// Papyrus recurring gifts.
	mission45_make_leaf(1031, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_POTTERY, 11, 12)
	mission45_make_leaf(1032, EVENT_TYPE_GIFT_FROM_PHARAOH, RESOURCE_POTTERY, 5, 12)

	// Bricks i=34 late KR+2.
	mission45_make_leaf(1035, EVENT_TYPE_REPUTATION_INCREASE, undefined, 2, 12)

	// Bricks i=37 ok/late → NEW_TRADE Kyrene.
	mission45_make_leaf(1038, EVENT_TYPE_CITY_STATUS_CHANGE, undefined, 8, 12,
		EVENT_SUBTYPE_NEW_TRADE_ROUTE, "Kyrene")

}

[es=event_mission_start, mission=mission45]
function mission45_on_start(ev) {
	__image_request_pak(PACK_ENEMY_ASSYRIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -1235
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_pi_yer")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_1_ASSYRIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
	mission45_ensure_chain_leaves()
}

[es=event_advance_month, mission=mission45]
function mission45_recurring_idle_tick(ev) {
	var abs = ev.years_since_start * 12 + ev.month
	mission_recurring_request_update_idle(mission, RESOURCE_CHICKPEAS, "chickpeas_recurring", abs)
	mission_recurring_request_update_idle(mission, RESOURCE_PAPYRUS, "papyrus_recurring", abs)
}

// pak i=0: chickpeas×6/10mo recurring y3m2+.
[es=event_advance_month, mission=mission45]
function mission45_event_i0_chickpeas(ev) {
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 2)) {
		return
	}
	if (ev.month != 2) {
		return
	}
	if (mission.event0_chickpeas_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_CHICKPEAS, "chickpeas_recurring", abs)) {
		return
	}
	mission.event0_chickpeas_last_year = ev.years_since_start
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 chickpeas×6 recurring", {ev:ev})
	// pak i=0 recurring — unique tag per year (do not use 2000+year: clashes with once roots).
	mission45_fire_request(3000 + 0 * 100 + ev.years_since_start, RESOURCE_CHICKPEAS, 6, 10, 1001, 1002, 1003, 0, 0, undefined, "Farafra Oasis")
}

// pak i=5: copper×9/7mo once y1m2 subtype=6.
[es=event_advance_month, mission=mission45]
function mission45_event_i5_copper(ev) {
	if (mission.event5_copper_done) {
		return
	}
	if (ev.years_since_start < 1 || (ev.years_since_start == 1 && ev.month < 2)) {
		return
	}
	mission.event5_copper_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 copper×9", {ev:ev})
	mission45_fire_request(2005, RESOURCE_COPPER, 9, 7, 1006, 1011, 1006, 6, 0, undefined, "Gaza")
}

// pak i=8: MESSAGE battle lost Farafra y3m7 → LOST Kyrene.
[es=event_advance_month, mission=mission45]
function mission45_event_i8_message(ev) {
	if (mission.event8_message_done) {
		return
	}
	if (ev.years_since_start < 3 || (ev.years_since_start == 3 && ev.month < 7)) {
		return
	}
	mission.event8_message_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 message battle lost Farafra", {ev:ev})
	var msg = city.create_chain_event({
		tag_id: 2008, type: EVENT_TYPE_MESSAGE, amount: 8,
		subtype: EVENT_SUBTYPE_MSG_DISTANT_BATTLE_LOST, city: "Farafra Oasis",
		trigger: EVENT_TRIGGER_ONCE
	})
	msg.set_param("months_initial", 12)
	msg.set_completed_action_tag(1010)
	msg.execute()
}

// pak i=12: troops×11/10mo once y2m6 sender=pharaoh subtype=2.
[es=event_advance_month, mission=mission45]
function mission45_event_i12_troops(ev) {
	if (mission.event12_troops_done) {
		return
	}
	if (ev.years_since_start < 2 || (ev.years_since_start == 2 && ev.month < 6)) {
		return
	}
	mission.event12_troops_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 troops×11", {ev:ev})
	mission45_fire_request(2012, RESOURCE_TROOPS, 11, 10, 1013, 1014, 1015, 2, 1, 1016, "Men-nefer")
}

// pak i=19: papyrus×8/10mo once y8m3.
[es=event_advance_month, mission=mission45]
function mission45_event_i19_papyrus(ev) {
	if (mission.event19_papyrus_done) {
		return
	}
	if (ev.years_since_start < 8 || (ev.years_since_start == 8 && ev.month < 3)) {
		return
	}
	mission.event19_papyrus_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 papyrus×8", {ev:ev})
	mission45_fire_request(2019, RESOURCE_PAPYRUS, 8, 10, 1020, 1021, 1022, 0, 0, undefined, "Jericho")
}

// pak i=23: grain×11/7mo once y11m8 subtype=5.
[es=event_advance_month, mission=mission45]
function mission45_event_i23_grain(ev) {
	if (mission.event23_grain_done) {
		return
	}
	if (ev.years_since_start < 11 || (ev.years_since_start == 11 && ev.month < 8)) {
		return
	}
	mission.event23_grain_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 grain×11", {ev:ev})
	mission45_fire_request(2023, RESOURCE_GRAIN, 11, 7, 1024, 1025, 1026, 5, 0, undefined, "Gaza")
}

// pak i=27: troops×12/5mo once y13m0 sender=pharaoh subtype=1.
[es=event_advance_month, mission=mission45]
function mission45_event_i27_troops(ev) {
	if (mission.event27_troops_done) {
		return
	}
	if (ev.years_since_start < 13) {
		return
	}
	mission.event27_troops_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 troops×12", {ev:ev})
	mission45_fire_request(2027, RESOURCE_TROOPS, 12, 5, 1013, 1028, 1021, 1, 1, undefined, "Gaza")
}

// pak i=30: papyrus×6/8mo recurring y14m0+.
[es=event_advance_month, mission=mission45]
function mission45_event_i30_papyrus(ev) {
	if (ev.years_since_start < 14) {
		return
	}
	if (ev.month != 0) {
		return
	}
	if (mission.event30_papyrus_last_year == ev.years_since_start) {
		return
	}
	var abs = ev.years_since_start * 12 + ev.month
	if (!mission_recurring_request_may_fire(mission, RESOURCE_PAPYRUS, "papyrus_recurring", abs)) {
		return
	}
	mission.event30_papyrus_last_year = ev.years_since_start
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 papyrus×6 recurring", {ev:ev})
	// pak i=30 recurring — unique tag per year.
	mission45_fire_request(3000 + 30 * 100 + ev.years_since_start, RESOURCE_PAPYRUS, 6, 8, 1031, 1021, 1032, 0, 0, undefined, "Men-nefer")
}

// pak i=33: wage +3 once y15m4.
[es=event_advance_month, mission=mission45]
function mission45_event_i33_wage(ev) {
	if (mission.event33_wage_done) {
		return
	}
	if (ev.years_since_start < 15 || (ev.years_since_start == 15 && ev.month < 4)) {
		return
	}
	mission.event33_wage_done = true
	log_info("akhenaten: mission 45 wage +3", {ev:ev})
	var wage = city.create_chain_event({
		tag_id: 2033, type: EVENT_TYPE_WAGE_INCREASE, amount: 3, trigger: EVENT_TRIGGER_ONCE
	})
	wage.execute()
}

// pak i=34: bricks×19/12mo once y21m2 sender=pharaoh subtype=4.
[es=event_advance_month, mission=mission45]
function mission45_event_i34_bricks(ev) {
	if (mission.event34_bricks_done) {
		return
	}
	if (ev.years_since_start < 21 || (ev.years_since_start == 21 && ev.month < 2)) {
		return
	}
	mission.event34_bricks_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 bricks×19", {ev:ev})
	mission45_fire_request(2034, RESOURCE_BRICKS, 19, 12, 1022, 1021, 1035, 4, 1, undefined, "Men-nefer")
}

// pak i=36: grain×9/8mo once y24m10 subtype=5.
[es=event_advance_month, mission=mission45]
function mission45_event_i36_grain(ev) {
	if (mission.event36_grain_done) {
		return
	}
	if (ev.years_since_start < 24 || (ev.years_since_start == 24 && ev.month < 10)) {
		return
	}
	mission.event36_grain_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 grain×9", {ev:ev})
	mission45_fire_request(2036, RESOURCE_GRAIN, 9, 8, 1031, 1021, 1022, 5, 0, undefined, "Farafra Oasis")
}

// pak i=37: bricks×8/10mo once y7m10 subtype=4.
[es=event_advance_month, mission=mission45]
function mission45_event_i37_bricks(ev) {
	if (mission.event37_bricks_done) {
		return
	}
	if (ev.years_since_start < 7 || (ev.years_since_start == 7 && ev.month < 10)) {
		return
	}
	mission.event37_bricks_done = true
	mission45_ensure_chain_leaves()
	log_info("akhenaten: mission 45 bricks×8", {ev:ev})
	// refuse → invasion via event_request_cleared (JS chain); no leaf 1039.
	mission45_fire_request(2037, RESOURCE_BRICKS, 8, 10, 1038, 0, 1038, 4, 0, undefined, "Farafra Oasis")
}

// Chain-only invasions after request outcomes.
[es=event_request_cleared, mission=mission45]
function mission45_on_request_cleared(ev) {
	var outcome = mission_request_outcome(ev)

	// pak: copper refuse / weapons×9 refuse|late / weapons×23 any → LOST Farafra (1011) → raid i=4.
	if (ev.tag_id == 2005 && outcome == "refuse"
			|| ev.tag_id == 1006 && (outcome == "refuse" || outcome == "late")
			|| ev.tag_id == 1007 && (outcome == "ok" || outcome == "refuse" || outcome == "late")) {
		mission_raid_schedule(mission, mission45_raid_list(), "i4", 1)
		return
	}
	// pak i=27 refused → i=28 kingdom −10 → i=29 Pharaoh's army.
	if (ev.tag_id == 2027 && outcome == "refuse") {
		mission_raid_schedule(mission, mission45_raid_list(), "i29", 4)
		return
	}
	if (ev.tag_id == 2037 && outcome == "refuse") {
		mission_raid_schedule(mission, mission45_raid_list(), "i39", 11)
	}
}

// pak i=4 (chains i=9 as it attacks), i=29, i=39: the raids the request outcomes send; delays are their time.year.
function mission45_raid_list() {
	var A = ENEMY_1_ASSYRIAN
	var E = EVENT_INVADER_ENEMY
	return [
		{ key: "i4", invasion_id: 4, invader: E, enemy: A, amount: 17, months_initial: 8, location: [9, 9, -1, -1],
			warships: 3, attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS, then: [{ key: "i9", delay: 1 }] },
		{ key: "i9", invasion_id: 9, invader: E, enemy: A, amount: 13, months_initial: 2, location: [1, 1, -1, -1],
			attack_target: EVENT_ATTACK_TARGET_FOOD },
		{ key: "i29", invasion_id: 29, invader: EVENT_INVADER_PHARAOH, enemy: ENEMY_3_EGYPTIAN, amount: 12,
			months_initial: 12, location: [2, 2, -1, -1], attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS },
		{ key: "i39", invasion_id: 39, invader: E, enemy: A, amount: 27, months_initial: 6, location: [9, 9, -1, -1],
			warships: 3, attack_target: EVENT_ATTACK_TARGET_RANDOM }
	]
}

[es=event_advance_month, mission=mission45]
function mission45_raids(ev) {
	mission_raids_month(mission, mission45, ev, mission45_raid_list())
}
