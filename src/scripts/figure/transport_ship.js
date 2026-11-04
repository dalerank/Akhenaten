log_info("akhenaten: figure transport_ship started")

figure_transport_ship {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		// OG groups 73/74/75 → SprMain local 34/35/36 (group − 39).
		walk { id:34, max_frames:4, duration:10 }
		swim { id:34, max_frames:4, duration:10 }
		death { id:35, max_frames:8, loop:false }
		idle { id:36, max_frames:1 }
		// OG IMAGE_GROUP_FIGURE_SHIP_WAKE = 495 → SprMain 456.
		wake { id:456, max_frames:4, duration:3 }
		// OG swept 702/703/704 — placeholder (=normal) until River of Blood sweep.
		swim_swept { id:34, max_frames:4, duration:10 }
		death_swept { id:35, max_frames:8, loop:false }
		idle_swept { id:36, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRANSPORT_SHIP }
	}

	sounds {
		transport_must_protect_our_ship { sound: "transport_e01.wav", text: "#transport_must_protect_our_ship" }
		transport_enemy_is_here { sound: "transport_e02.wav", text: "#transport_enemy_is_here" }
		transport_were_prepared { sound: "transport_e03.wav", text: "#transport_were_prepared" }
		transport_ready_if_need_arises { sound: "transport_e04.wav", text: "#transport_ready_if_need_arises" }
	}

	category: figure_category_citizen
	max_damage: 250
	terrain_usage : TERRAIN_USAGE_ANY
	meta { text_id: 184, help_link:"message_figure_transport_ship" }

	// OG ships_player / military_rules
	dock_wait_ticks: 50
	face_enemy_wait: 19
	face_enemy_range: 5
	legion_drowns_tick: 2
	evade_ticks: 75
	evade_range: 18
	hull_auto_repair_percent: 15
	// Flee probe length (OG transport_escapes used ±10). Tries flee dir ±45°.
	escape_distance: 10
}

function figure_transport_ship_phrase_key(f) {
	var keys = []
	var state = f.action_state

	if (__city_figures_total_invading_enemies() > 0) {
		keys.push("transport_enemy_is_here")
	}

	// ACTION_213_DOCKED / 217_QUEUED
	if (state == 213 || state == 217) {
		keys.push("transport_were_prepared")
	}

	// ACTION_215_EVADING — enemy nearby
	if (state == 215) {
		keys.push("transport_enemy_is_here")
	}

	// In transit: waiting / to wharf / sailing / to legion / to landing / repair
	if (state == 211 || state == 212 || state == 214 || state == 216
		|| state == 218 || state == 219 || state == 220 || state == 221 || state == 223) {
		keys.push("transport_must_protect_our_ship")
	}

	keys.push("transport_ready_if_need_arises")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_transport_ship, setup_phrase)]
function figure_transport_ship_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_transport_ship_phrase_key(f))
}
