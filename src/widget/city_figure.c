#include <core/string.h>
#include "city_figure.h"

#include "city/view.h"
#include "figure/formation.h"
#include "figure/image.h"
#include "figuretype/editor.h"
#include "graphics/image.h"
#include "graphics/text.h"


static void tile_cross_country_offset_to_pixel_offset(int cross_country_x, int cross_country_y, int *pixel_x, int *pixel_y) {
    int dir = city_view_orientation();
    if (dir == DIR_0_TOP_RIGHT || dir == DIR_4_BOTTOM_LEFT) {
        int base_pixel_x = 2 * cross_country_x - 2 * cross_country_y;
        int base_pixel_y = cross_country_x + cross_country_y;
        *pixel_x = dir == DIR_0_TOP_RIGHT ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_0_TOP_RIGHT ? base_pixel_y : -base_pixel_y;
    } else {
        int base_pixel_x = 2 * cross_country_x + 2 * cross_country_y;
        int base_pixel_y = cross_country_x - cross_country_y;
        *pixel_x = dir == DIR_2_BOTTOM_RIGHT ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_6_TOP_LEFT ? base_pixel_y : -base_pixel_y;
    }
}

#include "widget/city_building_ghost.h"
#include "building/properties.h"
#include "figure/route.h"

void figure::draw_debug() {

//    if (id == 6)
//        return;


    building *b = building_get(building_id);
    building *bdest = building_get(destination_building_id);

    uint8_t str[10];
    pixel_coordinate coords;
    coords = city_view_grid_offset_to_pixel(tile_x, tile_y);
    adjust_pixel_offset(&coords.x, &coords.y);

    coords.x -= 10;

    string_from_int(str, coords.x, 0);
    text_draw(str, coords.x, coords.y, FONT_NORMAL_PLAIN, 0);
    string_from_int(str, coords.y, 0);
    text_draw(str, coords.x, coords.y+10, FONT_NORMAL_PLAIN, 0);
    string_from_int(str, grid_offset_figure, 0);
    text_draw(str, coords.x, coords.y+20, FONT_NORMAL_PLAIN, 0);

    coords.y -= 80;

    // id
    string_from_int(str, id, 0);
    draw_text_shadow(str, coords.x, coords.y, COLOR_WHITE);

    // type
    string_from_int(str, type, 0);
    draw_text_shadow(str, coords.x, coords.y+10, COLOR_BLUE);

    // action state
    string_from_int(str, action_state, 0);
    draw_text_shadow(str, coords.x, coords.y+20, COLOR_RED);

    // wait_ticks
    string_from_int(str, wait_ticks, 0);
    draw_text_shadow(str, coords.x, coords.y+30, COLOR_WHITE);

    if (resource_id) {
        string_from_int(str, resource_id, 0);
        draw_text_shadow(str, coords.x+25, coords.y+10, COLOR_GREEN);
        string_from_int(str, loads_counter, 0);
        draw_text_shadow(str, coords.x+25, coords.y+20, COLOR_GREEN);
    }
//    else {
//        draw_text_shadow((uint8_t*)string_from_ascii("-"), coords.x+40, coords.y+10, COLOR_GREEN);
//        draw_text_shadow((uint8_t*)string_from_ascii("-"), coords.x+40, coords.y+20, COLOR_GREEN);
//    }

//    coords = city_view_grid_offset_to_pixel(destination_x, destination_y);
//    draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 33, coords.x, coords.y, COLOR_MASK_NONE);
//    text_draw(str, coords.x, coords.y, FONT_NORMAL_BLACK, 0);

    if (false && routing_path_id && (roam_length == max_roam_length || roam_length == 0)) {
        coords = city_view_grid_offset_to_pixel(destination_x, destination_y);
        draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 33, coords.x, coords.y, COLOR_MASK_NONE);
        text_draw(str, coords.x, coords.y, FONT_LARGE_BLACK, COLOR_BLACK);
        int tx = tile_x;
        int ty = tile_y;
        coords = city_view_grid_offset_to_pixel(tx, ty);
        image_draw(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
        for (int i = routing_path_current_tile; i < routing_path_length; i++) {
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
            coords = city_view_grid_offset_to_pixel(tx, ty);
            image_draw(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
        }
        coords = city_view_grid_offset_to_pixel(tx, ty);
        draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, coords.x, coords.y);
    }
    if (false && b->type) {
        const building_properties *props = building_properties_for_type(b->type);
        coords = city_view_grid_offset_to_pixel(b->grid_offset);
        draw_building(image_id_from_group(props->image_group) + props->image_offset, coords.x, coords.y);
//        draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, coords.x, coords.y);
//        image_draw(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
    }
    if (false && bdest->type) {
        const building_properties *props = building_properties_for_type(bdest->type);
        coords = city_view_grid_offset_to_pixel(bdest->grid_offset);
        draw_building(image_id_from_group(props->image_group) + props->image_offset, coords.x, coords.y, COLOR_MASK_RED);
    }
}

