#include "figuretype/figure_robber.h"

#include "building/building.h"
#include "building/building_mansion.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "core/random.h"
#include "figuretype/figure_tomb_robber.h"
#include "game/game.h"
#include "game/game_config.h"
#include "game/game_events.h"
#include "grid/road_access.h"
#include "js/js_game.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_robber);

namespace {

// OG difficulty_percentage for mansion/palace haul (Very Easy … Very Hard).
constexpr int k_steal_pct_by_difficulty[5] = {3, 6, 9, 12, 15};

bool building_is_mansion_type(e_building_type type) {
    return type >= BUILDING_PERSONAL_MANSION && type <= BUILDING_DYNASTY_MANSION;
}

// OG is_palace_type: palaces, tax collectors, courthouse.
bool building_is_money_building_type(e_building_type type) {
    switch (type) {
    case BUILDING_VILLAGE_PALACE:
    case BUILDING_TOWN_PALACE:
    case BUILDING_TAX_COLLECTOR:
    case BUILDING_TAX_COLLECTOR_UPGRADED:
    case BUILDING_COURTHOUSE:
    case BUILDING_VILLAGE_PALACE_UP:
    case BUILDING_TOWN_PALACE_UP:
    case BUILDING_CITY_PALACE:
        return true;
    default:
        return false;
    }
}

bool building_is_palace_or_mansion(building &b) {
    return building_is_mansion_type(b.type) || building_is_money_building_type(b.type);
}

int steal_percentage() {
    const int diff = std::clamp<int>(game_difficulty(), 0, 4);
    return k_steal_pct_by_difficulty[diff];
}

void show_robbery_warning(pcstr key) {
    events::emit(event_city_warning{key});
}

void show_robbery_message(pcstr key, int amount, int tile_offset) {
    bool show_popup = false;
    if (g_city.sentiment.last_mugger_message <= 0) {
        g_city.sentiment.last_mugger_message = 90;
        show_popup = true;
    }
    events::emit(event_message{show_popup, key, amount, tile_offset, SOURCE_LOCATION});
}

// OG criminal_find_rich_building: nearest mansion/palace/tax/court with money.
int criminal_find_rich_building(figure &f) {
    const bool has_savings = g_city.kingdome.personal_savings > 0;
    const bool has_treasury = g_city.finance.treasury > 0;
    if (!has_savings && !has_treasury) {
        return 0;
    }

    int best_id = 0;
    int best_dist = 10000;
    buildings_valid_do([&](building &b) {
        if (!building_is_palace_or_mansion(b)) {
            return;
        }
        if (building_is_mansion_type(b.type) && !has_savings) {
            return;
        }
        if (building_is_money_building_type(b.type) && !has_treasury) {
            return;
        }
        if (b.tax_income_or_storage <= 0 && !building_is_mansion_type(b.type)) {
            return;
        }
        if (building_is_mansion_type(b.type)) {
            auto *m = b.dcast_mansion();
            if (m && m->runtime_data().personal_savings_storage <= 0 && g_city.kingdome.personal_savings <= 0) {
                return;
            }
        }

        tile2i road = b.road_access.valid() ? b.road_access : b.tile;
        const int dist = calc_maximum_distance(f.tile, road);
        if (dist < best_dist) {
            best_dist = dist;
            best_id = b.id;
        }
    });
    return best_id;
}

void steal_from_destination(figure &f) {
    building *b = f.destination();
    if (!b || !b->is_valid()) {
        return;
    }

    const int pct = steal_percentage();
    if (building_is_mansion_type(b->type)) {
        const int amount = calc_adjust_with_percentage<int>(g_city.kingdome.personal_savings, pct);
        if (amount <= 0) {
            return;
        }
        if (g_city.kingdome.personal_savings >= (uint16_t)amount) {
            g_city.kingdome.personal_savings -= (uint16_t)amount;
        } else {
            g_city.kingdome.personal_savings = 0;
        }
        if (auto *m = b->dcast_mansion()) {
            auto &d = m->runtime_data();
            if (d.personal_savings_storage >= amount) {
                d.personal_savings_storage -= amount;
            } else {
                d.personal_savings_storage = 0;
            }
        }
        g_city.finance.process_stolen(amount);
        show_robbery_warning("#thief_stole_savings");
        show_robbery_message("thief_stole_savings", amount, f.tile.grid_offset());
        return;
    }

    if (!building_is_money_building_type(b->type)) {
        return;
    }

    const int amount = calc_adjust_with_percentage<int>(b->tax_income_or_storage, pct);
    if (amount <= 0) {
        return;
    }
    if (b->tax_income_or_storage >= amount) {
        b->tax_income_or_storage -= (int16_t)amount;
    } else {
        b->tax_income_or_storage = 0;
    }
    g_city.finance.process_stolen(amount);

    pcstr warn = "#palace_robbed";
    switch (b->type) {
    case BUILDING_VILLAGE_PALACE:
    case BUILDING_TOWN_PALACE:
    case BUILDING_TAX_COLLECTOR:
    case BUILDING_TAX_COLLECTOR_UPGRADED:
        warn = "#tax_collector_robbed";
        break;
    case BUILDING_COURTHOUSE:
        warn = "#courthouse_robbed";
        break;
    default:
        warn = "#palace_robbed";
        break;
    }
    show_robbery_warning(warn);
    show_robbery_message("message_tutorial_crime", amount, f.tile.grid_offset());
}

void remake_instant_steal_on_create(figure &f) {
    const int taxes_this_year = g_city.finance.this_year.income.taxes;
    if (taxes_this_year > 20) {
        int money_stolen = taxes_this_year / 4;
        if (money_stolen > 400) {
            money_stolen = 400 - random_byte() / 2;
        }
        show_robbery_message("message_tutorial_crime", money_stolen, f.tile.grid_offset());
        g_city.finance.process_stolen(money_stolen);
        return;
    }

    const int treasury = g_city.finance.treasury;
    if (treasury > 0) {
        int money_stolen = (random_byte() / 2) % 100;
        if (money_stolen > 0) {
            show_robbery_message("message_tutorial_crime", money_stolen, f.tile.grid_offset());
            g_city.finance.process_stolen(money_stolen);
        }
    }
}

} // namespace

