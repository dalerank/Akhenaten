log_info("akhenaten: figure tomb_artisan started")

// TODO: dump SprMain2 / Expansion walk/work/death ids — temporarily reuse bricklayer SprMain.
figure_tomb_artisan {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:109, max_frames:12 }
		death { id:110, max_frames:8, loop:false }
		work { id:111, max_frames:12, duration:4 }
		idle { id:112, max_frames:8, duration:2 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TOMB_ARTISAN }
	}

	sounds {
		tomb_artisan_ready { sound:"artisan_e01.wav", text: "#tomb_artisan_ready" }
		tomb_artisan_going_to_work { sound:"artisan_e01.wav", text: "#tomb_artisan_going_to_work" }
		tomb_artisan_decorating { sound:"artisan_e02.wav", text: "#tomb_artisan_decorating" }
		tomb_artisan_return_home { sound:"artisan_e02.wav", text: "#tomb_artisan_return_home" }
		tomb_artisan_disease_risk { sound:"tomb_artisan_disease_risk.wav", text: "#tomb_artisan_disease_risk" }
		tomb_artisan_no_food_in_city { sound:"tomb_artisan_no_food_in_city.wav", text: "#tomb_artisan_no_food_in_city" }
		tomb_artisan_city_have_no_army { sound:"tomb_artisan_city_have_no_army.wav", text: "#tomb_artisan_city_have_no_army" }
		tomb_artisan_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		tomb_artisan_gods_are_angry { sound:"tomb_artisan_gods_are_angry.wav", text: "#tomb_artisan_gods_are_angry" }
		tomb_artisan_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		tomb_artisan_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		tomb_artisan_low_entertainment { sound:"tomb_artisan_low_entertainment.wav", text: "#tomb_artisan_low_entertainment" }
		tomb_artisan_city_is_good { sound:"tomb_artisan_city_is_good.wav", text: "#tomb_artisan_city_is_good" }
		tomb_artisan_city_is_amazing { sound:"tomb_artisan_city_is_amazing.wav", text: "#tomb_artisan_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS,
}

function figure_tomb_artisan_gods_are_angry() {
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

function figure_tomb_artisan_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("tomb_artisan_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("tomb_artisan_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("tomb_artisan_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("tomb_artisan_need_workers")
	}

	if (figure_tomb_artisan_gods_are_angry()) {
		keys.push("tomb_artisan_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("tomb_artisan_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("tomb_artisan_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("tomb_artisan_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("tomb_artisan_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("tomb_artisan_city_is_amazing")
	}

	if (keys.length == 0) {
		return "tomb_artisan_decorating"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_tomb_artisan, setup_phrase)]
function figure_tomb_artisan_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case 10: // ACTION_10_TOMB_ARTISAN_CREATED
		figure_apply_phrase(f, "tomb_artisan_ready")
		return
	case 11: // ACTION_11_TOMB_ARTISAN_GOING
		figure_apply_phrase(f, "tomb_artisan_going_to_work")
		return
	case 14: // ACTION_14_TOMB_ARTISAN_WORK
		figure_apply_phrase(f, "tomb_artisan_decorating")
		return
	case 16: // ACTION_16_TOMB_ARTISAN_RETURN_HOME
		figure_apply_phrase(f, "tomb_artisan_return_home")
		return
	}

	figure_apply_phrase(f, figure_tomb_artisan_city_phrase_key())
}
