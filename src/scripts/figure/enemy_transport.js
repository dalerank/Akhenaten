log_info("akhenaten: figure enemy_transport started")

function figure_enemy_transport_gods_are_angry() {
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

function figure_enemy_transport_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.num_forts < 1) {
		keys.push("enemy_transport_no_army")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("enemy_transport_no_food")
	}

	if (city.health_rating < 30) {
		keys.push("enemy_transport_disease")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("enemy_transport_need_workers")
	}

	if (figure_enemy_transport_gods_are_angry()) {
		keys.push("enemy_transport_gods_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("enemy_transport_city_is_bad")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("enemy_transport_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("enemy_transport_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("enemy_transport_city_is_good")
	}

	keys.push("enemy_transport_for_glory")
	keys.push("enemy_transport_idle")

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_enemy_transport_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_2_ENEMY_TRANSPORT_DISEMBARKING:
		return "enemy_transport_disembarking"
	case ACTION_1_ENEMY_TRANSPORT_SAILING:
		if (Math.random() < 0.5) {
			return "enemy_transport_sailing"
		}
		break
	case ACTION_0_ENEMY_TRANSPORT_CREATED:
		return "enemy_transport_created"
	}

	return figure_enemy_transport_city_phrase_key()
}

function figure_enemy_transport_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_transport_phrase_key(f))
}

[es=(figure_enemy_transport_generic, setup_phrase)]
function figure_enemy_transport_generic_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_egyptian_transport_ship, setup_phrase)]
function figure_egyptian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_barbarian_transport_ship, setup_phrase)]
function figure_barbarian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_assyrian_transport_ship, setup_phrase)]
function figure_assyrian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_canaanite_transport_ship, setup_phrase)]
function figure_canaanite_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_hittite_transport_ship, setup_phrase)]
function figure_hittite_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_hyksos_transport_ship, setup_phrase)]
function figure_hyksos_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_kushite_transport_ship, setup_phrase)]
function figure_kushite_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_libian_transport_ship, setup_phrase)]
function figure_libian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_nubian_transport_ship, setup_phrase)]
function figure_nubian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_persian_transport_ship, setup_phrase)]
function figure_persian_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_phoenician_transport_ship, setup_phrase)]
function figure_phoenician_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_roman_transport_ship, setup_phrase)]
function figure_roman_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }

[es=(figure_seapeople_transport_ship, setup_phrase)]
function figure_seapeople_transport_ship_setup_phrase(ev) { figure_enemy_transport_setup_phrase(ev) }
