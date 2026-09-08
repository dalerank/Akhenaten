#include "figure_noble.h"

#include "figure/action.h"
#include "js/js_game.h"

const e_noble_action_tokens_t ANK_CONFIG_ENUM(e_noble_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_noble);

void figure_noble::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_0_NOBLE_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_1_NOBLE_RETURNING);
        break;

    case ACTION_1_NOBLE_RETURNING:
        do_returnhome(TERRAIN_USAGE_ROADS);
        break;
    }
}

void figure_noble::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

void figure_noble::before_poof() {
}
