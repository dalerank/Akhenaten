log_info("akhenaten: figure constable started")

figure_constable {
	overlay : OVERLAY_CRIME
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:20, max_frames:12 }
		death { id:21, max_frames:8, loop:false }
		attack { id:21, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_CONSTABLE }
	}

	sounds {
		policeman_low_crime_level { sound: "police_e01.WAV", text: "#policeman_low_crime_level" }
		policeman_usual_crime_level { sound: "police_e02.WAV", text: "#policeman_usual_crime_level" }
		policeman_very_low_crime_level { sound: "police_e03.WAV", text: "#policeman_very_low_crime_level" }
		policeman_iam_too_busy_that_talk { sound: "police_e04.WAV", text: "#policeman_iam_too_busy_that_talk" }
		policeman_i_hope_my_work_is_need { sound: "police_e05.WAV", text: "#policeman_i_hope_my_work_is_need" }
		policeman_city_not_safety { sound: "police_e06.WAV", text: "#policeman_city_not_safety" }
		policeman_need_workers { sound: "police_e07.WAV", text: "#policeman_need_workers" }
		policeman_enemies_are_coming { sound: "police_e08.WAV", text: "#policeman_enemies_are_coming" }
		policeman_desease_can_start_at_any_moment { sound: "police_g01.WAV", text: "#policeman_desease_can_start_at_any_moment" }
		policeman_no_food_in_city { sound: "police_g02.WAV", text: "#policeman_no_food_in_city" }
		policeman_no_army { sound: "police_g03.WAV", text: "#policeman_no_army" }
		policeman_need_more_workers { sound: "police_g04.WAV", text: "#policeman_need_more_workers" }
		policeman_gods_are_angry { sound: "police_g05.WAV", text: "#policeman_gods_are_angry" }
		policeman_no_army_2 { sound: "police_g06.wav", text: "#policeman_no_army_2" }
		policeman_much_unemployments { sound: "police_g07.WAV", text: "#policeman_much_unemployments" }
		policeman_low_entertainment { sound: "police_g08.WAV", text: "#policeman_low_entertainment" }
		policeman_city_is_good { sound: "police_g09.WAV", text: "#policeman_city_is_good" }
		policeman_city_is_amazing { sound: "police_g10.WAV", text: "#policeman_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 100
	attack_value: 5
	defense_value: 3
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 640
}

function figure_constable_gods_are_angry() {
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

function figure_constable_city_phrase_key(f) {
	var keys = []
	var crime = f.min_max_seen
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (crime < 10) {
		keys.push("policeman_very_low_crime_level")
	} else if (crime < 30) {
		keys.push("policeman_low_crime_level")
	} else {
		keys.push("policeman_usual_crime_level")
	}

	// C++ had formation_get_num_forts() < 0 (never true); match fireman/other walkers.
	if (city.num_forts < 1) {
		keys.push("policeman_city_not_safety")
		keys.push("policeman_enemies_are_coming")
		keys.push("policeman_no_army")
		keys.push("policeman_no_army_2")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("policeman_need_workers")
	}

	if (city.labor.workers_needed >= 20) {
		keys.push("policeman_need_more_workers")
	}

	if (city.health_rating < 20) {
		keys.push("policeman_desease_can_start_at_any_moment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("policeman_no_food_in_city")
	}

	if (figure_constable_gods_are_angry()) {
		keys.push("policeman_gods_are_angry")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("policeman_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("policeman_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("policeman_city_is_amazing")
	} else if (sentiment > 40) {
		keys.push("policeman_city_is_good")
	}

	keys.push("policeman_iam_too_busy_that_talk")
	keys.push("policeman_i_hope_my_work_is_need")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_constable, setup_phrase)]
function figure_constable_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	// ACTION_76/77/150 — going to / fighting enemy
	if (state == 76 || state == 77 || state == 150) {
		figure_apply_phrase(f, "policeman_enemies_are_coming")
		return
	}

	figure_apply_phrase(f, figure_constable_city_phrase_key(f))
}
