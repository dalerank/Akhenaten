#include "app/app.h"
#include "dev/debug.h"

#include "building/building.h"
#include "building/building_statue.h"
#include "building/building_temple_complex.h"
#include "building/construction/build_planner.h"
#include "grid/building.h"
#include "grid/property.h"
#include "grid/sprite.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "graphics/text.h"

static int north_tile_grid_offset(int x, int y) {
    int grid_offset = MAP_OFFSET(x, y);
    int size = map_property_multi_tile_size(grid_offset);
    for (int i = 0; i < size && map_property_multi_tile_x(grid_offset); i++) {
        grid_offset += GRID_OFFSET(-1, 0);
    }

    for (int i = 0; i < size && map_property_multi_tile_y(grid_offset); i++) {
        grid_offset += GRID_OFFSET(0, -1);
    }

    return grid_offset;
}

static void draw_sprite_frames_tile(vec2i pixel, tile2i point, painter &ctx) {
    const int grid_offset = point.grid_offset();
    const int x = pixel.x + 15;
    const int y = pixel.y;
    const int x1 = pixel.x + 8 + 30;
    char str[64];

    const int b_id = map_building_at(grid_offset);
    building *b = building_get(b_id);

    if (b_id && grid_offset == b->tile.grid_offset()) {
        ghost_draw::draw_building_ghost(ctx, image_id_from_group(GROUP_SUNKEN_TILE) + 3, {x - 15, y}, COLOR_MASK_GREEN);
    }
    if (b_id && grid_offset == north_tile_grid_offset(b->tile.x(), b->tile.y())) {
        ctx.img_generic(image_id_from_group(GROUP_DEBUG_WIREFRAME_TILE) + 3, {x - 15, y}, COLOR_MASK_RED);
    }

    const int anim = map_sprite_animation_at(grid_offset);
    if (anim) {
        text_draw(bstring32(anim).c_str(), x, y + 10, FONT_SMALL_OUTLINED, COLOR_WHITE);
    }

    if (b_id && map_property_is_draw_tile(grid_offset) && b->labor_category != LABOR_CATEGORY_NONE) {
        switch (b->type) {
        default:
            break;
        case BUILDING_SMALL_STATUE:
        case BUILDING_MEDIUM_STATUE:
        case BUILDING_LARGE_STATUE: {
            auto statue = b->dcast_statue();
            debug_text(ctx, str, x1, y + 10, 0, "", statue->runtime_data().variant, COLOR_WHITE);
            break;
        }
        case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        case BUILDING_TEMPLE_COMPLEX_RA:
        case BUILDING_TEMPLE_COMPLEX_PTAH:
        case BUILDING_TEMPLE_COMPLEX_SETH:
        case BUILDING_TEMPLE_COMPLEX_BAST: {
            auto complex = b->dcast_temple_complex();
            auto &d = complex->runtime_data();
            debug_text(ctx, str, x1, y + 10, 0, "", d.variant, COLOR_WHITE);
            debug_text(ctx, str, x1, y + 20, 0, "", d.temple_complex_upgrades, COLOR_LIGHT_BLUE);
            break;
        }
        }
    }
}

void ANK_REGISTER_APPLICATION_MODULE(register_sprite_frames_debug) {
    g_debug.add_tile_render_handler("sprite_frames", draw_sprite_frames_tile);
}
