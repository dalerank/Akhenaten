#include "figuretype/figure_frog.h"

#include "building/building.h"
#include "building/building_house.h"
#include "city/city.h"
#include "city/city_message.h"
#include "city/city_warnings.h"
#include "core/calc.h"
#include "core/log.h"
#include "core/random.h"
#include "dev/debug.h"
#include "figuretype/figure_homeless.h"
#include "game/game_events.h"
#include "game/simulation_time.h"
#include "grid/grid.h"
#include "grid/road_access.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/scenario.h"

#include <cmath>
#include <vector>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_frog);

namespace {

    int random_15bit() {
        random_generate_next();
        return (uint16_t)random_short() & 0x7fff;
    }

void cancel_incoming_immigrant(building &b) {
    figure *f = b.get_figure(BUILDING_SLOT_IMMIGRANT);
    b.remove_figure(BUILDING_SLOT_IMMIGRANT);
    if (!f || !f->is_alive()) {
        return;
    }
    if (f->type == FIGURE_IMMIGRANT) {
        f->poof();
        return;
    }
    if (f->type == FIGURE_HOMELESS) {
        if (auto *hl = f->dcast_homeless()) {
            hl->runtime_data().adv_home_building_id = 0;
        }
        f->home_building_id = 0;
        f->advance_action(ACTION_0_HOMELESS_CREATED);
        f->wait_ticks = 0;
    }
}

// OG animals.c search_rings: square rings around the tile, top row first, clockwise.
bool find_nearest_terrain(tile2i from, int terrain, int rings, tile2i& out) {
    static const int dx[4] = {1, 0, -1, 0};
    static const int dy[4] = {0, 1, 0, -1};
    for (int ring = 0; ring <= rings; ring++) {
        const int size = 2 * ring + 1;
        int x = from.x() - ring;
        int y = from.y() - ring;
        for (int side = 0; side < 4; side++) {
            for (int i = 0; i < size; i++) {
                const tile2i t(x, y);
                if (map_grid_is_inside(t, 1) && map_terrain_is(t, terrain) && !map_terrain_is(t, TERRAIN_DIKE)) {
                    out = t;
                    return true;
                }
                x += dx[side];
                y += dy[side];
            }
            x -= dx[side];
            y -= dy[side];
        }
    }
    return false;
}

int distance_to(tile2i a, tile2i b) {
    const int dx = a.x() - b.x();
    const int dy = a.y() - b.y();
    return (int)std::sqrt((double)(dx * dx + dy * dy));
}

void infest_by_chance(building& house) {
    const auto& p = figure_frog::current_params();
    const int roll = random_15bit() % 100;
    tile2i water;
    if (roll < p.house_chance && figure_frog::find_water(house, water)) {
        figure_frog::create_at(house, water);
    }
}

} // namespace

bool figure_frog::find_water(building& house, tile2i& out) {
    const int limit = std::max(g_scenario.map.width, g_scenario.map.height);
    tile2i marsh_tile;
    tile2i water_tile;
    int marsh = limit;
    if (find_nearest_terrain(house.tile, TERRAIN_MARSHLAND, limit, marsh_tile)) {
        marsh = distance_to(house.tile, marsh_tile);
    }
    int water = limit;
    if (find_nearest_terrain(house.tile, TERRAIN_WATER, limit, water_tile)) {
        water = distance_to(house.tile, water_tile);
    }
    if (marsh > water && water < limit) {
        out = water_tile;
        return true;
    }
    if (marsh < water && marsh < limit) {
        out = marsh_tile;
        return true;
    }
    return false;
}

figure* figure_frog::create_at(building& house, tile2i water) {
    figure* f = figure_create(FIGURE_FROG, water, DIR_0_TOP_RIGHT);
    if (!f || !f->is_alive()) {
        return nullptr;
    }
    figure_frog(f).runtime_data().house_id = house.id;
    cancel_incoming_immigrant(house);
    house.set_figure(BUILDING_SLOT_IMMIGRANT, f->id);
    f->advance_action(ACTION_120_FROG_CREATED);
    f->wait_ticks = (int16_t)(random_15bit() % std::max<int>(1, current_params().max_start_delay));
    return f;
}

