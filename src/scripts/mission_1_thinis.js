log_info("akhenaten: mission 1 started")

mission1 {
	start_message : "message_gold_and_crime"
	env {
		has_animals : true		
	    gods_least_mood : 50
	    marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
		hide_nilometer : true
	}
	player_rank : 0
	hide_won_screen : true
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]

	buildings  [
					BUILDING_HOUSE_VACANT_LOT, BUILDING_CLEAR_LAND, BUILDING_ROAD,
					BUILDING_FIREHOUSE, BUILDING_POLICE_STATION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_WATER_SUPPLY,
					BUILDING_GOLD_MINE, BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				]

	vars {
		gold_mined : 500
		victory_last_action_delay : 4
		nogranary_population_cap : 150
		population_to_start_collapse_event : 200

		gold_mined_handled : false
		temples_built : false
		booth_built : false
		juggler_school_built : false
		tutorial_collapsed_handled : false
		last_action_time : 0
	}
}

[event=event_update_mission_goal, mission=mission1]
function mission1_update_goal(ev) {
	if (!mission.gold_mined_handled) {
		city.set_goal_tooltip("#mission1_goal_build_temples")
		return
	}

	if (!mission.temples_built) {
		city.set_goal_tooltip("#mission1_goal_build_entertainment")
		return
	}

	city.set_goal_tooltip("#mission1_goal_build_mines")
}

[event=event_mission_start, mission=mission1]
function mission1_on_start(ev) {
	for (var i = 0; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 0)
	}

	if (mission.gold_mined_handled) {
		city.use_building(BUILDING_TEMPLE_BAST, true)
		city.use_building(BUILDING_SHRINE_BAST, true)
		city.use_building(BUILDING_FESTIVAL_SQUARE, true)		
	}

	if (mission.temples_built) {
		city.use_building(BUILDING_BOOTH, true)
		city.use_building(BUILDING_JUGGLER_SCHOOL, true)
	}

	if (mission.tutorial_collapsed_handle) {
		city.use_building(BUILDING_ARCHITECT_POST, true)
	}

    city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
}

[event=event_advance_week, mission=mission1]
function mission0_handle_collapse_event(ev) {
	if (mission.tutorial_collapsed_handled) {
		return;
	}

	if (city.population < mission.population_to_start_collapse_event) {
		return;
	}

	var house = city.get_random_house()
	house.add_collapse_damage(2000)
}

[event=event_collase_damage, mission=mission1]
function mission1_handle_collapse(ev) {
    if (mission.tutorial_collapsed_handled) {
        return;
    }
	
	mission.last_action_time = game.absolute_day
	mission.tutorial_collapsed_handled = true

	city.use_building(BUILDING_ARCHITECT_POST, true)
    ui.popup_message("message_tutorial_collapsed_building")
}

[event=event_advance_day, mission=mission1]
function mission1_check_gold_mined(ev) {
    if (mission.gold_mined_handled) {
        return
    } 

    if (city.finance.income.gold_delivered < mission.gold_mined) {
        return
    }

    mission.last_action_time = game.absolute_day
    mission.gold_mined_handled = true

	city.use_building(BUILDING_TEMPLE_BAST, true)
	city.use_building(BUILDING_SHRINE_BAST, true)
	city.use_building(BUILDING_FESTIVAL_SQUARE, true)

	ui.popup_message("message_tutorial_the_gods_of_egypt")
}

[event=event_migration_update, mission=mission1]
function mission1_handle_population_cap(ev) {
    var granary_built = city.count_active_buildings(BUILDING_GRANARY)
    var max_pop = (granary_built > 0) ? 0 : mission.nogranary_population_cap

    migration.set_population_cap("no_granary_population_cap", max_pop)
}

[event=event_update_victory_state, mission=mission1]
function mission1_handle_victory_state(ev) {
	city.set_victory_reason("gold_mined_handled", mission.gold_mined_handled)
	city.set_victory_reason("temples_built", mission.temples_built)
	city.set_victory_reason("tutorial_collapsed_handled", mission.tutorial_collapsed_handled)
	city.set_victory_reason("booth_built", mission.booth_built)
	city.set_victory_reason("juggler_school_built", mission.juggler_school_built)

    var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay;
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}

[event=event_advance_day, mission=mission1]
function mission1_on_build_temple(ev) {
    if (mission.temples_built) {
        return
    }

    var temples_count = city.count_active_buildings(BUILDING_TEMPLE_BAST)
    if (temples_count == 0) {
        return
    }

	city.use_building(BUILDING_BOOTH, true)
	city.use_building(BUILDING_JUGGLER_SCHOOL, true)

    mission.last_action = game.absolute_day
    mission.temples_built = true

    ui.popup_message("message_tutorial_entertainment");
}

[event=event_advance_day, mission=mission1]
function mission1_on_build_booth(ev) {
    if (mission.booth_built) {
        return
    }

    var booth_count = city.count_active_buildings(BUILDING_BOOTH)
    if (booth_count == 0) {
        return
    }

	mission.last_action = game.absolute_day
    mission.booth_built = true
}

[event=event_advance_day, mission=mission1]
function mission1_on_build_juggler_school(ev) {
	if (mission.juggler_school_built) {
		return
	}

	var juggler_school_count = city.count_active_buildings(BUILDING_JUGGLER_SCHOOL)
	if (juggler_school_count == 0) {
		return
	}

	mission.last_action = game.absolute_day
    mission.juggler_school_built = true
}