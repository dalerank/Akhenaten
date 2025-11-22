log_info("akhenaten: mission 3 started")

mission3 {
	start_message : "message_developing_culture"
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 0
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN, BUILDING_GRAIN_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_FERRY,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_STORAGE_YARD,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_RA, BUILDING_SHRINE_RA, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_BREWERY_WORKSHOP
				]

	vars {
		beer_stored : 300
		victory_last_action_delay : 3

		beer_stored_handled : false
		tax_collector_built : false
		modest_houses_reached : false
		last_action_time : 0
	}
}

[event=event_update_mission_goal, mission=mission3]
function mission3_update_goal(ev) {
	if (!mission.modest_houses_reached) {
		city.set_goal_tooltip("#reach_modest_houses_number")
		return
	}

	if (!mission.beer_stored_handled) {
		city.set_goal_tooltip("#mission3_brew_beer")
		return
	}

	if (!mission.tax_collector_built) {
		city.set_goal_tooltip("#build_tax_collector")
		return
	}
}

[event=event_mission_start, mission=mission3]
function mission3_on_start(ev) {
	if (mission.tax_collector_built) {
		city.use_building(BUILDING_TAX_COLLECTOR, true)
		city.use_building(BUILDING_PERSONAL_MANSION, true)
	}

	if (mission.beer_stored_handled) {
		city.use_building(BUILDING_TAX_COLLECTOR, true)
		city.use_building(BUILDING_PERSONAL_MANSION, true)
	}

	city.set_advisor_available(ADVISOR_LABOR, 1)
	city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
	city.set_advisor_available(ADVISOR_FINANCIAL, 1)
}

[event=event_warehouse_filled, mission=mission3]
function mission3_warehouse_beer_check(ev) {
    if (mission.beer_stored_handled) {
        return
    }

    var beer_amount = city.yards_stored(RESOURCE_BEER)
    if (beer_amount < mission.beer_stored) {
        return
    }

    mission.beer_stored_handled = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_TAX_COLLECTOR, true)
	city.use_building(BUILDING_PERSONAL_MANSION, true)

	ui.popup_message("message_tutorial_finances")
}

[event=event_building_create, mission=mission3]
function mission3_on_build_tax_collector(ev) {
    if (mission.tax_collector_built) {
        return
    }

	var is_tax_collector = city.building_is_tax_collector(ev.bid)
    if (!is_tax_collector) {
        return
    }

	mission.last_action_time = game.absolute_day
    mission.tax_collector_built = true
}

[event=event_advance_day, mission=mission3]
function mission3_handle_spacious_apartment() {
    if (mission.spacious_apartment_built) {
        return
    }

    var modest_houses_count = city.count_total_buildings(BUILDING_HOUSE_MODEST_HOMESTEAD);
    if (modest_houses_count < mission.modest_houses_needed) {
        return
    }

    mission.modest_houses_reached = true
    mission.last_action_time = game.absolute_day
}

[event=event_update_victory_state, mission=mission3]
function mission3_handle_victory_state(ev) {
	city.set_victory_reason("beer_stored_handled", mission.beer_stored_handled)
	city.set_victory_reason("tax_collector_built", mission.tax_collector_built)

	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}
