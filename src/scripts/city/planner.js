log_info("akhenaten: city_planner.js started")

city_planner = extend(__city_planner, {
    // => build_type
    // => in_progress
    // => construction_update_items

    preview_path: null

    update: __city_planner_update
    can_be_placed: __city_planner_can_be_placed
    construction_start: __city_planner_construction_start
    construction_update: __city_planner_construction_update
    construction_finalize: __city_planner_construction_finalize
    construction_cancel: __city_planner_construction_cancel
    last_created_building_id: __city_planner_last_created_building_id
    validate_last_created: __city_planner_validate_last_created

    draw_blocked: __city_planner_draw_blocked
    draw_ghost: __city_planner_draw_ghost
    draw_flat_tiles: __city_planner_draw_flat_tiles
    draw_isometric_ghost: __city_planner_draw_isometric_ghost
    tile_to_pixel: __lookup_tile_to_pixel

    rotate_by_hotkey: function() {
        var cfg = get_building_config_by_id(city_planner.build_type)
        var allow_rotate = cfg && cfg.flags && cfg.flags.allow_rotate

        if (!game_features.gameui_rotate_manually && !allow_rotate) {
            return
        }

        var rotation = city_planner.global_rotation + 1
        if (rotation > 3) {
            rotation = 0
        }

        city_planner.global_rotation = rotation
        city_planner.road_orientation = city_planner.road_orientation == 1 ? 2 : 1
    }
})

[es=event_rotate_building]
function city_planner_on_rotate_building(ev) {
    city_planner.rotate_by_hotkey()
    __city_planner_update_orientations()
}

[es=event_change_building_variant]
function city_planner_on_change_building_variant(ev) {
    __city_planner_next_building_variant()
}

city.planner = city_planner
