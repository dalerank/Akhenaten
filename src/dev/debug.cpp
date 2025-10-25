#include "debug.h"

#include <cmath>

#include "core/string.h"
#include "graphics/text.h"

#include "graphics/graphics.h"
#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

#include "building/monuments.h"
#include "building/building_entertainment.h"
#include "building/building_house.h"
#include "city/city.h"
#include "graphics/clouds.h"
#include "graphics/view/lookup.h"
#include "grid/canals.h"
#include "grid/building.h"
#include "grid/floodplain.h"
#include "grid/image.h"
#include "grid/moisture.h"
#include "grid/property.h"
#include "grid/road_network.h"
#include "grid/routing/routing.h"
#include "grid/sprite.h"
#include "grid/terrain.h"
#include "grid/vegetation.h"
#include "grid/gardens.h"
#include "grid/random.h"
#include "grid/soldier_strength.h"
#include "widget/city/building_ghost.h"
#include "game/game.h"

#include "building/construction/build_planner.h"
#include "building/building_statue.h"
#include "building/building_farm.h"
#include "building/building_temple_complex.h"
#include "city/coverage.h"
#include "city/city_floods.h"
#include "game/game_events.h"
#include "sound/sound_city.h"
#include "sound/sound.h"
#include "core/random.h"
#include "figure/route.h"
#include "game/tutorial.h"
#include "grid/figure.h"
#include "platform/renderer.h"
#include "widget/debug_console.h"
#include "overlays/city_overlay.h"
#include "scenario/scenario_invasion.h"

#include "js/js_game.h"

int debug_range_3 = 0;
int debug_range_4 = 0;
int g_debug_figure_id = 0;

game_debug_t g_debug;
bool g_debug_show_opts[e_debug_opt_size] = { 0 };

const token_holder<e_debug_render, e_debug_render_none, e_debug_render_size> ANK_CONFIG_ENUM(e_debug_render_tokens);
const token_holder<e_debug_option, e_debug_show_floods, e_debug_opt_size> ANK_CONFIG_ENUM(e_debug_option_tokens);

declare_console_var_int(debugrender, 0);
declare_console_var_int(debugbuildingid, 0);

static const uint8_t* font_test_str = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/,._äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";
static const uint8_t* font_test_str_ascii = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/,._";
static const uint8_t* font_test_str_extended = (uint8_t*)(char*)"äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";

static void debug_font_line(int* y, e_font font) {
    int line_height = font_definition_for(font)->line_height;
    if (line_height < 11)
        line_height = 11;
    line_height += 5;
    text_draw(font_test_str_ascii, 5, *y, font, COLOR_MASK_NONE);
    *y += line_height;
    //    text_draw(font_test_str_extended, 5, *y, font, COLOR_MASK_NONE); *y += line_height;
}

void debug_font_test() {
    ImageDraw::fill_rect(vec2i{0, 0}, vec2i{1600, 300}, COLOR_FONT_LIGHT_GRAY);
    //    auto str = string_from_ascii(font_test_str, true);
    int y = 10;
    debug_font_line(&y, FONT_SMALL_PLAIN);
    debug_font_line(&y, FONT_NORMAL_BLACK_ON_LIGHT);
    debug_font_line(&y, FONT_NORMAL_WHITE_ON_DARK);
    debug_font_line(&y, FONT_NORMAL_YELLOW);
    debug_font_line(&y, FONT_NORMAL_BLUE);
    debug_font_line(&y, FONT_LARGE_BLACK_ON_LIGHT);
    debug_font_line(&y, FONT_LARGE_BLACK_ON_DARK);
    debug_font_line(&y, FONT_SMALL_OUTLINED);
    debug_font_line(&y, FONT_NORMAL_BLACK_ON_DARK);
    debug_font_line(&y, FONT_SMALL_SHADED);
}

void debug_text(painter &ctx, pstr str, int x, int y, int indent, pcstr text, int value, color color, e_font font) {
    text_draw(ctx, (const uint8_t *)string_from_ascii(text), x, y, font, color);
    text_draw(ctx, (uint8_t*)bstring32(value).c_str(), x + indent, y, font, color);
}

void debug_text_a(painter &ctx, pstr str, int x, int y, int indent, pcstr text, color color, e_font font) {
    text_draw(ctx, (const uint8_t *)string_from_ascii(text), x, y, font, color);
}

void debug_text_float(int x, int y, int indent, pcstr text, float value, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    bstring64 buffer;
    buffer.printf("0.2f", value);
    text_draw(buffer.data(), x + indent, y, FONT_SMALL_OUTLINED, color);
}

void debug_text_dual_left(int x, int y, int indent, int indent2, pcstr text, int value1, int value2, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    text_draw_left(bstring32(value1).c_str(), x + indent, y, FONT_SMALL_OUTLINED, color);
    text_draw_left(bstring32(value2).c_str(), x + indent + indent2, y, FONT_SMALL_OUTLINED, color);
}

void debug_draw_line_with_contour(int x_start, int x_end, int y_start, int y_end, color col) {
    graphics_renderer()->draw_line(vec2i{x_start - 1, x_end - 1}, vec2i{x_start, y_end}, COLOR_BLACK);
    graphics_renderer()->draw_line(vec2i{x_start + 1, x_end + 1}, vec2i{x_start, y_end}, COLOR_BLACK);
    graphics_renderer()->draw_line(vec2i{x_start, x_end}, vec2i{y_start - 1, y_end - 1}, COLOR_BLACK);
    graphics_renderer()->draw_line(vec2i{x_start, x_end}, vec2i{y_start + 1, y_end + 1}, COLOR_BLACK);
    graphics_renderer()->draw_line(vec2i{x_start, x_end}, vec2i{y_start, y_end}, col);
}