void hippodrome_horse_adjust(int *x, int *y, int val) {
//    int val = wait_ticks_missile;
    switch (city_view_orientation()) {
        case DIR_0_TOP_RIGHT:
            x += 10;
            if (val <= 10)
                y -= 2;
            else if (val <= 11)
                y -= 10;
            else if (val <= 12)
                y -= 18;
            else if (val <= 13)
                y -= 16;
            else if (val <= 20)
                y -= 14;
            else if (val <= 21)
                y -= 10;
            else
                y -= 2;
            break;
        case DIR_2_BOTTOM_RIGHT:
            x -= 10;
            if (val <= 9)
                y -= 12;
            else if (val <= 10)
                y += 4;
            else if (val <= 11) {
                x -= 5;
                y += 2;
            } else if (val <= 13)
                x -= 5;
            else if (val <= 20)
                y -= 2;
            else if (val <= 21)
                y -= 6;
            else
                y -= 12;
        case DIR_4_BOTTOM_LEFT:
            x += 20;
            if (val <= 9)
                y += 4;
            else if (val <= 10) {
                x += 10;
                y += 4;
            } else if (val <= 11) {
                x += 10;
                y -= 4;
            } else if (val <= 13)
                y -= 6;
            else if (val <= 20)
                y -= 12;
            else if (val <= 21)
                y -= 10;
            else {
                y -= 2;
            }
            break;
        case DIR_6_TOP_LEFT:
            x -= 10;
            if (val <= 9)
                y -= 12;
            else if (val <= 10)
                y += 4;
            else if (val <= 11)
                y += 2;
            else if (val <= 13) {
                // no change
            } else if (val <= 20)
                y -= 2;
            else if (val <= 21)
                y -= 6;
            else
                y -= 12;
            break;
    }
//    draw_figure_with_cart(x, y);
}
void figure::draw_fort_standard(int x, int y) {
    if (!formation_get(formation_id)->in_distant_battle) {
        // base
        image_draw(sprite_image_id, x, y);
        // flag
        int flag_height = image_get(cart_image_id)->height;
        image_draw(cart_image_id, x, y - flag_height);
        // top icon
        int icon_image_id =
                image_id_from_group(GROUP_FIGURE_FORT_STANDARD_ICONS) + formation_get(formation_id)->legion_id;
        image_draw(icon_image_id, x, y - image_get(icon_image_id)->height - flag_height);
    }
}
void figure::draw_map_flag(int x, int y) {
    // base
    image_draw(sprite_image_id, x, y);
    // flag
    image_draw(cart_image_id, x, y - image_get(cart_image_id)->height);
    // flag number
    int number = 0;
    int id = resource_id;
    if (id >= MAP_FLAG_INVASION_MIN && id < MAP_FLAG_INVASION_MAX)
        number = id - MAP_FLAG_INVASION_MIN + 1;
    else if (id >= MAP_FLAG_FISHING_MIN && id < MAP_FLAG_FISHING_MAX)
        number = id - MAP_FLAG_FISHING_MIN + 1;
    else if (id >= MAP_FLAG_HERD_MIN && id < MAP_FLAG_HERD_MAX)
        number = id - MAP_FLAG_HERD_MIN + 1;

    if (number > 0)
        text_draw_number_colored(number, '@', " ", x + 6, y + 7, FONT_NORMAL_PLAIN, COLOR_WHITE);

}

#include "window/city.h"

