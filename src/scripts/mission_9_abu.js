log_info("akhenaten: mission 9 abu started")

mission9 = { // Abu
	start_message : 0, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
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

	cities : [
		{
			name : "Byblos",
			is_sea_trade : true,
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Behdet",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Abedju",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Nubt",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Men-nefer",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Timna",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Kyrene",
			max_traders : 1
			trade_limits : default_trade_limits
		},

		{
			name : "Selima Oasis",
			max_traders : 1
			trade_limits : default_trade_limits
		},
	],

	events : [
		{
			type: "EVENT_SUBTYPE_FOREIGN_CITY_CONQUERED"
			time { year : 2664, month : 5 }
			city: "Selima Oasis"
			amount { value : 1400 }
			deadline : 9
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