log_info("akhenaten: figure priest started")

figure_priest {
	animations {
		osiris_walk { pack:PACK_SPR_MAIN, id:197, max_frames:12 }
		osiris_death { pack:PACK_SPR_MAIN, id:198, loop:false }
		ra_walk { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		ra_death { pack:PACK_SPR_MAIN, id:211, loop:false }
		ptah_walk { pack:PACK_SPR_MAIN, id:187, max_frames:12 }
		ptah_death { pack:PACK_SPR_MAIN, id:188, loop:false }
		seth_walk { pack:PACK_SPR_MAIN, id:193, max_frames:12 }
		seth_death { pack:PACK_SPR_MAIN, id:194, loop:false }
		bast_walk { pack:PACK_SPR_MAIN, id:208, max_frames:12 }
		bast_death { pack:PACK_SPR_MAIN, id:209, loop:false }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PRIEST }
	}

	sounds {
		// Cleopatra has no e03/e04 for osiris/ra/ptah/seth — reuse nearest g-lines.
		osiris_god_love_festival { sound:"priest_osiris_e01.wav", text: "#osiris_god_love_festival" }
		osiris_city_low_mood { sound:"priest_osiris_e02.wav", text: "#osiris_city_low_mood" }
		osiris_low_entertainment { sound:"priest_osiris_g08.wav", text: "#osiris_low_entertainment" }
		osiris_disease_in_city { sound:"priest_osiris_g01.wav", text: "#osiris_disease_in_city" }
		osiris_city_low_health { sound:"priest_osiris_g01.wav", text: "#osiris_city_low_health" }
		osiris_no_food_in_city { sound:"priest_osiris_g02.wav", text: "#osiris_no_food_in_city" }
		osiris_city_not_safety { sound:"priest_osiris_g03.wav", text: "#osiris_city_not_safety" }
		osiris_need_workers { sound:"priest_osiris_g04.wav", text: "#osiris_need_workers" }
		osiris_gods_are_angry { sound:"priest_osiris_g05.wav", text: "#osiris_gods_are_angry" }
		osiris_low_sentiment { sound:"priest_osiris_g06.wav", text: "#osiris_low_sentiment" }
		osiris_much_unemployments { sound:"priest_osiris_g07.wav", text: "#osiris_much_unemployments" }
		osiris_need_entertainment { sound:"priest_osiris_g08.wav", text: "#osiris_need_entertainment" }
		osiris_city_is_good { sound:"priest_osiris_g09.wav", text: "#osiris_city_is_good" }
		osiris_city_is_amazing { sound:"priest_osiris_g10.wav", text: "#osiris_city_is_amazing" }

		ra_god_love_festival { sound:"priest_ra_e01.wav", text: "#ra_god_love_festival" }
		ra_city_low_mood { sound:"priest_ra_e02.wav", text: "#ra_city_low_mood" }
		ra_low_entertainment { sound:"priest_ra_g08.wav", text: "#ra_low_entertainment" }
		ra_disease_in_city { sound:"priest_ra_g01.wav", text: "#ra_disease_in_city" }
		ra_city_low_health { sound:"priest_ra_g01.wav", text: "#ra_city_low_health" }
		ra_no_food_in_city { sound:"priest_ra_g02.wav", text: "#ra_no_food_in_city" }
		ra_city_not_safety { sound:"priest_ra_g03.wav", text: "#ra_city_not_safety" }
		ra_need_workers { sound:"priest_ra_g04.wav", text: "#ra_need_workers" }
		ra_gods_are_angry { sound:"priest_ra_g05.wav", text: "#ra_gods_are_angry" }
		ra_low_sentiment { sound:"priest_ra_g06.wav", text: "#ra_low_sentiment" }
		ra_much_unemployments { sound:"priest_ra_g07.wav", text: "#ra_much_unemployments" }
		ra_need_entertainment { sound:"priest_ra_g08.wav", text: "#ra_need_entertainment" }
		ra_city_is_good { sound:"priest_ra_g09.wav", text: "#ra_city_is_good" }
		ra_city_is_amazing { sound:"priest_ra_g10.wav", text: "#ra_city_is_amazing" }

		ptah_god_love_festival { sound:"priest_ptah_e01.wav", text: "#ptah_god_love_festival" }
		ptah_city_low_mood { sound:"priest_ptah_e02.wav", text: "#ptah_city_low_mood" }
		ptah_low_entertainment { sound:"priest_ptah_g08.wav", text: "#ptah_low_entertainment" }
		ptah_disease_in_city { sound:"priest_ptah_g01.wav", text: "#ptah_disease_in_city" }
		ptah_city_low_health { sound:"priest_ptah_g01.wav", text: "#ptah_city_low_health" }
		ptah_no_food_in_city { sound:"priest_ptah_g02.wav", text: "#ptah_no_food_in_city" }
		ptah_city_not_safety { sound:"priest_ptah_g03.wav", text: "#ptah_city_not_safety" }
		ptah_need_workers { sound:"priest_ptah_g04.wav", text: "#ptah_need_workers" }
		ptah_gods_are_angry { sound:"priest_ptah_g05.wav", text: "#ptah_gods_are_angry" }
		ptah_low_sentiment { sound:"priest_ptah_g06.wav", text: "#ptah_low_sentiment" }
		ptah_much_unemployments { sound:"priest_ptah_g07.wav", text: "#ptah_much_unemployments" }
		ptah_need_entertainment { sound:"priest_ptah_g08.wav", text: "#ptah_need_entertainment" }
		ptah_city_is_good { sound:"priest_ptah_09.wav", text: "#ptah_city_is_good" }
		ptah_city_is_amazing { sound:"priest_ptah_g10.wav", text: "#ptah_city_is_amazing" }

		seth_god_love_festival { sound:"priest_seth_e01.wav", text: "#seth_god_love_festival" }
		seth_city_low_mood { sound:"priest_seth_e02.wav", text: "#seth_city_low_mood" }
		seth_low_entertainment { sound:"priest_seth_g08.wav", text: "#seth_low_entertainment" }
		seth_disease_in_city { sound:"priest_seth_g01.wav", text: "#seth_disease_in_city" }
		seth_city_low_health { sound:"priest_seth_g01.wav", text: "#seth_city_low_health" }
		seth_no_food_in_city { sound:"priest_seth_g02.wav", text: "#seth_no_food_in_city" }
		seth_city_not_safety { sound:"priest_seth_g03.wav", text: "#seth_city_not_safety" }
		seth_need_workers { sound:"priest_seth_g04.wav", text: "#seth_need_workers" }
		seth_gods_are_angry { sound:"priest_seth_g05.wav", text: "#seth_gods_are_angry" }
		seth_low_sentiment { sound:"priest_seth_g06.wav", text: "#seth_low_sentiment" }
		seth_much_unemployments { sound:"priest_seth_g07.wav", text: "#seth_much_unemployments" }
		seth_need_entertainment { sound:"priest_seth_g08.wav", text: "#seth_need_entertainment" }
		seth_city_is_good { sound:"priest_seth_g09.wav", text: "#seth_city_is_good" }
		seth_city_is_amazing { sound:"priest_seth_g10.wav", text: "#seth_city_is_amazing" }

		bast_god_love_festival { sound:"priest_bast_e01.wav", text: "#bast_god_love_festival" }
		bast_city_low_mood { sound:"priest_bast_e02.wav", text: "#bast_city_low_mood" }
		bast_low_entertainment { sound:"priest_bast_e03.wav", text: "#bast_low_entertainment" }
		bast_disease_in_city { sound:"priest_bast_e04.wav", text: "#bast_disease_in_city" }
		bast_city_low_health { sound:"priest_bast_g01.wav", text: "#bast_city_low_health" }
		bast_no_food_in_city { sound:"priest_bast_g02.wav", text: "#bast_no_food_in_city" }
		bast_city_not_safety { sound:"priest_bast_g03.wav", text: "#bast_city_not_safety" }
		bast_need_workers { sound:"priest_bast_g04.wav", text: "#bast_need_workers" }
		bast_gods_are_angry { sound:"priest_bast_g05.wav", text: "#bast_gods_are_angry" }
		bast_low_sentiment { sound:"priest_bast_g06.wav", text: "#bast_low_sentiment" }
		bast_much_unemployments { sound:"priest_bast_g07.wav", text: "#bast_much_unemployments" }
		bast_need_entertainment { sound:"priest_bast_g08.wav", text: "#bast_need_entertainment" }
		bast_city_is_good { sound:"priest_bast_g09.wav", text: "#bast_city_is_good" }
		bast_city_is_amazing { sound:"priest_bast_g10.wav", text: "#bast_city_is_amazing" }
	}

	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_priest
	record_path : true
}

