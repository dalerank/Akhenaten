#include "figuretype/figure_locust.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_floods.h"
#include "core/log.h"
#include "core/random.h"
#include "game/game_events.h"
#include "js/js_game.h"
#include "scenario/scenario.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_locust);

namespace {

int random_15bit() {
    random_generate_next();
    return (uint16_t)random_short() & 0x7fff;
}

int flood_month_before() {
    const int month = g_floods.season_month - 1;
    return month < 0 ? month + 12 : month;
}

bool field_in_use(const building& field) {
    return field.state == BUILDING_STATE_VALID || field.state == BUILDING_STATE_MOTHBALLED;
}

} // namespace

void figure_locust::on_create() {
    base.terrain_usage = TERRAIN_USAGE_ANYWHERE;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    advance_action(ACTION_120_LOCUST_CREATED);
}

void figure_locust::figure_action() {
    const auto& p = current_params();
    base.terrain_usage = TERRAIN_USAGE_ANYWHERE;

    building* field = building_get(runtime_data().farm_id);
    if (!field || !field_in_use(*field)) {
        poof();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        break;

    case ACTION_120_LOCUST_CREATED:
        base.set_flag(e_figure_flag_invisible, true);
        base.animctx.restart();
        if (--base.wait_ticks < 1) {
            base.figure_route_add();
            if (base.routing_path_id < 1) {
                poof();
            } else {
                advance_action(ACTION_121_LOCUST_GOING_TO_FIELD);
            }
        }
        break;

    case ACTION_121_LOCUST_GOING_TO_FIELD:
        base.set_flag(e_figure_flag_invisible, false);
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_REROUTE) {
            advance_action(ACTION_120_LOCUST_CREATED);
            base.wait_ticks = 1;
            base.route_remove();
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH) {
            field->distance_from_entry = 0;
            poof();
        } else if (direction() == DIR_FIGURE_NONE) {
            advance_action(ACTION_122_LOCUST_EATING);
            base.destination_tile = field->tile;
        }
        break;

    case ACTION_122_LOCUST_EATING: {
        const int countdown = g_city.plagues.locusts_countdown;
        const int cap = std::max(0, countdown - p.countdown_fly_off);
        if (field->progress > cap) {
            field->progress = (uint16_t)cap;
            if (auto* farm = field->dcast_farm()) {
                farm->update_tiles_image();
            }
        }
        if (countdown <= p.countdown_fly_off) {
            const int width = g_scenario.map.width;
            const int r = random_15bit() % std::max(1, width / 4);
            base.destination_tile = tile2i(width * 3 / 8 - r + 2, width * 7 / 8 - r - 2);
            base.roam_length = 0;
            advance_action(ACTION_123_LOCUST_FLYING_OFF);
        }
        break;
    }

    case ACTION_123_LOCUST_FLYING_OFF:
        base.set_flag(e_figure_flag_invisible, false);
        base.move_ticks(base.speed_multiplier);
        if (direction() == DIR_FIGURE_REROUTE || direction() == DIR_FIGURE_CAN_NOT_REACH
            || direction() == DIR_FIGURE_NONE) {
            poof();
        }
        break;

    default:
        advance_action(ACTION_120_LOCUST_CREATED);
        break;
    }
}

void figure_locust::update_animation() {
    image_set_animation(action_state() == ACTION_122_LOCUST_EATING ? animkeys().eating : animkeys().walk);
}

void figure_locust::main_image_update() {
    base.main_image_id = base.animctx.start_frame() + base.animctx.current_frame();
}

void figure_locust::start_plague() {
    g_city.plagues.locusts_countdown = -1;
    g_city.change_happiness(-current_params().happiness_loss);
}

void figure_locust::update_month(int month) {
    if (g_city.plagues.locusts_countdown != -1) {
        return;
    }
    const auto& p = current_params();
    const int flood_month = flood_month_before();
    if (flood_month != month + p.months_before_flood && flood_month != month + p.months_before_flood - 12) {
        return;
    }

    g_city.plagues.locusts_countdown = p.countdown_after_plague;
    const int width = g_scenario.map.width;
    const int side = std::max<int>(1, p.square_side);
    int locusts = 0;
    for (auto& farm : city_buildings()) {
        if (farm.state == BUILDING_STATE_UNUSED || !farm.is_farm()) {
            continue;
        }
        for (int i = 0; i < p.locusts_per_farm; i++) {
            const int offset = random_15bit() % std::max(1, width / 4);
            const tile2i spawn(width * 7 / 8 - offset, width * 3 / 8 - offset);
            figure* f = figure_create(FIGURE_LOCUST, spawn, DIR_0_TOP_RIGHT);
            if (!f || !f->is_alive()) {
                continue;
            }
            figure_locust(f).runtime_data().farm_id = farm.id;
            f->advance_action(ACTION_120_LOCUST_CREATED);
            f->wait_ticks = (int16_t)(random_15bit() % std::max<int>(1, p.max_start_delay));
            f->destination_tile = tile2i(farm.tile.x() + i / side, farm.tile.y() + i % side);
            locusts++;
        }

        building_farm* field = farm.dcast_farm();
        if (field && farm.num_workers > 0) {
            auto& d = field->runtime_data();
            d.labor_days_left = 0;
            farm.num_workers = 0;
            figure* laborer = figure_get(d.worker_id);
            if (d.worker_id && laborer->is_alive() && laborer->type == FIGURE_LABORER) {
                laborer->poof();
            }
            d.worker_id = 0;
        }
    }

    events::emit(event_sound_track{"plague_locusts"});
    logs::info("[disaster] locusts hit the farms, locusts=%d countdown=%d", locusts, g_city.plagues.locusts_countdown);
}

void __locust_start_plague() {
    figure_locust::start_plague();
}
ANK_FUNCTION(__locust_start_plague)
