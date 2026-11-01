#include "figure_bubbles.h"

#include "graphics/animkeys.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bubbles);

// OG figure_bubbles_action (0x004941B0): wait_ticks++, die when pre-increment value > 0x15,
// image = wait_ticks + image_bubbles + 1.
void figure_bubbles::figure_action() {
    const int16_t ticks = base.wait_ticks++;
    if (ticks > 0x15) {
        poof();
        return;
    }
}

void figure_bubbles::update_animation() {
    const int img = anim(animkeys().walk).first_img();
    base.main_image_id = img + base.wait_ticks + 1;
    base.animctx.base = 0;
}

figure *figure_bubbles::create(tile2i tile) {
    figure *f = figure_create(FIGURE_BUBBLES, tile, DIR_0_TOP_RIGHT);
    if (!f || !f->id) {
        return nullptr;
    }
    f->wait_ticks = 0;
    f->image_set_animation(animkeys().walk);
    return f;
}
