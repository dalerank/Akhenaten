#include "ornaments.h"

#include "building/building.h"
#include "building/model.h"
#include "building/building_dock.h"
#include "building/building_granary.h"
#include "building/building_education.h"
#include "building/building_workshop.h"
#include "building/building_farm.h"
#include "building/monuments.h"
#include "building/building_animation.h"
#include "building/monument_mastaba.h"
#include "city/buildings.h"
#include "city/floods.h"
#include "city/labor.h"
#include "city/ratings.h"
#include "core/direction.h"
#include "game/time.h"
#include "graphics/graphics.h"
#include "graphics/image_desc.h"
#include "graphics/image.h"
#include "graphics/view/lookup.h"
#include "grid/floodplain.h"
#include "grid/image.h"
#include "grid/property.h"
#include "grid/random.h"
#include "grid/terrain.h"
#include <cmath>

void building_draw_normal_anim(painter &ctx, vec2i pixel, building *b, tile2i tile, const animation_t &anim, int color_mask) {
    if (anim.pack > 0 && anim.iid > 0) {
        int anim_id = image_id_from_group(anim.pack, anim.iid) + anim.offset;
        building_draw_normal_anim(ctx, pixel + anim.pos, b, tile, anim_id, color_mask, 0, anim.max_frames);
        return;
    }

    if (anim.anim_id <= 0) {
        return;
    }
    int anim_id = image_group(anim.anim_id);
    int base_id = anim.base_id > 0 ? image_group(anim.base_id) : 0;

    building_draw_normal_anim(ctx, pixel + anim.pos, b, tile, anim_id, color_mask, base_id, anim.max_frames);
}

void building_draw_normal_anim(painter &ctx, vec2i pos, building* b, tile2i tile, int sprite_id, int color_mask, int base_id, int max_frames) {
    if (!sprite_id) {
        return;
    }

    int grid_offset = tile.grid_offset();
    if (!base_id) {
        base_id = map_image_at(grid_offset);
    }

    int animation_offset = building_animation_offset(b, base_id, grid_offset, max_frames);
    if (animation_offset == 0) {
        return;
    }

    if (base_id == sprite_id) {
        ImageDraw::img_ornament(ctx, sprite_id + animation_offset, base_id, pos.x, pos.y, color_mask);
    } else {
        ImageDraw::img_sprite(ctx, sprite_id + animation_offset, pos.x, pos.y, color_mask);
    }
}


static void draw_gatehouse_anim(int x, int y, building* b, painter &ctx) {
    int xy = map_property_multi_tile_xy(b->tile.grid_offset());
    int orientation = city_view_orientation();
    if ((orientation == DIR_0_TOP_RIGHT && xy == EDGE_X1Y1) || (orientation == DIR_2_BOTTOM_RIGHT && xy == EDGE_X0Y1)
        || (orientation == DIR_4_BOTTOM_LEFT && xy == EDGE_X0Y0)
        || (orientation == DIR_6_TOP_LEFT && xy == EDGE_X1Y0)) {
        int image_id = image_id_from_group(GROUP_BULIDING_GATEHOUSE);
        int color_mask = drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0;
        if (b->subtype.orientation == 1) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(ctx, image_id, x - 22, y - 80, color_mask);
            else
                ImageDraw::img_generic(ctx, image_id + 1, x - 18, y - 81, color_mask);
        } else if (b->subtype.orientation == 2) {
            if (orientation == DIR_0_TOP_RIGHT || orientation == DIR_4_BOTTOM_LEFT)
                ImageDraw::img_generic(ctx, image_id + 1, x - 18, y - 81, color_mask);
            else
                ImageDraw::img_generic(ctx, image_id, x - 22, y - 80, color_mask);
        }
    }
}

/////// ORNAMENTS

static void draw_hippodrome_ornaments(vec2i pixel, map_point point, painter &ctx) {
    int grid_offset = point.grid_offset();
    int x = pixel.x;
    int y = pixel.y;
    int image_id = map_image_at(grid_offset);
    const image_t* img = image_get(image_id);
    building* b = building_at(grid_offset);
    if (img->animation.num_sprites && map_property_is_draw_tile(grid_offset) && b->type == BUILDING_SENET_HOUSE) {
        ImageDraw::img_generic(ctx, image_id + 1, x + img->animation.sprite_offset.x, y + img->animation.sprite_offset.y - img->height + 90, drawing_building_as_deleted(b) ? COLOR_MASK_RED : 0);
    }
}

void draw_ornaments_flat(vec2i point, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    // tile must contain image draw data
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    int image_id = map_image_at(grid_offset);
    building* b = building_at(grid_offset);

    if (b->type == 0 || b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    // draw in red if necessary
    int color_mask = 0;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset)) {
        color_mask = COLOR_MASK_RED;
    }

    b->dcast()->draw_ornaments_and_animations_flat(ctx, point, tile, color_mask);
}

void draw_ornaments_and_animations_height(vec2i point, tile2i tile, painter &ctx) {
    int grid_offset = tile.grid_offset();
    // tile must contain image draw data
    if (!map_property_is_draw_tile(grid_offset)) {
        return;
    }

    int image_id = map_image_at(grid_offset);
    building* b = building_at(grid_offset);
    if (b->type == BUILDING_STORAGE_YARD && b->state == BUILDING_STATE_CREATED) {
        ImageDraw::img_generic(ctx, image_id + 17, point.x - 5, point.y - 42);
    }

    if (b->type == 0 || b->state == BUILDING_STATE_UNUSED) {
        return;
    }

    // draw in red if necessary
    int color_mask = 0;
    if (drawing_building_as_deleted(b) || map_property_is_deleted(grid_offset)) {
        color_mask = COLOR_MASK_RED;
    }

    switch (b->type) {
    case BUILDING_BURNING_RUIN:
        building_draw_normal_anim(ctx, point, b, tile, image_id, color_mask);
        break;

    case BUILDING_GRANITE_QUARRY:
        building_draw_normal_anim(ctx, point + vec2i{54, 15}, b, tile, image_id_from_group(PACK_SPR_AMBIENT, 49) - 1, color_mask);
        break; 

    case BUILDING_MUD_GATEHOUSE:
        draw_gatehouse_anim(point.x, point.y, b, ctx);
        break;

    default:
        b->dcast()->draw_ornaments_and_animations_height(ctx, point, tile, color_mask);
        break;
    }

    // specific buildings
    building_workshop_draw_raw_material_storage(ctx, b, point, color_mask);
    //    draw_hippodrome_ornaments(pixel, point);
}