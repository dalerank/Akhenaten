log_info("akhenaten: mission 129 bridges started")

// Custom mission 129 — Bridges, "20 Years until invasion" (Cleopatra map Bridges.map). Rank 0 (Village Elder).
//
// Goals:     monuments 13, housing level 10 (house count is enabled with goal 0).
// Start:     funds 7500, no rescue loan, debt interest 5% (normal difficulty).
// Gods:      Ra.
// Monuments: large obelisk, small obelisk.
// Trade:     none — our city is Djedu, Abu is display only, no trade routes.
// Enemies:   one Egyptian army (Pharaoh's), by sea with 9 warships from the map exit.
// Timeline:  Pharaoh's army of 16 announced y25m0, attacks the best buildings y25m1. No requests or other
//            events.
//
// Notes for developers:
// - The map's own building flags turn off the fishing wharf, granary, well and water supply; they are
//   allowed here because the city sells fish and the map has 8 fishing points.
// - The map's event sends the army from point 9 (a sea point) with 9 warships; the map has no valid
//   invasion points, so as in OG invasion_start_sea it sails from the map exit.
// - Raids follow the OG invasion cycle (missions.js mission_raids_month): warnings from the event's month,
//   the attack months_initial months later, the point rolled from the event's location_fields.
// - The army size and year 25 come from the map's event; the subtitle's "20 years" is the map's own text.

mission129 { // Bridges.map
	selection_title : "Bridges"
	selection_subtitle : "20 Years until invasion"
	selection_text : "Keep an eye on the clock, as Pharaoh will send his hordes if you don't complete his obelisk in time. The region has all the resources needed to complete the monument, and you won't be hounded by any outside distractions like requests for items.  Successful cities will have carefully planned roads and will make skillful use of the available land."
	player_rank : 0

	// map Normal funds=7500 loan=0 debt_interest=5 → int_dcy around Normal.
	initial_funds [15000, 10000, 7500, 5000, 4000]
	rescue_loans [0, 0, 0, 0, 0]
	debt_interest [1, 3, 5, 8, 10]

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
		tree_grow : default_tree_grow
		hide_nilometer : true
	}
	religion_enabled : true
	hide_won_screen : false

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
		BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
		BUILDING_WELL, BUILDING_WATER_SUPPLY, BUILDING_DENTIST, BUILDING_PHYSICIAN, BUILDING_MORTUARY,
		BUILDING_WATER_LIFT,
		BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD, BUILDING_ARTISANS_GUILD,
		BUILDING_WORK_CAMP,
		BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_PLAZA,
		BUILDING_POTTERY_WORKSHOP, BUILDING_JEWELS_WORKSHOP, BUILDING_WEAPONSMITH,
		BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_FAMILY_MANSION, BUILDING_DYNASTY_MANSION,
		BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD, BUILDING_DOCK,
		BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA,
		BUILDING_CLAY_PIT, BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_GEMSTONE_MINE,
		BUILDING_STONE_QUARRY, BUILDING_LIMESTONE_QUARRY, BUILDING_GRANITE_QUARRY, BUILDING_SANDSTONE_QUARRY,
		BUILDING_REED_GATHERER, BUILDING_WOOD_CUTTERS,
		BUILDING_FERRY, BUILDING_LOW_BRIDGE, BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF,
		BUILDING_SCRIBAL_SCHOOL,
		BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
		BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE,
		BUILDING_MUD_WALL,
		BUILDING_SMALL_OBELISK, BUILDING_LARGE_OBELISK,
	]

	// Goals vs Bridges.map scenario_info: monuments 1/13, housing_level 1/10,
	// housing_count 1/0 (enabled, goal 0 — keep as-is).
	win_criteria {
		culture       {enabled : false }
		prosperity    {enabled : false }
		monuments     {enabled : true, goal : 13 }
		kingdom       {enabled : false }
		population    {enabled : false }
		housing_count {enabled : true, goal : 0 }
		housing_level {enabled : true, goal : 10 }
	}

	entry_point [54, 122]
	exit_point [69, 137]
	river_entry_point [41, 30]
	river_exit_point [49, 117]
	disembark_points [ [63, 118] ]
	fishing_points [
		[17, 69], [39, 70], [55, 73], [84, 73], [98, 76], [127, 73], [63, 29], [76, 106]
	]

	enable_scenario_events : true

	map_background : {pack:PACK_EMPIRE, id:1}
	hide_pak_cities : true
	cities [
		{
			name : "Djedu"
			idx : 10
			pos : [529, 391]
			route : 0
			type : EMPIRE_CITY_OURS
			sells [ RESOURCE_FISH, RESOURCE_CLAY, RESOURCE_TIMBER, RESOURCE_GRANITE, RESOURCE_COPPER ]
			buys []
		}

		{
			name : "Abu"
			idx : 0
			pos : [1171, 198]
			route : 0
			trade : false
			type : EMPIRE_CITY_EGYPTIAN
		}
	]

	hide_pak_routes : true
	empire_routes []

	hide_pak_objects : true

	vars {
		raids : ""
	}
}

[es=event_mission_start, mission=mission129]
function mission129_on_start(ev) {
	empire.set_id(1)
	empire.set_expanded(false)
	city.set_empire_available(1)
	for (var i = ADVISOR_NONE + 1; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 1)
	}
}

// map i=0: Pharaoh's army.
function mission129_raid_list() {
	return [
		{ key: "i0", invasion_id: 1, year: 25, month: 0, invader: EVENT_INVADER_PHARAOH, enemy: ENEMY_3_EGYPTIAN,
			amount: 16, months_initial: 1, location: [9, 9, -1, -1], warships: 9,
			attack_target: EVENT_ATTACK_TARGET_BEST_BUILDINGS }
	]
}

[es=event_advance_month, mission=mission129]
function mission129_raids(ev) {
	mission_raids_month(mission, mission129, ev, mission129_raid_list())
}
