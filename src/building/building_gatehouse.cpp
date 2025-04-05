#include "building_gatehouse.h"

#include "js/js_game.h"
#include "grid/property.h"
#include "city/labor.h"
#include "core/direction.h"
#include "grid/terrain.h"
#include "grid/building_tiles.h"
#include "window/building/common.h"
#include "graphics/elements/ui.h"
#include "io/gamefiles/lang.h"
#include "graphics/graphics.h"
#include "widget/city/ornaments.h"

buildings::model_t<building_brick_gatehouse> brick_gatehouse_m;
buildings::model_t<building_mud_gatehouse> mud_gatehouse_m;

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

void building_mud_gatehouse::window_info_background(object_info &c) {
    c.help_id = 85;
    window_building_play_sound(&c, "Wavs/gatehouse.wav");
    outer_panel_draw(c.offset, c.bgsize.x, c.bgsize.y);
    lang_text_draw_centered(e_text_gate_house, 0, c.offset.x, c.offset.y + 10, 16 * c.bgsize.x, FONT_LARGE_BLACK_ON_LIGHT);
    window_building_draw_description_at(c, 16 * c.bgsize.y - 158, 90, 1);
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
