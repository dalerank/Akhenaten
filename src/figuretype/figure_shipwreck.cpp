#include "figure_shipwreck.h"

#include "figuretype/figure_bubbles.h"
#include "grid/water.h"
#include "graphics/animkeys.h"
#include "graphics/elements/ui.h"
#include "game/game.h"
#include "js/js_game.h"
#include "window/building/figures.h"
#include "city/object_info.h"
#include "graphics/elements/lang_text.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_shipwreck);

void figure_shipwreck::on_create() {
    figure_impl::on_create();
    base.allow_move_type = EMOVE_DEEPWATER;
    base.wait_ticks = 0;
    base.progress_on_tile = 0;
}

void figure_shipwreck::figure_action() {
    // OG figure_shipwreck_action (shipwreck.c).
    base.set_flag(e_figure_flag_invisible, false);
    base.height_adjusted_ticks = 0;
    base.allow_move_type = EMOVE_DEEPWATER;

    if (++base.progress_on_tile >= SHIPWRECK_FRAMES) {
        poof();
        return;
    }

    if (base.wait_ticks < SHIPWRECK_WAIT_SETTLED) {
        base.map_figure_remove();
        water_dest result = map_water_find_shipwreck_tile(base);
        if (result.found) {
            base.tile = result.tile;
            base.cc_coords.x = 15 * tilex() + 7;
            base.cc_coords.y = 15 * tiley() + 7;
        }
        base.map_figure_add();
        base.wait_ticks = SHIPWRECK_WAIT_SETTLED;
    }
}

void figure_shipwreck::update_animation() {
    const int img = anim(animkeys().walk).first_img();
    base.main_image_id = img + base.progress_on_tile;
    base.animctx.base = 0;
}

bool figure_shipwreck::window_info_background(object_info &c) {
    painter ctx = game.painter();
    ctx.img_generic(anim(animkeys().big_image).first_img(), c.offset + vec2i{28, 112});
    lang_text_draw(64, type(), c.offset.x + 92, c.offset.y + 139, FONT_NORMAL_BLACK_ON_DARK);
    return true;
}

figure *figure_shipwreck::create(tile2i tile) {
    figure_bubbles::create(tile);
    figure *f = figure_create(FIGURE_SHIPWRECK, tile, DIR_0_TOP_RIGHT);
    if (!f || !f->id) {
        return nullptr;
    }
    f->wait_ticks = 0;
    f->progress_on_tile = 0;
    f->allow_move_type = EMOVE_DEEPWATER;
    f->image_set_animation(animkeys().walk);
    return f;
}
