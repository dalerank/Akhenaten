log_info("akhenaten: overlay criminal started")

[es=(overlay_criminal, get_tooltip_for_building)]
function criminal_building_tooltip(ev) {
    var house = city.get_house(ev.bid)
    if (!house || house.population <= 0) {
        city.overlay_tooltip = "#criminal_level_worst"
        return
    }

    var criminal = house.criminal_active
    if (criminal >= 80) {
        city.overlay_tooltip = "#criminal_level_worst"
    } else if (criminal >= 60) {
        city.overlay_tooltip = "#criminal_level_high"
    } else if (criminal >= 40) {
        city.overlay_tooltip = "#criminal_level_secure"
    } else if (criminal >= 30) {
        city.overlay_tooltip = "#crime_level_high"
    } else if (criminal >= 20) {
        city.overlay_tooltip = "#crime_level_normal"
    } else {
        city.overlay_tooltip = "#crime_level_low"
    }
}
