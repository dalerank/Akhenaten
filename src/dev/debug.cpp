#include "debug.h"

#include <cmath>

#include <graphics/text.h>
#include <core/string.h>

#include <graphics/image.h>
#include <core/image_group.h>

#include <city/view/lookup.h>
#include <widget/city/building_ghost.h>
#include <map/building.h>
#include <map/property.h>
#include <map/terrain.h>
#include <map/road_network.h>
#include <map/routing/routing.h>
#include <map/moisture.h>
#include <map/floodplain.h>
#include <map/aqueduct.h>
#include <city/data_private.h>
#include <building/industry.h>
#include <map/sprite.h>
#include <map/image.h>
#include <map/vegetation.h>

#include <figure/route.h>
#include <map/figure.h>
#include <game/time.h>
#include <building/construction/build_planner.h>
#include <core/random.h>
#include <city/gods.h>
#include <building/count.h>
#include <city/culture.h>
#include <city/floods.h>
#include <game/tutorial.h>
#include <map/tiles.h>

int debug_range_1 = 0;
int debug_range_2 = 0;
int debug_range_3 = 0;
int debug_range_4 = 0;

void handle_debug_hotkeys(const hotkeys *h) {
    if (h->debug_1_up)
        debug_range_1+=1;
    if (h->debug_1_down)
        debug_range_1-=1;
    if (h->debug_2_up)
        debug_range_2+=1;
    if (h->debug_2_down)
        debug_range_2-=1;
//    if (debug_range_1 < 0)
//        debug_range_1 = 0;
//    if (debug_range_1 > 20)
//        debug_range_1 = 20;
}

