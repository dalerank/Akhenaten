log_info("akhenaten: figure reed_gatherer started")

figure_reed_gatherer {
	animations {
		walk { pack:PACK_SPR_MAIN, id:37, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:38, max_frames:8, loop:false }
		work { pack:PACK_SPR_MAIN, id:39, max_frames:15 }
		back { pack:PACK_SPR_MAIN, id:40, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_REED_GATHERER }
	}

	sounds {
		reed_to_the_marsh_i_march { sound: "REED_E01.WAV", text: "#reed_to_the_marsh_i_march" }
		reed_will_make_some_fine_papyrus { sound: "REED_E02.WAV", text: "#reed_will_make_some_fine_papyrus" }
		reed_disease_risk { sound: "reed_disease_risk.wav", text: "#reed_disease_risk" }
		reed_no_food_in_city { sound: "reed_no_food_in_city.wav", text: "#reed_no_food_in_city" }
		reed_city_have_no_army { sound: "reed_city_have_no_army.wav", text: "#reed_city_have_no_army" }
		reed_need_workers { sound: "hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		reed_gods_are_angry { sound: "reed_gods_are_angry.wav", text: "#reed_gods_are_angry" }
		reed_city_is_bad { sound: "hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		reed_much_unemployment { sound: "hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		reed_low_entertainment { sound: "reed_low_entertainment.wav", text: "#reed_low_entertainment" }
		reed_city_is_good { sound: "reed_city_is_good.wav", text: "#reed_city_is_good" }
		reed_city_is_amazing { sound: "reed_city_is_amazing.wav", text: "#reed_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ANY,
	max_amount : 25,
}

function figure_reed_gatherer_gods_are_angry() {
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

function figure_reed_gatherer_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("reed_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("reed_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("reed_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("reed_need_workers")
	}

	if (figure_reed_gatherer_gods_are_angry()) {
		keys.push("reed_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("reed_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("reed_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("reed_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("reed_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("reed_city_is_amazing")
	}

	return keys
}

[es=(figure_reed_gatherer, setup_phrase)]
function figure_reed_gatherer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = []
	var state = f.action_state
	switch (state) {
	case 8:  // ACTION_8_REED_GATHERER_RECALCULATE
	case 14: // ACTION_14_REED_GATHERER_CREATED
	case 9:  // ACTION_9_REED_GATHERER_GOTO_RESOURCE
		keys.push("reed_to_the_marsh_i_march")
		break
	case 10: // ACTION_10_REED_GATHERER_WORK
	case 11: // ACTION_11_REED_GATHERER_RETURN_HOME
		keys.push("reed_will_make_some_fine_papyrus")
		break
	}

	var city_keys = figure_reed_gatherer_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("reed_to_the_marsh_i_march")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
