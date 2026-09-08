log_info("akhenaten: figure zookeeper started")

// Cleopatra SprMain2: bmp "zookeeper", group 35 starts at entry 1616 (SprMain2_01616).
figure_zookeeper {
	overlay : OVERLAY_ZOO
	animations {
		walk { pack:PACK_EXPANSION_SPR, id:35, max_frames:12 }
		death { pack:PACK_EXPANSION_SPR, id:36, max_frames:7, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_ZOOKEEPER }
	}

	sounds {
		zookeeper_danger_of_plague { sound: "zookeeper_e01.wav", text: "#zookeeper_danger_of_plague" }
		zookeeper_no_food_in_city { sound: "zookeeper_e02.wav", text: "#zookeeper_no_food_in_city" }
		zookeeper_defenses_are_weak { sound: "zookeeper_e03.wav", text: "#zookeeper_defenses_are_weak" }
		zookeeper_need_more_workers { sound: "zookeeper_e04.wav", text: "#zookeeper_need_more_workers" }
		zookeeper_gods_are_angry { sound: "zookeeper_e05.wav", text: "#zookeeper_gods_are_angry" }
		zookeeper_reputation_is_low { sound: "zookeeper_e06.wav", text: "#zookeeper_reputation_is_low" }
		zookeeper_high_unemployment { sound: "zookeeper_e07.wav", text: "#zookeeper_high_unemployment" }
		zookeeper_low_entertainment { sound: "zookeeper_e08.wav", text: "#zookeeper_low_entertainment" }
		zookeeper_city_is_ok { sound: "zookeeper_e09.wav", text: "#zookeeper_city_is_ok" }
		zookeeper_city_is_amazing { sound: "zookeeper_e10.wav", text: "#zookeeper_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length: 640
	permission : epermission_entertainer
}

function figure_zookeeper_gods_are_angry() {
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

function figure_zookeeper_phrase_key() {
	if (__city_figures_total_invading_enemies() > 0) {
		return "zookeeper_defenses_are_weak"
	}

	// C++ scanned houses for disease_days; health rating is the JS proxy.
	if (city.health_rating < 20) {
		return "zookeeper_danger_of_plague"
	}

	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (sentiment < 30) {
		keys.push("zookeeper_reputation_is_low")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("zookeeper_high_unemployment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("zookeeper_no_food_in_city")
	}

	if (city.labor.workers_needed > 10) {
		keys.push("zookeeper_need_more_workers")
	}

	if (figure_zookeeper_gods_are_angry()) {
		keys.push("zookeeper_gods_are_angry")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("zookeeper_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("zookeeper_city_is_amazing")
	} else if (sentiment > 40) {
		keys.push("zookeeper_city_is_ok")
	}

	if (keys.length == 0) {
		return "zookeeper_city_is_ok"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_zookeeper, setup_phrase)]
function figure_zookeeper_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_zookeeper_phrase_key())
}
