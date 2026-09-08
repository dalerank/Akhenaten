log_info("akhenaten: figure noble started")

figure_noble {
	animations {
		walk { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_NOBLES }
	}

	sounds {
		noble_taking_a_stroll { sound:"noble_taking_a_stroll.wav", text: "#noble_taking_a_stroll" }
		noble_returning_home { sound:"noble_returning_home.wav", text: "#noble_returning_home" }
		noble_disease_risk { sound:"noble_disease_risk.wav", text: "#noble_disease_risk" }
		noble_no_food_in_city { sound:"noble_no_food_in_city.wav", text: "#noble_no_food_in_city" }
		noble_city_have_no_army { sound:"noble_city_have_no_army.wav", text: "#noble_city_have_no_army" }
		noble_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		noble_gods_are_angry { sound:"noble_gods_are_angry.wav", text: "#noble_gods_are_angry" }
		noble_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		noble_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		noble_low_entertainment { sound:"noble_low_entertainment.wav", text: "#noble_low_entertainment" }
		noble_city_is_good { sound:"noble_city_is_good.wav", text: "#noble_city_is_good" }
		noble_city_is_amazing { sound:"noble_city_is_amazing.wav", text: "#noble_city_is_amazing" }
	}

	category: figure_category_native
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ROADS
}

function figure_noble_gods_are_angry() {
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

function figure_noble_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("noble_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("noble_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("noble_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("noble_need_workers")
	}

	if (figure_noble_gods_are_angry()) {
		keys.push("noble_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("noble_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("noble_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("noble_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("noble_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("noble_city_is_amazing")
	}

	return keys
}

[es=(figure_noble, setup_phrase)]
function figure_noble_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = []
	var state = f.action_state
	switch (state) {
	case ACTION_0_NOBLE_ROAMING:
		keys.push("noble_taking_a_stroll")
		break
	case ACTION_1_NOBLE_RETURNING:
		keys.push("noble_returning_home")
		break
	}

	var city_keys = figure_noble_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("noble_taking_a_stroll")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
