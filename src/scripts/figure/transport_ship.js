log_info("akhenaten: figure transport_ship started")

figure_transport_ship {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:34, max_frames:4, duration:10 }
		swim { id:34, max_frames:4, duration:10 }
		death { id:35, max_frames:8, loop:false }
		idle { id:35, offset:8, max_frames:1 }
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
}

function figure_transport_ship_phrase_key(f) {
	var keys = []
	var state = f.action_state

	if (__city_figures_total_invading_enemies() > 0) {
		keys.push("transport_enemy_is_here")
	}

	// ACTION_213_TRANSPORT_SHIP_MOORED
	if (state == 213) {
		keys.push("transport_were_prepared")
	}

	// ACTION_211_CREATED / 212_GOING_TO_WHARF / 215_LEAVING
	if (state == 211 || state == 212 || state == 215) {
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
