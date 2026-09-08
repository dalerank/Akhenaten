log_info("akhenaten: figure tomb_robber started")

figure_tomb_robber {
	overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:32, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:33, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TOMB_ROBER }
	}

	sounds {
		tomb_robber_gold_should_be_for_living { sound: "robber_e01.wav", text: "#tomb_robber_gold_should_be_for_living" }
		tomb_robber_just_think_of_the_fortune { sound: "robber_e02.wav", text: "#tomb_robber_just_think_of_the_fortune" }
		tomb_robber_tax_too_high { sound: "robber_tax_too_high.wav", text: "#tomb_robber_tax_too_high" }
		tomb_robber_wages_too_low { sound: "robber_wages_too_low.wav", text: "#tomb_robber_wages_too_low" }
		tomb_robber_no_jobs { sound: "robber_no_jobs.wav", text: "#tomb_robber_no_jobs" }
		tomb_robber_no_food_in_city { sound: "robber_no_food_in_city.wav", text: "#tomb_robber_no_food_in_city" }
		tomb_robber_city_have_no_army { sound: "robber_city_have_no_army.wav", text: "#tomb_robber_city_have_no_army" }
		tomb_robber_need_workers { sound: "hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		tomb_robber_gods_are_angry { sound: "robber_gods_are_angry.wav", text: "#tomb_robber_gods_are_angry" }
		tomb_robber_city_is_bad { sound: "hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		tomb_robber_much_unemployment { sound: "hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		tomb_robber_low_entertainment { sound: "robber_low_entertainment.wav", text: "#tomb_robber_low_entertainment" }
		tomb_robber_city_is_good { sound: "robber_city_is_good.wav", text: "#tomb_robber_city_is_good" }
		tomb_robber_city_is_amazing { sound: "robber_city_is_amazing.wav", text: "#tomb_robber_city_is_amazing" }
	}

	category : figure_category_criminal
	max_damage : 10
	speed_mult : 2
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
}

function figure_tomb_robber_gods_are_angry() {
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

function figure_tomb_robber_phrase_key(f) {
	var mood_cause = city.sentiment.low_mood_cause

	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "tomb_robber_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "tomb_robber_wages_too_low"
	}
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "tomb_robber_no_jobs"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "tomb_robber_no_food_in_city"
	}

	var state = f.action_state
	switch (state) {
	case 120: // ACTION_120_TOMB_ROBBER_CREATED
	case 121: // ACTION_121_TOMB_ROBBER_GOING_TO_TOMB
		return "tomb_robber_gold_should_be_for_living"
	case 122: // ACTION_122_TOMB_ROBBER_STEALING
		return "tomb_robber_just_think_of_the_fortune"
	case 123: // ACTION_123_TOMB_ROBBER_FLEEING
	case 124: // ACTION_124_TOMB_ROBBER_CAUGHT
		return "tomb_robber_just_think_of_the_fortune"
	}

	var keys = []
	var sentiment = city.sentiment.value

	keys.push("tomb_robber_gold_should_be_for_living")
	keys.push("tomb_robber_just_think_of_the_fortune")

	if (city.num_forts < 1) {
		keys.push("tomb_robber_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("tomb_robber_need_workers")
	}

	if (figure_tomb_robber_gods_are_angry()) {
		keys.push("tomb_robber_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("tomb_robber_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("tomb_robber_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("tomb_robber_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("tomb_robber_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("tomb_robber_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_tomb_robber, setup_phrase)]
function figure_tomb_robber_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_tomb_robber_phrase_key(f))
}