void draw_debug_line(uint8_t* str, int x, int y, int indent, const char *text, int value, color_t color) {
    text_draw_shadow(string_from_ascii(text), x, y, color);
    string_from_int(str, value, 0);
    text_draw_shadow(str, x + indent, y, color);
}
void draw_debug_line_float(uint8_t* str, int x, int y, int indent, const char *text, double value, color_t color) {
    text_draw_shadow(string_from_ascii(text), x, y, color);
    string_from_int(str, value, 0);
    int l = string_length(str);
    auto p = &str[l];
    string_copy(string_from_ascii("."), p, 2);
    string_from_int(&str[l+1], (double)(value - (double)(int)value) * 100.0f, 0);
    text_draw_shadow(str, x + indent, y, color);
}
void draw_debug_line_double_left(uint8_t* str, int x, int y, int indent, int indent2, const char *text, int value1, int value2, color_t color) {
    text_draw_shadow(string_from_ascii(text), x, y, color);
    string_from_int(str, value1, 0);
    text_draw_shadow_left(str, x + indent, y, color);
    string_from_int(str, value2, 0);
    text_draw_shadow_left(str, x + indent + indent2, y, color);
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
void draw_debug_tile(pixel_coordinate pixel, map_point point) {
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
    building *b = building_get(b_id);

    int x0 = x + 8;
    int x1 = x0 + 30;
    int x2 = x1 + 30;
    x += 15;

    switch (DB2) {
        default:
            break;
        case 1: // BUILDING IDS
            if (b_id && b->tile.grid_offset() == grid_offset)
                draw_building(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, x - 15, y, COLOR_MASK_GREEN);
            if (b_id && map_property_is_draw_tile(grid_offset)) { //b->tile.grid_offset() == grid_offset
                bool red = !map_terrain_is(grid_offset, TERRAIN_BUILDING);
                draw_debug_line(str, x0, y + 0, 0, "", b_id, red ? COLOR_LIGHT_RED : COLOR_WHITE);
                draw_debug_line(str, x0, y + 10, 0, "", b->type, red ? COLOR_LIGHT_RED : COLOR_LIGHT_BLUE);
                if (!b->is_main())
                    text_draw_shadow((uint8_t *)string_from_ascii("sub"), x0, y - 10, COLOR_RED);
            }
            break;
        case 2: // DRAW-TILES AND SIZES
            if (map_terrain_is(grid_offset, TERRAIN_BUILDING)) {
                if (map_property_is_draw_tile(grid_offset)) {
                    draw_debug_line(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_GREEN);
                    draw_debug_line(str, x1, y + 10, 0, "", b->size, COLOR_WHITE);
                } else
                    draw_debug_line(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_RED);
            } else if (!map_property_is_draw_tile(grid_offset))
                draw_debug_line(str, x, y + 10, 0, "", map_property_multi_tile_xy(grid_offset), COLOR_LIGHT_BLUE);
            break;
        case 3: // ROADS
            if (b_id && map_property_is_draw_tile(grid_offset)) { //&& b->tile.grid_offset() == grid_offset
                draw_debug_line(str, x0, y + 5, 0, "", b->road_access.x(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
                draw_debug_line(str, x0, y + 15, 0, "", b->road_access.y(), b->has_road_access ? COLOR_GREEN : COLOR_LIGHT_RED);
                if (b->has_road_access) {
                    auto tile_coords = mappoint_to_pixel(b->road_access);
                    draw_building(image_id_from_group(GROUP_TERRAIN_OVERLAY_COLORED) + 23, tile_coords.x, tile_coords.y, COLOR_MASK_GREEN);
                }
            }
            if (map_terrain_is(grid_offset, TERRAIN_ROAD)) {
                d = map_road_network_get(grid_offset);
                draw_debug_line(str, x, y + 10, 10, "R", d, COLOR_WHITE);
            } else if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD)) {
                d = map_road_network_get(grid_offset);
                draw_debug_line(str, x, y + 10, 10, "R", d, COLOR_LIGHT_BLUE);
            }
            break;
        case 4: // ROUTING DISTANCE
            d = map_routing_distance(grid_offset);
            if (d > 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE);
            else if (d == 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 5: // CITIZEN ROUTING GRID
            d = map_citizen_grid(grid_offset);
            if (d > 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE);
            else
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 6: // MOISTURE
            d = map_moisture_get(grid_offset);
            if (d & MOISTURE_GRASS)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_WHITE);
            else if (d & MOISTURE_TRANSITION)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
            else if (d & MOISTURE_SHORE_TALLGRASS)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_GREEN);
            break;
        case 7: // PROPER GRASS LEVEL
            d = map_grasslevel_get(grid_offset);
            if (d) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_GREEN); break;
        case 8: // FERTILITY & SOIL DEPLETION
            d = map_get_fertility(grid_offset, FERT_WITH_MALUS);
            if (d) {
                int n = map_get_fertility(grid_offset, FERT_NO_MALUS);
                if (d == n || map_terrain_is(grid_offset, TERRAIN_MEADOW))
                    draw_debug_line(str, x, y + 5, 0, "", d, COLOR_LIGHT_GREEN);
                else {
                    draw_debug_line(str, x, y + 5, 0, "", d, COLOR_LIGHT_BLUE);
                    d = map_get_fertility(grid_offset, FERT_ONLY_MALUS);
                    draw_debug_line(str, x, y + 15, 0, "", d, COLOR_LIGHT_RED);
                }
            }
            break;
        case 9: // FLOODPLAIN SHORE ORDER
            d = map_get_floodplain_row(grid_offset);
            if (d > -1) draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED); break;
        case 10: // FLOODPLAIN TERRAIN FLAGS
            d = map_terrain_is(grid_offset, TERRAIN_BUILDING);
            if (map_terrain_is(grid_offset, TERRAIN_FLOODPLAIN)) {
                if (map_terrain_is(grid_offset, TERRAIN_WATER)) {
                    if (map_terrain_is(grid_offset, TERRAIN_SUBMERGED_ROAD))
                        draw_debug_line(str, x, y + 10, 0, "", d, 0xff777777);
                    else if (map_building_at(grid_offset) > 0)
                        draw_debug_line(str, x, y + 10, 0, "", d, 0xff550000);
                } else {
                    if (map_terrain_is(grid_offset, TERRAIN_ROAD))
                        draw_debug_line(str, x, y + 10, 0, "", d, 0xffffffff);
                    else if (map_building_at(grid_offset) > 0)
                        draw_debug_line(str, x, y + 10, 0, "", d, 0xffaa0000);
                }
            }
            if (map_terrain_is(grid_offset, TERRAIN_AQUEDUCT)) {
                int a = map_aqueduct_at(grid_offset);
                if (map_terrain_is(grid_offset, TERRAIN_WATER))
                    draw_debug_line(str, x, y + 10, 0, "", a, 0xff557777);
                else
                    draw_debug_line(str, x, y + 10, 0, "", a, 0xff5577ff);
            } else if (map_terrain_is(grid_offset, TERRAIN_IRRIGATION_RANGE)) {
                if (map_terrain_is(grid_offset, TERRAIN_WATER))
                    draw_debug_line(str, x, y + 10, 0, "", d, 0xff007777);
                else
                    draw_debug_line(str, x, y + 10, 0, "", d, 0xff00ffff);
            }
            break;
        case 11: // LABOR
            if (b_id && map_property_is_draw_tile(grid_offset) && (b->labor_category != -1 || building_is_floodplain_farm(b))) {
                if (b->labor_category != CATEGORY_FOR_building(b))
                    draw_debug_line(str, x0, y + 10, 10, "!!", b->labor_category, COLOR_RED); // incorrect category??
                else
                    draw_debug_line(str, x0, y + 10, 0, "", b->labor_category, COLOR_WHITE);
                draw_debug_line(str, x1, y + 10, 0, "", b->houses_covered, COLOR_LIGHT_RED);
                draw_debug_line(str, x0, y + 20, 0, "", b->num_workers, COLOR_LIGHT_BLUE);
                draw_debug_line(str, x1 - 10, y + 20, 4, ":", b->worker_percentage(), COLOR_LIGHT_BLUE);
                //
                if (building_is_farm(b->type)) {
                    draw_debug_line(str, x1 + 40, y + 20, 40, "fert.", map_get_fertility_for_farm(b->tile.grid_offset()), COLOR_FONT_ORANGE_LIGHT);
                    draw_debug_line(str, x0, y + 30, 0, "", b->data.industry.progress, COLOR_GREEN);
                    draw_debug_line(str, x1 + 10, y + 30, 4, ":", b->data.industry.progress / 20, COLOR_GREEN);
                    draw_debug_line(str, x1 + 40, y + 30, 40, "exp.", farm_expected_produce(b), COLOR_GREEN);
                    if (building_is_floodplain_farm(b)) {
                        draw_debug_line(str, x0, y + 40, 0, "", b->data.industry.labor_state, COLOR_WHITE);
                        draw_debug_line(str, x1, y + 40, 0, "", b->data.industry.labor_days_left, COLOR_WHITE);
                    }
                }
                if (b->data.entertainment.booth_corner_grid_offset) {
                    draw_debug_line(str, x0, y + 30, 0, "", b->data.entertainment.days1, COLOR_GREEN);
                    draw_debug_line(str, x1, y + 30, 0, "", b->data.entertainment.days2, COLOR_GREEN);
                    draw_debug_line(str, x0, y + 40, 0, "", b->data.entertainment.days3_or_play, COLOR_GREEN);
                }
            }
            break;
        case 12: // SPRITE FRAMES

            if (grid_offset == MAP_OFFSET(b->tile.x(), b->tile.y()))
                draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 3, x - 15, y, COLOR_MASK_GREEN);
            if (grid_offset == north_tile_grid_offset(b->tile.x(), b->tile.y()))
                ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, x - 15, y, COLOR_MASK_RED);
            d = map_sprite_animation_at(grid_offset);
            if (d) {
                string_from_int(str, d, 0);
                text_draw_shadow(str, x, y + 10, COLOR_WHITE);
            }

            // STATUES & MONUMENTS

            if (b_id && map_property_is_draw_tile(grid_offset) && (b->labor_category != -1 || building_is_floodplain_farm(b))) {
                switch (b->type) {
                    case BUILDING_SMALL_STATUE:
                    case BUILDING_MEDIUM_STATUE:
                    case BUILDING_LARGE_STATUE:
                        draw_debug_line(str, x1, y + 10, 0, "", b->data.monuments.variant, COLOR_WHITE);
                        break;
                        //
                    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
                    case BUILDING_TEMPLE_COMPLEX_RA:
                    case BUILDING_TEMPLE_COMPLEX_PTAH:
                    case BUILDING_TEMPLE_COMPLEX_SETH:
                    case BUILDING_TEMPLE_COMPLEX_BAST:
                        draw_debug_line(str, x1, y + 10, 0, "", b->data.monuments.variant, COLOR_WHITE);
                        draw_debug_line(str, x1, y + 20, 0, "", b->data.monuments.temple_complex_attachments, COLOR_LIGHT_BLUE);
                        break;
                }
            }
            break;
        case 13: // TERRAIN BIT FIELD
            draw_debug_line(str, x, y + 10, 0, "", map_terrain_get(grid_offset), COLOR_LIGHT_BLUE);
            break;
        case 14: // IMAGE FIELD
            draw_debug_line(str, x, y + 10, 0, "", map_image_at(grid_offset) - 14252, COLOR_LIGHT_RED);
            break;
        case 15: // MARSHLAND DEPLETION
            d = map_get_vegetation_growth(grid_offset);
            if (d != 255)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 16: // MARSHLAND
            d = map_terrain_is(grid_offset, TERRAIN_MARSHLAND);
            if (d != 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 17: // TERRAIN TYPE
            d = map_terrain_get(grid_offset);
//            if (d != 0)
            draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_BLUE);
            break;
        case 18: // UNKNOWN SOIL GRID
            d = map_get_UNK04(grid_offset);
            if (d != 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
        case 19: // UNKNOWN 32BIT GRID
            d = map_get_UNK03(grid_offset);
            if (d != 0)
                draw_debug_line(str, x, y + 10, 0, "", d, COLOR_LIGHT_RED);
            break;
    }
}
void draw_debug_figures(pixel_coordinate pixel, map_point point) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int figure_id = map_figure_at(grid_offset);
    while (figure_id) {
        figure *f = figure_get(figure_id);
        f->draw_debug();
        if (figure_id != f->next_figure)
            figure_id = f->next_figure;
        else
            figure_id = 0;
    }
}

