log_info("akhenaten: figure academy_scriber started")

figure_academy_scriber {
	overlay : OVERLAY_SCRIBAL_SCHOOL
	animations {
		walk { pack:PACK_SPR_MAIN, id:199, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:200, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_SCRIBER }
	}

	sounds {
		scriber_these_festivals { sound: "scribe_e01.wav", text: "#scriber_these_festivals" }
		scriber_plague_could_break_out { sound: "scribe_g01.wav", text: "#scriber_plague_could_break_out" }
		scriber_no_food_in_city { sound: "scribe_g02.wav", text: "#scriber_no_food_in_city" }
		scriber_defenses_are_weak { sound: "scribe_g03.wav", text: "#scriber_defenses_are_weak" }
		scriber_need_more_workers { sound: "scribe_g04.wav", text: "#scriber_need_more_workers" }
		scriber_gods_are_angry { sound: "scribe_g05.wav", text: "#scriber_gods_are_angry" }
		scriber_reputation_is_low { sound: "scribe_g06.wav", text: "#scriber_reputation_is_low" }
		scriber_high_unemployment { sound: "scribe_g07.wav", text: "#scriber_high_unemployment" }
		scriber_low_entertainment { sound: "scribe_g08.wav", text: "#scriber_low_entertainment" }
		scriber_city_is_ok { sound: "scribe_g09.wav", text: "#scriber_city_is_ok" }
		scriber_city_is_amazing { sound: "scribe_g10.wav", text: "#scriber_city_is_amazing" }
	}

	category : figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
}

[es=(figure_academy_scriber, setup_phrase)]
function figure_academy_scriber_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_scriber_city_phrase_key())
}
