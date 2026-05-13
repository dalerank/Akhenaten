#include "figure_noble.h"

#include "figure/action.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_noble);

void figure_noble::figure_action() {
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_125_ROAMER_ROAMING:
        do_roam(TERRAIN_USAGE_ROADS, ACTION_126_ROAMER_RETURNING);
        break;

    case ACTION_126_ROAMER_RETURNING:
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
