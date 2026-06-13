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

[es=(overlay_crime, draw_custom_top)]
function crime_draw_custom_top(ev) {
    if (game.debug_render_mode != e_debug_render_overlay_add) {
        return
    }

    var text
    var building = city.get_building(ev.bid)
    if (building && building.valid) {
        text = "" + building.crime_influence_value
    } else {
        text = "" + __crime_at_tile(ev.tile.x, ev.tile.y)
    }

    var pos = { x: ev.mpos.x + 15, y: ev.mpos.y + 15 }
    ui.text_abs_colored(text, pos, FONT_SMALL_OUTLINED, COLOR_LIGHT_BLUE)
}
