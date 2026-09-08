log_info("akhenaten: figure enemy_archer started")

function figure_enemy_archer_taunt_keys() {
	return [
		"enemy_archer_city_will_fall",
		"enemy_archer_arrows_ready",
		"enemy_archer_for_glory"
	]
}

function figure_enemy_archer_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_3_ENEMY_ARCHER_SHOOT_MISSILE:
		return "enemy_archer_shooting"
	case ACTION_2_ENEMY_ARCHER_MARCHING:
		return "enemy_archer_marching"
	case ACTION_4_ENEMY_ARCHER_LEAVING:
		return "enemy_archer_leaving"
	case ACTION_0_ENEMY_ARCHER_INITIAL:
	case ACTION_1_ENEMY_ARCHER_WAITING:
		return "enemy_archer_waiting"
	}

	var taunts = figure_enemy_archer_taunt_keys()
	return taunts[Math.floor(Math.random() * taunts.length)]
}

function figure_enemy_archer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_archer_phrase_key(f))
}

[es=(figure_barbarian_archer, setup_phrase)]
function figure_barbarian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_assyrian_archer, setup_phrase)]
function figure_assyrian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_canaanite_archer, setup_phrase)]
function figure_canaanite_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_egyptian_archer, setup_phrase)]
function figure_egyptian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_egyptian_mounted_archer, setup_phrase)]
function figure_egyptian_mounted_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_hittite_archer, setup_phrase)]
function figure_hittite_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_hyksos_archer, setup_phrase)]
function figure_hyksos_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_libian_archer, setup_phrase)]
function figure_libian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_nubian_archer, setup_phrase)]
function figure_nubian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_persian_archer, setup_phrase)]
function figure_persian_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_roman_archer, setup_phrase)]
function figure_roman_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }

[es=(figure_seapeople_archer, setup_phrase)]
function figure_seapeople_archer_setup_phrase(ev) { figure_enemy_archer_setup_phrase(ev) }
