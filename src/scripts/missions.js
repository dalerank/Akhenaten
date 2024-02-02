log_info("akhenaten: missions started")

mission0 = { // Nubt
	start_message : 150, //TUTORIAL_HOUSING_AND_ROADS, 248 = 150 + 99 - 1
	city_has_animals : true,
}

mission5 = { // Timna
	start_message : 146, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	city_has_animals : true,
	requests : [
		{
			year : 2850,
			resource : "copper",
			amount : 500,
			deadline : 12,
		},
		{
			year : 2849,
			resource : "gems",
			amount : 1500,
			deadline : 12,
		},
		{
			year : 2848,
			resource : "deben",
			amount : [800, 1000],
			deadline : 12,
		}
	],

	attacks : [
		{
			year : 2848,
			type : "bedouin",
			amount : 4,
		}
	],

	trade_routes : [
		{
			city : "meninefer",
			reputation : 60,
		}
	]

}