void figure::draw_debug() {

    int DB1 = abs(debug_range_1) % 6;
    if (DB1 == 0)
        return;

    building *b = home();
    building *bdest = destination();

    uint8_t str[10];
    pixel_coordinate coords;
    coords = mappoint_to_pixel(map_point(tile.x(), tile.y()));
    adjust_pixel_offset(&coords.x, &coords.y);
    coords.x -= 10;
    coords.y -= 80;
    int indent = 0;

    switch (DB1) {
        case 1: // ACTION & STATE IDS
            draw_debug_line(str, coords.x, coords.y, indent, "", id, COLOR_WHITE);
            draw_debug_line(str, coords.x, coords.y + 10, indent, "", type, COLOR_LIGHT_BLUE);
            draw_debug_line(str, coords.x, coords.y + 20, indent, "", action_state, COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x, coords.y + 30, indent, "", wait_ticks, COLOR_WHITE);
            draw_debug_line(str, coords.x, coords.y + 40, indent, "", roam_length, COLOR_WHITE);

            coords.y += 80;

            string_from_int(str, tile.x(), 0);
            text_draw(str, coords.x, coords.y, FONT_NORMAL_PLAIN, 0);
            string_from_int(str, tile.y(), 0);
            text_draw(str, coords.x, coords.y+10, FONT_NORMAL_PLAIN, 0);
            string_from_int(str, tile.grid_offset(), 0);
            text_draw(str, coords.x, coords.y+20, FONT_NORMAL_PLAIN, 0);
            string_from_int(str, progress_on_tile, 0);
            text_draw(str, coords.x, coords.y+30, FONT_NORMAL_PLAIN, 0);
            string_from_int(str, routing_path_current_tile, 0);
            text_draw(str, coords.x+30, coords.y+30, FONT_NORMAL_PLAIN, 0);
            break;
        case 2: // ROUTING
            // draw path
            if (routing_path_id) { //&& (roam_length == max_roam_length || roam_length == 0)
                auto tile_coords = mappoint_to_pixel(map_point(destination()->tile.x(), destination()->tile.y()));
                draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 3, tile_coords.x, tile_coords.y);
                tile_coords = mappoint_to_pixel(map_point(destination_tile.x(), destination_tile.y()));
                draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, tile_coords.x, tile_coords.y);
                int tx = tile.x();
                int ty = tile.y();
                tile_coords = mappoint_to_pixel(map_point(tx, ty));
                ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, tile_coords.x,
                                       tile_coords.y);
                int starting_tile_index = routing_path_current_tile;
                if (progress_on_tile >= 0 && progress_on_tile < 8) // adjust half-tile offset
                    starting_tile_index--;
                for (int i = starting_tile_index; i < routing_path_length; i++) {
                    auto pdir = figure_route_get_direction(routing_path_id, i);
                    switch (pdir) {
                        case 0:
                            ty--;
                            break;
                        case 1:
                            tx++;
                            ty--;
                            break;
                        case 2:
                            tx++;
                            break;
                        case 3:
                            tx++;
                            ty++;
                            break;
                        case 4:
                            ty++;
                            break;
                        case 5:
                            tx--;
                            ty++;
                            break;
                        case 6:
                            tx--;
                            break;
                        case 7:
                            tx--;
                            ty--;
                            break;
                    }
                    tile_coords = mappoint_to_pixel(map_point(tx, ty));
                    ImageDraw::img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, tile_coords.x,
                                           tile_coords.y);
                }
            }

            // the rest of values, on top of all else
            if (routing_path_id) {
                draw_debug_line(str, coords.x, coords.y, indent, "", routing_path_id, COLOR_LIGHT_RED);
                draw_debug_line(str, coords.x, coords.y + 10, indent, "", routing_path_current_tile, COLOR_LIGHT_RED);
                draw_debug_line(str, coords.x, coords.y + 20, indent, "", routing_path_length, COLOR_LIGHT_RED);
            } else {
                draw_debug_line(str, coords.x, coords.y, indent, "", roam_length, COLOR_LIGHT_BLUE);
                draw_debug_line(str, coords.x, coords.y + 10, indent, "", roam_wander_freely, COLOR_LIGHT_BLUE);
                draw_debug_line(str, coords.x, coords.y + 20, indent, "", max_roam_length, COLOR_LIGHT_BLUE);
            }
            draw_debug_line(str, coords.x, coords.y + 30, indent, "", terrain_usage, COLOR_WHITE);
            switch (direction) {
                case DIR_FIGURE_CAN_NOT_REACH:
                    draw_debug_line(str, coords.x, coords.y + 40, indent, "", direction, COLOR_LIGHT_RED);
                    break;
                case DIR_FIGURE_REROUTE:
                    draw_debug_line(str, coords.x, coords.y + 40, indent, "", direction, COLOR_LIGHT_BLUE);
                    break;
                case DIR_FIGURE_NONE:
                    draw_debug_line(str, coords.x, coords.y + 40, indent, "", direction, COLOR_GREEN);
                    break;
                default:
                    draw_debug_line(str, coords.x, coords.y + 40, indent, "", direction, COLOR_WHITE);
                    break;
            }
            draw_debug_line(str, coords.x + 10, coords.y + 40, 5, ":", roam_turn_direction,
                            roam_turn_direction ? COLOR_LIGHT_BLUE : 0xff777777);

            coords.y += 50;
            string_from_int(str, progress_on_tile, 0);
            text_draw(str, coords.x, coords.y + 30, FONT_NORMAL_PLAIN, 0);
            break;
        case 3: // RESOURCE CARRY
            if (resource_id) {
                draw_debug_line(str, coords.x, coords.y, indent, "",  resource_id, COLOR_GREEN);
                draw_debug_line(str, coords.x, coords.y + 10, indent, "",  resource_amount_full, resource_amount_full ? COLOR_GREEN : 0xff777777);
                draw_debug_line(str, coords.x, coords.y + 20, indent, "",  collecting_item_id, collecting_item_id ? COLOR_LIGHT_BLUE : 0xff777777);
            }
            break;
        case 4: // BUILDING DATA
            draw_debug_line(str, coords.x + 0, coords.y, indent, "",  homeID(), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x + 20, coords.y, 8, ":",  home()->get_figure_slot(this), homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x + 0, coords.y + 10, indent, "",  destinationID(), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x + 20, coords.y + 10, 8, ":",  destination()->get_figure_slot(this), destinationID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x + 0, coords.y + 20, indent, "",  immigrant_homeID(), immigrant_homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            draw_debug_line(str, coords.x + 20, coords.y + 20, 8, ":",  immigrant_home()->get_figure_slot(this), immigrant_homeID() > 0 ? COLOR_WHITE : COLOR_LIGHT_RED);
            break;
        case 5: // FESTIVAL
            coords.y += 30;
            draw_debug_line(str, coords.x, coords.y, indent, "", unk_ph1_269, COLOR_WHITE);
            draw_debug_line(str, coords.x, coords.y + 10, indent, "", unk_ph4_ffff, COLOR_WHITE);
            draw_debug_line(str, coords.x, coords.y + 20, indent, "", festival_remaining_dances, COLOR_WHITE);
            break;
    }
}

