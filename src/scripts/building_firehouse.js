log_info("akhenaten: loading building_firehouse")

building_firehouse {
    animations {
        _pack { pack:PACK_GENERAL }
        preview { id:78 }
        base { id:78 }
        work { pos [25, -30], id:78, offset:1, max_frames:11 }
    }

    labor_category : LABOR_CATEGORY_INFRASTRUCTURE
    min_houses_coverage : 50
    meta { help_id: 355, text_id: 164 }
    info_sound : "Wavs/prefecture.wav"
    building_size : 1
    cost [ 6, 12, 25, 40, 60 ]
    desirability { value[-2], step[1], step_size[1], range[2] }
    laborers [6]
    fire_risk [0]
    damage_risk [2]
    flags {
        is_infrastructure: true
    }
}

[es=(building_firehouse, update_graphic)]
function building_firehouse_on_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.can_play_animation() ? "work" : "none"
    building.set_animation(animkey)
}

