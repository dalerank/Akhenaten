log_info("akhenaten: figure soldier started")

figure_soldier_infantry {
	overlay : OVERLAY_PAVILION
	animations {
		walk { pack:PACK_SPR_MAIN, id:64, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:65, max_frames:8, loop:false }
		attack { pack:PACK_SPR_MAIN, id:66, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_INFANTRY }
	}

	sounds {
		soldier_no_enemies_sighted { sound:"guard_e01.wav", text: "#soldier_no_enemies_sighted" }
		soldier_ready_approaching_enemy { sound:"guard_e02.wav", text: "#soldier_ready_approaching_enemy" }
		soldier_no_trouble_defeating_army { sound:"guard_e03.wav", text: "#soldier_no_trouble_defeating_army" }
		soldier_enemy_is_fierce { sound:"guard_e04.wav", text: "#soldier_enemy_is_fierce" }
		soldier_disease_risk { sound:"soldier_disease_risk.wav", text: "#soldier_disease_risk" }
		soldier_no_food_in_city { sound:"soldier_no_food_in_city.wav", text: "#soldier_no_food_in_city" }
		soldier_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		soldier_gods_are_angry { sound:"soldier_gods_are_angry.wav", text: "#soldier_gods_are_angry" }
		soldier_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		soldier_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		soldier_low_entertainment { sound:"soldier_low_entertainment.wav", text: "#soldier_low_entertainment" }
		soldier_city_is_good { sound:"soldier_city_is_good.wav", text: "#soldier_city_is_good" }
		soldier_city_is_amazing { sound:"soldier_city_is_amazing.wav", text: "#soldier_city_is_amazing" }
	}

	is_soldier : true
	category: figure_category_armed
	max_damage : 150
	attack_value : 10
	terrain_usage : TERRAIN_USAGE_ANY
}

figure_soldier_archer {
	overlay : OVERLAY_PAVILION
	animations {
		walk { pack:PACK_SPR_MAIN, id:61, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:62, max_frames:8, loop:false }
		attack { pack:PACK_SPR_MAIN, id:63, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ARCHER }
	}

	sounds {
		soldier_no_enemies_sighted { sound:"guard_e01.wav", text: "#soldier_no_enemies_sighted" }
		soldier_ready_approaching_enemy { sound:"guard_e02.wav", text: "#soldier_ready_approaching_enemy" }
		soldier_no_trouble_defeating_army { sound:"guard_e03.wav", text: "#soldier_no_trouble_defeating_army" }
		soldier_enemy_is_fierce { sound:"guard_e04.wav", text: "#soldier_enemy_is_fierce" }
		soldier_disease_risk { sound:"soldier_disease_risk.wav", text: "#soldier_disease_risk" }
		soldier_no_food_in_city { sound:"soldier_no_food_in_city.wav", text: "#soldier_no_food_in_city" }
		soldier_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		soldier_gods_are_angry { sound:"soldier_gods_are_angry.wav", text: "#soldier_gods_are_angry" }
		soldier_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		soldier_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		soldier_low_entertainment { sound:"soldier_low_entertainment.wav", text: "#soldier_low_entertainment" }
		soldier_city_is_good { sound:"soldier_city_is_good.wav", text: "#soldier_city_is_good" }
		soldier_city_is_amazing { sound:"soldier_city_is_amazing.wav", text: "#soldier_city_is_amazing" }
	}

	is_soldier : true
	category: figure_category_armed
	max_damage : 80
	attack_value : 4
	missile_attack_value : 4
	missile_delay : 100
	terrain_usage : TERRAIN_USAGE_ANY
}

figure_soldier_charioteer {
	overlay : OVERLAY_PAVILION
	animations {
		walk { pack:PACK_SPR_MAIN, id:67, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:68, max_frames:8, loop:false }
		attack { pack:PACK_SPR_MAIN, id:69, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FCHARIOTEER }
	}

	sounds {
		soldier_no_enemies_sighted { sound:"guard_e01.wav", text: "#soldier_no_enemies_sighted" }
		soldier_ready_approaching_enemy { sound:"guard_e02.wav", text: "#soldier_ready_approaching_enemy" }
		soldier_no_trouble_defeating_army { sound:"guard_e03.wav", text: "#soldier_no_trouble_defeating_army" }
		soldier_enemy_is_fierce { sound:"guard_e04.wav", text: "#soldier_enemy_is_fierce" }
		soldier_disease_risk { sound:"soldier_disease_risk.wav", text: "#soldier_disease_risk" }
		soldier_no_food_in_city { sound:"soldier_no_food_in_city.wav", text: "#soldier_no_food_in_city" }
		soldier_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		soldier_gods_are_angry { sound:"soldier_gods_are_angry.wav", text: "#soldier_gods_are_angry" }
		soldier_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		soldier_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		soldier_low_entertainment { sound:"soldier_low_entertainment.wav", text: "#soldier_low_entertainment" }
		soldier_city_is_good { sound:"soldier_city_is_good.wav", text: "#soldier_city_is_good" }
		soldier_city_is_amazing { sound:"soldier_city_is_amazing.wav", text: "#soldier_city_is_amazing" }
	}

	is_soldier : true
	category: figure_category_armed
	max_damage : 120
	attack_value : 8
	terrain_usage : TERRAIN_USAGE_ANY
}

function figure_soldier_gods_are_angry() {
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

function figure_soldier_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push("soldier_no_enemies_sighted")
	keys.push("soldier_no_trouble_defeating_army")

	if (city.health_rating < 30) {
		keys.push("soldier_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("soldier_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("soldier_need_workers")
	}

	if (figure_soldier_gods_are_angry()) {
		keys.push("soldier_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("soldier_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("soldier_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("soldier_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("soldier_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("soldier_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_soldier_phrase_key(f) {
	var state = f.action_state

	// ACTION_90_SOLDIER_ATTACK
	if (state == 90) {
		return "soldier_ready_approaching_enemy"
	}

	// ACTION_87_SOLDIER_GOING_TO_DISTANT_BATTLE / ACTION_89_AT_DISTANT_BATTLE
	if (state == 87 || state == 89) {
		return "soldier_no_trouble_defeating_army"
	}

	if (__city_figures_total_invading_enemies() > 0) {
		if (Math.random() < 0.5) {
			return "soldier_enemy_is_fierce"
		}
		return "soldier_ready_approaching_enemy"
	}

	return figure_soldier_city_phrase_key()
}

function figure_soldier_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_soldier_phrase_key(f))
}

[es=(figure_soldier_infantry, setup_phrase)]
function figure_soldier_infantry_setup_phrase(ev) { figure_soldier_setup_phrase(ev) }

[es=(figure_soldier_archer, setup_phrase)]
function figure_soldier_archer_setup_phrase(ev) { figure_soldier_setup_phrase(ev) }

[es=(figure_soldier_charioteer, setup_phrase)]
function figure_soldier_charioteer_setup_phrase(ev) { figure_soldier_setup_phrase(ev) }