void debug_draw_rect_with_contour(int x, int y, int w, int h, color col) {
    graphics_renderer()->draw_rect(vec2i{x - 1, y - 1}, vec2i{w, h}, COLOR_BLACK);
    graphics_renderer()->draw_rect(vec2i{x + 1, y + 1}, vec2i{w, h}, COLOR_BLACK);
    graphics_renderer()->draw_rect(vec2i{x, y}, vec2i{w - 1, h - 1}, COLOR_BLACK);
    graphics_renderer()->draw_rect(vec2i{x, y}, vec2i{w + 1, h + 1}, COLOR_BLACK);
    graphics_renderer()->draw_rect(vec2i{x, y}, vec2i{w, h}, col);
}

void debug_draw_crosshair(int x, int y) {
    graphics_renderer()->draw_line(vec2i{x, x + 10}, vec2i{y, y}, COLOR_GREEN);
    graphics_renderer()->draw_line(vec2i{x, x}, vec2i{y, y + 10}, COLOR_RED);
}

void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask) {
    int x2 = x - img->animation.sprite_offset.x;
    int y2 = y - img->animation.sprite_offset.y;
    graphics_renderer()->draw_rect(vec2i(x2 * scale, y2 * scale), vec2i(img->width * scale, img->height * scale), color_mask);
    debug_draw_crosshair((x2 + img->animation.sprite_offset.x) * scale, (y2 + img->animation.sprite_offset.y) * scale);
}

void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x, int tile_size_y) {
    float scale = g_zoom.get_scale();

    int left_x = x;
    int left_y = y + HALF_TILE_HEIGHT_PIXELS;

    int top_x = left_x + (tile_size_y * HALF_TILE_WIDTH_PIXELS);
    int top_y = left_y - (tile_size_y * HALF_TILE_HEIGHT_PIXELS);

    int right_x = top_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int right_y = top_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    int bottom_x = left_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int bottom_y = left_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    if (rect != COLOR_NULL) {
        graphics_renderer()->draw_rect(vec2i(x * scale, y * scale), vec2i(TILE_WIDTH_PIXELS * scale, TILE_HEIGHT_PIXELS * scale), rect);
    }

    if (bb != COLOR_NULL) {
        graphics_renderer()->draw_line(vec2i(left_x * scale, top_x * scale), vec2i(left_y * scale, top_y * scale), bb);
        graphics_renderer()->draw_line(vec2i(top_x * scale, right_x * scale), vec2i(top_y * scale, right_y * scale), bb);
        graphics_renderer()->draw_line(vec2i(right_x * scale, bottom_x * scale), vec2i(right_y * scale, bottom_y * scale), bb);
        graphics_renderer()->draw_line(vec2i(bottom_x * scale, left_x * scale), vec2i(bottom_y * scale, left_y * scale), bb);
    }
}
void debug_draw_tile_top_bb(int x, int y, int height, color color, int size) {
    float scale = g_zoom.get_scale();

    int left_x = x;
    int left_bottom = y + HALF_TILE_HEIGHT_PIXELS;

    int right_x = left_x + (size * HALF_TILE_WIDTH_PIXELS);
    int right_bottom = left_bottom - (size * HALF_TILE_HEIGHT_PIXELS);

    int left_top = left_bottom - height;
    int right_top = right_bottom - height;

    graphics_renderer()->draw_line(vec2i(left_x * scale, right_x * scale), vec2i(left_bottom * scale, right_bottom * scale), color);
    graphics_renderer()->draw_line(vec2i(left_x * scale, right_x * scale), vec2i(left_top * scale, right_top * scale), color);

    graphics_renderer()->draw_line(vec2i(left_x * scale, left_x * scale), vec2i(left_bottom * scale, left_top * scale), color);
    graphics_renderer()->draw_line(vec2i(right_x * scale, right_x * scale), vec2i(right_bottom * scale, right_top * scale), color);
}

static int north_tile_grid_offset(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int size = map_property_multi_tile_size(grid_offset);
    for (int i = 0; i < size && map_property_multi_tile_x(grid_offset); i++) {
        grid_offset += GRID_OFFSET(-1, 0);
    }

    for (int i = 0; i < size && map_property_multi_tile_y(grid_offset); i++) {
        grid_offset += GRID_OFFSET(0, -1);
    }

    return grid_offset;
}

bool get_debug_draw_option(int opt) {
    return g_debug_show_opts[opt];
}

void set_debug_draw_option(int opt, bool e) {
    g_debug_show_opts[opt] = e;
}

