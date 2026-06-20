log_info("akhenaten: building_well started")

[es=(building_well, ghost_preview)]
function building_well_ghost_preview(ev) {
    if (game_features.gameui_show_water_structure_range) {
        var overlay = get_image({ pack: PACK_TERRAIN, id: 21 }).tid
        var pixels = __camera_tile_range_pixels(city.planner.end, 1, 2)
        for (var i = 0; i < pixels.length; i++) {
            city.planner.draw_overlay_tile(pixels[i], overlay, COLOR_MASK_BLUE)
        }
    }

    var params = city.get_building_params_by_type(BUILDING_WELL)
    city.planner.draw_ghost(ev.pixel, params.preview_image)
}
