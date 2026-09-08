log_info("akhenaten: figure rioter started")

figure_rioter {
	overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:29, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:30, max_frames:8, loop:false }
		attack { pack:PACK_SPR_MAIN, id:31, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_RIOTER }
	}

	sounds {
		rioter_burn_it_down { sound:"rioter_burn_it_down.wav", text: "#rioter_burn_it_down" }
		rioter_tax_too_high { sound:"rioter_tax_too_high.wav", text: "#rioter_tax_too_high" }
		rioter_wages_too_low { sound:"rioter_wages_too_low.wav", text: "#rioter_wages_too_low" }
		rioter_no_jobs { sound:"rioter_no_jobs.wav", text: "#rioter_no_jobs" }
		rioter_no_food_in_city { sound:"rioter_no_food_in_city.wav", text: "#rioter_no_food_in_city" }
		rioter_city_have_no_army { sound:"rioter_city_have_no_army.wav", text: "#rioter_city_have_no_army" }
		rioter_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		rioter_gods_are_angry { sound:"rioter_gods_are_angry.wav", text: "#rioter_gods_are_angry" }
		rioter_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		rioter_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		rioter_low_entertainment { sound:"rioter_low_entertainment.wav", text: "#rioter_low_entertainment" }
		rioter_city_is_good { sound:"rioter_city_is_good.wav", text: "#rioter_city_is_good" }
		rioter_city_is_amazing { sound:"rioter_city_is_amazing.wav", text: "#rioter_city_is_amazing" }
	}

	category : figure_category_criminal
	max_damage : 12
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
}

function figure_rioter_gods_are_angry() {
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

function figure_rioter_phrase_key() {
	var mood_cause = city.sentiment.low_mood_cause

	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "rioter_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "rioter_wages_too_low"
	}
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "rioter_no_jobs"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "rioter_no_food_in_city"
	}

	var keys = []
	var sentiment = city.sentiment.value

	keys.push("rioter_burn_it_down")

	if (city.num_forts < 1) {
		keys.push("rioter_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("rioter_need_workers")
	}

	if (figure_rioter_gods_are_angry()) {
		keys.push("rioter_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("rioter_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("rioter_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("rioter_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("rioter_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("rioter_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_rioter, setup_phrase)]
function figure_rioter_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_rioter_phrase_key())
}
