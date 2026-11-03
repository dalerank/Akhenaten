log_info("akhenaten: building_apothecary started")

[es=building]
building_apothecary {
    type: BUILDING_APOTHECARY
    animations {
        preview { pos [0, 0], pack:PACK_GENERAL, id:68 }
        base { pos [0, 0], pack:PACK_GENERAL, id:68 }
        work { pos [25, -35], pack:PACK_GENERAL, id:68, offset:1, max_frames:11 }
    }
    labor_category : LABOR_CATEGORY_WATER_HEALTH
    overlay : OVERLAY_APOTHECARY
    sound_channel : SOUND_CHANNEL_CITY_APOTHECARY
    min_houses_coverage : 50
    max_serve_clients : 100
    spawn_delays : [3, 7, 15, 29, 44]
    meta { text_id:81, help_link:"message_building_apothecary" }
    info_sound : "Wavs/apothecary.wav"
    building_size : 1
    cost [ 6, 24, 30, 36, 45 ]
    desirability { value[1], step[1], step_size[-1], range[1] }
    laborers[5]
    fire_risk [ 4, 17, 20, 24, 30 ]
    damage_risk [0]
    flags {
        draw_normal_anim: true
    }
}

[es=(building_apothecary, spawn_figure)]
function building_apothecary_spawn_figure(ev) {
    city.get_building(ev.bid).spawn_service_walker(building_apothecary, FIGURE_HERBALIST, ACTION_4_HERBALIST_ROAMING)
}

[es=(building_apothecary, update_graphic)]
function building_apothecary_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
