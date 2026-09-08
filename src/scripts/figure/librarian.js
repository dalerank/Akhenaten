log_info("akhenaten: figure librarian started")

figure_librarian {
	overlay : OVERLAY_LIBRARY
	animations {
		walk { pack:PACK_SPR_MAIN, id:57, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:58, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_LIBRARIAN }
	}

	sounds {
		library_read_about_festivals { sound: "library_e01.wav", text: "#library_read_about_festivals" }
		library_people_are_sick { sound: "library_g01.wav", text: "#library_people_are_sick" }
		library_no_food_in_city { sound: "library_g02.wav", text: "#library_no_food_in_city" }
		library_defenses_are_weak { sound: "library_g03.wav", text: "#library_defenses_are_weak" }
		library_need_more_workers { sound: "library_g04.wav", text: "#library_need_more_workers" }
		library_gods_are_angry { sound: "library_g05.wav", text: "#library_gods_are_angry" }
		library_reputation_is_low { sound: "library_g06.wav", text: "#library_reputation_is_low" }
		library_high_unemployment { sound: "library_g07.wav", text: "#library_high_unemployment" }
		library_low_entertainment { sound: "library_g08.wav", text: "#library_low_entertainment" }
		library_city_is_ok { sound: "library_g09.wav", text: "#library_city_is_ok" }
		library_city_is_amazing { sound: "library_g10.wav", text: "#library_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_education
}

function figure_librarian_gods_are_angry() {
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

function figure_librarian_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (__city_festival.months_since_festival > 6) {
		keys.push("library_read_about_festivals")
		keys.push("library_low_entertainment")
	}

	if (city.health_rating < 40) {
		keys.push("library_people_are_sick")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("library_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("library_defenses_are_weak")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("library_need_more_workers")
	}

	if (figure_librarian_gods_are_angry()) {
		keys.push("library_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("library_reputation_is_low")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("library_high_unemployment")
	}

	if (sentiment > 90) {
		keys.push("library_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("library_city_is_ok")
	}

	if (keys.length == 0) {
		return "library_city_is_ok"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_librarian, setup_phrase)]
function figure_librarian_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_librarian_city_phrase_key())
}
