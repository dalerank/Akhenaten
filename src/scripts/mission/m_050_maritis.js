log_info("akhenaten: mission 50 maritis started")

// Mission 50 — Maritis, "Caesar and Cleopatra". Rank 1 (Village Noble).
//
// Goals:     population 1000, culture 10, prosperity 25, kingdom 35, 15 houses at housing level 4,
//            survive 7 years.
// Start:     funds 11000, rescue loan 1500, debt interest 7% (normal difficulty).
// Gods:      Ra, Ptah (patron).
// Monuments: none.
// Trade:     can open — Men-nefer, Meidum, Migdol, Tyre (by sea); display only — Gaza, Alexandria.
// Enemies:   Egyptian raids, entering at the map exit. The scenario enemy is Persian, but no Persian army
//            is sent.
// Timeline:  raid 30 announced y2m7, attacks y3m1, and a month later raid 25 is announced (attacks y3m8,
//            with Pharaoh's gift of 10 weapons); y3m4 request 11 reeds (delivered: gift of 11 pottery; late:
//            gift of 5 pottery; refused: kingdom −7); y4m4 Pharaoh asks 16 troops (sent: kingdom +8; late:
//            +4; refused: battle-lost message; refused or lost: raid 26 announced two months later, attacks
//            6 months after that, and three trade routes are lost as it attacks); y5m5 Pharaoh
//            asks 6 papyrus (delivered: gift of 7 pottery; refused: −7; late: +4); y6m1 request 8 fish
//            (delivered: gift of 5 luxury goods; refused: Tyre route lost; late: gift of 3 luxury goods).
//
// Notes for developers:
// - The Egyptian invasions of the original are raids from JS (mission50_raids): pak i=3, i=4 a month after
//   i=3 attacks, i=13 two months after the pak i=9 troop request (tag 1009) is refused or lost
//   (mission50_on_request_cleared). Their events[] slots stay as EVENT_TYPE_NONE so the other indexes
//   keep; tags 1014 and 1017 let the raids fire the chained events.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields.
// - The gifts at indexes 0, 1, 2 and 19 are already fired in the original; they stay only to keep the
//   indexes of the other events.
// - The other events are declared in events[] and run by the engine; on_*_action values are indexes into
//   that list.

