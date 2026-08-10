log_info("akhenaten: mission 46 migdol started")

// Cleop mission1.pak scenario 46 (dump 2026-07-31). Empire id=1.
// Scenario enemy ENEMY_8_NUBIAN (briefing = Assyrians / Asarhaddon - pak id wins).
// Gods: Osiris(1), Ptah(1), Seth(2). MM subtitle: Repel the Assyrians. Start year -677.
// Funds Normal 15002 / loan 2500 / debt_interest 7. Rank 5 (pak).
// Win: pop 1000 / culture 10 / prosperity 15 / monuments off / kingdom off /
//   housing level 10 / survival 7y (m25=2 m50=4 m75=6).
// Climate central; map_background empire pack id 24.
// Redefine: enable_scenario_events + events[] (10; 4 invasions) + hide_pak empire + texts/ornaments.
// Config-only fish/herd (omit -> empty). Inv land/sea empty in pak -> omit (exit fallback).
// Sparse pak_allowed (hut/road/clear) -> briefing fill (military / weapons trade).
// Trade JS: Enkomi / Men-nefer / Timna. next_mission 47.
// Alt briefing: message_mission_pelusium (455). Invasions declarative in events[] (calendar once).

mission46 { // Migdol - Repel the Assyrians
	map_file : "data/maps/m_046_migdol.map"
	start_message : "message_mission_migdol"
	selection_title : "Migdol"
	player_rank : 5

	next_mission : 47

	// pak Normal funds=15002 loan=2500 debt_interest=7 -> int_dcy around Normal.
	initial_funds [30004, 20003, 15002, 10001, 7951]
	rescue_loans [5000, 3330, 2500, 1670, 1325]
	debt_interest [4, 5, 7, 9, 11]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C46_mission.mp3"
		victory : "Voice/Mission/C46_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_DOCK, BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_LETTUCE_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
		BUILDING_SCRIBAL_SCHOOL,
	]

	win_criteria {
		population    {enabled : true, goal : 1000 }
		culture       {enabled : true, goal : 10 }
		prosperity    {enabled : true, goal : 15 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : false, goal : 0 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 10 }
		survival_time {enabled : true, years : 7 }
		milestone25_year : 2
		milestone50_year : 4
		milestone75_year : 6
	}

	entry_point [71, 96]
	exit_point [71, 16]
	river_entry_point [7, 48]
	river_exit_point [48, 102]
	// pak inv land/sea empty - omit (invasions fall back to map exit).
	fishing_points [ [14, 54], [34, 79], [22, 43] ]
	herd_points_predator [ [95, 62] ]
	herd_points_prey [ [27, 68] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_COPPER }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_CONTAMINATED_WATER
			time { year : 5, month : 6 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
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
			subtype : 3
			city_id : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 6 }
			item { value : RESOURCE_LETTUCE }
			amount { value : 6 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 0
			on_refusal_action : 4
			on_too_late_action : 5
			on_defeat_action : -1
			sender_faction : 0
			subtype : 5
			city_id : 8
		}
		{
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 2, month : 0 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 7 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 5 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 4 }
			item { value : 1 }
			amount { value : 4 }
			months_initial : 1
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
			invasion_attack_target : 3
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 2, month : 8 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 4
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 2
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
			invasion_attack_target : 3
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 4, month : 3 }
			item { value : 1 }
			amount { value : 15 }
			months_initial : 4
			location_fields [ 2, -1, 2, 3 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
			invasion_attack_target : 0
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 5, month : 3 }
			item { value : 1 }
			amount { value : 25 }
			months_initial : 5
			location_fields [ 4, -1, 4, 5 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 2
		}
	]

	map_background : {pack:PACK_EMPIRE, id:24}
	hide_pak_cities : true
	cities [
		{
			name : "Migdol"
			idx : 15
			pos : [659, 377]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_LETTUCE, RESOURCE_CHICKPEAS, RESOURCE_FISH, RESOURCE_REEDS ]
			buys [ RESOURCE_GEMS, RESOURCE_COPPER, RESOURCE_SANDSTONE ]
		}
		{
			name : "Enkomi"
			idx : 4
			pos : [679, 49]
			route : 1
			is_open : false
			cost_to_open : 700
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_COPPER ]
			buys [ RESOURCE_CHICKPEAS, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 4000 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 4000 }
			]
		}
		{
			name : "Men-nefer"
			idx : 10
			pos : [540, 497]
			route : 2
			is_open : false
			cost_to_open : 200
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_POTTERY, RESOURCE_BARLEY, RESOURCE_CHARIOTS ]
			buys [ RESOURCE_WEAPONS, RESOURCE_LUXURY_GOODS, RESOURCE_PAPYRUS, RESOURCE_COPPER ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_CHARIOTS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Timna"
			idx : 20
			pos : [912, 459]
			route : 3
			is_open : false
			cost_to_open : 280
			is_sea_trade : false
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS, RESOURCE_POTTERY, RESOURCE_COPPER ]
			buys [ RESOURCE_FISH, RESOURCE_BEER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_FISH, limit: 4000 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Abu"
			idx : 0
			pos : [874, 1158]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Byblos"
			idx : 1
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Dakhla Oasis"
			idx : 2
			pos : [349, 1037]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Djedu"
			idx : 3
			pos : [535, 389]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Farafra Oasis"
			idx : 5
			pos : [327, 831]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Gaza"
			idx : 6
			pos : [846, 280]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Henen-nesw"
			idx : 7
			pos : [534, 626]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Jericho"
			idx : 8
			pos : [897, 238]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Kyrene"
			idx : 9
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Mycenae"
			idx : 11
			pos : [27, 15]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "On"
			idx : 13
			pos : [572, 454]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Qadesh"
			idx : 14
			pos : [962, 10]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sawu"
			idx : 16
			pos : [907, 834]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Serabit Khadim"
			idx : 17
			pos : [796, 563]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sharuhen"
			idx : 18
			pos : [836, 359]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Thinis"
			idx : 19
			pos : [687, 871]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Tyre"
			idx : 21
			pos : [877, 121]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Waset"
			idx : 22
			pos : [818, 966]
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
			points [ [714, 76], [734, 83], [757, 100], [828, 131], [865, 144], [865, 175], [854, 207], [847, 250], [844, 279], [830, 303], [799, 326], [768, 338], [725, 339], [710, 347], [691, 359], [679, 382] ]
		}
		{
			route : 2
			type : 1
			points [ [581, 524], [594, 509], [599, 496], [599, 479], [612, 470], [633, 448], [653, 439], [664, 430], [675, 416], [672, 408] ]
		}
		{
			route : 3
			type : 1
			points [ [914, 478], [875, 477], [841, 460], [739, 436], [693, 405] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [561, 552], image : 13859, expanded_image : 4 }
		{ pos : [507, 486], image : 13864, expanded_image : 9 }
		{ pos : [539, 502], image : 13856, expanded_image : 1 }
		{ pos : [577, 601], image : 13858, expanded_image : 3 }
		{ pos : [516, 507], image : 13855, expanded_image : 0 }
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
		start_message_shown : false
	}
}

[es=event_mission_start, mission=mission46]
function mission46_on_start(ev) {
	log_info("mission46: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_NUBIAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -677
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_migdol")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_8_NUBIAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}
