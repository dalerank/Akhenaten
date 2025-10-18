log_info("akhenaten: missions started")

mission_sounds = []
// 0: no traders, less 1500: 1 trader, less 2500: 2 traders, less 4000: 3 traders, less 10000: 4 traders
default_trade_limits = [0, 1500, 2500, 4000, 10000] 

for (var i = 0; i < 38; i++) {
	mission_sounds[i] = {
		mission: i,
		briefing: _format("Voice/Mission/{0}_mission.mp3", (i + 200).toString()),
		victory: _format("Voice/Mission/{0}_victory.mp3", (i + 200).toString())
	}
}

default_marshland_grow {
	random_max : 10
	random_min : 5
}

default_tree_grow {
	random_max : 2
	random_min : 1	
}

mission0 = { // Nubt
	start_message : 150 //TUTORIAL_HOUSING_AND_ROADS, 248 = 150 + 99 - 1
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	religion_enabled : false
	hide_won_screen : true
	player_rank : 0

	initial_funds : [7500, 5000, 3750, 2500, 2000]
	rescue_loans : [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers : [300, 200, 150, 100, 75]

	buildings : [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD
	]

	extra_damage : {
		house0: { type:BUILDING_HOUSE_CRUDE_HUT, fire: +0, collapse: +0}
		house1: { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}	
		house2: { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}
	}

	stages : {
		tutorial_fire: [BUILDING_FIREHOUSE]
		tutorial_food: [BUILDING_HUNTING_LODGE, BUILDING_GRANARY, BUILDING_BAZAAR]
		tutorial_water: [BUILDING_WATER_SUPPLY]
		tutorial_collapse: [BUILDING_ARCHITECT_POST]
	}

	vars : {
		granary_open_population : 160
		population_cap_firstfire : 0
		granary_meat_stored : 400
		victory_last_action_delay : 4
	}
}

mission1 = {
	start_message : 241 - 99, //MESSAGE_TUTORIAL_GOLD_AND_CRIME
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 0,
	hide_won_screen : true,
	initial_funds : [7500, 5000, 3750, 2500, 2000],
	rescue_loans : [7500, 5000, 3750, 2500, 2000],

	buildings : [
					BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
					BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_WATER_SUPPLY,
					BUILDING_GOLD_MINE, BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				],
	stages : {
		tutorial_gods : [BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE],
		tutorial_entertainment : [BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL]
	}

	vars : {
		gold_mined : 500
		victory_last_action_delay : 4
		nogranary_populcation_cap : 150
	}
}

mission2 = {
	start_message : 242 - 99,
	env {
		has_animals : true		
	    gods_least_mood : 50
	}
	player_rank : 0,
	initial_funds : [7500, 5000, 3750, 2500, 2000],
	rescue_loans : [7500, 5000, 3750, 2500, 2000],
	house_tax_multipliers : [300, 200, 150, 100, 75],

	buildings : [
					BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE, BUILDING_WATER_SUPPLY,
					BUILDING_FIGS_FARM, BUILDING_WORK_CAMP, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BAZAAR, BUILDING_GRANARY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_FESTIVAL_SQUARE
				],
	stages : {
		tutorial_industry: [BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_STORAGE_YARD],
		tutorial_health: [BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN],
		tutorial_gardens: [BUILDING_ROADBLOCK, BUILDING_FERRY, BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA],
	}

	vars : {
		figs_stored : 800
		pottery_step1_stored : 100
		pottery_step1_population_cap : 500
		pottery_step2_stored : 200
		victory_last_action_delay : 3
	}

	marshland_grow : default_marshland_grow
	tree_grow : default_tree_grow
}

mission3 = {
	start_message : 241 - 99
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 0
	initial_funds : [7500, 5000, 3750, 2500, 2000]
	rescue_loans : [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers : [300, 200, 150, 100, 75]

	buildings : [
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_FERRY,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_STORAGE_YARD,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_BREWERY_WORKSHOP
				]
	stages : {
		tutorial_finance: [BUILDING_TAX_COLLECTOR, BUILDING_PERSONAL_MANSION]
	}

	vars : {
		beer_stored : 300
		victory_last_action_delay : 3
	}
}

mission4 = {
	start_message : 241 - 99,
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1,
	initial_funds : [7500, 5000, 3750, 2500, 2000],
	rescue_loans : [7500, 5000, 3750, 2500, 2000],
	house_tax_multipliers : [300, 200, 150, 100, 75],

	buildings : [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_MUD_WALL,

					BUILDING_BULLFIGHT_SCHOOL, BUILDING_MUD_GATEHOUSE, BUILDING_TOWER_GATEHOUSE, BUILDING_MUD_TOWER,
				],
	stages : {
		tutorial_education: [BUILDING_REED_GATHERER, BUILDING_PAPYRUS_WORKSHOP, BUILDING_SCRIBAL_SCHOOL],
		tutorial_trading: [BUILDING_DOCK],
		tutorial_monuments: [BUILDING_BRICKLAYERS_GUILD, BUILDING_SMALL_MASTABA]
	}

	cities : [
		{
			name : "Nekhen",
			is_sea_trade : false,
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Perwadjyt",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		},
	]

	vars : {
		spacious_apartment_built : 1
		papyrus_stored : 100
		victory_last_action_delay : 3
	}
}

mission7 = { // Abydos
	start_message : 146, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1,
	next_mission : 8,
	initial_funds : [7500, 5000, 3750, 2500, 2000],
	rescue_loans : [7500, 5000, 3750, 2500, 2000],
	house_tax_multipliers : [300, 200, 150, 100, 75],

	buildings: [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_WORK_CAMP, BUILDING_FLAX_FARM, BUILDING_BARLEY_FARM,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_RECRUITER, BUILDING_FORT_INFANTRY, BUILDING_FORT_ARCHERS, BUILDING_WEAPONSMITH,
					BUILDING_SCRIBAL_SCHOOL,
					BUILDING_CLAY_PIT, BUILDING_REED_GATHERER,
					BUILDING_POTTERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
					BUILDING_SHIPWRIGHT, BUILDING_FISHING_WHARF, BUILDING_FERRY,
					BUILDING_WARSHIP_WHARF, BUILDING_TRANSPORT_WHARF, BUILDING_DOCK,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS,
					BUILDING_BRICKLAYERS_GUILD,
					BUILDING_SMALL_MASTABA, BUILDING_MEDIUM_MASTABA,
					BUILDING_FESTIVAL_SQUARE, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, 
					BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL, BUILDING_SENET_HOUSE
				],
	stages : {
	},

	enable_scenario_events : false,
	events : [
		{
			type: EVENT_TYPE_REQUEST,
			year : 2684,
			month : 1,
			resource : RESOURCE_POTTERY,
			amount : 1400,
			deadline : 9,
		},

		{
			type: EVENT_TYPE_INVASION,
			year : 2670,
			month : 2,
		},

		{
			type: "pharaoh_gift", //EVENT_TYPE_INVASION,
			year: 2670,
			month: 8,
		},
	],

	cities : [
		{
			name : "Byblos",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		},
		{
			name : "Perwadjyt",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		},
	],

	choice_background : {pack:PACK_UNLOADED, id:12},
	choice_image1 : {pack:PACK_UNLOADED, id:13, offset:0},
	choice_image1_pos : [192, 144],
	choice_title : [144, 19],
	choice : [
		{
			name : "Abydos",
			id : 6,
			image: {pack:PACK_UNLOADED, id:20, offset:0},
			tooltip : [144, 20],
			pos : [620, 420],
		},

		{
			name : "Behdet",
			id : 7,
			image: {pack:PACK_UNLOADED, id:20},
			tooltip : [144, 21],
			pos : [640, 480],
		}
	],
}