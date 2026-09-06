log_info("akhenaten: figure carpenter started")

figure_carpenter {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:145, max_frames:12 }
		death { id:146, max_frames:8, loop:false }
		work_ground { id:147, max_frames:7 }
		work_wall { id:148, max_frames:7 }
		climbing { id:149, max_frames:3 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_CARPENTER }
	}

	sounds {
		carpenter_work_my_tools_need_for_monument { sound:"carpenter_e01.wav", text: "#carpenter_work_my_tools_need_for_monument" }
		carpenter_this_monument_will_be_short { sound:"carpenter_e02.wav", text: "#carpenter_this_monument_will_be_short" }
		carpenter_work_wall { sound:"carpenter_work_wall.wav", text: "#carpenter_work_wall" }
		carpenter_looking_for_spot { sound:"carpenter_looking_for_spot.wav", text: "#carpenter_looking_for_spot" }
		carpenter_return_to_guild { sound:"carpenter_return_to_guild.wav", text: "#carpenter_return_to_guild" }
		carpenter_work_garden { sound:"carpenter_work_garden.wav", text: "#carpenter_work_garden" }
		carpenter_disease_risk { sound:"carpenter_disease_risk.wav", text: "#carpenter_disease_risk" }
		carpenter_no_food_in_city { sound:"carpenter_no_food_in_city.wav", text: "#carpenter_no_food_in_city" }
		carpenter_city_have_no_army { sound:"carpenter_city_have_no_army.wav", text: "#carpenter_city_have_no_army" }
		carpenter_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		carpenter_gods_are_angry { sound:"carpenter_gods_are_angry.wav", text: "#carpenter_gods_are_angry" }
		carpenter_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		carpenter_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		carpenter_low_entertainment { sound:"carpenter_low_entertainment.wav", text: "#carpenter_low_entertainment" }
		carpenter_city_is_good { sound:"carpenter_city_is_good.wav", text: "#carpenter_city_is_good" }
		carpenter_city_is_amazing { sound:"carpenter_city_is_amazing.wav", text: "#carpenter_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_carpenter_gods_are_angry() {
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

function figure_carpenter_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause

	if (city.health_rating < 30) {
		keys.push("carpenter_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("carpenter_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("carpenter_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("carpenter_need_workers")
	}

	if (figure_carpenter_gods_are_angry()) {
		keys.push("carpenter_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("carpenter_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("carpenter_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("carpenter_low_entertainment")
	}

	var sentiment = city.sentiment.value
	if (sentiment > 50) {
		keys.push("carpenter_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("carpenter_city_is_amazing")
	}

	if (keys.length == 0) {
		return "carpenter_work_my_tools_need_for_monument"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_carpenter, setup_phrase)]
function figure_carpenter_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case ACTION_2_CARPENTER_WORK_GROUND:
		figure_apply_phrase(f, "carpenter_this_monument_will_be_short")
		return
	case ACTION_3_CARPENTER_WORK_VERT:
		figure_apply_phrase(f, "carpenter_work_wall")
		return
	case ACTION_5_CARPENTER_LOOKING_FOR_WORK_TILE:
		figure_apply_phrase(f, "carpenter_looking_for_spot")
		return
	case ACTION_4_CARPENTER_RETURN_HOME:
		figure_apply_phrase(f, "carpenter_return_to_guild")
		return
	case ACTION_9_CARPENTER_GOING_TO_GARDEN:
		figure_apply_phrase(f, "carpenter_work_garden")
		return
	}

	figure_apply_phrase(f, figure_carpenter_city_phrase_key())
}
