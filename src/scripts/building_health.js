log_info("akhenaten: building health started")


[es=(building_apothecary, spawn_figure)]
function building_apothecary_spawn_figure(ev) {
    log_info("building_apothecary_spawn_figure: " + building_apothecary.min_houses_coverage)
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_HERBALIST, building_apothecary.min_houses_coverage, ACTION_4_HERBALIST_ROAMING)
}

[es=(building_apothecary, update_graphic)]
function building_apothecary_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.can_play_animation() ? "work" : "none"
    building.set_animation(animkey)
}