#include "figuretype/figure_pharaoh.h"

#include "game/simulation_time.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_pharaoh);

namespace {

constexpr int k_pharaoh_roam_days = 8;

} // namespace

void figure_pharaoh::on_create() {
    base.roam_wander_freely = true;
    base.max_roam_length = 320;
    // figure_create leaves action_state=0; start cinematic roam without a home.
    advance_action(ACTION_120_PHARAOH_CREATED);
}

void figure_pharaoh::figure_action() {
    if (!base.is_alive()) {
        return;
    }

    switch (action_state()) {
    case ACTION_120_PHARAOH_CREATED:
        base.wait_ticks = 0;
        advance_action(ACTION_121_PHARAOH_ROAMING);
        break;

    case ACTION_121_PHARAOH_ROAMING:
        // Free roam without home (cinematic stub) — no ACTION_126 returnhome.
        base.roam_ticks(1);
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * k_pharaoh_roam_days) {
            poof();
        }
        break;
    }
}

void figure_pharaoh::update_animation() {
    // Walk-only art; ignore corpse death key (missing group).
    image_set_animation(animkeys().walk);
}
