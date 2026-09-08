log_info("akhenaten: figure musician started")

figure_musician {
	overlay : OVERLAY_BANDSTAND
	animations {
		walk { pack:PACK_SPR_MAIN, id:191, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:192, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MUSICIAN }
	}

	sounds {
		musician_i_like_festivals { sound:"musician_e01.wav", text: "#musician_i_like_festivals" }
		musician_city_heath_too_low { sound:"musician_g01.wav", text: "#musician_city_heath_too_low" }
		musician_no_food_in_city { sound:"musician_g02.wav", text: "#musician_no_food_in_city" }
		musician_city_not_safety_workers_leaving { sound:"musician_g03.wav", text: "#musician_city_not_safety_workers_leaving" }
		musician_need_workers { sound:"musician_g04.wav", text: "#musician_need_workers" }
		musician_gods_are_angry { sound:"musician_g05.wav", text: "#musician_gods_are_angry" }
		musician_city_is_bad_reputation { sound:"musician_g06.wav", text: "#musician_city_is_bad_reputation" }
		musician_much_unemployments { sound:"musician_g07.wav", text: "#musician_much_unemployments" }
		musician_no_entertainment_need { sound:"musician_g08.wav", text: "#musician_no_entertainment_need" }
		musician_city_not_bad { sound:"musician_g09.wav", text: "#musician_city_not_bad" }
		musician_city_is_good { sound:"musician_g10.wav", text: "#musician_city_is_good" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission: epermission_entertainer
}

function figure_musician_gods_are_angry() {
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

function figure_musician_months_since_last_festival() {
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

function figure_musician_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (figure_musician_months_since_last_festival() < 6) {
		keys.push("musician_i_like_festivals")
	}

	if (city.num_forts < 1) {
		keys.push("musician_city_not_safety_workers_leaving")
	}

	if (city.health_rating < 40) {
		keys.push("musician_city_heath_too_low")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("musician_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("musician_need_workers")
	}

	if (figure_musician_gods_are_angry()) {
		keys.push("musician_gods_are_angry")
	}

	if (sentiment < 30) {
		keys.push("musician_city_is_bad_reputation")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("musician_much_unemployments")
	}

	if (city.houses.missing.more_entertainment == 0) {
		keys.push("musician_no_entertainment_need")
	}

	if (sentiment < 50) {
		keys.push("musician_city_not_bad")
	} else {
		keys.push("musician_city_is_good")
	}

	if (keys.length == 0) {
		return "musician_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_musician, setup_phrase)]
function figure_musician_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_musician_city_phrase_key())
}
