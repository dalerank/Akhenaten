#include "distant_battle.h"

#include "city/buildings.h"
#include "city/map.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/military.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "empire/empire_city.h"
#include "empire/empire_object.h"
#include "empire/type.h"
#include "figure/formation_batalion.h"
#include "figuretype/figure_soldier.h"
#include "game/game.h"
#include "empire/empire.h"
#include "city/city.h"
#include "scenario/scenario.h"

distant_battles_t g_distant_battle;

void distant_battles_t::clear() {
    battle.clear();
    dispatched_army.clear();
}

void distant_battles_t::battle_state_t::clear() {
    memset(this, 0, sizeof(battle_state_t));
}

const army_path &distant_battles_t::get_path() {
    if (dispatched_army.path.empty()) {
        const empire_object *capital = g_empire.ourcity_object();
        if (!capital || !battle.city) {
            return dispatched_army.path;
        }

        const empire_city* battle_city = g_empire.city(battle.city);
        if (!battle_city) {
            return dispatched_army.path;
        }

        const empire_object* battle_city_obj = battle_city->get_empire_object();
        if (!battle_city_obj) {
            return dispatched_army.path;
        }

        vec2i start = capital->pos;
        vec2i end = battle_city_obj->pos;

        vec2i direction = end - start;
        float distance = start.dist(end);
        
        if (distance < 1.0f) {
            dispatched_army.path.push_back(start);
            dispatched_army.path.push_back(end);
            return dispatched_army.path;
        }

        // Calculate number of path points based on distance
        // More points for longer distances, but cap at reasonable number
        int num_points = (int)(distance / 50.0f) + 3; // At least 3 points, more for longer distances
        num_points = std::min<int>(num_points, army_path::capacity());
        
        float dir_x = (float)direction.x / distance;
        float dir_y = (float)direction.y / distance;
        
        // Perpendicular to (dir_x, dir_y) is (-dir_y, dir_x)
        float perp_x = -dir_y;
        float perp_y = dir_x;
        
        // Deviation amplitude - percentage of distance (15% deviation)
        float deviation_amplitude = distance * 0.15f;
        dispatched_army.path.push_back(start);
        
        for (int i = 1; i < num_points - 1; ++i) {
            float t = (float)i / (float)(num_points - 1); // 0.0 to 1.0
            
            vec2i base_point = start + direction * t;
            
            float deviation1 = ::sinf(t * 3.14159f * 2.0f) * deviation_amplitude;
            float deviation2 = ::sinf(t * 3.14159f * 4.0f) * deviation_amplitude * 0.5f;
            float total_deviation = deviation1 + deviation2;
            
            vec2i deviated_point = base_point + vec2i(
                (int)(perp_x * total_deviation),
                (int)(perp_y * total_deviation)
            );
            
            dispatched_army.path.push_back(deviated_point);
        }
        
        dispatched_army.path.push_back(end);
    }

    return dispatched_army.path;
}

vec2i dispatched_army_t::get_current_position() const {
    if (path.empty()) {
        return vec2i{0, 0};
    }
    
    if (state == state_returning) {
        int reverse_index = path.size() - 1 - position_index;
        reverse_index = std::max(0, std::min(reverse_index, (int)path.size() - 1));
        return path[reverse_index];
    } else {
        uint8_t safe_index = std::min(position_index, (uint8_t)(path.size() - 1));
        return path[safe_index];
    }
}

void dispatched_army_t::clear() {
    state = state_inactive;
    await_soldiers = 0;
    position_index = 0;
    movement_delay = 0;
    movement_delay_max = 0;
    path.clear();
}

void distant_battles_t::dispatch_to_distant_battle(int egyptian_strength, uint8_t soldiers_num) {
    battle.egyptian_months_to_travel_forth = g_scenario.empire.distant_battle_kingdome_travel_months;
    battle.egyptian_strength = egyptian_strength;

    dispatched_army.state = dispatched_army_t::state_awaiting_soldiers;
    dispatched_army.await_soldiers = soldiers_num;
    dispatched_army.position_index = 0;
    dispatched_army.movement_delay = 0;
    dispatched_army.movement_delay_max = 2;
}

