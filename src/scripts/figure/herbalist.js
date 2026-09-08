log_info("akhenaten: figure herbalist started")

figure_herbalist {
	overlay : OVERLAY_APOTHECARY
	animations {
		walk { pack:PACK_SPR_MAIN, id:180, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:181, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_HERBALIST }
	}

	sounds {
		malaria_not_a_problem { sound:"apothecary_e02.wav", text: "#malaria_not_a_problem" }
		malaria_outbreak_could_strike { sound:"apothecary_e03.wav", text: "#malaria_outbreak_could_strike" }
		herbalist_no_food_in_city { sound:"herbalist_no_food_in_city.wav", text: "#herbalist_no_food_in_city" }
		herbalist_city_have_no_army { sound:"herbalist_city_have_no_army.wav", text: "#herbalist_city_have_no_army" }
		herbalist_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		herbalist_gods_are_angry { sound:"herbalist_gods_are_angry.wav", text: "#herbalist_gods_are_angry" }
		herbalist_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		herbalist_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		herbalist_low_entertainment { sound:"herbalist_low_entertainment.wav", text: "#herbalist_low_entertainment" }
		herbalist_city_is_good { sound:"herbalist_city_is_good.wav", text: "#herbalist_city_is_good" }
		herbalist_city_is_amazing { sound:"herbalist_city_is_amazing.wav", text: "#herbalist_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_medicine
}

function figure_herbalist_gods_are_angry() {
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

function figure_herbalist_city_phrase_keys(f) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (f.min_max_seen > 0) {
		keys.push("malaria_outbreak_could_strike")
	} else {
		keys.push("malaria_not_a_problem")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("herbalist_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("herbalist_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("herbalist_need_workers")
	}

	if (figure_herbalist_gods_are_angry()) {
		keys.push("herbalist_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("herbalist_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("herbalist_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("herbalist_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("herbalist_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("herbalist_city_is_amazing")
	}

	return keys
}

[es=(figure_herbalist, setup_phrase)]
function figure_herbalist_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_herbalist_city_phrase_keys(f)
	if (keys.length == 0) {
		keys.push("malaria_not_a_problem")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
