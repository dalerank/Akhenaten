#include "building_gatehouse.h"

#include "grid/property.h"
#include "core/direction.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "io/gamefiles/lang.h"
#include "graphics/graphics.h"
#include "widget/city/ornaments.h"
#include "building/rotation.h"
#include "construction/build_planner.h"
#include "city/city.h"

building_brick_gatehouse::static_params brick_gatehouse_m;
building_mud_gatehouse::static_params mud_gatehouse_m;

template<typename T>
void building_gatehouse::static_params_t<T>::planer_ghost_preview(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel) const {
    bool fully_blocked = false;
    bool blocked = false, tmp_blocked;
    if (g_city.finance.is_out_of_money()) {
        fully_blocked = true;
        blocked = true;
    }

    int local_rotation = -1;

    uint32_t restricted_terrain = TERRAIN_ALL;
    restricted_terrain -= TERRAIN_ROAD;
    
    tile2i tile_second_part;

    const int city_orientation = city_view_orientation() / 2;
    tile2i possible_next, possible_next_w;
    blocked_tile_vec tmp_tiles;
    switch (city_orientation) {
    case 0:
        possible_next = end.shifted(0, -1);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 0;
            tile_second_part = possible_next;
        }

        possible_next_w = end.shifted(1, 0);
        tmp_tiles.clear();
        tmp_blocked = !!planer.is_blocked_for_building(possible_next_w, 1, tmp_tiles, restricted_terrain);
        if (!tmp_blocked) {
            local_rotation = 1;
            tile_second_part = possible_next_w;
            break;
        }
        break;
    
    case 1:
        break;
    
    case 2:
        break;
    
    case 3:
        break;
    }

    blocked_tile_vec blocked_tiles_main;
    blocked_tile_vec blocked_tiles_second;

    if (local_rotation >= 0) {
        blocked |= !!planer.is_blocked_for_building(end, 1, blocked_tiles_main, restricted_terrain);
        blocked |= !!planer.is_blocked_for_building(tile_second_part, 1, blocked_tiles_second, restricted_terrain);
    } else {
        blocked = true;
        blocked_tiles_main.clear();
        blocked_tiles_second.clear();
        blocked_tiles_main.push_back({ end, true });
        blocked_tiles_main.push_back({ end.shifted(0, -1), true });
    }

    int orientation_index = building_rotation_get_storage_fort_orientation(local_rotation) / 2;
    vec2i main_pixel = pixel + this->ghost.main_view_offset[orientation_index];
    vec2i ground_pixel = pixel + this->ghost.part_view_offset[orientation_index];

    if (blocked) {
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_main);
        planer.draw_partially_blocked(ctx, fully_blocked, blocked_tiles_second);
    } else {
        if (orientation_index == 0 || orientation_index == 3) {
            // draw fort first, then ground
            int image_id = this->anim["base_n"].first_img();
            int image_sec_id = this->anim["base_second_n"].first_img();
            planer.draw_building_ghost(ctx, image_sec_id, ground_pixel);
            planer.draw_building_ghost(ctx, image_id, main_pixel);
        } else {
            // draw ground first, then fort
            int image_id = this->anim["base_w"].first_img();
            int image_sec_id = this->anim["base_second_w"].first_img();
            planer.draw_building_ghost(ctx, image_sec_id, main_pixel);
            planer.draw_building_ghost(ctx, image_id, ground_pixel);
        }
    }
}

template<typename T>
void building_gatehouse::static_params_t<T>::planer_ghost_blocked(build_planner &planer, painter &ctx, tile2i start, tile2i end, vec2i pixel, bool fully_blocked) const {
    planer_ghost_preview(planer, ctx, start, end, pixel);
}

void building_gatehouse::on_create(int orientation) {
    base.orientation = orientation;
}

void building_gatehouse::on_place_update_tiles(int orientation, int variant) {
    const auto &p = building_impl::params(type());
    map_building_tiles_add(id(), tile(), p.building_size, p.anim["base"].first_img() + orientation, TERRAIN_BUILDING | TERRAIN_GATEHOUSE);
    map_terrain_add_gatehouse_roads(tilex(), tiley(), orientation);
}

void building_gatehouse::on_place_checks() {
    /*nothing*/
}

bool building_mud_gatehouse::draw_ornaments_and_animations_height(painter &ctx, vec2i point, tile2i tile, color color_mask) {
    int xy = map_property_multi_tile_xy(tile.grid_offset());
    int orientation = city_view_orientation();
    int x = point.x;
    int y = point.y;
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) || (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1)
        || (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0)
        || (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = mud_gatehouse_m.anim["base"].first_img();
        int color_mask = drawing_building_as_deleted(&base) ? COLOR_MASK_RED : 0;
        if (base.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(ctx, image_id, x - 22, y - 80, color_mask);
            else
                ImageDraw::img_generic(ctx, image_id + 1, x - 18, y - 81, color_mask);
        } else if (base.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(ctx, image_id + 1, x - 18, y - 81, color_mask);
            else
                ImageDraw::img_generic(ctx, image_id, x - 22, y - 80, color_mask);
        }
    }
    return true;
}

void building_mud_gatehouse::update_map_orientation(int orientation) {
    int image_id = mud_gatehouse_m.anim["base"].first_img();
    int map_orientation = city_view_orientation();
    int orientation_is_top_bottom = map_orientation == DIR_0_TOP_RIGHT || map_orientation == DIR_4_BOTTOM_LEFT;
    if (base.orientation == 1) {
        if (orientation_is_top_bottom)
            image_id += 1;
        else {
            image_id += 2;
        }
    } else {
        if (orientation_is_top_bottom)
            image_id += 2;
        else {
            image_id += 1;
        }
    }
    map_building_tiles_add(id(), tile(), base.size, image_id, TERRAIN_GATEHOUSE | TERRAIN_BUILDING);
    map_terrain_add_gatehouse_roads(tilex(), tiley(), 0);
}