function figure_priest_god_prefix(home_type) {
	switch (home_type) {
	case BUILDING_TEMPLE_OSIRIS:
	case BUILDING_TEMPLE_COMPLEX_OSIRIS:
		return { prefix: "osiris", god: GOD_OSIRIS }
	case BUILDING_TEMPLE_RA:
	case BUILDING_TEMPLE_COMPLEX_RA:
		return { prefix: "ra", god: GOD_RA }
	case BUILDING_TEMPLE_PTAH:
	case BUILDING_TEMPLE_COMPLEX_PTAH:
		return { prefix: "ptah", god: GOD_PTAH }
	case BUILDING_TEMPLE_SETH:
	case BUILDING_TEMPLE_COMPLEX_SETH:
		return { prefix: "seth", god: GOD_SETH }
	case BUILDING_TEMPLE_BAST:
	case BUILDING_TEMPLE_COMPLEX_BAST:
		return { prefix: "bast", god: GOD_BAST }
	}
	return null
}

function figure_priest_gods_are_angry() {
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

function figure_priest_city_phrase_key(prefix, god_type) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	function k(suffix) {
		return prefix + "_" + suffix
	}

	if (city.num_forts < 1) {
		keys.push(k("city_not_safety"))
	}

	if (city.gods.at(god_type).months_since_festival < 6) {
		keys.push(k("god_love_festival"))
	}

	if (city.labor.workers_needed >= 10) {
		keys.push(k("need_workers"))
	}

	if (sentiment < 30) {
		keys.push(k("city_low_mood"))
	}

	if (city.houses.missing.more_entertainment > 1) {
		keys.push(k("low_entertainment"))
	} else {
		keys.push(k("need_entertainment"))
	}

	// C++ scanned disease_days; health rating is the JS proxy.
	if (city.health_rating < 40) {
		keys.push(k("disease_in_city"))
	}

	if (city.health_rating < 30) {
		keys.push(k("city_low_health"))
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push(k("no_food_in_city"))
	}

	if (figure_priest_gods_are_angry()) {
		keys.push(k("gods_are_angry"))
	}

	if (city.kingdome.rating < 30) {
		keys.push(k("low_sentiment"))
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push(k("much_unemployments"))
	}

	if (sentiment > 90) {
		keys.push(k("city_is_amazing"))
	} else if (sentiment > 40) {
		keys.push(k("city_is_good"))
	}

	if (keys.length == 0) {
		return k("city_is_good")
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_priest, setup_phrase)]
function figure_priest_setup_phrase(ev) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	var home = f.home
	if (!home || !home.valid) {
		return
	}

	var info = figure_priest_god_prefix(home.type)
	if (!info) {
		return
	}

	figure_apply_phrase(f, figure_priest_city_phrase_key(info.prefix, info.god))
}
