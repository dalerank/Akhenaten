log_info("akhenaten: mission 2 started")

mission2 {
	start_message : "message_farming_along_the_nile"
	env {
		has_animals : true		
	    gods_least_mood : 50
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 0,
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings [
				BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE, BUILDING_WATER_SUPPLY,
				BUILDING_FIGS_FARM, BUILDING_WORK_CAMP, BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BAZAAR, BUILDING_GRANARY,
				BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_FESTIVAL_SQUARE
			  ]

	vars {
		figs_stored : 800
		pottery_step1_stored : 100
		pottery_step1_population_cap : 500
		pottery_step2_stored : 200
		victory_last_action_delay : 3

		figs_stored_handled : false
		disease_handled : false
		pottery_step1_stored_handled : false
		pottery_step2_stored_handled : false
	}
}

[event=event_migration_update, mission=mission2]
function mission2_handle_population_cap(ev) {
    var max_pop = (!mission.pottery_step1_stored_handled) ? mission.pottery_step1_population_cap : 0;
    migration.set_population_cap("pottery_not_produced_population_cap", max_pop)
}

[event=event_update_mission_goal, mission=mission2]
function mission2_update_goal(ev) {
	if (!mission.figs_stored_handled) {
		city.set_goal_tooltip("#mission2_store_figs")
		return
	}

	if (!mission.pottery_step1_stored_handled) {
		city.set_goal_tooltip("#mission2_pottery_step1")
		return
	}

	if (!mission.pottery_step2_stored_handled) {
		city.set_goal_tooltip("#mission2_pottery_step2")
		return
	}	
}

[event=event_mission_start, mission=mission2]
function mission2_on_start(ev) {
	for (var i = 0; i <= ADVISOR_DIPLOMACY; i++) {
		city.set_advisor_available(i, 0)
	}
	
	if (mission.figs_stored_handled) {
		city.use_building(BUILDING_CLAY_PIT, true)
		city.use_building(BUILDING_POTTERY_WORKSHOP, true)
		city.use_building(BUILDING_STORAGE_YARD, true)
		city.set_advisor_available(ADVISOR_LABOR, 1)
	}

	if (mission.pottery_step2_stored_handled) {
		city.use_building(BUILDING_ROADBLOCK, true)
		city.use_building(BUILDING_SMALL_STATUE, true)
		city.use_building(BUILDING_MEDIUM_STATUE, true)
		city.use_building(BUILDING_LARGE_STATUE, true)
		city.use_building(BUILDING_GARDENS, true)
		city.use_building(BUILDING_PLAZA, true)
		city.use_building(BUILDING_MENU_WATER_CROSSINGS, true)
	}

	if (mission.disease_handled) {
	   city.use_building(BUILDING_APOTHECARY, true)
	   city.use_building(BUILDING_PHYSICIAN, true)
	   city.set_advisor_available(ADVISOR_HEALTH, 1)
	}

	city.set_advisor_available(ADVISOR_POPULATION, 1)
	city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
}

[event=event_granary_resource_added, mission=mission2]
function mission2_on_filled_granary(ev) {
    if (mission.figs_stored_handled) {
        return
    }

    var granary = city.get_granary(ev.bid)
    var figs_stored = granary ? granary.amount(RESOURCE_FIGS) : 0

    if (figs_stored < mission.figs_stored) {
        return
    }

	mission.figs_stored_handled = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_CLAY_PIT, true)
	city.use_building(BUILDING_POTTERY_WORKSHOP, true)
	city.use_building(BUILDING_STORAGE_YARD, true)

	city.set_advisor_available(ADVISOR_LABOR, 1)

	ui.popup_message("message_tutorial_industry")
}

[event=event_warehouse_filled, mission=mission2]
function mission2_warehouse_pottery_1_check(ev) {
    if (mission.pottery_step1_stored_handled) {
        return
    }

    var amount = city.yards_stored(RESOURCE_POTTERY)
    if (amount < mission.pottery_step1_stored) {
        return
    }

	mission.pottery_step1_stored_handled = true
	mission.last_action_time = game.absolute_day
}

[event=event_warehouse_filled, mission=mission2]
function mission2_warehouse_pottery_2_check(ev) {
	if (!mission.pottery_step1_stored_handled) {
        return
    }

	if (mission.pottery_step2_stored_handled) {
        return
    }

	var amount = city.yards_stored(RESOURCE_POTTERY)
    if (amount < mission.pottery_step2_stored) {
        return
    }

	mission.pottery_step2_stored_handled = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_ROADBLOCK, true)
	city.use_building(BUILDING_SMALL_STATUE, true)
	city.use_building(BUILDING_MEDIUM_STATUE, true)
	city.use_building(BUILDING_LARGE_STATUE, true)
	city.use_building(BUILDING_GARDENS, true)
	city.use_building(BUILDING_PLAZA, true)
	city.use_building(BUILDING_MENU_WATER_CROSSINGS, true)

	ui.popup_message("message_tutorial_municipal_structures")
}

[event=event_city_disease, mission=mission2]
function mission2_on_disease(ev) {
    if (mission.disease_handled) {
        return
    }

    mission.last_action_time = game.absolute_day
    mission.disease_handled = true

	city.use_building(BUILDING_WATER_SUPPLY, true)
	city.use_building(BUILDING_APOTHECARY, true)
	city.use_building(BUILDING_PHYSICIAN, true)

	city.set_advisor_available(ADVISOR_HEALTH, 1)

	ui.popup_message("message_basic_healthcare")
}

[event=event_update_victory_state, mission=mission2]
function mission2_handle_victory_state(ev) {
	city.set_victory_reason("figs_stored_handled", mission.figs_stored_handled)
	city.set_victory_reason("disease_handled", mission.disease_handled)
	city.set_victory_reason("pottery_step1_stored_handled", mission.pottery_step1_stored_handled)
	city.set_victory_reason("pottery_step2_stored_handled", mission.pottery_step2_stored_handled)

	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay;
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}