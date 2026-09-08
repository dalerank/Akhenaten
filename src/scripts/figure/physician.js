log_info("akhenaten: figure physician started")

figure_physician {
	overlay : OVERLAY_PHYSICIAN
	animations {
		walk { pack:PACK_SPR_MAIN, id:71, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:72, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PHYSICIAN }
	}

	sounds {
		doctor_plague_could_strike_us_dead { sound:"doctor_e01.wav", text: "#doctor_plague_could_strike_us_dead" }
		doctor_concerned_about_plague { sound:"doctor_g01.wav", text: "#doctor_concerned_about_plague" }
		doctor_no_food_in_city { sound:"doctor_g02.wav", text: "#doctor_no_food_in_city" }
		doctor_defenses_weak { sound:"doctor_g03.wav", text: "#doctor_defenses_are_weak" }
		doctor_need_more_workers { sound:"doctor_g04.wav", text: "#doctor_need_more_workers" }
		doctor_gods_are_angry { sound:"doctor_g05.wav", text: "#doctor_gods_are_angry" }
		doctor_reputation_is_low { sound:"doctor_g06.wav", text: "#doctor_reputation_is_low" }
		doctor_unemployment_is_high { sound:"doctor_g07.wav", text: "#doctor_unemployment_is_high" }
		doctor_low_entertainment { sound:"doctor_g08.wav", text: "#doctor_low_entertainment" }
		doctor_city_is_ok { sound:"doctor_g09.wav", text: "#doctor_city_is_ok" }
		doctor_city_is_the_best { sound:"doctor_g10.wav", text: "#doctor_city_is_the_best" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
	health_heal_amount : 1
}

function figure_physician_gods_are_angry() {
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

function figure_physician_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var health = city.health_rating

	if (health < 20) {
		keys.push("doctor_plague_could_strike_us_dead")
	} else if (health < 40) {
		keys.push("doctor_concerned_about_plague")
	} else if (health > 80) {
		keys.push("doctor_city_is_the_best")
	}

	if (city.num_forts < 1) {
		keys.push("doctor_defenses_weak")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("doctor_no_food_in_city")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("doctor_unemployment_is_high")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("doctor_need_more_workers")
	}

	if (figure_physician_gods_are_angry()) {
		keys.push("doctor_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("doctor_reputation_is_low")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("doctor_low_entertainment")
	}

	if (keys.length == 0) {
		return "doctor_city_is_ok"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_physician, setup_phrase)]
function figure_physician_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_physician_city_phrase_key())
}
