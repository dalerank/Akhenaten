log_info("akhenaten: figure water_carrier started")

figure_water_carrier {
	overlay : OVERLAY_WATER
	animations {
		walk { pack:PACK_SPR_MAIN, id:59, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:60, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_WATER_CARRIER }
	}

	sounds {
		water_desease_can_start_at_any_moment { sound: "water_g01.wav", text: "#water_desease_can_start_at_any_moment" }
		water_no_food_in_city { sound: "water_g02.wav", text: "#water_no_food_in_city" }
		water_city_have_no_army { sound: "water_g03.wav", text: "#water_city_have_no_army" }
		water_need_workers { sound: "water_g04.wav", text: "#water_need_workers" }
		water_gods_are_angry { sound: "water_g05.wav", text: "#water_gods_are_angry" }
		water_city_is_bad { sound: "water_g06.wav", text: "#water_city_is_bad" }
		water_much_unemployments { sound: "water_g07.wav", text: "#water_much_unemployments" }
		water_low_entertainment { sound: "water_g08.wav", text: "#water_low_entertainment" }
		water_city_is_good { sound: "water_g09.wav", text: "#water_city_is_good" }
		water_city_is_amazing { sound: "water_g10.wav", text: "#water_city_is_amazing" }
	}

	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 640
	record_path : true
}

function figure_water_carrier_gods_are_angry() {
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

function figure_water_carrier_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("water_desease_can_start_at_any_moment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("water_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("water_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("water_need_workers")
	}

	if (figure_water_carrier_gods_are_angry()) {
		keys.push("water_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("water_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("water_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("water_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("water_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("water_city_is_good")
	}

	if (keys.length == 0) {
		return "water_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_water_carrier, setup_phrase)]
function figure_water_carrier_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_water_carrier_city_phrase_key())
}
