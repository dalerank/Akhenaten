log_info("akhenaten: figure flotsam started")

figure_flotsam = {
	animations : {
		walk : {pack:PACK_SPR_AMBIENT, id:0, max_frames: 12}
		big_image : { pack:PACK_UNLOADED, id:25, offset:FIGURE_FLOTSAM }
	}

	sounds {
		flotsam_plato_unexamined { sound:"flotsam_plato_unexamined.wav", text: "#flotsam_plato_unexamined" }
		flotsam_plato_cave { sound:"flotsam_plato_cave.wav", text: "#flotsam_plato_cave" }
		flotsam_plato_wise { sound:"flotsam_plato_wise.wav", text: "#flotsam_plato_wise" }
		flotsam_plato_courage { sound:"flotsam_plato_courage.wav", text: "#flotsam_plato_courage" }
		flotsam_plato_knowledge { sound:"flotsam_plato_knowledge.wav", text: "#flotsam_plato_knowledge" }
		flotsam_plato_opinion { sound:"flotsam_plato_opinion.wav", text: "#flotsam_plato_opinion" }
		flotsam_plato_love { sound:"flotsam_plato_love.wav", text: "#flotsam_plato_love" }
		flotsam_plato_justice { sound:"flotsam_plato_justice.wav", text: "#flotsam_plato_justice" }
		flotsam_plato_music { sound:"flotsam_plato_music.wav", text: "#flotsam_plato_music" }
		flotsam_plato_ignorance { sound:"flotsam_plato_ignorance.wav", text: "#flotsam_plato_ignorance" }
		flotsam_plato_excess { sound:"flotsam_plato_excess.wav", text: "#flotsam_plato_excess" }
		flotsam_plato_war { sound:"flotsam_plato_war.wav", text: "#flotsam_plato_war" }
		flotsam_plato_meta { sound:"flotsam_plato_meta.wav", text: "#flotsam_plato_meta" }
	}

	category: figure_category_inactive
	max_damage : 0
	terrain_usage : TERRAIN_USAGE_ANY
}

function figure_flotsam_phrase_keys() {
	return [
		"flotsam_plato_unexamined",
		"flotsam_plato_cave",
		"flotsam_plato_wise",
		"flotsam_plato_courage",
		"flotsam_plato_knowledge",
		"flotsam_plato_opinion",
		"flotsam_plato_love",
		"flotsam_plato_justice",
		"flotsam_plato_music",
		"flotsam_plato_ignorance",
		"flotsam_plato_excess",
		"flotsam_plato_war",
		"flotsam_plato_meta"
	]
}

[es=(figure_flotsam, setup_phrase)]
function figure_flotsam_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_flotsam_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
