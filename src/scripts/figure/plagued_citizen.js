log_info("akhenaten: figure plagued_citizen started")

// Plague carrier — OG image groups 242 walk / 244 death (SprMain 203 / 205, shared with figure_drunkard).
figure_plagued_citizen {
	animations {
		walk { pack:PACK_SPR_MAIN, id:203, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:205, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PLAGUED_CITIZEN }
	}

	sounds {
		plagued_i_feel_awful { sound:"disease_e01.wav", text: "#plagued_i_feel_awful" }
		plagued_fever_spreads { sound:"plagued_fever_spreads.wav", text: "#plagued_fever_spreads" }
		plagued_no_food_in_city { sound:"plagued_no_food_in_city.wav", text: "#plagued_no_food_in_city" }
		plagued_city_have_no_army { sound:"plagued_city_have_no_army.wav", text: "#plagued_city_have_no_army" }
		plagued_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		plagued_gods_are_angry { sound:"plagued_gods_are_angry.wav", text: "#plagued_gods_are_angry" }
		plagued_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		plagued_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		plagued_low_entertainment { sound:"plagued_low_entertainment.wav", text: "#plagued_low_entertainment" }
		plagued_city_is_good { sound:"plagued_city_is_good.wav", text: "#plagued_city_is_good" }
		plagued_city_is_amazing { sound:"plagued_city_is_amazing.wav", text: "#plagued_city_is_amazing" }
	}

	// OG Figure_model.txt row 98, city_disasters.h PLAGUE_FIGURE_WAIT_TICKS, plagues.h PLAGUE_CITIZEN_ROAD_RADIUS.
	category: figure_category_citizen
	max_damage: 10
	terrain_usage: TERRAIN_USAGE_ROADS
	spawn_wait_ticks: 500
	road_radius: 2

	// OG figure_data.c figure_corpse_offsets[wait_ticks / 2]: death frame from each wait_ticks on.
	corpse_frames: [
		{ wait_ticks:0, frame:0 }    // index 0
		{ wait_ticks:2, frame:1 }    // index 1
		{ wait_ticks:4, frame:2 }    // index 2
		{ wait_ticks:6, frame:3 }    // index 3
		{ wait_ticks:8, frame:4 }    // index 4..15
		{ wait_ticks:32, frame:5 }   // index 16..35
		{ wait_ticks:72, frame:6 }   // index 36..75
		{ wait_ticks:152, frame:7 }  // index 76..127
		{ wait_ticks:256, frame:0 }  // index 128
		{ wait_ticks:258, frame:1 }  // index 129
		{ wait_ticks:260, frame:2 }  // index 130
		{ wait_ticks:262, frame:3 }  // index 131
		{ wait_ticks:264, frame:4 }  // index 132..143
		{ wait_ticks:288, frame:0 }  // index 144..255, zero-filled
	]
}

function figure_plagued_citizen_gods_are_angry() {
	for (var i = 0; i < gods.length; i++) {
		var god = gods[i]
		if (!city.gods.is_known(god.type)) {
			continue
		}
		if (city.gods.at(god.type).mood < 51) {
			return true
		}
	}
	return false
}

function figure_plagued_citizen_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push("plagued_i_feel_awful")
	keys.push("plagued_fever_spreads")

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("plagued_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("plagued_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("plagued_need_workers")
	}

	if (figure_plagued_citizen_gods_are_angry()) {
		keys.push("plagued_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("plagued_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("plagued_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("plagued_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("plagued_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("plagued_city_is_amazing")
	}

	return keys
}

[es=(figure_plagued_citizen, setup_phrase)]
function figure_plagued_citizen_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = figure_plagued_citizen_city_phrase_keys()
	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
