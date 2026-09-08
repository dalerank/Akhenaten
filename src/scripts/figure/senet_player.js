log_info("akhenaten: figure senet_player started")

figure_senet_player {
	overlay : OVERLAY_SENET_HOUSE
	animations {
		walk { pack:PACK_SPR_MAIN, id:132, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:133, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SENET_PLAYER }
	}

	sounds {
		senet_i_like_festivals { sound:"senet_e01.wav", text: "#senet_i_like_festivals" }
		senet_disease_in_city { sound:"senet_g01.wav", text: "#senet_disease_in_city" }
		senet_city_low_sentiment { sound:"senet_g02.wav", text: "#senet_city_low_sentiment" }
		senet_city_not_safety_workers_leaving { sound:"senet_g03.wav", text: "#senet_city_not_safety_workers_leaving" }
		senet_salary_too_low { sound:"senet_g04.wav", text: "#senet_salary_too_low" }
		senet_gods_are_angry { sound:"senet_g05.wav", text: "#senet_gods_are_angry" }
		senet_city_verylow_sentiment { sound:"senet_g06.wav", text: "#senet_city_verylow_sentiment" }
		senet_much_unemployments { sound:"senet_g07.wav", text: "#senet_much_unemployments" }
		senet_low_entertainment { sound:"senet_g08.wav", text: "#senet_low_entertainment" }
		senet_city_is_good { sound:"senet_g09.wav", text: "#senet_city_is_good" }
		senet_city_is_amazing { sound:"senet_g10.wav", text: "#senet_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	max_roam_length: 640
	permission : epermission_entertainer
}

function figure_senet_player_gods_are_angry() {
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

function figure_senet_player_months_since_last_festival() {
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

function figure_senet_player_city_phrase_key() {
	if (__city_figures_total_invading_enemies() > 0) {
		return "senet_city_not_safety_workers_leaving"
	}

	if (city.health_rating < 20) {
		return "senet_disease_in_city"
	}

	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (figure_senet_player_months_since_last_festival() < 6) {
		keys.push("senet_i_like_festivals")
	}

	if (sentiment < 30) {
		if (sentiment < 20) {
			keys.push("senet_city_verylow_sentiment")
		}
		keys.push("senet_city_low_sentiment")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("senet_much_unemployments")
	}

	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		keys.push("senet_salary_too_low")
	}

	if (figure_senet_player_gods_are_angry()) {
		keys.push("senet_gods_are_angry")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("senet_low_entertainment")
	}

	if (sentiment > 40) {
		keys.push("senet_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("senet_city_is_amazing")
	}

	if (keys.length == 0) {
		return "senet_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_senet_player, setup_phrase)]
function figure_senet_player_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_senet_player_city_phrase_key())
}
