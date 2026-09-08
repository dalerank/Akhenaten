log_info("akhenaten: figure enemy_warship started")

function figure_enemy_warship_gods_are_angry() {
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

function figure_enemy_warship_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.num_forts < 1) {
		keys.push("enemy_warship_no_army")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("enemy_warship_no_food")
	}

	if (city.health_rating < 30) {
		keys.push("enemy_warship_disease")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("enemy_warship_need_workers")
	}

	if (figure_enemy_warship_gods_are_angry()) {
		keys.push("enemy_warship_gods_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("enemy_warship_city_is_bad")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("enemy_warship_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("enemy_warship_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("enemy_warship_city_is_good")
	}

	keys.push("enemy_warship_for_glory")
	keys.push("enemy_warship_idle")

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_enemy_warship_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_3_ENEMY_WARSHIP_ATTACK:
		return "enemy_warship_attacking"
	case ACTION_2_ENEMY_WARSHIP_PURSUING:
		if (Math.random() < 0.5) {
			return "enemy_warship_pursuing"
		}
		break
	case ACTION_0_ENEMY_WARSHIP_CREATED:
		return "enemy_warship_created"
	case ACTION_1_ENEMY_WARSHIP_IDLE:
		return "enemy_warship_idle"
	}

	return figure_enemy_warship_city_phrase_key()
}

function figure_enemy_warship_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_warship_phrase_key(f))
}

[es=(figure_enemy_warship_generic, setup_phrase)]
function figure_enemy_warship_generic_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_assyrian_war_ship, setup_phrase)]
function figure_assyrian_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_canaanite_war_ship, setup_phrase)]
function figure_canaanite_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_egyptian_galera, setup_phrase)]
function figure_egyptian_galera_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_egyptian_war_ship, setup_phrase)]
function figure_egyptian_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_hittite_war_ship, setup_phrase)]
function figure_hittite_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_hyksos_war_ship, setup_phrase)]
function figure_hyksos_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_kushite_war_ship, setup_phrase)]
function figure_kushite_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_libian_war_ship, setup_phrase)]
function figure_libian_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_nubian_war_ship, setup_phrase)]
function figure_nubian_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_persian_war_ship, setup_phrase)]
function figure_persian_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_phoenician_war_ship, setup_phrase)]
function figure_phoenician_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_roman_war_ship, setup_phrase)]
function figure_roman_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }

[es=(figure_seapeople_war_ship, setup_phrase)]
function figure_seapeople_war_ship_setup_phrase(ev) { figure_enemy_warship_setup_phrase(ev) }
