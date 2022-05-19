#include <core/string.h>
#include <cmath>
#include <city/view/lookup.h>
#include <dev/debug.h>
#include <d2d1.h>

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

void figure::draw_fort_standard(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {
    if (!formation_get(formation_id)->in_distant_battle) {
        // base
        ImageDraw::img_generic(sprite_image_id, pixel.x, pixel.y);
        // flag
        int flag_height = image_get(cart_image_id)->height;
        ImageDraw::img_generic(cart_image_id, pixel.x, pixel.y - flag_height);
        // top icon
        int icon_image_id =
                image_id_from_group(GROUP_FIGURE_FORT_STANDARD_ICONS) + formation_get(formation_id)->legion_id;
        ImageDraw::img_generic(icon_image_id, pixel.x, pixel.y - image_get(icon_image_id)->height - flag_height);
    }
}
void figure::draw_map_flag(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {
    // base
    ImageDraw::img_generic(sprite_image_id, pixel.x, pixel.y);
    // flag
    ImageDraw::img_generic(cart_image_id, pixel.x, pixel.y - image_get(cart_image_id)->height);
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
        text_draw_number_colored(number, '@', " ", pixel.x + 6, pixel.y + 7, FONT_NORMAL_PLAIN, COLOR_WHITE);

}

#include "window/city.h"

void figure::adjust_pixel_offset(pixel_coordinate *pixel) {
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

    pixel->x += x_offset + 29;
    pixel->y += y_offset + 15 + 8;

//    const image *img = is_enemy_image ? image_get_enemy(sprite_image_id) : image_get(sprite_image_id);
//    *x += x_offset - img->sprite_offset_x;
//    *y += y_offset - img->sprite_offset_y;
}
void figure::draw_figure_main(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {

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
        ImageDraw::img_enemy(sprite_image_id, pixel.x + x_correction, pixel.y + y_correction, COLOR_MASK_NONE);
    else
        ImageDraw::img_sprite(sprite_image_id, pixel.x + x_correction, pixel.y + y_correction, COLOR_MASK_NONE);
}
void figure::draw_figure_cart(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {
    const image *img = image_get(cart_image_id);
    ImageDraw::img_generic(cart_image_id, pixel.x + cart_offset.x - img->animation.sprite_x_offset,
                           pixel.y + cart_offset.y - img->animation.sprite_y_offset - 7);
}
void figure::draw_figure_with_cart(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {
    draw_figure_cart(pixel, highlight, coord_out);
    draw_figure_main(pixel, highlight, coord_out);
    return; // pharaoh doesn't draw carts on top - to rework maybe later..?

    if (cart_offset.y >= 0) {
        draw_figure_main(pixel, highlight, coord_out);
        draw_figure_cart(pixel, highlight, coord_out);
    } else {
        draw_figure_cart(pixel, highlight, coord_out);
        draw_figure_main(pixel, highlight, coord_out);
    }
}
void figure::city_draw_figure(pixel_coordinate pixel, int highlight, pixel_coordinate *coord_out) {
//    pixel_coordinate coords2 = mappoint_to_pixel(map_point(tile.x(), tile.y()));
    adjust_pixel_offset(&pixel);
    if (coord_out != nullptr) {
        highlight = 0;
        coord_out->x = pixel.x;
        coord_out->y = pixel.y;
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
                draw_figure_with_cart(pixel, highlight, coord_out);
                break;
//            case FIGURE_HIPPODROME_HORSES:
//                hippodrome_horse_adjust(&x, &y, wait_ticks_missile);
//                draw_figure_with_cart(pixel, highlight, coord_out);
//                break;
            case FIGURE_FORT_STANDARD:
                draw_fort_standard(pixel, highlight, coord_out);
                break;
            case FIGURE_MAP_FLAG:
                draw_map_flag(pixel, highlight, coord_out);
                break;
            default:
                draw_figure_main(pixel, highlight, coord_out);
                break;
        }
    } else {
        draw_figure_main(pixel, highlight, coord_out);
        if (!is_enemy_image && highlight)
            ImageDraw::img_sprite(sprite_image_id, pixel.x, pixel.y, COLOR_MASK_LEGION_HIGHLIGHT);
//            ImageDraw::img_alpha_blended(sprite_image_id, pixel.x, pixel.y, COLOR_MASK_LEGION_HIGHLIGHT);
    }
//    draw_debug();
}