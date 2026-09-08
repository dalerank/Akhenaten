log_info("akhenaten: figure funeral_walker started")

figure_funeral_walker {
	animations {
		walk { pack:PACK_SPR_MAIN, id:116, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:117, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FUNERAL_WALKER }
	}

	sounds {
		funeral_walker_ready { sound:"funeral_walker_ready.wav", text: "#funeral_walker_ready" }
		funeral_walker_going_to_tomb { sound:"funeral_walker_going_to_tomb.wav", text: "#funeral_walker_going_to_tomb" }
		funeral_walker_arrived { sound:"funeral_walker_arrived.wav", text: "#funeral_walker_arrived" }
		funeral_walker_lost_path { sound:"funeral_walker_lost_path.wav", text: "#funeral_walker_lost_path" }
		funeral_walker_disease_risk { sound:"funeral_walker_disease_risk.wav", text: "#funeral_walker_disease_risk" }
		funeral_walker_no_food_in_city { sound:"funeral_walker_no_food_in_city.wav", text: "#funeral_walker_no_food_in_city" }
		funeral_walker_city_have_no_army { sound:"funeral_walker_city_have_no_army.wav", text: "#funeral_walker_city_have_no_army" }
		funeral_walker_need_workers { sound:"funeral_walker_need_workers.wav", text: "#funeral_walker_need_workers" }
		funeral_walker_gods_are_angry { sound:"funeral_walker_gods_are_angry.wav", text: "#funeral_walker_gods_are_angry" }
		funeral_walker_city_is_bad { sound:"funeral_walker_city_is_bad.wav", text: "#funeral_walker_city_is_bad" }
		funeral_walker_much_unemployment { sound:"funeral_walker_much_unemployment.wav", text: "#funeral_walker_much_unemployment" }
		funeral_walker_low_entertainment { sound:"funeral_walker_low_entertainment.wav", text: "#funeral_walker_low_entertainment" }
		funeral_walker_city_is_good { sound:"funeral_walker_city_is_good.wav", text: "#funeral_walker_city_is_good" }
		funeral_walker_city_is_amazing { sound:"funeral_walker_city_is_amazing.wav", text: "#funeral_walker_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY
	max_amount: 8
}

function figure_funeral_walker_gods_are_angry() {
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

function figure_funeral_walker_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("funeral_walker_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("funeral_walker_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("funeral_walker_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("funeral_walker_need_workers")
	}

	if (figure_funeral_walker_gods_are_angry()) {
		keys.push("funeral_walker_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("funeral_walker_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("funeral_walker_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("funeral_walker_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("funeral_walker_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("funeral_walker_city_is_amazing")
	}

	if (keys.length == 0) {
		return "funeral_walker_ready"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_funeral_walker_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_0_FUNERAL_CREATED:
		return "funeral_walker_ready"
	case ACTION_1_FUNERAL_GOING_TO_TOMB:
		return "funeral_walker_going_to_tomb"
	case ACTION_2_FUNERAL_ARRIVED:
		return "funeral_walker_arrived"
	case ACTION_3_FUNERAL_ABORT:
		return "funeral_walker_lost_path"
	}

	return figure_funeral_walker_city_phrase_key()
}

[es=(figure_funeral_walker, setup_phrase)]
function figure_funeral_walker_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case ACTION_0_FUNERAL_CREATED:
	case ACTION_1_FUNERAL_GOING_TO_TOMB:
	case ACTION_2_FUNERAL_ARRIVED:
	case ACTION_3_FUNERAL_ABORT:
		figure_apply_phrase(f, figure_funeral_walker_phrase_key(f))
		return
	}

	figure_apply_phrase(f, figure_funeral_walker_city_phrase_key())
}