void figure_frog::infest_house(building& b) {
    auto* house = b.dcast_house();
    if (!house || !house->hsize()) {
        return;
    }
    auto& d = house->runtime_data();
    const int pop = house->house_population();
    if (pop > 0) {
        events::emit(event_create_homeless{b.tile, pop, SOURCE_LOCATION});
        d.population = 0;
    }
    // OG keeps the house sick for whole months of the frog countdown; our infestation counts days.
    const int months
      = g_city.plagues.frogs_countdown / simulation_time_t::ticks_in_day / simulation_time_t::days_in_month;
    d.frog_infest_days = (uint8_t)calc_bound(std::max(1, months) * simulation_time_t::days_in_month, 1, 255);
}

void figure_frog::start_plague(int amount) {
    const auto& p = current_params();
    g_city.plagues.frogs_countdown = amount * p.ticks_per_amount;

    std::vector<building_house*> houses;
    int level = 0;
    int people = 0;
    buildings_house_do([&](building_house* house) {
        if (!house->base.is_valid() || !house->hsize()) {
            return;
        }
        houses.push_back(house);
        level = std::max<int>(level, house->type());
        people += house->house_population();
    });

    const int target = people * p.people_percent / 100;
    int sum = 0;
    for (; level >= BUILDING_HOUSE_CRUDE_HUT && sum < target; level--) {
        for (building_house* house : houses) {
            if (house->type() != level) {
                continue;
            }
            sum += house->house_population();
            if (sum <= target) {
                infest_by_chance(house->base);
            }
        }
    }

    events::emit(event_sound_track{"plague_frogs"});
    g_city.change_happiness(-p.happiness_loss);
    logs::info("[disaster] frogs amount=%d countdown=%d target=%d", amount, g_city.plagues.frogs_countdown, target);
}

void figure_frog::on_create() {
    base.terrain_usage = TERRAIN_USAGE_AMPHIBIA;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    advance_action(ACTION_120_FROG_CREATED);
}

void figure_frog::on_post_load() {
    base.terrain_usage = TERRAIN_USAGE_AMPHIBIA;
    base.allow_move_type = EMOVE_AMPHIBIAN;
}

void figure_frog::figure_action() {
    base.terrain_usage = TERRAIN_USAGE_AMPHIBIA;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    const auto& p = current_params();

    building* b = building_get(runtime_data().house_id);
    building_house* house = (b && b->is_valid()) ? b->dcast_house() : nullptr;
    if (!house || !house->hsize() || !b->has_figure(BUILDING_SLOT_IMMIGRANT, id())) {
        poof();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_120_FROG_CREATED: {
        base.set_flag(e_figure_flag_invisible, true);
        if (--base.wait_ticks > 0) {
            break;
        }
        const tile2i road = map_closest_road_within_radius(b->tile, b->size, p.road_radius);
        if (!road.valid()) {
            poof();
            break;
        }
        base.destination_tile = road;
        base.roam_length = 0;
        advance_action(ACTION_121_FROG_GOING_TO_HOUSE);
        break;
    }

    case ACTION_121_FROG_GOING_TO_HOUSE:
        base.set_flag(e_figure_flag_invisible, false);
        if (random_15bit() % 100 >= p.move_chance) {
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_AMPHIBIA, ACTION_122_FROG_ENTERING_HOUSE,
              ACTION_121_FROG_GOING_TO_HOUSE)) {
            base.set_cross_country_destination(b->tile);
            base.roam_length = 0;
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            b->remove_figure(BUILDING_SLOT_IMMIGRANT);
            poof();
        }
        break;

    case ACTION_122_FROG_ENTERING_HOUSE:
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (base.move_ticks_cross_country(1) == 1) {
            infest_house(*b);
            b->remove_figure(BUILDING_SLOT_IMMIGRANT);
            poof();
        }
        break;

    default:
        advance_action(ACTION_120_FROG_CREATED);
        break;
    }
}

void figure_frog::update_animation() {
    xstring animkey = animkeys().walk;
    if (action_state(FIGURE_ACTION_149_CORPSE) || !base.is_alive()) {
        animkey = animkeys().death;
    } else if (action_state() == ACTION_120_FROG_CREATED || direction() == DIR_FIGURE_NONE) {
        animkey = animkeys().idle;
    }
    image_set_animation(animkey);
}

declare_console_command_p(frog_plague) {
    figure_frog::start_plague(figure_frog::current_params().ptah_curse_amount);
    messages::popup("message_plague_of_frogs", 0, 0);
    events::emit(event_city_warning{"Frog Plague"});
}
