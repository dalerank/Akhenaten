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
		tutorial_water { buildings: [BUILDING_WATER_SUPPLY] }
		tutorial_collapse { buildings: [BUILDING_ARCHITECT_POST] }
	}

	vars {
		granary_open_population : 160
		population_cap_firstfire : 0
		granary_meat_stored : 400
		victory_last_action_delay : 4

		tutorial_fire_handled : false
		tutorial_granary_opened : false
		last_action_time : 0
	}
}

[event=event_mission_start, mission=mission0]
function tutorial1_on_start(ev) {
	city.set_goal_tooltip("#mission0_goal_create_housing")

	if (mission.tutorial_granary_opened) {
		city.use_building(BUILDING_HUNTING_LODGE, true)
		city.use_building(BUILDING_GRANARY, true)
		city.use_building(BUILDING_BAZAAR, true)
		city.set_goal_tooltip("#mission0_goal_build_granary")
	}

	if (mission.tutorial_fire_handled) {
		city.use_building(BUILDING_FIREHOUSE, true)
	}
}

[event=event_fire_damage, mission=mission0]
function tutorial1_handle_fire(ev) {
	if (mission.tutorial_fire_handled) {
		return
	}
    
	mission.last_action_time = game.absolute_day
	mission.tutorial_fire_handled = true
	
	city.use_building(BUILDING_FIREHOUSE, true)
	ui.popup_message("message_fire_in_the_village")
	
	log_info("granary_open_population:${mission.last_action_time}")
	log_info("tutorial1_handle_fire:${mission.tutorial_fire_handled}")
}

[event=event_population_changed, mission=mission0]
function tutorial1_handle_population_for_granary(ev) {
	if (mission.granary_opened) {
		return;
	}

	if (ev.value < mission.granary_open_population) {
		return;
	}

	city.use_building(BUILDING_HUNTING_LODGE, true)
	city.use_building(BUILDING_GRANARY, true)
	city.use_building(BUILDING_BAZAAR, true)

	mission.last_action_time = game.absolute_day
	mission.tutorial_granary_opened = true

	ui.popup_message("message_tutorial_food_or_famine")

	log_info("granary_open_population:${mission.last_action_time}")
	log_info("tutorial1_handle_population_for_granary:${mission.tutorial_granary_opened}")
}