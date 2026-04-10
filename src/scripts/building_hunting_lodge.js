log_info("akhenaten: loading building_hunting_lodge")

building_hunting_lodge {
    animations {
        preview { pack:PACK_GENERAL, id:176}
        base { pack:PACK_GENERAL, id:176}
        work { pos:[20, -15], pack:PACK_GENERAL, id:176, offset:1, max_frames:18, duration:3 }
        gamemeat { pos:[61, 14], pack:PACK_GENERAL, id:205 }
        minimap {pack:PACK_GENERAL, id:149, offset:160}
    }

    labor_category : LABOR_CATEGORY_FOOD_PRODUCTION
    output {
        resource : RESOURCE_GAMEMEAT
    }

    meta { help_id:90, text_id:154 }
    info_sound : "Wavs/lo_hunt.wav"
    building_size : 2
    min_houses_coverage : 100
    cost [ 5, 10, 25, 40, 60 ]
    desirability { value[-4], step[1], step_size[2], range[4] }
    laborers [6],
    fire_risk [5]
    damage_risk [2]
    spawn_delay_100_percent : 1
    spawn_delay_75_percent : 5
    spawn_delay_50_percent : 10
    spawn_delay_25_percent : 15
    spawn_delay_default : 30
    flags {
        is_food: true
    }
}

[es=(building_hunting_lodge, update_graphic)]
function building_hunting_lodge_on_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.can_play_animation ? "work" : "none"
    building.set_animation(animkey)
}
