log_info("akhenaten: building_courthouse started")

[es=(building_courthouse, spawn_figure)]
function building_courthouse_spawn_figure(ev) {
    var building = city.get_building(ev.bid)
    building.common_spawn_roamer(FIGURE_MAGISTRATE, building_courthouse.min_houses_coverage, ACTION_125_ROAMER_ROAMING)
}

[es=(building_courthouse, update_graphic)]
function building_courthouse_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
