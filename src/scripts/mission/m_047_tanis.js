log_info("akhenaten: mission 47 tanis started")

// Cleopatra campaign scenario 47. Empire id=1.

// Scenario enemy ENEMY_11_ROMAN (briefing = Persian / Conon - pak id wins).
// Gods: Osiris(1), Ra(2), Seth(1). MM subtitle: Rebirth of a Navy. Start year -395.
// Funds Normal 8000 / loan 2000 / debt_interest 8. Rank 6 (pak).
// Win: pop 2500 / culture 30 / prosperity 40 / monuments off / kingdom 45 /
//   housing level 10 / survival 10y (m25=3 m50=6 m75=10). time_limit off (pak years=10 unused).
// Climate central; map_background empire pack id 24.
// Redefine: enable_scenario_events + events[] (20; favour KR; i=0 ok=55 clamped to -1) + hide_pak empire + texts/ornaments.
// Config-only fish/herd/disembark/inv (omit -> empty). Must copy from dump.
// Sparse pak_allowed -> briefing fill; warship TEMP (CL-M / Naval) despite editor slot 43 off.
// Trade JS: Enkomi (timber+copper) / Men-nefer / Athens.
// next_mission -1 (campaign end - must not spill to Capital 48).
// Alt briefing: message_mission_tanis_2 (456). Warship TEMP (CL-M / Naval).

