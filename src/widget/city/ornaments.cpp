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
#include "city/city_floods.h"
#include "city/labor.h"
#include "city/ratings.h"
#include "city/city_buildings.h"
#include "core/direction.h"
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
    }
}

void building_draw_normal_anim(painter &ctx, vec2i pos, building* b, tile2i tile, int sprite_id, int color_mask, int base_id, int max_frames, int duration) {
    if (!sprite_id) {
        return;
    }

    int grid_offset = tile.grid_offset();
    if (!base_id) {
        base_id = map_image_at(grid_offset);
    }

    int animation_offset = building_animation_offset(b, base_id, grid_offset, max_frames, duration);
    if (animation_offset == 0) {
        return;
    }

    if (base_id == sprite_id) {
        ImageDraw::img_ornament(ctx, sprite_id + animation_offset, base_id, pos.x, pos.y, color_mask);
    } else {
        ImageDraw::img_sprite(ctx, sprite_id + animation_offset, pos.x, pos.y, color_mask);
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

    b->dcast()->draw_ornaments_and_animations_height(ctx, point, tile, color_mask);
}