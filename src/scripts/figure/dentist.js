log_info("akhenaten: figure dentist started")

figure_dentist {
	animations {
		walk { pack:PACK_SPR_MAIN, id:182, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:183, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DENTIST }
	}

	sounds {
		dentist_concerned_about_plague { sound:"dentist_g01.wav", text: "#dentist_concerned_about_plague" }
		dentist_no_food_in_city { sound:"dentist_g02.wav", text: "#dentist_no_food_in_city" }
		dentist_defenses_weak { sound:"dentist_g03.wav", text: "#dentist_defenses_are_weak" }
		dentist_need_more_workers { sound:"dentist_g04.wav", text: "#dentist_need_more_workers" }
		dentist_gods_are_angry { sound:"dentist_g05.wav", text: "#dentist_gods_are_angry" }
		dentist_reputation_is_low { sound:"dentist_g06.wav", text: "#dentist_reputation_is_low" }
		dentist_unemployment_is_high { sound:"dentist_g07.wav", text: "#dentist_much_unemployments" }
		dentist_low_entertainment { sound:"dentist_g08.wav", text: "#dentist_low_entertainment" }
		dentist_city_is_ok { sound:"dentist_g09.wav", text: "#dentist_city_is_ok" }
		dentist_city_is_the_best { sound:"dentist_g10.wav", text: "#dentist_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

function figure_dentist_gods_are_angry() {
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

function figure_dentist_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 40) {
		keys.push("dentist_concerned_about_plague")
	}

	if (city.num_forts < 1) {
		keys.push("dentist_defenses_weak")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("dentist_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("dentist_need_more_workers")
	}

	if (figure_dentist_gods_are_angry()) {
		keys.push("dentist_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("dentist_reputation_is_low")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("dentist_unemployment_is_high")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("dentist_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("dentist_city_is_the_best")
	} else if (sentiment > 50) {
		keys.push("dentist_city_is_ok")
	}

	if (keys.length == 0) {
		return "dentist_city_is_ok"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_dentist, setup_phrase)]
function figure_dentist_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_dentist_city_phrase_key())
}
