#include "figuretype/figure_locust.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_floods.h"
#include "core/log.h"
#include "core/random.h"
#include "game/game_events.h"
#include "graphics/image.h"
#include "js/js_game.h"
#include "scenario/scenario.h"

#include <algorithm>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_locust);

namespace {

constexpr int k_locust_cloud_groups = 5; // SprMain2 g30–34

void apply_float_height(figure &f, int height) {
    f.target_height = (uint8_t)height;
    f.current_height = (uint8_t)height;
    // Refresh so advance_figure_tick does not decay height while idle/drifting.
    f.height_adjusted_ticks = 32;
}

int random_15bit() {
    random_generate_next();
    return (uint16_t)random_short() & 0x7fff;
}

int flood_month_before() {
    const int month = g_floods.season / 30 - 1;
    return month < 0 ? month + 12 : month;
}

} // namespace

void figure_locust::on_create() {
    base.terrain_usage = TERRAIN_USAGE_ANY;
    base.use_cross_country = true;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    apply_float_height(base, current_params().float_height);
    runtime_data().cloud_variant = (uint8_t)(random_byte() % k_locust_cloud_groups);
    advance_action(ACTION_120_LOCUST_CREATED);
}

void figure_locust::on_post_load() {
    base.use_cross_country = true;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    apply_float_height(base, current_params().float_height);
    auto &d = runtime_data();
    if (d.cloud_variant >= k_locust_cloud_groups) {
        d.cloud_variant = 0;
    }
}

void figure_locust::figure_action() {
    const auto& p = current_params();
    base.use_cross_country = true;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    apply_float_height(base, p.float_height);

    building* field = building_get(runtime_data().farm_id);
    if (!field || !field->is_valid() || !field->is_farm()) {
        poof();
        return;
    }

    switch (action_state()) {
    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    case ACTION_120_LOCUST_CREATED:
        base.set_flag(e_figure_flag_invisible, true);
        if (--base.wait_ticks < 1) {
            if (!base.destination_tile.valid()) {
                poof();
                break;
            }
            advance_action(ACTION_121_LOCUST_GOING_TO_FIELD);
        }
        break;

    case ACTION_121_LOCUST_GOING_TO_FIELD:
        base.set_flag(e_figure_flag_invisible, false);
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_122_LOCUST_EATING, ACTION_123_LOCUST_FLYING_OFF)) {
            base.destination_tile = field->tile;
        } else if (action_state() == ACTION_123_LOCUST_FLYING_OFF) {
            poof();
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
        if (!base.destination_tile.valid()
            || do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_123_LOCUST_FLYING_OFF,
              ACTION_123_LOCUST_FLYING_OFF)
            || direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            poof();
        }
        break;

    default:
        advance_action(ACTION_120_LOCUST_CREATED);
        break;
    }
}

void figure_locust::update_animation() {
    // Timing strip from JS walk (g30); main_image_update remaps to variant group.
    image_set_animation(animkeys().walk);
}

void figure_locust::main_image_update() {
    // Cloud strip is NOT 8-dir (group has only 6 frames). Default
    // start+dir+8*frame would read past the atlas into neighboring groups.
    const int variant = std::min<int>(runtime_data().cloud_variant, k_locust_cloud_groups - 1);
    const int start = image_id_from_group(PACK_EXPANSION_SPR, 30 + variant);
    // Pharaoh-only / missing SprMain2: hide rather than garbage atlas reads.
    if (start <= 0) {
        base.main_image_id = 0;
        return;
    }
    const int frame = std::min<int>(base.animctx.current_frame(), 5);
    base.main_image_id = start + frame;
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
    buildings_valid_farms_do([&](building& farm) {
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
    });

    events::emit(event_sound_track{"plague_locusts"});
    logs::info("[disaster] locusts hit the farms, locusts=%d countdown=%d", locusts, g_city.plagues.locusts_countdown);
}

void __locust_start_plague() {
    figure_locust::start_plague();
}
ANK_FUNCTION(__locust_start_plague)
