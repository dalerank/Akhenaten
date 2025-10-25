#include "city/city.h"

#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include "view/lookup.h"
#include "game/game.h"

ANK_REGISTER_PROPS_ITERATOR(config_show_camera_properties);
void config_show_camera_properties(bool header) {
    if (header) {
        return;
    }

    bool common_open = ImGui::TreeNodeEx("Camera", ImGuiTreeNodeFlags_None, "Camera");
    if (common_open) {
        ImGui::BeginTable("Camera", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

        painter ctx = game.painter();

        tile2i camera_tile = city_view_get_camera_mappoint();
        vec2i camera_pixels = camera_get_pixel_offset_internal(ctx);

        auto mm_view = g_city_view.get_scrollable_pixel_limits();

        vec2i real_max = city_view_get_camera_max_tile();

        vec2i max_pixel_offset = city_view_get_camera_max_pixel_offset();

        game_debug_show_property("view min", mm_view.min);
        game_debug_show_property("view max", mm_view.max);
        game_debug_show_property("camera", g_city_view.camera.position);

        game_debug_show_property("scroll min", vec2i{ SCROLL_MIN_SCREENTILE_X, SCROLL_MIN_SCREENTILE_Y }, true);
        game_debug_show_property("tile", camera_tile);
        game_debug_show_property("rela_max", real_max);

        game_debug_show_property("pixel min", vec2i{ 0, 0 }, true);
        game_debug_show_property("pixel", camera_pixels);
        game_debug_show_property("pixek max", max_pixel_offset);

        game_debug_show_property("v.tiles", vec2i{ g_city_view.viewport.size_pixels.x / 60, g_city_view.viewport.size_pixels.y / 30 }, true);
        game_debug_show_property("v.pixels", g_city_view.viewport.size_pixels);

        game_debug_show_property("zoom", g_zoom.get_percentage(), true);
        game_debug_show_property("scale", g_zoom.get_scale(), true);

        game_debug_show_property("target", g_zoom.ftarget(), true);
        game_debug_show_property("delta", g_zoom.fdelta(), true);

        vec2i pixel = { mouse_get()->x, mouse_get()->y };
        game_debug_show_property("mouse", pixel, true);

        vec2i viewp = pixel_to_viewport(pixel);
        game_debug_show_property("viewp", viewp, true);

        vec2i coord = pixel_to_camera_coord(pixel, false);
        game_debug_show_property("coord", coord, true);

        screen_tile screen = pixel_to_screentile(pixel);
        game_debug_show_property("tile", screen);

        vec2i offset = { coord.x % TILE_WIDTH_PIXELS, coord.y % TILE_HEIGHT_PIXELS };
        game_debug_show_property("offset", offset, true);
        
        tile2i point = screen_to_tile(screen);
        game_debug_show_property("point", point);
        game_debug_show_property("grid_offset", point.grid_offset(), true);

        game_debug_show_property("terrain type", get_terrain_type("type: ", point), true);
        pixel = lookup_tile_to_pixel(point);
        game_debug_show_property("pixel", pixel, true);
       
        ImGui::EndTable();

        ImGui::TreePop();
    }
}