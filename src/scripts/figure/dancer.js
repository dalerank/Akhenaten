log_info("akhenaten: figure dancer started")

figure_dancer {
	overlay : OVERLAY_PAVILION
	animations {
		walk { pack:PACK_SPR_MAIN, id:128, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:129, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DANCER }
	}

	sounds {
		dancer_i_like_festivals { sound:"dancer_e01.wav", text: "#dancer_i_like_festivals" }
		dancer_desease_can_start_at_any_moment { sound:"dancer_g01.wav", text: "#dancer_desease_can_start_at_any_moment" }
		dancer_no_food_in_city { sound:"dancer_g02.wav", text: "#dancer_no_food_in_city" }
		dancer_city_not_safety_workers_leaving { sound:"dancer_g03.wav", text: "#dancer_city_not_safety_workers_leaving" }
		dancer_need_workers { sound:"dancer_g04.wav", text: "#dancer_need_workers" }
		dancer_gods_are_angry { sound:"dancer_g05.wav", text: "#dancer_gods_are_angry" }
		dancer_city_is_bad { sound:"dancer_g06.wav", text: "#dancer_city_is_bad" }
		dancer_much_unemployments { sound:"dancer_g07.wav", text: "#dancer_much_unemployments" }
		dancer_salary_too_low { sound:"dancer_g08.wav", text: "#dancer_salary_too_low" }
		dancer_city_is_good { sound:"dancer_g09.wav", text: "#dancer_city_is_good" }
		dancer_city_is_amazing { sound:"dancer_g10.wav", text: "#dancer_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission : epermission_entertainer
}

function figure_dancer_gods_are_angry() {
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

function figure_dancer_months_since_last_festival() {
	var months = 999
	for (var i = 0; i < gods.length; i++) {
		var god = gods[i]
		if (!city.gods.is_known(god.type)) {
			continue
		}
		var m = city.gods.at(god.type).months_since_festival
		if (m < months) {
			months = m
		}
	}
	return months
}

function figure_dancer_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (figure_dancer_months_since_last_festival() < 6) {
		keys.push("dancer_i_like_festivals")
	}

	if (city.health_rating < 20) {
		keys.push("dancer_desease_can_start_at_any_moment")
	}

	if (city.num_forts < 1) {
		keys.push("dancer_city_not_safety_workers_leaving")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("dancer_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("dancer_need_workers")
	}

	if (figure_dancer_gods_are_angry()) {
		keys.push("dancer_gods_are_angry")
	}
	// C++ also pushed dancer_gods_are_pleasures when calm — no WAV exists, skip.

	if (city.kingdome.rating < 30) {
		keys.push("dancer_city_is_bad")
	}

	if (sentiment > 50) {
		keys.push("dancer_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("dancer_city_is_amazing")
	}

	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		keys.push("dancer_salary_too_low")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("dancer_much_unemployments")
	}

	if (keys.length == 0) {
		return "dancer_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_dancer, setup_phrase)]
function figure_dancer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_dancer_city_phrase_key())
}
