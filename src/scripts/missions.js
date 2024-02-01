log_info("akhenaten: missions started")

mission0 = { // Nubt
	start_message : 150, //TUTORIAL_HOUSING_AND_ROADS
}

mission5 = { // Timna
	start_message : 0,
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