void city_show_message_criminal(xstring message_id, int money_stolen, int tile_offset) {
    show_robbery_message(message_id.c_str(), money_stolen, tile_offset);
}

void figure_robber::figure_action() {
    if (game_features::gameplay_change_robber_remake.to_bool()) {
        switch (action_state()) {
        case ACTION_120_ROBBER_CREATED: {
            base.wait_ticks = 0;
            int senate_id = g_city.buildings.get_palace_id();
            building *b_dst = building_get(senate_id);
            tile2i road_tile = map_closest_road_within_radius(b_dst->tile, b_dst->size, 2);
            if (road_tile.valid()) {
                base.destination_tile = road_tile;
                set_destination(senate_id);
                advance_action(ACTION_121_ROBBER_MOVING);
                route_remove();
            } else {
                advance_action(ACTION_123_ROBBER_LEAVING);
            }
            break;
        }
        case ACTION_123_ROBBER_LEAVING: {
            base.wait_ticks = 0;
            tile2i exit = g_city.map.exit_point;
            if (do_goto(exit, TERRAIN_USAGE_ANY)) {
                poof();
            }
            break;
        }
        case ACTION_121_ROBBER_MOVING: {
            base.move_ticks(1);
            base.wait_ticks = 0;
            if (direction() == DIR_FIGURE_NONE) {
                poof();
            } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
                advance_action(ACTION_120_ROBBER_CREATED);
                route_remove();
            } else if (direction() == DIR_FIGURE_ATTACK) {
                if (base.animctx.frame > 12) {
                    base.animctx.frame = 0;
                }
            }
            break;
        }
        case ACTION_122_ROBBER_HIDE:
            poof();
            break;
        case ACTION_10_ROBBER_FLEEING:
            // Gold-cart flee works in remake too (OG supplement).
            if (++base.wait_ticks > 10) {
                g_city.finance.process_stolen(100);
                show_robbery_warning("#gold_miner_robbed");
                show_robbery_message("message_tutorial_crime", 100, tile().grid_offset());
                poof();
            }
            break;
        default:
            advance_action(ACTION_120_ROBBER_CREATED);
            break;
        }

        if (action_state() != ACTION_10_ROBBER_FLEEING) {
            base.wait_ticks++;
            if (base.wait_ticks > 200) {
                poof();
                base.animctx.frame = 0;
            }
        }
        return;
    }

    // --- OG figure_criminal_action ---
    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_8_ROBBER_WAITING:
        if (++base.wait_ticks <= 0x28) {
            break;
        }
        {
            const int building_id = criminal_find_rich_building(base);
            if (!building_id) {
                poof();
                break;
            }
            building *b = building_get(building_id);
            tile2i road = b->road_access.valid() ? b->road_access : b->tile;
            base.destination_tile = road;
            set_destination(building_id);
            advance_action(ACTION_9_ROBBER_GOING_TO_ROB);
            base.wait_ticks = 0;
            route_remove();
        }
        break;

    case ACTION_9_ROBBER_GOING_TO_ROB: {
        // OG: move at 2× type speed.
        const int speed = std::max(1, (int)base.speed_multiplier) * 2;
        base.move_ticks(speed);
        if (direction() == DIR_FIGURE_NONE) {
            steal_from_destination(base);
            poof();
        } else if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH) {
            poof();
        }
        break;
    }

    case ACTION_10_ROBBER_FLEEING:
        if (++base.wait_ticks > 10) {
            g_city.finance.process_stolen(100);
            show_robbery_warning("#gold_miner_robbed");
            show_robbery_message("message_tutorial_crime", 100, tile().grid_offset());
            poof();
        }
        break;

    default: {
        // OG criminal_start: enter WAITING with random 0..9 wait.
        advance_action(ACTION_8_ROBBER_WAITING);
        random_generate_next();
        base.wait_ticks = (int16_t)((random_byte() & 0x7f) % 10);
        break;
    }
    }
}

