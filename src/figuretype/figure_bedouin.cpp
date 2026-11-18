#include "figure_bedouin.h"

#include "core/profiler.h"
#include "figure/formation.h"
#include "game/game_events.h"
#include "game/sound_effect.h"
#include "js/js_register.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_bedouin)

void figure_bedouin::figure_action() {
    OZZY_PROFILER_FUNCTION();

    const formation* m = formation_get(base.formation_id);
    if (m && m->is_herd) {
        poof();
        return;
    }

    figure_enemy_fast_sword::figure_action();

    if (base.is_alive() && base.in_attack() && base.opponent_id > 0) {
        play_attack_sound();
    }
}

void figure_bedouin::play_attack_sound() {
    events::emit(event_sound_effect{SOUND_EFFECT_POLICE_ATTACK});
}

int figure_bedouin::enemy_walk_ticks() {
    auto& d = runtime_data();
    const auto& cycle = current_params().move_cycle;
    if (cycle.empty()) {
        return 0;
    }
    if (d.move_counter >= cycle.size()) {
        d.move_counter = 0;
    }
    return cycle[d.move_counter++];
}
