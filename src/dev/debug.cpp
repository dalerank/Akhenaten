#include "debug.h"

#include <cmath>

#include "core/string.h"
#include "graphics/text.h"

#include "graphics/graphics.h"

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

#include "js/js_game.h"

int debug_range_3 = 0;
int debug_range_4 = 0;
int g_debug_figure_id = 0;

game_debug_t g_debug;
bool g_debug_show_opts[e_debug_opt_size] = { 0 };

const token_holder<e_debug_render, e_debug_render_none, e_debug_render_size> ANK_CONFIG_ENUM(e_debug_render_tokens);

declare_console_var_int(debugrender, 0);
declare_console_var_int(debugtile, 0);
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
    graphics_fill_rect(vec2i{0, 0}, vec2i{1600, 300}, COLOR_FONT_LIGHT_GRAY);
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

void debug_text(painter &ctx, uint8_t* str, int x, int y, int indent, const char* text, int value, color color, e_font font) {
    text_draw(ctx, string_from_ascii(text), x, y, font, color);
    string_from_int(str, value, 0);
    text_draw(ctx, str, x + indent, y, font, color);
}

void debug_text_a(painter &ctx, uint8_t* str, int x, int y, int indent, const char* text, color color, e_font font) {
    text_draw(ctx, string_from_ascii(text), x, y, font, color);
}

void debug_text_float(uint8_t* str, int x, int y, int indent, const char* text, double value, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    string_from_int(str, (int)value, 0);
    int l = string_length(str);
    auto p = &str[l];
    string_copy(string_from_ascii("."), p, 2);
    string_from_int(&str[l + 1], (double)(value - (double)(int)value) * 100.0f, 0);
    text_draw(str, x + indent, y, FONT_SMALL_OUTLINED, color);
}

