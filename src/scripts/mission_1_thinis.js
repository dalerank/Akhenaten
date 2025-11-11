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
					BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_WATER_SUPPLY,
					BUILDING_GOLD_MINE, BUILDING_VILLAGE_PALACE, BUILDING_HUNTING_LODGE,
				]

	vars {
		gold_mined : 500
		victory_last_action_delay : 4
		nogranary_population_cap : 150

		gold_mined_handled : false
		temples_built : false
	}
}

[event=event_mission_start, mission=mission1]
function tutorial2_on_start(ev) {
	city.set_goal_tooltip("#mission1_goal_build_mines")

	if (mission.gold_mined_handled) {
		city.use_building(BUILDING_TEMPLE_BAST, true)
		city.use_building(BUILDING_SHRINE_BAST, true)
		city.use_building(BUILDING_FESTIVAL_SQUARE, true)
		city.set_goal_tooltip("#mission1_goal_build_temples")
	}

	if (mission.temples_built) {
		city.use_building(BUILDING_BOOTH, true)
		city.use_building(BUILDING_JUGGLER_SCHOOL, true)
		city.set_goal_tooltip("#mission1_goal_build_entertainment")
	}

    city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
}

[event=event_advance_day, mission=mission1]
function tutorial2_check_gold_mined(ev) {
    if (mission.gold_mined_handled) {
        return
    } 

    if (finance.income.gold_delivered < mission.gold_mined) {
        return
    }

    mission.last_action = game.absolute_day
    mission.gold_mined_handled = true

	city.use_building(BUILDING_TEMPLE_BAST, true)
	city.use_building(BUILDING_SHRINE_BAST, true)
	city.use_building(BUILDING_FESTIVAL_SQUARE, true)

	ui.popup_message("message_tutorial_the_gods_of_egypt")
}

[event=event_migration_update, mission=mission1]
function tutorial2_population_cap(ev) {
    var granary_built = city.count_active_buildings(BUILDING_GRANARY)
    var max_pop = (granary_built > 0) ? 0 : mission.nogranary_population_cap

    migration.set_population_cap("no_granary_population_cap", max_pop)
}

[event=event_update_victory_state, mission=mission1]
function tutorial2_handle_victory_state(ev) {
	city.set_victory_reason("gold_mined_handled", mission.gold_mined_handled)
	city.set_victory_reason("temples_built", mission.temples_built)

    var some_days_after_last_action = (game.absolute_day - mission.last_action) > mission.victory_last_action_delay;
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}

[event=event_building_create, mission=mission1]
function tutorial_2_on_build_temple(ev) {
    if (mission.temples_built) {
        return
    }

    var is_temple = city.building_is_temple(ev.bid)
    if (!is_temple) {
        return
    }

	city.use_building(BUILDING_BOOTH, true)
	city.use_building(BUILDING_JUGGLER_SCHOOL, true)

    mission.last_action = game.absolute_day
    mission.temples_built = true

    ui.popup_message("message_tutorial_entertainment");
}