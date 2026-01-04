log_info("akhenaten: mission 0 nubt started")

mission0 { // Nubt
	start_message : "message_housing_and_roads"
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
		hide_nilometer : true
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

	vars {
		granary_open_population : 160
		population_cap_firstfire : 0
		granary_meat_stored : 400
		victory_last_action_delay : 4
		population_to_start_fire_event : 120
		population_cap : 250

		tutorial_fire_handled : false
		tutorial_collapsed_handled : false
		tutorial_firehouse_built : false
		tutorial_granary_opened : false
		tutorial_gamemeat_stored : false
		last_action_time : 0
	}
}

[event=event_mission_start, mission=mission0]
function mission0_on_start(ev) {
	for (var i = 0; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 0)
	}

	if (mission.tutorial_granary_opened) {
		city.use_building(BUILDING_HUNTING_LODGE, true)
		city.use_building(BUILDING_GRANARY, true)
		city.use_building(BUILDING_BAZAAR, true)
	}

	if (mission.tutorial_fire_handled) {
		city.use_building(BUILDING_FIREHOUSE, true)
	}

	if (mission.tutorial_gamemeat_stored) {
		city.use_building(BUILDING_WATER_SUPPLY, true)
	}

	migration.set_population_cap("first_mission_population_cap", mission.population_cap)
}

[event=event_register_mission_animals, mission=mission0]
function mission0_register_animals(ev) {
	city.remove_animals()

	city.add_animals_point(0, /*x*/40, /*y*/60, FIGURE_OSTRICH, 4)
	city.set_animals_area(0, 16)
}

[event=event_advance_day, mission=mission0]
function mission0_on_build_firehouse(ev) {
    if (mission.tutorial_firehouse_built) {
        return
    }

    var firehouse_count = city.count_active_buildings(BUILDING_FIREHOUSE)
    if (firehouse_count == 0) {
        return
    }

	mission.last_action = game.absolute_day
    mission.tutorial_firehouse_built = true
}

[event=event_advance_week, mission=mission0]
function mission0_handle_fire_event(ev) {
	if (mission.tutorial_fire_handled) {
		return;
	}

	if (city.population < mission.population_to_start_fire_event) {
		return;
	}

	var house = city.get_random_house()
	house.add_fire_damage(2000)
}

[event=event_update_mission_goal, mission=mission0]
function mission0_update_goal(ev) {
	if (mission.tutorial_granary_opened) {
		city.set_goal_tooltip("#mission0_goal_build_granary")
		return
	}

	city.set_goal_tooltip("#mission0_goal_create_housing")
}

[event=event_fire_damage, mission=mission0]
function mission0_handle_fire(ev) {
	if (mission.tutorial_fire_handled) {
		return
	}
    
	mission.last_action_time = game.absolute_day
	mission.tutorial_fire_handled = true
	
	city.use_building(BUILDING_FIREHOUSE, true)
	ui.popup_message("message_fire_in_the_village")
}

[event=event_collase_damage, mission=mission0]
function mission0_handle_collapse(ev) {
    if (mission.tutorial_collapsed_handled) {
        return;
    }
	
	mission.last_action_time = game.absolute_day
	mission.tutorial_collapsed_handled = true

	city.use_building(BUILDING_ARCHITECT_POST, true)
    ui.popup_message("message_tutorial_collapsed_building")
}

[event=event_population_changed, mission=mission0]
function mission0_handle_population_for_granary(ev) {
	if (mission.tutorial_granary_opened) {
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
}

[event=event_granary_resource_added, mission=mission0]
function mission0_on_filled_granary(ev) {
    if (mission.tutorial_gamemeat_stored) {
        return;
    }

    var granary = city.get_granary(ev.bid)
    var meat_stored = granary.amount(RESOURCE_GAMEMEAT)

    if (meat_stored < mission.granary_meat_stored) {
        return;
    }

	mission.tutorial_gamemeat_stored = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_WATER_SUPPLY, true)
	ui.popup_message("message_tutorial_clean_water")
}

[event=event_update_victory_state, mission=mission0]
function mission0_handle_victory_state(ev) {
	city.set_victory_reason("gamemeat_stored", mission.tutorial_gamemeat_stored)
	city.set_victory_reason("tutorial_granary_opened", mission.tutorial_granary_opened)
	city.set_victory_reason("tutorial_firehouse_built", mission.tutorial_firehouse_built)

	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay;
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}

[event=event_migration_update, mission=mission0]
function mission0_handle_population_cap(ev) {
	migration.set_unemployments_cap({reason:"mission_0_unemployment_cap", min:-10, max:10})
}