void draw_debug_tile(vec2i pixel, tile2i point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;

    int DB2 = abs(debug_render_mode()) % e_debug_render_size;

    if (DB2 == 0)
        return;

    // globals
    int d = 0;
    char str[64];
    int b_id = map_building_at(grid_offset);
    building* b = building_get(b_id);

    int x0 = x + 8;
    int x1 = x0 + 30;
    int x2 = x1 + 30;
    x += 15;

    switch (DB2) {
    default:
        break;

    case e_debug_render_building: // BUILDING IDS
        if (b_id && b->tile.grid_offset() == grid_offset) {
            build_planner::draw_building_ghost(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, {x - 15, y}, COLOR_MASK_GREEN_30);
        }

        if (b_id && map_property_is_draw_tile(grid_offset)) { // b->tile.grid_offset() == grid_offset
            bool red = !map_terrain_is(grid_offset, TERRAIN_BUILDING);
            debug_text(ctx, str, x0, y + 0, 0, "", b_id, red ? COLOR_LIGHT_RED : COLOR_WHITE);
            debug_text(ctx, str, x0, y + 10, 0, "", b->type, red ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
            if (!b->is_main()) {
                text_draw(ctx, (uint8_t *)string_from_ascii("sub"), x0, y - 10, FONT_SMALL_OUTLINED, COLOR_RED);
            }
        }
        break;

    case e_debug_render_tilesize: // DRAW-TILES AND SIZES
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            if (map_property_is_draw_tile(grid_offset)) {
                debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_GREEN);
                debug_text(ctx, str, x1, y + 10, 0, "", b->size, COLOR_WHITE);
            } else {
                debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_RED);
            }
        } else if (!map_property_is_draw_tile(grid_offset)) {
            debug_text(ctx, str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_BLUE);
        }
        break;

    case e_debug_render_roads:                                                   // ROADS
        if (b_id && map_property_is_draw_tile(grid_offset)) { //&& b->tile.grid_offset() == grid_offset
            debug_text(ctx, str, x0, y + 5, 0, "", b->road_access.x(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
            debug_text(ctx, str, x0, y + 15, 0, "", b->road_access.y(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
            if (b->has_road_access) {
                auto tile_coords = lookup_tile_to_pixel(b->road_access);
                build_planner::draw_building_ghost(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, tile_coords, COLOR_MASK_GREEN);
            }
        }
        if (map_terrain_is(grid_offset, TERRAIN_ROAD) || map_terrain_is(grid_offset, TERRAIN_FERRY_ROUTE)) {
            d = map_road_network_get(grid_offset);
            debug_text(ctx, str, x, y + 10, 10, "R", d, COLOR_WHITE);
        } else if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
            d = map_road_network_get(grid_offset);
            debug_text(ctx, str, x, y + 10, 10, "R", d, COLOR_LIGHT_BLUE);
        }
        break;

    case e_debug_render_routing_dist: // ROUTING DISTANCE
        d = map_routing_distance(grid_offset);
        debug_text(ctx, str, x, y + 10, 0, "", d, d > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;

    case e_debug_render_routing_grid: // CITIZEN ROUTING GRID
        d = map_citizen_grid(grid_offset);
        debug_text(ctx, str, x, y + 10, 0, "", d, d >= 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;

    case e_debug_render_routing_noncitizen: // CITIZEN ROUTING GRID
        d = map_noncitizen_grid(grid_offset);
        debug_text(ctx, str, x, y + 10, 0, "", d, d >= 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;

    case e_debug_render_routing_amphibia: // CITIZEN ROUTING GRID
        d = map_amphibia_grid(grid_offset);
        debug_text(ctx, str, x, y + 10, 0, "", d, d >= 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;

    case e_debug_render_routing_water: // CITIZEN ROUTING GRID
        d = map_water_grid(grid_offset);
        debug_text(ctx, str, x, y + 10, 0, "", d, d >= 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;

    case e_debug_render_moisture: // MOISTURE
        d = map_moisture_get(grid_offset);
        if (d & MOISTURE_GRASS)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_WHITE);
        else if (d & MOISTURE_TRANSITION)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
        else if (d & MOISTURE_SHORE_TALLGRASS)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_GREEN);
        break;

    case e_debug_render_grass_level: // PROPER GRASS LEVEL
        d = map_grasslevel_get(grid_offset);
        if (d)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_GREEN);
        break;

    case e_debug_render_canals: // PROPER CANAL LEVEL
        d = map_canal_at(grid_offset);
        if (d)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_GREEN);
        break;

    case e_debug_render_gardens:
        d = map_garden_at(grid_offset);
        if (d) {
            int decay = map_tiles_garden_decay_get(tile2i(grid_offset));
            int garden = map_tiles_garden_get(tile2i(grid_offset), false);
            debug_text(ctx, str, x0, y + 5, 0, "", garden, COLOR_GREEN);
            debug_text(ctx, str, x0, y + 15, 0, "", decay, COLOR_LIGHT_RED);
        }
        break;

    case e_debug_render_grass_soil_depletion: // FERTILITY & SOIL DEPLETION
        d = map_get_fertility(grid_offset, FERT_WITH_MALUS);
        if (d) {
            int n = map_get_fertility(grid_offset, FERT_NO_MALUS);
            if (d == n || map_terrain_is(grid_offset, TERRAIN_MEADOW))
                debug_text(ctx, str, x, y + 5, 0, "", d, COLOR_LIGHT_GREEN);
            else {
                debug_text(ctx, str, x, y + 5, 0, "", d, COLOR_LIGHT_BLUE);
                d = map_get_fertility(grid_offset, FERT_ONLY_MALUS);
                debug_text(ctx, str, x, y + 15, 0, "", d, COLOR_LIGHT_RED);
            }
        }
        break;

    case e_debug_render_grass_flood_order: // FLOODPLAIN SHORE ORDER
        d = map_get_floodplain_row(grid_offset);
        if (d > -1)
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;

    case e_debug_render_grass_flood_flags: // FLOODPLAIN TERRAIN FLAGS
        d = map_terrain_is(grid_offset, TERRAIN_BUILDING);
        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD))
                    debug_text(ctx, str, x, y + 10, 0, "", d, 0xff777777);
                else if (map_building_at(grid_offset) > 0)
                    debug_text(ctx, str, x, y + 10, 0, "", d, 0xff550000);
            } else {
                if (map_terrain_is(grid_offset, TERRAIN_ROAD))
                    debug_text(ctx, str, x, y + 10, 0, "", d, 0xffffffff);
                else if (map_building_at(grid_offset) > 0)
                    debug_text(ctx, str, x, y + 10, 0, "", d, 0xffaa0000);
            }
        }

        if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
            int a = map_canal_at(grid_offset);
            if (map_terrain_is(grid_offset, TERRAIN_WATER))
                debug_text(ctx, str, x, y + 10, 0, "", a, 0xff557777);
            else
                debug_text(ctx, str, x, y + 10, 0, "", a, 0xff5577ff);
        } else if (map_terrain_is(grid_offset, TERRAIN_IRRIGATION_RANGE)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER))
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xff007777);
            else
                debug_text(ctx, str, x, y + 10, 0, "", d, 0xff00ffff);
        }
        break;

    case e_debug_render_labor: // LABOR
        if (b_id && map_property_is_draw_tile(grid_offset)
            && (b->labor_category != LABOR_CATEGORY_NONE || building_is_floodplain_farm(*b))) {

            if (b->labor_category != category_for_building(b)) {
                debug_text(ctx, str, x0, y + 10, 10, "!!", b->labor_category, COLOR_RED); // incorrect category??
            } else {
                debug_text(ctx, str, x0, y + 10, 0, "", b->labor_category, COLOR_WHITE);
            }
            debug_text(ctx, str, x1, y + 10, 0, "", b->houses_covered, COLOR_LIGHT_RED);
            debug_text(ctx, str, x0, y + 20, 0, "", b->num_workers, COLOR_LIGHT_BLUE);
            debug_text(ctx, str, x1 - 10, y + 20, 4, ":", b->worker_percentage(), COLOR_LIGHT_BLUE);
            //
            if (building_is_farm(b->type)) {
                const auto farm = b->dcast_farm();
                debug_text(ctx, str,x1 + 40,y + 20,40,"fert.", map_get_fertility_for_farm(b->tile.grid_offset()),COLOR_FONT_ORANGE_LIGHT);
                debug_text(ctx, str, x0, y + 30, 0, "", farm->progress(), COLOR_GREEN);
                debug_text(ctx, str, x1 + 10, y + 30, 4, ":", farm->progress() / 20, COLOR_GREEN);
                debug_text(ctx, str, x1 + 40, y + 30, 40, "exp.", farm->expected_produce(), COLOR_GREEN);
                if (building_is_floodplain_farm(*b)) {
                    auto &d = b->dcast_farm()->runtime_data();
                    debug_text(ctx, str, x0, y + 40, 0, "", d.labor_state, COLOR_WHITE);
                    debug_text(ctx, str, x1, y + 40, 0, "", d.labor_days_left, COLOR_WHITE);
                }
            }

            auto ent = b->dcast_entertainment();
            if (ent) {
                auto &d = ent->runtime_data();
                debug_text(ctx, str, x0, y + 30, 0, "", d.juggler_visited, COLOR_GREEN);
                debug_text(ctx, str, x1, y + 30, 0, "", d.musician_visited, COLOR_GREEN);
                debug_text(ctx, str, x0, y + 40, 0, "", d.dancer_visited, COLOR_GREEN);
            }
        }
        break;

    case e_debug_render_sprite_frames: // SPRITE FRAMES
        if (grid_offset == b->tile.grid_offset()) {
            build_planner::draw_building_ghost(ctx, image_id_from_group(GROUP_SUNKEN_TILE) + 3, {x - 15, y}, COLOR_MASK_GREEN);
        }
        if (grid_offset == north_tile_grid_offset(b->tile.x(), b->tile.y())) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, x - 15, y, COLOR_MASK_RED);
        }
        d = map_sprite_animation_at(grid_offset);
        if (d) {
            text_draw(bstring32(d).c_str(), x, y + 10, FONT_SMALL_OUTLINED, COLOR_WHITE);
        }

        // STATUES & MONUMENTS

        if (b_id && map_property_is_draw_tile(grid_offset) && (b->labor_category != LABOR_CATEGORY_NONE)) {
            switch (b->type) {
            case BUILDING_SMALL_STATUE:
            case BUILDING_MEDIUM_STATUE:
            case BUILDING_LARGE_STATUE:
                {
                    auto statue = b->dcast_statue();
                    debug_text(ctx, str, x1, y + 10, 0, "", statue->runtime_data().variant, COLOR_WHITE);
                }
                break;
                //
            case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            case BUILDING_TEMPLE_COMPLEX_RA:
            case BUILDING_TEMPLE_COMPLEX_PTAH:
            case BUILDING_TEMPLE_COMPLEX_SETH:
            case BUILDING_TEMPLE_COMPLEX_BAST:
                {
                    auto complex = b->dcast_temple_complex();
                    auto &d = complex->runtime_data();
                    debug_text(ctx, str, x1, y + 10, 0, "", d.variant, COLOR_WHITE);
                    debug_text(ctx, str, x1, y + 20, 0, "", d.temple_complex_upgrades, COLOR_LIGHT_BLUE);
                }
                break;
            }
        }
        break;

    case e_debug_render_terrain_bits: // TERRAIN BIT FIELD
        debug_text(ctx, str, x, y + 10, 0, "", map_terrain_get(grid_offset), COLOR_LIGHT_BLUE);
        break;

    case e_debug_render_tile_pos:
        ImageDraw::img_generic(ctx, image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel.x, pixel.y, 0x80000000);
        if (!(point.x() % 5) && !(point.y() % 5)) {
            snprintf((char*)str, 30, "(%d,%d)", point.x(), point.y());
            debug_text_a(ctx, str, x, y + 10, 0, str, COLOR_WHITE, FONT_SMALL_PLAIN);

            vec2i voff = point.to_view();
            snprintf((char *)str, 48, "(%d,%d) (%d,%d)", pixel.x, pixel.y, voff.x, voff.y);
            debug_text_a(ctx, str, x, y + 20, 0, str, COLOR_BLUE, FONT_SMALL_PLAIN);
        }
        break;

    case e_debug_render_tile_toph: {
        int image_id = map_image_at(grid_offset);
        const image_t *img = image_get(image_id);
        snprintf((char*)str, 30, "%d", img->isometric_top_height());
        debug_text_a(ctx, str, x, y + 10, 0, str, COLOR_WHITE, FONT_SMALL_PLAIN);
        }
        break;

    case e_debug_render_floodplain_shore:
        d = map_get_floodplain_edge(point);
        if (d) {
            text_draw(bstring32(d).c_str(), x, y + 15, FONT_SMALL_OUTLINED, COLOR_WHITE);
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel.x, pixel.y, 0x80000000);
        }
        break;

    case e_debug_render_image: // IMAGE FIELD
        debug_text(ctx, str, x, y + 10, 0, "", map_image_at(grid_offset), COLOR_LIGHT_RED);
        break;

    case e_debug_render_image_alt: // IMAGE ALT FIELD
        { 
            int image_alt_value = map_image_alt_at(grid_offset);
            int image_alt_id = (image_alt_value & 0x00ffffff);
            uint8_t image_alt_alpha = (image_alt_value & 0xff000000) >> 24;
            if (image_alt_id > 0 && image_alt_alpha > 0) {
                snprintf((char *)str, 30, "%d(%d)", image_alt_id, image_alt_alpha);
                debug_text_a(ctx, str, x, y + 10, 0, (pcstr)str, COLOR_LIGHT_RED);
            }
        }
        break;

    case e_debug_render_vegetation_growth:
        if (map_terrain_is(grid_offset, TERRAIN_MARSHLAND | TERRAIN_TREE)) {
            d = map_get_vegetation_growth(grid_offset);
            debug_text(ctx, str, x, y + 10, 0, "", d, (d < 200) ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
        }
        break;

    case e_debug_render_damage:
        if (b_id && b) {
            snprintf((char *)str, 30, "f:%d/d:%d", b->fire_risk, b->damage_risk);
            text_draw(ctx, (uint8_t*)str, x, y + 10, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
        }
        break;

    case e_debug_render_overall_entertainment:
        {
            auto house = building_get(b_id)->dcast_house();
            if (house) {
                debug_text(ctx, str, x, y + 10, 0, "", house->runtime_data().entertainment, COLOR_LIGHT_BLUE);
            }
        }
        break;

    case e_debug_render_desirability:
        if (g_desirability.get(grid_offset) != 0) {
            debug_text(ctx, str, x, y + 10, 0, "", g_desirability.get(grid_offset), COLOR_LIGHT_RED);
        }
        break;

    case e_debug_render_marshland:
        d = map_terrain_is(grid_offset, TERRAIN_MARSHLAND);
        if (d != 0) {
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        }
        break;

    case e_debug_render_terrain_type: // TERRAIN TYPE
        d = map_terrain_get(grid_offset);
        text_draw(ctx, bstring32().printf("%x", d), x, y + 10, FONT_SMALL_PLAIN, COLOR_LIGHT_BLUE, 0.5f);
        break;

    case e_debug_render_soil: // UNKNOWN SOIL GRID
        d = map_get_UNK04(grid_offset);
        if (d != 0) {
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        }
        break;

    case e_debug_render_unk_19: // UNKNOWN 32BIT GRID
        d = map_get_UNK03(grid_offset);
        if (d != 0) {
            debug_text(ctx, str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        }
        break;

    case e_debug_render_monuments:
        if (auto monument = b->dcast_monument(); !!monument) {            
            d = map_monuments_get_progress(tile2i(grid_offset));
            b->is_valid()
                ? snprintf((char *)str, 30, "%d[%d]", monument->runtime_data().phase, d)
                : snprintf((char *)str, 30, "%d", d);
            debug_text_a(ctx, str, x, y + 10, 0, (pcstr)str, COLOR_RED, FONT_SMALL_PLAIN);
        }
        break;

    case e_debug_render_height:
        d = map_building_height_at(grid_offset);
        snprintf((char *)str, 30, "%d", d);
        debug_text_a(ctx, str, x, y + 10, 0, (pcstr)str, COLOR_RED, FONT_SMALL_PLAIN);
        break;

    case e_debug_render_river_shore:
        d = map_terrain_is(grid_offset, TERRAIN_SHORE);
        if (d) {
            text_draw(bstring32(d).c_str(), x, y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel.x, pixel.y, 0x80000000);
        }
        break;

    case e_debug_render_invasion_point:
        d = map_invasion_point(tile2i(grid_offset));
        if (d) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel.x, pixel.y, 0x80000000);
            text_draw((d == 1) ? "L" : "S", x, y + 15, FONT_SMALL_PLAIN, (d == 1) ? COLOR_RED : COLOR_RED);
        }
        break;

    case e_debug_render_soldier_strength:
        d = map_soldier_strength_get(grid_offset);
        if (d) {
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, pixel.x, pixel.y, 0x80000000);
            snprintf((char *)str, 30, "%d", d);
            text_draw(str, x, y + 15, FONT_SMALL_PLAIN, COLOR_RED);
        }
        break;

    case e_debug_render_tile_random:
        d = map_random_get(tile2i(grid_offset));
        if (d) {
            snprintf((char *)str, 30, "%d", d);
            debug_text_a(ctx, str, x, y + 10, 0, (pcstr)str, COLOR_LIGHT_BLUE, FONT_SMALL_PLAIN);
        }
    }


}

