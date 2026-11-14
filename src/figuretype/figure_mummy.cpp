#include "figuretype/figure_mummy.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "core/log.h"
#include "core/random.h"
#include "figure/figure.h"
#include "grid/road_access.h"
#include "js/js_game.h"

const e_mummy_action_tokens_t ANK_CONFIG_ENUM(e_mummy_action_tokens)

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_mummy);

namespace {

    int random_15bit() {
        random_generate_next();
        return (uint16_t)random_short() & 0x7fff;
    }

    int count_mummies() {
        int n = 0;
        for (int i = 1; i < MAX_FIGURES; i++) {
            figure* f = figure_get(i);
            if (f->state != FIGURE_STATE_NONE && f->type == FIGURE_MUMMY) {
                n++;
            }
        }
        return n;
    }

    void start_roaming(figure& f, building& source) {
        f.set_home(source.id);
        f.advance_action(ACTION_1_MUMMY_ROAMING);
        f.init_roaming_from_building(source.figure_roam_direction);
        source.figure_roam_direction += 2;
        if (source.figure_roam_direction > 6) {
            source.figure_roam_direction = 0;
        }
        f.roam_length = 0;
    }

} // namespace

void figure_mummy::on_create() {
    // Soldiers target is_enemy() || is_criminal(); params().is_enemy sets enemy flag at create.
    base.flags |= e_figure_flag_criminal;
    advance_action(ACTION_0_MUMMY_CREATED);
}

bool figure_mummy::is_source_building(building& b) {
    if (!b.is_valid()) {
        return false;
    }
    const e_building_type type = b.type;
    const bool source = (type > BUILDING_MUD_TOWER && type < BUILDING_TEMPLE_COMPLEX_OSIRIS)
                        || type == BUILDING_MORTUARY || type == BUILDING_PYRAMID || type == BUILDING_MAUSOLEUM
                        || type == BUILDING_SMALL_ROYAL_TOMB || type == BUILDING_MEDIUM_ROYAL_TOMB
                        || type == BUILDING_LARGE_ROYAL_TOMB || type == BUILDING_GRAND_ROYAL_TOMB;
    return source && map_closest_road_within_radius(b.road_access, 1, current_params().road_radius).valid();
}

figure* figure_mummy::start_plague(int amount) {
    g_city.plagues.mummies_max = amount;
    int count = 0;
    for (auto& b : city_buildings()) {
        if (is_source_building(b)) {
            count++;
        }
    }
    if (count <= 0) {
        return nullptr;
    }

    const int wanted = random_15bit() % count + 1;
    int seen = 0;
    building* source = nullptr;
    for (auto& b : city_buildings()) {
        if (is_source_building(b) && ++seen == wanted) {
            source = &b;
            break;
        }
    }
    if (!source) {
        return nullptr;
    }

    const tile2i road = map_closest_road_within_radius(source->road_access, 1, current_params().road_radius);
    figure* f = figure_create(FIGURE_MUMMY, road, DIR_4_BOTTOM_LEFT);
    if (!f || !f->is_alive()) {
        return nullptr;
    }
    f->wait_ticks = 0;
    start_roaming(*f, *source);
    logs::info("[disaster] mummies from building %d, max=%d", source->id, amount);
    return f;
}

void figure_mummy::figure_action() {
    if (!base.is_alive()) {
        return;
    }
    const auto& p = current_params();

    if (base.opponent_id > 0) {
        figure* victim = figure_get(base.opponent_id);
        if (victim->is_dead() && count_mummies() < g_city.plagues.mummies_max) {
            figure* risen = figure_create(FIGURE_MUMMY, victim->tile, DIR_4_BOTTOM_LEFT);
            if (risen && risen->is_alive()) {
                risen->wait_ticks = (int16_t)(random_15bit() % p.roam_spread + p.roam_min);
                building* source = home();
                if (source && source->is_valid()) {
                    start_roaming(*risen, *source);
                } else {
                    risen->advance_action(ACTION_1_MUMMY_ROAMING);
                    risen->roam_wander_freely = true;
                }
            }
        }
        base.set_flag(e_figure_flag_inattack);
        base.figure_combat_handle_attack();
        return;
    }

    switch (action_state()) {
    case ACTION_0_MUMMY_CREATED:
        advance_action(ACTION_1_MUMMY_ROAMING);
        base.roam_wander_freely = true;
        break;

    case ACTION_1_MUMMY_ROAMING:
        if (++base.roam_length >= base.max_roam_length
            && !map_closest_road_within_radius(tile(), 1, p.road_radius).valid()) {
            poof();
            break;
        }
        if ((runtime_data().step++ & 1) == 0) {
            base.roam_ticks(1);
        }
        break;
    }
}

void figure_mummy::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE) || !base.is_alive()) {
        animkey = animkeys().death;
    } else if (base.in_attack()) {
        animkey = animkeys().attack;
    }
    image_set_animation(animkey);
}

void figure_mummy::acquire_attack() {
    // Default acquire_attack() is empty — without the flag, tile-overlap combat
    // re-enters every step and never locks the mummy into handle_attack.
    base.set_flag(e_figure_flag_inattack);
}
