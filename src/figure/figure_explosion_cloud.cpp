#include "figure/figure.h"

#include "core/profiler.h"
#include "graphics/image.h"

#include <algorithm>

static const int CLOUD_TILE_OFFSETS[] = {0, 0, 0, 1, 1, 2};
static const int CLOUD_CC_OFFSETS[] = {0, 7, 14, 7, 14, 7};
static const int CLOUD_SPEED[] = {1, 2, 1, 3, 2, 1, 3, 2, 1, 1, 2, 1, 2, 1, 3, 1};

static const vec2i CLOUD_DIRECTION[] = {
    {0, -6}, {-2, -5}, {-4, -4}, {-5, -2}, {-6, 0}, {-5, -2}, {-3, -3}, {-3, -6},
    {0, 6}, {2, 5}, {4, 4}, {5, 2}, {6, 0}, {5, 2}, {3, 3}, {3, 6}
};

void figure_create_explosion_cloud(tile2i tile, int size) {
    int tile_offset = CLOUD_TILE_OFFSETS[size];
    int cc_offset = CLOUD_CC_OFFSETS[size];
    for (int i = 0; i < 16; i++) {
        figure* f = figure_create(FIGURE_EXPLOSION, tile.shifted(tile_offset, tile_offset), DIR_0_TOP_RIGHT);
        if (f->id) {
            f->cc_coords.x += cc_offset;
            f->cc_coords.y += cc_offset;
            f->destination_tile = tile.shifted(CLOUD_DIRECTION[i].x, CLOUD_DIRECTION[i].y);
            f->set_cross_country_direction(f->cc_coords.x, f->cc_coords.y, 15 * f->destination_tile.x() + cc_offset, 15 * f->destination_tile.y() + cc_offset, true);
            f->speed_multiplier = CLOUD_SPEED[i];
        }
    }
}

void figure::explosion_cloud_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Explode Cloud");
    use_cross_country = true;
    progress_on_tile++;
    if (progress_on_tile > 44) {
        poof();
    }

    move_ticks_cross_country(speed_multiplier);
    if (progress_on_tile < 48) {
        sprite_image_id = image_id_from_group(IMG_EXPLOSION) + std::clamp(progress_on_tile / 2, 0, MAX_CLOUD_IMAGE_OFFSETS);
    } else {
        sprite_image_id = image_id_from_group(IMG_EXPLOSION) + MAX_CLOUD_IMAGE_OFFSETS;
    }
    anim_base = 0;
}