void draw_debug_figures() {

}

void figure::draw_debug() {
    if (draw_mode == 0) {
        return;
    }

    building *b = home();
    building *bdest = destination();

    char str[10];
    vec2i pixel = lookup_tile_to_pixel(tile);
    pixel = adjust_pixel_offset(pixel);
    pixel.x -= 10;
    pixel.y -= 80;
    int indent = 0;
    color col = COLOR_WHITE;
    painter ctx = game.painter();

    if (!!(draw_mode & e_figure_draw_overlay)) {
        debug_text(ctx, str, pixel.x, pixel.y, indent, "", id, COLOR_WHITE);
        debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "", type, COLOR_LIGHT_BLUE);
        debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "", action_state, COLOR_LIGHT_RED);
        debug_text(ctx, str, pixel.x, pixel.y + 30, indent, "", wait_ticks, COLOR_WHITE);
        debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", roam_length, COLOR_WHITE);
        if (true) {
            vec2i tp = lookup_tile_to_pixel(tile);
            if (tile.grid_offset() != -1)
                debug_draw_tile_box(tp.x, tp.y, COLOR_LIGHT_BLUE, COLOR_GREEN);
        }
        pixel.y += 80;
        debug_text(ctx, str, pixel.x, pixel.y, indent, "", tile.x(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "", tile.y(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "", tile.grid_offset(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(ctx, str, pixel.x, pixel.y + 30, indent, "", progress_on_tile, COLOR_FONT_MEDIUM_GRAY);
        debug_text(ctx, str, pixel.x + 30, pixel.y + 30, indent, "", routing_path_current_tile, COLOR_FONT_MEDIUM_GRAY);
    }

    if (!!(draw_mode & e_figure_draw_routing)) {
        // draw path
        if (routing_path_id) {
            vec2i coords = lookup_tile_to_pixel(destination()->tile);
            build_planner::draw_building_ghost(ctx, image_id_from_group(PACK_CUSTOM, 1) + 3, coords);
            coords = lookup_tile_to_pixel(destination_tile);
            build_planner::draw_building_ghost(ctx, image_id_from_group(PACK_CUSTOM, 1) + 3, coords);
            int tx = tile.x();
            int ty = tile.y();
            coords = lookup_tile_to_pixel(tile);
            ImageDraw::img_generic(ctx, image_id_from_group(PACK_CUSTOM, 1) + 3, coords.x, coords.y);
            int starting_tile_index = routing_path_current_tile;
            if (progress_on_tile >= 0 && progress_on_tile < 8) { // adjust half-tile offset
                starting_tile_index--;
            }

            for (int i = starting_tile_index; i < routing_path_length; i++) {
                int img_index = 10;
                auto pdir = figure_route_get_direction(routing_path_id, i);
                switch (pdir) {
                case 0: ty--; img_index = 0; break;
                case 1: tx++; ty--; break;
                case 2: tx++; img_index = 1; break;
                case 3: tx++; ty++; break;
                case 4: ty++; img_index = 0; break;
                case 5: tx--; ty++; break;
                case 6: tx--; img_index = 1; break;
                case 7: tx--; ty--; break;
                }
                coords = lookup_tile_to_pixel(tile2i(tx, ty));
                ImageDraw::img_generic(ctx, image_id_from_group(PACK_CUSTOM, 1) + img_index, coords.x, coords.y);
            }
        }

        // the rest of values, on top of all else
        if (routing_path_id) {
            debug_text(ctx, str, pixel.x, pixel.y, indent, "", routing_path_id, COLOR_LIGHT_RED);
            debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "", routing_path_current_tile, COLOR_LIGHT_RED);
            debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "", routing_path_length, COLOR_LIGHT_RED);
        } else {
            debug_text(ctx, str, pixel.x, pixel.y, indent, "", roam_length, COLOR_LIGHT_BLUE);
            debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "", roam_wander_freely, COLOR_LIGHT_BLUE);
            debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "", max_roam_length, COLOR_LIGHT_BLUE);
        }

        debug_text(ctx, str, pixel.x, pixel.y + 30, indent, "", terrain_usage, COLOR_WHITE);

        switch (direction) {
        case DIR_FIGURE_CAN_NOT_REACH:
            debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_LIGHT_RED);
            break;
        case DIR_FIGURE_REROUTE:
            debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_LIGHT_BLUE);
            break;
        case DIR_FIGURE_NONE:
            debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_GREEN);
            break;
        default:
            debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_WHITE);
            break;
        }
        debug_text(ctx, str, pixel.x + 10, pixel.y + 40, 5, ":", roam_turn_direction, roam_turn_direction ? COLOR_LIGHT_BLUE : COLOR_FONT_MEDIUM_GRAY);

        pixel.y += 50;
        text_draw(bstring32(progress_on_tile).c_str(), pixel.x, pixel.y + 30, FONT_SMALL_PLAIN, 0);
    }

    if (!!(draw_mode & e_figure_draw_carry)) { // RESOURCE CARRY
        if (resource_id) {
            debug_text(ctx, str, pixel.x, pixel.y, indent, "", resource_id, COLOR_GREEN);
            debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "", resource_amount_full, resource_amount_full ? COLOR_GREEN : COLOR_FONT_MEDIUM_GRAY);
            debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "", collecting_item_id, collecting_item_id ? COLOR_LIGHT_BLUE : COLOR_FONT_MEDIUM_GRAY);
        }
    }

    if (!!(draw_mode & e_figure_draw_building)) {
        debug_text(ctx, str, pixel.x + 0, pixel.y, indent, "", homeID(), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(ctx, str, pixel.x + 20, pixel.y, 8, ":", home()->get_figure_slot(this), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(ctx, str, pixel.x + 0, pixel.y + 10, indent, "", destinationID(), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(ctx, str, pixel.x + 20, pixel.y + 10, 8, ":", destination()->get_figure_slot(this), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
    }

    if (!!(draw_mode & e_figure_draw_festival)) {
        pixel.y += 30;
        //debug_text(ctx, str, pixel.x, pixel.y, indent, "", unk_ph1_269, COLOR_WHITE);
        //debug_text(ctx, str, pixel.x, pixel.y + 10, indent, "service[0]", data.value[0], COLOR_WHITE);
        //debug_text(ctx, str, pixel.x, pixel.y + 20, indent, "service[1]", data.value[1], COLOR_WHITE);
        //debug_text(ctx, str, pixel.x, pixel.y + 30, indent, "service[2]", data.value[2], COLOR_WHITE);
        // debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", festival_remaining_dances, COLOR_WHITE);
    }

    if (!!(draw_mode & e_figure_cross_country_move)) { // CROSS-COUNTRY MOVEMENT
        if (use_cross_country) {
            vec2i tp;
            if (tile.grid_offset() != -1) {
                tp = lookup_tile_to_pixel(tile);
                debug_draw_tile_box(tp.x, tp.y, COLOR_NULL, COLOR_GREEN);
            }
            if (destination_tile.grid_offset() != -1) {
                tp = lookup_tile_to_pixel(destination_tile);
                debug_draw_tile_box(tp.x, tp.y, COLOR_NULL, COLOR_FONT_YELLOW);
            }
        }
        col = use_cross_country ? COLOR_WHITE : COLOR_FONT_MEDIUM_GRAY;
        debug_text(ctx, str, pixel.x, pixel.y, indent, "", use_cross_country);
        pixel.y += 10;
        debug_text(ctx, str, pixel.x, pixel.y, indent, "", cc_direction, col);
        pixel.y += 10;

        debug_text(ctx, str, pixel.x, pixel.y, indent, "", cc_coords.x, col);
        debug_text(ctx, str, pixel.x + 40, pixel.y, indent, "", cc_coords.y, col);
        pixel.y += 10;

        debug_text(ctx, str, pixel.x, pixel.y, indent, "", cc_destination.x, col);
        debug_text(ctx, str, pixel.x + 40, pixel.y, indent, "", cc_destination.y, col);
        pixel.y += 10;

        debug_text(ctx, str, pixel.x, pixel.y, indent, "", cc_delta_xy, col);
        pixel.y += 10;
        debug_text(ctx, str, pixel.x, pixel.y, indent, "", cc_delta.x, col);
        debug_text(ctx, str, pixel.x + 40, pixel.y, indent, "", cc_delta.y, col);
        pixel.y += 10;
    }

    dcast()->debug_draw();
}

void set_debug_building_id(int bid) {
    debugbuildingid.value = bid;
}

int get_debug_building_id() {
    return debugbuildingid();
}

e_debug_render debug_render_mode() {
    return (e_debug_render)debugrender.value;
}

void set_debug_render_mode(e_debug_render mode) {
    debugrender.value = mode;
}

bstring256 get_terrain_type(pcstr def, tile2i tile) {
    int type = map_terrain_get(tile.grid_offset());

    bstring256 buffer = get_terrain_type(def, type);
    if (type & TERRAIN_BUILDING) {
        bstring32 bstr;
        building *b = building_get(map_building_at(tile));
        bstr.printf("bld:%d,", b ? b->type : -1);
        buffer.append(bstr);
    }

    return buffer;
}

bstring256 get_terrain_type(pcstr def, int type) {
    bstring256 buffer;
    buffer.append(def);
    if (type & TERRAIN_DUNE) buffer.append("dune,");
    if (type & TERRAIN_TREE) buffer.append("tree,");
    if (type & TERRAIN_ROCK) buffer.append("rock,");
    if (type & TERRAIN_WATER) buffer.append("water,");

    if (type & TERRAIN_SHRUB) buffer.append("shrub,");
    if (type & TERRAIN_GARDEN) buffer.append("garden,");
    if (type & TERRAIN_ROAD) buffer.append("road,");
    if (type & TERRAIN_GROUNDWATER) buffer.append("grdwater,");
    if (type & TERRAIN_CANAL) buffer.append("canal,");
    if (type & TERRAIN_ELEVATION) buffer.append("elevat,");
    if (type & TERRAIN_ACCESS_RAMP) buffer.append("ramp,");
    if (type & TERRAIN_MEADOW) buffer.append("meadow,");
    if (type & TERRAIN_RUBBLE) buffer.append("rubble,");
    if (type & TERRAIN_FOUNTAIN_RANGE) buffer.append("fountain,");
    if (type & TERRAIN_WALL) buffer.append("wall,");
    if (type & TERRAIN_GATEHOUSE) buffer.append("gate,");
    if (type & TERRAIN_FLOODPLAIN) buffer.append("flood,");
    if (type & TERRAIN_FERRY_ROUTE) buffer.append("wtrroute,");

    return buffer;
}

ANK_REGISTER_PROPS_ITERATOR(config_show_debug_properties);
void config_show_debug_properties(bool header) {
    if (header) {
        return;
    }

    ImGui::BeginTable("Debug", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable);

    game_debug_show_property("Render Mode", e_debug_render_tokens.name((e_debug_render)debugrender()) );

    ImGui::EndTable();
}

void draw_debug_ui(int x, int y) {
    char str[300];

    painter ctx = game.painter();
    /////// RANDOM
    if (false) {
        auto randm = random_data_struct();

        int cl = 60;
        debug_text(ctx, str, x, y + 15, cl, "iv1:", randm->iv1);
        debug_text(ctx, str, x, y + 25, cl, "iv2:", randm->iv2);
        debug_text(ctx, str, x, y + 35, cl, "1_3b:", randm->random1_3bit);
        debug_text(ctx, str, x, y + 45, cl, "1_7b:", randm->random1_7bit);
        debug_text(ctx, str, x, y + 55, cl, "1_15b:", randm->random1_15bit);
        debug_text(ctx, str, x, y + 65, cl, "2_3b:", randm->random2_3bit);
        debug_text(ctx, str, x, y + 75, cl, "2_7b:", randm->random2_7bit);
        debug_text(ctx, str, x, y + 85, cl, "2_15b:", randm->random2_15bit);

        debug_text(ctx, str, x, y + 105, cl, "scum:", anti_scum_random_15bit(false));
        y += 100;
    }

    /////// FLOODS
    if (g_debug_show_opts[e_debug_show_floods]) {
        float _c_curr = g_floods.current_cycle();
        float _c_start = g_floods.start_cycle();
        float _c_end = g_floods.end_cycle();

        int _c_period_last = g_floods.period_length(false);
        int _c_period_next = g_floods.period_length(true);

        float rc_curr = fmod(_c_curr, CYCLES_IN_A_YEAR);
        float rc_start = fmod(_c_start, CYCLES_IN_A_YEAR);
        float rc_end = fmod(_c_end, CYCLES_IN_A_YEAR);

        // floodplains timeline (yearly)
        auto dot = string_from_ascii(",");
        for (int i = 0; i < 392; ++i) {
            text_draw(dot, x + i - 1, y + 15, FONT_SMALL_PLAIN, 0);
        }

        for (int i = 0; i < 392; ++i) {
            int abs_i = i;
            text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);

            if ((i > rc_start - 28 && i < rc_end + 28)
                || (i > rc_start - 28 - CYCLES_IN_A_YEAR && i < rc_end + 28 - CYCLES_IN_A_YEAR)
                || (i > rc_start - 28 + CYCLES_IN_A_YEAR && i < rc_end + 28 + CYCLES_IN_A_YEAR)) {
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_FONT_ORANGE_LIGHT);
            }

            if ((i > rc_start && i < rc_end) || (i > rc_start - CYCLES_IN_A_YEAR && i < rc_end - CYCLES_IN_A_YEAR)
                || (i > rc_start + CYCLES_IN_A_YEAR && i < rc_end + CYCLES_IN_A_YEAR))
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_RED);

            if (g_floods.debug_period() > 0) {
                if (abs_i > _c_start + _c_period_next && abs_i < _c_end - _c_period_next)
                    text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_GREEN);
            } else {
                if (abs_i > _c_start + _c_period_last && abs_i < _c_end - _c_period_last)
                    text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_GREEN);
            }
        }

        // cursor
        text_draw(dot, x + rc_curr, y + 15, FONT_SMALL_OUTLINED, COLOR_FONT_YELLOW);
        text_draw(string_from_ascii("\'"), x + rc_curr, y + 25, FONT_SMALL_OUTLINED, COLOR_FONT_YELLOW);
        debug_text_float(x + rc_curr + 5, y + 25, 0, "", _c_curr);  // current cycle
        debug_text(ctx, str, x + rc_curr + 54, y + 25, 5, ":", g_floods.state); // current cycle

        debug_text(ctx, str, x, y + 35, 60, "debug:", g_floods.debug_period());
        debug_text(ctx, str, x, y + 45, 60, "ftick:", g_floods.fticks);

        y += 50;

        int cl = 60;
        debug_text(ctx, str, x, y + 15, cl + 15, "CURRENT:", _c_curr);             // current cycle
        debug_text(ctx, str, x + 105, y + 15, 10, "/", g_floods.current_subcycle()); // current cycle
        debug_text(ctx, str, x, y + 25, cl, "t-49:", _c_start - 49);               // 49 cycles prior
        debug_text(ctx, str, x, y + 35, cl, "t-28:", _c_start - 28);               // 28 cycles prior
        debug_text(ctx, str, x, y + 45, cl, "  START", _c_start);                  // flood start

        if (g_floods.debug_period() > 0) {
            debug_text(ctx, str, x, y + 55, cl, "rest:", _c_start + _c_period_next);  // first rest period
            debug_text(ctx, str, x, y + 65, cl, "retract:", _c_end - _c_period_next); // first rest period
        } else {
            debug_text(ctx, str, x, y + 55, cl, "rest:", _c_start + _c_period_last);  // first rest period
            debug_text(ctx, str, x, y + 65, cl, "retract:", _c_end - _c_period_last); // first rest period
        }

        debug_text(ctx, str, x, y + 75, cl, "    END", _c_end);    // flood end
        debug_text(ctx, str, x, y + 85, cl, "t+23:", _c_end + 23); // lands farmable again
        debug_text(ctx, str, x, y + 95, cl, "t+28:", _c_end + 28); // lands farmable again

        cl = 100;
        y += 10;
        debug_text(ctx, str, x, y + 105, cl, "season_initial:", g_floods.season_initial);
        debug_text(ctx, str, x, y + 115, cl, "duration_initial:", g_floods.duration_initial);
        debug_text(ctx, str, x, y + 125, cl, "quality_initial:", g_floods.quality_initial);
        debug_text(ctx, str, x, y + 135, cl, "season:", g_floods.season);
        debug_text(ctx, str, x, y + 145, cl, "duration:", g_floods.duration);
        debug_text(ctx, str, x, y + 155, cl, "quality:", g_floods.quality_current);
        debug_text(ctx, str, x, y + 165, cl, "(unk00):", g_floods.unk00);
        debug_text(ctx, str, x, y + 175, cl, "quality_next:", g_floods.quality_next);
        debug_text(ctx, str, x, y + 185, cl, "quality_last:", g_floods.quality_last);

        cl = 150;
        debug_text(ctx, str, x, y + 205, cl, "progress:", g_floods.flood_progress);   // status 30 (???)
        debug_text(ctx, str, x, y + 215, cl, "(unk01):", g_floods.unk01);             // ???
        debug_text(ctx, str, x, y + 225, cl, "state:", g_floods.state);               // floodplains state
        debug_text(ctx, str, x, y + 235, cl, "width:", g_floods.floodplain_width);    
        debug_text(ctx, str, x, y + 245, cl, "hasplains:", g_floods.has_floodplains); 
        debug_text(ctx, str, x, y + 255, cl, "force_inundation:", g_floods.force_inundation);
        debug_text(ctx, str, x, y + 265, cl, "flood_progress_tick:", g_floods.flood_progress_tick);
        debug_text(ctx, str, x, y + 275, cl, "target_progress:", g_floods.flood_progress_target);
        y += 350;
    }
}

console_command::console_command(pcstr name, std::function<void(std::istream &is, std::ostream &os)> f) {
    bind_debug_command(name, f);
}

console_var_int::console_var_int(pcstr name, int v) : value(v) {
    bind_debug_console_var_int(name, value);
}

console_ref_int16::console_ref_int16(pcstr name, int16_t &v) : value(&v) {
    bind_debug_console_var_int16(name, v);
}

console_ref_uint8::console_ref_uint8(pcstr name, uint8_t &v) : value(&v) {
    bind_debug_console_var_uint8(name, v);
}

console_ref_int32::console_ref_int32(pcstr name, int &v) : value(&v) {
    bind_debug_console_var_int(name, v);
}

console_ref_float::console_ref_float(pcstr name, float &v) : value(&v) {
    bind_debug_console_var_float(name, v);
}

console_var_bool::console_var_bool(pcstr name, bool v) : value(v) {
    bind_debug_console_var_bool(name, value);
}

console_ref_bool::console_ref_bool(pcstr name, bool &v) : value(&v) {
    bind_debug_console_var_bool(name, v);
}

void game_debug_t::init() {    
    events::subscribe([] (event_debug_render_change ev) {
        debugrender.value += ev.value;
    });
}
