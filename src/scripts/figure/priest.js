log_info("akhenaten: figure priest started")

figure_priest {
	animations {
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_PRIEST }
	}

	god_configs : [ "figure_priest_osiris", "figure_priest_ra", "figure_priest_ptah", "figure_priest_seth", "figure_priest_bast" ]
	category: figure_category_citizen
	max_damage : 10
	terrain_usage : TERRAIN_USAGE_ROADS
	max_roam_length : 384
	permission : epermission_priest
	record_path : true
}

figure_priest_osiris {
	god : GOD_OSIRIS
	temples : [ BUILDING_TEMPLE_OSIRIS, BUILDING_TEMPLE_COMPLEX_OSIRIS ]
	overlay : OVERLAY_RELIGION_OSIRIS

	animations {
		walk { pack:PACK_SPR_MAIN, id:197, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:198, loop:false }
	}

	sounds {
		// Cleopatra has no e03/e04 for osiris/ra/ptah/seth — reuse nearest g-lines.
		god_love_festival { sound:"priest_osiris_e01.wav", text: "#osiris_god_love_festival" }
		city_low_mood { sound:"priest_osiris_e02.wav", text: "#osiris_city_low_mood" }
		low_entertainment { sound:"priest_osiris_g08.wav", text: "#osiris_low_entertainment" }
		disease_in_city { sound:"priest_osiris_g01.wav", text: "#osiris_disease_in_city" }
		city_low_health { sound:"priest_osiris_g01.wav", text: "#osiris_city_low_health" }
		no_food_in_city { sound:"priest_osiris_g02.wav", text: "#osiris_no_food_in_city" }
		city_not_safety { sound:"priest_osiris_g03.wav", text: "#osiris_city_not_safety" }
		need_workers { sound:"priest_osiris_g04.wav", text: "#osiris_need_workers" }
		gods_are_angry { sound:"priest_osiris_g05.wav", text: "#osiris_gods_are_angry" }
		low_sentiment { sound:"priest_osiris_g06.wav", text: "#osiris_low_sentiment" }
		much_unemployments { sound:"priest_osiris_g07.wav", text: "#osiris_much_unemployments" }
		need_entertainment { sound:"priest_osiris_g08.wav", text: "#osiris_need_entertainment" }
		city_is_good { sound:"priest_osiris_g09.wav", text: "#osiris_city_is_good" }
		city_is_amazing { sound:"priest_osiris_g10.wav", text: "#osiris_city_is_amazing" }
	}
}

figure_priest_ra {
	god : GOD_RA
	temples : [ BUILDING_TEMPLE_RA, BUILDING_TEMPLE_COMPLEX_RA ]
	overlay : OVERLAY_RELIGION_RA

	animations {
		walk { pack:PACK_SPR_MAIN, id:210, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:211, loop:false }
	}

	sounds {
		god_love_festival { sound:"priest_ra_e01.wav", text: "#ra_god_love_festival" }
		city_low_mood { sound:"priest_ra_e02.wav", text: "#ra_city_low_mood" }
		low_entertainment { sound:"priest_ra_g08.wav", text: "#ra_low_entertainment" }
		disease_in_city { sound:"priest_ra_g01.wav", text: "#ra_disease_in_city" }
		city_low_health { sound:"priest_ra_g01.wav", text: "#ra_city_low_health" }
		no_food_in_city { sound:"priest_ra_g02.wav", text: "#ra_no_food_in_city" }
		city_not_safety { sound:"priest_ra_g03.wav", text: "#ra_city_not_safety" }
		need_workers { sound:"priest_ra_g04.wav", text: "#ra_need_workers" }
		gods_are_angry { sound:"priest_ra_g05.wav", text: "#ra_gods_are_angry" }
		low_sentiment { sound:"priest_ra_g06.wav", text: "#ra_low_sentiment" }
		much_unemployments { sound:"priest_ra_g07.wav", text: "#ra_much_unemployments" }
		need_entertainment { sound:"priest_ra_g08.wav", text: "#ra_need_entertainment" }
		city_is_good { sound:"priest_ra_g09.wav", text: "#ra_city_is_good" }
		city_is_amazing { sound:"priest_ra_g10.wav", text: "#ra_city_is_amazing" }
	}
}

