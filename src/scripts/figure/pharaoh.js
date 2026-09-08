log_info("akhenaten: figure pharaoh started")

// Cinematic / victory VFX walker — walk-only (SprMain 28); no death group.
figure_pharaoh {
	animations {
		walk { pack:PACK_SPR_MAIN, id:28, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PHARAOH }
	}

	sounds {
		pharaoh_inspecting_city { sound:"pharaoh_e01.wav", text: "#pharaoh_inspecting_city" }
		pharaoh_disease_risk { sound:"pharaoh_disease_risk.wav", text: "#pharaoh_disease_risk" }
		pharaoh_no_food_in_city { sound:"pharaoh_no_food_in_city.wav", text: "#pharaoh_no_food_in_city" }
		pharaoh_city_have_no_army { sound:"pharaoh_city_have_no_army.wav", text: "#pharaoh_city_have_no_army" }
		pharaoh_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		pharaoh_gods_are_angry { sound:"pharaoh_gods_are_angry.wav", text: "#pharaoh_gods_are_angry" }
		pharaoh_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		pharaoh_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		pharaoh_low_entertainment { sound:"pharaoh_low_entertainment.wav", text: "#pharaoh_low_entertainment" }
		pharaoh_city_is_good { sound:"pharaoh_city_is_good.wav", text: "#pharaoh_city_is_good" }
		pharaoh_city_is_amazing { sound:"pharaoh_city_is_amazing.wav", text: "#pharaoh_city_is_amazing" }
	}

	category: figure_category_special
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ANY
	max_amount: 2
	max_roam_length: 320
}

function figure_pharaoh_gods_are_angry() {
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

function figure_pharaoh_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push("pharaoh_inspecting_city")

	if (city.health_rating < 30) {
		keys.push("pharaoh_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("pharaoh_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("pharaoh_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("pharaoh_need_workers")
	}

	if (figure_pharaoh_gods_are_angry()) {
		keys.push("pharaoh_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("pharaoh_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("pharaoh_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("pharaoh_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("pharaoh_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("pharaoh_city_is_amazing")
	}

	return keys
}

[es=(figure_pharaoh, setup_phrase)]
function figure_pharaoh_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_pharaoh_city_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
