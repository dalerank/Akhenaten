log_info("akhenaten: figure ostrich_hunter started")

figure_ostrich_hunter {
	animations {
		_pack { pack:PACK_SPR_MAIN }
		walk { id:45, max_frames:12 }
		death { id:46, max_frames:8, loop:false }
		hunt { id:47, max_frames:12, loop:false }
		fight { id:48, max_frames:12 }
		//work_in_field : {  id:49, max_frames:12, loop:false }
		pack { id:50, max_frames:12, loop:false }
		unpack { id:50, max_frames:12, loop:false, start_frame:11, reverse:true }
		move_pack { id:51, max_frames:12 }
		big_image { pack:PACK_UNLOADED, id:25, offset:FIGURE_OSTRICH_HUNTER }
	}

	sounds {
		hunter_investigate : {sound:"hunter_ostrich_investigate.wav", text: "#hunter_ostrich_investigate"}
		hunter_chase : {sound:"hunter_ostrich_chase.wav", text: "#hunter_ostrich_chase"}
		hunter_hunting : {sound:"hunt_ostrich_e01.wav", text: "#hunter_ostrich_hunting"}
		hunter_back : {sound:"hunt_ostrich_e02.wav", text: "#hunter_ostrich_back"}
		hunter_reroute_packed : {sound:"hunter_ostrich_reroute_packed.wav", text: "#hunter_ostrich_reroute_packed"}
		hunter_look_packed : {sound:"hunter_ostrich_look_packed.wav", text: "#hunter_ostrich_look_packed"}
		hunter_unloading : {sound:"hunter_ostrich_unloading.wav", text: "#hunter_ostrich_unloading"}
		hunter_disease_risk : {sound:"hunter_ostrich_disease_risk.wav", text: "#hunter_ostrich_disease_risk"}
		hunter_no_food_in_city : {sound:"hunter_ostrich_no_food_in_city.wav", text: "#hunter_ostrich_no_food_in_city"}
		hunter_city_have_no_army : {sound:"hunter_ostrich_city_have_no_army.wav", text: "#hunter_ostrich_city_have_no_army"}
		hunter_need_workers : {sound:"hunter_ostrich_need_workers.wav", text: "#hunter_ostrich_need_workers"}
		hunter_gods_are_angry : {sound:"hunter_ostrich_gods_are_angry.wav", text: "#hunter_ostrich_gods_are_angry"}
		hunter_city_is_bad : {sound:"hunter_ostrich_city_is_bad.wav", text: "#hunter_ostrich_city_is_bad"}
		hunter_much_unemployment : {sound:"hunter_ostrich_much_unemployment.wav", text: "#hunter_ostrich_much_unemployment"}
		hunter_low_entertainment : {sound:"hunter_ostrich_low_entertainment.wav", text: "#hunter_ostrich_low_entertainment"}
		hunter_city_is_good : {sound:"hunter_ostrich_city_is_good.wav", text: "#hunter_ostrich_city_is_good"}
		hunter_city_is_amazing : {sound:"hunter_ostrich_city_is_amazing.wav", text: "#hunter_ostrich_city_is_amazing"}
	}

	category: figure_category_armed
	max_damage: 30
	attack_value: 4
	missile_attack_value: 4
	animal_attack_value: 100
	// OG shoot tick/timeout/dist; terrain stays ANIMAL (remake — roads strand off-map hunts).
	shoot_tick: 9
	shoot_timeout: 300
	attack_distance: 3
	terrain_usage : TERRAIN_USAGE_ANIMAL
	max_hunting_distance : 15
	prey_type : FIGURE_OSTRICH
	missile_type : FIGURE_HUNTER_SPEAR
	record_path : true
}

function figure_ostrich_hunter_gods_are_angry() {
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

function figure_ostrich_hunter_city_phrase_key() {
    var keys = []
    var mood_cause = city.sentiment.low_mood_cause

    if (city.health_rating < 30) {
        keys.push("hunter_disease_risk")
    }

    if (mood_cause == 1) { // LOW_MOOD_NO_FOOD
        keys.push("hunter_no_food_in_city")
    }

    if (city.num_forts < 1) {
        keys.push("hunter_city_have_no_army")
    }

    if (city.labor.workers_needed >= 10) {
        keys.push("hunter_need_workers")
    }

    if (figure_ostrich_hunter_gods_are_angry()) {
        keys.push("hunter_gods_are_angry")
    }

    if (city.kingdome.rating < 30) {
        keys.push("hunter_city_is_bad")
    }

    if (mood_cause == 2) { // LOW_MOOD_NO_JOBS
        keys.push("hunter_much_unemployment")
    }

    if (__city_festival.months_since_festival > 6) {
        keys.push("hunter_low_entertainment")
    }

    var sentiment = city.sentiment.value
    if (sentiment > 50) {
        keys.push("hunter_city_is_good")
    }

    if (sentiment > 90) {
        keys.push("hunter_city_is_amazing")
    }

    if (keys.length == 0) {
        return "hunter_back"
    }

    return keys[Math.floor(Math.random() * keys.length)]
}

[es=(figure_ostrich_hunter, setup_phrase)]
function figure_ostrich_hunter_setup_phrase(ev) {
    var f = city.get_figure(ev.fid)
    if (!f || !f.valid) {
        return
    }

    var state = f.action_state
    switch (state) {
    case ACTION_16_OSTRICH_HUNTER_INVESTIGATE:
        figure_apply_phrase(f, "hunter_investigate")
        return
    case ACTION_9_OSTRICH_HUNTER_CHASE_PREY:
        figure_apply_phrase(f, "hunter_chase")
        return
    case ACTION_15_OSTRICH_HUNTER_HUNT:
        figure_apply_phrase(f, "hunter_hunting")
        return
    case ACTION_12_OSTRICH_HUNTER_MOVE_PACKED:
        figure_apply_phrase(f, "hunter_back")
        return
    case ACTION_12_OSTRICH_HUNTER_MOVE_RANDOM_PACKED:
        figure_apply_phrase(f, "hunter_reroute_packed")
        return
    case ACTION_12_OSTRICH_HUNTER_LOOK_RANDOM_PACKED:
        figure_apply_phrase(f, "hunter_look_packed")
        return
    case ACTION_14_OSTRICH_HUNTER_UNLOADING:
        figure_apply_phrase(f, "hunter_unloading")
        return
    }

    figure_apply_phrase(f, figure_ostrich_hunter_city_phrase_key())
}
