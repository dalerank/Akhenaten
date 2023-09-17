#include "debug.h"

#include <cmath>

#include "core/string.h"
#include "graphics/text.h"

#include "graphics/boilerplate.h"

#include "building/industry.h"
#include "city/data_private.h"
#include "graphics/view/lookup.h"
#include "grid/aqueduct.h"
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
#include "widget/city/building_ghost.h"

#include "building/construction/build_planner.h"
#include "building/count.h"
#include "city/coverage.h"
#include "city/floods.h"
#include "city/gods.h"
#include "core/random.h"
#include "figure/route.h"
#include "game/time.h"
#include "game/tutorial.h"
#include "grid/figure.h"
#include "platform/renderer.h"

int debug_range_1 = 0;
int debug_range_2 = 0;
int debug_range_3 = 0;
int debug_range_4 = 0;

void handle_debug_hotkeys(const hotkeys* h) {
    if (h->debug_1_up)
        debug_range_1 += 1;
    if (h->debug_1_down)
        debug_range_1 -= 1;
    if (h->debug_2_up)
        debug_range_2 += 1;
    if (h->debug_2_down)
        debug_range_2 -= 1;
    //    if (debug_range_1 < 0)
    //        debug_range_1 = 0;
    //    if (debug_range_1 > 20)
    //        debug_range_1 = 20;
}

static const uint8_t* font_test_str = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/"
                                                        ",._äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";
static const uint8_t* font_test_str_ascii = (uint8_t*)(char*)"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!\"%*()-+=:;'?\\/,._";
static const uint8_t* font_test_str_extended = (uint8_t*)(char*)"äáàâëéèêïíìîöóòôüúùûçñæßÄÉÜÑÆŒœÁÂÀÊÈÍÎÌÓÔÒÖÚÛÙ¡¿^°ÅØåø";

