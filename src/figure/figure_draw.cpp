#include "core/string.h"
#include "dev/debug.h"
#include "graphics/view/lookup.h"

#include "figuretype/editor.h"
#include "formation.h"
#include "graphics/boilerplate.h"
#include "graphics/text.h"
#include "image.h"

void figure::draw_fort_standard(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
    if (!formation_get(formation_id)->in_distant_battle) {
        // base
        ImageDraw::img_generic(sprite_image_id, pixel.x, pixel.y);
        // flag
        int flag_height = image_get(cart_image_id)->height;
        ImageDraw::img_generic(cart_image_id, pixel.x, pixel.y - flag_height);
        // top icon
        int icon_image_id
          = image_id_from_group(GROUP_FIGURE_FORT_STANDARD_ICONS) + formation_get(formation_id)->legion_id;
        ImageDraw::img_generic(icon_image_id, pixel.x, pixel.y - image_get(icon_image_id)->height - flag_height);
    }
}
void figure::draw_map_flag(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
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
        text_draw_number_colored(number, '@', " ", pixel.x + 6, pixel.y + 7, FONT_SMALL_PLAIN, COLOR_WHITE);
}

void figure::adjust_pixel_offset(pixel_coordinate* pixel) {
    // determining x/y offset on tile
    int x_offset = 0;
    int y_offset = 0;
    if (use_cross_country) {
        auto cc_offets = tile_pixel_coords();
        x_offset = cc_offets.x;
        y_offset = cc_offets.y;
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
void figure::draw_figure_main(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
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

    const image_t* img = is_enemy_image ? image_get_enemy(sprite_image_id) : image_get(sprite_image_id);
    ImageDraw::img_sprite(sprite_image_id, pixel.x + x_correction, pixel.y + y_correction, COLOR_MASK_NONE);
}
void figure::draw_figure_cart(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
    const image_t* img = image_get(cart_image_id);
    ImageDraw::img_sprite(cart_image_id, pixel.x + cart_offset.x, pixel.y + cart_offset.y - 7);
}
void figure::draw_figure_with_cart(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
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
void figure::city_draw_figure(pixel_coordinate pixel, int highlight, pixel_coordinate* coord_out) {
    // This is to update the sprite's direction when rotating the city view.
    // Unfortunately, because the only thing we have at the time of file loading is
    // the raw sprite image id, it doesn't work if we haven't performed at least a
    // single frame of figure action after loading a file (i.e. if paused instantly)
    figure_image_update(true);

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
    }
}