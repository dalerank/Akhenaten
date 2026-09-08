log_info("akhenaten: figure market_trader started")

figure_market_trader {
	overlay : OVERLAY_BAZAAR_ACCESS
	animations {
		walk { pack:PACK_SPR_MAIN, id:18, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:19, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_MARKET_TRADER }
	}

	sounds {
		goods_are_finished { sound:"mkt_seller_e01.wav", text: "#goods_are_finished" }
		we_are_selling_goods { sound:"mkt_seller_e02.wav", text: "#we_are_selling_goods" }
		seller_city_has_low_health { sound:"seller_city_has_low_health.wav", text: "#seller_city_has_low_health" }
		seller_no_food_in_city { sound:"seller_no_food_in_city.wav", text: "#seller_no_food_in_city" }
		seller_city_have_no_army { sound:"seller_city_have_no_army.wav", text: "#seller_city_have_no_army" }
		seller_much_unemployments { sound:"seller_much_unemployments.wav", text: "#seller_much_unemployments" }
		seller_gods_are_angry { sound:"seller_gods_are_angry.wav", text: "#seller_gods_are_angry" }
		seller_city_is_bad_reputation { sound:"seller_city_is_bad_reputation.wav", text: "#seller_city_is_bad_reputation" }
		seller_too_much_unemployments { sound:"seller_too_much_unemployments.wav", text: "#seller_too_much_unemployments" }
		seller_low_entertainment { sound:"seller_low_entertainment.wav", text: "#seller_low_entertainment" }
		seller_city_is_good { sound:"seller_city_is_good.wav", text: "#seller_city_is_good" }
		seller_city_is_amazing { sound:"seller_city_is_amazing.wav", text: "#seller_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_market
	record_path : true
}

function figure_market_trader_gods_are_angry() {
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

function figure_market_trader_work_phrase_key(f) {
	// ACTION_126_MARKET_TRADER_RETURNING / ACTION_126_ROAMER_RETURNING
	if (f.action_state == 126) {
		return "goods_are_finished"
	}
	return "we_are_selling_goods"
}

function figure_market_trader_city_phrase_key(f) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	keys.push(figure_market_trader_work_phrase_key(f))

	if (city.health_rating < 30) {
		keys.push("seller_city_has_low_health")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("seller_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("seller_city_have_no_army")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("seller_much_unemployments")
	}

	if (figure_market_trader_gods_are_angry()) {
		keys.push("seller_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("seller_city_is_bad_reputation")
	}

	if (city.labor.unemployment_percentage >= 15) {
		keys.push("seller_too_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("seller_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("seller_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("seller_city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_market_trader, setup_phrase)]
function figure_market_trader_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_market_trader_city_phrase_key(f))
}
