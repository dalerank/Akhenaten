log_info("akhenaten: figure magistrate started")

figure_magistrate {
	overlay : OVERLAY_COUTHOUSE
	animations {
		walk { pack: PACK_SPR_MAIN, id: 212, max_frames:12 }
		death { pack: PACK_SPR_MAIN, id: 213, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MAGISTRATE }
	}

	sounds {
		magistrate_i_hope_we_are_ready { sound: "magistrate_e02.wav", text: "#magistrate_i_hope_we_are_ready" }
		magistrate_no_criminals_in_city { sound: "magistrate_e03.wav", text: "#magistrate_no_criminals_in_city" }
		magistrate_all_good_in_city { sound: "magistrate_e04.wav", text: "#magistrate_all_good_in_city" }
		magistrate_streets_still_arent_safety { sound: "magistrate_e05.wav", text: "#magistrate_streets_still_arent_safety" }
		magistrate_disease_in_city { sound: "magistrate_g01.wav", text: "#magistrate_disease_in_city" }
		magistrate_no_food_in_city { sound: "magistrate_g02.wav", text: "#magistrate_no_food_in_city" }
		magistrate_city_not_safety { sound: "magistrate_g03.wav", text: "#magistrate_city_not_safety" }
		magistrate_need_workers { sound: "magistrate_g04.wav", text: "#magistrate_need_workers" }
		magistrate_gods_are_angry { sound: "magistrate_g05.wav", text: "#magistrate_gods_are_angry" }
		magistrate_city_bad_reputation { sound: "magistrate_g06.wav", text: "#magistrate_city_bad_reputation" }
		magistrate_much_unemployments { sound: "magistrate_g07.wav", text: "#magistrate_much_unemployments" }
		magistrate_no_entertainment_need { sound: "magistrate_g08.wav", text: "#magistrate_no_entertainment_need" }
		magistrate_city_not_bad { sound: "magistrate_g09.wav", text: "#magistrate_city_not_bad" }
		magistrate_city_is_amazing { sound: "magistrate_g10.wav", text: "#magistrate_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	meta { text_id: 210, help_link:"message_history_defensive_structures" }
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 800
}

function figure_magistrate_gods_are_angry() {
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

function figure_magistrate_city_phrase_key(f) {
	// C++ scanned houses for disease_days and returned early; health rating is the JS proxy.
	if (city.health_rating < 40) {
		return "magistrate_disease_in_city"
	}

	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.sentiment.criminals <= 0) {
		keys.push("magistrate_no_criminals_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("magistrate_city_not_safety")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("magistrate_need_workers")
	}

	if (figure_magistrate_gods_are_angry()) {
		keys.push("magistrate_gods_are_angry")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("magistrate_no_food_in_city")
	}

	if (city.kingdome.rating < 10) {
		keys.push("magistrate_city_bad_reputation")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("magistrate_much_unemployments")
	}

	if (city.houses.missing.more_entertainment > 0) {
		keys.push("magistrate_no_entertainment_need")
	}

	if (sentiment > 90) {
		keys.push("magistrate_city_is_amazing")
	} else if (sentiment > 30) {
		keys.push("magistrate_city_not_bad")
	}

	if (f.min_max_seen > 60) {
		keys.push("magistrate_all_good_in_city")
	} else {
		keys.push("magistrate_streets_still_arent_safety")
	}

	keys.push("magistrate_i_hope_we_are_ready")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_magistrate, setup_phrase)]
function figure_magistrate_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_magistrate_city_phrase_key(f))
}
