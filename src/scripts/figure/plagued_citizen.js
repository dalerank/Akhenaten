log_info("akhenaten: figure plagued_citizen started")

// Plague carrier — SprMain GROUP_FIGURE_DESEASED (203/205).
// TEMP: same strip ids as figure_drunkard (art collision; follow-up after pak dump).
figure_plagued_citizen {
	animations {
		walk { pack:PACK_SPR_MAIN, id:203, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:205, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PLAGUED_CITIZEN }
	}

	sounds {
		plagued_i_feel_awful { sound:"disease_e01.wav", text: "#plagued_i_feel_awful" }
		plagued_fever_spreads { sound:"plagued_fever_spreads.wav", text: "#plagued_fever_spreads" }
		plagued_no_food_in_city { sound:"plagued_no_food_in_city.wav", text: "#plagued_no_food_in_city" }
		plagued_city_have_no_army { sound:"plagued_city_have_no_army.wav", text: "#plagued_city_have_no_army" }
		plagued_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		plagued_gods_are_angry { sound:"plagued_gods_are_angry.wav", text: "#plagued_gods_are_angry" }
		plagued_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		plagued_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		plagued_low_entertainment { sound:"plagued_low_entertainment.wav", text: "#plagued_low_entertainment" }
		plagued_city_is_good { sound:"plagued_city_is_good.wav", text: "#plagued_city_is_good" }
		plagued_city_is_amazing { sound:"plagued_city_is_amazing.wav", text: "#plagued_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ROADS
	max_roam_length: 480
}

function figure_plagued_citizen_gods_are_angry() {
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

function figure_plagued_citizen_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push("plagued_i_feel_awful")
	keys.push("plagued_fever_spreads")

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("plagued_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("plagued_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("plagued_need_workers")
	}

	if (figure_plagued_citizen_gods_are_angry()) {
		keys.push("plagued_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("plagued_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("plagued_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("plagued_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("plagued_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("plagued_city_is_amazing")
	}

	return keys
}

[es=(figure_plagued_citizen, setup_phrase)]
function figure_plagued_citizen_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_plagued_citizen_city_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
