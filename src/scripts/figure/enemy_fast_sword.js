log_info("akhenaten: figure enemy_fast_sword started")

function figure_enemy_fast_sword_gods_are_angry() {
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

function figure_enemy_fast_sword_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.num_forts < 1) {
		keys.push("enemy_sword_no_army")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("enemy_sword_no_food")
	}

	if (city.health_rating < 30) {
		keys.push("enemy_sword_disease")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("enemy_sword_need_workers")
	}

	if (figure_enemy_fast_sword_gods_are_angry()) {
		keys.push("enemy_sword_gods_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("enemy_sword_city_is_bad")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("enemy_sword_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("enemy_sword_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("enemy_sword_city_is_good")
	}

	keys.push("enemy_sword_for_glory")
	keys.push("enemy_sword_waiting")

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_enemy_fast_sword_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_154_ENEMY_FAST_SWORD_ATTACK:
		return "enemy_sword_attacking"
	case ACTION_156_ENEMY_FAST_SWORD_LEAVING:
		return "enemy_sword_leaving"
	case ACTION_153_ENEMY_FAST_SWORD_MARCHING:
		if (Math.random() < 0.5) {
			return "enemy_sword_marching"
		}
		break
	}

	return figure_enemy_fast_sword_city_phrase_key()
}

function figure_enemy_fast_sword_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_fast_sword_phrase_key(f))
}

[es=(figure_barbarian_sword, setup_phrase)]
function figure_barbarian_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_assyrian_sword, setup_phrase)]
function figure_assyrian_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_canaanite_sword, setup_phrase)]
function figure_canaanite_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_hyksos_sword, setup_phrase)]
function figure_hyksos_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_kushite_axeman, setup_phrase)]
function figure_kushite_axeman_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_libian_sword, setup_phrase)]
function figure_libian_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_nubian_axeman, setup_phrase)]
function figure_nubian_axeman_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_phoenician_swordman, setup_phrase)]
function figure_phoenician_swordman_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_roman_legioner, setup_phrase)]
function figure_roman_legioner_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_seapeople_axeman, setup_phrase)]
function figure_seapeople_axeman_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_egyptian_fast_sword, setup_phrase)]
function figure_egyptian_fast_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_egyptian_sword, setup_phrase)]
function figure_egyptian_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_egyptian_heavy_sword, setup_phrase)]
function figure_egyptian_heavy_sword_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_egyptian_axe, setup_phrase)]
function figure_egyptian_axe_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_egyptian_camel, setup_phrase)]
function figure_egyptian_camel_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }

[es=(figure_kingdome_infantry, setup_phrase)]
function figure_kingdome_infantry_setup_phrase(ev) { figure_enemy_fast_sword_setup_phrase(ev) }
