log_info("akhenaten: figure lumberjack started")

figure_lumberjack {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk  { id:73, max_frames:12 }
		death { id:74, max_frames:8, loop:false  }
		work  { id:75, max_frames:12 }
		back  { id:76, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LUMBERJACK }
	}

	sounds {
		lumberjack_hunting { sound:"woodcutter_e01.wav", text: "#lumberjack_hunting" }
		lumberjack_back { sound:"woodcutter_e02.wav", text: "#lumberjack_back" }
		lumberjack_disease_risk { sound:"lumberjack_disease_risk.wav", text: "#lumberjack_disease_risk" }
		lumberjack_no_food_in_city { sound:"lumberjack_no_food_in_city.wav", text: "#lumberjack_no_food_in_city" }
		lumberjack_city_have_no_army { sound:"lumberjack_city_have_no_army.wav", text: "#lumberjack_city_have_no_army" }
		lumberjack_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		lumberjack_gods_are_angry { sound:"lumberjack_gods_are_angry.wav", text: "#lumberjack_gods_are_angry" }
		lumberjack_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		lumberjack_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		lumberjack_low_entertainment { sound:"lumberjack_low_entertainment.wav", text: "#lumberjack_low_entertainment" }
		lumberjack_city_is_good { sound:"lumberjack_city_is_good.wav", text: "#lumberjack_city_is_good" }
		lumberjack_city_is_amazing { sound:"lumberjack_city_is_amazing.wav", text: "#lumberjack_city_is_amazing" }
	}

	category: figure_category_armed
	max_damage: 40
	attack_value: 4
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 50
}

function figure_lumberjack_gods_are_angry() {
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

function figure_lumberjack_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("lumberjack_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("lumberjack_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("lumberjack_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("lumberjack_need_workers")
	}

	if (figure_lumberjack_gods_are_angry()) {
		keys.push("lumberjack_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("lumberjack_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("lumberjack_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("lumberjack_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("lumberjack_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("lumberjack_city_is_amazing")
	}

	return keys
}

[es=(figure_lumberjack, setup_phrase)]
function figure_lumberjack_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = []
	var state = f.action_state
	switch (state) {
	case ACTION_0_LUMBERJACK_CREATED:
	case ACTION_1_LUMBERJACK_RECALCULATE:
	case ACTION_2_LUMBERJACK_GOTO_RESOURCE:
	case ACTION_3_LUMBERJACK_WORK:
		keys.push("lumberjack_hunting")
		break
	case ACTION_4_LUMBERJACK_RETURN_HOME:
		keys.push("lumberjack_back")
		break
	}

	var city_keys = figure_lumberjack_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("lumberjack_hunting")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
