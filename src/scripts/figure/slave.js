log_info("akhenaten: figure slave started")

figure_slave {
	animations {
		walk { pack:PACK_SPR_MAIN, id:45, max_frames:12 }
		cart { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SLAVE }
	}

	sounds {
		slave_break_our_chains { sound:"slave_break_our_chains.wav", text: "#slave_break_our_chains" }
		slave_tax_too_high { sound:"slave_tax_too_high.wav", text: "#slave_tax_too_high" }
		slave_wages_too_low { sound:"slave_wages_too_low.wav", text: "#slave_wages_too_low" }
		slave_no_jobs { sound:"slave_no_jobs.wav", text: "#slave_no_jobs" }
		slave_no_food_in_city { sound:"slave_no_food_in_city.wav", text: "#slave_no_food_in_city" }
		slave_city_have_no_army { sound:"slave_city_have_no_army.wav", text: "#slave_city_have_no_army" }
		slave_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		slave_gods_are_angry { sound:"slave_gods_are_angry.wav", text: "#slave_gods_are_angry" }
		slave_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		slave_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		slave_low_entertainment { sound:"slave_low_entertainment.wav", text: "#slave_low_entertainment" }
		slave_city_is_good { sound:"slave_city_is_good.wav", text: "#slave_city_is_good" }
		slave_city_is_amazing { sound:"slave_city_is_amazing.wav", text: "#slave_city_is_amazing" }
	}

	category: figure_category_native
	max_damage: 10
}

function figure_slave_gods_are_angry() {
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

function figure_slave_phrase_key() {
	var mood_cause = city.sentiment.low_mood_cause

	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "slave_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "slave_wages_too_low"
	}
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "slave_no_jobs"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "slave_no_food_in_city"
	}

	var keys = []
	var sentiment = city.sentiment.value

	keys.push("slave_break_our_chains")

	if (city.num_forts < 1) {
		keys.push("slave_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("slave_need_workers")
	}

	if (figure_slave_gods_are_angry()) {
		keys.push("slave_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("slave_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("slave_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("slave_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("slave_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("slave_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_slave, setup_phrase)]
function figure_slave_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_slave_phrase_key())
}
