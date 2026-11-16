log_info("akhenaten: mission 52 actium started")

// Mission 52 — Actium, "Antony and Cleopatra". Rank 10 (Pharaoh).
//
// Goals:     population 1000, kingdom 50, housing level 5, survive 6 years.
// Start:     funds 7000, rescue loan 2000, debt interest 3% (normal difficulty); archers and infantry
//            carried over from the previous mission join.
// Gods:      Ra (patron).
// Monuments: none.
// Trade:     can open — Athens, Alexandria (by sea); opened by events — Kyrene; display only — Enkomi, Gaza,
//            Knossos, Men-nefer, Tyre, Meidum, Waset, Buhen, Byblos.
// Enemies:   Persian fleet (the briefing's Octavian), both raids by sea from sea point 0 or 1.
// Timeline:  y1m8 request 5 timber (prices fall, or rise if refused); y2m4 request 6 copper
//            (delivered or late: Kyrene route opens; refused: Alexandria buys less timber); y3m2 famine
//            request for 5 fish (delivered: gift of 5 weapons, kingdom +6; refused: Alexandria route lost);
//            from y3m7 request 16 timber every year (delivered: gift of 7 weapons; late: 5 weapons;
//            refused: kingdom −4); y3m8 sea trade problem; raid 19 with 5 warships announced y4m4, attacks
//            y4m8; 2 months later raid 40 with 4 warships is announced and attacks the month after (y4m11),
//            and as it attacks the Athens route is lost.
//
// Notes for developers:
// - events[] invasions do not run (no favour trigger), so the raids follow the OG invasion cycle from JS
//   (missions.js mission_raids_month: warnings from the event's month, the attack months_initial months
//   later, the point rolled from the event's location_fields); i=12 chains i=17 and i=17 the Athens route
//   loss (tag 18) as they attack.
// - The warship wharf is enabled for the navy briefing although the original scenario disallows it.
// - next_mission -1: the campaign ends here.

