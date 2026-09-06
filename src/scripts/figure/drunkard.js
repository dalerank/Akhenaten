log_info("akhenaten: figure drunkard started")

figure_drunkard {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:203, max_frames:12 }
		back { id:203, max_frames:12 }
		womit { id:204, max_frames:12, duration:4 }
		death { id:205, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DRUNKARD }
	}

	sounds {
		drunkard_need_drink { sound:"drunkard_e01.wav", text: "#drunkard_need_drink" }
		drunkard_going_to_tavern { sound:"drunkard_e02.wav", text: "#drunkard_going_to_tavern" }
		drunkard_time_for_beer { sound:"drunkard_e03.wav", text: "#drunkard_time_for_beer" }
		drunkard_feeling_dizzy { sound:"drunkard_e04.wav", text: "#drunkard_feeling_dizzy" }
		drunkard_oh_my_stomach { sound:"drunkard_e05.wav", text: "#drunkard_oh_my_stomach" }
		drunkard_going_home { sound:"drunkard_e06.wav", text: "#drunkard_going_home" }
		drunkard_disease_risk { sound:"drunkard_disease_risk.wav", text: "#drunkard_disease_risk" }
		drunkard_no_food_in_city { sound:"drunkard_no_food_in_city.wav", text: "#drunkard_no_food_in_city" }
		drunkard_city_have_no_army { sound:"drunkard_city_have_no_army.wav", text: "#drunkard_city_have_no_army" }
		drunkard_need_workers { sound:"drunkard_need_workers.wav", text: "#drunkard_need_workers" }
		drunkard_gods_are_angry { sound:"drunkard_gods_are_angry.wav", text: "#drunkard_gods_are_angry" }
		drunkard_city_is_bad { sound:"drunkard_city_is_bad.wav", text: "#drunkard_city_is_bad" }
		drunkard_much_unemployment { sound:"drunkard_much_unemployment.wav", text: "#drunkard_much_unemployment" }
		drunkard_low_entertainment { sound:"drunkard_low_entertainment.wav", text: "#drunkard_low_entertainment" }
		drunkard_city_is_good { sound:"drunkard_city_is_good.wav", text: "#drunkard_city_is_good" }
		drunkard_city_is_amazing { sound:"drunkard_city_is_amazing.wav", text: "#drunkard_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	walk_delay : 50
	womit_delay : 50
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

function figure_drunkard_gods_are_angry() {
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

function figure_drunkard_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("drunkard_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("drunkard_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("drunkard_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("drunkard_need_workers")
	}

	if (figure_drunkard_gods_are_angry()) {
		keys.push("drunkard_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("drunkard_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("drunkard_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("drunkard_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("drunkard_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("drunkard_city_is_good")
	}

	if (keys.length == 0) {
		return "drunkard_feeling_dizzy"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_drunkard, setup_phrase)]
function figure_drunkard_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case 12: // ACTION_12_DRUNKARD_CREATED_SOBER
		figure_apply_phrase(f, "drunkard_need_drink")
		return
	case 13: // ACTION_13_DRUNKARD_ENTER_SENET_HOUSE
		figure_apply_phrase(f, "drunkard_time_for_beer")
		return
	case 14: // ACTION_14_DRUNKARD_CREATED
		figure_apply_phrase(f, "drunkard_feeling_dizzy")
		return
	case 10: // ACTION_10_DRUNKARD_WOMIT
		figure_apply_phrase(f, "drunkard_oh_my_stomach")
		return
	case 9: // ACTION_9_DRUNKARD_GOTO_SENET_HOUSE
		if (Math.random() < 0.5) {
			figure_apply_phrase(f, "drunkard_going_to_tavern")
			return
		}
		break
	case 11: // ACTION_11_DRUNKARD_RETURN_HOME
		if (Math.random() < 0.5) {
			figure_apply_phrase(f, "drunkard_going_home")
			return
		}
		break
	}

	figure_apply_phrase(f, figure_drunkard_city_phrase_key())
}
