log_info("akhenaten: figure delivery_boy started")

figure_delivery_boy {
	overlay : OVERLAY_BAZAAR_ACCESS
	animations {
		walk { pack:PACK_SPR_MAIN, id:9, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:10, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_DELIVERY_BOY }
	}

	sounds {
		marketboy_these_baskets_are_too_heavy { sound: "marketboy_e01.wav", text: "#marketboy_these_baskets_are_too_heavy" }
		marketboy_bossy_lady_makes_me_carry_goods { sound: "marketboy_e02.wav", text: "#marketboy_bossy_lady_makes_me_carry_goods" }
		marketboy_one_day_ill_run_the_bazaar { sound: "marketboy_e03.wav", text: "#marketboy_one_day_ill_run_the_bazaar" }
		marketboy_runaway { sound: "marketboy_runaway.wav", text: "#marketboy_runaway" }
		marketboy_disease_risk { sound: "marketboy_disease_risk.wav", text: "#marketboy_disease_risk" }
		marketboy_no_food_in_city { sound: "marketboy_no_food_in_city.wav", text: "#marketboy_no_food_in_city" }
		marketboy_city_have_no_army { sound: "marketboy_city_have_no_army.wav", text: "#marketboy_city_have_no_army" }
		marketboy_need_workers { sound: "marketboy_need_workers.wav", text: "#marketboy_need_workers" }
		marketboy_gods_are_angry { sound: "marketboy_gods_are_angry.wav", text: "#marketboy_gods_are_angry" }
		marketboy_city_is_bad { sound: "marketboy_city_is_bad.wav", text: "#marketboy_city_is_bad" }
		marketboy_much_unemployment { sound: "marketboy_much_unemployment.wav", text: "#marketboy_much_unemployment" }
		marketboy_low_entertainment { sound: "marketboy_low_entertainment.wav", text: "#marketboy_low_entertainment" }
		marketboy_city_is_good { sound: "marketboy_city_is_good.wav", text: "#marketboy_city_is_good" }
		marketboy_city_is_amazing { sound: "marketboy_city_is_amazing.wav", text: "#marketboy_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage: 10
	terrain_usage : TERRAIN_USAGE_ROADS,
}

function figure_delivery_boy_gods_are_angry() {
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

function figure_delivery_boy_work_phrase_keys() {
	return [
		"marketboy_these_baskets_are_too_heavy",
		"marketboy_bossy_lady_makes_me_carry_goods",
		"marketboy_one_day_ill_run_the_bazaar"
	]
}

function figure_delivery_boy_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.health_rating < 30) {
		keys.push("marketboy_disease_risk")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("marketboy_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("marketboy_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("marketboy_need_workers")
	}

	if (figure_delivery_boy_gods_are_angry()) {
		keys.push("marketboy_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("marketboy_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("marketboy_much_unemployment")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("marketboy_low_entertainment")
	}

	if (sentiment > 50) {
		keys.push("marketboy_city_is_good")
	}

	if (sentiment > 90) {
		keys.push("marketboy_city_is_amazing")
	}

	if (keys.length == 0) {
		var work = figure_delivery_boy_work_phrase_keys()
		return work[Math.floor(Math.random() * work.length)]
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_delivery_boy, setup_phrase)]
function figure_delivery_boy_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	// FIGURE_ACTION_132_FOLLOWER_RUNAWAY
	if (f.action_state == 132) {
		figure_apply_phrase(f, "marketboy_runaway")
		return
	}

	// Mix work chatter with city mood.
	if (Math.random() < 0.45) {
		var work = figure_delivery_boy_work_phrase_keys()
		figure_apply_phrase(f, work[Math.floor(Math.random() * work.length)])
		return
	}

	figure_apply_phrase(f, figure_delivery_boy_city_phrase_key())
}