figure_priest_ptah {
	god : GOD_PTAH
	temples : [ BUILDING_TEMPLE_PTAH, BUILDING_TEMPLE_COMPLEX_PTAH ]
	overlay : OVERLAY_RELIGION_PTAH

	animations {
		walk { pack:PACK_SPR_MAIN, id:187, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:188, loop:false }
	}

	sounds {
		god_love_festival { sound:"priest_ptah_e01.wav", text: "#ptah_god_love_festival" }
		city_low_mood { sound:"priest_ptah_e02.wav", text: "#ptah_city_low_mood" }
		low_entertainment { sound:"priest_ptah_g08.wav", text: "#ptah_low_entertainment" }
		disease_in_city { sound:"priest_ptah_g01.wav", text: "#ptah_disease_in_city" }
		city_low_health { sound:"priest_ptah_g01.wav", text: "#ptah_city_low_health" }
		no_food_in_city { sound:"priest_ptah_g02.wav", text: "#ptah_no_food_in_city" }
		city_not_safety { sound:"priest_ptah_g03.wav", text: "#ptah_city_not_safety" }
		need_workers { sound:"priest_ptah_g04.wav", text: "#ptah_need_workers" }
		gods_are_angry { sound:"priest_ptah_g05.wav", text: "#ptah_gods_are_angry" }
		low_sentiment { sound:"priest_ptah_g06.wav", text: "#ptah_low_sentiment" }
		much_unemployments { sound:"priest_ptah_g07.wav", text: "#ptah_much_unemployments" }
		need_entertainment { sound:"priest_ptah_g08.wav", text: "#ptah_need_entertainment" }
		city_is_good { sound:"priest_ptah_09.wav", text: "#ptah_city_is_good" }
		city_is_amazing { sound:"priest_ptah_g10.wav", text: "#ptah_city_is_amazing" }
	}
}

figure_priest_seth {
	god : GOD_SETH
	temples : [ BUILDING_TEMPLE_SETH, BUILDING_TEMPLE_COMPLEX_SETH ]
	overlay : OVERLAY_RELIGION_SETH

	animations {
		walk { pack:PACK_SPR_MAIN, id:193, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:194, loop:false }
	}

	sounds {
		god_love_festival { sound:"priest_seth_e01.wav", text: "#seth_god_love_festival" }
		city_low_mood { sound:"priest_seth_e02.wav", text: "#seth_city_low_mood" }
		low_entertainment { sound:"priest_seth_g08.wav", text: "#seth_low_entertainment" }
		disease_in_city { sound:"priest_seth_g01.wav", text: "#seth_disease_in_city" }
		city_low_health { sound:"priest_seth_g01.wav", text: "#seth_city_low_health" }
		no_food_in_city { sound:"priest_seth_g02.wav", text: "#seth_no_food_in_city" }
		city_not_safety { sound:"priest_seth_g03.wav", text: "#seth_city_not_safety" }
		need_workers { sound:"priest_seth_g04.wav", text: "#seth_need_workers" }
		gods_are_angry { sound:"priest_seth_g05.wav", text: "#seth_gods_are_angry" }
		low_sentiment { sound:"priest_seth_g06.wav", text: "#seth_low_sentiment" }
		much_unemployments { sound:"priest_seth_g07.wav", text: "#seth_much_unemployments" }
		need_entertainment { sound:"priest_seth_g08.wav", text: "#seth_need_entertainment" }
		city_is_good { sound:"priest_seth_g09.wav", text: "#seth_city_is_good" }
		city_is_amazing { sound:"priest_seth_g10.wav", text: "#seth_city_is_amazing" }
	}
}

