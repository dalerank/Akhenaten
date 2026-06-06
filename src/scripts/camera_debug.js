log_info("akhenaten: camera_debug")

var TILE_WIDTH_PIXELS = 60
var TILE_HEIGHT_PIXELS = 30

[es=event_draw_debug_properties]
function camera_debug_draw_properties(ev) {
    if (!imgui.tree_node_ex("Camera")) {
        return
    }

    imgui.begin_table("Camera", 2, imgui.table_flags_debug_props())

    imgui.property_input("view min", __city_view_scroll_min())
    imgui.property_input("view max", __city_view_scroll_max())
    imgui.property_input("camera", __city_view, "camera_position")

    imgui.property_input("scroll min", __city_view, "scroll_min_screentile")
    imgui.property_input("tile", __city_view, "camera_mappoint")
    imgui.property_input("rela_max", __city_view, "camera_max_tile")

    imgui.property_input("pixel min", Vec2i(0, 0))
    imgui.property_input("pixel", __city_view, "camera_pixel_offset_internal")
    imgui.property_input("pixek max", __city_view, "camera_max_pixel_offset")

    imgui.property_input("v.tiles", __city_view, "viewport_tiles")
    imgui.property_input("v.pixels", __city_view, "size_pixels")

    imgui.property_input("zoom", __zoom_percentage())
    imgui.property_input("scale", __zoom_scale())
    imgui.property_input("target", __zoom_target())
    imgui.property_input("delta", __zoom_delta())

    var pixel = Vec2i(__mouse.x, __mouse.y)
    imgui.property_input("mouse", pixel)
    imgui.property_input("viewp", __city_view, "mouse_viewport")
    imgui.property_input("coord", __city_view, "mouse_camera_coord")

    var screen = __pixel_to_screentile(pixel)
    imgui.property_input("tile", screen)

    imgui.property_input("offset", __city_view, "mouse_camera_offset")

    var point = __screen_to_tile(screen)
    imgui.property_input("point", point)
    imgui.property_input("grid_offset", __city_view, "mouse_grid_offset")

    imgui.property_input("terrain type", __city_view, "mouse_terrain_type")
    imgui.property_input("pixel", __city_view, "mouse_tile_pixel")

    imgui.end_table()
    imgui.tree_pop()
}
