#include "figure_seagulls.h"

#include "core/random.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seagulls);

void figure_seagulls::on_create() {
    figure_impl::on_create();
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    base.set_flag(e_figure_flag_invisible, true);
}

void figure_seagulls::figure_action() {
    // OG figure_seagulls_action (0x0049B390): terrain ANY, ghost, cross-country — no AI/draw.
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    base.set_flag(e_figure_flag_invisible, true);
}

figure *figure_seagulls::create(tile2i tile) {
    random_generate_next();
    figure *f = figure_create(FIGURE_SEAGULLS, tile, DIR_0_TOP_RIGHT);
    f->animctx.frame = random_byte() & 0x1f;
    f->progress_on_tile = random_byte() & 7;
    return f;
}
