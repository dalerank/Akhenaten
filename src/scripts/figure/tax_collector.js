log_info("akhenaten: figure tax_collector started")

figure_tax_collector {
	overlay : OVERLAY_TAX_INCOME
	animations {
		walk { pack:PACK_SPR_MAIN, id:41, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:42, max_frames:8, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_TAX_COLLECTOR }
	}

	sounds {
		taxman_need_more_tax_collectors { sound: "taxman_e01.wav", text: "#taxman_need_more_tax_collectors" }
		taxman_high_taxes { sound: "taxman_e02.wav", text: "#taxman_high_taxes" }
		taxman_much_pooh_houses { sound: "taxman_e03.wav", text: "#taxman_much_pooh_houses" }
		taxman_desease_can_start_at_any_moment { sound: "taxman_g01.wav", text: "#taxman_desease_can_start_at_any_moment" }
		taxman_no_food_in_city { sound: "taxman_g02.wav", text: "#taxman_no_food_in_city" }
		taxman_city_have_no_army { sound: "taxman_g03.wav", text: "#taxman_city_have_no_army" }
		taxman_need_workers { sound: "taxman_g04.wav", text: "#taxman_need_workers" }
		taxman_gods_are_angry { sound: "taxman_g05.wav", text: "#taxman_gods_are_angry" }
		taxman_city_is_bad { sound: "taxman_g06.wav", text: "#taxman_city_is_bad" }
		taxman_much_unemployments { sound: "taxman_g07.wav", text: "#taxman_much_unemployments" }
		taxman_low_entertainment { sound: "taxman_g08.wav", text: "#taxman_low_entertainment" }
		taxman_city_is_good { sound: "taxman_g09.wav", text: "#taxman_city_is_good" }
		taxman_city_is_amazing { sound: "taxman_g10.wav", text: "#taxman_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 20
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 512
	permission : epermission_tax_collector
}

function figure_tax_collector_gods_are_angry() {
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

function figure_tax_collector_city_phrase_key() {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.taxes.percentage_taxed_people < 80) {
		keys.push("taxman_need_more_tax_collectors")
	}

	if (mood_cause == 3) { // LOW_MOOD_HIGH_TAXES
		keys.push("taxman_high_taxes")
	}

	// C++ used this walker's poor_taxed/middle/reach ratio (>50% poor). Not in JS yet.
	if (city.taxes.percentage_taxed_people >= 50) {
		keys.push("taxman_much_pooh_houses")
	}

	if (city.health_rating < 30) {
		keys.push("taxman_desease_can_start_at_any_moment")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("taxman_no_food_in_city")
	}

	if (city.num_forts < 1) {
		keys.push("taxman_city_have_no_army")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("taxman_need_workers")
	}

	if (figure_tax_collector_gods_are_angry()) {
		keys.push("taxman_gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("taxman_city_is_bad")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("taxman_much_unemployments")
	}

	if (__city_festival.months_since_festival > 6) {
		keys.push("taxman_low_entertainment")
	}

	if (sentiment > 90) {
		keys.push("taxman_city_is_amazing")
	} else if (sentiment > 50) {
		keys.push("taxman_city_is_good")
	}

	if (keys.length == 0) {
		return "taxman_city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_tax_collector, setup_phrase)]
function figure_tax_collector_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_tax_collector_city_phrase_key())
}
