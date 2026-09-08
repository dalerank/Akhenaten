log_info("akhenaten: figure homeless started")

figure_homeless = {
	animations : {
		walk : { pack: PACK_SPR_MAIN, id: 12, max_frames:12 }
		death : { pack: PACK_SPR_MAIN, id: 13, max_frames:8, loop:false }
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_HOMELESS }
	}

	sounds {
		homeless_no_job_in_city { sound:"emigrant_e01.wav", text: "#homeless_no_job_in_city" }
		homeless_no_food_in_city { sound:"emigrant_e02.wav", text: "#homeless_no_food_in_city" }
		homeless_tax_too_high { sound:"emigrant_e03.wav", text: "#homeless_tax_too_high" }
		homeless_salary_too_low { sound:"emigrant_e04.wav", text: "#homeless_salary_too_low" }
		homeless_found_new_house { sound:"immigrant_e02.wav", text: "#homeless_found_new_house" }
		homeless_no_house_for_me { sound:"emigrant_e05.wav", text: "#homeless_no_house_for_me" }
		homeless_need_workers { sound:"emigrant_need_workers.wav", text: "#homeless_need_workers" }
		homeless_city_is_bad { sound:"emigrant_city_is_bad.wav", text: "#homeless_city_is_bad" }
		homeless_gods_are_angry { sound:"emigrant_gods_are_angry.wav", text: "#homeless_gods_are_angry" }
		homeless_city_bad_reputation { sound:"vagrant_e02.wav", text: "#homeless_city_bad_reputation" }
		homeless_city_is_good { sound:"emigrant_city_is_good.wav", text: "#homeless_city_is_good" }
		homeless_i_was_kicked_out_of_my_home { sound:"vagrant_e01.wav", text: "#homeless_i_was_kicked_out_of_my_home" }
		homeless_i_cant_find_a_place_to_live { sound:"vagrant_e02.wav", text: "#homeless_i_cant_find_a_place_to_live" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS
}

function figure_homeless_gods_are_angry() {
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

function figure_homeless_phrase_key(f) {
	var mood_cause = city.sentiment.low_mood_cause

	// C++ returned these immediately (no random pool).
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "homeless_no_job_in_city"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "homeless_no_food_in_city"
	}
	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "homeless_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "homeless_salary_too_low"
	}

	var keys = []
	var state = f.action_state
	var sentiment = city.sentiment.value

	// ACTION_8_HOMELESS_GOING_TO_HOUSE
	if (state == 8) {
		keys.push("homeless_found_new_house")
	}

	// ACTION_6_HOMELESS_LEAVING
	if (state == 6) {
		keys.push("homeless_no_house_for_me")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("homeless_need_workers")
	}

	if (city.kingdome.rating < 30) {
		keys.push("homeless_city_is_bad")
	}

	if (figure_homeless_gods_are_angry()) {
		keys.push("homeless_gods_are_angry")
	}

	if (sentiment < 30) {
		keys.push("homeless_city_bad_reputation")
	} else if (sentiment > 50) {
		keys.push("homeless_city_is_good")
	}

	keys.push("homeless_i_was_kicked_out_of_my_home")
	keys.push("homeless_i_cant_find_a_place_to_live")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_homeless, setup_phrase)]
function figure_homeless_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_homeless_phrase_key(f))
}
