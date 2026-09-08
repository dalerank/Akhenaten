log_info("akhenaten: figure labor_seeker started")

figure_labor_seeker {
	overlay : OVERLAY_DAMAGE
	animations {
		walk { pack:PACK_SPR_MAIN, id:206, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:207, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LABOR_SEEKER }
	}

	sounds {
		recruiter_disease_in_city { sound:"Labor_e01.wav", text: "#recruiter_disease_in_city" }
		recruiter_no_food_in_city { sound:"Labor_e02.wav", text: "#recruiter_no_food_in_city" }
		recruiter_city_not_safety { sound:"Labor_g01.wav", text: "#recruiter_city_not_safety" }
		recruiter_need_workers { sound:"Labor_g02.wav", text: "#recruiter_need_workers" }
		recruiter_gods_are_angry { sound:"Labor_g03.wav", text: "#recruiter_gods_are_angry" }
		recruiter_enemies_attack { sound:"Labor_g04.wav", text: "#recruiter_enemies_attack" }
		recruiter_i_looking_for_the_workers { sound:"Labor_g05.wav", text: "#recruiter_i_looking_for_the_workers" }
		recruiter_boring { sound:"Labor_g06.wav", text: "#recruiter_boring" }
		recruiter_living_here { sound:"Labor_g07.wav", text: "#recruiter_living_here" }
		recruiter_city_is_amazing { sound:"Labor_g08.wav", text: "#recruiter_city_is_amazing" }
		recruiter_i_want_to_leave_city { sound:"Labor_g09.wav", text: "#recruiter_i_want_to_leave_city" }
		recruiter_much_unemployments { sound:"Labor_g10.wav", text: "#recruiter_much_unemployments" }
		recruiter_no_jobs { sound:"Labor_g10.wav", text: "#recruiter_no_jobs" }
		recruiter_no_some_workers { sound:"Labor_g05.wav", text: "#recruiter_no_some_workers" }
		recruiter_need_more_workers { sound:"Labor_g02.wav", text: "#recruiter_need_more_workers" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

function figure_labor_seeker_gods_are_angry() {
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

function figure_labor_seeker_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var workers_needed = city.labor.workers_needed

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("recruiter_no_jobs")
	}

	// C++ used workers_needed >= 0 (almost always true).
	if (workers_needed >= 0) {
		keys.push("recruiter_no_some_workers")
	}

	if (workers_needed >= 10) {
		keys.push("recruiter_need_workers")
	}

	if (workers_needed >= 20) {
		keys.push("recruiter_need_more_workers")
	}

	// C++ scanned houses for disease_days; health rating is the JS proxy.
	if (city.health_rating < 20) {
		keys.push("recruiter_disease_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("recruiter_city_not_safety")
	}

	if (figure_labor_seeker_gods_are_angry()) {
		keys.push("recruiter_gods_are_angry")
	} else {
		keys.push("recruiter_city_is_amazing")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("recruiter_no_food_in_city")
	}

	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		keys.push("recruiter_i_want_to_leave_city")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("recruiter_much_unemployments")
	}

	keys.push("recruiter_i_looking_for_the_workers")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_labor_seeker, setup_phrase)]
function figure_labor_seeker_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_labor_seeker_phrase_key())
}