static void debug_font_line(int* y, font_t font) {
    int line_height = font_definition_for(font)->line_height;
    if (line_height < 11)
        line_height = 11;
    line_height += 5;
    text_draw(font_test_str_ascii, 5, *y, font, COLOR_MASK_NONE);
    *y += line_height;
    //    text_draw(font_test_str_extended, 5, *y, font, COLOR_MASK_NONE); *y += line_height;
}
void debug_font_test() {
    graphics_fill_rect(0, 0, 1600, 300, COLOR_FONT_LIGHT_GRAY);
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

void debug_text(uint8_t* str, int x, int y, int indent, const char* text, int value, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
    string_from_int(str, value, 0);
    text_draw(str, x + indent, y, FONT_SMALL_OUTLINED, color);
}

void debug_text_a(uint8_t* str, int x, int y, int indent, const char* text, color color) {
    text_draw(string_from_ascii(text), x, y, FONT_SMALL_OUTLINED, color);
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
    graphics_renderer()->draw_line(x_start - 1, x_end - 1, y_start, y_end, COLOR_BLACK);
    graphics_renderer()->draw_line(x_start + 1, x_end + 1, y_start, y_end, COLOR_BLACK);
    graphics_renderer()->draw_line(x_start, x_end, y_start - 1, y_end - 1, COLOR_BLACK);
    graphics_renderer()->draw_line(x_start, x_end, y_start + 1, y_end + 1, COLOR_BLACK);
    graphics_renderer()->draw_line(x_start, x_end, y_start, y_end, col);
}

void debug_draw_rect_with_contour(int x, int y, int w, int h, color col) {
    graphics_renderer()->draw_rect(x - 1, y - 1, w, h, COLOR_BLACK);
    graphics_renderer()->draw_rect(x + 1, y + 1, w, h, COLOR_BLACK);
    graphics_renderer()->draw_rect(x, y, w - 1, h - 1, COLOR_BLACK);
    graphics_renderer()->draw_rect(x, y, w + 1, h + 1, COLOR_BLACK);
    graphics_renderer()->draw_rect(x, y, w, h, col);
}

void debug_draw_crosshair(int x, int y) {
    graphics_renderer()->draw_line(x, x + 10, y, y, COLOR_GREEN);
    graphics_renderer()->draw_line(x, x, y, y + 10, COLOR_RED);
}

void debug_draw_sprite_box(int x, int y, const image_t* img, float scale, color color_mask) {
    int x2 = x - img->animation.sprite_x_offset;
    int y2 = y - img->animation.sprite_y_offset;
    graphics_renderer()->draw_rect(x2 * scale, y2 * scale, img->width * scale, img->height * scale, color_mask);
    debug_draw_crosshair((x2 + img->animation.sprite_x_offset) * scale, (y2 + img->animation.sprite_y_offset) * scale);
}

void debug_draw_tile_box(int x, int y, color rect, color bb, int tile_size_x, int tile_size_y) {
    float scale = zoom_get_scale();

    int left_x = x;
    int left_y = y + HALF_TILE_HEIGHT_PIXELS;

    int top_x = left_x + (tile_size_y * HALF_TILE_WIDTH_PIXELS);
    int top_y = left_y - (tile_size_y * HALF_TILE_HEIGHT_PIXELS);

    int right_x = top_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int right_y = top_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    int bottom_x = left_x + (tile_size_x * HALF_TILE_WIDTH_PIXELS);
    int bottom_y = left_y + (tile_size_x * HALF_TILE_HEIGHT_PIXELS);

    if (rect != COLOR_NULL) {
        graphics_renderer()->draw_rect(x * scale, y * scale, TILE_WIDTH_PIXELS * scale, TILE_HEIGHT_PIXELS * scale, rect);
    }

    if (bb != COLOR_NULL) {
        graphics_renderer()->draw_line(left_x * scale, top_x * scale, left_y * scale, top_y * scale, bb);
        graphics_renderer()->draw_line(top_x * scale, right_x * scale, top_y * scale, right_y * scale, bb);
        graphics_renderer()->draw_line(right_x * scale, bottom_x * scale, right_y * scale, bottom_y * scale, bb);
        graphics_renderer()->draw_line(bottom_x * scale, left_x * scale, bottom_y * scale, left_y * scale, bb);
    }
}
void debug_draw_tile_top_bb(int x, int y, int height, color color, int size) {
    float scale = zoom_get_scale();

    int left_x = x;
    int left_bottom = y + HALF_TILE_HEIGHT_PIXELS;

    int right_x = left_x + (size * HALF_TILE_WIDTH_PIXELS);
    int right_bottom = left_bottom - (size * HALF_TILE_HEIGHT_PIXELS);

    int left_top = left_bottom - height;
    int right_top = right_bottom - height;

    graphics_renderer()->draw_line(left_x * scale, right_x * scale, left_bottom * scale, right_bottom * scale, color);
    graphics_renderer()->draw_line(left_x * scale, right_x * scale, left_top * scale, right_top * scale, color);

    graphics_renderer()->draw_line(left_x * scale, left_x * scale, left_bottom * scale, left_top * scale, color);
    graphics_renderer()->draw_line(right_x * scale, right_x * scale, right_bottom * scale, right_top * scale, color);
}

//////////

static int north_tile_grid_offset(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int size = map_property_multi_tile_size(grid_offset);
    for (int i = 0; i < size && map_property_multi_tile_x(grid_offset); i++)
        grid_offset += GRID_OFFSET(-1, 0);
    for (int i = 0; i < size && map_property_multi_tile_y(grid_offset); i++)
        grid_offset += GRID_OFFSET(0, -1);
    return grid_offset;
}

void draw_debug_tile(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;

    int DB2 = abs(debug_range_2) % 20;
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
    case 1: // BUILDING IDS
        if (b_id && b->tile.grid_offset() == grid_offset) {
            draw_building(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, {x - 15, y}, COLOR_MASK_GREEN);
        }

        if (b_id && map_property_is_draw_tile(grid_offset)) { // b->tile.grid_offset() == grid_offset
            bool red = !map_terrain_is(grid_offset, TERRAIN_BUILDING);
            debug_text(str, x0, y + 0, 0, "", b_id, red ? COLOR_LIGHT_RED : COLOR_WHITE);
            debug_text(str, x0, y + 10, 0, "", b->type, red ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
            if (!b->is_main())
                text_draw((uint8_t*)string_from_ascii("sub"), x0, y - 10, FONT_SMALL_OUTLINED, COLOR_RED);
        }
        break;
    case 2: // DRAW-TILES AND SIZES
        if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
            if (map_property_is_draw_tile(grid_offset)) {
                debug_text(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_GREEN);
                debug_text(str, x1, y + 10, 0, "", b->size, COLOR_WHITE);
            } else
                debug_text(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_RED);
        } else if (!map_property_is_draw_tile(grid_offset))
            debug_text(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_BLUE);
        break;
    case 3:                                                   // ROADS
        if (b_id && map_property_is_draw_tile(grid_offset)) { //&& b->tile.grid_offset() == grid_offset
            debug_text(str, x0, y + 5, 0, "", b->road_access.x(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
            debug_text(str, x0, y + 15, 0, "", b->road_access.y(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
            if (b->has_road_access) {
                auto tile_coords = mappoint_to_pixel(b->road_access);
                draw_building(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23,
                              tile_coords,
                              COLOR_MASK_GREEN);
            }
        }
        if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
            d = map_road_network_get(grid_offset);
            debug_text(str, x, y + 10, 10, "R", d, COLOR_WHITE);
        } else if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
            d = map_road_network_get(grid_offset);
            debug_text(str, x, y + 10, 10, "R", d, COLOR_LIGHT_BLUE);
        }
        break;
    case 4: // ROUTING DISTANCE
        d = map_routing_distance(grid_offset);
        if (d > 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_WHITE);
        else if (d == 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 5: // CITIZEN ROUTING GRID
        d = map_citizen_grid(grid_offset);
        if (d > 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_WHITE);
        else
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 6: // MOISTURE
        d = map_moisture_get(grid_offset);
        if (d & MOISTURE_GRASS)
            debug_text(str, x, y + 10, 0, "", d, COLOR_WHITE);
        else if (d & MOISTURE_TRANSITION)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
        else if (d & MOISTURE_SHORE_TALLGRASS)
            debug_text(str, x, y + 10, 0, "", d, COLOR_GREEN);
        break;
    case 7: // PROPER GRASS LEVEL
        d = map_grasslevel_get(grid_offset);
        if (d)
            debug_text(str, x, y + 10, 0, "", d, COLOR_GREEN);
        break;
    case 8: // FERTILITY & SOIL DEPLETION
        d = map_get_fertility(grid_offset, FERT_WITH_MALUS);
        if (d) {
            int n = map_get_fertility(grid_offset, FERT_NO_MALUS);
            if (d == n || map_terrain_is(grid_offset, TERRAIN_MEADOW))
                debug_text(str, x, y + 5, 0, "", d, COLOR_LIGHT_GREEN);
            else {
                debug_text(str, x, y + 5, 0, "", d, COLOR_LIGHT_BLUE);
                d = map_get_fertility(grid_offset, FERT_ONLY_MALUS);
                debug_text(str, x, y + 15, 0, "", d, COLOR_LIGHT_RED);
            }
        }
        break;
    case 9: // FLOODPLAIN SHORE ORDER
        d = map_get_floodplain_row(grid_offset);
        if (d > -1)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 10: // FLOODPLAIN TERRAIN FLAGS
        d = map_terrain_is(grid_offset, TERRAIN_BUILDING);
        if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD))
                    debug_text(str, x, y + 10, 0, "", d, 0xff777777);
                else if (map_building_at(grid_offset) > 0)
                    debug_text(str, x, y + 10, 0, "", d, 0xff550000);
            } else {
                if (map_terrain_is(grid_offset, TERRAIN_ROAD))
                    debug_text(str, x, y + 10, 0, "", d, 0xffffffff);
                else if (map_building_at(grid_offset) > 0)
                    debug_text(str, x, y + 10, 0, "", d, 0xffaa0000);
            }
        }
        if (map_terrain_is(grid_offset, TERRAIN_CANAL)) {
            int a = map_aqueduct_at(grid_offset);
            if (map_terrain_is(grid_offset, TERRAIN_WATER))
                debug_text(str, x, y + 10, 0, "", a, 0xff557777);
            else
                debug_text(str, x, y + 10, 0, "", a, 0xff5577ff);
        } else if (map_terrain_is(grid_offset, TERRAIN_IRRIGATION_RANGE)) {
            if (map_terrain_is(grid_offset, TERRAIN_WATER))
                debug_text(str, x, y + 10, 0, "", d, 0xff007777);
            else
                debug_text(str, x, y + 10, 0, "", d, 0xff00ffff);
        }
        break;
    case 11: // LABOR
        if (b_id && map_property_is_draw_tile(grid_offset)
            && (b->labor_category != (uint8_t)-1 || building_is_floodplain_farm(b))) {
            if (b->labor_category != category_for_building(b))
                debug_text(str, x0, y + 10, 10, "!!", b->labor_category, COLOR_RED); // incorrect category??
            else
                debug_text(str, x0, y + 10, 0, "", b->labor_category, COLOR_WHITE);
            debug_text(str, x1, y + 10, 0, "", b->houses_covered, COLOR_LIGHT_RED);
            debug_text(str, x0, y + 20, 0, "", b->num_workers, COLOR_LIGHT_BLUE);
            debug_text(str, x1 - 10, y + 20, 4, ":", b->worker_percentage(), COLOR_LIGHT_BLUE);
            //
            if (building_is_farm(b->type)) {
                debug_text(str,x1 + 40,y + 20,40,"fert.",map_get_fertility_for_farm(b->tile.grid_offset()),COLOR_FONT_ORANGE_LIGHT);
                debug_text(str, x0, y + 30, 0, "", b->data.industry.progress, COLOR_GREEN);
                debug_text(str, x1 + 10, y + 30, 4, ":", b->data.industry.progress / 20, COLOR_GREEN);
                debug_text(str, x1 + 40, y + 30, 40, "exp.", farm_expected_produce(b), COLOR_GREEN);
                if (building_is_floodplain_farm(b)) {
                    debug_text(str, x0, y + 40, 0, "", b->data.industry.labor_state, COLOR_WHITE);
                    debug_text(str, x1, y + 40, 0, "", b->data.industry.labor_days_left, COLOR_WHITE);
                }
            }
            if (b->data.entertainment.booth_corner_grid_offset) {
                debug_text(str, x0, y + 30, 0, "", b->data.entertainment.days1, COLOR_GREEN);
                debug_text(str, x1, y + 30, 0, "", b->data.entertainment.days2, COLOR_GREEN);
                debug_text(str, x0, y + 40, 0, "", b->data.entertainment.days3_or_play, COLOR_GREEN);
            }
        }
        break;
    case 12: // SPRITE FRAMES

        if (grid_offset == MAP_OFFSET(b->tile.x(), b->tile.y()))
            draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 3, {x - 15, y}, COLOR_MASK_GREEN);
        if (grid_offset == north_tile_grid_offset(b->tile.x(), b->tile.y()))
            ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, x - 15, y, COLOR_MASK_RED);
        d = map_sprite_animation_at(grid_offset);
        if (d) {
            string_from_int(str, d, 0);
            text_draw(str, x, y + 10, FONT_SMALL_OUTLINED, COLOR_WHITE);
        }

        // STATUES & MONUMENTS

        if (b_id && map_property_is_draw_tile(grid_offset)
            && (b->labor_category != -1 || building_is_floodplain_farm(b))) {
            switch (b->type) {
            case BUILDING_SMALL_STATUE:
            case BUILDING_MEDIUM_STATUE:
            case BUILDING_LARGE_STATUE:
                debug_text(str, x1, y + 10, 0, "", b->data.monuments.variant, COLOR_WHITE);
                break;
                //
            case BUILDING_TEMPLE_COMPLEX_OSIRIS:
            case BUILDING_TEMPLE_COMPLEX_RA:
            case BUILDING_TEMPLE_COMPLEX_PTAH:
            case BUILDING_TEMPLE_COMPLEX_SETH:
            case BUILDING_TEMPLE_COMPLEX_BAST:
                debug_text(str, x1, y + 10, 0, "", b->data.monuments.variant, COLOR_WHITE);
                debug_text(str, x1, y + 20, 0, "", b->data.monuments.temple_complex_attachments, COLOR_LIGHT_BLUE);
                break;
            }
        }
        break;
    case 13: // TERRAIN BIT FIELD
        debug_text(str, x, y + 10, 0, "", map_terrain_get(grid_offset), COLOR_LIGHT_BLUE);
        break;
    case 14: // IMAGE FIELD
        debug_text(str, x, y + 10, 0, "", map_image_at(grid_offset) - 14252, COLOR_LIGHT_RED);
        break;
    case 15: // MARSHLAND DEPLETION
        d = map_get_vegetation_growth(grid_offset);
        if (d != 255)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 16: // MARSHLAND
        d = map_terrain_is(grid_offset, TERRAIN_MARSHLAND);
        if (d != 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 17: // TERRAIN TYPE
        d = map_terrain_get(grid_offset);
        //            if (d != 0)
        debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
        break;
    case 18: // UNKNOWN SOIL GRID
        d = map_get_UNK04(grid_offset);
        if (d != 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    case 19: // UNKNOWN 32BIT GRID
        d = map_get_UNK03(grid_offset);
        if (d != 0)
            debug_text(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
        break;
    }
}
void draw_debug_figures(vec2i pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int figure_id = map_figure_id_get(grid_offset);
    while (figure_id) {
        figure* f = figure_get(figure_id);
        f->draw_debug();
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

void figure::draw_debug() {
    if (draw_debug_mode == 0)
        return;

    building* b = home();
    building* bdest = destination();

    uint8_t str[10];
    vec2i pixel;
    pixel = mappoint_to_pixel(map_point(tile.x(), tile.y()));
    adjust_pixel_offset(&pixel);
    pixel.x -= 10;
    pixel.y -= 80;
    int indent = 0;
    color col = COLOR_WHITE;

    switch (draw_debug_mode) {
    case 1: // ACTION & STATE IDS
        debug_text(str, pixel.x, pixel.y, indent, "", id, COLOR_WHITE);
        debug_text(str, pixel.x, pixel.y + 10, indent, "", type, COLOR_LIGHT_BLUE);
        debug_text(str, pixel.x, pixel.y + 20, indent, "", action_state, COLOR_LIGHT_RED);
        debug_text(str, pixel.x, pixel.y + 30, indent, "", wait_ticks, COLOR_WHITE);
        debug_text(str, pixel.x, pixel.y + 40, indent, "", roam_length, COLOR_WHITE);
        if (true) {
            vec2i tp = mappoint_to_pixel(tile);
            if (tile.grid_offset() != -1)
                debug_draw_tile_box(tp.x, tp.y, COLOR_LIGHT_BLUE, COLOR_GREEN);
        }
        pixel.y += 80;
        debug_text(str, pixel.x, pixel.y, indent, "", tile.x(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(str, pixel.x, pixel.y + 10, indent, "", tile.y(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(str, pixel.x, pixel.y + 20, indent, "", tile.grid_offset(), COLOR_FONT_MEDIUM_GRAY);
        debug_text(str, pixel.x, pixel.y + 30, indent, "", progress_on_tile, COLOR_FONT_MEDIUM_GRAY);
        debug_text(str, pixel.x + 30, pixel.y + 30, indent, "", routing_path_current_tile, COLOR_FONT_MEDIUM_GRAY);
        break;
    case FIGURE_DRAW_DEBUG_ROUTING:
        // draw path
        if (routing_path_id) { //&& (roam_length == max_roam_length || roam_length == 0)
            vec2i coords = mappoint_to_pixel(map_point(destination()->tile.x(), destination()->tile.y()));
            draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 3, coords);
            coords = mappoint_to_pixel(map_point(destination_tile.x(), destination_tile.y()));
            draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, coords);
            int tx = tile.x();
            int ty = tile.y();
            coords = mappoint_to_pixel(map_point(tx, ty));
            ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
            int starting_tile_index = routing_path_current_tile;
            if (progress_on_tile >= 0 && progress_on_tile < 8) { // adjust half-tile offset
                starting_tile_index--;
            }

            for (int i = starting_tile_index; i < routing_path_length; i++) {
                auto pdir = figure_route_get_direction(routing_path_id, i);
                switch (pdir) {
                case 0: ty--; break;
                case 1: tx++; ty--; break;
                case 2: tx++; break;
                case 3: tx++; ty++; break;
                case 4: ty++; break;
                case 5: tx--; ty++; break;
                case 6: tx--; break;
                case 7: tx--; ty--; break;
                }
                coords = mappoint_to_pixel(map_point(tx, ty));
                ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
            }
        }

        // the rest of values, on top of all else
        if (routing_path_id) {
            debug_text(str, pixel.x, pixel.y, indent, "", routing_path_id, COLOR_LIGHT_RED);
            debug_text(str, pixel.x, pixel.y + 10, indent, "", routing_path_current_tile, COLOR_LIGHT_RED);
            debug_text(str, pixel.x, pixel.y + 20, indent, "", routing_path_length, COLOR_LIGHT_RED);
        } else {
            debug_text(str, pixel.x, pixel.y, indent, "", roam_length, COLOR_LIGHT_BLUE);
            debug_text(str, pixel.x, pixel.y + 10, indent, "", roam_wander_freely, COLOR_LIGHT_BLUE);
            debug_text(str, pixel.x, pixel.y + 20, indent, "", max_roam_length, COLOR_LIGHT_BLUE);
        }

        debug_text(str, pixel.x, pixel.y + 30, indent, "", terrain_usage, COLOR_WHITE);

        switch (direction) {
        case DIR_FIGURE_CAN_NOT_REACH:
            debug_text(str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_LIGHT_RED);
            break;
        case DIR_FIGURE_REROUTE:
            debug_text(str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_LIGHT_BLUE);
            break;
        case DIR_FIGURE_NONE:
            debug_text(str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_GREEN);
            break;
        default:
            debug_text(str, pixel.x, pixel.y + 40, indent, "", direction, COLOR_WHITE);
            break;
        }
        debug_text(str, pixel.x + 10, pixel.y + 40, 5, ":", roam_turn_direction, roam_turn_direction ? COLOR_LIGHT_BLUE : COLOR_FONT_MEDIUM_GRAY);

        pixel.y += 50;
        string_from_int(str, progress_on_tile, 0);
        text_draw(str, pixel.x, pixel.y + 30, FONT_SMALL_PLAIN, 0);
        break;
    case 3: // RESOURCE CARRY
        if (resource_id) {
            debug_text(str, pixel.x, pixel.y, indent, "", resource_id, COLOR_GREEN);
            debug_text(str, pixel.x, pixel.y + 10, indent, "", resource_amount_full, resource_amount_full ? COLOR_GREEN : COLOR_FONT_MEDIUM_GRAY);
            debug_text(str, pixel.x, pixel.y + 20, indent, "", collecting_item_id, collecting_item_id ? COLOR_LIGHT_BLUE : COLOR_FONT_MEDIUM_GRAY);
        }
        break;
    case 4: // BUILDING DATA
        debug_text(str, pixel.x + 0, pixel.y, indent, "", homeID(), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(str, pixel.x + 20, pixel.y, 8, ":", home()->get_figure_slot(this), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(str, pixel.x + 0, pixel.y + 10, indent, "", destinationID(), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(str, pixel.x + 20, pixel.y + 10, 8, ":", destination()->get_figure_slot(this), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(str, pixel.x + 0, pixel.y + 20, indent, "", immigrant_homeID(), immigrant_homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        debug_text(str, pixel.x + 20, pixel.y + 20, 8, ":", immigrant_home()->get_figure_slot(this), immigrant_homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
        break;
    case 5: // FESTIVAL
        pixel.y += 30;
        debug_text(str, pixel.x, pixel.y, indent, "", unk_ph1_269, COLOR_WHITE);
        debug_text(str, pixel.x, pixel.y + 10, indent, "", unk_ph4_ffff, COLOR_WHITE);
        debug_text(str, pixel.x, pixel.y + 20, indent, "", festival_remaining_dances, COLOR_WHITE);
        break;
    case 6: // CROSS-COUNTRY MOVEMENT
        if (use_cross_country) {
            vec2i tp;
            if (tile.grid_offset() != -1) {
                tp = mappoint_to_pixel(tile);
                debug_draw_tile_box(tp.x, tp.y, COLOR_NULL, COLOR_GREEN);
            }
            if (destination_tile.grid_offset() != -1) {
                tp = mappoint_to_pixel(destination_tile);
                debug_draw_tile_box(tp.x, tp.y, COLOR_NULL, COLOR_FONT_YELLOW);
            }
        }
        col = use_cross_country ? COLOR_WHITE : COLOR_FONT_MEDIUM_GRAY;
        debug_text(str, pixel.x, pixel.y, indent, "", use_cross_country);
        pixel.y += 10;
        debug_text(str, pixel.x, pixel.y, indent, "", cc_direction, col);
        pixel.y += 10;

        debug_text(str, pixel.x, pixel.y, indent, "", cc_coords.x, col);
        debug_text(str, pixel.x + 40, pixel.y, indent, "", cc_coords.y, col);
        pixel.y += 10;

        debug_text(str, pixel.x, pixel.y, indent, "", cc_destination.x, col);
        debug_text(str, pixel.x + 40, pixel.y, indent, "", cc_destination.y, col);
        pixel.y += 10;

        debug_text(str, pixel.x, pixel.y, indent, "", cc_delta_xy, col);
        pixel.y += 10;
        debug_text(str, pixel.x, pixel.y, indent, "", cc_delta.x, col);
        debug_text(str, pixel.x + 40, pixel.y, indent, "", cc_delta.y, col);
        pixel.y += 10;
        break;
    }
}

const char* get_terrain_type(char* buffer, const char* def, map_point tile) {
    int type = map_terrain_get(tile.grid_offset());
    strcat(buffer, def);
    if (type & TERRAIN_DUNE) strcat(buffer, "dune,");
    if (type & TERRAIN_TREE) strcat(buffer, "tree,");
    if (type & TERRAIN_ROCK) strcat(buffer, "rock,");
    if (type & TERRAIN_WATER) strcat(buffer, "water,");
    if (type & TERRAIN_BUILDING) {
        bstring32 bstr;
        building *b = building_get(map_building_at(tile));
        bstr.printf("bld:%d,", b ? b->type : -1);
        strcat(buffer, bstr.c_str());
    }
    if (type & TERRAIN_SHRUB) strcat(buffer, "shrub,");
    if (type & TERRAIN_GARDEN) strcat(buffer, "garden,");
    if (type & TERRAIN_ROAD) strcat(buffer, "road,");
    if (type & TERRAIN_GROUNDWATER) strcat(buffer, "grdwater,");
    if (type & TERRAIN_CANAL) strcat(buffer, "canal,");
    if (type & TERRAIN_ELEVATION) strcat(buffer, "elevat,");
    if (type & TERRAIN_ACCESS_RAMP) strcat(buffer, "ramp,");
    if (type & TERRAIN_MEADOW) strcat(buffer, "meadow,");
    if (type & TERRAIN_RUBBLE) strcat(buffer, "rubble,");
    if (type & TERRAIN_FOUNTAIN_RANGE) strcat(buffer, "fountain,");
    if (type & TERRAIN_WALL) strcat(buffer, "wall,");
    if (type & TERRAIN_GATEHOUSE) strcat(buffer, "gate,");
    if (type & TERRAIN_FLOODPLAIN) strcat(buffer, "flood,");
    if (type & TERRAIN_FERRY_ROUTE) strcat(buffer, "wtrroute,");

    return buffer;
}

bool g_debug_show_opts[e_debug_opt_size] = {0};

void draw_debug_ui(int x, int y) {
    uint8_t str[300];

    /////// DEBUG PAGES NAME
    if (g_debug_show_opts[e_debug_show_pages]) {
        y += 13;
        int DB1 = abs(debug_range_1) % 7;
        int DB2 = abs(debug_range_2) % 20;

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
        case 1:
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
            text_draw((uint8_t*)string_from_ascii("SPRITE FRAMES / STATUES AND MONUMENTS"),
                      x,
                      y + 10,
                      FONT_SMALL_OUTLINED,
                      col);
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
        const auto& time = gametime();

        debug_text(str, x, y + 15, 50, "tick:", time.tick);
        debug_text(str, x + 80, y + 15, 50, "iscycle:", tick_is_flood_cycle());
        debug_text(str, x, y + 25, 50, "cycle:", floods_current_cycle());
        debug_text(str, x + 90, y + 25, 60, "frame:", floods_current_subcycle());

        debug_text(str, x, y + 35, 50, "day:", time.day);
        debug_text(str, x, y + 45, 50, "month:", time.month);
        debug_text(str, x, y + 55, 50, "year:", time.year);
        debug_text(str, x, y + 65, 60, "abs. tick:", game_time_absolute_tick()); // absolute tick of the year
        debug_text(str, x, y + 75, 60, "abs. day:", game_time_absolute_day());   // absolute day of the year
        y += 80;
    }

    /////// BUILD PLANNER
    if (g_debug_show_opts[e_debug_show_build_planner]) {
        int cl = 90;
        debug_text(str, x, y + 15, cl, "type:", Planner.build_type);
        debug_text(str, x, y + 25, cl, "in progress:", Planner.in_progress);
        debug_text(str, x, y + 35, cl, "draw as con.:", Planner.draw_as_constructing);
        debug_text(str, x, y + 45, cl, "orientation:", Planner.absolute_orientation);
        debug_text(str, x + 40, y + 45, cl, "", Planner.relative_orientation);
        debug_text(str, x, y + 55, cl, "variant:", Planner.variant);
        debug_text(str, x, y + 65, cl, "start:", Planner.start.x());
        debug_text(str, x + 40, y + 65, cl, "", Planner.start.y());
        debug_text(str, x, y + 75, cl, "end:", Planner.end.x());
        debug_text(str, x + 40, y + 75, cl, "", Planner.end.y());

        screen_tile screen_start = mappoint_to_screentile(Planner.start);
        screen_tile screen_end = mappoint_to_screentile(Planner.end);
        debug_text(str, x + 170, y + 65, 60, "screen:", screen_start.x);
        debug_text(str, x + 170 + 40, y + 65, 60, "", screen_start.y);
        debug_text(str, x + 170, y + 75, 60, "screen:", screen_end.x);
        debug_text(str, x + 170 + 40, y + 75, 60, "", screen_end.y);

        //        screen_tile screen_start2 = attempt_mappoint_to_screen(Planner.start);
        //        screen_tile screen_end2 = attempt_mappoint_to_screen(Planner.end);
        //        color col = (screen_start != screen_start2) ? COLOR_LIGHT_RED : COLOR_LIGHT_GREEN;
        //        draw_debug_line(str, x + 300, y + 65, 60, "direct:", screen_start2.x, col); draw_debug_line(str, x +
        //        300 + 40, y + 65, 60, "", screen_start2.y, col); col = (screen_end != screen_end2) ? COLOR_LIGHT_RED :
        //        COLOR_LIGHT_GREEN; draw_debug_line(str, x + 300, y + 75, 60, "direct:", screen_end2.x, col);
        //        draw_debug_line(str, x + 300 + 40, y + 75, 60, "", screen_end2.y, col);

        debug_text(str, x, y + 85, cl, "cost:", Planner.total_cost);
        y += 90;
    }

    /////// RANDOM
    if (false) {
        auto randm = random_data_struct();

        int cl = 60;
        debug_text(str, x, y + 15, cl, "iv1:", randm->iv1);
        debug_text(str, x, y + 25, cl, "iv2:", randm->iv2);
        debug_text(str, x, y + 35, cl, "1_3b:", randm->random1_3bit);
        debug_text(str, x, y + 45, cl, "1_7b:", randm->random1_7bit);
        debug_text(str, x, y + 55, cl, "1_15b:", randm->random1_15bit);
        debug_text(str, x, y + 65, cl, "2_3b:", randm->random2_3bit);
        debug_text(str, x, y + 75, cl, "2_7b:", randm->random2_7bit);
        debug_text(str, x, y + 85, cl, "2_15b:", randm->random2_15bit);

        debug_text(str, x, y + 105, cl, "scum:", anti_scum_random_15bit(false));
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

        if (city_gods_is_known(GOD_OSIRIS) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 15, c0, c1, "Osiris:", city_data.religion.gods[0].mood, city_data.religion.gods[0].target_mood);
            debug_text_dual_left(str, x + c2, y + 15, 0, c1, "", city_data.religion.gods[0].wrath_bolts, city_data.religion.gods[0].happy_ankhs);
            debug_text(str, x + c3, y + 15, cl, "", building_count_total(BUILDING_SHRINE_OSIRIS));
            debug_text(str, x + c4, y + 15, cl, "", building_count_active(BUILDING_TEMPLE_OSIRIS));
            debug_text(str, x + c5, y + 15, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_OSIRIS));
            debug_text(str, x + c6, y + 15, c7, "%", city_culture_coverage_religion(GOD_OSIRIS));
            debug_text(str, x + c8, y + 15, cl, "", city_data.religion.gods[0].months_since_festival);
        }

        if (city_gods_is_known(GOD_RA) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 25, c0, c1, "Ra:", city_data.religion.gods[1].mood, city_data.religion.gods[1].target_mood);
            debug_text_dual_left(str, x + c2, y + 25, 0, c1, "", city_data.religion.gods[1].wrath_bolts, city_data.religion.gods[1].happy_ankhs);
            debug_text(str, x + c3, y + 25, cl, "", building_count_total(BUILDING_SHRINE_RA));
            debug_text(str, x + c4, y + 25, cl, "", building_count_active(BUILDING_TEMPLE_RA));
            debug_text(str, x + c5, y + 25, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_RA));
            debug_text(str, x + c6, y + 25, c7, "%", city_culture_coverage_religion(GOD_RA));
            debug_text(str, x + c8, y + 25, cl, "", city_data.religion.gods[1].months_since_festival);
        }

        if (city_gods_is_known(GOD_PTAH) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 35, c0, c1, "Ptah:", city_data.religion.gods[2].mood, city_data.religion.gods[2].target_mood);
            debug_text_dual_left(str, x + c2, y + 35, 0, c1, "", city_data.religion.gods[2].wrath_bolts, city_data.religion.gods[2].happy_ankhs);
            debug_text(str, x + c3, y + 35, cl, "", building_count_total(BUILDING_SHRINE_PTAH));
            debug_text(str, x + c4, y + 35, cl, "", building_count_active(BUILDING_TEMPLE_PTAH));
            debug_text(str, x + c5, y + 35, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_PTAH));
            debug_text(str, x + c6, y + 35, c7, "%", city_culture_coverage_religion(GOD_PTAH));
            debug_text(str, x + c8, y + 35, cl, "", city_data.religion.gods[2].months_since_festival);
        }

        if (city_gods_is_known(GOD_SETH) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 45, c0, c1, "Seth:", city_data.religion.gods[3].mood, city_data.religion.gods[3].target_mood);
            debug_text_dual_left(str, x + c2, y + 45, 0, c1, "", city_data.religion.gods[3].wrath_bolts, city_data.religion.gods[3].happy_ankhs);
            debug_text(str, x + c3, y + 45, cl, "", building_count_total(BUILDING_SHRINE_SETH));
            debug_text(str, x + c4, y + 45, cl, "", building_count_active(BUILDING_TEMPLE_SETH));
            debug_text(str, x + c5, y + 45, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_SETH));
            debug_text(str, x + c6, y + 45, c7, "%", city_culture_coverage_religion(GOD_SETH));
            debug_text(str, x + c8, y + 45, cl, "", city_data.religion.gods[3].months_since_festival);
        }

        if (city_gods_is_known(GOD_BAST) != GOD_STATUS_UNKNOWN) {
            debug_text_dual_left(str, x, y + 55, c0, c1, "Bast:", city_data.religion.gods[4].mood, city_data.religion.gods[4].target_mood);
            debug_text_dual_left(str, x + c2, y + 55, 0, c1, "", city_data.religion.gods[4].wrath_bolts, city_data.religion.gods[4].happy_ankhs);
            debug_text(str, x + c3, y + 55, cl, "", building_count_total(BUILDING_SHRINE_BAST));
            debug_text(str, x + c4, y + 55, cl, "", building_count_active(BUILDING_TEMPLE_BAST));
            debug_text(str, x + c5, y + 55, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_BAST));
            debug_text(str, x + c6, y + 55, c7, "%", city_culture_coverage_religion(GOD_BAST));
            debug_text(str, x + c8, y + 55, cl, "", city_data.religion.gods[4].months_since_festival);
        }

        cl = 180;
        debug_text(str, x, y + 75, cl, "150% export profits:", city_data.religion.ra_150_export_profits_months_left);
        debug_text(str, x, y + 85, cl, "No traders:", city_data.religion.ra_no_traders_months_left);
        debug_text(str, x, y + 95, cl, "Slightly increased trades:", city_data.religion.ra_slightly_increased_trading_months_left);
        debug_text(str, x, y + 105, cl, "Slightly reduced trades:", city_data.religion.ra_slightly_reduced_trading_months_left);
        debug_text(str, x, y + 115, cl, "Harshly reduced trades:", city_data.religion.ra_harshly_reduced_trading_months_left);

        debug_text(str, x, y + 125, cl, "Enemy troops kill:", city_data.religion.seth_crush_enemy_troops);
        debug_text(str, x, y + 135, cl, "Player troops protection:", city_data.religion.seth_protect_player_troops);

        debug_text(str, x, y + 145, cl, "Double farm yields:", city_data.religion.osiris_double_farm_yield);
        debug_text(str, x, y + 155, cl, "Floods will destroy farms:", city_data.religion.osiris_flood_will_destroy_active);
        y += 170;
    }

    if (g_debug_show_opts[e_debug_show_migration]) {
        int cl = 180;
        debug_text(str, x, y + 1, cl, "invading_cap:", city_data.migration.invading_cap);
        debug_text(str, x, y + 13, cl, "migration_cap:", city_data.migration.migration_cap);
        debug_text(str, x, y + 25, cl, "percentage_by_sentiment:", city_data.migration.percentage_by_sentiment);
        debug_text(str, x, y + 37, cl, "emigration_message_shown:", city_data.migration.emigration_message_shown);
        debug_text(str, x, y + 49, cl, "newcomers:", city_data.migration.newcomers);
        debug_text(str, x, y + 61, cl, "percentage:", city_data.migration.percentage);
        debug_text(str, x, y + 73, cl, "no_immigration_cause:", city_data.migration.no_immigration_cause);
        debug_text(str, x, y + 85, cl, "refused_immigrants_today:", city_data.migration.refused_immigrants_today);
        debug_text(str, x, y + 97, cl, "emigrated_today:", city_data.migration.emigrated_today);
        debug_text(str, x, y + 109, cl, "immigrated_today:", city_data.migration.immigrated_today);
        debug_text(str, x, y + 121, cl, "emigration_queue_size:", city_data.migration.emigration_queue_size);
        debug_text(str, x, y + 133, cl, "immigration_queue_size:", city_data.migration.immigration_queue_size);
        debug_text(str, x, y + 145, cl, "immigration_duration:", city_data.migration.immigration_duration);
        debug_text(str, x, y + 157, cl, "emigration_amount_per_batch:", city_data.migration.emigration_amount_per_batch);
        debug_text(str, x, y + 169, cl, "emigration_duration:", city_data.migration.emigration_duration);
        debug_text(str, x, y + 181, cl, "immigration_amount_per_batch:", city_data.migration.immigration_amount_per_batch);
        y += 200;
    }

    if (g_debug_show_opts[e_debug_show_sentiment]) {
        int cl = 180;
        debug_text(str, x, y + 1, cl, "value:", city_data.sentiment.value);
        debug_text(str, x, y + 13, cl, "previous_value:", city_data.sentiment.previous_value);
        debug_text(str, x, y + 25, cl, "message_delay:", city_data.sentiment.message_delay);
        debug_text(str, x, y + 37, cl, "include_tents:", city_data.sentiment.include_tents);
        debug_text(str, x, y + 49, cl, "unemployment:", city_data.sentiment.unemployment);
        debug_text(str, x, y + 61, cl, "wages:", city_data.sentiment.wages);
        debug_text(str, x, y + 73, cl, "low_mood_cause:", city_data.sentiment.low_mood_cause);
        debug_text(str, x, y + 85, cl, "protesters:", city_data.sentiment.protesters);
        debug_text(str, x, y + 97, cl, "criminals:", city_data.sentiment.criminals);
        debug_text(str, x, y + 109, cl, "can_create_mugger:", city_data.sentiment.can_create_mugger);
        debug_text(str, x, y + 121, cl, "can_create_protestor:", city_data.sentiment.can_create_protestor);
        debug_text(str, x, y + 133, cl, "last_mugger_message:", city_data.sentiment.last_mugger_message);
        debug_text(str, x, y + 145, cl, "contribution_taxes:", city_data.sentiment.contribution_taxes);
        debug_text(str, x, y + 157, cl, "contribution_wages:", city_data.sentiment.contribution_wages);
        debug_text(str, x, y + 169, cl, "contribution_employment:", city_data.sentiment.contribution_employment);
        debug_text(str, x, y + 181, cl, "penalty_tents:", city_data.sentiment.penalty_tents);
        debug_text(str, x, y + 193, cl, "monuments:", city_data.sentiment.monuments);
        debug_text(str, x, y + 205, cl, "religion_coverage:", city_data.sentiment.religion_coverage);
        y += 210;
    }

    /////// FLOODS
    if (g_debug_show_opts[e_debug_show_floods]) {
        const auto& floods = floodplain_data();

        double _c_curr = floods_current_cycle();
        double _c_start = floods_start_cycle();
        double _c_end = floods_end_cycle();

        int _c_period_last = floods_period_length(false);
        int _c_period_next = floods_period_length(true);

        float rc_curr = fmod(_c_curr, CYCLES_IN_A_YEAR);
        float rc_start = fmod(_c_start, CYCLES_IN_A_YEAR);
        float rc_end = fmod(_c_end, CYCLES_IN_A_YEAR);
        if (rc_curr < 0.1 && game_time_month() > 1)
            rc_curr = CYCLES_IN_A_YEAR;

        // floodplains timeline (yearly)
        double additional_abs_ticks = CYCLES_IN_A_YEAR * (double)game_time_year_since_start();
        auto dot = string_from_ascii(",");
        for (int i = 0; i < 392; ++i) {
            text_draw(dot, x + i - 1, y + 15, FONT_SMALL_PLAIN, 0);
        }
        for (int i = 0; i < 392; ++i) {
            int abs_i = i + additional_abs_ticks;
            text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_WHITE);

            if ((i > rc_start - 28 && i < rc_end + 28)
                || (i > rc_start - 28 - CYCLES_IN_A_YEAR && i < rc_end + 28 - CYCLES_IN_A_YEAR)
                || (i > rc_start - 28 + CYCLES_IN_A_YEAR && i < rc_end + 28 + CYCLES_IN_A_YEAR))
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_FONT_ORANGE_LIGHT);

            if ((i > rc_start && i < rc_end) || (i > rc_start - CYCLES_IN_A_YEAR && i < rc_end - CYCLES_IN_A_YEAR)
                || (i > rc_start + CYCLES_IN_A_YEAR && i < rc_end + CYCLES_IN_A_YEAR))
                text_draw(dot, x + i, y + 15, FONT_SMALL_PLAIN, COLOR_RED);

            if (floods_debug_period() > 0) {
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
        debug_text(str, x + rc_curr + 54, y + 25, 5, ":", floods.state); // current cycle

        debug_text(str, x, y + 35, 60, "debug:", floods_debug_period());
        debug_text(str, x, y + 45, 60, "ftick:", floods_fticks());

        y += 50;

        int cl = 60;
        debug_text(str, x, y + 15, cl + 15, "CURRENT:", _c_curr);             // current cycle
        debug_text(str, x + 105, y + 15, 10, "/", floods_current_subcycle()); // current cycle
        debug_text(str, x, y + 25, cl, "t-49:", _c_start - 49);               // 49 cycles prior
        debug_text(str, x, y + 35, cl, "t-28:", _c_start - 28);               // 28 cycles prior
        debug_text(str, x, y + 45, cl, "  START", _c_start);                  // flood start
        if (floods_debug_period() > 0) {
            debug_text(str, x, y + 55, cl, "rest:", _c_start + _c_period_next);  // first rest period
            debug_text(str, x, y + 65, cl, "retract:", _c_end - _c_period_next); // first rest period
        } else {
            debug_text(str, x, y + 55, cl, "rest:", _c_start + _c_period_last);  // first rest period
            debug_text(str, x, y + 65, cl, "retract:", _c_end - _c_period_last); // first rest period
        }
        debug_text(str, x, y + 75, cl, "    END", _c_end);    // flood end
        debug_text(str, x, y + 85, cl, "t+23:", _c_end + 23); // lands farmable again
        debug_text(str, x, y + 95, cl, "t+28:", _c_end + 28); // lands farmable again

        cl = 100;
        y += 10;
        debug_text(str, x, y + 105, cl, "season_initial:", floods.season_initial);
        debug_text(str, x, y + 115, cl, "duration_initial:", floods.duration_initial);
        debug_text(str, x, y + 125, cl, "quality_initial:", floods.quality_initial);
        debug_text(str, x, y + 135, cl, "season:", floods.season);
        debug_text(str, x, y + 145, cl, "duration:", floods.duration);
        debug_text(str, x, y + 155, cl, "quality:", floods.quality);
        debug_text(str, x, y + 165, cl, "(unk00):", floods.unk00);
        debug_text(str, x, y + 175, cl, "quality_next:", floods.quality_next);
        debug_text(str, x, y + 185, cl, "quality_last:", floods.quality_last);

        cl = 60;
        debug_text(str, x, y + 205, cl, "progress:", floods.flood_progress);   // status 30 (???)
        debug_text(str, x, y + 215, cl, "(unk01):", floods.unk01);             // ???
        debug_text(str, x, y + 225, cl, "state:", floods.state);               // floodplains state
        debug_text(str, x, y + 235, cl, "width:", floods.floodplain_width);    // status 10 (???)
        debug_text(str, x, y + 245, cl, "hasplains:", floods.has_floodplains); // status 10 (???)
        y += 350;
    }

    /////// CAMERA
    if (g_debug_show_opts[e_debug_show_camera]) {
        map_point camera_tile = city_view_get_camera_mappoint();
        vec2i camera_pixels = camera_get_pixel_offset_internal();

        vec2i min_pos, max_pos;
        city_view_get_camera_scrollable_pixel_limits(min_pos, max_pos);

        auto& viewdata = city_view_data_unsafe();
        int real_max_x;
        int real_max_y;
        city_view_get_camera_max_tile(&real_max_x, &real_max_y);

        int max_x_pixel_offset;
        int max_y_pixel_offset;
        city_view_get_camera_max_pixel_offset(&max_x_pixel_offset, &max_y_pixel_offset);

        y += 30;
        debug_text_dual_left(str, x, y - 15, 90, 40, "---min:", min_pos.x, min_pos.y);
        debug_text_dual_left(str, x, y - 5, 90, 40, "camera:", viewdata.camera.position.x, viewdata.camera.position.y);
        debug_text_dual_left(str, x, y + 5, 90, 40, "---max:", max_pos.x, max_pos.y);

        debug_text_dual_left(str, x, y + 25, 90, 40, "---min:", SCROLL_MIN_SCREENTILE_X, SCROLL_MIN_SCREENTILE_Y);
        debug_text_dual_left(str, x, y + 35, 90, 40, "tile:", camera_tile.x(), camera_tile.y());
        debug_text_dual_left(str, x, y + 45, 90, 40, "---max:", real_max_x, real_max_y);

        debug_text_dual_left(str, x, y + 65, 90, 40, "---min:", 0, 0);
        debug_text_dual_left(str, x, y + 75, 90, 40, "pixel:", camera_pixels.x, camera_pixels.y);
        debug_text_dual_left(str, x, y + 85, 90, 40, "---max:", max_x_pixel_offset, max_y_pixel_offset);

        debug_text_dual_left(str, x, y + 105, 90, 40, "v.tiles:", viewdata.viewport.size_pixels.x / 60, viewdata.viewport.size_pixels.y / 30);
        debug_text_dual_left(str, x, y + 115, 90, 40, "v.pixels:", viewdata.viewport.size_pixels.y, viewdata.viewport.size_pixels.y);

        debug_text(str, x, y + 125, 50, "zoom:", zoom_get_percentage());
        debug_text_float(str, x, y + 125, 50 + 40, "", zoom_get_scale());

        debug_text_float(str, x, y + 135, 50, "target:", zoom_debug_target());
        debug_text_float(str, x + 100, y + 135, 50, "delta:", zoom_debug_delta());

        vec2i pixel = {mouse_get()->x, mouse_get()->y};
        debug_text(str, x, y + 145, 50, "mouse:", pixel.x);
        debug_text(str, x + 40, y + 145, 50, "", pixel.y);

        vec2i viewp = pixel_to_viewport_coord(pixel);
        debug_text(str, x, y + 155, 50, "viewp:", viewp.x);
        debug_text(str, x + 40, y + 155, 50, "", viewp.y);

        camera_coordinate coord = pixel_to_camera_coord(pixel, false);
        debug_text(str, x, y + 165, 50, "coord:", coord.x);
        debug_text(str, x + 40, y + 165, 50, "", coord.y);

        screen_tile screen = pixel_to_screentile(pixel);
        debug_text(str, x, y + 175, 50, "tile:", screen.x);
        debug_text(str, x + 40, y + 175, 50, "", screen.y);

        vec2i offset = {coord.x % TILE_WIDTH_PIXELS, coord.y % TILE_HEIGHT_PIXELS};
        debug_text(str, x, y + 185, 50, "offset:", offset.x);
        debug_text(str, x + 40, y + 185, 50, "", offset.y);

        map_point point = screentile_to_mappoint(screen);
        debug_text(str, x, y + 195, 50, "point:", point.x());
        debug_text(str, x + 40, y + 195, 50, "", point.y());
        debug_text(str, x + 80, y + 195, 50, "", point.grid_offset());

        char type_str[256] = {0};
        debug_text_a(str, x + 180, y + 195, 50, get_terrain_type(type_str, "type: ", point));
        pixel = mappoint_to_pixel(point);
        debug_text(str, x, y + 205, 50, "pixel:", pixel.x);
        debug_text(str, x + 40, y + 205, 50, "", pixel.y);

        //        if (point.grid_offset() != -1)
        //            debug_draw_tile_box(pixel.x, pixel.y);

        //        pixel = mappoint_to_pixel(screentile_to_mappoint(city_view_data_unsafe()->camera.tile_internal));
        //        debug_draw_tile_box(pixel.x, pixel.y);

        y += 200;
    }

    /////// TUTORIAL
    if (g_debug_show_opts[e_debug_show_tutorial]) {
        auto flags = tutorial_flags_struct();
        struct tutopt { const char *optname; bool value; };
        for (int i = 0; i < 41; i++) {
            tutopt f{"", flags->pharaoh.flags[i]};
            switch (i) {
            case 0:
                f = { "1:fire", flags->tutorial_1.fire };
                break;
            case 1:
                f = { "1:pop_150", flags->tutorial_1.population_150_reached };
                break;
            case 2:
                f = { "1:meat_400", flags->tutorial_1.gamemeat_400_stored };
                break;
            case 3:
                f = { "1:collapse", flags->tutorial_1.collapse };
                break;
            case 4:
                f = { "2:gold_500", flags->tutorial_2.gold_mined_500 };
                break;
            case 5:
                f = { "2:temples_done", flags->tutorial_2.temples_built };
                break;
            case 6:
                f = { "2:crime", flags->tutorial_2.crime };
                break;
            case 7:
                f = { "3:figs_800", flags->tutorial_3.figs_800_stored };
                break;
            case 8:
                f = { "3:pottery_200", flags->tutorial_3.pottery_made };
                break;
            case 9:
                f = { "4:disease", flags->tutorial_3.disease };
                break;
            case 10:
                f = { "4:beer_300", flags->tutorial_4.beer_made };
                break;
            case 11:
                f = { "4:apartment", flags->pharaoh.spacious_apartment };
                break;
            case 15:
                f = { "tut1 start", flags->pharaoh.tut1_start };
                break;
            case 16:
                f = { "tut2 start", flags->pharaoh.tut2_start };
                break;
            case 17:
                f = { "tut3 start", flags->pharaoh.tut3_start };
                break;
            case 18:
                f = { "tut4 start", flags->pharaoh.tut4_start };
                break;
            case 19:
                f = { "tut5 start", flags->pharaoh.tut5_start };
                break;
            case 20:
                f = { "tut6 start", flags->pharaoh.tut6_start };
                break;
            case 21:
                f = { "tut7 start", flags->pharaoh.tut7_start };
                break;
            case 22:
                f = { "tut8 start" , flags->pharaoh.tut8_start };
                break;
            }

            int color = f.value ? COLOR_GREEN : COLOR_WHITE;
            text_draw((uint8_t*)string_from_ascii(f.optname), x + 3, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
            text_draw((uint8_t*)string_from_ascii(":"), x + 3 + 20, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
            text_draw((uint8_t*)string_from_ascii(f.value ? "yes" : "no"), x + 3 + 45, y + 115 + i * 10, FONT_SMALL_OUTLINED, color);
        }
    }
}