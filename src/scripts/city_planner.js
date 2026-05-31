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
    tile_to_pixel: __lookup_tile_to_pixel
})

city.planner = city_planner
