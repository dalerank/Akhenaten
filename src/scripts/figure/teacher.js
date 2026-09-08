log_info("akhenaten: figure teacher started")

figure_teacher {
	overlay : OVERLAY_SCRIBAL_SCHOOL
	animations {
		walk { pack:PACK_SPR_MAIN, id:201, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:202, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TEACHER }
	}

	sounds {
		teacher_festival_info { sound: "teacher_e01.wav", text: "#teacher_festival_info" }
		teacher_low_entertainment { sound: "teacher_e01.wav", text: "#teacher_low_entertainment" }
		teacher_desease_can_start_at_any_moment { sound: "teacher_g01.wav", text: "#teacher_desease_can_start_at_any_moment" }
		teacher_no_food_in_city { sound: "teacher_g02.wav", text: "#teacher_no_food_in_city" }
		teacher_city_not_safety { sound: "teacher_g03.wav", text: "#teacher_city_not_safety" }
		teacher_need_workers { sound: "teacher_g04.wav", text: "#teacher_need_workers" }
		teacher_gods_are_angry { sound: "teacher_g05.wav", text: "#teacher_gods_are_angry" }
		teacher_low_rating { sound: "teacher_g06.wav", text: "#teacher_low_rating" }
		teacher_much_unemployments { sound: "teacher_g07.wav", text: "#teacher_much_unemployments" }
		teacher_city_is_good { sound: "teacher_g08.wav", text: "#teacher_city_is_good" }
		teacher_city_much_better { sound: "teacher_g09.wav", text: "#teacher_city_much_better" }
		teacher_city_is_amazing { sound: "teacher_g10.wav", text: "#teacher_city_is_amazing" }
	}

	category : figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_education
}

function figure_teacher_gods_are_angry() {
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

function figure_teacher_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 20) {
		keys.push("teacher_desease_can_start_at_any_moment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("teacher_low_entertainment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("teacher_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("teacher_city_not_safety")
	}

	if (figure_teacher_gods_are_angry()) {
		keys.push("teacher_gods_are_angry")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("teacher_need_workers")
	}

	if (city.kingdome.rating < 30) {
		keys.push("teacher_low_rating")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("teacher_much_unemployments")
	}

	if (sentiment > 90) {
		keys.push("teacher_city_is_amazing")
	} else if (sentiment > 70) {
		keys.push("teacher_city_much_better")
	} else if (sentiment > 40) {
		keys.push("teacher_city_is_good")
	}

	keys.push("teacher_festival_info")

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_teacher, setup_phrase)]
function figure_teacher_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_teacher_city_phrase_key())
}
