#include "figure_constable.h"

#include "city/city.h"
#include "core/calc.h"
#include "figure/enemy_army.h"
#include "building/building_storage_yard.h"
#include "figure/service.h"
#include "figuretype/figure_native.h"
#include "figuretype/figure_tomb_robber.h"
#include "game/game_config.h"
#include "grid/routing/routing.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_constable);

void figure_constable::figure_action() {
    if (action_state() == ACTION_74_CONSTABLE_REQUESTING_WEAPONS && !base.in_attack()) {
        request_weapons_remake();
        return;
    }
    law_walker_action();
}

void figure_constable::on_walk_cycle(bool wrapped) {
    if (wrapped) {
        fight_enemy();
    }
    arrest_tomb_robber_remake();
}

void figure_constable::on_attack_tick() {
    if (base.attack_image_offset == 12) {
        base.play_attack_sound();
    }
}

// Remake police weapons (gameplay_change_police_weapons): the constable walks to a storage yard and leaves a
// weapons request there for the yard to deliver to its station.
void figure_constable::request_weapons_remake() {
    base.terrain_usage = TERRAIN_USAGE_ROADS;
    building* yard_building = has_destination() ? destination() : nullptr;
    building_storage_yard* yard = yard_building ? yard_building->dcast_storage_yard() : nullptr;
    if (yard && direction() != DIR_FIGURE_NONE) {
        base.move_ticks(1);
        if (direction() != DIR_FIGURE_CAN_NOT_REACH) {
            return;
        }
        yard = nullptr;
    }

    if (yard) {
        auto& requests = yard->runtime_data().police_station_weapon_requests;
        const building_id station_id = home()->id;
        if (std::find(requests.begin(), requests.end(), station_id) == requests.end()) {
            const auto empty_it = std::find(requests.begin(), requests.end(), 0);
            if (empty_it != requests.end()) {
                *empty_it = station_id;
            }
        }
    }

    return_home();
}

bool figure_constable::fight_enemy() {
    if (!g_city.figures_has_security_breach() && enemy_army_total_enemy_formations() <= 0) {
        return false;
    }

    if (base.in_attack()) {
        return false;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
    case ACTION_70_LAW_WALKER_CREATED:
    case ACTION_71_LAW_WALKER_ENTERING_EXITING:
    case ACTION_76_LAW_WALKER_CHASE:
        return false;
    }

    const auto& p = current_params();
    auto& d = runtime_data();
    if (++d.wait_ticks_next_target < p.enemy_search_ticks) {
        return false;
    }

    d.wait_ticks_next_target = 0;
    const figure_id enemy_id = closest_enemy(p.enemy_search_distance);
    if (enemy_id <= 0) {
        return false;
    }

    figure* enemy = figure_get(enemy_id);
    advance_action(ACTION_76_LAW_WALKER_CHASE);
    base.destination_tile = enemy->tile;
    base.target_figure_id = enemy_id;
    enemy->targeted_by_figure_id = id();
    route_remove();
    return true;
}

// Remake tomb robber (gameplay_change_tomb_robber_remake) is caught by a constable; OG constables only fight on
// contact.
void figure_constable::arrest_tomb_robber_remake() {
    if (!game_features::gameplay_change_tomb_robber_remake.to_bool() || base.in_attack()) {
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
    case ACTION_70_LAW_WALKER_CREATED:
    case ACTION_71_LAW_WALKER_ENTERING_EXITING:
    case ACTION_76_LAW_WALKER_CHASE:
        return;
    }

    const int max_distance = current_params().tomb_robber_arrest_distance;
    const auto result = base.is_nearby(NEARBY_HOSTILE, max_distance);
    if (result.fid <= 0 || result.distance > max_distance) {
        return;
    }

    figure* criminal = figure_get(result.fid);
    if (criminal->type != FIGURE_TOMB_ROBER || !criminal->is_alive()) {
        return;
    }

    auto* robber = criminal->dcast<figure_tomb_robber>();
    if (robber && robber->arrest()) {
        base.target_figure_id = 0;
    }
}

figure_id figure_constable::closest_enemy(int max_distance) const {
    const auto& p = current_params();
    std::array<figure_id, CONSTABLE_MAX_ENEMY_CANDIDATES> ids;
    std::array<int, CONSTABLE_MAX_ENEMY_CANDIDATES> offsets;
    int count = 0;

    for (int i = 1; i < MAX_FIGURES; i++) {
        figure* f = figure_get(i);
        if (!f->is_alive() || f->targeted_by_figure_id != 0) {
            continue;
        }
        if (count >= CONSTABLE_MAX_ENEMY_CANDIDATES) {
            break;
        }

        int factor = 0;
        if (f->type == FIGURE_INDIGENOUS_NATIVE && f->action_state == ACTION_11_NATIVE_ATTACKING) {
            factor = p.native_distance_factor;
        } else if (f->dcast()->dcast_enemy() && !f->is_boat()) {
            factor = p.enemy_distance_factor;
        } else if (std::find(p.chased_animals.begin(), p.chased_animals.end(), f->type) != p.chased_animals.end()) {
            factor = p.animal_distance_factor;
        } else {
            continue;
        }

        const int distance = calc_maximum_distance(tile(), f->tile) * factor;
        if (distance < max_distance) {
            ids[count] = i;
            offsets[count] = f->tile.grid_offset();
            count++;
        }
    }

    if (count == 0) {
        return 0;
    }

    const int index = map_routing_citizen_find_first_of_any(tile(), offsets.data(), count);
    return index > 0 ? ids[index - 1] : 0;
}

int figure_constable::provide_service() {
    base.min_max_seen = (uint8_t)figure_provide_crime_coverage(tile(), current_params().crime_reduction);
    return 0;
}
