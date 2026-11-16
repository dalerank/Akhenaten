log_info("akhenaten: figure tomb_artisan started")

// OG image groups 694 walk / 695 death / 697 work = Cleopatra SprMain2 (group base 659).
// Work frame = animation_frame / 2, so 6 frames shown two ticks each.
figure_tomb_artisan {
	animations {
		_pack { pack:PACK_EXPANSION_SPR }
		walk { id:35, max_frames:12 }
		death { id:36, max_frames:8, loop:false }
		work { id:38, max_frames:6, duration:2 }
		big_image { pack:PACK_EXPANSION, id:1, offset:1 }
	}

	sounds {
		tomb_artisan_going_to_work { sound:"artisan_e01.wav", text: "#tomb_artisan_going_to_work" }
		tomb_artisan_decorating { sound:"artisan_e02.wav", text: "#tomb_artisan_decorating" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS,
	max_roam_length: 512
	task_search_base: 30
	task_search_rand: 30
	guild_road_radius: 2
	work_ticks: 100
}

// OG figure_phrase_determine: monument group, phrase 0 on the way to the site, 1 otherwise.
[es=(figure_tomb_artisan, setup_phrase)]
function figure_tomb_artisan_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	if (f.action_state == 11) { // ACTION_11_TOMB_ARTISAN_GOING
		figure_apply_phrase(f, "tomb_artisan_going_to_work")
		return
	}
	figure_apply_phrase(f, "tomb_artisan_decorating")
}
