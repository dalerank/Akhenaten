log_info("akhenaten: figure immigrant started")

figure_immigrant {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id: 14, max_frames:12 }
		death { id: 15, max_frames:8, loop:false }
		swim { id:138, max_frames:4, duration:4 }
		cart { id:52, max_frames:1 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_IMMIGRANT }
	}

	sounds {
		immigrant_im_new_here { sound:"immigrant_e01.wav", text: "#immigrant_im_new_here" }
		immigrant_heard_there_is_a_job_here { sound:"immigrant_e02.wav", text: "#immigrant_heard_there_is_a_job_here" }
		immigrant_city_has_plenty_of_food { sound:"immigrant_e03.wav", text: "#immigrant_city_has_plenty_of_food" }
		immigrant_disease_risk { sound:"immigrant_disease_risk.wav", text: "#immigrant_disease_risk" }
		immigrant_city_have_no_army { sound:"immigrant_city_have_no_army.wav", text: "#immigrant_city_have_no_army" }
		immigrant_need_workers { sound:"immigrant_need_workers.wav", text: "#immigrant_need_workers" }
		immigrant_gods_are_angry { sound:"immigrant_gods_are_angry.wav", text: "#immigrant_gods_are_angry" }
		immigrant_city_is_bad { sound:"immigrant_city_is_bad.wav", text: "#immigrant_city_is_bad" }
		immigrant_much_unemployment { sound:"immigrant_much_unemployment.wav", text: "#immigrant_much_unemployment" }
		immigrant_low_entertainment { sound:"immigrant_low_entertainment.wav", text: "#immigrant_low_entertainment" }
		immigrant_city_is_good { sound:"immigrant_city_is_good.wav", text: "#immigrant_city_is_good" }
		immigrant_city_is_amazing { sound:"immigrant_city_is_amazing.wav", text: "#immigrant_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 20
	terrain_usage: TERRAIN_USAGE_ANIMAL
}

function figure_immigrant_gods_are_angry() {
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

function figure_immigrant_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("immigrant_disease_risk")
	}

	if (city.num_forts < 1) {
		keys.push("immigrant_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("immigrant_need_workers")
	}

	if (figure_immigrant_gods_are_angry()) {
		keys.push("immigrant_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("immigrant_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("immigrant_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("immigrant_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("immigrant_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("immigrant_city_is_amazing")
	}

	return keys
}

function figure_immigrant_phrase_key(f) {
	var keys = []
	var state = f.action_state
	switch (state) {
	case ACTION_0_IMMIGRANT_CREATED:
	case ACTION_8_RECALCULATE:
		keys.push("immigrant_im_new_here")
		break
	case ACTION_1_IMMIGRANT_ARRIVING:
		keys.push("immigrant_heard_there_is_a_job_here")
		break
	case ACTION_2_IMMIGRANT_ENTERING_HOUSE:
		keys.push("immigrant_city_has_plenty_of_food")
		break
	}

	var city_keys = figure_immigrant_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("immigrant_im_new_here")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_immigrant, setup_phrase)]
function figure_immigrant_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_immigrant_phrase_key(f))
}
