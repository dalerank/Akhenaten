#include "figuretype/figure_protestor.h"

#include "figure/service.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_protestor);

void figure_protestor::figure_action() {
    //    terrain_usage = TERRAIN_USAGE_ROADS;
    //    figure_image_increase_offset(64);
    //    cart_image_id = 0;
    //    if (action_state == FIGURE_ACTION_149_CORPSE)
    //        poof();

    base.wait_ticks++;
    if (base.wait_ticks > 200) {
        poof();
        base.animctx.frame = 0;
    }
}

void figure_protestor::update_animation() {
    xstring animkey = animkeys().walk;

    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death; // = image_id_from_group(GROUP_FIGURE_THIEF_DEATH) + figure_image_corpse_offset();
    } else {
        animkey = animkeys().walk; // sprite_image_id = image_id_from_group(GROUP_FIGURE_THIEF_WALK) + CRIMINAL_OFFSETS[anim.frame / 4] + 104;
    }

    image_set_animation(animkey);
}