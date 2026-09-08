log_info("akhenaten: figure emigrant started")

figure_emigrant {
	animations {
		walk { pack:PACK_SPR_MAIN, id:2, max_frames:12 }
		death { pack: PACK_SPR_MAIN, id:3, max_frames:8, loop:false }
		cart { pack:PACK_SPR_MAIN, id:52, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_EMIGRANT }
	}

	sounds {
		emigrant_no_job_in_city { sound:"emigrant_e01.wav", text: "#emigrant_no_job_in_city" }
		emigrant_no_food_in_city { sound:"emigrant_e02.wav", text: "#emigrant_no_food_in_city" }
		emigrant_tax_too_high { sound:"emigrant_e03.wav", text: "#emigrant_tax_too_high" }
		emigrant_salary_too_low { sound:"emigrant_e04.wav", text: "#emigrant_salary_too_low" }
		emigrant_no_house_for_me { sound:"emigrant_e05.wav", text: "#emigrant_no_house_for_me" }
		emigrant_disease_risk { sound:"emigrant_disease_risk.wav", text: "#emigrant_disease_risk" }
		emigrant_city_have_no_army { sound:"emigrant_city_have_no_army.wav", text: "#emigrant_city_have_no_army" }
		emigrant_need_workers { sound:"emigrant_need_workers.wav", text: "#emigrant_need_workers" }
		emigrant_gods_are_angry { sound:"emigrant_gods_are_angry.wav", text: "#emigrant_gods_are_angry" }
		emigrant_city_is_bad { sound:"emigrant_city_is_bad.wav", text: "#emigrant_city_is_bad" }
		emigrant_low_entertainment { sound:"emigrant_low_entertainment.wav", text: "#emigrant_low_entertainment" }
		emigrant_city_is_good { sound:"emigrant_city_is_good.wav", text: "#emigrant_city_is_good" }
		emigrant_city_is_amazing { sound:"emigrant_city_is_amazing.wav", text: "#emigrant_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ANIMAL,
}

function figure_emigrant_gods_are_angry() {
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

function figure_emigrant_phrase_key(f) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("emigrant_no_job_in_city")
	}
	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("emigrant_no_food_in_city")
	}
	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		keys.push("emigrant_tax_too_high")
	}
	if (mood_cause == 4) { // LOW_MOOD_LOW_WAGES
		keys.push("emigrant_salary_too_low")
	}
	if (mood_cause == 5 || !f.destination_building_id) { // LOW_MOOD_MANY_TENTS
		keys.push("emigrant_no_house_for_me")
	}

	if (city.health_rating < 30) {
		keys.push("emigrant_disease_risk")
	}

	if (city.num_forts < 1) {
		keys.push("emigrant_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("emigrant_need_workers")
	}

	if (figure_emigrant_gods_are_angry()) {
		keys.push("emigrant_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("emigrant_city_is_bad")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("emigrant_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("emigrant_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("emigrant_city_is_good")
	}

	if (keys.length == 0) {
		return "emigrant_no_house_for_me"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_emigrant, setup_phrase)]
function figure_emigrant_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_emigrant_phrase_key(f))
}
