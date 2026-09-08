log_info("akhenaten: figure mummy started")

// Undead curse walker — Cleopatra SprMain2 bmp "mummy":
// group 40 = SprMain2_01919 walk (12×8); 41 attack (11×8); 42 idle (12×8).
// No death strip in pak (Blood_Transport begins at group 43) — reuse walk for death.
figure_mummy {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:40, max_frames:12 }
		attack { pack:PACK_EXPANSION_SPR, id:41, max_frames:11 }
		idle { pack:PACK_EXPANSION_SPR, id:42, max_frames:12 }
		death { pack:PACK_EXPANSION_SPR, id:40, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MUMMY }
	}

	sounds {
		mummy_risen { sound:"mummy_risen.wav", text: "#mummy_risen" }
		mummy_walks_streets { sound:"mummy_walks_streets.wav", text: "#mummy_walks_streets" }
		mummy_attacking { sound:"mummy_attacking.wav", text: "#mummy_attacking" }
		mummy_disease_risk { sound:"mummy_disease_risk.wav", text: "#mummy_disease_risk" }
		mummy_no_food_in_city { sound:"mummy_no_food_in_city.wav", text: "#mummy_no_food_in_city" }
		mummy_city_have_no_army { sound:"mummy_city_have_no_army.wav", text: "#mummy_city_have_no_army" }
		mummy_need_workers { sound:"mummy_need_workers.wav", text: "#mummy_need_workers" }
		mummy_gods_are_angry { sound:"mummy_gods_are_angry.wav", text: "#mummy_gods_are_angry" }
		mummy_city_is_bad { sound:"mummy_city_is_bad.wav", text: "#mummy_city_is_bad" }
		mummy_much_unemployment { sound:"mummy_much_unemployment.wav", text: "#mummy_much_unemployment" }
		mummy_low_entertainment { sound:"mummy_low_entertainment.wav", text: "#mummy_low_entertainment" }
		mummy_city_is_good { sound:"mummy_city_is_good.wav", text: "#mummy_city_is_good" }
		mummy_city_is_amazing { sound:"mummy_city_is_amazing.wav", text: "#mummy_city_is_amazing" }
	}

	category: figure_category_hostile
	is_enemy: true
	max_damage: 20
	attack_value: 8
	defense_value: 2
	terrain_usage: TERRAIN_USAGE_ANY
	// Live cap enforced in figure_mummy::spawn_wave (max 4).
	max_roam_length: 480
}

function figure_mummy_gods_are_angry() {
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

function figure_mummy_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("mummy_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("mummy_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("mummy_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("mummy_need_workers")
	}

	if (figure_mummy_gods_are_angry()) {
		keys.push("mummy_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("mummy_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("mummy_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("mummy_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("mummy_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("mummy_city_is_amazing")
	}

	return keys
}

[es=(figure_mummy, setup_phrase)]
function figure_mummy_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = []
	var state = f.action_state
	if (f.anim_key == "attack") {
		keys.push("mummy_attacking")
	} else if (state == ACTION_0_MUMMY_CREATED) {
		keys.push("mummy_risen")
	} else if (state == ACTION_1_MUMMY_ROAMING) {
		keys.push("mummy_walks_streets")
	}

	var city_keys = figure_mummy_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("mummy_walks_streets")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
