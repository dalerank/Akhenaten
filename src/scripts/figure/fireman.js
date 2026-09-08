log_info("akhenaten: figure fireman started")

figure_fireman {
	overlay : OVERLAY_WATER
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:6, max_frames:12 }
		death { id:7, max_frames:8, loop:false }
		fight_fire { id:8, max_frames:36 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FIREMAN }
	}

	sounds {
		fireman_fighting_fire { sound:"fireman_e01.wav", text: "#fireman_fighting_fire" }
		fireman_going_to_fire { sound:"fireman_e02.wav", text: "#fireman_going_to_fire" }
		fireman_fighting_fire_also { sound:"fireman_e03.wav", text: "#fireman_fighting_fire_also" }
		fireman_desease_can_start_at_any_moment { sound:"fireman_g01.wav", text: "#fireman_desease_can_start_at_any_moment" }
		fireman_no_food_in_city { sound:"fireman_g02.wav", text: "#fireman_no_food_in_city" }
		fireman_city_not_safety_workers_leaving { sound:"fireman_g03.wav", text: "#fireman_city_not_safety_workers_leaving" }
		fireman_need_workers { sound:"fireman_g04.wav", text: "#fireman_need_workers" }
		fireman_gods_are_angry { sound:"fireman_g05.wav", text: "#fireman_gods_are_angry" }
		fireman_hight_fire_level { sound:"fireman_g06.wav", text: "#fireman_hight_fire_level" }
		fireman_need_more_workers { sound:"fireman_g07.wav", text: "#fireman_need_more_workers" }
		fireman_low_entertainment { sound:"fireman_g08.wav", text: "#fireman_low_entertainment" }
		fireman_gods_are_pleasures { sound:"fireman_g09.wav", text: "#fireman_gods_are_pleasures" }
		fireman_city_is_amazing { sound:"fireman_g10.wav", text: "#fireman_city_is_amazing" }
	}

	category : figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ANIMAL
	max_roam_length : 640
	permission : epermission_maintenance
	fire_detection_distance : 10
	record_path : true
}

function figure_fireman_gods_are_angry() {
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

function figure_fireman_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 20) {
		keys.push("fireman_desease_can_start_at_any_moment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("fireman_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("fireman_city_not_safety_workers_leaving")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("fireman_need_workers")
	}

	if (city.labor.workers_needed >= 20) {
		keys.push("fireman_need_more_workers")
	}

	if (__city_has_high_fire_risk()) {
		keys.push("fireman_hight_fire_level")
	}

	if (figure_fireman_gods_are_angry()) {
		keys.push("fireman_gods_are_angry")
	} else {
		keys.push("fireman_gods_are_pleasures")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("fireman_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("fireman_city_is_amazing")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_fireman_phrase_key(f) {
	var state = f.action_state
	// ACTION_74_FIREMAN_GOING_TO_FIRE
	if (state == 74) {
		return "fireman_going_to_fire"
	}

	// ACTION_75_FIREMAN_AT_FIRE
	if (state == 75) {
		var fighting = ["fireman_fighting_fire", "fireman_fighting_fire_also"]
		return fighting[Math.floor(Math.random() * fighting.length)]
	}

	return figure_fireman_city_phrase_key()
}

[es=(figure_fireman, setup_phrase)]
function figure_fireman_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_fireman_phrase_key(f))
}