mission50 { // Maritis - Caesar and Cleopatra
	map_file : "data/maps/m_050_maritis.map"
	start_message : "message_mission_maritis"
	selection_title : "Maritis"
	player_rank : 1

	next_mission : 51

	// pak Normal funds=11000 loan=1500 debt_interest=7 -> int_dcy around Normal.
	initial_funds [22000, 14670, 11000, 7370, 5830]
	rescue_loans [3000, 2000, 1500, 1005, 795]
	debt_interest [4, 5, 7, 9, 11]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C50_mission.mp3"
		victory : "Voice/Mission/C50_victory.mp3"
	}

	// buildings[] synced to pak_editor_allow (25 on): military+forts+zoo+gold;
	// OFF: water_supply/apothecary/tax/palace/roadblock/ferry/gardens/statues/
	// tower/gate/recruiter/academy/warship/transport/scribal/library/senet/dance/festival.
	// Always: vacant/clear/road/fire/architect/police/well + Ra/Ptah temples.
	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_IRRIGATION_DITCH,
		BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
		BUILDING_WEAPONSMITH, BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL,
		BUILDING_DOCK, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_PTAH,
		BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
		BUILDING_ZOO,
	]

	win_criteria {
		population    {enabled : true, goal : 1000 }
		culture       {enabled : true, goal : 10 }
		prosperity    {enabled : true, goal : 25 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 35 }
		housing_count {enabled : true, goal : 15 }
		housing_level {enabled : true, goal : 4 }
		survival_time {enabled : true, years : 7 }
		milestone25_year : 3
		milestone50_year : 4
		milestone75_year : 5
	}

	entry_point [113, 93]
	exit_point [106, 100]
	river_entry_point [3, 66]
	river_exit_point [54, 122]
	// pak inv land/sea empty - omit (invasions fall back to map exit).
	fishing_points [
		[41, 99], [69, 110], [56, 93], [31, 76]
	]
	herd_points_predator [ [80, 123], [35, 88], [60, 25] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{ // pak i=0
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 0, month : 1 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 32 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ALREADY_FIRED
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 6
		}
		{ // pak i=1
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 2 }
			item { value : RESOURCE_MEAT }
			amount { value : 30 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ALREADY_FIRED
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=2
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 0, month : 3 }
			item { value : RESOURCE_GRAIN }
			amount { value : 30 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ALREADY_FIRED
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{ // pak i=3: invasion, started from JS (mission50_raids)
			type : EVENT_TYPE_NONE
		}
		{ // pak i=4: invasion, started from JS (mission50_raids)
			type : EVENT_TYPE_NONE
		}
		{ // pak i=5
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 4 }
			item { value : RESOURCE_REEDS }
			amount { value : 11 }
			months_initial : 8
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 6
			on_refusal_action : 7
			on_too_late_action : 8
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=6
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_POTTERY }
			amount { value : 11 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{ // pak i=7
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 7 }
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
		{ // pak i=8
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_POTTERY }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 4, 4, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=9
			type : EVENT_TYPE_REQUEST
			tag_id : 1009
			time { year : 4, month : 4 }
			item { value : RESOURCE_TROOPS }
			amount { value : 16 }
			months_initial : 9
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 10
			on_refusal_action : 11
			on_too_late_action : 12
			on_defeat_action : 13
			sender_faction : 1
			subtype : 1
			city_id : 4
		}
		{ // pak i=10
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 2, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=11
			type : EVENT_TYPE_MESSAGE
			time { year : 3, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 13
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 7
		}
		{ // pak i=12
			type : EVENT_TYPE_REPUTATION_INCREASE
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
			city_id : 6
		}
		{ // pak i=13: invasion, started from JS (mission50_raids, armed by mission50_on_request_cleared)
			type : EVENT_TYPE_NONE
		}
		{ // pak i=14
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			tag_id : 1014
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 15
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 4
		}
		{ // pak i=15
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 16
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 4
		}
		{ // pak i=16
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
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
			subtype : 3
			city_id : 8
		}
		{ // pak i=17
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			tag_id : 1017
			time { year : 2, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{ // pak i=18
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 5 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 6 }
			months_initial : 8
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 20
			on_refusal_action : 7
			on_too_late_action : 12
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 5
		}
		{ // pak i=19
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 4 }
			item { value : RESOURCE_TIMBER }
			amount { value : 2 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ALREADY_FIRED
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=20
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_POTTERY }
			amount { value : 7 }
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
		{ // pak i=21
			type : EVENT_TYPE_REQUEST
			time { year : 6, month : 1 }
			item { value : RESOURCE_FISH }
			amount { value : 8 }
			months_initial : 9
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 22
			on_refusal_action : 23
			on_too_late_action : 24
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{ // pak i=22
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{ // pak i=23
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 7
		}
		{ // pak i=24
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 2, month : 0 }
			item { value : RESOURCE_LUXURY_GOODS }
			amount { value : 3 }
			months_initial : 12
			location_fields [ 6, 6, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
	]

	map_background : {pack:PACK_EMPIRE, id:26}

	hide_pak_cities : true
	cities [
		{
			name : "Gaza"
			idx : 0
			pos : [853, 275]
			route : 5
			trade : false
			cost_to_open : 700
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Men-nefer"
			idx : 1
			pos : [551, 497]
			route : 3
			is_open : false
			cost_to_open : 90
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			buys [ RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER ]
			route_limits [
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Tyre"
			idx : 3
			pos : [877, 121]
			route : 6
			is_open : false
			cost_to_open : 780
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			sells [ RESOURCE_LINEN, RESOURCE_LUXURY_GOODS, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_GRAIN, RESOURCE_POTTERY, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Alexandria"
			idx : 20
			pos : [389, 375]
			route : 1
			trade : false
			cost_to_open : 90
			is_sea_trade : true
			type : EMPIRE_CITY_PHARAOH
		}
		{
			name : "Meidum"
			idx : 24
			pos : [568, 581]
			route : 4
			is_open : false
			cost_to_open : 185
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN ]
			buys [ RESOURCE_TIMBER, RESOURCE_REEDS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_REEDS, limit: 2500 }
			]
		}
		{
			name : "Migdol"
			idx : 27
			pos : [617, 412]
			route : 2
			is_open : false
			cost_to_open : 190
			is_sea_trade : false
			type : EMPIRE_CITY_EGYPTIAN_TRADING
			sells [ RESOURCE_GRAIN, RESOURCE_MEAT, RESOURCE_WEAPONS, RESOURCE_TIMBER ]
			buys [ RESOURCE_LINEN, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_GRAIN, limit: 2500 }
				{ resource: RESOURCE_MEAT, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 1500 }
				{ resource: RESOURCE_LINEN, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Maritis"
			idx : 28
			pos : [442, 423]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_CHICKPEAS, RESOURCE_FISH, RESOURCE_REEDS ]
		}
	]

	hide_pak_routes : true
	empire_routes [
		{
			route : 1
			type : 2
			points [ [407, 426], [442, 438] ]
		}
		{
			route : 2
			type : 1
			points [ [621, 442], [600, 461], [587, 482], [581, 498], [575, 513], [556, 512], [521, 494], [498, 465], [477, 449] ]
		}
		{
			route : 3
			type : 1
			points [ [550, 519], [517, 500], [494, 481], [474, 453] ]
		}
		{
			route : 4
			type : 1
			points [ [581, 581], [575, 557], [557, 533], [530, 512], [500, 493], [473, 470], [464, 454] ]
		}
		{
			route : 5
			type : 2
			points [ [851, 292], [811, 308], [784, 331], [745, 341], [695, 353], [668, 352], [613, 337], [555, 336], [525, 339], [471, 352], [439, 372], [419, 398], [425, 421], [444, 436] ]
		}
		{
			route : 6
			type : 2
			points [ [875, 143], [860, 161], [848, 232], [835, 287], [812, 304], [778, 324], [722, 337], [669, 340], [607, 330], [526, 335], [476, 346], [436, 365], [414, 393], [414, 405], [420, 421], [442, 434] ]
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
		{ name : "#lower_egypt", pos : [506, 461] }
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
		raids : ""
	}
}

[es=event_mission_start, mission=mission50]
function mission50_on_start(ev) {
	__image_request_pak(PACK_ENEMY_PERSIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -50
	scenario.alt_predator_type = true
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_maritis")
	empire.set_id(0)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_9_PERSIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// pak i=3: the calendar Egyptian invasion; as it attacks it chains i=4, 25 more due a month later (its time.year),
// which bring Pharaoh's gift of 10 weapons (pak i=17) as they attack. The map has no invasion points, so both come
// in by the map exit. pak i=13: see mission50_on_request_cleared.
function mission50_raid_list() {
	return [
		{ key: "i3", invasion_id: 3, year: 2, month: 7, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 30,
			months_initial: 6, location: [3, -1, 1, 5], attack_target: EVENT_ATTACK_TARGET_TROOPS,
			then: [{ key: "i4", delay: 1 }] },
		{ key: "i4", invasion_id: 4, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 25, months_initial: 6,
			location: [3, -1, 1, 5], attack_target: EVENT_ATTACK_TARGET_TROOPS, chain_tag: 1017 },
		{ key: "i13", invasion_id: 13, invader: EVENT_INVADER_EGYPT, enemy: ENEMY_3_EGYPTIAN, amount: 26,
			months_initial: 6, location: [2, -1, 1, 5], attack_target: EVENT_ATTACK_TARGET_RANDOM, chain_tag: 1014 }
	]
}

[es=event_advance_month, mission=mission50]
function mission50_raids(ev) {
	mission_raids_month(mission, mission50, ev, mission50_raid_list())
}

// pak i=9 (Pharaoh asks 16 troops) refused or lost -> i=13 Egyptian invasion 26, due 2 months later (its
// time.year); as it attacks the routes of pak i=14, 15, 16 are lost one after another.
[es=event_request_cleared, mission=mission50]
function mission50_on_request_cleared(ev) {
	if (ev.tag_id == 1009 && mission_request_outcome(ev) == "refuse") {
		mission_raid_schedule(mission, mission50_raid_list(), "i13", 2)
	}
}
