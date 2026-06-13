log_info("akhenaten: overlay desirability started")

[es=(overlay_desirability, get_tooltip)]
function desirability_tile_tooltip(ev) {
    var desirability = __desirability_at_tile(ev.tile.x, ev.tile.y)
    if (desirability < 0) {
        city.overlay_tooltip = "#desirability_level_low"
    } else if (desirability == 0) {
        city.overlay_tooltip = "#desirability_level_normal"
    } else {
        city.overlay_tooltip = "#desirability_level_high"
    }
}
