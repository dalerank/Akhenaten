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

	extra_damage {
		house0 { type:BUILDING_HOUSE_CRUDE_HUT, fire: +0, collapse: +0}
		house1 { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}	
		house2 { type:BUILDING_HOUSE_STURDY_HUT, fire: +0, collapse: +0}
	}

	vars {
		granary_open_population : 160
		population_cap_firstfire : 0
		granary_meat_stored : 400
		victory_last_action_delay : 4
		population_cap : 250
		victory_reason : "some_days_after_last_action"

		tutorial_fire_handled : false
		tutorial_collapsed_handle : false
		tutorial_granary_opened : false
		tutorial_gamemeat_stored : false
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

	if (mission.tutorial_collapsed_handle) {
		city.use_building(BUILDING_ARCHITECT_POST, true)
	}

	if (mission.tutorial_gamemeat_stored) {
		city.use_building(BUILDING_WATER_SUPPLY, true)
	}

	migration.population_cap = mission.population_cap;
	city.set_victory_reason(mission.victory_reason, false)
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

	log_info("granary_open_population:${mission.last_action_time}")
	log_info("tutorial1_handle_population_for_granary:${mission.tutorial_granary_opened}")
}

[event=event_collase_damage, mission=mission0]
function tutorial1_handle_collapse(ev) {
    if (mission.tutorial_collapsed_handle) {
        return;
    }
	
	mission.last_action_time = game.absolute_day
	mission.tutorial_collapsed_handle = true

	city.use_building(BUILDING_ARCHITECT_POST, true)

    ui.popup_message("message_tutorial_collapsed_building")
}

[event=event_granary_resource_added, mission=mission0]
function tutorial1_on_filled_granary(ev) {
	log_info("granary_open_population:${ev.bid}", {ev: ev})
    if (mission.tutorial_gamemeat_stored) {
        return;
    }

    var granary = city.get_granary(ev.bid)
    var meat_stored = granary.amount(RESOURCE_GAMEMEAT)

	log_info("meat_stored:${meat_stored}", {meat_stored: meat_stored})
    if (meat_stored < mission.granary_meat_stored) {
        return;
    }

	mission.tutorial_gamemeat_stored = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_WATER_SUPPLY, true)

	ui.popup_message("message_tutorial_clean_water")
}

[event=event_update_victory_state, mission=mission0]
function tutorial1_handle_victory_state(ev) {
	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay;
	city.set_victory_reason(mission.victory_reason, some_days_after_last_action)
}

[event=event_migration_update, mission=mission0]
function tutorial1_handle_population_cap(ev) {
	// do nothing
}