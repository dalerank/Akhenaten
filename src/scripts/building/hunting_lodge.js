log_info("akhenaten: loading building_hunting_lodge")

[es=building]
building_hunting_lodge {
    type: BUILDING_HUNTING_LODGE
    animations {
        preview { pack:PACK_GENERAL, id:176}
        base { pack:PACK_GENERAL, id:176}
        work { pos:[20, -15], pack:PACK_GENERAL, id:176, offset:1, max_frames:18, duration:3 }
        minimap {pack:PACK_GENERAL, id:149, offset:160}
    }
    overlay_anims {
        gamemeat {
            pos:[61, 14]
            pack:PACK_GENERAL
            id:205
            max_frames:5
            stack: false
            resource: RESOURCE_GAMEMEAT
            default_active: true
        }
    }

    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
    output {
        resource : RESOURCE_GAMEMEAT
    }

    meta { help_link:"message_building_hunting_lodge" }
    info_title_id : "#hunting_lodge"
    info_sound : "Wavs/lo_hunt.wav"
    sound_channel : SOUND_CHANNEL_CITY_HUNTER_LOUDGE
    building_size : 2
    min_houses_coverage : 100
    cost [ 5, 10, 25, 40, 60 ]
    desirability { value[-4], step[1], step_size[2], range[4] }
    laborers [6],
    fire_risk [5]
    damage_risk [2]
    spawn_delay [
        { pct: 100, delay: 1 }
        { pct: 75, delay: 5 }
        { pct: 50, delay: 10 }
        { pct: 25, delay: 15 }
        { pct: 1, delay: 30 }
    ]
    // Original lodge fields a hunting party of three.
    max_hunters [3]
    hunter_by_climate [FIGURE_ANTELOPE_HUNTER, FIGURE_BIRDS_HUNTER, FIGURE_OSTRICH_HUNTER]
    hunter_by_climate_legacy [FIGURE_ANTELOPE_HUNTER, FIGURE_OSTRICH_HUNTER, FIGURE_OSTRICH_HUNTER]
    flags {
        is_food: true
        keeps_visitor_paths: true
    }
}

function hunting_lodge_spawn_timer(b) {
    var pct = b.worker_percentage
    var table = building_hunting_lodge.spawn_delay
    for (var i = 0; i < table.length; i++) {
        if (pct >= table[i].pct) {
            return table[i].delay
        }
    }
    return -1
}

function hunting_lodge_resolve_hunter_type() {
    var p = building_hunting_lodge
    var table = scenario.has_prey_points ? p.hunter_by_climate : p.hunter_by_climate_legacy
    var hunter = table[scenario.climate]
    return hunter != null ? hunter : FIGURE_OSTRICH_HUNTER
}

function hunting_lodge_can_spawn_hunter(b) {
    if (b.stored_resource(RESOURCE_GAMEMEAT) >= 500) {
        return false
    }

    var max_hunters = dcy_get(building_hunting_lodge.max_hunters)
    var hunters = b.get_figures_number(FIGURE_OSTRICH_HUNTER) + b.get_figures_number(FIGURE_ANTELOPE_HUNTER) + b.get_figures_number(FIGURE_BIRDS_HUNTER)
    return hunters < max_hunters
}

[es=(building_hunting_lodge, spawn_figure)]
function building_hunting_lodge_spawn_figure(ev) {
    if (city.resources.gamemeat.mothballed) {
        return
    }

    var b = city.get_building(ev.bid)
    b.check_labor_problem()
    if (!b.has_road_access) {
        return
    }

    if (b.num_workers < b.max_workers) {
        b.common_spawn_labor_seeker(building_hunting_lodge.min_houses_coverage)
    }

    var spawn_delay = hunting_lodge_spawn_timer(b)
    if (spawn_delay == -1) {
        return
    }

    b.figure_spawn_delay += 1
    if (b.figure_spawn_delay < spawn_delay) {
        return
    }

    if (hunting_lodge_can_spawn_hunter(b)) {
        b.figure_spawn_delay = 0
        b.create_figure_generic(hunting_lodge_resolve_hunter_type(), ACTION_8_RECALCULATE, BUILDING_SLOT_HUNTER)
    }

    if (b.common_spawn_goods_output_cartpusher()) {
        b.figure_spawn_delay = 0
    }
}

[es=(building_hunting_lodge, update_animation)]
function building_hunting_lodge_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }

    if (b.worker_percentage <= 50) {
        b.play_animation = false
        return
    }

    var hunters = b.get_figures_number(FIGURE_OSTRICH_HUNTER)
        + b.get_figures_number(FIGURE_ANTELOPE_HUNTER)
        + b.get_figures_number(FIGURE_BIRDS_HUNTER)
    b.play_animation = b.stored_resource(RESOURCE_GAMEMEAT) > 0 || hunters > 0
}

[es=(building_hunting_lodge, update_graphic)]
function building_hunting_lodge_on_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}

[es=(building_hunting_lodge, draw_usable_paths)]
function building_hunting_lodge_draw_usable_paths(ev) {
    city.get_building(ev.bid).draw_usable_paths()
}
