log_info("akhenaten: mission 52 actium started")

// Full empire redefine (CC52). Dump 2026-08-01 Cleop.
// MM briefing: message_mission_actium (446) — *Antony and Cleopatra*.
// Pak map subtitle: "The Battle of Actium" (UI uses start_message subtitle).
// Rank 10. Year -35. Enemy ENEMY_9_PERSIAN (briefing Octavian — pak id wins).
// Win: pop 1000 / culture OFF / prosperity OFF / monuments OFF /
//      kingdom 50 / housing 0x lv5 / survival 6y (m 2/4/6).
// Monuments: none. Burial: none. Gods: Ra(2).
// Env: alt_predator=1 (northern); set in on_start.
// Invasions x2 via_sea (loc 9 → sea_point 0); calendar JS (events[] INVASION = no-op).
// Warship editor slot 43 OFF — TEMP on for navy briefing (Tanis pattern).
// SKIP empty map_obj idx=6. Orphan Waset route 17 -> 0.
// next_mission -1 (campaign end — must not spill past 52).

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
	house_tax_multipliers [300, 200, 150, 100, 75]

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
			max_traders : 1
			trade_limits : default_trade_limits
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
			max_traders : 1
			trade_limits : default_trade_limits
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
		start_message_shown : false
		inv12_done : false
		inv12_active : false
		inv12_enemies_seen : false
		inv17_done : false
	}
}

function mission52_sea(i) {
	var pts = [[52, 56], [38, 66]]
	if (i < 0 || i >= pts.length) { return [-1, -1] }
	return pts[i]
}

function mission52_enemy_raid(invasion_id, size, sea_point, on_completed_tag) {
	var sea = mission52_sea(sea_point === undefined ? 0 : sea_point)
	__image_request_pak(PACK_ENEMY_PERSIAN)
	var opts = {
		mode: ATTACK_TYPE_ENEMIES,
		enemy: ENEMY_9_PERSIAN,
		size: size,
		invasion_id: invasion_id,
		want_destroy_buildings: size,
		invasion_attack_target: EVENT_ATTACK_TARGET_TROOPS,
		via_sea: 1,
		sea_point: sea_point === undefined ? 0 : sea_point,
		tilex: sea[0],
		tiley: sea[1]
	}
	// C++ bind fire_chain_by_tag (+ drain) — not __city_event_fire_chain from JS.
	if (on_completed_tag !== undefined && on_completed_tag > 0) {
		opts.on_completed_tag = on_completed_tag
	}
	return city.start_foreign_army_invasion(opts)
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

// Calendar invasions (events[] EVENT_TYPE_INVASION is engine no-op — B2 / CC52.N).
// pak i=12 y4m4 ×19 loc9 sea → wipe → i=17 ×40 → wipe bind → i=18 LOST_TRADE (tag_id 18).
[es=event_advance_month, mission=mission52]
function mission52_calendar_invasions(ev) {
	if (!mission.inv12_done && ev.years_since_start == 4 && ev.month == 4) {
		mission.inv12_done = true
		mission.inv12_active = true
		mission.inv12_enemies_seen = false
		log_info("akhenaten: mission 52 sea invasion ×19 (i=12)")
		mission52_enemy_raid(12, 19, 0)
	}

	if (mission.inv12_active && !mission.inv17_done) {
		if (city.num_enemy_formations > 0) {
			mission.inv12_enemies_seen = true
			return
		}
		if (!mission.inv12_enemies_seen) {
			return
		}
		mission.inv12_active = false
		mission.inv17_done = true
		log_info("akhenaten: mission 52 sea invasion ×40 (i=17) → chain tag 18")
		mission52_enemy_raid(17, 40, 0, 18)
	}
}
