log_info("akhenaten: figure market_buyer started")

figure_market_buyer {
	overlay : OVERLAY_BAZAAR_ACCESS
	animations {
		walk { pack:PACK_SPR_MAIN, id:16, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:17, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MARKET_BUYER }
	}

	sounds {
		buyer_goto_store { sound:"mkt_buyer_e01.wav", text: "#buyer_goto_store" }
		buyer_back_to_market { sound:"mkt_buyer_e02.wav", text: "#buyer_back_to_market" }
		buyer_city_has_low_health { sound:"mkt_buyer_g01.wav", text: "#buyer_city_has_low_health" }
		buyer_no_food_in_city { sound:"mkt_buyer_g02.wav", text: "#buyer_no_food_in_city" }
		buyer_city_have_no_army { sound:"mkt_buyer_g03.wav", text: "#buyer_city_have_no_army" }
		buyer_much_unemployments { sound:"mkt_buyer_g04.wav", text: "#buyer_much_unemployments" }
		buyer_gods_are_angry { sound:"mkt_buyer_g05.wav", text: "#buyer_gods_are_angry" }
		buyer_city_is_bad_reputation { sound:"mkt_buyer_g06.wav", text: "#buyer_city_is_bad_reputation" }
		buyer_too_much_unemployments { sound:"mkt_buyer_g07.wav", text: "#buyer_too_much_unemployments" }
		buyer_low_entertainment { sound:"mkt_buyer_g08.wav", text: "#buyer_low_entertainment" }
		buyer_city_is_good { sound:"mkt_buyer_g09.wav", text: "#buyer_city_is_good" }
		buyer_city_is_amazing { sound:"mkt_buyer_g10.wav", text: "#buyer_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS,
	record_path : true
}

function figure_market_buyer_gods_are_angry() {
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

function figure_market_buyer_city_phrase_key(f) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	// ACTION_145_MARKET_BUYER_GOING_TO_STORAGE / ACTION_146_MARKET_BUYER_RETURNING
	if (f.action_state == 145) {
		keys.push("buyer_goto_store")
	} else if (f.action_state == 146) {
		keys.push("buyer_back_to_market")
	}

	if (city.health_rating < 30) {
		keys.push("buyer_city_has_low_health")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("buyer_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("buyer_city_have_no_army")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("buyer_much_unemployments")
	}

	if (figure_market_buyer_gods_are_angry()) {
		keys.push("buyer_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("buyer_city_is_bad_reputation")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("buyer_too_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("buyer_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("buyer_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("buyer_city_is_good")
	}

	if (keys.length == 0) {
		return "buyer_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_market_buyer, setup_phrase)]
function figure_market_buyer_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_market_buyer_city_phrase_key(f))
}
