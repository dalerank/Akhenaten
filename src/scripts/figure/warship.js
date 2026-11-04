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
	hunt_range : 228
	missile_range : 10
	patrol_extra_range : 10
	patrol_radius : 10
	damaged_percent : 15
	dock_wait_ticks : 50
	face_enemy_wait : 19
	face_enemy_range : 5
	ram_cooldown : 15
	evade_ticks : 75
	evade_range : 18
	shoot_ticks : 100
	target_check_ticks : 10
	full_moves : 80
	full_steps : 8
	fatigue_ticks : 200
	ram_fast_percent : 120
	score_loaded_transport : 25
	score_land_enemy : 17
	score_warship : 15
	score_transport : 10
	escape_distance : 10
	fatigue_rest_interval : 40
	fatigue_grow_interval : 80
	fatigue_combat_interval : 20
	fatigue_rest_amount : 2

	meta { text_id: 184, help_link:"message_building_warship" }
	terrain_usage : TERRAIN_USAGE_ANY
}

function figure_warship_phrase_key(f) {
	var keys = []
	var state = f.action_state

	if (state == ACTION_24_WARSHIP_ATTACKING_SHIP || state == ACTION_9_WARSHIP_STRAIGHT) {
		keys.push("warship_well_fight_to_the_death")
	}

	if (__city_figures_total_invading_enemies() > 0) {
		keys.push("warship_enemies_coming_this_way")
	}

	if (state == ACTION_10_WARSHIP_HUNTING || state == ACTION_23_WARSHIP_PATROLLING) {
		keys.push("warship_ready_to_attack_invaders")
	}

	if (state == ACTION_8_WARSHIP_WAITING || state == ACTION_20_WARSHIP_DOCKED) {
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