void figure_robber::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE)) {
        animkey = animkeys().death;
    }
    image_set_animation(animkey);
}

void figure_robber::create(building *b) {
    g_city.sentiment.criminals++;
    auto house = b->dcast_house();
    if (!house) {
        return;
    }

    auto &housed = house->runtime_data();
    if (housed.criminal_active <= 60 || !g_city.sentiment.can_create_mugger) {
        return;
    }

    housed.criminal_active -= 60;
    tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
    if (!road_tile.valid()) {
        return;
    }

    // OG: when tomb robbers are possible, house crime prefers FIG_TOMB_ROBBER.
    const bool spawn_tomb = !game_features::gameplay_change_tomb_robber_remake.to_bool()
        && figure_tomb_robber::og_possible();
    figure *f = figure_create(spawn_tomb ? FIGURE_TOMB_ROBER : FIGURE_ROBBER, road_tile, DIR_4_BOTTOM_LEFT);
    f->wait_ticks = 10 + (b->map_random_7bit & 0xf);
    g_city.ratings.monument_record_criminal();

    if (spawn_tomb) {
        f->advance_action(ACTION_8_TOMB_ROBBER_WAITING);
        return;
    }

    if (game_features::gameplay_change_robber_remake.to_bool()) {
        f->advance_action(ACTION_120_ROBBER_CREATED);
        remake_instant_steal_on_create(*f);
    } else {
        // OG: wait state; theft happens on arrival at rich building.
        f->advance_action(ACTION_8_ROBBER_WAITING);
    }
}
