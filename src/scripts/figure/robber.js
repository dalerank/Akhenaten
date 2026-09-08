log_info("akhenaten: figure robber started")

figure_robber {
	overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:32, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:33, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ROBBER }
	}

	sounds {
		robber_maybe_stealing_will_get_attention { sound: "thief_e01.wav", text: "#robber_maybe_stealing_will_get_attention" }
		robber_i_take_what_i_want { sound: "thief_e02.wav", text: "#robber_i_take_what_i_want" }
		robber_more_profitable_than_other_jobs { sound: "thief_e03.wav", text: "#robber_more_profitable_than_other_jobs" }
		robber_take_take_take { sound: "thief_e04.wav", text: "#robber_take_take_take" }
		robber_tax_too_high { sound: "robber_tax_too_high.wav", text: "#robber_tax_too_high" }
		robber_wages_too_low { sound: "robber_wages_too_low.wav", text: "#robber_wages_too_low" }
		robber_no_jobs { sound: "robber_no_jobs.wav", text: "#robber_no_jobs" }
		robber_no_food_in_city { sound: "robber_no_food_in_city.wav", text: "#robber_no_food_in_city" }
		robber_city_have_no_army { sound: "robber_city_have_no_army.wav", text: "#robber_city_have_no_army" }
		robber_need_workers { sound: "hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		robber_gods_are_angry { sound: "robber_gods_are_angry.wav", text: "#robber_gods_are_angry" }
		robber_city_is_bad { sound: "hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		robber_much_unemployment { sound: "hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		robber_low_entertainment { sound: "robber_low_entertainment.wav", text: "#robber_low_entertainment" }
		robber_city_is_good { sound: "robber_city_is_good.wav", text: "#robber_city_is_good" }
		robber_city_is_amazing { sound: "robber_city_is_amazing.wav", text: "#robber_city_is_amazing" }
	}

	category : figure_category_criminal
	max_damage : 12
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
}

function figure_robber_gods_are_angry() {
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

function figure_robber_phrase_key() {
	var mood_cause = city.sentiment.low_mood_cause

	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "robber_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "robber_wages_too_low"
	}
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "robber_no_jobs"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "robber_no_food_in_city"
	}

	var keys = []
	var sentiment = city.sentiment.value

	keys.push("robber_maybe_stealing_will_get_attention")
	keys.push("robber_i_take_what_i_want")
	keys.push("robber_more_profitable_than_other_jobs")
	keys.push("robber_take_take_take")

	if (city.num_forts < 1) {
		keys.push("robber_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("robber_need_workers")
	}

	if (figure_robber_gods_are_angry()) {
		keys.push("robber_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("robber_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("robber_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("robber_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("robber_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("robber_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_robber, setup_phrase)]
function figure_robber_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_robber_phrase_key())
}
