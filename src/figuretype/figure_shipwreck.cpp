#include "figure_shipwreck.h"

#include "grid/water.h"
#include "core/random.h"
#include "figure/route.h"
#include "graphics/graphics.h"
#include "graphics/image.h"
#include "graphics/elements/ui.h"
#include "window/building/figures.h"
#include "game/game.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_shipwreck);

void figure_shipwreck::figure_action() {
    base.height_adjusted_ticks = 0;
    base.allow_move_type = EMOVE_DEEPWATER;

    if (base.wait_ticks < 1000) {
        base.map_figure_remove();
        water_dest result = map_water_find_shipwreck_tile(base);
        if (result.found) {
            base.tile = result.tile;
            base.cc_coords.x = 15 * tilex() + 7;
            base.cc_coords.y = 15 * tiley() + 7;
        }
        base.map_figure_add();
        base.wait_ticks = 1000;
    }

    base.wait_ticks++;
    if (base.wait_ticks > 2000) {
        poof();
    }
}

void figure_shipwreck::update_animation() {
    base.main_image_id = anim(animkeys().walk).first_img() + base.animctx.frame / 16;
}

bool figure_shipwreck::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ctx.img_generic(anim(animkeys().big_image).first_img(), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);

    return true;
}

figure *figure_shipwreck::create(tile2i tile) {
    random_generate_next();
    figure* f = figure_create(FIGURE_SHIPWRECK, tile, DIR_0_TOP_RIGHT);
    f->animctx.frame = random_byte() & 0x1f;
    f->progress_on_tile = random_byte() & 7;
    f->advance_action(ACTION_15_SHIPWRECK_RETURNING);
    f->set_cross_country_direction(f->cc_coords.x, f->cc_coords.y, 15 * f->destination_tile.x(), 15 * f->destination_tile.y(), 0);
    f->image_set_animation(animkeys().walk);
    return f;
}