figure_priest_bast {
	god : GOD_BAST
	temples : [ BUILDING_TEMPLE_BAST, BUILDING_TEMPLE_COMPLEX_BAST ]
	overlay : OVERLAY_RELIGION_BAST
	// Isis altar on the Bast complex: the priestess clears infected houses and plagued walkers.
	altar_cures_plague : true

	animations {
		walk { pack:PACK_SPR_MAIN, id:208, max_frames:12 }
		death { pack:PACK_SPR_MAIN, id:209, loop:false }
	}

	sounds {
		god_love_festival { sound:"priest_bast_e01.wav", text: "#bast_god_love_festival" }
		city_low_mood { sound:"priest_bast_e02.wav", text: "#bast_city_low_mood" }
		low_entertainment { sound:"priest_bast_e03.wav", text: "#bast_low_entertainment" }
		disease_in_city { sound:"priest_bast_e04.wav", text: "#bast_disease_in_city" }
		city_low_health { sound:"priest_bast_g01.wav", text: "#bast_city_low_health" }
		no_food_in_city { sound:"priest_bast_g02.wav", text: "#bast_no_food_in_city" }
		city_not_safety { sound:"priest_bast_g03.wav", text: "#bast_city_not_safety" }
		need_workers { sound:"priest_bast_g04.wav", text: "#bast_need_workers" }
		gods_are_angry { sound:"priest_bast_g05.wav", text: "#bast_gods_are_angry" }
		low_sentiment { sound:"priest_bast_g06.wav", text: "#bast_low_sentiment" }
		much_unemployments { sound:"priest_bast_g07.wav", text: "#bast_much_unemployments" }
		need_entertainment { sound:"priest_bast_g08.wav", text: "#bast_need_entertainment" }
		city_is_good { sound:"priest_bast_g09.wav", text: "#bast_city_is_good" }
		city_is_amazing { sound:"priest_bast_g10.wav", text: "#bast_city_is_amazing" }
	}
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

function figure_priest_city_phrase_key(god_type) {
	var keys = []
	var mood_cause = city.sentiment.low_mood_cause
	var sentiment = city.sentiment.value

	if (city.num_forts < 1) {
		keys.push("city_not_safety")
	}

	if (city.gods.at(god_type).months_since_festival < 6) {
		keys.push("god_love_festival")
	}

	if (city.labor.workers_needed >= 10) {
		keys.push("need_workers")
	}

	if (sentiment < 30) {
		keys.push("city_low_mood")
	}

	if (city.houses.missing.more_entertainment > 1) {
		keys.push("low_entertainment")
	} else {
		keys.push("need_entertainment")
	}

	// C++ scanned disease_days; health rating is the JS proxy.
	if (city.health_rating < 40) {
		keys.push("disease_in_city")
	}

	if (city.health_rating < 30) {
		keys.push("city_low_health")
	}

	if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
		keys.push("no_food_in_city")
	}

	if (figure_priest_gods_are_angry()) {
		keys.push("gods_are_angry")
	}

	if (city.kingdome.rating < 30) {
		keys.push("low_sentiment")
	}

	if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
		keys.push("much_unemployments")
	}

	if (sentiment > 90) {
		keys.push("city_is_amazing")
	} else if (sentiment > 40) {
		keys.push("city_is_good")
	}

	if (keys.length == 0) {
		return "city_is_good"
	}

	return keys[Math.floor(Math.random() * keys.length)]
}

function figure_priest_setup_phrase(ev, god_type) {
	var f = city.get_figure(ev.fid)
	if (!f || !f.valid) {
		return
	}

	figure_apply_phrase(f, figure_priest_city_phrase_key(god_type))
}

[es=(figure_priest_osiris, setup_phrase)]
function figure_priest_osiris_setup_phrase(ev) { figure_priest_setup_phrase(ev, GOD_OSIRIS) }

[es=(figure_priest_ra, setup_phrase)]
function figure_priest_ra_setup_phrase(ev) { figure_priest_setup_phrase(ev, GOD_RA) }

[es=(figure_priest_ptah, setup_phrase)]
function figure_priest_ptah_setup_phrase(ev) { figure_priest_setup_phrase(ev, GOD_PTAH) }

[es=(figure_priest_seth, setup_phrase)]
function figure_priest_seth_setup_phrase(ev) { figure_priest_setup_phrase(ev, GOD_SETH) }

[es=(figure_priest_bast, setup_phrase)]
function figure_priest_bast_setup_phrase(ev) { figure_priest_setup_phrase(ev, GOD_BAST) }
