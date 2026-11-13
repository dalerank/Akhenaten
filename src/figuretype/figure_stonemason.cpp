#include "figure_stonemason.h"

#include "building/monument_caesareum.h"
#include "building/monument_mastaba.h"
#include "building/monument_pyramid.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_obelisk.h"
#include "building/monument_royal_tomb.h"
#include "building/monument_sphinx.h"
#include "building/monument_sun_temple.h"
#include "building/monument_alexandria_library.h"
#include "building/monument_mausoleum.h"
#include "building/building_statue.h"
#include "building/monuments.h"
#include "building/monument_pyramid_figure.h"
#include "game/simulation_time.h"
#include "grid/terrain.h"
#include "grid/grid.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_stonemason);

const figure_stonemason_action_tokens_t ANK_CONFIG_ENUM(figure_stonemason_action_tokens)

void figure_stonemason::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    building *bhome = home();
    building *b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    if (!bhome->is_valid() || !b_dest->is_valid()) {
        poof();
        return;
    }

    if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (action_state()) {
    case ACTION_11_MASON_CREATED_ROAMING:
        base.destination_tile = destination()->access_tile();
        advance_action(ACTION_12_MASON_GOING_TO_STATUE);
        break;

    case ACTION_0_MASON_CREATED: {
            if (b_dest->dcast_mausoleum()) {
                if (!building_mausoleum::find_work_for_figure(id())) {
                    advance_action(ACTION_6_MASON_RETURN_HOME);
                }
                break;
            }
            if (auto *cae = b_dest->dcast_caesareum()) {
                if (!cae->claim_worker(base)) {
                    advance_action(ACTION_6_MASON_RETURN_HOME);
                    break;
                }
            }
            // Prefer monument access_point (enter_offset); fall back to access_tile.
            if (auto *mon = b_dest->dcast_monument()) {
                base.destination_tile = mon->access_point();
            } else {
                base.destination_tile = destination()->access_tile();
            }
            advance_action(ACTION_1_MASON_GOING);
        }
        break;

    case ACTION_10_MASON_DESTROY:
        poof();
        break;

    case ACTION_12_MASON_GOING_TO_STATUE:
        do_goto(base.destination_tile, terrain_usage,
                ACTION_13_MASON_WORK_STATUE_GROUND, ACTION_10_MASON_DESTROY);
        break;

    case ACTION_1_MASON_GOING: {
        auto *sun = b_dest->dcast_sun_temple();
        auto *library = b_dest->dcast_alexandria_library();
        const bool to_obelisk = b_dest->dcast_obelisk() != nullptr || b_dest->dcast_sphinx() != nullptr
                                || b_dest->dcast_royal_tomb() != nullptr || (sun && sun->part_index() == 0);
        const bool to_og_pyramid = b_dest->dcast_pyramid()
            && g_monument_pyramid_engine.uses_block_engine(b_dest);
        short arrived = to_obelisk
            ? (short)ACTION_9_MASON_WORK_OBELISK
            : (to_og_pyramid ? (short)ACTION_16_MASON_CLIMB_RAMP : (short)ACTION_7_MASON_LOOKING_FOR_WORK_TILE);
        // OG: side parts / library mason wait for a material sled before working.
        if ((sun && sun->part_index() != 0) || library || b_dest->dcast_mausoleum() || b_dest->dcast_caesareum()) {
            arrived = ACTION_19_MASON_WAIT_FOR_BLOCK;
        }
        if (do_goto(base.destination_tile, terrain_usage, arrived, ACTION_10_MASON_DESTROY)) {
            base.wait_ticks = 0;
            if (to_obelisk) {
                // Obelisk is impassable — stand at access_point; building draws work anim.
                base.set_flag(e_figure_flag_invisible);
            } else if (to_og_pyramid) {
                // OG: pyramid_figure_start_climb then walk_on_ramp each tick.
                pyramid_figure_start_climb(id());
            }
        }
        break;
    }

    case ACTION_16_MASON_CLIMB_RAMP: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        pyramid_figure_walk_on_ramp(id(), 0, ACTION_6_MASON_RETURN_HOME, ACTION_17_MASON_FIND_PART);
        break;
    }

    case ACTION_17_MASON_FIND_PART: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        pyramid_figure_find_next_part(id(), 1, ACTION_6_MASON_RETURN_HOME, ACTION_20_MASON_NEXT_CASING,
            ACTION_18_MASON_WALK_TO_PART);
        route_remove();
        break;
    }

    case ACTION_18_MASON_WALK_TO_PART: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        auto &rd = runtime_data();
        if (rd.walk_mode != PYRAMID_WALK_NONE) {
            if (!pyramid_figure_climb_step(id(), 1)) {
                break;
            }
            pyramid_figure_snap_to_part(id());
            auto *ps = pyramid_part_state_get(rd.part_bid ? rd.part_bid : pyramid_figure_work_part_bid(&base));
            base.wait_ticks = 0;
            if (ps && ps->stage == PYRAMID_STAGE_MAIN_MATERIAL) {
                advance_action(ACTION_19_MASON_WAIT_FOR_BLOCK);
            } else {
                advance_action(ACTION_21_MASON_PYRAMID_WORK);
            }
        }
        break;
    }

    case ACTION_20_MASON_NEXT_CASING: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        pyramid_stonemason_arrive_part(id());
        break;
    }

    case ACTION_19_MASON_WAIT_FOR_BLOCK: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        // OG sun temple / library: linger until a laborer sled wakes us to WORK.
        if (auto *sun = b_dest->dcast_sun_temple()) {
            if (sun->runtime_data().og_part.worker_figure_id != id()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *maus = b_dest->dcast_mausoleum()) {
            if (maus->runtime_data().og_part.worker_figure_id != id()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *cae = b_dest->dcast_caesareum()) {
            if (cae->worker_figure_id() != id()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *library = b_dest->dcast_alexandria_library()) {
            auto *main = library->main_library();
            if (!main || main->runtime_data().og_part.worker_figure_id != id()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        auto &rd = runtime_data();
        if (rd.walk_mode == PYRAMID_WALK_NONE) {
            advance_action(ACTION_6_MASON_RETURN_HOME);
            break;
        }
        auto *ps = pyramid_part_state_get(rd.part_bid);
        if (!ps || ps->worker_figure_id != id()) {
            advance_action(ACTION_6_MASON_RETURN_HOME);
            rd.walk_mode = PYRAMID_WALK_NONE;
        }
        break;
    }

    case ACTION_21_MASON_PYRAMID_WORK: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        auto &rd = runtime_data();
        building_id part_id = rd.part_bid ? rd.part_bid : pyramid_figure_work_part_bid(&base);
        // Casing ticks via shared place_block path when wired; otherwise linger then home.
        if (part_id && g_monument_pyramid_engine.uses_block_engine(b_dest)) {
            pyramid_engine_place_block(part_id, id());
        } else {
            advance_action(ACTION_6_MASON_RETURN_HOME);
        }
        break;
    }

    case ACTION_7_MASON_LOOKING_FOR_WORK_TILE: {
        // Bail if monument finished while we were still on-site (progress may
        // still look "workable" if the last phase skipped the zeroing clear).
        if (auto *mon = b_dest->dcast_monument()) {
            if (mon->is_finished()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
                return;
            }
        }
        // Mastaba / pyramid: claim a 2×2 work site (same pattern as bricklayers).
        // Sphinx: time-based progress() on the monument — linger then home.
        if (smart_cast<building_mastaba>(b_dest) || smart_cast<building_pyramid>(b_dest)) {
            tile2i wait_tile = building_monument_mason_waiting_tile(b_dest);
            if (!wait_tile.valid()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
                return;
            }

            map_grid_area_foreach(wait_tile.shifted(-1, -1), wait_tile, [] (tile2i t) {
                if (!map_monuments_get_progress(t)) {
                    map_monuments_set_progress(t, 1);
                }
            });

            base.destination_tile = wait_tile;
            advance_action(ACTION_2_MASON_GOING_TO_PLACE);
        } else {
            base.wait_ticks++;
            if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
        }
        break;
    }

    case ACTION_5_MASON_WORK_WALL:
        break;

    case ACTION_9_MASON_WORK_OBELISK: {
        if (auto *maus = b_dest->dcast_mausoleum()) {
            base.set_flag(e_figure_flag_invisible);
            if (maus->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                maus->remove_worker(id());
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        building *worked = building_get(runtime_data().destination_bid);
        if (!worked || !worked->id) {
            worked = destination();
        }
        if (auto* tomb = worked ? worked->dcast_royal_tomb() : nullptr) {
            base.set_flag(e_figure_flag_invisible);
            if (tomb->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                tomb->remove_worker(id());
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *sphinx = worked ? worked->dcast_sphinx() : nullptr) {
            base.set_flag(e_figure_flag_invisible);
            if (sphinx->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *cae = worked ? worked->dcast_caesareum() : nullptr) {
            base.set_flag(e_figure_flag_invisible);
            if (cae->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *sun = worked ? worked->dcast_sun_temple() : nullptr) {
            base.set_flag(e_figure_flag_invisible);
            if (sun->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                if (auto *mon = worked->dcast_monument()) {
                    mon->remove_worker(id());
                }
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        if (auto *library = worked ? worked->dcast_alexandria_library() : nullptr) {
            base.set_flag(e_figure_flag_invisible);
            if (library->work_tick(base)) {
                base.set_flag(e_figure_flag_invisible, false);
                if (auto *mon = worked->dcast_monument()) {
                    mon->remove_worker(id());
                }
                advance_action(ACTION_6_MASON_RETURN_HOME);
            }
            break;
        }
        auto *obelisk = worked ? worked->dcast_obelisk() : nullptr;
        if (!obelisk) {
            advance_action(ACTION_6_MASON_RETURN_HOME);
            break;
        }

        base.set_flag(e_figure_flag_invisible);
        obelisk->set_stonemason_works(id());

        base.wait_ticks++;
        if (base.wait_ticks > obelisk->current_work_ticks()) {
            obelisk->stonemason_complete_work();
            base.set_flag(e_figure_flag_invisible, false);
            advance_action(ACTION_6_MASON_RETURN_HOME);
        }
        break;
    }

    case ACTION_2_MASON_GOING_TO_PLACE:
        base.roam_wander_freely = false;
        if (auto *mon = b_dest->dcast_monument(); mon && mon->is_finished()) {
            advance_action(ACTION_6_MASON_RETURN_HOME);
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY,
                    ACTION_3_MASON_WAITING_RESOURCES, ACTION_6_MASON_RETURN_HOME)) {
            base.wait_ticks = 0;
            runtime_data().idle_wait_count = 0;
            base.direction = 0;
            // Only claim idle tiles — never wipe mid-progress on resume after poof.
            map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                if (map_monuments_get_progress(t) == 0) {
                    map_monuments_set_progress(t, 1);
                }
            });
        }
        break;

    case ACTION_3_MASON_WAITING_RESOURCES: {
            if (auto *mon = b_dest->dcast_monument(); mon && mon->is_finished()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
                break;
            }
            base.wait_ticks++;
            if (base.wait_ticks > 30) {
                auto &d = runtime_data();
                base.wait_ticks = 0;
                d.idle_wait_count++;
                int progress = map_monuments_get_progress(tile());
                // Already past the material gate (or resumed mid-lay) → work.
                if (progress >= 2 && progress < 200) {
                    advance_action(ACTION_4_MASON_WORK_GROUND);
                } else {
                    bool area_ready = true;
                    map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                        area_ready &= (map_monuments_get_progress(t) == 2);
                    });
                    if (area_ready) {
                        advance_action(ACTION_4_MASON_WORK_GROUND);
                    } else if (d.idle_wait_count > 20) {
                        advance_action(ACTION_6_MASON_RETURN_HOME);
                    }
                }
            }
        }
        break;

    case ACTION_13_MASON_WORK_STATUE_GROUND:
    case ACTION_14_MASON_WORK_STATUE_WALL:
        base.wait_ticks++;
        if (base.wait_ticks > simulation_time_t::ticks_in_day * 2) {
            auto statue = smart_cast<building_statue>(building_get(runtime_data().destination_bid));
            if (statue) {
                statue->set_service(100);
            }
            advance_action(ACTION_6_MASON_RETURN_HOME);
        }
        break;

    case ACTION_4_MASON_WORK_GROUND: {
            if (auto *mon = b_dest->dcast_monument(); mon && mon->is_finished()) {
                advance_action(ACTION_6_MASON_RETURN_HOME);
                break;
            }
            int progress = map_monuments_get_progress(tile());
            if (progress < 200) {
                map_grid_area_foreach(tile().shifted(-1, -1), tile(), [&] (tile2i t) {
                    map_monuments_set_progress(t, progress + 1);
                });
            } else {
                advance_action(ACTION_7_MASON_LOOKING_FOR_WORK_TILE);
            }
        }
        break;

    case ACTION_6_MASON_RETURN_HOME:
        base.set_flag(e_figure_flag_invisible, false);
        // Fail → destroy (action 8 had no handler and left the walker stuck).
        if (do_gotobuilding(home(), true, TERRAIN_USAGE_PREFER_ROADS,
                            ACTION_10_MASON_DESTROY, ACTION_10_MASON_DESTROY)) {
            poof();
        }
        break;

    case ACTION_8_MASON_RANDOM_TILE:
        // Legacy fail state from older saves — just leave.
        advance_action(ACTION_10_MASON_DESTROY);
        break;
    }
}

void figure_stonemason::on_destroy() {
    figure_impl::on_destroy();

    base.set_flag(e_figure_flag_invisible, false);

    // Clear monument/statue worker slot. destination_bid is set at spawn; fall back
    // to figure destination when missing (older saves / mid-path).
    building *b_dest = building_get(runtime_data().destination_bid);
    if (!b_dest || !b_dest->id) {
        b_dest = destination();
    }
    if (b_dest && b_dest->id) {
        b_dest->remove_figure_by_id(base.id);
        if (auto *mon = b_dest->dcast_monument()) {
            mon->remove_worker(base.id);
        }
    }
}

void figure_stonemason::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_3_MASON_WAITING_RESOURCES:
        image_set_animation(animkeys().work_ground);
        break;

    case ACTION_4_MASON_WORK_GROUND:
    case ACTION_13_MASON_WORK_STATUE_GROUND:
        image_set_animation(animkeys().work_ground);
        break;

    case ACTION_5_MASON_WORK_WALL:
    case ACTION_9_MASON_WORK_OBELISK:
    case ACTION_14_MASON_WORK_STATUE_WALL:
        image_set_animation(animkeys().work_wall);
        break;

    case ACTION_6_MASON_RETURN_HOME:
        image_set_animation(animkeys().walk);
        break;

    case ACTION_16_MASON_CLIMB_RAMP:
    case ACTION_18_MASON_WALK_TO_PART:
    case ACTION_20_MASON_NEXT_CASING:
        image_set_animation(animkeys().walk);
        break;

    case ACTION_19_MASON_WAIT_FOR_BLOCK:
        image_set_animation(animkeys().work_ground);
        break;

    case ACTION_21_MASON_PYRAMID_WORK:
        image_set_animation(animkeys().work_wall);
        break;
    }
}
