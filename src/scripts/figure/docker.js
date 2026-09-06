log_info("akhenaten: figure docker started")

figure_docker {
	animations {
		walk { pack:PACK_SPR_MAIN, id:43, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:44, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DOCKER }
	}

	sounds {
		docker_need_more_help { sound:"dockpusher_e01.wav", text: "#docker_need_more_help" }
		docker_wait_until_space_opens_up { sound:"dockpusher_e02.wav", text: "#docker_wait_until_space_opens_up" }
		docker_cant_haul_goods_much_farther { sound:"dockpusher_e03.wav", text: "#docker_cant_haul_goods_much_farther" }
		docker_disease_risk { sound:"docker_disease_risk.wav", text: "#docker_disease_risk" }
		docker_no_food_in_city { sound:"docker_no_food_in_city.wav", text: "#docker_no_food_in_city" }
		docker_city_have_no_army { sound:"docker_city_have_no_army.wav", text: "#docker_city_have_no_army" }
		docker_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		docker_gods_are_angry { sound:"docker_gods_are_angry.wav", text: "#docker_gods_are_angry" }
		docker_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		docker_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		docker_low_entertainment { sound:"docker_low_entertainment.wav", text: "#docker_low_entertainment" }
		docker_city_is_good { sound:"docker_city_is_good.wav", text: "#docker_city_is_good" }
		docker_city_is_amazing { sound:"docker_city_is_amazing.wav", text: "#docker_city_is_amazing" }
	}

	use_cart : true
	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_docker_gods_are_angry() {
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

function figure_docker_city_phrase_keys() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("docker_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("docker_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("docker_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("docker_need_workers")
	}

	if (figure_docker_gods_are_angry()) {
		keys.push("docker_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("docker_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("docker_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("docker_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("docker_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("docker_city_is_amazing")
	}

	return keys
}

[es=(figure_docker, setup_phrase)]
function figure_docker_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var keys = []
	var state = f.action_state
	var dock = city.get_dock(f.home_building_id)

	if (state == ACTION_1_DOCKER_IMPORT_QUEUE || state == ACTION_2_DOCKER_EXPORT_QUEUE) {
		keys.push("docker_wait_until_space_opens_up")
	}

	if (dock && dock.num_ships > 60) {
		keys.push("docker_need_more_help")
	}

	if (state == ACTION_3_DOCKER_IMPORT_GOING_TO_WAREHOUSE ||
		state == ACTION_4_DOCKER_EXPORT_GOING_TO_WAREHOUSE) {
		if (__figure_source_dest_max_distance(f.id) >= 25) {
			keys.push("docker_cant_haul_goods_much_farther")
		}
	}

	var city_keys = figure_docker_city_phrase_keys()
	for (var i = 0; i < city_keys.length; i++) {
		keys.push(city_keys[i])
	}

	if (keys.length == 0) {
		keys.push("docker_need_more_help")
	}

	figure_apply_phrase(f, keys[Math.floor(Math.random() * keys.length)])
}
