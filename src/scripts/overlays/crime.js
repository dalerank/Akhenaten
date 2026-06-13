log_info("akhenaten: overlay crime started")

[es=(overlay_crime, get_tooltip)]
function crime_tile_tooltip(ev) {
    var crime = __crime_at_tile(ev.tile.x, ev.tile.y)
    if (crime < 0) {
        city.overlay_tooltip = "#crime_level_low"
    } else if (crime == 0) {
        city.overlay_tooltip = "#crime_level_normal"
    } else {
        city.overlay_tooltip = "#crime_level_high"
    }
}
