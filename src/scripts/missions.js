log_info("akhenaten: missions started")

mission_sounds = []

for (var i = 0; i < 38; i++) {
	mission_sounds[i] = {
		mission: i,
		briefing: _format("Voice/Mission/{0}_mission.mp3", (i + 200).toString()),
		victory: _format("Voice/Mission/{0}_victory.mp3", (i + 200).toString())
	}
}

mission0 = { // Nubt
	start_message : 150 //TUTORIAL_HOUSING_AND_ROADS, 248 = 150 + 99 - 1
	env {
		has_animals : true		
	    gods_least_mood : 50
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
}

mission3 = {
	start_message : 241 - 99
	env {
		has_animals : true		
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
		},

		{
			name : "Perwadjyt",
			is_sea_trade : true,
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
		},
		{
			name : "Perwadjyt",
			is_sea_trade : true,
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

mission9 = { // Abu
	start_message : 0, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	env {
		has_animals : true		
	}
	player_rank : 1,
	next_mission : 10,
	choice_background : {pack:PACK_UNLOADED, id:12},
	choice_image1 : {pack:PACK_UNLOADED, id:13, offset:0},
	choice_image1_pos : [192, 144],
	choice_title : [144, 22],
	initial_funds : [7500, 5000, 3750, 2500, 2000],
	rescue_loans : [7500, 5000, 3750, 2500, 2000],
	house_tax_multipliers : [300, 200, 150, 100, 75],

	init_resources : {
		grain : { type:RESOURCE_GRAIN, allow: true},
		barley: { type:RESOURCE_BARLEY, allow: true},
		flax: { type:RESOURCE_FLAX, allow:true},
		lettuce: { type:RESOURCE_LETTUCE, allow:true},
		chickpeas: { type:RESOURCE_CHICKPEAS, allow:true},
	},

	buildings : [
		         BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
				 BUILDING_JEWELS_WORKSHOP, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_WEAVER_WORKSHOP, BUILDING_PAPYRUS_WORKSHOP, BUILDING_BRICKS_WORKSHOP,
				 BUILDING_GRANITE_QUARRY, BUILDING_SANDSTONE_QUARRY, BUILDING_GEMSTONE_MINE,
				 BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_CHICKPEAS_FARM, BUILDING_FLAX_FARM, BUILDING_LETTUCE_FARM, BUILDING_WORK_CAMP,
				 BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH,
				 BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION,
				 BUILDING_WATER_SUPPLY,
				 BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD, 
				 BUILDING_ROADBLOCK, BUILDING_FERRY, BUILDING_DOCK,
				 BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_PAVILLION, BUILDING_DANCE_SCHOOL,
				 BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_FAMILY_MANSION, BUILDING_TOWN_PALACE,
				 BUILDING_FESTIVAL_SQUARE, BUILDING_TEMPLE_COMPLEX_OSIRIS, BUILDING_TEMPLE_COMPLEX_PTAH,
				 BUILDING_IRRIGATION_DITCH, BUILDING_WATER_LIFT,
				],
	stages : {
	},

	cities : [
		{
			name : "Byblos",
			is_sea_trade : true,
		},

		{
			name : "Behdet",
		},

		{
			name : "Abedju",
		},

		{
			name : "Nubt",
		},

		{
			name : "Men-nefer",
		},

		{
			name : "Timna",
		},

		{
			name : "Kyrene",
		},

		{
			name : "Selima Oasis",
		},
	],

	events : [
		{
			type: "EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED",
			year : 2664,
			month : 5,
			city: "Selima Oasis",
			amount : 1400,
			deadline : 9,
		},
	],

	choice : [
		{
			name : "Selima",
			id : 8,
			image: {pack:PACK_UNLOADED, id:20, offset:0},
			tooltip : [144, 23],
			pos : [620, 420],
		},

		{
			name : "Abu",
			id : 9,
			image: {pack:PACK_UNLOADED, id:20},
			tooltip : [144, 24],
			pos : [640, 480],
		}
	],
}