log_info("akhenaten: figure storageyard_cart started")

figure_storageyard_cart {
	animations {
		walk { pack: PACK_SPR_MAIN, id:43, max_frames:12 }
		idle { pack: PACK_SPR_MAIN, id:43, max_frames:1, loop:false }
		death { pack: PACK_SPR_MAIN, id:44, max_frames:8, loop:false }
		swim { pack:PACK_SPR_MAIN, id:138, max_frames:4, duration:4 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_STORAGEYARD_CART }
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
	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_storageyard_cart_phrase_key(f) {
	var state = f.action_state
	switch (state) {
	case 50: // ACTION_50_WAREHOUSECART_CREATED
		return "cartpusher_i_have_no_destination"
	case 9:  // ACTION_9_WAREHOUSECART_DELIVERING_GOODS
	case 51: // ACTION_51_WAREHOUSECART_DELIVERING_RESOURCE
		return "cartpusher_delivering_items"
	case 52: // ACTION_52_WAREHOUSECART_AT_DELIVERY_BUILDING
		return "cartpusher_have_no_place_for_goods"
	case 53: // ACTION_53_WAREHOUSECART_RETURNING_EMPTY
		return "cartpusher_back_to_home"
	case 54: // ACTION_54_WAREHOUSECART_GETTING_FOOD
	case 57: // ACTION_57_WAREHOUSECART_GETTING_RESOURCE
		return "cartpusher_road_too_long"
	case 55: // ACTION_55_WAREHOUSECART_AT_GRANARY_GETTING
	case 58: // ACTION_58_WAREHOUSECART_AT_WAREHOUSE_GETTING_GOODS
		return "cartpusher_i_have_time_for_rest"
	case 56: // ACTION_56_WAREHOUSECART_RETURNING_WITH_FOOD
	case 59: // ACTION_59_WAREHOUSECART_RETURNING_WITH_RESOURCE
		return "cartpusher_back_to_home"
	case 60: // ACTION_60_WAREHOUSECART_UNLOADING_AT_HOME
		return "cartpusher_have_no_place_for_goods"
	}

	return figure_cartpusher_city_phrase_key()
}

[es=(figure_storageyard_cart, setup_phrase)]
function figure_storageyard_cart_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_storageyard_cart_phrase_key(f))
}
