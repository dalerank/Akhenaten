log_info("akhenaten: figure stonemason started")

figure_stonemason {
	animations {
		walk { pack:PACK_SPR_MAIN, id:150, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:151, max_frames:8, loop:false }
		work_ground { pack:PACK_SPR_MAIN, id:152, max_frames:7 }
		work_wall { pack:PACK_SPR_MAIN, id:153, max_frames:7 }
		climbing { pack:PACK_SPR_MAIN, id:154, max_frames:3 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_STONEMASON }
	}

	sounds {
		stonemason_ready { sound:"stone_e01.wav", text: "#stonemason_ready" }
		stonemason_going_to_work { sound:"stone_e01.wav", text: "#stonemason_going_to_work" }
		stonemason_working_ground { sound:"stone_e02.wav", text: "#stonemason_working_ground" }
		stonemason_working_wall { sound:"stone_e02.wav", text: "#stonemason_working_wall" }
		stonemason_work_complete { sound:"stone_e02.wav", text: "#stonemason_work_complete" }
		stonemason_looking_for_work { sound:"stone_e01.wav", text: "#stonemason_looking_for_work" }
		stonemason_disease_risk { sound:"stonemason_disease_risk.wav", text: "#stonemason_disease_risk" }
		stonemason_no_food_in_city { sound:"stonemason_no_food_in_city.wav", text: "#stonemason_no_food_in_city" }
		stonemason_city_have_no_army { sound:"stonemason_city_have_no_army.wav", text: "#stonemason_city_have_no_army" }
		stonemason_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		stonemason_gods_are_angry { sound:"stonemason_gods_are_angry.wav", text: "#stonemason_gods_are_angry" }
		stonemason_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		stonemason_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		stonemason_low_entertainment { sound:"stonemason_low_entertainment.wav", text: "#stonemason_low_entertainment" }
		stonemason_city_is_good { sound:"stonemason_city_is_good.wav", text: "#stonemason_city_is_good" }
		stonemason_city_is_amazing { sound:"stonemason_city_is_amazing.wav", text: "#stonemason_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_stonemason_gods_are_angry() {
	for (var i = 0; i < gods.length; i++) {
		var god = gods[i]
		if (!city.gods.is_known(god.type)) {
			continue
		}
		if (city.gods.at(god.type).mood < 51) {
			return true
		}
	}
	return false
}

function figure_stonemason_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("stonemason_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("stonemason_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("stonemason_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("stonemason_need_workers")
	}

	if (figure_stonemason_gods_are_angry()) {
		keys.push("stonemason_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("stonemason_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("stonemason_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("stonemason_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("stonemason_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("stonemason_city_is_amazing")
	}

	if (keys.length == 0) {
		return "stonemason_ready"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_stonemason, setup_phrase)]
function figure_stonemason_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case 10: // FIGURE_ACTION_10_MASON_CREATED
	case 30: // FIGURE_ACTION_30_MASON_CREATED_ROAMING
		figure_apply_phrase(f, "stonemason_ready")
		return
	case 11: // FIGURE_ACTION_11_MASON_GOING
	case 31: // FIGURE_ACTION_31_MASON_GOING_TO_STATUE
		figure_apply_phrase(f, "stonemason_going_to_work")
		return
	case 14: // FIGURE_ACTION_14_MASON_WORK_GROUND
	case 32: // FIGURE_ACTION_14_MASON_WORK_STATUE_GROUND
		figure_apply_phrase(f, "stonemason_working_ground")
		return
	case 15: // FIGURE_ACTION_15_MASON_WORK_WALL
	case 33: // FIGURE_ACTION_14_MASON_WORK_STATUE_WALL
		figure_apply_phrase(f, "stonemason_working_wall")
		return
	case 16: // FIGURE_ACTION_16_MASON_RETURN_HOME
		figure_apply_phrase(f, "stonemason_work_complete")
		return
	case 12: // FIGURE_ACTION_12_MASON_GOING_TO_PLACE
	case 13: // FIGURE_ACTION_13_MASON_WAITING_RESOURCES
	case 17: // FIGURE_ACTION_17_MASON_LOOKING_FOR_WORK_TILE
	case 18: // FIGURE_ACTION_18_MASON_RANDOM_TILE
		figure_apply_phrase(f, "stonemason_looking_for_work")
		return
	}

	figure_apply_phrase(f, figure_stonemason_city_phrase_key())
}
