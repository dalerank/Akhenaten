log_info("akhenaten: figure worker started")

figure_worker {
	overlay : OVERLAY_LABOR
	animations {
		walk { pack:PACK_SPR_MAIN, id:116, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:117, max_frames:8, loop:false }
		work { pack:PACK_SPR_MAIN, id:118, max_frames:12 }
		pulling { pack:PACK_SPR_MAIN, id:160, max_frames:12 } // OG IMAGE_GROUP_FIGURE_LABORER_PULLING
	}

	sounds {
		worker_going_to_workplace { sound:"worker_e02.wav", text: "#worker_going_to_workplace" }
		worker_farm_is_flooded { sound:"worker_e03.wav", text: "#worker_farm_is_flooded" }
		worker_desease_can_start_at_any_moment { sound:"worker_g01.wav", text: "#worker_desease_can_start_at_any_moment" }
		worker_no_food_in_city { sound:"worker_g02.wav", text: "#worker_no_food_in_city" }
		worker_enemies_in_city { sound:"worker_g03.wav", text: "#worker_enemies_in_city" }
		worker_need_workers { sound:"worker_g04.wav", text: "#worker_need_workers" }
		worker_gods_are_angry { sound:"worker_g05.wav", text: "#worker_gods_are_angry" }
		worker_city_is_bad { sound:"worker_g06.wav", text: "#worker_city_is_bad" }
		worker_much_unemployments { sound:"worker_g07.wav", text: "#worker_much_unemployments" }
		worker_low_entertainment { sound:"worker_g08.wav", text: "#worker_low_entertainment" }
		worker_city_is_good { sound:"worker_g09.wav", text: "#worker_city_is_good" }
		worker_city_is_amazing { sound:"worker_g10.wav", text: "#worker_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	record_path : true
	// OG laborer.c handles FIGURE_ACTION_WAIT_FOR_FERRY / ON_FERRY; its sled train rides along.
	can_cross_ferry: true
	boards_ferry: true
	// OG laborer_rules defaults (laborer.c).
	load: 400
	yard_wait_ticks: 4
	ramp_route_retry_ticks: 30
	ramp_route_give_up_ticks: 120
	delivered_wait_ticks: 42
	ferry_wait_ticks: 100
	max_roam_ticks: 512
	farm_walk_ticks: 3200
	home_road_radius: 2
	max_out: 4
	labor_seeker_houses: 50
	spawn_delay_full: 3
	spawn_delay_75_percent: 7
	spawn_delay_50_percent: 15
	spawn_delay_25_percent: 29
	spawn_delay_low: 47
	farm_search_distance: 40
	farm_busy_labor_days: 48
	farm_labor_days: 96
	camp_labor_days: 32
	level_tiles_in_a_row: 4
	monument_work_searches: 4
}

function figure_worker_gods_are_angry() {
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

function figure_worker_phrase_key(f) {
	if (__city_figures_total_invading_enemies() > 10) {
		return "worker_enemies_in_city"
	}

	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	// ACTION_10_WORKER_GOING
	if (f.action_state == 10) {
		keys.push("worker_going_to_workplace")
	}

	if (!city.floods.state_is(FLOOD_STATE_FARMABLE)) {
		keys.push("worker_farm_is_flooded")
	}

	if (city.health_rating < 30) {
		keys.push("worker_desease_can_start_at_any_moment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("worker_no_food_in_city")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("worker_need_workers")
	}

	if (figure_worker_gods_are_angry()) {
		keys.push("worker_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("worker_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("worker_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("worker_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("worker_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("worker_city_is_good")
	}

	if (keys.length == 0) {
		return "worker_going_to_workplace"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_worker, setup_phrase)]
function figure_worker_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_worker_phrase_key(f))
}
