log_info("akhenaten: clouds_debug")

[es=event_draw_debug_properties]
function clouds_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Clouds")) {
        return
    }

    if (imgui.button("Reset Clouds")) {
        __clouds_reset()
    }

    imgui.begin_table("Clouds", 2, imgui.table_flags_debug_props())
    imgui.property_input("num_cloud_ellipses", __clouds_config, "num_cloud_ellipses")
    imgui.property_input("cloud_alpha_increase", __clouds_config, "cloud_alpha_increase")
    imgui.property_input("cloud_columns", __clouds_config, "cloud_columns")
    imgui.property_input("cloud_rows", __clouds_config, "cloud_rows")
    imgui.property_input("cloud_width", __clouds_config, "cloud_width")
    imgui.property_input("cloud_height", __clouds_config, "cloud_height")
    imgui.property_input("cloud_size_ratio", __clouds_config, "cloud_size_ratio")
    imgui.property_input("cloud_scale", __clouds_config, "cloud_scale")
    imgui.property_input("cloud_min_creation_timeout", __clouds_config, "cloud_min_creation_timeout")
    imgui.property_input("cloud_max_creation_timeout", __clouds_config, "cloud_max_creation_timeout")
    imgui.property_input("pause_min_frames", __clouds_config, "pause_min_frames")
    imgui.end_table()

    var count = __clouds_count()
    for (var i = 0; i < count; i++) {
        if (!imgui.tree_node_ex2("Cloud" + i, "Cloud " + i)) {
            continue
        }

        imgui.begin_table("Cloud" + i, 2, imgui.table_flags_debug_props())
        imgui.property_input("status", __clouds_cloud_status(i))
        imgui.property_input("speedx", __clouds_cloud_speedx(i))
        imgui.property_input("speedy", __clouds_cloud_speedy(i))
        imgui.property_input("pos", __clouds_cloud_pos(i))
        imgui.property_input("render_pos", __clouds_cloud_render_pos(i))
        imgui.end_table()

        imgui.tree_pop()
    }

    imgui.tree_pop()
}
