#include "city_figure.h"

#include "city/view.h"
#include "figure/formation.h"
#include "figure/image.h"
#include "figuretype/editor.h"
#include "graphics/image.h"
#include "graphics/text.h"


static void tile_cross_country_offset_to_pixel_offset(int cross_country_x, int cross_country_y, int *pixel_x, int *pixel_y) {
    int dir = city_view_orientation();
    if (dir == DIR_0_TOP || dir == DIR_4_BOTTOM) {
        int base_pixel_x = 2 * cross_country_x - 2 * cross_country_y;
        int base_pixel_y = cross_country_x + cross_country_y;
        *pixel_x = dir == DIR_0_TOP ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_0_TOP ? base_pixel_y : -base_pixel_y;
    } else {
        int base_pixel_x = 2 * cross_country_x + 2 * cross_country_y;
        int base_pixel_y = cross_country_x - cross_country_y;
        *pixel_x = dir == DIR_2_RIGHT ? base_pixel_x : -base_pixel_x;
        *pixel_y = dir == DIR_6_LEFT ? base_pixel_y : -base_pixel_y;
    }
}
static int tile_progress_to_pixel_offset_x(int direction, int progress) {
    if (progress >= 15)
        return 0;

    switch (direction) {
        case DIR_0_TOP:
        case DIR_2_RIGHT:
            return 2 * progress - 28;
        case DIR_1_TOP_RIGHT:
            return 4 * progress - 56;
        case DIR_4_BOTTOM:
        case DIR_6_LEFT:
            return 28 - 2 * progress;
        case DIR_5_BOTTOM_LEFT:
            return 56 - 4 * progress;
        default:
            return 0;
    }
}
static int tile_progress_to_pixel_offset_y(int direction, int progress) {
    if (progress >= 15)
        return 0;

    switch (direction) {
        case DIR_0_TOP:
        case DIR_6_LEFT:
            return 14 - progress;
        case DIR_2_RIGHT:
        case DIR_4_BOTTOM:
            return progress - 14;
        case DIR_3_BOTTOM_RIGHT:
            return 2 * progress - 28;
        case DIR_7_TOP_LEFT:
            return 28 - 2 * progress;
        default:
            return 0;
    }
}
static void tile_progress_to_pixel_offset(int direction, int progress, int *pixel_x, int *pixel_y) {
    *pixel_x = tile_progress_to_pixel_offset_x(direction, progress);
    *pixel_y = tile_progress_to_pixel_offset_y(direction, progress);
}

#include "widget/city_building_ghost.h"
#include "building/properties.h"
#include "figure/route.h"

void figure::draw_debug() {
    building *b = building_get(building_id);
    building *bdest = building_get(destination_building_id);

    pixel_offset coords;

//    coords = city_view_grid_offset_to_pixel(destination_grid_offset);
//    draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, coords.x, coords.y);

    if (routing_path_id) {
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
    if (b->type) {
        const building_properties *props = building_properties_for_type(b->type);
        coords = city_view_grid_offset_to_pixel(b->grid_offset);
        draw_building(image_id_from_group(props->image_group) + props->image_offset, coords.x, coords.y);
//        draw_building(image_id_from_group(GROUP_SUNKEN_TILE) + 20, coords.x, coords.y);
//        image_draw(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, coords.x, coords.y);
    }
    if (bdest->type) {
        const building_properties *props = building_properties_for_type(bdest->type);
        coords = city_view_grid_offset_to_pixel(bdest->grid_offset);
        draw_building(image_id_from_group(props->image_group) + props->image_offset, coords.x, coords.y);
    }
}
void figure::adjust_pixel_offset(int *x, int *y) {
    // determining x/y offset on tile
    int x_offset = 0;
    int y_offset = 0;
    if (use_cross_country) {
        tile_cross_country_offset_to_pixel_offset(cross_country_x % 15, cross_country_y % 15, &x_offset, &y_offset);
        y_offset -= missile_damage;
    } else {
        tile_progress_to_pixel_offset(figure_image_normalize_direction(direction), progress_on_tile, &x_offset, &y_offset);
        y_offset -= current_height;
    }

    x_offset += 29;
    y_offset += 15 + 8;

    const image *img = is_enemy_image ? image_get_enemy(image_id) : image_get(image_id);
    *x += x_offset - img->sprite_offset_x;
    *y += y_offset - img->sprite_offset_y;
}
void figure::draw_figure(int x, int y, int highlight)
{
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
                draw_hippodrome_horse(x, y);
                break;
            case FIGURE_FORT_STANDARD:
                draw_fort_standard(x, y);
                break;
            case FIGURE_MAP_FLAG:
                draw_map_flag(x, y);
                break;
            default:
                image_draw(image_id, x, y);
                break;
        }
    } else {
        if (is_enemy_image)
            image_draw_enemy(image_id, x, y);
        else {
            image_draw(image_id, x, y);
            if (highlight)
                image_draw_blend_alpha(image_id, x, y, COLOR_MASK_LEGION_HIGHLIGHT);
        }
    }
    draw_debug();
}
void figure::city_draw_figure(int x, int y, int highlight)
{
    adjust_pixel_offset(&x, &y);
    draw_figure(x, y, highlight);
}
void figure::city_draw_selected_figure(int x, int y, pixel_coordinate *coord)
{
    adjust_pixel_offset(&x, &y);
    draw_figure(x, y, 0);
    coord->x = x;
    coord->y = y;
}

void figure::draw_figure_with_cart(int x, int y) {
    if (y_offset_cart >= 0) {
        image_draw(image_id, x, y);
        image_draw(cart_image_id, x + x_offset_cart, y + y_offset_cart);
    } else {
        image_draw(cart_image_id, x + x_offset_cart, y + y_offset_cart);
        image_draw(image_id, x, y);
    }
}
void figure::draw_hippodrome_horse(int x, int y) {
    int val = wait_ticks_missile;
    switch (city_view_orientation()) {
        case DIR_0_TOP:
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
        case DIR_2_RIGHT:
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
        case DIR_4_BOTTOM:
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
        case DIR_6_LEFT:
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
    draw_figure_with_cart(x, y);
}
void figure::draw_fort_standard(int x, int y) {
    if (!formation_get(formation_id)->in_distant_battle) {
        // base
        image_draw(image_id, x, y);
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
    image_draw(image_id, x, y);
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