void distant_battles_t::update_day() {
    if (has_distant_battle()) {
        switch (dispatched_army.state) {
        case dispatched_army_t::state_awaiting_soldiers:
            // Wait for all soldiers to join
            // When await_soldiers reaches 0, transition to traveling
            if (dispatched_army.await_soldiers == 0) {
                const auto &path = get_path();
                verify_no_crash(!path.empty());

                dispatched_army.state = dispatched_army_t::state_traveling;
                dispatched_army.position_index = 0;
                dispatched_army.movement_delay = 0;
                dispatched_army.movement_delay_max = 2;
            }
            break;

        case dispatched_army_t::state_traveling: {
                if (dispatched_army.movement_delay > 0) {
                    dispatched_army.movement_delay--;
                    break;
                }

                if (dispatched_army.position_index < dispatched_army.path.size() - 1) {
                    dispatched_army.position_index++;
                    dispatched_army.movement_delay = dispatched_army.movement_delay_max;
                } else {
                    dispatched_army.state = dispatched_army_t::state_at_battle;
                }
            }
            break;

        case dispatched_army_t::state_at_battle:
            process_distant_battle_impl();
            dispatched_army.state = dispatched_army_t::state_returning;
            break;

        case dispatched_army_t::state_returning: {
                if (dispatched_army.movement_delay > 0) {
                    dispatched_army.movement_delay--;
                    break;
                }

                int reverse_index = dispatched_army.path.size() - 1 - dispatched_army.position_index;
                if (reverse_index > 0) {
                    dispatched_army.position_index++;
                    dispatched_army.movement_delay = dispatched_army.movement_delay_max;
                } else {
                    dispatched_army.state = dispatched_army_t::state_inactive;
                    dispatched_army.position_index = 0;
                    dispatched_army.return_from_distant_battle();
                }
            }
            break;
        }
        dispatched_army.pos = dispatched_army.get_current_position();
    }
}

void dispatched_army_t::return_soldiers(formation *m) {
    m->in_distant_battle = 0;
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure *f = figure_get(m->figures[fig]);
            if (!f->is_dead()) {
                f->action_state = ACTION_88_SOLDIER_RETURNING_FROM_DISTANT_BATTLE;
                f->formation_at_rest = 1;
            }
        }
    }
}

void dispatched_army_t::return_from_distant_battle() {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (m->in_use && m->own_batalion && m->in_distant_battle) {
            return_soldiers(m);
        }
    }
}

void distant_battles_t::update_month() {
    if (!has_distant_battle()) {
        for (int i = 0; i < MAX_INVASIONS; i++) {
            const bool should_start_battle = g_scenario.invasions[i].type == INVASION_TYPE_DISTANT_BATTLE
                && game.simtime.year == g_scenario.invasions[i].year + g_scenario.start_year
                && game.simtime.month == g_scenario.invasions[i].month
                && g_scenario.empire.distant_battle_enemy_travel_months > 4
                && g_scenario.empire.distant_battle_kingdome_travel_months > 4;

            if (should_start_battle) {
                events::emit(event_message{ true, "message_kingdome_requests_army", 0, 0 });
                g_distant_battle.init_distant_battle(g_scenario.invasions[i].amount);
                return;
            }
        }
    }

    process_distant_battle_impl();
}

void distant_battles_t::determine_distant_battle_city() {
    battle.city = g_empire.get_city_vulnerable();
}

bool distant_battles_t::city_is_egyptian() {
    return battle.city_foreign_months_left <= 0;
}

int distant_battles_t::kingdome_army_is_traveling() {
    return battle.egyptian_months_to_travel_forth > 0 || battle.egyptian_months_to_travel_back > 0;
}

int distant_battles_t::enemy_months_traveled() {
    return battle.egyptian_months_traveled;
}

void distant_battles_t::init_distant_battle(int enemy_strength) {
    battle.enemy_months_traveled = 1;
    battle.egyptian_months_traveled = 1;
    battle.months_until_battle = 24;
    battle.enemy_strength = enemy_strength;
    battle.total_count++;
    battle.egyptian_months_to_travel_back = 0;
    battle.egyptian_months_to_travel_forth = 0;
}

int distant_battles_t::has_distant_battle() {
    return battle.months_until_battle > 0
        || battle.egyptian_months_to_travel_back > 0
        || battle.egyptian_months_to_travel_forth > 0
        || battle.city_foreign_months_left > 0;
}

void distant_battles_t::process_distant_battle_impl() {
    if (battle.months_until_battle > 0) {
        --battle.months_until_battle;
        if (battle.months_until_battle > 0) {
            update_time_traveled();
        } else {
            fight_distant_battle();
        }
    } else {
        update_aftermath();
    }
}

void distant_battles_t::set_city_vulnerable() {
    if (battle.city) {
        g_empire.city(battle.city)->set_vulnerable();
    }
}

int distant_battles_t::enemy_strength() {
    return battle.enemy_strength;
}

void distant_battles_t::update_aftermath() {
    if (battle.egyptian_months_to_travel_back > 0) {
        battle.egyptian_months_to_travel_back--;
        battle.egyptian_months_traveled = battle.egyptian_months_to_travel_back;
        if (battle.egyptian_months_to_travel_back <= 0) {
            if (battle.city_foreign_months_left) {
                // soldiers return - not in time
                events::emit(event_message{ true, "message_troops_return_failed", 0, g_city.map.exit_point.grid_offset() });
            } else {
                // victorious
                events::emit(event_message{ true, "message_troops_return_victorious", 0, g_city.map.exit_point.grid_offset() });
            }
            battle.egyptian_months_traveled = 0;
            formation_batalions_return_from_distant_battle();
        }
    } else if (battle.city_foreign_months_left > 0) {
        battle.city_foreign_months_left--;
        if (battle.city_foreign_months_left <= 0) {
            events::emit(event_message{ true, "message_city_retaken", 0, 0 });
            set_city_vulnerable();
        }
    }
}