mission47 { // Tanis - Rebirth of a Navy
	map_file : "data/maps/m_047_tanis.map"
	start_message : "message_mission_tanis"
	selection_title : "Tanis"
	player_rank : 6

	next_mission : -1

	// pak Normal funds=8000 loan=2000 debt_interest=8 -> int_dcy around Normal.
	initial_funds [16000, 10670, 8000, 5360, 4240]
	rescue_loans [4000, 2670, 2000, 1340, 1060]
	debt_interest [5, 6, 8, 10, 12]
	house_tax_multipliers [300, 200, 150, 100, 75]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
	}

	sounds {
		briefing : "Voice/Mission/C47_mission.mp3"
		victory : "Voice/Mission/C47_victory.mp3"
	}

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_DENTIST, BUILDING_MORTUARY,
		BUILDING_WELL, BUILDING_IRRIGATION_DITCH,
		BUILDING_VILLAGE_PALACE, BUILDING_TOWN_PALACE, BUILDING_CITY_PALACE, BUILDING_WORK_CAMP,
		BUILDING_WOOD_CUTTERS, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_BRICKLAYERS_GUILD,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP,
		BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP, BUILDING_CHARIOTS_WORKSHOP,
		BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
		BUILDING_RECRUITER, BUILDING_WEAPONSMITH, BUILDING_MILITARY_ACADEMY,
		BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_FORT_CHARIOTEERS,
		BUILDING_MUD_WALL, BUILDING_MUD_GATEHOUSE, BUILDING_MUD_TOWER,
		BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_SHIPWRIGHT, BUILDING_DOCK,
		BUILDING_FISHING_WHARF, BUILDING_LOW_BRIDGE, BUILDING_FERRY,
		BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_FLAX_FARM, BUILDING_FIGS_FARM,
		BUILDING_CHICKPEAS_FARM, BUILDING_POMEGRANATES_FARM,
		BUILDING_CLAY_PIT, BUILDING_REED_GATHERER, BUILDING_GOLD_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,
		BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_RA, BUILDING_TEMPLE_COMPLEX_SETH,
		BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND,
		BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY, BUILDING_ZOO,
	]

	win_criteria {
		population    {enabled : true, goal : 2500 }
		culture       {enabled : true, goal : 30 }
		prosperity    {enabled : true, goal : 40 }
		monuments     {enabled : false, goal : 0 }
		kingdom       {enabled : true, goal : 45 }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 10 }
		survival_time {enabled : true, years : 10 }
		milestone25_year : 3
		milestone50_year : 6
		milestone75_year : 10
	}

	entry_point [92, 161]
	exit_point [107, 146]
	river_entry_point [35, 50]
	river_exit_point [125, 126]
	disembark_points [ [31, 96], [14, 96] ]
	invasion_points_land [ [107, 87], [86, 73] ]
	invasion_points_sea [ [145, 5], [166, 13] ]
	fishing_points [ [46, 101], [96, 66], [59, 78] ]
	herd_points_predator [ [65, 75], [135, 58] ]

	hide_pak_burial : true
	burial_provisions [ ]

	enable_scenario_events : true
	events [
		{
			type : EVENT_TYPE_INVASION
			time { year : 4, month : 0 }
			item { value : 1 }
			amount { value : 0 }
			months_initial : 2
			location_fields [ 9, -1, 9, 10 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 7
			invasion_attack_target : 3
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 2, month : 7 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 7 }
			months_initial : 6
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 2
			on_refusal_action : 4
			on_too_late_action : 3
			on_defeat_action : -1
			sender_faction : 1
			subtype : 0
			city_id : 7
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 1, month : 0 }
			item { value : RESOURCE_CHICKPEAS }
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
			city_id : 6
		}
		{
			type : EVENT_TYPE_PRICE_INCREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_CHICKPEAS }
			amount { value : 4 }
			months_initial : 12
			location_fields [ 1, 1, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 0
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 17
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 3
			city_id : 4
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 6, month : 2 }
			item { value : 1 }
			amount { value : 16 }
			months_initial : 8
			location_fields [ 11, 11, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 0
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 4
			invasion_attack_target : 2
		}
		{
			type : EVENT_TYPE_LOCUSTS
			time { year : 5, month : 4 }
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
			type : EVENT_TYPE_REQUEST
			time { year : 3, month : 6 }
			item { value : RESOURCE_PAPYRUS }
			amount { value : 5 }
			months_initial : 6
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : 8
			on_refusal_action : 9
			on_too_late_action : 10
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 5
		}
		{
			type : EVENT_TYPE_REPUTATION_INCREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 5 }
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
		{
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
			city_id : 5
		}
		{
			type : EVENT_TYPE_DEMAND_DECREASE
			time { year : 1, month : 0 }
			item { value : RESOURCE_POMEGRANATES }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 3, 3, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
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
			time { year : 7, month : 5 }
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
			subtype : 3
			city_id : 4
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 8, month : 2 }
			item { value : 1 }
			amount { value : 12 }
			months_initial : 10
			location_fields [ 11, -1, 10, 12 ]
			event_trigger_type : EVENT_TRIGGER_ONCE
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 5, month : 3 }
			item { value : RESOURCE_FISH }
			amount { value : 9 }
			months_initial : 8
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_RECURRING
			on_completed_action : 14
			on_refusal_action : 15
			on_too_late_action : 16
			on_defeat_action : -1
			sender_faction : 1
			subtype : 3
			city_id : 6
		}
		{
			type : EVENT_TYPE_GIFT_FROM_PHARAOH
			time { year : 3, month : 0 }
			item { value : RESOURCE_WEAPONS }
			amount { value : 11 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 16
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
		}
		{
			type : EVENT_TYPE_REPUTATION_DECREASE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 4 }
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
		{
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
			city_id : 5
		}
		{
			type : EVENT_TYPE_REQUEST
			time { year : 8, month : 0 }
			item { value : RESOURCE_REEDS }
			amount { value : 10 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : 18
			on_refusal_action : 15
			on_too_late_action : 18
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 6
		}
		{
			type : EVENT_TYPE_CITY_STATUS_CHANGE
			time { year : 1, month : 0 }
			item { value : 1 }
			amount { value : 8 }
			months_initial : 12
			location_fields [ 2, 2, -1, -1 ]
			event_trigger_type : EVENT_TRIGGER_ONLY_VIA_EVENT
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 2
			city_id : 8
		}
		{
			type : EVENT_TYPE_INVASION
			time { year : 1, month : 0 }
			item { value : 3 }
			amount { value : 26 }
			months_initial : 11
			location_fields [ 1, -1, 1, 2 ]
			event_trigger_type : EVENT_TRIGGER_BY_FAVOUR
			on_completed_action : -1
			on_refusal_action : -1
			on_too_late_action : -1
			on_defeat_action : -1
			sender_faction : 0
			subtype : 0
			city_id : 8
			invasion_attack_target : 4
		}
	]

	map_background : {pack:PACK_EMPIRE, id:24}
	hide_pak_cities : true
	cities [
		{
			name : "Tanis"
			idx : 4
			pos : [587, 388]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_POMEGRANATES, RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_REEDS ]
			buys [ RESOURCE_BEER, RESOURCE_LINEN, RESOURCE_STONE, RESOURCE_LIMESTONE, RESOURCE_SANDSTONE ]
		}
		{
			name : "Enkomi"
			idx : 5
			pos : [679, 49]
			route : 1
			is_open : false
			cost_to_open : 800
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_FISH, RESOURCE_TIMBER, RESOURCE_COPPER ]
			buys [ RESOURCE_POMEGRANATES, RESOURCE_BEER ]
			route_limits [
				{ resource: RESOURCE_POMEGRANATES, limit: 1500 }
				{ resource: RESOURCE_FISH, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_COPPER, limit: 2500 }
			]
		}
		{
			name : "Men-nefer"
			idx : 11
			pos : [540, 497]
			route : 2
			is_open : false
			cost_to_open : 150
			is_sea_trade : false
			type : EMPIRE_CITY_PHARAOH_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_CHICKPEAS, RESOURCE_BARLEY ]
			buys [ RESOURCE_POTTERY, RESOURCE_BEER, RESOURCE_TIMBER, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_CHICKPEAS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 4000 }
				{ resource: RESOURCE_BARLEY, limit: 2500 }
				{ resource: RESOURCE_BEER, limit: 2500 }
				{ resource: RESOURCE_TIMBER, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
			]
		}
		{
			name : "Athens"
			idx : 48
			pos : [20, 0]
			route : 3
			is_open : false
			cost_to_open : 1000
			is_sea_trade : true
			type : EMPIRE_CITY_FOREIGN_TRADING
			max_traders : 1
			trade_limits : default_trade_limits
			sells [ RESOURCE_WEAPONS, RESOURCE_POTTERY, RESOURCE_LUXURY_GOODS ]
			buys [ RESOURCE_POMEGRANATES, RESOURCE_PAPYRUS ]
			route_limits [
				{ resource: RESOURCE_POMEGRANATES, limit: 2500 }
				{ resource: RESOURCE_WEAPONS, limit: 2500 }
				{ resource: RESOURCE_POTTERY, limit: 2500 }
				{ resource: RESOURCE_LUXURY_GOODS, limit: 2500 }
				{ resource: RESOURCE_PAPYRUS, limit: 2500 }
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
			name : "Behdet"
			idx : 1
			pos : [836, 1069]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Byblos"
			idx : 2
			pos : [891, 68]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Dakhla Oasis"
			idx : 3
			pos : [349, 1037]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Farafra Oasis"
			idx : 6
			pos : [327, 831]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Gaza"
			idx : 7
			pos : [846, 280]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Henen-nesw"
			idx : 8
			pos : [534, 626]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Jericho"
			idx : 9
			pos : [896, 233]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Kyrene"
			idx : 10
			pos : [22, 341]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Menat Khufu"
			idx : 12
			pos : [587, 721]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Nekhen"
			idx : 14
			pos : [797, 1011]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "On"
			idx : 15
			pos : [572, 454]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Qadesh"
			idx : 16
			pos : [962, 10]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Migdol"
			idx : 17
			pos : [657, 379]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Sauty"
			idx : 18
			pos : [636, 790]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Sawu"
			idx : 19
			pos : [907, 834]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Sharuhen"
			idx : 20
			pos : [836, 359]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Thinis"
			idx : 21
			pos : [687, 871]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
		{
			name : "Timna"
			idx : 22
			pos : [905, 453]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Tyre"
			idx : 23
			pos : [877, 121]
			route : 0
			trade : false
			type : EMPIRE_CITY_FOREIGN
		}
		{
			name : "Waset"
			idx : 24
			pos : [820, 960]
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
			points [ [715, 70], [864, 118], [872, 140], [861, 178], [855, 216], [844, 248], [848, 286], [814, 313], [770, 334], [725, 336], [680, 360], [640, 356], [629, 379], [614, 393] ]
		}
		{
			route : 2
			type : 1
			points [ [566, 520], [566, 491], [564, 472], [579, 446], [589, 439], [598, 418] ]
		}
		{
			route : 3
			type : 2
			points [ [46, 30], [71, 53], [83, 79], [118, 101], [245, 123], [275, 128], [293, 155], [502, 339], [542, 335], [570, 342], [593, 328], [633, 342], [638, 355], [627, 382], [621, 393] ]
		}
	]

	hide_pak_objects : true
	empire_ornaments [
		{ pos : [561, 552], image : 13859, expanded_image : 4 }
		{ pos : [507, 486], image : 13864, expanded_image : 9 }
		{ pos : [539, 502], image : 13856, expanded_image : 1 }
		{ pos : [577, 601], image : 13858, expanded_image : 3 }
		{ pos : [516, 507], image : 13855, expanded_image : 0 }
		{ pos : [836, 935], image : 13869, expanded_image : 14 }
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

[es=event_mission_start, mission=mission47]
function mission47_on_start(ev) {
	log_info("mission47: on_start", {ev:ev})
	__image_request_pak(PACK_ENEMY_ROMAN)
	__image_request_pak(PACK_ENEMY_EGYPTIAN)
	scenario.start_year = -395
	__scenario_monuments.first = 0
	__scenario_monuments.second = 0
	__scenario_monuments.third = 0
	mission_show_start_message(mission, "message_mission_tanis")
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	city.set_scenario_enemy_id(ENEMY_11_ROMAN)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}
