log_info("akhenaten: loading building_police_station")

[es=(building_police_station, update_graphic)]
function building_police_station_on_update_graphic(ev) {
    var building = city.get_building(ev.bid)
    var animkey = building.play_animation ? "work" : "none"
    building.set_animation(animkey)
}
