log_info("akhenaten: mission 0 nubt started")

mission0 { // Nubt
	start_message : "message_housing_and_roads"
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	religion_enabled : false
	hide_won_screen : true
	player_rank : 0

	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
		BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD
	]

	extra_damage {
		house0 { type:BUILDING_HOUSE_CRUDE_HUT, fire: +0, collapse: +0}
		house1 { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}	
		house2 { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}
	}

	stages {
		tutorial_fire [BUILDING_FIREHOUSE]
		tutorial_food [BUILDING_HUNTING_LODGE, BUILDING_GRANARY, BUILDING_BAZAAR]
		tutorial_water [BUILDING_WATER_SUPPLY]
		tutorial_collapse [BUILDING_ARCHITECT_POST]
	}

	vars {
		granary_open_population : 160
		population_cap_firstfire : 0
		granary_meat_stored : 400
		victory_last_action_delay : 4

		tutorial_fire_handled : false
		last_action_time : 0
	}
}

[event=event_fire_damage, mission=mission0]
function tutorial1_handle_fire(ev) {
	//if (mission.tutorial_fire_handled) {
	//	return
	//}
    //
	//mission.last_action_time = game.absolute_day()
	//mission.tutorial_fire_handled = true
    //
	//mission.use_building(BUILDING_FIREHOUSE, true)
	//ui.show_message("message_fire_in_the_village")
	log_info("tutorial1_handle_fire")
}
