log_info("akhenaten: figure bricklayer started")

figure_bricklayer {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:109, max_frames:12 }
		death { id:110, max_frames:8, loop:false }
		work { id:111, max_frames:12, duration:4 }
		idle { id:112, max_frames:8, duration:2 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_BRICKLAYER }
	}

	sounds {
		brick_bricklaying_time_at_monument { sound:"brick_e01.wav", text: "#brick_bricklaying_time_at_monument" }
		brick_monument_will_be_strong { sound:"brick_e02.wav", text: "#brick_monument_will_be_strong" }
		brick_waiting_for_bricks { sound:"brick_waiting_for_bricks.wav", text: "#brick_waiting_for_bricks" }
		brick_looking_for_spot { sound:"brick_looking_for_spot.wav", text: "#brick_looking_for_spot" }
		brick_work_statue { sound:"brick_work_statue.wav", text: "#brick_work_statue" }
		brick_return_to_guild { sound:"brick_return_to_guild.wav", text: "#brick_return_to_guild" }
		brick_leaving_site { sound:"brick_leaving_site.wav", text: "#brick_leaving_site" }
		brick_disease_risk { sound:"brick_disease_risk.wav", text: "#brick_disease_risk" }
		brick_no_food_in_city { sound:"brick_no_food_in_city.wav", text: "#brick_no_food_in_city" }
		brick_city_have_no_army { sound:"brick_city_have_no_army.wav", text: "#brick_city_have_no_army" }
		brick_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		brick_gods_are_angry { sound:"brick_gods_are_angry.wav", text: "#brick_gods_are_angry" }
		brick_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		brick_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		brick_low_entertainment { sound:"brick_low_entertainment.wav", text: "#brick_low_entertainment" }
		brick_city_is_good { sound:"brick_city_is_good.wav", text: "#brick_city_is_good" }
		brick_city_is_amazing { sound:"brick_city_is_amazing.wav", text: "#brick_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_bricklayer_gods_are_angry() {
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

function figure_bricklayer_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause

	if (city.health_rating < 30) {
		keys.push("brick_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("brick_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("brick_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("brick_need_workers")
	}

	if (figure_bricklayer_gods_are_angry()) {
		keys.push("brick_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("brick_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("brick_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("brick_low_entertainment")
	}

	var sentiment = city.sentiment.value
	if (sentiment > 50) {
		keys.push("brick_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("brick_city_is_amazing")
	}

	if (keys.length == 0) {
		return "brick_bricklaying_time_at_monument"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_bricklayer, setup_phrase)]
function figure_bricklayer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case ACTION_4_BRICKLAYER_LAY_BRICKS:
		figure_apply_phrase(f, "brick_monument_will_be_strong")
		return
	case ACTION_12_BRICKLAYER_WORK_STATUE:
		figure_apply_phrase(f, "brick_work_statue")
		return
	case ACTION_5_BRICKLAYER_LOOKING_FOR_IDLE_TILE:
		figure_apply_phrase(f, "brick_looking_for_spot")
		return
	case ACTION_3_BRICKLAYER_WAITING_RESOURCES:
		figure_apply_phrase(f, "brick_waiting_for_bricks")
		return
	case ACTION_6_BRICKLAYER_RETURN_HOME:
		figure_apply_phrase(f, "brick_return_to_guild")
		return
	case ACTION_7_BRICKLAYER_EXIT_FROM_MONUMENT:
		figure_apply_phrase(f, "brick_leaving_site")
		return
	}

	figure_apply_phrase(f, figure_bricklayer_city_phrase_key())
}
