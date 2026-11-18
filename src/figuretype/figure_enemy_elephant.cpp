#include "figure_enemy_elephant.h"

#include "city/city_figures.h"
#include "figure/formation.h"
#include "figuretype/figure_soldier.h"
#include "grid/figure.h"
#include "grid/grid.h"
#include "js/js_register.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_elephant)

void figure_enemy_elephant::figure_action() {
    figure_enemy_fast_sword::figure_action();
    // Parent may have entered dying/dead this tick — no splash after that.
    if (base.is_alive()) {
        trample_adjacent(false);
    }
}

void figure_enemy_elephant::trample_adjacent(bool force) {
    auto &d = runtime_data();
    if (!force) {
        if (d.trample_cooldown > 0) {
            d.trample_cooldown--;
            return;
        }
    }

    const int splash = std::max(1, base.attack_value() / 2);
    bool hit_any = false;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            tile2i t = tile().shifted(dx, dy);
            if (!map_grid_is_valid_offset(t)) {
                continue;
            }

            int fid = map_figure_id_get(t);
            while (fid > 0) {
                figure *f = figure_get(fid);
                fid = f->next_figure;
                if (!f->is_valid() || f->is_dead() || f->id == id()) {
                    continue;
                }
                // Locked C3 opponent already takes hit_opponent blows — skip splash.
                if (f->id == base.opponent_id) {
                    continue;
                }
                if (!smart_cast<figure_soldier>(f)) {
                    continue;
                }

                f->apply_damage(splash, id());
                if (f->damage > f->max_damage()) {
                    f->kill();
                    f->wait_ticks = 0;
                    f->play_die_sound();
                    if (f->formation_id > 0) {
                        formation_update_morale_after_death(formation_get(f->formation_id));
                    }
                }
                hit_any = true;
            }
        }
    }

    if (hit_any || force) {
        const int delay = std::max(1, (int)interval_attack_delay());
        d.trample_cooldown = (uint8_t)std::min(delay, 255);
    }
}