void debug_text_dual_left(uint8_t* str, int x, int y, int indent, int indent2, const char* text, int value1, int value2, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    string_from_int(str, value1, 0);
    text_draw_left(str, x + indent, y, FONT_SMALL_OUTLINED, color);
    string_from_int(str, value2, 0);
    text_draw_left(str, x + indent + indent2, y, FONT_SMALL_OUTLINED, color);
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
    uint8_t str[30];
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
                debug_text(ctx, str,x1 + 40,y + 20,40,"fert.",map_get_fertility_for_farm(b->tile.grid_offset()),COLOR_FONT_ORANGE_LIGHT);
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
            string_from_int(str, d, 0);
            text_draw(ctx, str, x, y + 10, FONT_SMALL_OUTLINED, COLOR_WHITE);
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
            debug_text_a(ctx, str, x, y + 10, 0, (const char*)str, COLOR_WHITE, FONT_SMALL_PLAIN);
        }
        break;

    case e_debug_render_tile_toph: {
        int image_id = map_image_at(grid_offset);
        const image_t *img = image_get(image_id);
        snprintf((char*)str, 30, "%d", img->isometric_top_height());
        debug_text_a(ctx, str, x, y + 10, 0, (const char*)str, COLOR_WHITE, FONT_SMALL_PLAIN);
        }
        break;

    case e_debug_render_floodplain_shore:
        d = map_get_floodplain_edge(point);
        if (d) {
            string_from_int(str, d, 0);
            text_draw(ctx, str, x, y + 15, FONT_SMALL_OUTLINED, COLOR_WHITE);
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

    case e_debug_render_damage_fire: // FIRE
        if (b_id && b) {
            debug_text(ctx, str, x, y + 10, 0, "", b->fire_risk, COLOR_LIGHT_RED);
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
            string_from_int(str, d, 0);
            text_draw(ctx, str, x, y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);
            ImageDraw::img_generic(ctx, image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, pixel.x, pixel.y, 0x80000000);
        }
        break;
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

    uint8_t str[10];
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
        string_from_int(str, progress_on_tile, 0);
        text_draw(ctx, str, pixel.x, pixel.y + 30, FONT_SMALL_PLAIN, 0);
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
        debug_text(ctx, str, pixel.x, pixel.y + 40, indent, "", festival_remaining_dances, COLOR_WHITE);
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

void draw_debug_ui(int x, int y) {
    uint8_t str[300];

    painter ctx = game.painter();
    /////// DEBUG PAGES NAME
    if (g_debug_show_opts[e_debug_show_pages]) {
        y += 13;
        int DB1 = abs(debugtile()) % 7;
        int DB2 = abs(debugrender()) % 20;

        color col = COLOR_GREEN;

        string_from_int(str, DB1);
        text_draw(str, x, y, FONT_SMALL_OUTLINED, col);
        text_draw((uint8_t*)string_from_ascii(":"), x + 14, y, FONT_SMALL_OUTLINED, col);
        x += 20;
        switch (DB1) {
        case 1:
            text_draw((uint8_t*)string_from_ascii("ACTION / STATE IDS"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        case 2:
            text_draw((uint8_t*)string_from_ascii("ROUTING"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        case 3:
            text_draw((uint8_t*)string_from_ascii("RESOURCES / CARRYING"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        case 4:
            text_draw((uint8_t*)string_from_ascii("HOME IDS"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        case 5:
            text_draw((uint8_t*)string_from_ascii("FESTIVAL"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        case 6:
            text_draw((uint8_t*)string_from_ascii("CROSS-COUNTRY"), x, y, FONT_SMALL_OUTLINED, col);
            break;
        }
        y += 3;
        x -= 20;
        string_from_int(str, DB2);
        text_draw(str, x, y + 10, FONT_SMALL_OUTLINED, col);
        text_draw((uint8_t*)string_from_ascii(":"), x + 14, y + 10, FONT_SMALL_OUTLINED, col);
        x += 20;
        switch (DB2) {
        default:
            break;
        case e_debug_render_building:
            text_draw((uint8_t*)string_from_ascii("BUILDING IDS"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 2:
            text_draw((uint8_t*)string_from_ascii("DRAW-TILES AND SIZES"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 3:
            text_draw((uint8_t*)string_from_ascii("ROADS"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 4:
            text_draw((uint8_t*)string_from_ascii("ROUTING DISTANCE"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 5:
            text_draw((uint8_t*)string_from_ascii("CITIZEN ROUTING GRID"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 6:
            text_draw((uint8_t*)string_from_ascii("MOISTURE"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 7:
            text_draw((uint8_t*)string_from_ascii("PROPER GRASS LEVEL"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 8:
            text_draw((uint8_t*)string_from_ascii("FERTILITY / SOIL DEPLETION"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 9:
            text_draw((uint8_t*)string_from_ascii("FLOODPLAIN SHORE ORDER"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 10:
            text_draw((uint8_t*)string_from_ascii("FLOODPLAIN TERRAIN FLAGS"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 11:
            text_draw((uint8_t*)string_from_ascii("LABOR"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 12:
            text_draw((uint8_t*)string_from_ascii("SPRITE FRAMES / STATUES AND MONUMENTS"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 13:
            text_draw((uint8_t*)string_from_ascii("TERRAIN BIT FIELD"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 14:
            text_draw((uint8_t*)string_from_ascii("IMAGE FIELD"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 15:
            text_draw((uint8_t*)string_from_ascii("MARSHLAND DEPLETION"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 16:
            text_draw((uint8_t*)string_from_ascii("MARSHLAND"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 17:
            text_draw((uint8_t*)string_from_ascii("TERRAIN TYPE"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 18:
            text_draw((uint8_t*)string_from_ascii("UNKNOWN SOIL GRID"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        case 19:
            text_draw((uint8_t*)string_from_ascii("UNKNOWN 32BIT GRID"), x, y + 10, FONT_SMALL_OUTLINED, col);
            break;
        }
        y += 10;
        x -= 20;
    }

    /////// TIME
    if (g_debug_show_opts[e_debug_show_game_time]) {
        debug_text(ctx, str, x, y + 15, 50, "tick:", game.simtime.tick);
        debug_text(ctx, str, x + 80, y + 15, 50, "iscycle:", g_floods.is_start_cycle());
        debug_text(ctx, str, x, y + 25, 50, "cycle:", g_floods.current_cycle());
        debug_text(ctx, str, x + 90, y + 25, 60, "frame:", g_floods.current_subcycle());

        debug_text(ctx, str, x, y + 35, 50, "day:", game.simtime.day);
        debug_text(ctx, str, x, y + 45, 50, "month:", game.simtime.month);
        debug_text(ctx, str, x, y + 55, 50, "year:", game.simtime.year);
        debug_text(ctx, str, x, y + 65, 60, "abs. tick:", game.simtime.absolute_tick(true)); // absolute tick of the year
        debug_text(ctx, str, x, y + 75, 60, "year tick:", game.simtime.absolute_tick(false)); // absolute tick of the year
        debug_text(ctx, str, x, y + 85, 60, "abs. day:", game.simtime.absolute_day(true));   // absolute day of the year
        debug_text(ctx, str, x, y + 95, 60, "year day:", game.simtime.absolute_day(false));   // absolute day of the year
        y += 80;
    }

    /////// BUILD PLANNER
    if (g_debug_show_opts[e_debug_show_build_planner]) {
        int cl = 90;
        debug_text(ctx, str, x, y + 15, cl, "type:", g_city_planner.build_type);
        debug_text(ctx, str, x, y + 25, cl, "in progress:", g_city_planner.in_progress);
        debug_text(ctx, str, x, y + 35, cl, "draw as con.:", g_city_planner.draw_as_constructing);
        debug_text(ctx, str, x, y + 45, cl, "orientation:", g_city_planner.absolute_orientation);
        debug_text(ctx, str, x + 40, y + 45, cl, "", g_city_planner.relative_orientation);
        debug_text(ctx, str, x, y + 55, cl, "variant:", g_city_planner.building_variant);
        debug_text(ctx, str, x, y + 65, cl, "start:", g_city_planner.start.x());
        debug_text(ctx, str, x + 40, y + 65, cl, "", g_city_planner.start.y());
        debug_text(ctx, str, x, y + 75, cl, "end:", g_city_planner.end.x());
        debug_text(ctx, str, x + 40, y + 75, cl, "", g_city_planner.end.y());

        vec2i screen_start = tile_to_screen(g_city_planner.start);
        vec2i screen_end = tile_to_screen(g_city_planner.end);
        debug_text(ctx, str, x + 170, y + 65, 60, "screen:", screen_start.x);
        debug_text(ctx, str, x + 170 + 40, y + 65, 60, "", screen_start.y);
        debug_text(ctx, str, x + 170, y + 75, 60, "screen:", screen_end.x);
        debug_text(ctx, str, x + 170 + 40, y + 75, 60, "", screen_end.y);

        //        screen_tile screen_start2 = attempt_mappoint_to_screen(Planner.start);
        //        screen_tile screen_end2 = attempt_mappoint_to_screen(Planner.end);
        //        color col = (screen_start != screen_start2) ? COLOR_LIGHT_RED : COLOR_LIGHT_GREEN;
        //        draw_debug_line(str, x + 300, y + 65, 60, "direct:", screen_start2.x, col); draw_debug_line(str, x +
        //        300 + 40, y + 65, 60, "", screen_start2.y, col); col = (screen_end != screen_end2) ? COLOR_LIGHT_RED :
        //        COLOR_LIGHT_GREEN; draw_debug_line(str, x + 300, y + 75, 60, "direct:", screen_end2.x, col);
        //        draw_debug_line(str, x + 300 + 40, y + 75, 60, "", screen_end2.y, col);

        debug_text(ctx, str, x, y + 85, cl, "cost:", g_city_planner.total_cost);
        y += 90;
    }

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

    /////// RELIGION
    if (g_debug_show_opts[e_debug_show_religion]) {
        int cl = 0; 
        text_draw((uint8_t*)string_from_ascii("                    mood/target  wrath/ankhs            buildings  coverage  festival"), x, y + 15, FONT_SMALL_OUTLINED, COLOR_WHITE);
        y += 15;
        int c0 = 60;
        int c1 = 40;
        int c2 = 140;
        int c3 = 220;
        int c4 = 240;
        int c5 = 260;
        int c6 = 290;
        int c7 = 15;
        int c8 = 360;

        if (g_city.religion.is_god_known(GOD_OSIRIS) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 15, c0, c1, "Osiris:", g_city.religion.gods[0].mood, g_city.religion.gods[0].target_mood);
            debug_text_dual_left(str, x + c2, y + 15, 0, c1, "", g_city.religion.gods[0].wrath_bolts, g_city.religion.gods[0].happy_ankhs);
            debug_text(ctx, str, x + c3, y + 15, cl, "", g_city.buildings.count_total(BUILDING_SHRINE_OSIRIS));
            debug_text(ctx, str, x + c4, y + 15, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_OSIRIS));
            debug_text(ctx, str, x + c5, y + 15, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_COMPLEX_OSIRIS));
            debug_text(ctx, str, x + c6, y + 15, c7, "%", g_city.religion.coverage_avg(GOD_OSIRIS));
            debug_text(ctx, str, x + c8, y + 15, cl, "", g_city.religion.gods[0].months_since_festival);
        }

        if (g_city.religion.is_god_known(GOD_RA) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 25, c0, c1, "Ra:", g_city.religion.gods[1].mood, g_city.religion.gods[1].target_mood);
            debug_text_dual_left(str, x + c2, y + 25, 0, c1, "", g_city.religion.gods[1].wrath_bolts, g_city.religion.gods[1].happy_ankhs);
            debug_text(ctx, str, x + c3, y + 25, cl, "", g_city.buildings.count_total(BUILDING_SHRINE_RA));
            debug_text(ctx, str, x + c4, y + 25, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_RA));
            debug_text(ctx, str, x + c5, y + 25, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_COMPLEX_RA));
            debug_text(ctx, str, x + c6, y + 25, c7, "%", g_city.religion.coverage_avg(GOD_RA));
            debug_text(ctx, str, x + c8, y + 25, cl, "", g_city.religion.gods[1].months_since_festival);
        }

        if (g_city.religion.is_god_known(GOD_PTAH) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 35, c0, c1, "Ptah:", g_city.religion.gods[2].mood, g_city.religion.gods[2].target_mood);
            debug_text_dual_left(str, x + c2, y + 35, 0, c1, "", g_city.religion.gods[2].wrath_bolts, g_city.religion.gods[2].happy_ankhs);
            debug_text(ctx, str, x + c3, y + 35, cl, "", g_city.buildings.count_total(BUILDING_SHRINE_PTAH));
            debug_text(ctx, str, x + c4, y + 35, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_PTAH));
            debug_text(ctx, str, x + c5, y + 35, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_COMPLEX_PTAH));
            debug_text(ctx, str, x + c6, y + 35, c7, "%", g_city.religion.coverage_avg(GOD_PTAH));
            debug_text(ctx, str, x + c8, y + 35, cl, "", g_city.religion.gods[2].months_since_festival);
        }

        if (g_city.religion.is_god_known(GOD_SETH) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 45, c0, c1, "Seth:", g_city.religion.gods[3].mood, g_city.religion.gods[3].target_mood);
            debug_text_dual_left(str, x + c2, y + 45, 0, c1, "", g_city.religion.gods[3].wrath_bolts, g_city.religion.gods[3].happy_ankhs);
            debug_text(ctx, str, x + c3, y + 45, cl, "", g_city.buildings.count_total(BUILDING_SHRINE_SETH));
            debug_text(ctx, str, x + c4, y + 45, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_SETH));
            debug_text(ctx, str, x + c5, y + 45, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_COMPLEX_SETH));
            debug_text(ctx, str, x + c6, y + 45, c7, "%", g_city.religion.coverage_avg(GOD_SETH));
            debug_text(ctx, str, x + c8, y + 45, cl, "", g_city.religion.gods[3].months_since_festival);
        }

        if (g_city.religion.is_god_known(GOD_BAST) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 55, c0, c1, "Bast:", g_city.religion.gods[4].mood, g_city.religion.gods[4].target_mood);
            debug_text_dual_left(str, x + c2, y + 55, 0, c1, "", g_city.religion.gods[4].wrath_bolts, g_city.religion.gods[4].happy_ankhs);
            debug_text(ctx, str, x + c3, y + 55, cl, "", g_city.buildings.count_total(BUILDING_SHRINE_BAST));
            debug_text(ctx, str, x + c4, y + 55, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_BAST));
            debug_text(ctx, str, x + c5, y + 55, cl, "", g_city.buildings.count_active(BUILDING_TEMPLE_COMPLEX_BAST));
            debug_text(ctx, str, x + c6, y + 55, c7, "%", g_city.religion.coverage_avg(GOD_BAST));
            debug_text(ctx, str, x + c8, y + 55, cl, "", g_city.religion.gods[4].months_since_festival);
        }

        cl = 180;
        debug_text(ctx, str, x, y + 75, cl, "150% export profits:", g_city.religion.ra_150_export_profits_months_left);
        debug_text(ctx, str, x, y + 85, cl, "No traders:", g_city.religion.ra_no_traders_months_left);
        debug_text(ctx, str, x, y + 95, cl, "Slightly increased trades:", g_city.religion.ra_slightly_increased_trading_months_left);
        debug_text(ctx, str, x, y + 105, cl, "Slightly reduced trades:", g_city.religion.ra_slightly_reduced_trading_months_left);
        debug_text(ctx, str, x, y + 115, cl, "Harshly reduced trades:", g_city.religion.ra_harshly_reduced_trading_months_left);

        debug_text(ctx, str, x, y + 125, cl, "Enemy troops kill:", g_city.religion.seth_crush_enemy_troops);
        debug_text(ctx, str, x, y + 135, cl, "Player troops protection:", g_city.religion.seth_protect_player_troops);

        debug_text(ctx, str, x, y + 145, cl, "Double farm yields days:", g_city.religion.osiris_double_farm_yield_days);
        debug_text(ctx, str, x, y + 155, cl, "Floods will destroy farms:", g_city.religion.osiris_flood_will_destroy_active);
        y += 170;
    }

    if (g_debug_show_opts[e_debug_show_sound_channels]) {
        const auto &channels = g_sound.channels();
        int cl = 180;
        for (const auto &ch: channels) {
            if (!ch.playing) {
                continue;
            }
            debug_text(ctx, str, x, y + 1, cl, bstring256().printf("%03u: L%03u: R:%03u: %s", &ch - channels.begin(), ch.left_pan, ch.right_pan, ch.filename.c_str()).c_str(), 0);
            y += 12;
        }
    }

    if (g_debug_show_opts[e_debug_show_migration]) {
        int cl = 180;
        debug_text_a(ctx, str, x, y + 1, cl, "====================== migration ======================");
        y += 12;
        debug_text(ctx, str, x, y + 1, cl, "invading_cap:", g_city.migration.invading_cap);
        debug_text(ctx, str, x, y + 13, cl, "migration_cap:", g_city.migration.migration_cap);
        debug_text(ctx, str, x, y + 25, cl, "percentage_by_sentiment:", g_city.migration.percentage_by_sentiment);
        debug_text(ctx, str, x, y + 37, cl, "emigration_message_shown:", g_city.migration.emigration_message_shown);
        debug_text(ctx, str, x, y + 49, cl, "newcomers:", g_city.migration.newcomers);
        debug_text(ctx, str, x, y + 61, cl, "percentage:", g_city.migration.percentage);
        debug_text(ctx, str, x, y + 73, cl, "no_immigration_cause:", g_city.migration.no_immigration_cause);
        debug_text(ctx, str, x, y + 85, cl, "refused_immigrants_today:", g_city.migration.refused_immigrants_today);
        debug_text(ctx, str, x, y + 97, cl, "emigrated_today:", g_city.migration.emigrated_today);
        debug_text(ctx, str, x, y + 109, cl, "immigrated_today:", g_city.migration.immigrated_today);
        debug_text(ctx, str, x, y + 121, cl, "emigration_queue_size:", g_city.migration.emigration_queue_size);
        debug_text(ctx, str, x, y + 133, cl, "immigration_queue_size:", g_city.migration.immigration_queue_size);
        debug_text(ctx, str, x, y + 145, cl, "immigration_duration:", g_city.migration.immigration_duration);
        debug_text(ctx, str, x, y + 157, cl, "emigration_amount_per_batch:", g_city.migration.emigration_amount_per_batch);
        debug_text(ctx, str, x, y + 169, cl, "emigration_duration:", g_city.migration.emigration_duration);
        debug_text(ctx, str, x, y + 181, cl, "immigration_amount_per_batch:", g_city.migration.immigration_amount_per_batch);
        debug_text(ctx, str, x, y + 193, cl, "nobles_leave_city_this_year:", g_city.migration.nobles_leave_city_this_year);
        y += 212;
    }

    if (g_debug_show_opts[e_debug_show_sentiment]) {
        int cl = 180;
        debug_text(ctx, str, x, y + 1, cl, "value:", g_city.sentiment.value);
        debug_text(ctx, str, x, y + 13, cl, "previous_value:", g_city.sentiment.previous_value);
        debug_text(ctx, str, x, y + 25, cl, "message_delay:", g_city.sentiment.message_delay);
        debug_text(ctx, str, x, y + 37, cl, "include_tents:", g_city.sentiment.include_huts);
        debug_text(ctx, str, x, y + 49, cl, "unemployment_pct:", g_city.sentiment.unemployment_pct);
        debug_text(ctx, str, x, y + 61, cl, "wages:", g_city.sentiment.wages);
        debug_text(ctx, str, x, y + 73, cl, "low_mood_cause:", g_city.sentiment.low_mood_cause);
        debug_text(ctx, str, x, y + 85, cl, "protesters:", g_city.sentiment.protesters);
        debug_text(ctx, str, x, y + 97, cl, "criminals:", g_city.sentiment.criminals);
        debug_text(ctx, str, x, y + 109, cl, "can_create_mugger:", g_city.sentiment.can_create_mugger);
        debug_text(ctx, str, x, y + 121, cl, "can_create_protestor:", g_city.sentiment.can_create_protestor);
        debug_text(ctx, str, x, y + 133, cl, "last_mugger_message:", g_city.sentiment.last_mugger_message);
        debug_text(ctx, str, x, y + 145, cl, "contribution_taxes:", g_city.sentiment.contribution_taxes);
        debug_text(ctx, str, x, y + 157, cl, "contribution_wages:", g_city.sentiment.contribution_wages);
        debug_text(ctx, str, x, y + 169, cl, "contribution_employment:", g_city.sentiment.contribution_employment);
        debug_text(ctx, str, x, y + 181, cl, "penalty_huts:", g_city.sentiment.contribution_penalty_huts);
        debug_text(ctx, str, x, y + 193, cl, "monuments:", g_city.sentiment.contribution_monuments);
        debug_text(ctx, str, x, y + 205, cl, "religion_coverage:", g_city.sentiment.contribution_religion_coverage);
        y += 210;
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
        debug_text_float(str, x + rc_curr + 5, y + 25, 0, "", _c_curr);  // current cycle
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

    /////// CAMERA
    if (g_debug_show_opts[e_debug_show_camera]) {
        tile2i camera_tile = city_view_get_camera_mappoint();
        vec2i camera_pixels = camera_get_pixel_offset_internal(ctx);

        auto mm_view = g_city_view.get_scrollable_pixel_limits();

        int real_max_x;
        int real_max_y;
        city_view_get_camera_max_tile(&real_max_x, &real_max_y);

        int max_x_pixel_offset;
        int max_y_pixel_offset;
        city_view_get_camera_max_pixel_offset(&max_x_pixel_offset, &max_y_pixel_offset);

        y += 30;
        debug_text_dual_left(str, x, y - 15, 90, 40, "---min:", mm_view.min.x, mm_view.min.y);
        debug_text_dual_left(str, x, y - 5, 90, 40, "camera:", g_city_view.camera.position.x, g_city_view.camera.position.y);
        debug_text_dual_left(str, x, y + 5, 90, 40, "---max:", mm_view.max.x, mm_view.max.y);

        debug_text_dual_left(str, x, y + 25, 90, 40, "---min:", SCROLL_MIN_SCREENTILE_X, SCROLL_MIN_SCREENTILE_Y);
        debug_text_dual_left(str, x, y + 35, 90, 40, "tile:", camera_tile.x(), camera_tile.y());
        debug_text_dual_left(str, x, y + 45, 90, 40, "---max:", real_max_x, real_max_y);

        debug_text_dual_left(str, x, y + 65, 90, 40, "---min:", 0, 0);
        debug_text_dual_left(str, x, y + 75, 90, 40, "pixel:", camera_pixels.x, camera_pixels.y);
        debug_text_dual_left(str, x, y + 85, 90, 40, "---max:", max_x_pixel_offset, max_y_pixel_offset);

        debug_text_dual_left(str, x, y + 105, 90, 40, "v.tiles:", g_city_view.viewport.size_pixels.x / 60, g_city_view.viewport.size_pixels.y / 30);
        debug_text_dual_left(str, x, y + 115, 90, 40, "v.pixels:", g_city_view.viewport.size_pixels.y, g_city_view.viewport.size_pixels.y);

        debug_text(ctx, str, x, y + 125, 50, "zoom:", g_zoom.get_percentage());
        debug_text_float(str, x, y + 125, 50 + 40, "", g_zoom.get_scale());

        debug_text_float(str, x, y + 135, 50, "target:", g_zoom.ftarget());
        debug_text_float(str, x + 100, y + 135, 50, "delta:", g_zoom.fdelta());

        vec2i pixel = {mouse_get()->x, mouse_get()->y};
        debug_text(ctx, str, x, y + 145, 50, "mouse:", pixel.x);
        debug_text(ctx, str, x + 40, y + 145, 50, "", pixel.y);

        vec2i viewp = pixel_to_viewport(pixel);
        debug_text(ctx, str, x, y + 155, 50, "viewp:", viewp.x);
        debug_text(ctx, str, x + 40, y + 155, 50, "", viewp.y);

        vec2i coord = pixel_to_camera_coord(pixel, false);
        debug_text(ctx, str, x, y + 165, 50, "coord:", coord.x);
        debug_text(ctx, str, x + 40, y + 165, 50, "", coord.y);

        screen_tile screen = pixel_to_screentile(pixel);
        debug_text(ctx, str, x, y + 175, 50, "tile:", screen.x);
        debug_text(ctx, str, x + 40, y + 175, 50, "", screen.y);

        vec2i offset = {coord.x % TILE_WIDTH_PIXELS, coord.y % TILE_HEIGHT_PIXELS};
        debug_text(ctx, str, x, y + 185, 50, "offset:", offset.x);
        debug_text(ctx, str, x + 40, y + 185, 50, "", offset.y);

        tile2i point = screen_to_tile(screen);
        debug_text(ctx, str, x, y + 195, 50, "point:", point.x());
        debug_text(ctx, str, x + 40, y + 195, 50, "", point.y());
        debug_text(ctx, str, x + 80, y + 195, 50, "", point.grid_offset());

        debug_text_a(ctx, str, x + 180, y + 195, 50, get_terrain_type("type: ", point));
        pixel = lookup_tile_to_pixel(point);
        debug_text(ctx, str, x, y + 205, 50, "pixel:", pixel.x);
        debug_text(ctx, str, x + 40, y + 205, 50, "", pixel.y);

        //        if (point.grid_offset() != -1)
        //            debug_draw_tile_box(pixel.x, pixel.y);

        //        pixel = tile_to_pixel(screentile_to_mappoint(city_view_data_unsafe()->camera.tile_internal));
        //        debug_draw_tile_box(pixel.x, pixel.y);

        y += 200;
    }

    /////// CLOUDS
    if (g_debug_show_opts[e_debug_show_clouds]) {
        y += 30;

        // TODO: label drawn clouds
        // auto& viewdata = city_view_data_unsafe();
        // vec2i min_pos, max_pos;
        // city_view_get_camera_scrollable_pixel_limits(viewdata, min_pos, max_pos);
        // const int x_offset = viewdata.camera.position.x - min_pos.x;
        // const int y_offset = viewdata.camera.position.y - min_pos.y;
        // float scale = g_zoom.get_scale();

        for (int i = 0; i < NUM_CLOUDS; i++) {
            const cloud_type *cloud = &g_cloud_data.clouds[i];
            e_cloud_status status = cloud->status;
            char status_text[32] = {};
            switch (status) {
                case e_cloud_status_inactive: snprintf(status_text, 32, "%s", "status: INACTIVE"); break;
                case e_cloud_status_created: snprintf(status_text, 32, "%s", "status: CREATED"); break;
                case e_cloud_status_moving: snprintf(status_text, 32, "%s", "status: MOVING"); break;
            }

            // debug_text(ctx, str, (cloud->render_x - x_offset) * scale, (cloud->render_y - y_offset) * scale, 50, "Cloud", i);
            debug_text(ctx, str, x, y - 20, 70, "---cloud ", i);
            debug_text_a(ctx, str, x, y - 10, 70, status_text);
            debug_text_dual_left(str, x, y, 120, 40, "speed x,y:", cloud->speed.x.current_speed,
                                 cloud->speed.y.current_speed);
            debug_text_dual_left(str, x, y + 10, 120, 40, "pos x,y: ", cloud->x, cloud->y);
            debug_text_dual_left(str, x, y + 20, 120, 40, "render pos x,y: ", cloud->render_x, cloud->render_y);
            y += 40;
        }

        y += 200;
    }

    /////// TUTORIAL
    if (g_debug_show_opts[e_debug_show_tutorial]) {
        const auto &flags = g_tutorials_flags;
        struct tutopt { const char *optname; bool value; };
        for (int i = 0; i < 41; i++) {
            tutopt f{"", flags.pharaoh.flags[i]};
            switch (i) {
            case 0:
                f = { "1:fire", flags.tutorial_1.building_burned };
                break;
            case 1:
                f = { "1:granary_opened", flags.tutorial_1.granary_opened };
                break;
            case 2:
                f = { "1:meat_400", flags.tutorial_1.gamemeat_stored };
                break;
            case 3:
                f = { "1:collapse", flags.tutorial_1.building_collapsed };
                break;
            case 4:
                f = { "2:gold_mined", flags.tutorial_2.gold_mined };
                break;
            case 5:
                f = { "2:temples_done", flags.tutorial_2.temples_built };
                break;
            case 6:
                f = { "2:crime", flags.tutorial_2.crime };
                break;
            case 7:
                f = { "3:figs", flags.tutorial_3.figs_stored };
                break;
            case 8:
                f = { "3:pottery_100", flags.tutorial_3.pottery_made_1 };
                break;
            case 9:
                f = { "3:pottery_100", flags.tutorial_3.pottery_made_2 };
                break;
            case 10:
                f = { "3:disease", flags.tutorial_3.disease };
                break;
            case 11:
                f = { "4:beer_300", flags.tutorial_4.beer_made };
                break;
            case 12:
                f = { "5:apartment", flags.tutorial_5.spacious_apartment };
                break;
            case 15:
                f = { "tut1 start", flags.tutorial_1.started };
                break;
            case 16:
                f = { "tut2 start", flags.tutorial_2.started };
                break;
            case 17:
                f = { "tut3 start", flags.tutorial_3.started };
                break;
            case 18:
                f = { "tut4 start", flags.tutorial_4.started };
                break;
            case 19:
                f = { "tut5 start", flags.tutorial_5.started };
                break;
            case 20:
                f = { "tut6 start", flags.tutorial_6.started };
                break;
            case 21:
                f = { "tut7 start", flags.pharaoh.tut7_start };
                break;
            case 22:
                f = { "tut8 start" , flags.pharaoh.tut8_start };
                break;
            }

            int color = f.value ? COLOR_GREEN : COLOR_WHITE;
            text_draw((uint8_t*)string_from_ascii(f.optname), x + 3, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
            text_draw((uint8_t*)string_from_ascii(":"), x + 3 + 20, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
            text_draw((uint8_t*)string_from_ascii(f.value ? "yes" : "no"), x + 3 + 45, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
        }
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
    events::subscribe([] (event_debug_tile_change ev) {
        debugtile.value += ev.value;
    });    
    
    events::subscribe([] (event_debug_render_change ev) {
        debugrender.value += ev.value;
    });
}