void draw_debug_ui(int x, int y) {
    uint8_t str[300];

    /////// DEBUG PAGES NAME
    if (true) {
        y += 13;
        int DB1 = abs(debug_range_1) % 6;
        int DB2 = abs(debug_range_2) % 20;

        color_t col = COLOR_GREEN;

        string_from_int(str, DB1);
        text_draw_shadow(str, x, y, col);
        text_draw_shadow((uint8_t *) string_from_ascii(":"), x + 14, y, col);
        x += 20;
        switch (DB1) {
            case 1:
                text_draw_shadow((uint8_t *) string_from_ascii("ACTION / STATE IDS"), x, y, col);
                break;
            case 2:
                text_draw_shadow((uint8_t *) string_from_ascii("ROUTING"), x, y, col);
                break;
            case 3:
                text_draw_shadow((uint8_t *) string_from_ascii("RESOURCES / CARRYING"), x, y, col);
                break;
            case 4:
                text_draw_shadow((uint8_t *) string_from_ascii("N/A"), x, y, col);
                break;
            case 5:
                text_draw_shadow((uint8_t *) string_from_ascii("FESTIVAL"), x, y, col);
                break;
        }
        y += 3;
        x -= 20;
        string_from_int(str, DB2);
        text_draw_shadow(str, x, y + 10, col);
        text_draw_shadow((uint8_t *) string_from_ascii(":"), x + 14, y + 10, col);
        x += 20;
        switch (DB2) {
            default: break;
            case 1: text_draw_shadow((uint8_t *) string_from_ascii("BUILDING IDS"), x, y + 10, col); break;
            case 2: text_draw_shadow((uint8_t *) string_from_ascii("DRAW-TILES AND SIZES"), x, y + 10, col); break;
            case 3: text_draw_shadow((uint8_t *) string_from_ascii("ROADS"), x, y + 10, col); break;
            case 4: text_draw_shadow((uint8_t *) string_from_ascii("ROUTING DISTANCE"), x, y + 10, col); break;
            case 5: text_draw_shadow((uint8_t *) string_from_ascii("CITIZEN ROUTING GRID"), x, y + 10, col); break;
            case 6: text_draw_shadow((uint8_t *) string_from_ascii("MOISTURE"), x, y + 10, col); break;
            case 7: text_draw_shadow((uint8_t *) string_from_ascii("PROPER GRASS LEVEL"), x, y + 10, col); break;
            case 8: text_draw_shadow((uint8_t *) string_from_ascii("FERTILITY / SOIL DEPLETION"), x, y + 10, col); break;
            case 9: text_draw_shadow((uint8_t *) string_from_ascii("FLOODPLAIN SHORE ORDER"), x, y + 10, col); break;
            case 10: text_draw_shadow((uint8_t *) string_from_ascii("FLOODPLAIN TERRAIN FLAGS"), x, y + 10, col); break;
            case 11: text_draw_shadow((uint8_t *) string_from_ascii("LABOR"), x, y + 10, col); break;
            case 12: text_draw_shadow((uint8_t *) string_from_ascii("SPRITE FRAMES / STATUES AND MONUMENTS"), x, y + 10, col); break;
            case 13: text_draw_shadow((uint8_t *) string_from_ascii("TERRAIN BIT FIELD"), x, y + 10, col); break;
            case 14: text_draw_shadow((uint8_t *) string_from_ascii("IMAGE FIELD"), x, y + 10, col); break;
            case 15: text_draw_shadow((uint8_t *) string_from_ascii("MARSHLAND DEPLETION"), x, y + 10, col); break;
            case 16: text_draw_shadow((uint8_t *) string_from_ascii("MARSHLAND"), x, y + 10, col); break;
            case 17: text_draw_shadow((uint8_t *) string_from_ascii("TERRAIN TYPE"), x, y + 10, col); break;
            case 18: text_draw_shadow((uint8_t *) string_from_ascii("UNKNOWN SOIL GRID"), x, y + 10, col); break;
            case 19: text_draw_shadow((uint8_t *) string_from_ascii("UNKNOWN 32BIT GRID"), x, y + 10, col); break;
        }
        y += 10;
        x -= 20;
    }

    /////// TIME
    if (true) {
        auto time = game_time_struct();

        draw_debug_line(str, x, y + 15, 50, "tick:", time->tick);
        draw_debug_line(str, x + 80, y + 15, 50, "iscycle:", is_flood_cycle_tick());
        draw_debug_line(str, x, y + 25, 50, "cycle:", floodplains_current_cycle());
        draw_debug_line(str, x + 90, y + 25, 60, "frame:", floodplains_current_cycle_tick());

        draw_debug_line(str, x, y + 35, 50, "day:", time->day);
        draw_debug_line(str, x, y + 45, 50, "month:", time->month);
        draw_debug_line(str, x, y + 55, 50, "year:", time->year);
        draw_debug_line(str, x, y + 65, 60, "abs. tick:", game_time_absolute_tick()); // absolute tick of the year
        draw_debug_line(str, x, y + 75, 60, "abs. day:", game_time_absolute_day()); // absolute day of the year
        y += 80;
    }

    /////// BUILD PLANNER
    if (false) {
        int cl = 90;
        draw_debug_line(str, x, y + 15, cl, "type:", Planner.build_type);
        draw_debug_line(str, x, y + 25, cl, "in progress:", Planner.in_progress);
        draw_debug_line(str, x, y + 35, cl, "draw as con.:", Planner.draw_as_constructing);
        draw_debug_line(str, x, y + 45, cl, "orientation:", Planner.absolute_orientation); draw_debug_line(str, x + 40, y + 45, cl, "", Planner.relative_orientation);
        draw_debug_line(str, x, y + 55, cl, "variant:", Planner.variant);
        draw_debug_line(str, x, y + 65, cl, "start:", Planner.start.x()); draw_debug_line(str, x + 40, y + 65, cl, "", Planner.start.y());
        draw_debug_line(str, x, y + 75, cl, "end:", Planner.end.x()); draw_debug_line(str, x + 40, y + 75, cl, "", Planner.end.y());
        draw_debug_line(str, x, y + 85, cl, "cost:", Planner.total_cost);
        y += 90;
    }

    /////// RANDOM
    if (false) {
        auto randm = random_data_struct();

        int cl = 60;
        draw_debug_line(str, x, y + 15, cl, "iv1:", randm->iv1);
        draw_debug_line(str, x, y + 25, cl, "iv2:", randm->iv2);
        draw_debug_line(str, x, y + 35, cl, "1_3b:", randm->random1_3bit);
        draw_debug_line(str, x, y + 45, cl, "1_7b:", randm->random1_7bit);
        draw_debug_line(str, x, y + 55, cl, "1_15b:", randm->random1_15bit);
        draw_debug_line(str, x, y + 65, cl, "2_3b:", randm->random2_3bit);
        draw_debug_line(str, x, y + 75, cl, "2_7b:", randm->random2_7bit);
        draw_debug_line(str, x, y + 85, cl, "2_15b:", randm->random2_15bit);

        draw_debug_line(str, x, y + 105, cl, "scum:", anti_scum_random_15bit(false));
        y += 100;
    }

    /////// RELIGION
    if (true) {
        int cl = 0;
        text_draw_shadow((uint8_t *) string_from_ascii("      mood/target  wrath/ankhs   buildings  coverage  festival"), x, y + 15, COLOR_WHITE);
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
        if (god_known_status(0) != GOD_STATUS_UNKNOWN) {
            draw_debug_line_double_left(str, x, y + 15, c0, c1, "Osiris:",
                                        city_data.religion.gods[0].mood,
                                        city_data.religion.gods[0].target_mood);
            draw_debug_line_double_left(str, x + c2, y + 15, 0, c1, "",
                                        city_data.religion.gods[0].wrath_bolts,
                                        city_data.religion.gods[0].happy_ankhs);
            draw_debug_line(str, x + c3, y + 15, cl, "", building_count_total(BUILDING_SHRINE_OSIRIS));
            draw_debug_line(str, x + c4, y + 15, cl, "", building_count_active(BUILDING_TEMPLE_OSIRIS));
            draw_debug_line(str, x + c5, y + 15, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_OSIRIS));
            draw_debug_line(str, x + c6, y + 15, c7, "%", city_culture_coverage_religion(0));
            draw_debug_line(str, x + c8, y + 15, cl, "", city_data.religion.gods[0].months_since_festival);
        }
        if (god_known_status(1) != GOD_STATUS_UNKNOWN)
        {
            draw_debug_line_double_left(str, x, y + 25, c0, c1, "Ra:",
                                        city_data.religion.gods[1].mood,
                                        city_data.religion.gods[1].target_mood);
            draw_debug_line_double_left(str, x + c2, y + 25, 0, c1, "",
                                        city_data.religion.gods[1].wrath_bolts,
                                        city_data.religion.gods[1].happy_ankhs);
            draw_debug_line(str, x + c3, y + 25, cl, "", building_count_total(BUILDING_SHRINE_RA));
            draw_debug_line(str, x + c4, y + 25, cl, "", building_count_active(BUILDING_TEMPLE_RA));
            draw_debug_line(str, x + c5, y + 25, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_RA));
            draw_debug_line(str, x + c6, y + 25, c7, "%", city_culture_coverage_religion(1));
            draw_debug_line(str, x + c8, y + 25, cl, "", city_data.religion.gods[1].months_since_festival);
        }
        if (god_known_status(2) != GOD_STATUS_UNKNOWN) {
            draw_debug_line_double_left(str, x, y + 35, c0, c1, "Ptah:",
                                        city_data.religion.gods[2].mood,
                                        city_data.religion.gods[2].target_mood);
            draw_debug_line_double_left(str, x + c2, y + 35, 0, c1, "",
                                        city_data.religion.gods[2].wrath_bolts,
                                        city_data.religion.gods[2].happy_ankhs);
            draw_debug_line(str, x + c3, y + 35, cl, "", building_count_total(BUILDING_SHRINE_PTAH));
            draw_debug_line(str, x + c4, y + 35, cl, "", building_count_active(BUILDING_TEMPLE_PTAH));
            draw_debug_line(str, x + c5, y + 35, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_PTAH));
            draw_debug_line(str, x + c6, y + 35, c7, "%", city_culture_coverage_religion(2));
            draw_debug_line(str, x + c8, y + 35, cl, "", city_data.religion.gods[2].months_since_festival);
        }
        if (god_known_status(3) != GOD_STATUS_UNKNOWN) {
            draw_debug_line_double_left(str, x, y + 45, c0, c1, "Seth:",
                                        city_data.religion.gods[3].mood,
                                        city_data.religion.gods[3].target_mood);
            draw_debug_line_double_left(str, x + c2, y + 45, 0, c1, "",
                                        city_data.religion.gods[3].wrath_bolts,
                                        city_data.religion.gods[3].happy_ankhs);
            draw_debug_line(str, x + c3, y + 45, cl, "", building_count_total(BUILDING_SHRINE_SETH));
            draw_debug_line(str, x + c4, y + 45, cl, "", building_count_active(BUILDING_TEMPLE_SETH));
            draw_debug_line(str, x + c5, y + 45, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_SETH));
            draw_debug_line(str, x + c6, y + 45, c7, "%", city_culture_coverage_religion(3));
            draw_debug_line(str, x + c8, y + 45, cl, "", city_data.religion.gods[3].months_since_festival);
        }
        if (god_known_status(4) != GOD_STATUS_UNKNOWN) {
            draw_debug_line_double_left(str, x, y + 55, c0, c1, "Bast:",
                                        city_data.religion.gods[4].mood,
                                        city_data.religion.gods[4].target_mood);
            draw_debug_line_double_left(str, x + c2, y + 55, 0, c1, "",
                                        city_data.religion.gods[4].wrath_bolts,
                                        city_data.religion.gods[4].happy_ankhs);
            draw_debug_line(str, x + c3, y + 55, cl, "", building_count_total(BUILDING_SHRINE_BAST));
            draw_debug_line(str, x + c4, y + 55, cl, "", building_count_active(BUILDING_TEMPLE_BAST));
            draw_debug_line(str, x + c5, y + 55, cl, "", building_count_active(BUILDING_TEMPLE_COMPLEX_BAST));
            draw_debug_line(str, x + c6, y + 55, c7, "%", city_culture_coverage_religion(4));
            draw_debug_line(str, x + c8, y + 55, cl, "", city_data.religion.gods[4].months_since_festival);
        }

        cl = 180;
        draw_debug_line(str, x, y + 75, cl, "150% export profits:", city_data.religion.ra_150_export_profits_months_left);
        draw_debug_line(str, x, y + 85, cl, "No traders:", city_data.religion.ra_no_traders_months_left);
        draw_debug_line(str, x, y + 95, cl, "Slightly increased trades:", city_data.religion.ra_slightly_increased_trading_months_left);
        draw_debug_line(str, x, y + 105, cl, "Slightly reduced trades:", city_data.religion.ra_slightly_reduced_trading_months_left);
        draw_debug_line(str, x, y + 115, cl, "Harshly reduced trades:", city_data.religion.ra_harshly_reduced_trading_months_left);

        draw_debug_line(str, x, y + 125, cl, "Enemy troops kill:", city_data.religion.seth_crush_enemy_troops);
        draw_debug_line(str, x, y + 135, cl, "Player troops protection:", city_data.religion.seth_protect_player_troops);

        draw_debug_line(str, x, y + 145, cl, "Double farm yields:", city_data.religion.osiris_double_farm_yield);
        draw_debug_line(str, x, y + 155, cl, "Floods will destroy farms:", city_data.religion.osiris_flood_will_destroy_active);
        y += 170;
    }

    /////// FLOODS
    if (true) {
        auto floods = floodplain_data();

        double _c_curr = floodplains_current_cycle();
        double _c_start = floodplains_flooding_start_cycle();
        double _c_end = floodplains_flooding_end_cycle();

        int _c_period_last = floodplains_flooding_cycles_length(false);
        int _c_period_next = floodplains_flooding_cycles_length(true);

        float rc_curr = fmod(_c_curr, cycles_in_a_year);
        float rc_start = fmod(_c_start, cycles_in_a_year);
        float rc_end = fmod(_c_end, cycles_in_a_year);
        if (rc_curr < 0.1 && game_time_month() > 1)
            rc_curr = cycles_in_a_year;

        // floodplains timeline (yearly)
        double additional_abs_ticks = cycles_in_a_year * (double)game_time_year_since_start();
        auto dot = string_from_ascii(",");
        for (int i = 0; i < 392; ++i) {
            text_draw(dot, x + i - 1, y + 15, FONT_NORMAL_PLAIN, 0);
        }
        for (int i = 0; i < 392; ++i) {
            int abs_i = i + additional_abs_ticks;
            text_draw(dot, x + i, y + 15, FONT_NORMAL_PLAIN, COLOR_WHITE);

            if ((i > rc_start - 49 && i < rc_end + 28)
            || (i > rc_start - 49 - cycles_in_a_year && i < rc_end + 28 - cycles_in_a_year)
            || (i > rc_start - 49 + cycles_in_a_year && i < rc_end + 28 + cycles_in_a_year))
                text_draw(dot, x + i, y + 15, FONT_NORMAL_PLAIN, COLOR_FONT_ORANGE_LIGHT);

            if ((i > rc_start && i < rc_end)
            || (i > rc_start - cycles_in_a_year && i < rc_end - cycles_in_a_year)
            || (i > rc_start + cycles_in_a_year && i < rc_end + cycles_in_a_year))
                text_draw(dot, x + i, y + 15, FONT_NORMAL_PLAIN, COLOR_RED);

            if (floods_debug_period() > 0) {
                if (abs_i > _c_start + _c_period_next && abs_i < _c_end - _c_period_next)
                    text_draw(dot, x + i, y + 15, FONT_NORMAL_PLAIN, COLOR_GREEN);
            } else {
                if (abs_i > _c_start + _c_period_last && abs_i < _c_end - _c_period_last)
                    text_draw(dot, x + i, y + 15, FONT_NORMAL_PLAIN, COLOR_GREEN);
            }
        }

        // cursor
        text_draw_shadow(dot, x + rc_curr, y + 15, COLOR_FONT_YELLOW);
        text_draw_shadow(string_from_ascii("\'"), x + rc_curr, y + 25, COLOR_FONT_YELLOW);
        draw_debug_line_float(str, x + rc_curr + 5, y + 25, 0, "", _c_curr); // current cycle
        draw_debug_line(str, x + rc_curr + 54, y + 25, 5, ":", floods->state); // current cycle

        draw_debug_line(str, x, y + 35, 60, "debug:", floods_debug_period());
        draw_debug_line(str, x, y + 45, 60, "ftick:", floodplain_flooding_tick());

        y += 50;

        int cl = 60;
        draw_debug_line(str, x, y + 15, cl, "current:", _c_curr); // current cycle
        draw_debug_line(str, x + 85, y + 15, 10, "/", floodplains_current_cycle_tick()); // current cycle
        draw_debug_line(str, x, y + 25, cl, "t-49:", _c_start - 49); // 49 cycles prior
        draw_debug_line(str, x, y + 35, cl, "t-28:", _c_start - 28); // 28 cycles prior
        draw_debug_line(str, x, y + 45, cl, "start:", _c_start); // flood start
        if (floods_debug_period() > 0) {
            draw_debug_line(str, x, y + 55, cl, "rest:", _c_start + _c_period_next); // first rest period
            draw_debug_line(str, x, y + 65, cl, "retract:", _c_end - _c_period_next); // first rest period
        } else {
            draw_debug_line(str, x, y + 55, cl, "rest:", _c_start + _c_period_last); // first rest period
            draw_debug_line(str, x, y + 65, cl, "retract:", _c_end - _c_period_last); // first rest period
        }
        draw_debug_line(str, x, y + 75, cl, "end:", _c_end); // flood end
        draw_debug_line(str, x, y + 85, cl, "final:", _c_end + 28); // lands farmable again

        cl = 100;
        draw_debug_line(str, x, y + 105, cl, "season_initial:", floods->season_initial);
        draw_debug_line(str, x, y + 115, cl, "duration_initial:", floods->duration_initial);
        draw_debug_line(str, x, y + 125, cl, "quality_initial:", floods->quality_initial);
        draw_debug_line(str, x, y + 135, cl, "season:", floods->season);
        draw_debug_line(str, x, y + 145, cl, "duration:", floods->duration);
        draw_debug_line(str, x, y + 155, cl, "quality:", floods->quality);
        draw_debug_line(str, x, y + 165, cl, "(unk00):", floods->unk00);
        draw_debug_line(str, x, y + 175, cl, "quality_next:", floods->quality_next);
        draw_debug_line(str, x, y + 185, cl, "quality_last:", floods->quality_last);

        cl = 60;
        draw_debug_line(str, x, y + 205, cl, "progress:", floods->flood_progress); // status 30 (???)
        draw_debug_line(str, x, y + 215, cl, "(unk01):", floods->unk01); // ???
        draw_debug_line(str, x, y + 225, cl, "state:", floods->state); // floodplains state
        draw_debug_line(str, x, y + 235, cl, "width:", floods->floodplain_width); // status 10 (???)
        draw_debug_line(str, x, y + 245, cl, "hasplains:", floods->has_floodplains); // status 10 (???)
        y += 350;
    }

    /////// CAMERA
    if (false) {
        map_point camera_tile = city_view_get_camera_tile();
        pixel_coordinate camera_pixels = city_view_get_camera_pixel_offset();

        view_data* viewdata = city_view_data_unsafe();
        int real_max_x;
        int real_max_y;
        city_view_get_camera_max_tile(&real_max_x, &real_max_y);

        int max_x_pixel_offset;
        int max_y_pixel_offset;
        city_view_get_camera_max_pixel_offset(&max_x_pixel_offset, &max_y_pixel_offset);

        draw_debug_line_double_left(str, x, y + 15, 90, 40, "camera:", viewdata->camera.position.x, viewdata->camera.position.y);
        draw_debug_line_double_left(str, x, y + 25, 90, 40, "---min:", SCROLLABLE_X_MIN_TILE(), SCROLLABLE_Y_MIN_TILE());
        draw_debug_line_double_left(str, x, y + 35, 90, 40, "tile:", camera_tile.x(), camera_tile.y());
        draw_debug_line_double_left(str, x, y + 45, 90, 40, "---max:", real_max_x, real_max_y);

        draw_debug_line_double_left(str, x, y + 65, 90, 40, "---min:", 0, 0);
        draw_debug_line_double_left(str, x, y + 75, 90, 40, "pixel:", camera_pixels.x, camera_pixels.y);
        draw_debug_line_double_left(str, x, y + 85, 90, 40, "---max:", max_x_pixel_offset, max_y_pixel_offset);

        draw_debug_line_double_left(str, x, y + 105, 90, 40, "v.tiles:", viewdata->viewport.width_pixels / 60, viewdata->viewport.height_pixels / 30);
        draw_debug_line_double_left(str, x, y + 115, 90, 40, "v.pixels:", viewdata->viewport.width_pixels, viewdata->viewport.height_pixels);
        y += 120;
    }

    /////// TUTORIAL
    if (false) {auto flags = tutorial_flags_struct();
        const char* const flagnames[41] = {
                "fire",
                "pop_150",
                "meat_400",
                "collapse",
                "gold_500",
                "temples_done",
                "disease",
                "figs_800",
                "???",
                "pottery_200",
                "beer_300",
                "",
                "",
                "",
                "",
                "tut1 start",
                "tut2 start",
                "tut3 start",
                "tut4 start",
                "tut5 start",
                "tut6 start",
                "tut7 start",
                "tut8 start",
                "",
                "",
                "",
                ////////////
                "// bazaar",
                "// pottery",
                "",
                "",
                "// tut4 ???",
                "// tut5 ???",
                "",
                "// water supply",
                "// tut4 ???",
                "",
                "// entertainment",
                "// temples",
                "// taxes",
                "// mansion",
                "",
        };
        for (int i = 0; i < 41; i++) {
            int f = flags->pharaoh.flags[i];
            switch (i) {
                case 0: f = flags->pharaoh.fire; break;
                case 1: f = flags->pharaoh.population_150_reached; break;
                case 2: f = flags->pharaoh.gamemeat_400_stored; break;
                case 3: f = flags->pharaoh.collapse; break;
                case 4: f = flags->pharaoh.gold_mined_500; break;
                case 5: f = flags->pharaoh.temples_built; break;
//            case 6: ??? crime?
                case 7: f = flags->pharaoh.figs_800_stored; break;
                case 8: f = flags->pharaoh.disease; break;
                case 9: f = flags->pharaoh.pottery_made; break;
                case 10: f = flags->pharaoh.beer_made; break;
                case 11: f = flags->pharaoh.spacious_apartment; break;
                    //
                case 15: f = flags->pharaoh.tut1_start; break;
                case 16: f = flags->pharaoh.tut2_start; break;
                case 17: f = flags->pharaoh.tut3_start; break;
                case 18: f = flags->pharaoh.tut4_start; break;
                case 19: f = flags->pharaoh.tut5_start; break;
                case 20: f = flags->pharaoh.tut6_start; break;
                case 21: f = flags->pharaoh.tut7_start; break;
                case 22: f = flags->pharaoh.tut8_start; break;
            }

            int color = COLOR_WHITE;
            if (f)
                color = COLOR_GREEN;
            string_from_int(str, i, 0);
            text_draw_shadow(str, x + 3, y + 115 + i * 10, color);
            text_draw_shadow((uint8_t *) string_from_ascii(":"), x + 3 + 20, y + 115 + i * 10, color);
            string_from_int(str, f, 0);
            text_draw_shadow(str, x + 3 + 30, y + 115 + i * 10, color);
            text_draw_shadow((uint8_t *) string_from_ascii(flagnames[i]), x + 3 + 45, y + 115 + i * 10, color);
        }
    }
}