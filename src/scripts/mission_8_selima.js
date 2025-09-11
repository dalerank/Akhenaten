log_info("akhenaten: mission 8 selima started")

mission8 = { // Selima
	start_message : 0, //TUTORIAL_SOLDIERS_AND_FORT, 245 = 146 + 99 - 1
	city_has_animals : true
	player_rank : 1
	next_mission : 10
	choice_background : {pack:PACK_UNLOADED, id:12}
	choice_image1 : {pack:PACK_UNLOADED, id:13, offset:0}
	choice_image1_pos : [192, 144]
	choice_title : [144, 22]
	money : [7500, 5000, 3750, 2500, 2000]
	rescue_loans : [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers : [300, 200, 150, 100, 75]

	buildings : [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
				]

	stages : { // 
	}

	win_criteria : {
		population_enabled : true
		population_goal : 2500
	}

	choice : [
		{
			name : "Selima"
			id : 8
			image: {pack:PACK_UNLOADED, id:20, offset:0}
			tooltip : [144, 23]
			pos : [620, 420]
		},

		{
			name : "Abu"
			id : 9
			image: {pack:PACK_UNLOADED, id:20}
			tooltip : [144, 24]
			pos : [640, 480]
		}
	],
}