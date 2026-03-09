log_info("akhenaten: building health started")

building_apothecary = {
animations : {
    preview : { pos : [0, 0], pack:PACK_GENERAL, id:68 },
    base : { pos : [0, 0], pack:PACK_GENERAL, id:68 },
    work : { pos : [25, -35], pack:PACK_GENERAL, id:68, offset:1, max_frames:11 },
}
labor_category : LABOR_CATEGORY_WATER_HEALTH
overlay : OVERLAY_APOTHECARY
sound_channel : SOUND_CHANNEL_CITY_APOTHECARY
min_houses_coverage : 50
max_serve_clients : 100
meta : { help_id:63, text_id:81 }
building_size : 1
cost : [ 6, 10, 15, 30, 50 ]
desirability : { value:[1], step:[1], step_size:[-1], range: [1] }
laborers:[5], fire_risk:[4], damage_risk: [2]
}


[es=(building_apothecary, spawn_figure)]
function building_apothecary_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_HERBALIST, building_apothecary.min_houses_coverage, ACTION_4_HERBALIST_ROAMING)
}

[es=(building_apothecary, update_graphic)]
function building_apothecary_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.can_play_animation() ? "work" : "none"
    building.set_animation(animkey)
}