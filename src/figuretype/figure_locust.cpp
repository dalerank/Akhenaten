#include "figuretype/figure_locust.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_industry.h"
#include "city/city_warnings.h"
#include "core/random.h"
#include "game/game_events.h"
#include "graphics/image.h"
#include "grid/terrain.h"
#include "js/js_game.h"
#include "scenario/map.h"
#include "scenario/scenario.h"
#include "sound/sound.h"

#include <algorithm>
#include <iostream>
#include <vector>

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_locust);

namespace {

constexpr int k_locust_cloud_groups = 5; // SprMain2 g30–34

void apply_float_height(figure &f, int height) {
    f.target_height = (uint8_t)height;
    f.current_height = (uint8_t)height;
    // Refresh so advance_figure_tick does not decay height while idle/drifting.
    f.height_adjusted_ticks = 32;
}

tile2i pick_farm_spawn_tile() {
    std::vector<tile2i> farms;
    buildings_valid_farms_do([&](building &b) {
        tile2i t = b.tile;
        if (t.valid()) {
            farms.push_back(t);
        }
    });

    if (!farms.empty()) {
        tile2i base = farms[random_byte() % (int)farms.size()];
        // Jitter ±1 so clouds are not stacked on the building origin.
        int dx = (int)(random_byte() % 3) - 1;
        int dy = (int)(random_byte() % 3) - 1;
        tile2i jittered(base.x() + dx, base.y() + dy);
        if (jittered.valid() && !map_terrain_is(jittered, TERRAIN_WATER)) {
            return jittered;
        }
        return base;
    }

    scenario_map_init_entry_exit();
    tile2i entry = scenario_map_entry();
    if (entry.valid()) {
        return entry;
    }
    return tile2i(g_scenario.map.width / 2, g_scenario.map.height / 2);
}

void pick_drift_destination(figure &f) {
    // Cloud drifts over farmland / open ground — not road-roam (farms have no roads).
    // Prefer a different tile so zero-length CC paths don't instantly "arrive".
    tile2i dest = tile2i::invalid;
    for (int attempt = 0; attempt < 4; ++attempt) {
        tile2i cand = random_around_point(f.tile, f.tile, /*step*/3, /*bias*/6, /*max_dist*/12);
        if (!cand.valid() || map_terrain_is(cand, TERRAIN_WATER)) {
            continue;
        }
        if (cand != f.tile) {
            dest = cand;
            break;
        }
        if (!dest.valid()) {
            dest = cand;
        }
    }
    if (!dest.valid()) {
        dest = pick_farm_spawn_tile();
    }
    if (!dest.valid()) {
        dest = f.tile;
    }
    f.destination_tile = dest;
    // Clear stuck routing state so do_goto re-paths.
    if (f.direction >= 8) {
        f.direction = DIR_0_TOP_RIGHT;
    }
}

} // namespace

void figure_locust::on_create() {
    const auto &p = current_params();
    base.roam_wander_freely = true;
    base.max_roam_length = 320;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    // Float over crops/buildings — road roam_ticks would freeze on farm tiles.
    // action_perform resets use_cross_country every tick; figure_action sets it again.
    // Amphibian: CC drift can cross Nile/floodplain water; TERRAIN-only would kill().
    base.use_cross_country = true;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    apply_float_height(base, p.float_height);
    auto &d = runtime_data();
    d.days_left = p.swarm_days;
    d.cloud_variant = (uint8_t)(random_byte() % k_locust_cloud_groups);
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
    // Not wildlife — do not inflate city animals_number (uint8, shared with herds).
    base.use_cross_country = true;
    base.allow_move_type = EMOVE_AMPHIBIAN;
    base.terrain_usage = TERRAIN_USAGE_ANY;
    apply_float_height(base, current_params().float_height);

    switch (action_state()) {
    case ACTION_120_LOCUST_CREATED:
        if (base.wait_ticks > 0) {
            base.wait_ticks--;
            break;
        }
        pick_drift_destination(base);
        advance_action(ACTION_121_LOCUST_ROAMING);
        break;

    case ACTION_121_LOCUST_ROAMING:
        if (!base.destination_tile.valid()) {
            pick_drift_destination(base);
        }
        // Arrived / lost → pick another drift target (stay in ROAMING).
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_121_LOCUST_ROAMING, ACTION_121_LOCUST_ROAMING)) {
            pick_drift_destination(base);
        } else if (direction() == DIR_FIGURE_CAN_NOT_REACH || direction() == DIR_FIGURE_REROUTE) {
            pick_drift_destination(base);
        }
        break;

    case FIGURE_ACTION_149_CORPSE:
        base.figure_combat_handle_corpse();
        break;

    default:
        pick_drift_destination(base);
        advance_action(ACTION_121_LOCUST_ROAMING);
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

void figure_locust::update_day() {
    figure_impl::update_day();
    auto &d = runtime_data();
    if (d.days_left > 0) {
        d.days_left--;
    }
    if (d.days_left == 0) {
        poof();
    }
}

int figure_locust::spawn_swarm(int count) {
    const auto &p = figure_locust::current_params();
    if (count < 1) {
        count = p.default_swarm > 0 ? p.default_swarm : 8;
    }
    const int max_swarm = p.max_amount > 0 ? p.max_amount : 16;
    if (count > max_swarm) {
        count = max_swarm;
    }

    // Soft cap: repeated Osiris curses should not stack past max_amount.
    int live = 0;
    for (int i = 1; i < MAX_FIGURES; i++) {
        figure *f = figure_get(i);
        if (f && f->is_alive() && f->type == FIGURE_LOCUST) {
            live++;
        }
    }
    const int room = max_swarm - live;
    if (room <= 0) {
        return 0;
    }
    if (count > room) {
        count = room;
    }

    int first_id = 0;
    for (int i = 0; i < count; ++i) {
        tile2i spawn = pick_farm_spawn_tile();
        if (!spawn.valid()) {
            continue;
        }

        figure *f = figure_create(FIGURE_LOCUST, spawn, DIR_0_TOP_RIGHT);
        if (!f || !f->is_alive()) {
            continue;
        }

        auto &d = figure_locust(f).runtime_data();
        d.days_left = p.swarm_days;
        d.cloud_variant = (uint8_t)(random_byte() % k_locust_cloud_groups);
        f->allow_move_type = EMOVE_AMPHIBIAN;
        f->use_cross_country = true;
        apply_float_height(*f, p.float_height);
        f->advance_action(ACTION_120_LOCUST_CREATED);
        f->wait_ticks = (random_byte() & 0x7);
        if (!first_id) {
            first_id = f->id;
        }
    }

    return first_id;
}

void figure_locust::apply_plague(int swarm_count) {
    building_curse_farms(1);
    spawn_swarm(swarm_count);
    g_city.change_happiness(figure_locust::current_params().happiness_hit);
    // Cleopatra AUDIO/Ambient/Locusts.mp3 (sibling Frogs/Hailstorm for other plagues).
    events::emit(event_sound_track{ "plague_locusts" });
}

void __locust_apply_plague() {
    figure_locust::apply_plague();
}
ANK_FUNCTION(__locust_apply_plague)
