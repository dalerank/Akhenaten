log_info("akhenaten: figure frog started")

figure_frog {
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:22, max_frames:9 }
		idle { pack:PACK_EXPANSION_SPR, id:23, max_frames:9 }
		death { pack:PACK_EXPANSION_SPR, id:25, max_frames:6, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_FROG }
		icon { pack:PACK_EXPANSION, id:32 }
	}

	sounds {
		frog_joke_ribbit { sound:"frog_joke_ribbit.wav", text: "#frog_joke_ribbit" }
		frog_joke_plague { sound:"frog_joke_plague.wav", text: "#frog_joke_plague" }
		frog_joke_pad { sound:"frog_joke_pad.wav", text: "#frog_joke_pad" }
		frog_joke_pharaoh { sound:"frog_joke_pharaoh.wav", text: "#frog_joke_pharaoh" }
		frog_joke_flies { sound:"frog_joke_flies.wav", text: "#frog_joke_flies" }
		frog_joke_happy { sound:"frog_joke_happy.wav", text: "#frog_joke_happy" }
		frog_joke_croak { sound:"frog_joke_croak.wav", text: "#frog_joke_croak" }
		frog_joke_swarm { sound:"frog_joke_swarm.wav", text: "#frog_joke_swarm" }
		frog_joke_happiness { sound:"frog_joke_happiness.wav", text: "#frog_joke_happiness" }
		frog_joke_nile { sound:"frog_joke_nile.wav", text: "#frog_joke_nile" }
		frog_joke_amphibious { sound:"frog_joke_amphibious.wav", text: "#frog_joke_amphibious" }
		frog_joke_meta { sound:"frog_joke_meta.wav", text: "#frog_joke_meta" }
	}

	category: figure_category_inactive
	max_damage: 20
	attack_value: 0
	terrain_usage: TERRAIN_USAGE_ANIMAL
	max_roam_length: 480

	default_swarm: 10
	max_amount: 24
	plague_days: 80
	house_infest_days: 80
	happiness_hit: -10
}

function figure_frog_phrase_keys() {
	return [
		"frog_joke_ribbit",
		"frog_joke_plague",
		"frog_joke_pad",
		"frog_joke_pharaoh",
		"frog_joke_flies",
		"frog_joke_happy",
		"frog_joke_croak",
		"frog_joke_swarm",
		"frog_joke_happiness",
		"frog_joke_nile",
		"frog_joke_amphibious",
		"frog_joke_meta"
	]
}

[es=(figure_frog, setup_phrase)]
function figure_frog_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_frog_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