mission52 { // Actium - Antony and Cleopatra
	map_file : "data/maps/m_052_actium.map"

	// Map points from data/maps/m_052_actium.map.
	herd_points_prey [ [78, 98] ]

	start_message : "message_mission_actium"
	selection_title : "Actium"
	player_rank : 10
	carry_troops : ["archer", "infantry"]

	next_mission : -1

	// pak Normal funds=7000 loan=2000 debt_interest=3 -> int_dcy around Normal.
	initial_funds [14000, 9330, 7000, 4690, 3710]
	rescue_loans [4000, 2670, 2000, 1340, 1060]
	debt_interest [0, 1, 3, 5, 7]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C52_mission.mp3"
		victory : "Voice/Mission/C52_victory.mp3"
	}

	// buildings[] from pak_editor_allow (19 on) + always infra + Ra temples.
	// TEMP: warship+shipwright (briefing navy; editor slot 43 off) — TODO(NV).
	// OFF: granary/water_supply/tax/palace/mansion/gardens/plaza/statues/wall/
	// gate/ferry/fishing/academy/weaponsmith/music/dance/senet/festival/
	// school/library/zoo/apothecary/irrigation/water_lift.
	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL,
		BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_BAZAAR, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_SHIPWRIGHT, BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_LOW_BRIDGE,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE, BUILDING_COPPER_MINE,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_COMPLEX_RA,
		BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL,
	]

	win_criteria {
		population    {enabled : true, goal : 1000 }
		culture       {enabled : false, goal : 0 }
		prosperity    {enabled : false, goal : 15 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 50 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 5 }
		survival_time {enabled : true, years : 6 }
		milestone25_year : 2
		milestone50_year : 4
		milestone75_year : 6
	}

	entry_point [129, 61]
	exit_point [111, 97]
	river_entry_point [25, 94]
	river_exit_point [89, 120]
	disembark_points [ [61, 74], [59, 63], [55, 50] ]
	invasion_points_land [ [17, 13], [31, 3] ]
	invasion_points_sea [ [52, 56], [38, 66] ]
	fishing_points [ [50, 45], [73, 22] ]
	herd_points_predator [ [78, 98] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_REQUEST
			time { year : 1, month : 8 }
			item { value : RESOURCE_TIMBER }
			amount { value : 5 }
			months_initial : 9
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 1
			on_refusal_action : 2
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=1
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=2
			type : EVENT_TYPE_PRICE_INCREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=3
			type : EVENT_TYPE_PRICE_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=4
			type : EVENT_TYPE_REQUEST
			time { year : 2, month : 4 }
			item { value : RESOURCE_COPPER }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 5
			on_refusal_action : 6
			on_too_late_action : 7
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=5
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 5
		}
		{ // pak i=6
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_TIMBER }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 0
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=7
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 6
		}
		{ // pak i=8
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 2 }
			item { value : RESOURCE_FISH }
			amount { value : 5 }
			months_initial : 6
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 9
			on_refusal_action : 10
			on_too_late_action : 11
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 4
		}
		{ // pak i=9
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 11
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 4
		}
		{ // pak i=10
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=11
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 6 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 1
			city_id : 4
		}
		{ // pak i=12
			type : EVENT_TYPE_INVASION
			time { year : 4, month : 4 }
			item { value : 1 }
			amount { value : 19 }
			months_initial : 4
			location_fields [ 9, -1, 9, 11 ]
			warships : 5
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 17
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 3
		}
		{ // pak i=13
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 7 }
			item { value : RESOURCE_TIMBER }
			amount { value : 16 }
			months_initial : 10
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 14
			on_refusal_action : 19
			on_too_late_action : 16
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=14
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=15
			type : EVENT_TYPE_SEA_TRADE_PROBLEM
			time { year : 3, month : 8 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=16
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=17
			type : EVENT_TYPE_INVASION
			time { year : 2, month : 5 }
			item { value : 1 }
			amount { value : 40 }
			months_initial : 1
			location_fields [ 9, -1, 9, 11 ]
			warships : 4
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 18
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
			invasion_attack_target : 3
		}
		{ // pak i=18 — LOST_TRADE after i=17 wipe (CC52.N fires via tag)
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			tag_id : 18
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 8
		}
		{ // pak i=19
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
	]

	map_background : {pack:PACK_EMPIRE, id:26}

	hide_pak_cities : true
	cities [
		{
			name : "Enkomi"
			idx : 0
			pos : [679, 49]
			route : 0
			trade : false
			cost_to_open : 675
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Gaza"
			idx : 1
			pos : [853, 275]
			route : 0
			trade : false
			cost_to_open : 700
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Knossos"
			idx : 2
			pos : [199, 130]
			route : 2
			trade : false
			cost_to_open : 300
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Kyrene"
			idx : 3
			pos : [22, 341]
			route : 4
			trade : false
			cost_to_open : 310
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Men-nefer"
			idx : 4
			pos : [551, 497]
			route : 0
			trade : false
			cost_to_open : 290
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Athens"
			idx : 5
			pos : [29, 5]
			route : 1
			is_open : false
			cost_to_open : 185
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 4000 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Tyre"
			idx : 7
			pos : [877, 121]
			route : 0
			trade : false
			cost_to_open : 700
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Alexandria"
			idx : 24
			pos : [404, 390]
			route : 3
			is_open : false
			cost_to_open : 525
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_CHICKPEAS, RESOURCE_FISH, RESOURCE_POTTERY ]
			buys [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
			]
		}
		{
			name : "Meidum"
			idx : 28
			pos : [568, 581]
			route : 0
			trade : false
			cost_to_open : 475
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Waset"
			idx : 31
			pos : [830, 937]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Buhen"
			idx : 32
			pos : [763, 1344]
			route : 0
			trade : false
			cost_to_open : 1560
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Byblos"
			idx : 33
			pos : [904, 66]
			route : 0
			trade : false
			cost_to_open : 900
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Actium"
			idx : 34
			pos : [-2, 59]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FISH, RESOURCE_GAMEMEAT, RESOURCE_TIMBER ]
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [52, 34], [68, 65], [69, 102], [55, 124], [38, 130], [22, 116] ]
		}
		{
			route : 2
			type : 2
			points [ [195, 143], [174, 131], [119, 123], [73, 120], [45, 116] ]
		}
		{
			route : 3
			type : 2
			points [ [409, 418], [385, 415], [352, 442], [313, 435], [275, 428], [170, 403], [71, 345], [72, 250], [55, 178], [33, 141], [10, 115] ]
		}
		{
			route : 4
			type : 2
			points [ [7, 110], [18, 159], [24, 221], [25, 313], [38, 327], [42, 343] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [519, 492], image : 13856, expanded_image : 1 }
		{ pos : [503, 495], image : 13855, expanded_image : 0 }
		{ pos : [569, 576], image : 13856, expanded_image : 1 }
		{ pos : [551, 551], image : 13858, expanded_image : 3 }
		{ pos : [518, 496], image : 13864, expanded_image : 9 }
	]
	empire_texts [
		{ name : "#crete", pos : [83, 159] }
		{ name : "#cyprus", pos : [594, 107] }
		{ name : "#eastern_africa", pos : [1051, 1561] }
		{ name : "#eastern_desert", pos : [702, 773] }
		{ name : "#greece", pos : [-10, 66] }
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
	]

	vars {
		raids : ""
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission52]
function mission52_on_start(ev) {
	__image_request_pak(PACK_ENEMY_PERSIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -35
	scenario.alt_predator_type = true
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_actium")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_9_PERSIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak i=12 -> i=17 (2 months on, its time.year) -> i=18.
function mission52_raid_list() {
	var P = ENEMY_9_PERSIAN
	var E = EVENT_INVADER_ENEMY
	return [
		{ key: "i12", invasion_id: 12, year: 4, month: 4, invader: E, enemy: P, amount: 19, months_initial: 4,
			location: [9, -1, 9, 11], warships: 5, attack_target: EVENT_ATTACK_TARGET_TROOPS,
			then: [{ key: "i17", delay: 2 }] },
		{ key: "i17", invasion_id: 17, invader: E, enemy: P, amount: 40, months_initial: 1, location: [9, -1, 9, 11],
			warships: 4, attack_target: EVENT_ATTACK_TARGET_TROOPS, chain_tag: 18 }
	]
}

[es=event_advance_month, mission=mission52]
function mission52_raids(ev) {
	mission_raids_month(mission, mission52, ev, mission52_raid_list())
}
