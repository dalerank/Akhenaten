log_info("akhenaten: figure juggler started")

figure_juggler {
	overlay : OVERLAY_BOOTH
	animations {
		walk { pack:PACK_SPR_MAIN, id:130, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:131, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_JUGGLER }
	}

	sounds {
		juggler_i_like_festivals { sound:"juggler_e01.wav", text: "#juggler_i_like_festivals" }
		juggler_disease_in_city { sound:"juggler_g01.wav", text: "#juggler_disease_in_city" }
		juggler_city_low_sentiment { sound:"juggler_g02.wav", text: "#juggler_city_low_sentiment" }
		juggler_city_not_safety_workers_leaving { sound:"juggler_g03.wav", text: "#juggler_city_not_safety_workers_leaving" }
		juggler_salary_too_low { sound:"juggler_g04.wav", text: "#juggler_salary_too_low" }
		juggler_gods_are_angry { sound:"juggler_g05.wav", text: "#juggler_gods_are_angry" }
		juggler_city_verylow_sentiment { sound:"juggler_g06.wav", text: "#juggler_city_verylow_sentiment" }
		juggler_much_unemployments { sound:"juggler_g07.wav", text: "#juggler_much_unemployments" }
		juggler_low_entertainment { sound:"juggler_g08.wav", text: "#juggler_low_entertainment" }
		juggler_city_is_good { sound:"juggler_g09.wav", text: "#juggler_city_is_good" }
		juggler_city_is_amazing { sound:"juggler_g10.wav", text: "#juggler_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	max_roam_length: 640
	permission : epermission_entertainer
	record_path : true
}

function figure_juggler_gods_are_angry() {
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

function figure_juggler_months_since_last_festival() {
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

function figure_juggler_city_phrase_key() {
	if (__city_figures_total_invading_enemies() > 0) {
		return "juggler_city_not_safety_workers_leaving"
	}

	// C++ scanned houses for disease_days; health rating is the JS-exposed proxy.
	if (city.health_rating < 20) {
		return "juggler_disease_in_city"
	}

	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (figure_juggler_months_since_last_festival() < 6) {
		keys.push("juggler_i_like_festivals")
	}

	if (sentiment < 30) {
		if (sentiment < 20) {
			keys.push("juggler_city_verylow_sentiment")
		}
		keys.push("juggler_city_low_sentiment")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("juggler_much_unemployments")
	}

	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		keys.push("juggler_salary_too_low")
	}

	if (figure_juggler_gods_are_angry()) {
		keys.push("juggler_gods_are_angry")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("juggler_low_entertainment")
	}

	if (sentiment > 40) {
		keys.push("juggler_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("juggler_city_is_amazing")
	}

	if (keys.length == 0) {
		return "juggler_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_juggler, setup_phrase)]
function figure_juggler_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_juggler_city_phrase_key())
}
