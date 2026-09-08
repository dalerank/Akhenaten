log_info("akhenaten: figure enemy_chariot started")

function figure_enemy_chariot_taunt_keys() {
	return [
		"enemy_chariot_city_will_fall",
		"enemy_chariot_no_match",
		"enemy_chariot_for_glory"
	]
}

function figure_enemy_chariot_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_154_ENEMY_FAST_SWORD_ATTACK:
		return "enemy_chariot_attacking"
	case ACTION_153_ENEMY_FAST_SWORD_MARCHING:
		return "enemy_chariot_marching"
	case ACTION_156_ENEMY_FAST_SWORD_LEAVING:
		return "enemy_chariot_leaving"
	case ACTION_151_ENEMY_FAST_SWORD_INITIAL:
	case ACTION_152_ENEMY_FAST_SWORD_WAITING:
		return "enemy_chariot_waiting"
	}

	var taunts = figure_enemy_chariot_taunt_keys()
	return taunts[Math.floor(Math.random() * taunts.length)]
}

function figure_enemy_chariot_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_chariot_phrase_key(f))
}

[es=(figure_assyrian_chariot, setup_phrase)]
function figure_assyrian_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_hyksos_chariot, setup_phrase)]
function figure_hyksos_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_egyptian_chariot, setup_phrase)]
function figure_egyptian_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_canaanite_chariot, setup_phrase)]
function figure_canaanite_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_kushite_chariot, setup_phrase)]
function figure_kushite_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_hittite_chariot, setup_phrase)]
function figure_hittite_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_persian_chariot, setup_phrase)]
function figure_persian_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_libian_chariot, setup_phrase)]
function figure_libian_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_nubian_chariot, setup_phrase)]
function figure_nubian_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_phoenician_chariot, setup_phrase)]
function figure_phoenician_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_roman_chariot, setup_phrase)]
function figure_roman_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_seapeople_chariot, setup_phrase)]
function figure_seapeople_chariot_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }

[es=(figure_kingdome_mounted, setup_phrase)]
function figure_kingdome_mounted_setup_phrase(ev) { figure_enemy_chariot_setup_phrase(ev) }
