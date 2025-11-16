log_info("akhenaten: mission 5 timna started")

mission5 { // Timna
	start_message : "message_history_military"

	env {
		has_animals : true
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
		hide_nilometer : true
	}

	player_rank : 1
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
		         	BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
					BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL, BUILDING_CLAY_PIT, BUILDING_GEMSTONE_MINE, BUILDING_GOLD_MINE, BUILDING_COPPER_MINE, BUILDING_POTTERY_WORKSHOP,
					BUILDING_WEAVER_WORKSHOP, BUILDING_HUNTING_LODGE, BUILDING_TEMPLE_SETH, BUILDING_SHRINE_SETH,

					BUILDING_MORTUARY, BUILDING_STONEMASONS_GUILD, BUILDING_CARPENTERS_GUILD
				]
	stages {
		tutorial_irrigation { buildings: [BUILDING_WATER_LIFT, BUILDING_IRRIGATION_DITCH, ] }
		tutorial_guilds { buildings: [BUILDING_STORAGE_YARD, BUILDING_TAX_COLLECTOR, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL] }
	}
	enable_scenario_events : false,
	events [
		{
			time { year : 2850, month : 1 }
			resource : "copper"
			amount { value : 500 }
			deadline : 12
		}
		{
			time { year : 2849, month : 1 }
			resource : "gems"
			amount { value : 1500 }
			deadline : 12
		}
		{
			year : 2848
			resource : "deben"
			amount : [800, 1000]
			deadline : 12
		}
	]

	attacks  [
		{
			year : 2848
			type : "bedouin"
			amount : 4
			pepeat_after [6]
		}
	]

	gifts [
		{
				from: "pharaoh"
				condition {
					kingdome : 65
					resource : RESOURCE_CHICKPEAS
					amount [1600, 2400]
				}
		}
	]

	trade_routes [
		{
			city : "meninefer"
			reputation : 60
		}
	]
}