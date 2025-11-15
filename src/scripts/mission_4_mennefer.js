log_info("akhenaten: mission 4 started")

mission4 {
	start_message : "message_trade_on_the_water"
	env {
		has_animals : true		
		marshland_grow : default_marshland_grow
	    tree_grow : default_tree_grow
	}
	player_rank : 1
	initial_funds [7500, 5000, 3750, 2500, 2000]
	rescue_loans [7500, 5000, 3750, 2500, 2000]
	house_tax_multipliers [300, 200, 150, 100, 75]

	buildings  [
					BUILDING_SMALL_STATUE, BUILDING_MEDIUM_STATUE, BUILDING_LARGE_STATUE, BUILDING_GARDENS, BUILDING_PLAZA,
					BUILDING_ROADBLOCK, BUILDING_FIREHOUSE, BUILDING_ARCHITECT_POST, BUILDING_POLICE_STATION, BUILDING_VILLAGE_PALACE,
					BUILDING_TAX_COLLECTOR, BUILDING_COURTHOUSE, BUILDING_PERSONAL_MANSION,
					BUILDING_WATER_SUPPLY, BUILDING_APOTHECARY, BUILDING_PHYSICIAN,
					BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL, BUILDING_BANDSTAND, BUILDING_CONSERVATORY,
					BUILDING_TEMPLE_OSIRIS, BUILDING_SHRINE_OSIRIS, BUILDING_TEMPLE_PTAH, BUILDING_SHRINE_PTAH, BUILDING_TEMPLE_BAST, BUILDING_SHRINE_BAST, BUILDING_FESTIVAL_SQUARE,
					BUILDING_CLAY_PIT, BUILDING_POTTERY_WORKSHOP, BUILDING_BREWERY_WORKSHOP, BUILDING_BAZAAR, BUILDING_GRANARY, BUILDING_STORAGE_YARD,
					BUILDING_CHICKPEAS_FARM, BUILDING_BARLEY_FARM, BUILDING_WORK_CAMP,
					BUILDING_MUD_WALL,

					BUILDING_BULLFIGHT_SCHOOL, BUILDING_MUD_GATEHOUSE, BUILDING_TOWER_GATEHOUSE, BUILDING_MUD_TOWER,
				]

	cities [
		{
			name : "Nekhen"
			is_sea_trade : false
			max_traders : 1
			trade_limits : default_trade_limits
		}

		{
			name : "Perwadjyt"
			is_sea_trade : true
			max_traders : 1
			trade_limits : default_trade_limits
		}
	]

	vars {
		spacious_apartment_needed : 1
		papyrus_stored : 100
		bricks_stored_needed : 100
		victory_last_action_delay : 3

		spacious_apartment_built_handled : false
		papyrus_made_handled : false
		bricks_bought_handled : false
		last_action_time : 0
	}
}

[event=event_mission_start, mission=mission4]
function tutorial5_on_start(ev) {
	if (!mission.bricks_bought_handled) {
		city.set_goal_tooltip("#tutorial_goal_import_bricks")
	}

	if (mission.papyrus_made_handled) {
		city.set_advisor_available(ADVISOR_TRADE, 1)
		city.use_building(BUILDING_DOCK, true)
	} else {
		city.set_goal_tooltip("#tutorial_goal_scribal_school")
	}

	if (mission.spacious_apartment_built_handled) {
		city.use_building(BUILDING_REED_GATHERER, true)
		city.use_building(BUILDING_PAPYRUS_WORKSHOP, true)
		city.use_building(BUILDING_SCRIBAL_SCHOOL, true)
		city.set_advisor_available(ADVISOR_EDUCATION, 1)
	} else {
		city.set_goal_tooltip("#tutorial_goal_education")
	}

	if (mission.bricks_bought_handled) {
		city.use_building(BUILDING_BRICKLAYERS_GUILD, true)
		city.use_building(BUILDING_SMALL_MASTABA, true)
		city.set_advisor_available(ADVISOR_MONUMENTS, 1)
	} else {
		city.set_goal_tooltip("#tutorial_goal_import_bricks")
	}

	city.set_advisor_available(ADVISOR_LABOR, 1)
	city.set_advisor_available(ADVISOR_IMPERIAL, 1)
	city.set_advisor_available(ADVISOR_RATINGS, 1)
	city.set_advisor_available(ADVISOR_POPULATION, 1)
	city.set_advisor_available(ADVISOR_HEALTH, 1)
	city.set_advisor_available(ADVISOR_ENTERTAINMENT, 1)
	city.set_advisor_available(ADVISOR_RELIGION, 1)
	city.set_advisor_available(ADVISOR_FINANCIAL, 1)
	city.set_advisor_available(ADVISOR_CHIEF, 1)
}

[event=event_advance_day, mission=mission4]
function tutorial5_handle_spacious_apartment() {
    if (mission.spacious_apartment_built) {
        return
    }

    var spacious_apartment_count = city.count_total_buildings(BUILDING_HOUSE_SPACIOUS_APARTMENT);
    if (spacious_apartment_count < mission.spacious_apartment_needed) {
        return
    }

    mission.spacious_apartment_built_handled = true
    mission.last_action_time = game.absolute_day
	
    city.set_advisor_available(ADVISOR_EDUCATION, 1)
	
	city.use_building(BUILDING_REED_GATHERER, true)
	city.use_building(BUILDING_PAPYRUS_WORKSHOP, true)
	city.use_building(BUILDING_SCRIBAL_SCHOOL, true)

	city.set_goal_tooltip("#tutorial_goal_scribal_school")
    ui.popup_message("message_tutorial_education")
}

[event=event_update_victory_state, mission=mission4]
function tutorial5_handle_victory_state(ev) {
	city.set_victory_reason("spacious_apartment_built", mission.spacious_apartment_built_handled)
	city.set_victory_reason("papyrus_made", mission.papyrus_made_handled)
	city.set_victory_reason("bricks_bought", mission.bricks_bought_handled)

	var some_days_after_last_action = (game.absolute_day - mission.last_action_time) > mission.victory_last_action_delay
	city.set_victory_reason("some_days_after_last_action", some_days_after_last_action)
}

[event=event_warehouse_filled, mission=mission4]
function tutorial5_handle_papyrus(ev) {
    if (mission.papyrus_made_handled) {
        return
    }

	var papyrus_amount = city.yards_stored(RESOURCE_PAPYRUS)
    if (papyrus_amount < mission.papyrus_stored) {
        return
    }

    mission.papyrus_made_handled = true
	mission.last_action_time = game.absolute_day

	city.set_advisor_available(ADVISOR_TRADE, 1)
    city.use_building(BUILDING_DOCK, true)
	
	ui.popup_message("message_tutorial_trade_with_other_cities")
}

[event=event_warehouse_filled, mission=mission4]
function tutorial5_handle_bricks(ev) {
    if (mission.bricks_bought_handled) {
        return
    }

    var bricks_amount = city.yards_stored(RESOURCE_BRICKS)
    if (bricks_amount < mission.bricks_stored_needed) {
        return
    }

    mission.bricks_bought_handled = true
	mission.last_action_time = game.absolute_day

	city.use_building(BUILDING_BRICKLAYERS_GUILD, true)
	city.use_building(BUILDING_SMALL_MASTABA, true)

	city.set_advisor_available(ADVISOR_MONUMENTS, 1)
	ui.popup_message("message_tutorial_monuments")
}