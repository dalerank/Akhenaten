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
#include "scenario/scenario_event_manager.h"
#include "scenario/request.h"
#include "city/legion_requests.h"

distant_battles_t g_distant_battle;

void distant_battles_t::clear() {
    battle.clear();
    dispatched_army.clear();
    source_request_event_id = -1;
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
    
    if (state >= state_returning) {
        int reverse_index = path.size() - 1 - position_index;
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
    if (dispatched_army.state != dispatched_army_t::state_inactive) {
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
            if (battle.months_until_battle > 0) {
                battle.egyptian_months_to_travel_forth = 1;
                battle.months_until_battle = 1;
            }
            process_distant_battle_impl();
            dispatched_army.position_index = 0;
            if (dispatched_army.state == dispatched_army_t::state_traveling) {
               dispatched_army.state = dispatched_army_t::state_returning;
            }
            break;

        case dispatched_army_t::state_returning: 
        case dispatched_army_t::state_returning_win: 
        case dispatched_army_t::state_returning_lose: 
        case dispatched_army_t::state_returning_destroyed: {
                if (dispatched_army.movement_delay > 0) {
                    dispatched_army.movement_delay--;
                    break;
                }

                if (dispatched_army.position_index < dispatched_army.path.size()) {
                    dispatched_army.position_index++;
                    dispatched_army.movement_delay = dispatched_army.movement_delay_max;
                } else {
                    dispatched_army.position_index = 0;

                    if (dispatched_army.state == dispatched_army_t::state_returning_win) {
                        events::emit(event_message{ true, "message_troops_return_victorious", 0, g_city.map.exit_point.grid_offset(), SOURCE_LOCATION });
                    } else if (dispatched_army.state == dispatched_army_t::state_returning_lose || dispatched_army.state == dispatched_army_t::state_returning_destroyed) {
                        events::emit(event_message{ true, "message_troops_return_failed", 0, g_city.map.exit_point.grid_offset(), SOURCE_LOCATION });
                    }

                    dispatched_army.state = dispatched_army_t::state_inactive;
                    dispatched_army.return_from_distant_battle();
                    dispatched_army.path.clear();
                    battle.egyptian_months_to_travel_back = 0;
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
                f->action_state = ACTION_8_SOLDIER_RETURNING_FROM_DISTANT_BATTLE;
                f->wait_ticks = (rand() % 64 + 4);
                f->formation_at_rest = 1;
            }
        }
    }
}

void dispatched_army_t::return_from_distant_battle() {
    for (int i = 1; i < MAX_FORMATIONS; i++) {
        formation *m = formation_get(i);
        if (!m->in_use || !m->own_batalion || !m->in_distant_battle) {
            continue;
        }
        // Sea request return owns landing via transport ACTION_223 — do not yank soldiers off the ship.
        if (formation_legion_is_on_ship(i)) {
            continue;
        }
        return_soldiers(m);
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
                events::emit(event_message{ true, "message_kingdome_requests_army", 0, 0, SOURCE_LOCATION });
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
    if (battle.city_foreign_months_left > 0) {
        battle.city_foreign_months_left--;
        if (battle.city_foreign_months_left <= 0) {
            events::emit(event_message{ true, "message_city_retaken", 0, 0, SOURCE_LOCATION });
            set_city_vulnerable();
        }
        return;
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

static bool is_deferred_troop_request(const event_ph_t *ev) {
    return ev && ev->type == EVENT_TYPE_REQUEST
        && (e_resource)ev->item.value == RESOURCE_TROOPS
        && ev->on_defeat_action >= 0
        && !ev->is_active
        && ev->event_state <= e_event_state_overdue;
}

// source_request_event_id is not in the original city_data blob; after load (or if the
// runtime link was cleared) recover the inactive troop ask awaiting battle resolution.
static int16_t resolve_source_request_event_id(int16_t linked) {
    if (linked >= 0 && is_deferred_troop_request(g_scenario.events.at(linked))) {
        return linked;
    }

    int16_t found = -1;
    for (int i = 0; i < g_scenario.events.events_count(); i++) {
        const event_ph_t *ev = g_scenario.events.at(i);
        if (!is_deferred_troop_request(ev)) {
            continue;
        }
        if (found >= 0) {
            return -1; // ambiguous — do not guess
        }
        found = (int16_t)ev->event_id;
    }
    return found;
}

static int distant_battle_pct_loss(bool &won) {
    if (g_distant_battle.battle.egyptian_strength < g_distant_battle.battle.enemy_strength) {
        won = false;
        return 100;
    }
    won = true;
    const int pct_advantage = calc_percentage<int>(
        g_distant_battle.battle.egyptian_strength - g_distant_battle.battle.enemy_strength,
        g_distant_battle.battle.egyptian_strength);
    if (pct_advantage < 10)
        return 70;
    if (pct_advantage < 25)
        return 50;
    if (pct_advantage < 50)
        return 25;
    if (pct_advantage < 75)
        return 15;
    if (pct_advantage < 100)
        return 10;
    if (pct_advantage < 150)
        return 5;
    return 0;
}

bool distant_battles_t::player_has_won() {
    bool won = false;
    const int pct_loss = distant_battle_pct_loss(won);
    dispatched_army.formation_batalions_kill_in_distant_battle(pct_loss);
    return won;
}

// ONLY_VIA masters clone to ACTIVATED_*; drain so request ok/defeat leaves fire same month.
static void drain_activated_events(int from_index) {
    while (from_index < g_scenario.events.events_count()) {
        const int end = g_scenario.events.events_count();
        for (int i = from_index; i < end; ++i) {
            g_scenario.events.process_event(i, false, -1);
            g_scenario.events.process_active_request(i);
        }
        from_index = end;
    }
}

void distant_battles_t::fight_distant_battle() {
    const int16_t req_id = resolve_source_request_event_id(source_request_event_id);
    source_request_event_id = -1;
    const bool request_linked = req_id >= 0;

    bool won = false;
    if (battle.egyptian_months_to_travel_forth <= 0) {
        events::emit(event_message{ true, "message_distant_battle_lost_no_troops", 0, 0, SOURCE_LOCATION });
        dispatched_army.state = dispatched_army_t::state_returning;
        if (!request_linked) {
            g_city.kingdome.change(-50);
        }
        set_city_foreign();
        if (request_linked) {
            formation_legions_return_from_request(req_id);
        }
    } else if (battle.egyptian_months_to_travel_forth > 2) {
        events::emit(event_message{ true, "message_distant_battle_lost_too_late", 0, 0, SOURCE_LOCATION });
        if (!request_linked) {
            g_city.kingdome.change(-25);
        }
        set_city_foreign();
        battle.egyptian_months_to_travel_back = battle.egyptian_months_traveled;
        dispatched_army.state = dispatched_army_t::state_returning;
        if (request_linked) {
            formation_legions_return_from_request(req_id);
        }
    } else {
        int pct_loss = 0;
        if (request_linked) {
            pct_loss = distant_battle_pct_loss(won);
            formation_legions_request_losses(pct_loss, req_id);
            // Survivors sail/march home via transport 223 / land return — even on total wipe
            // (then request_losses already sank ships / cleared flags).
            formation_legions_return_from_request(req_id);
        } else {
            won = player_has_won();
        }

        if (!won) {
            events::emit(event_message{ true, "message_distant_battle_lost_too_weak", 0, 0, SOURCE_LOCATION });
            if (!request_linked) {
                g_city.kingdome.change(-10);
            }
            set_city_foreign();
            battle.egyptian_months_traveled = 0;
            dispatched_army.state = dispatched_army_t::state_returning_destroyed;
        } else {
            dispatched_army.state = dispatched_army_t::state_returning_win;

            if (!request_linked) {
                const auto city = g_empire.city(battle.city);
                if (city && city->get_empire_object()) {
                    uint16_t rtag = rand() % 0xffff;
                    g_scenario.events.win_distant_battle(rtag, city->name_str.c_str(), city->get_empire_object()->pos);
                    g_scenario.events.execute_event(rtag);
                }
                g_city.kingdome.change(25);
                city_buildings_earn_triumphal_obelisk();
            }

            battle.won_count++;
            battle.city_foreign_months_left = 0;
            battle.egyptian_months_to_travel_back = 0;
        }
    }

    if (request_linked) {
        event_ph_t *ev = g_scenario.events.at(req_id);
        if (ev) {
            ev->is_active = false;
            const int before = g_scenario.events.events_count();
            if (won) {
                ev->event_state = e_event_state_received;
                if (ev->on_completed_action >= 0) {
                    g_scenario.events.process_event(ev->on_completed_action, true, EVENT_ACTION_COMPLETED, ev->event_id);
                }
            } else {
                ev->event_state = e_event_state_failed;
                if (ev->on_defeat_action >= 0) {
                    g_scenario.events.process_event(ev->on_defeat_action, true, EVENT_ACTION_DEFEAT, ev->event_id);
                }
            }
            drain_activated_events(before);
            // Troop asks defer emit until battle resolves (see scenario_request_dispatch).
            scenario_request_emit_cleared(*ev, won);
        }
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

