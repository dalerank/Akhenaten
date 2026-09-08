log_info("akhenaten: figure governor started")

figure_governor {
	animations {
		walk { pack: PACK_SPR_MAIN, id:189, max_frames:12 }
		death { pack: PACK_SPR_MAIN, id:190, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_GOVERNOR }
	}

	sounds {
		governor_city_left_much_nobles { sound:"governor_e01.wav", text: "#governor_city_left_much_nobles" }
		governor_festival_was_near { sound:"governor_e02.wav", text: "#governor_festival_was_near" }
		governor_disease_risk { sound:"governor_disease_risk.wav", text: "#governor_disease_risk" }
		governor_no_food_in_city { sound:"governor_no_food_in_city.wav", text: "#governor_no_food_in_city" }
		governor_city_have_no_army { sound:"governor_city_have_no_army.wav", text: "#governor_city_have_no_army" }
		governor_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		governor_gods_are_angry { sound:"governor_gods_are_angry.wav", text: "#governor_gods_are_angry" }
		governor_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		governor_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		governor_low_entertainment { sound:"governor_low_entertainment.wav", text: "#governor_low_entertainment" }
		governor_city_is_good { sound:"governor_city_is_good.wav", text: "#governor_city_is_good" }
		governor_city_is_amazing { sound:"governor_city_is_amazing.wav", text: "#governor_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ROADS
}

function figure_governor_gods_are_angry() {
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

function figure_governor_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	var nobles = city.population_stats.people_in_manors
	var nobles_left = __city_migration.nobles_leave_city_this_year
	if (nobles > 0 && Math.floor((100 * nobles_left) / nobles) > 10) {
		keys.push("governor_city_left_much_nobles")
	}

	if (__city_festival.months_since_festival < 6) {
		keys.push("governor_festival_was_near")
	}

	if (city.health_rating < 30) {
		keys.push("governor_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("governor_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("governor_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("governor_need_workers")
	}

	if (figure_governor_gods_are_angry()) {
		keys.push("governor_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("governor_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("governor_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("governor_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("governor_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("governor_city_is_amazing")
	}

	return keys
}

[es=(figure_governor, setup_phrase)]
function figure_governor_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_governor_city_phrase_keys()
	if (keys.length == 0) {
		keys.push("governor_festival_was_near")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
