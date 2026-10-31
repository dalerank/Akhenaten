log_info("akhenaten: figure architector started")

figure_architector {
	overlay : OVERLAY_DAMAGE
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:4, max_frames:12 }
		death { id:5, max_frames:8, loop:false }
		work_ground { id:49, max_frames:6 }
		work_stand { id:50, max_frames:6 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ARCHITECT }
	}

	sounds {
		engineer_extreme_damage_level {sound:"engineer_e01.wav", text: "#engineer_extreme_damage_level"}
		engineer_i_am_works {sound:"engineer_e02.wav", text: "#engineer_i_am_works"}
		engineer_high_damage_level {sound:"engineer_g01.wav", text: "#engineer_high_damage_level"}
		engineer_no_food_in_city {sound:"engineer_g02.wav", text: "#engineer_no_food_in_city"}
		engineer_city_not_safety {sound:"engineer_g03.wav", text: "#engineer_city_not_safety"}
		engineer_need_more_workers {sound:"engineer_g04.wav", text: "#engineer_need_more_workers"}
		engineer_gods_are_angry {sound:"engineer_g05.wav", text: "#engineer_gods_are_angry"}
		engineer_city_has_bad_reputation {sound:"engineer_g06.wav", text: "#engineer_city_has_bad_reputation"}
		engineer_city_is_good {sound:"engineer_g07.wav", text: "#engineer_city_is_good"}
		engineer_low_entertainment {sound:"engineer_g08.wav", text: "#engineer_low_entertainment"}
		engineer_city_is_bad {sound:"engineer_g09.wav", text: "#engineer_city_is_bad"}
		engineer_city_is_amazing {sound:"engineer_g10.wav", text: "#engineer_city_is_amazing"}
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_service_buildings : 100
	max_roam_length : 640
	permission : epermission_maintenance
	effect_radius : 2
	risk_reduction_strength : 100
	risk_reduction_amount : 100
	record_path : true
}

function figure_architector_gods_are_angry() {
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

function figure_architector_damage_flags() {
	var extreme = false
	var high = false
	for (var bid = 1; bid < MAX_BUILDINGS; bid++) {
		var b = city.get_building(bid)
		if (!b || !b.valid) {
			continue
		}
		if (b.collapse_risk > 70) {
			extreme = true
		}
		if (b.collapse_risk > 50) {
			high = true
		}
		if (extreme && high) {
			break
		}
	}
	return { extreme: extreme, high: high }
}

function figure_architector_city_phrase_key() {
	var keys = []
	var damage = figure_architector_damage_flags()
	var sentiment = city.sentiment.value
	var mood_cause = city.sentiment.low_mood_cause

	if (damage.extreme) {
		keys.push("engineer_extreme_damage_level")
	}

	if (city.num_forts < 1) {
		keys.push("engineer_city_not_safety")
	}

	if (damage.high) {
		keys.push("engineer_high_damage_level")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("engineer_no_food_in_city")
	}

	if (city.labor.workers_needed >= 20) {
		keys.push("engineer_need_more_workers")
	}

	if (figure_architector_gods_are_angry()) {
		keys.push("engineer_gods_are_angry")
	}

	if (sentiment < 30) {
		keys.push("engineer_city_has_bad_reputation")
	}

	if (sentiment > 50) {
		keys.push("engineer_city_is_good")
	}

	if (sentiment >= 30) {
		keys.push("engineer_city_is_bad")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("engineer_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("engineer_city_is_amazing")
	}

	keys.push("engineer_i_am_works")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_architector, setup_phrase)]
function figure_architector_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	if (f.action_state == ACTION_5_ENGINEER_GOING_TO_DAMAGE) {
		figure_apply_phrase(f, "engineer_extreme_damage_level")
		return
	}

	figure_apply_phrase(f, figure_architector_city_phrase_key())
}
