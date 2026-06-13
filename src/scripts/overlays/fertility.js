log_info("akhenaten: overlay fertility started")

[es=(overlay_fertility, get_tooltip_for_building)]
function fertility_building_tooltip(ev) {
    var building = city.get_building(ev.bid)
    if (!building || !building.valid) {
        return
    }

    if (!__building_is_farm(ev.bid)) {
        city.overlay_tooltip = "#crime_level_low"
        return
    }

    var fertility = __fertility_for_farm_at_tile(building.tile.x, building.tile.y)
    if (fertility > 80) {
        city.overlay_tooltip = "#criminal_level_worst"
    } else if (fertility > 60) {
        city.overlay_tooltip = "#criminal_level_high"
    } else if (fertility > 40) {
        city.overlay_tooltip = "#criminal_level_secure"
    } else if (fertility > 20) {
        city.overlay_tooltip = "#crime_level_high"
    } else if (fertility > 10) {
        city.overlay_tooltip = "#crime_level_normal"
    } else {
        city.overlay_tooltip = "#crime_level_low"
    }
}
