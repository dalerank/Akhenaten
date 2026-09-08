log_info("akhenaten: figure warship started")

figure_warship {
	animations {
		walk { pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 }
		swim { pack:PACK_SPR_MAIN, id:141, max_frames:4, duration:10 }
		death { pack:PACK_SPR_MAIN, id:142, max_frames:8, loop:false }
		attack { pack:PACK_SPR_MAIN, id:143, max_frames:6, duration:5 }
		idle { pack:PACK_SPR_MAIN, id:143, offset:3, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_WARSHIP }
	}

	orders_info {
		goto_wharf { id: 1, text: 17 }
		engage_nearby { id: 2, text: 11 }
		hold_position { id: 3, text: 9 }
		seek_and_destroy { id: 4, text: 13 }
		repair { id: 5, text: 15 }
	}

	sounds {
		warship_well_fight_to_the_death { sound: "warship_e01.wav", text: "#warship_well_fight_to_the_death" }
		warship_enemy_is_too_much_for_us { sound: "warship_e02.wav", text: "#warship_enemy_is_too_much_for_us" }
		warship_enemies_coming_this_way { sound: "warship_e03.wav", text: "#warship_enemies_coming_this_way" }
		warship_ready_to_attack_invaders { sound: "warship_e04.wav", text: "#warship_ready_to_attack_invaders" }
		warship_ready_if_foes_come { sound: "warship_e05.wav", text: "#warship_ready_if_foes_come" }
	}

	category: figure_category_armed
	max_damage: 250
	attack_value : 12
	missile_attack_value : 6
	missile_delay : 200

	meta { text_id: 184, help_link:"message_building_warship" }
	terrain_usage : TERRAIN_USAGE_ANY
}

function figure_warship_phrase_key(f) {
	var keys = []
	var state = f.action_state

	// ACTION_204_WARSHIP_ATTACK
	if (state == 204) {
		keys.push("warship_well_fight_to_the_death")
	}

	if (__city_figures_total_invading_enemies() > 0) {
		keys.push("warship_enemies_coming_this_way")
	}

	// ACTION_206_WARSHIP_GOING_TO_PATROL / ACTION_209_WARSHIP_ON_PATROL
	if (state == 206 || state == 209) {
		keys.push("warship_ready_to_attack_invaders")
	}

	// ACTION_203_WARSHIP_MOORED
	if (state == 203) {
		keys.push("warship_ready_if_foes_come")
	}

	if (keys.length == 0) {
		return "warship_ready_if_foes_come"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_warship, setup_phrase)]
function figure_warship_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_warship_phrase_key(f))
}
