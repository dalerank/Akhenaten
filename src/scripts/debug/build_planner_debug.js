log_info("akhenaten: build_planner_debug")

[es=event_draw_debug_properties]
function build_planner_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Build planer")) {
        return
    }

    imgui.begin_table("Build planer", 2, imgui.table_flags_debug_props())

    imgui.property_input("type", __city_planner, "build_type")
    imgui.property_input("in progress", __city_planner, "in_progress")
    imgui.property_input("draw as con.", __city_planner, "draw_as_constructing")
    imgui.property_input("orientation abs", __city_planner, "absolute_orientation")
    imgui.property_input("orientation rel", __city_planner, "relative_orientation")
    imgui.property_input("variant:", __city_planner, "building_variant")
    imgui.property_input("start", Vec2i(__city_planner.start.x, __city_planner.start.y))
    imgui.property_input("end", __city_planner.end, "x")
    imgui.property_input("", __city_planner.end, "y")

    var screen_start = __camera_tile_to_screen(Vec2i(__city_planner.start.x, __city_planner.start.y))
    var screen_end = __camera_tile_to_screen(Vec2i(__city_planner.end.x, __city_planner.end.y))
    imgui.property_input("screen start", screen_start)
    imgui.property_input("screen ebd", screen_end)

    imgui.property_input("cost:", __city_planner, "total_cost")

    imgui.end_table()
    imgui.tree_pop()
}