void figure::adjust_pixel_offset(int *x, int *y) {
    // determining x/y offset on tile
    int x_offset = 0;
    int y_offset = 0;
    if (use_cross_country) {
        tile_cross_country_offset_to_pixel_offset(cross_country_x % 15, cross_country_y % 15, &x_offset, &y_offset);
        y_offset -= missile_damage;
    } else {
        int dir = figure_image_normalize_direction(direction);
//        x_offset = tile_progress_to_pixel_offset_x(dir, progress_on_tile);
//        y_offset = tile_progress_to_pixel_offset_y(dir, progress_on_tile);
        if (progress_on_tile >= 15) {
            x_offset = 0;
            y_offset = 0;
        }
        switch (dir) {
            case DIR_0_TOP_RIGHT:
                x_offset = 2 * progress_on_tile - 28;
                y_offset = 14 - progress_on_tile;
                break;
            case DIR_1_RIGHT:
                x_offset = 4 * progress_on_tile - 56;
                y_offset = 0;
                break;
            case DIR_2_BOTTOM_RIGHT:
                x_offset = 2 * progress_on_tile - 28;
                y_offset = progress_on_tile - 14;
                break;
            case DIR_3_BOTTOM:
                x_offset = 0;
                y_offset = 2 * progress_on_tile - 28;
                break;
            case DIR_4_BOTTOM_LEFT:
                x_offset = 28 - 2 * progress_on_tile;
                y_offset = progress_on_tile - 14;
                break;
            case DIR_5_LEFT:
                x_offset = 56 - 4 * progress_on_tile;
                y_offset = 0;
                break;
            case DIR_6_TOP_LEFT:
                x_offset = 28 - 2 * progress_on_tile;
                y_offset = 14 - progress_on_tile;
                break;
            case DIR_7_TOP:
                x_offset = 0;
                y_offset = 28 - 2 * progress_on_tile;
                break;
        }
        y_offset -= current_height;
    }

    *x += x_offset + 29;
    *y += y_offset + 15 + 8;

//    const image *img = is_enemy_image ? image_get_enemy(sprite_image_id) : image_get(sprite_image_id);
//    *x += x_offset - img->sprite_offset_x;
//    *y += y_offset - img->sprite_offset_y;
}
void figure::draw_figure_main(int x, int y) {

    int _x = 0;
    int _y = 3;

    switch (type) {
        case FIGURE_IMMIGRANT:
            _y = 10;
            break;
//        case FIGURE_TRADE_CARAVAN:
//        case FIGURE_TRADE_CARAVAN_DONKEY:
//            _x = 20;
//            _y = -4;
//            break;
    }

    const image *img = is_enemy_image ? image_get_enemy(sprite_image_id) : image_get(sprite_image_id);
    if (is_enemy_image)
        image_draw_enemy(sprite_image_id, x + _x - img->sprite_offset_x, y + _y - img->sprite_offset_y);
    else
        image_draw(sprite_image_id, x + _x - img->sprite_offset_x, y + _y - img->sprite_offset_y);
}
void figure::draw_figure_cart(int x, int y) {
    const image *img = image_get(cart_image_id);
    image_draw(cart_image_id, x + x_offset_cart - img->sprite_offset_x, y + y_offset_cart - img->sprite_offset_y - 7);
}
void figure::draw_figure_with_cart(int x, int y) {
    draw_figure_cart(x, y);
    draw_figure_main(x, y);
    return; // pharaoh doesn't draw carts on top - to rework maybe later..?

    if (y_offset_cart >= 0) {
        draw_figure_main(x, y);
        draw_figure_cart(x, y);
    } else {
        draw_figure_cart(x, y);
        draw_figure_main(x, y);
    }
}
void figure::city_draw_figure(int x, int y, int highlight, pixel_coordinate *coord) {
    pixel_coordinate coords2 = city_view_grid_offset_to_pixel(tile_x, tile_y);
    adjust_pixel_offset(&x, &y);
    if (coord != nullptr) {
        highlight = 0;
        coord->x = x;
        coord->y = y;
    }

    // draw_figure()
    if (cart_image_id) {
        switch (type) {
            case FIGURE_CART_PUSHER:
            case FIGURE_WAREHOUSEMAN:
//            case FIGURE_LION_TAMER:
            case FIGURE_DOCKER:
            case FIGURE_NATIVE_TRADER:
//            case FIGURE_IMMIGRANT:
//            case FIGURE_EMIGRANT:
                draw_figure_with_cart(x, y);
                break;
            case FIGURE_HIPPODROME_HORSES:
                hippodrome_horse_adjust(&x, &y, wait_ticks_missile);
                draw_figure_with_cart(x, y);
                break;
            case FIGURE_FORT_STANDARD:
                draw_fort_standard(x, y);
                break;
            case FIGURE_MAP_FLAG:
                draw_map_flag(x, y);
                break;
            default:
                draw_figure_main(x, y);
                break;
        }
    } else {
        draw_figure_main(x, y);
        if (!is_enemy_image && highlight)
            image_draw_blend_alpha(sprite_image_id, x, y, COLOR_MASK_LEGION_HIGHLIGHT);
    }
}