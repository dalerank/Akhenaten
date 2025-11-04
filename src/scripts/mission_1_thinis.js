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
	stages {
		tutorial_entertainment { buildings: [BUILDING_BOOTH, BUILDING_JUGGLER_SCHOOL] }
	}

	vars {
		gold_mined : 500
		victory_last_action_delay : 4
		nogranary_populcation_cap : 150

		gold_mined_handled : false
	}
}

[event=event_mission_start, mission=mission1]
function tutorial2_on_start(ev) {
	if (mission.gold_mined_handled) {
		city.use_building(BUILDING_TEMPLE_BAST, true)
		city.use_building(BUILDING_SHRINE_BAST, true)
		city.use_building(BUILDING_FESTIVAL_SQUARE, true)
	}
}

[event=event_advance_day, mission=mission1]
function tutorial2_check_gold_mined(ev) {
    if (mission.gold_mined_handled) {
        return;
    } 

    if (finance.income.gold_delivered < mission.gold_mined) {
        return;
    }

    mission.last_action = game.absolute_day
    mission.gold_mined_handled = true
	log_info("akhenaten: show the gods of egypt") 

	city.use_building(BUILDING_TEMPLE_BAST, true)
	city.use_building(BUILDING_SHRINE_BAST, true)
	city.use_building(BUILDING_FESTIVAL_SQUARE, true)

	ui.popup_message("message_tutorial_the_gods_of_egypt")
}