log_info("akhenaten: figure cartpusher started")

figure_cartpusher {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:43, max_frames:12 }
		idle { id:43, max_frames:1, loop:false }
		death { id:44, max_frames:8, loop:false }
		swim { id:138, max_frames:4, duration:4 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_CART_PUSHER }
	}

	sounds {
		cartpusher_have_no_place_for_goods { sound:"cartpusher_e01.wav", text: "#cartpusher_have_no_place_for_goods" }
		cartpusher_i_have_time_for_rest { sound:"cartpusher_e02.wav", text: "#cartpusher_i_have_time_for_rest" }
		cartpusher_road_too_long { sound:"cartpusher_e03.wav", text: "#cartpusher_road_too_long" }
		cartpusher_i_have_no_destination { sound:"cartpusher_e01.wav", text: "#cartpusher_i_have_no_destination" }
		cartpusher_back_to_home { sound:"cartpusher_e02.wav", text: "#cartpusher_back_to_home" }
		cartpusher_delivering_items { sound:"cartpusher_e03.wav", text: "#cartpusher_delivering_items" }
		cartpusher_disease_risk { sound:"cartpusher_disease_risk.wav", text: "#cartpusher_disease_risk" }
		cartpusher_no_food_in_city { sound:"cartpusher_no_food_in_city.wav", text: "#cartpusher_no_food_in_city" }
		cartpusher_city_have_no_army { sound:"cartpusher_city_have_no_army.wav", text: "#cartpusher_city_have_no_army" }
		cartpusher_need_workers { sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers" }
		cartpusher_gods_are_angry { sound:"cartpusher_gods_are_angry.wav", text: "#cartpusher_gods_are_angry" }
		cartpusher_city_is_bad { sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad" }
		cartpusher_much_unemployment { sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment" }
		cartpusher_low_entertainment { sound:"cartpusher_low_entertainment.wav", text: "#cartpusher_low_entertainment" }
		cartpusher_city_is_good { sound:"cartpusher_city_is_good.wav", text: "#cartpusher_city_is_good" }
		cartpusher_city_is_amazing { sound:"cartpusher_city_is_amazing.wav", text: "#cartpusher_city_is_amazing" }
	}

	use_cart : true
	wait_on_calculate_destination : 30
	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS,
	record_path : true
}

function figure_cartpusher_gods_are_angry() {
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

function figure_cartpusher_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause

	if (city.health_rating < 30) {
		keys.push("cartpusher_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("cartpusher_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("cartpusher_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("cartpusher_need_workers")
	}

	if (figure_cartpusher_gods_are_angry()) {
		keys.push("cartpusher_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("cartpusher_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("cartpusher_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("cartpusher_low_entertainment")
	}

	var sentiment = city.sentiment.value
	if (sentiment > 50) {
		keys.push("cartpusher_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("cartpusher_city_is_amazing")
	}

	if (keys.length == 0) {
		return "cartpusher_delivering_items"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_cartpusher, setup_phrase)]
function figure_cartpusher_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var state = f.action_state
	switch (state) {
	case ACTION_8_RECALCULATE:
	case ACTION_20_CARTPUSHER_INITIAL:
		figure_apply_phrase(f, "cartpusher_i_have_no_destination")
		return
	case ACTION_24_CARTPUSHER_AT_WAREHOUSE:
	case ACTION_25_CARTPUSHER_AT_GRANARY:
	case ACTION_26_CARTPUSHER_AT_WORKSHOP:
		figure_apply_phrase(f, "cartpusher_have_no_place_for_goods")
		return
	case ACTION_12_CARTPUSHER_DELIVERING_UNLOADING_GOODS:
	case ACTION_13_CARTPUSHER_DELIVERING_UNLOADING_FOODS:
	case ACTION_14_CARTPUSHER_UNLOADING_GOLD:
		figure_apply_phrase(f, "cartpusher_i_have_time_for_rest")
		return
	case ACTION_27_CARTPUSHER_RETURNING:
	case ACTION_53_CARTPUSHER_RETURNING_EMPTY:
	case ACTION_56_CARTPUSHER_RETURNING_WITH_FOOD:
		figure_apply_phrase(f, "cartpusher_back_to_home")
		return
	case ACTION_9_CARTPUSHER_DELIVERING_GOODS:
	case ACTION_10_CARTPUSHER_DELIVERING_FOOD:
	case ACTION_11_CARTPUSHER_DELIVERING_GOLD:
	case ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE:
	case ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY:
	case ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP:
	case ACTION_51_CARTPUSHER_DELIVERING_RESOURCE:
		figure_apply_phrase(f, "cartpusher_delivering_items")
		return
	case ACTION_54_CARTPUSHER_GETTING_FOOD:
	case ACTION_57_CARTPUSHER_GETTING_RESOURCE:
		figure_apply_phrase(f, "cartpusher_road_too_long")
		return
	}

	figure_apply_phrase(f, figure_cartpusher_city_phrase_key())
}
