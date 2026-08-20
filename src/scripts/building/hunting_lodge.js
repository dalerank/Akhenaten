log_info("akhenaten: loading building_hunting_lodge")

building_hunting_lodge {
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

    meta { text_id:154, help_link:"message_building_hunting_lodge" }
    info_sound : "Wavs/lo_hunt.wav"
    building_size : 2
    min_houses_coverage : 100
    cost [ 5, 10, 25, 40, 60 ]
    desirability { value[-4], step[1], step_size[2], range[4] }
    laborers [6],
    fire_risk [5]
    damage_risk [2]
    spawn_delay_100_percent [1]
    spawn_delay_75_percent [5]
    spawn_delay_50_percent [10]
    spawn_delay_25_percent [15]
    spawn_delay_default [30]
    // Original lodge fields a hunting party of three.
    max_hunters [3]
    // FIGURE_NONE = resolve from climate prey / legacy (see hunting_lodge_default_hunter_type).
    hunter_type : FIGURE_NONE
    flags {
        is_food: true
        keeps_visitor_paths: true
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