void distant_battles_t::set_city_foreign() {
    if (battle.city) {
        g_empire.city(battle.city)->set_foreign();
    }

    battle.city_foreign_months_left = 24;
}

void dispatched_army_t::formation_batalions_kill_soldiers(formation *m, int kill_percentage) {
    formation_change_morale(m, -75);
    int soldiers_total = 0;
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure *f = figure_get(m->figures[fig]);
            if (!f->is_dead())
                soldiers_total++;
        }
    }

    int soldiers_to_kill = calc_adjust_with_percentage(soldiers_total, kill_percentage);
    if (soldiers_to_kill >= soldiers_total) {
        m->is_at_fort = 1;
        m->in_distant_battle = 0;
    }
    for (int fig = 0; fig < m->num_figures; fig++) {
        if (m->figures[fig] > 0) {
            figure *f = figure_get(m->figures[fig]);
            if (!f->is_dead()) {
                if (soldiers_to_kill) {
                    soldiers_to_kill--;
                    f->poof();
                }
            }
        }
    }
}

void dispatched_army_t::formation_batalions_kill_in_distant_battle(int kill_percentage) {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);

        if (m->in_use && m->own_batalion && m->in_distant_battle) {
            formation_batalions_kill_soldiers(m, kill_percentage);
        }
    }
}

bool distant_battles_t::player_has_won() {
    bool won;
    int pct_loss;
    if (battle.egyptian_strength < battle.enemy_strength) {
        won = 0;
        pct_loss = 100;
    } else {
        won = 1;
        int pct_advantage = calc_percentage<int>(battle.egyptian_strength - battle.enemy_strength, battle.egyptian_strength);

        if (pct_advantage < 10)
            pct_loss = 70;
        else if (pct_advantage < 25)
            pct_loss = 50;
        else if (pct_advantage < 50)
            pct_loss = 25;
        else if (pct_advantage < 75)
            pct_loss = 15;
        else if (pct_advantage < 100)
            pct_loss = 10;
        else if (pct_advantage < 150)
            pct_loss = 5;
        else {
            pct_loss = 0;
        }
    }

    dispatched_army.formation_batalions_kill_in_distant_battle(pct_loss);
    return won;
}

void distant_battles_t::fight_distant_battle() {
    if (battle.egyptian_months_to_travel_forth <= 0) {
        events::emit(event_message{ true, "message_distant_battle_lost_no_troops", 0, 0 });
        g_city.kingdome.change(-50);
        set_city_foreign();
    } else if (battle.egyptian_months_to_travel_forth > 2) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_late", 0, 0 });
        g_city.kingdome.change(-25);
        set_city_foreign();
        battle.egyptian_months_to_travel_back = battle.egyptian_months_traveled;
    } else if (!player_has_won()) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_weak", 0, 0 });
        g_city.kingdome.change(-10);
        set_city_foreign();
        battle.egyptian_months_traveled = 0;
        // no return: all soldiers killed
    } else {
        events::emit(event_message{ true, "message_distant_battle_won", 0, 0 });
        g_city.kingdome.change(25);
        city_buildings_earn_triumphal_arch();

        battle.won_count++;
        battle.city_foreign_months_left = 0;
        battle.egyptian_months_to_travel_back = battle.egyptian_months_traveled;
    }
    battle.months_until_battle = 0;
    battle.enemy_months_traveled = 0;
    battle.egyptian_months_to_travel_forth = 0;
}

void distant_battles_t::update_time_traveled() {
    int egyptian_travel_months = g_scenario.empire.distant_battle_kingdome_travel_months;
    int enemy_travel_months = g_scenario.empire.distant_battle_enemy_travel_months;

    if (battle.months_until_battle < enemy_travel_months) {
        battle.enemy_months_traveled = enemy_travel_months - battle.months_until_battle + 1;
    } else {
        battle.enemy_months_traveled = 1;
    }

    if (battle.egyptian_months_to_travel_forth >= 1) {
        if (egyptian_travel_months - battle.egyptian_months_traveled
    > enemy_travel_months - battle.enemy_months_traveled) {
            battle.egyptian_months_to_travel_forth -= 2;
        } else {
            battle.egyptian_months_to_travel_forth--;
        }

        if (battle.egyptian_months_to_travel_forth <= 1) {
            battle.egyptian_months_to_travel_forth = 1;
        }

        battle.egyptian_months_traveled = egyptian_travel_months - battle.egyptian_months_to_travel_forth + 1;
        if (battle.egyptian_months_traveled < 1) {
            battle.egyptian_months_traveled = 1;
        }

        if (battle.egyptian_months_traveled > egyptian_travel_months) {
            battle.egyptian_months_traveled = egyptian_travel_months;
        }
    }
}

