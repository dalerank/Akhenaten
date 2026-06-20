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

[es=(building_well, on_place_checks)]
function building_well_on_place_checks(ev) {
    var b = city.get_building(ev.bid)
    var has_groundwater = terrain.is(b.tile, TERRAIN_GROUNDWATER)
    city.warnings.show_if_not(has_groundwater, "#needs_groundwater")
}

[es=(building_well, update_graphic)]
function building_well_update_graphic(ev) {
    var well = city.get_well(ev.bid)
    if (!well) {
        return
    }
    if (!well.can_play_animation) {
        well.set_animation("none")
        return
    }

    var animkey = well.is_fancy ? "base_work" : "fancy_work"
    well.set_animation(animkey)
}

[es=(building_well, update_month)]
function building_well_update_month(ev) {
    var well = city.get_well(ev.bid)
    var params = well.params
    var avg_desirability = __desirability_get_avg(well.tile, params.desirability_range_check)
    var is_fancy = avg_desirability > params.desirability_fancy
    well.set_fancy(is_fancy)
    var animkey = is_fancy ? "fancy" : "base"
    __map_image_set(well.tile, well.first_img(animkey))
}

[es=(building_well, ghost_preview)]
function building_well_ghost_preview(ev) {
    if (game_features.gameui_show_water_structure_range) {
        var overlay = get_image({ pack: PACK_TERRAIN, id: 21 }).tid
        var pixels = __camera_tile_range_pixels(city.planner.end, 1, 2)
        for (var i = 0; i < pixels.length; i++) {
            city.planner.draw_overlay_tile(pixels[i], overlay, COLOR_MASK_BLUE, 1.0)
        }
    }

    var params = city.get_building_params_by_type(BUILDING_WELL)
    city.planner.draw_ghost(ev.pixel, params.preview_image)
}
