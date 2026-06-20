log_info("akhenaten: building_well started")

function BuildingWell(building_id) {
    this.id = building_id
}

BuildingWell.prototype = Object.create(Building.prototype)
BuildingWell.prototype.constructor = BuildingWell

BuildingWell.prototype.necessity_status = function(radius) {
    return __building_well_necessity_status(this.id, radius)
}

city.get_well = function(building_id) {
    if (!__building_is_well(building_id)) {
        return null
    }
    return new BuildingWell(building_id)
}

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
