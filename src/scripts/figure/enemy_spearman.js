log_info("akhenaten: figure enemy_spearman started")

function figure_enemy_spearman_taunt_keys() {
	return [
		"enemy_spearman_city_will_fall",
		"enemy_spearman_spears_ready",
		"enemy_spearman_for_glory"
	]
}

function figure_enemy_spearman_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case ACTION_154_ENEMY_SPEARMAN_SHOOT_MISSILE:
		return "enemy_spearman_shooting"
	case ACTION_155_ENEMY_SPEARMAN_RELOAD:
		return "enemy_spearman_spears_ready"
	case ACTION_153_ENEMY_SPEARMAN_MARCHING:
		return "enemy_spearman_marching"
	case ACTION_156_ENEMY_SPEARMAN_LEAVING:
		return "enemy_spearman_leaving"
	case ACTION_151_ENEMY_SPEARMAN_INITIAL:
	case ACTION_152_ENEMY_SPEARMAN_WAITING:
		return "enemy_spearman_waiting"
	}

	var taunts = figure_enemy_spearman_taunt_keys()
	return taunts[Math.floor(Math.random() * taunts.length)]
}

function figure_enemy_spearman_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_enemy_spearman_phrase_key(f))
}

[es=(figure_egyptian_spearman, setup_phrase)]
function figure_egyptian_spearman_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }

[es=(figure_kingdome_javelin, setup_phrase)]
function figure_kingdome_javelin_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }

[es=(figure_hittite_spearman, setup_phrase)]
function figure_hittite_spearman_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }

[es=(figure_kushite_spearman, setup_phrase)]
function figure_kushite_spearman_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }

[es=(figure_persian_spearman, setup_phrase)]
function figure_persian_spearman_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }

[es=(figure_phoenician_spearman, setup_phrase)]
function figure_phoenician_spearman_setup_phrase(ev) { figure_enemy_spearman_setup_phrase(ev) }
