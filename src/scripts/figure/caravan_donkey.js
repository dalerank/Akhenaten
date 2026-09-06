log_info("akhenaten: figure caravan_donkey started")

figure_caravan_donkey {
	animations {
		walk { pack:PACK_SPR_MAIN, id:52, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:53, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TRADE_CARAVAN_DONKEY }
	}

	sounds {
		donkey_cicero_breathe { sound:"donkey_cicero_breathe.wav", text: "#donkey_cicero_breathe" }
		donkey_cicero_books { sound:"donkey_cicero_books.wav", text: "#donkey_cicero_books" }
		donkey_cicero_garden { sound:"donkey_cicero_garden.wav", text: "#donkey_cicero_garden" }
		donkey_cicero_gratitude { sound:"donkey_cicero_gratitude.wav", text: "#donkey_cicero_gratitude" }
		donkey_cicero_friendship { sound:"donkey_cicero_friendship.wav", text: "#donkey_cicero_friendship" }
		donkey_cicero_money { sound:"donkey_cicero_money.wav", text: "#donkey_cicero_money" }
		donkey_cicero_memory { sound:"donkey_cicero_memory.wav", text: "#donkey_cicero_memory" }
		donkey_cicero_moderation { sound:"donkey_cicero_moderation.wav", text: "#donkey_cicero_moderation" }
		donkey_cicero_mistakes { sound:"donkey_cicero_mistakes.wav", text: "#donkey_cicero_mistakes" }
		donkey_cicero_history { sound:"donkey_cicero_history.wav", text: "#donkey_cicero_history" }
		donkey_cicero_laws { sound:"donkey_cicero_laws.wav", text: "#donkey_cicero_laws" }
		donkey_cicero_not_alone { sound:"donkey_cicero_not_alone.wav", text: "#donkey_cicero_not_alone" }
		donkey_cicero_meta { sound:"donkey_cicero_meta.wav", text: "#donkey_cicero_meta" }
		donkey_cicero_runaway { sound:"donkey_cicero_runaway.wav", text: "#donkey_cicero_runaway" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_PREFER_ROADS
}

function figure_caravan_donkey_phrase_keys() {
	return [
		"donkey_cicero_breathe",
		"donkey_cicero_books",
		"donkey_cicero_garden",
		"donkey_cicero_gratitude",
		"donkey_cicero_friendship",
		"donkey_cicero_money",
		"donkey_cicero_memory",
		"donkey_cicero_moderation",
		"donkey_cicero_mistakes",
		"donkey_cicero_history",
		"donkey_cicero_laws",
		"donkey_cicero_not_alone",
		"donkey_cicero_meta"
	]
}

[es=(figure_caravan_donkey, setup_phrase)]
function figure_caravan_donkey_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	if (f.action_state == FIGURE_ACTION_132_FOLLOWER_RUNAWAY) {
		figure_apply_phrase(f, "donkey_cicero_runaway")
		return
	}

	var keys = figure_caravan_donkey_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
