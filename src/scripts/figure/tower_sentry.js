log_info("akhenaten: figure tower_sentry started")

figure_tower_sentry {
	overlay : OVERLAY_CRIME
	animations {
		walk { pack:PACK_SPR_MAIN, id:54, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:55, max_frames:8, loop:false }
		fire { pack:PACK_SPR_MAIN, id:56, max_frames:12 }
		attack { pack:PACK_SPR_MAIN, id:197, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TOWER_SENTRY }
	}

	sounds {
		tower_sentry_no_enemies_sighted { sound:"guard_e01.wav", text: "#tower_sentry_no_enemies_sighted" }
		tower_sentry_ready_approaching_enemy { sound:"guard_e02.wav", text: "#tower_sentry_ready_approaching_enemy" }
		tower_sentry_no_trouble_defeating_army { sound:"guard_e03.wav", text: "#tower_sentry_no_trouble_defeating_army" }
		tower_sentry_enemy_is_fierce { sound:"guard_e04.wav", text: "#tower_sentry_enemy_is_fierce" }
		tower_sentry_disease_risk { sound:"soldier_disease_risk.wav", text: "#tower_sentry_disease_risk" }
		tower_sentry_no_food_in_city { sound:"soldier_no_food_in_city.wav", text: "#tower_sentry_no_food_in_city" }
		tower_sentry_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		tower_sentry_gods_are_angry { sound:"soldier_gods_are_angry.wav", text: "#tower_sentry_gods_are_angry" }
		tower_sentry_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		tower_sentry_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		tower_sentry_low_entertainment { sound:"soldier_low_entertainment.wav", text: "#tower_sentry_low_entertainment" }
		tower_sentry_city_is_good { sound:"soldier_city_is_good.wav", text: "#tower_sentry_city_is_good" }
		tower_sentry_city_is_amazing { sound:"soldier_city_is_amazing.wav", text: "#tower_sentry_city_is_amazing" }
	}

	category: figure_category_armed
	max_damage : 40
	attack_value : 6
	terrain_usage : TERRAIN_USAGE_ANY
	max_amount : 25
	missile_delay : 40
}

function figure_tower_sentry_gods_are_angry() {
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

function figure_tower_sentry_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push("tower_sentry_no_enemies_sighted")
	keys.push("tower_sentry_no_trouble_defeating_army")

	if (city.health_rating < 30) {
		keys.push("tower_sentry_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("tower_sentry_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("tower_sentry_need_workers")
	}

	if (figure_tower_sentry_gods_are_angry()) {
		keys.push("tower_sentry_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("tower_sentry_city_is_bad")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("tower_sentry_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("tower_sentry_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("tower_sentry_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("tower_sentry_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_tower_sentry_phrase_key(f) {
	var state = f.action_state

	// ACTION_150_TOWER_SENTRY_ATTACK / ACTION_172_TOWER_SENTRY_FIRING
	if (state == 150 || state == 172) {
		return "tower_sentry_ready_approaching_enemy"
	}

	if (__city_figures_total_invading_enemies() > 0) {
		if (Math.random() < 0.5) {
			return "tower_sentry_enemy_is_fierce"
		}
		return "tower_sentry_ready_approaching_enemy"
	}

	return figure_tower_sentry_city_phrase_key()
}

[es=(figure_tower_sentry, setup_phrase)]
function figure_tower_sentry_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_tower_sentry_phrase_key(f))
}
