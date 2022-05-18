#include <core/string.h>
#include <cmath>
#include <city/view/lookup.h>
#include <dev/debug.h>

#include "city/view/view.h"
#include "formation.h"
#include "image.h"
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

#include "widget/city/building_ghost.h"
#include "building/properties.h"
#include "figure/route.h"
#include "window/city.h"

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
        ImageDraw::img_generic(sprite_image_id, x, y);
        // flag
        int flag_height = image_get(cart_image_id)->height;
        ImageDraw::img_generic(cart_image_id, x, y - flag_height);
        // top icon
        int icon_image_id =
                image_id_from_group(GROUP_FIGURE_FORT_STANDARD_ICONS) + formation_get(formation_id)->legion_id;
        ImageDraw::img_generic(icon_image_id, x, y - image_get(icon_image_id)->height - flag_height);
    }
}
void figure::draw_map_flag(int x, int y) {
    // base
    ImageDraw::img_generic(sprite_image_id, x, y);
    // flag
    ImageDraw::img_generic(cart_image_id, x, y - image_get(cart_image_id)->height);
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
        tile_cross_country_offset_to_pixel_offset(cc_coords.x % 15, cc_coords.y % 15, &x_offset, &y_offset);
        y_offset -= missile_damage;
    } else {
        int dir = figure_image_normalize_direction(direction);
//        x_offset = tile_progress_to_pixel_offset_x(dir, progress_on_tile);
//        y_offset = tile_progress_to_pixel_offset_y(dir, progress_on_tile);
//        if (progress_on_tile == 15) {
//            x_offset = 0;
//            y_offset = 0;
//        }

        int adjusted_progress = progress_on_tile;
        if (progress_on_tile >= 8)
            adjusted_progress -= 15;
//        else
//            adjusted_progress -= 1;

        switch (dir) {
            case DIR_0_TOP_RIGHT:
                x_offset += 2 * adjusted_progress;
                y_offset -= adjusted_progress;
                break;
            case DIR_1_RIGHT:
                x_offset += 4 * adjusted_progress;
                y_offset = 0;
                break;
            case DIR_2_BOTTOM_RIGHT:
                x_offset += 2 * adjusted_progress;
                y_offset += adjusted_progress;
                break;
            case DIR_3_BOTTOM:
                x_offset = 0;
                y_offset += 2 * adjusted_progress;
                break;
            case DIR_4_BOTTOM_LEFT:
                x_offset -= 2 * adjusted_progress;
                y_offset += adjusted_progress;
                break;
            case DIR_5_LEFT:
                x_offset -= 4 * adjusted_progress;
                y_offset = 0;
                break;
            case DIR_6_TOP_LEFT:
                x_offset -= 2 * adjusted_progress;
                y_offset -= adjusted_progress;
                break;
            case DIR_7_TOP:
                x_offset = 0;
                y_offset -= 2 * adjusted_progress;
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

    int x_correction = 0;
    int y_correction = 3;

    switch (type) {
        case FIGURE_IMMIGRANT: // todo: mmmmmmaybe I was using the wrong draw function all along. look into this
            y_correction = 10;
            break;
//        case FIGURE_TRADE_CARAVAN:
//        case FIGURE_TRADE_CARAVAN_DONKEY:
//            _x = 20;
//            _y = -4;
//            break;
    }

    const image *img = is_enemy_image ? image_get_enemy(sprite_image_id) : image_get(sprite_image_id);
    if (is_enemy_image)
        ImageDraw::img_enemy(sprite_image_id, x + x_correction, y + y_correction);
    else
        ImageDraw::img_generic(sprite_image_id, x + x_correction, y + y_correction);
}
void figure::draw_figure_cart(int x, int y) {
    const image *img = image_get(cart_image_id);
    ImageDraw::img_generic(cart_image_id, x + cart_offset.x - img->animation.sprite_x_offset,
                           y + cart_offset.y - img->animation.sprite_y_offset - 7);
}
void figure::draw_figure_with_cart(int x, int y) {
    draw_figure_cart(x, y);
    draw_figure_main(x, y);
    return; // pharaoh doesn't draw carts on top - to rework maybe later..?

    if (cart_offset.y >= 0) {
        draw_figure_main(x, y);
        draw_figure_cart(x, y);
    } else {
        draw_figure_cart(x, y);
        draw_figure_main(x, y);
    }
}
void figure::city_draw_figure(int x, int y, int highlight, pixel_coordinate *coord) {
    pixel_coordinate coords2 = mappoint_to_pixel(map_point(tile.x(), tile.y()));
    adjust_pixel_offset(&x, &y);
    if (coord != nullptr) {
        highlight = 0;
        coord->x = x;
        coord->y = y;
    }

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
            ImageDraw::img_alpha_blended(sprite_image_id, x, y, COLOR_MASK_LEGION_HIGHLIGHT);
    }
//    draw_debug();
}