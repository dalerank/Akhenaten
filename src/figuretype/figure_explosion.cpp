#include "figure_explosion.h"

#include "core/profiler.h"
#include "graphics/image.h"
#include "graphics/animkeys.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_explosion);

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

void figure_explosion::figure_action() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Figure/Explode Cloud");
    base.use_cross_country = true;
    base.progress_on_tile++;
    if (base.progress_on_tile > 44) {
        poof();
    }

    base.move_ticks_cross_country(base.speed_multiplier);
}

void figure_explosion::update_animation() {
    int img_id = anim(animkeys().poof).first_img();
    if (base.progress_on_tile < 48) {
        base.main_image_id = img_id + std::clamp(base.progress_on_tile / 2, 0, MAX_CLOUD_IMAGE_OFFSETS);
    } else {
        base.main_image_id = img_id + MAX_CLOUD_IMAGE_OFFSETS;
    }
    base.animctx.base = 0;
}
