log_info("akhenaten: figure protestor started")

figure_protestor {
	overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:32, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:33, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PROTESTER }
	}

	sounds {
		protestor_we_want_justice { sound:"protestor_we_want_justice.wav", text: "#protestor_we_want_justice" }
		protestor_tax_too_high { sound:"protestor_tax_too_high.wav", text: "#protestor_tax_too_high" }
		protestor_wages_too_low { sound:"protestor_wages_too_low.wav", text: "#protestor_wages_too_low" }
		protestor_no_jobs { sound:"protestor_no_jobs.wav", text: "#protestor_no_jobs" }
		protestor_no_food_in_city { sound:"protestor_no_food_in_city.wav", text: "#protestor_no_food_in_city" }
		protestor_city_have_no_army { sound:"protestor_city_have_no_army.wav", text: "#protestor_city_have_no_army" }
		protestor_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		protestor_gods_are_angry { sound:"protestor_gods_are_angry.wav", text: "#protestor_gods_are_angry" }
		protestor_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		protestor_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		protestor_low_entertainment { sound:"protestor_low_entertainment.wav", text: "#protestor_low_entertainment" }
		protestor_city_is_good { sound:"protestor_city_is_good.wav", text: "#protestor_city_is_good" }
		protestor_city_is_amazing { sound:"protestor_city_is_amazing.wav", text: "#protestor_city_is_amazing" }
	}

	category : figure_category_criminal
	max_damage : 12
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
}

function figure_protestor_gods_are_angry() {
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

function figure_protestor_phrase_key() {
	var mood_cause = city.sentiment.low_mood_cause

	// Protestors form around a concrete grievance — prefer that first.
	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		return "protestor_tax_too_high"
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		return "protestor_wages_too_low"
	}
	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		return "protestor_no_jobs"
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		return "protestor_no_food_in_city"
	}

	var keys = []
	var sentiment = city.sentiment.value

	keys.push("protestor_we_want_justice")

	if (city.num_forts < 1) {
		keys.push("protestor_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("protestor_need_workers")
	}

	if (figure_protestor_gods_are_angry()) {
		keys.push("protestor_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("protestor_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("protestor_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("protestor_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("protestor_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("protestor_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_protestor, setup_phrase)]
function figure_protestor_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_protestor_phrase_key())
}
