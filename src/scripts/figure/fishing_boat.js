log_info("akhenaten: figure fishing_boat started")

figure_fishing_boat {
	animations {
		walk { pack:PACK_SPR_MAIN, id:134, max_frames:4, duration:3 }
		swim { pack:PACK_SPR_MAIN, id:134, max_frames:4, duration:3 }
		death { pack:PACK_SPR_MAIN, id:135, max_frames:8, loop:false }
		work { pack:PACK_SPR_MAIN, id:135, max_frames:6, duration:5 }
		idle { pack:PACK_SPR_MAIN, id:136, offset:3, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FISHING_BOAT }
	}

	sounds {
		fishing_boat_ready { sound:"fishing_e01.wav", text: "#fishing_boat_ready" }
		fishing_boat_going_to_fish { sound:"fishing_e02.wav", text: "#fishing_boat_going_to_fish" }
		fishing_boat_fishing { sound:"fishing_e03.wav", text: "#fishing_boat_fishing" }
		fishing_boat_going_to_wharf { sound:"fishing_e01.wav", text: "#fishing_boat_going_to_wharf" }
		fishing_boat_at_wharf { sound:"fishing_e01.wav", text: "#fishing_boat_at_wharf" }
		fishing_boat_returning_with_fish { sound:"fishing_e02.wav", text: "#fishing_boat_returning_with_fish" }
		fishing_boat_looking_for_spot { sound:"fishing_e02.wav", text: "#fishing_boat_looking_for_spot" }
		fishing_boat_disease_risk { sound:"fishing_boat_disease_risk.wav", text: "#fishing_boat_disease_risk" }
		fishing_boat_no_food_in_city { sound:"fishing_boat_no_food_in_city.wav", text: "#fishing_boat_no_food_in_city" }
		fishing_boat_city_have_no_army { sound:"fishing_boat_city_have_no_army.wav", text: "#fishing_boat_city_have_no_army" }
		fishing_boat_need_workers { sound:"fishing_boat_need_workers.wav", text: "#fishing_boat_need_workers" }
		fishing_boat_gods_are_angry { sound:"fishing_boat_gods_are_angry.wav", text: "#fishing_boat_gods_are_angry" }
		fishing_boat_city_is_bad { sound:"fishing_boat_city_is_bad.wav", text: "#fishing_boat_city_is_bad" }
		fishing_boat_much_unemployment { sound:"fishing_boat_much_unemployment.wav", text: "#fishing_boat_much_unemployment" }
		fishing_boat_low_entertainment { sound:"fishing_boat_low_entertainment.wav", text: "#fishing_boat_low_entertainment" }
		fishing_boat_city_is_good { sound:"fishing_boat_city_is_good.wav", text: "#fishing_boat_city_is_good" }
		fishing_boat_city_is_amazing { sound:"fishing_boat_city_is_amazing.wav", text: "#fishing_boat_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ANY
	fish_per_trip : 50
	fishing_time_base : 200
	fishing_time_multiplier : 1
}

function figure_fishing_boat_gods_are_angry() {
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

function figure_fishing_boat_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("fishing_boat_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("fishing_boat_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("fishing_boat_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("fishing_boat_need_workers")
	}

	if (figure_fishing_boat_gods_are_angry()) {
		keys.push("fishing_boat_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("fishing_boat_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("fishing_boat_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("fishing_boat_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("fishing_boat_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("fishing_boat_city_is_amazing")
	}

	if (keys.length == 0) {
		return "fishing_boat_ready"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_fishing_boat_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_0_FISHING_BOAT_CREATED:
		return "fishing_boat_ready"
	case ACTION_1_FISHING_BOAT_GOING_TO_FISH:
		return "fishing_boat_going_to_fish"
	case ACTION_2_FISHING_BOAT_FISHING:
		return "fishing_boat_fishing"
	case ACTION_3_FISHING_BOAT_GOING_TO_WHARF:
		return "fishing_boat_going_to_wharf"
	case ACTION_4_FISHING_BOAT_AT_WHARF:
		return "fishing_boat_at_wharf"
	case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
		return "fishing_boat_returning_with_fish"
	case ACTION_6_FISHING_BOAT_RANDOM_FPOINT:
	case ACTION_7_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN:
	case ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF:
		return "fishing_boat_looking_for_spot"
	}

	return figure_fishing_boat_city_phrase_key()
}

[es=(figure_fishing_boat, setup_phrase)]
function figure_fishing_boat_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case ACTION_0_FISHING_BOAT_CREATED:
	case ACTION_1_FISHING_BOAT_GOING_TO_FISH:
	case ACTION_2_FISHING_BOAT_FISHING:
	case ACTION_3_FISHING_BOAT_GOING_TO_WHARF:
	case ACTION_4_FISHING_BOAT_AT_WHARF:
	case ACTION_5_FISHING_BOAT_RETURNING_WITH_FISH:
	case ACTION_6_FISHING_BOAT_RANDOM_FPOINT:
	case ACTION_7_FISHING_BOAT_FIND_RANDOM_WHARF_FOR_RETURN:
	case ACTION_8_FISHING_BOAT_RETURN_TO_RANDOM_WHARF:
		figure_apply_phrase(f, figure_fishing_boat_phrase_key(f))
		return
	}

	figure_apply_phrase(f, figure_fishing_boat_city_phrase_key())
}
