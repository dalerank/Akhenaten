log_info("akhenaten: figure embalmer started")

figure_embalmer {
	overlay : OVERLAY_MORTUARY
	animations {
		walk { pack:PACK_SPR_MAIN, id:195, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:196, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_EMBALMER }
	}

	sounds {
		embalmer_health_worsening { sound:"embalmer_e01.WAV", text: "#embalmer_health_worsening" }
		embalmer_concerned_about_plague { sound:"embalmer_g01.WAV", text: "#embalmer_concerned_about_plague" }
		embalmer_no_food_in_city { sound:"embalmer_g02.WAV", text: "#embalmer_no_food_in_city" }
		embalmer_defenses_weak { sound:"embalmer_g03.WAV", text: "#embalmer_defenses_weak" }
		embalmer_need_more_workers { sound:"embalmer_g04.WAV", text: "#embalmer_need_more_workers" }
		embalmer_gods_are_angry { sound:"embalmer_g05.WAV", text: "#embalmer_gods_are_angry" }
		embalmer_reputation_is_low { sound:"embalmer_g06.WAV", text: "#embalmer_reputation_is_low" }
		embalmer_unemployment_is_high { sound:"embalmer_g07.WAV", text: "#embalmer_unemployment_is_high" }
		embalmer_low_entertainment { sound:"embalmer_g08.WAV", text: "#embalmer_low_entertainment" }
		embalmer_city_is_ok { sound:"embalmer_g09.WAV", text: "#embalmer_city_is_ok" }
		embalmer_city_is_the_best { sound:"embalmer_g10.WAV", text: "#embalmer_city_is_the_best" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

function figure_embalmer_gods_are_angry() {
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

function figure_embalmer_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value
	var health = city.health_rating

	if (health < 20) {
		keys.push("embalmer_concerned_about_plague")
	} else if (health < 40) {
		keys.push("embalmer_health_worsening")
	}

	if (city.num_forts < 1) {
		keys.push("embalmer_defenses_weak")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("embalmer_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("embalmer_need_more_workers")
	}

	if (figure_embalmer_gods_are_angry()) {
		keys.push("embalmer_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("embalmer_reputation_is_low")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("embalmer_unemployment_is_high")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("embalmer_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("embalmer_city_is_the_best")
	} else if (sentiment > 50) {
		keys.push("embalmer_city_is_ok")
	}

	if (keys.length == 0) {
		return "embalmer_city_is_ok"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_embalmer, setup_phrase)]
function figure_embalmer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_embalmer_city_phrase_key())
}
