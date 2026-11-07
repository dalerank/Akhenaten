#include "figure_worker.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "building/building_storage_yard.h"
#include "building/monument_mastaba.h"
#include "grid/building.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_figure.h"
#include "building/monument_sun_temple.h"
#include "building/monuments.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_sled.h"
#include "figuretype/figure_stonemason.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "city/city_recorded_paths.h"
#include "city/ratings.h"
#include "graphics/image_groups.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_worker);

bool figure_worker::uses_ramp_climb(building *monument) const {
    building *head = monument ? (monument->main() ? monument->main() : monument) : nullptr;
    if (!head) {
        return false;
    }
    return mastaba_engine_is(head)
        || (g_monument_pyramid_engine.uses_block_engine(head) && !mastaba_engine_is(head));
}

tile2i figure_worker::ramp_entry_tile(building *monument) const {
    building *head = monument ? (monument->main() ? monument->main() : monument) : nullptr;
    if (!head) {
        return tile2i::invalid;
    }
    if (mastaba_engine_is(head)) {
        tile2i t = mastaba_engine_entry_tile(head);
        if (t.valid()) {
            return t;
        }
    }
    if (auto *mon = head->dcast_monument()) {
        return mon->access_point();
    }
    return head->tile;
}

static void worker_handoff_path_to_camp(figure &f) {
    if (!f.trail_path_id) {
        return;
    }
    building *h = f.home();
    if (!h || !h->params().flags.keeps_visitor_paths) {
        return;
    }
    building *main = h->main();
    if (main) {
        g_recorded_paths.handoff_to_building(f, main->id);
    }
}

tile2i figure_worker::monumen_tile4work(building *b) {
    building_monument *mastaba = b->dcast_monument();
    if (!mastaba) {
        return tile2i{-1, -1};
    }

    auto &d = mastaba->runtime_data();
    if (d.phase >= 2) {
        return tile2i{-1, -1};
    }

    grid_tiles tiles;
    if (b->dcast_sun_temple()) {
        building *main = b->main();
        const int body = main->size > 0 ? main->size : 10;
        tiles = map_grid_get_tiles(main->tile, main->tile.shifted(body - 1, body - 1));
    } else {
        tiles = map_grid_get_tiles(b, 0);
    }
    tile2i tile = map_grid_area_first(tiles, [&mastaba](tile2i tile) {
        int progress = map_monuments_get_progress(tile);
        if (!progress) {
            return true;
        }

        if (progress == 200) {
            return false;
        }

        auto workers = mastaba->active_workers();
        for (const auto &id : workers) {
            if (id) {
                figure *f = figure_get(id);
                if (f->destination_tile == tile) {
                    return false;
                }
            }
        }

        return true;
    });

    return tile;
}

void figure_worker::assign_brick_delivery(building *monument, figure_id mason_fid) {
    auto &rd = runtime_data();
    rd.mason_fid = mason_fid;
    rd.delivering_block = 1;
    rd.walk_mode = PYRAMID_WALK_NONE;
    set_destination(monument);
    base.wait_ticks = 0;
    base.leading_figure_id = (int16_t)mason_fid;
    if (figure *mason = figure_get(mason_fid)) {
        mason->leading_figure_id = (int16_t)id();
    }

    tile2i yard_tile;
    int understaffed = 0;
    building_id yard_id = building_storage_yard_for_storing(
        tile(), RESOURCE_BRICKS, 0, -1, &understaffed, yard_tile);
    if (yard_id && yard_tile.valid()) {
        base.destination_tile = yard_tile;
        advance_action(ACTION_15_LABORER_TO_STORAGE_YARD);
        return;
    }

    // No yard: go straight to waiting mason (tests / understocked cities).
    figure *mason = figure_get(mason_fid);
    if (mason && mason->is_alive()) {
        if (uses_ramp_climb(monument)) {
            tile2i entry = ramp_entry_tile(monument);
            base.destination_tile = entry.valid() ? entry : mason->tile;
        } else {
            base.destination_tile = mason->tile;
        }
        advance_action(ACTION_17_LABORER_TO_PYRAMID);
    } else {
        advance_action(ACTION_13_LABORER_RETURNING);
        set_destination(home());
    }
}

void figure_worker::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    int progress = 0;
    building *bhome = home();
    building *b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    bool stop_at_road = true;
    auto &rd = runtime_data();

    if (!bhome || !bhome->is_valid()) {
        poof();
        return;
    }

    if (rd.delivering_block) {
        // Brick-delivery path tolerates a missing destination during return.
    } else if (!b_dest || !b_dest->is_valid()) {
        poof();
        return;
    }

    figure_id dest_fid = 0;
    if (b_dest && b_dest->is_floodplain_farm()) {
        terrain_usage = TERRAIN_USAGE_ROADS;
        dest_fid = b_dest->dcast_farm()->expected_worker_id();
    } else if (b_dest && b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        stop_at_road = false;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (base.action_state) {
    case ACTION_9_LABORER_GOING_OUT:
        if (rd.delivering_block) {
            break;
        }
        if (dest_fid && dest_fid != id()) {
            set_destination(home());
            advance_action(ACTION_13_LABORER_RETURNING);
        } else {
            advance_action(ACTION_10_LABORER_TO_FARM);
        }
        break;

    case ACTION_14_LABORER_ROUTE_LOST:
        poof();
        break;

    case ACTION_10_LABORER_TO_FARM:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage, ACTION_10_LABORER_TO_FARM, ACTION_14_LABORER_ROUTE_LOST)) {
            worker_handoff_path_to_camp(base);
            if (b_dest->is_floodplain_farm()) {
                auto &d = b_dest->dcast_farm()->runtime_data();
                b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                d.work_camp_id = bhome->id;
                d.worker_id = 0;
                d.labor_state = LABOR_STATE_JUST_ENTERED;
                d.labor_days_left = 96;
                poof();
            } else if (b_dest->is_monument()) {
                tile2i tile_need_leveling = monumen_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    advance_action(ACTION_13_LABORER_RETURNING);
                    return;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                base.destination_tile = tile_need_leveling;
                advance_action(ACTION_21_LABORER_TO_LEVEL_TILE);
            }
        }
        break;

    case ACTION_21_LABORER_TO_LEVEL_TILE:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_22_LABORER_LEVEL_WORK, ACTION_14_LABORER_ROUTE_LOST)) {
            base.wait_ticks = 0;
            base.direction = 0;
        }
        break;

    case ACTION_22_LABORER_LEVEL_WORK:
        progress = map_monuments_get_progress(tile());
        if (progress < 200) {
            auto monument = b_dest->dcast_monument();
            monument->set_tile_progress(tile(), progress + 1);
        } else {
            advance_action(ACTION_13_LABORER_RETURNING);
            if (home()) {
                set_destination(home());
            }
        }
        break;

    case ACTION_15_LABORER_TO_STORAGE_YARD:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ROADS, -1, ACTION_13_LABORER_RETURNING)) {
            // Prefer removing one load from a yard under the tile; tolerate missing stock.
            int yard_bid = map_building_at(base.destination_tile);
            building *yb = yard_bid ? building_get(yard_bid) : nullptr;
            if (auto *yard = storage_yard_cast(yb ? yb->main() : nullptr)) {
                int bricks = monument_engine_config.default_bricks_per_block;
                if (auto *mason = figure_get(rd.mason_fid)) {
                    if (auto *bl = mason->dcast_bricklayer()) {
                        building *dest = building_get(bl->runtime_data().destination_bid);
                        if (auto *mon = dest ? dest->dcast_monument() : nullptr) {
                            bricks = mon->phase_bricks_per_block(mon->phase());
                            if (bricks <= 0) {
                                bricks = monument_engine_config.default_bricks_per_block;
                            }
                        }
                    }
                }
                yard->remove_resource(RESOURCE_BRICKS, bricks);
            }
            figure *mason = figure_get(rd.mason_fid);
            if (mason && mason->is_alive()) {
                if (uses_ramp_climb(b_dest)) {
                    tile2i entry = ramp_entry_tile(b_dest);
                    base.destination_tile = entry.valid() ? entry : mason->tile;
                    // OG at_storage_yard: spawn 5 pullers + sled chained to this laborer.
                    pyramid_figure_spawn_sled_train(id(), b_dest);
                } else {
                    base.destination_tile = mason->tile;
                }
                advance_action(ACTION_17_LABORER_TO_PYRAMID);
            } else {
                set_destination(home());
                advance_action(ACTION_13_LABORER_RETURNING);
            }
        }
        break;

    case ACTION_17_LABORER_TO_PYRAMID: {
        const bool climb = rd.delivering_block && uses_ramp_climb(b_dest);
        // OG SLED_AT_RAMP: while still routed to the entry, yield if another laborer is equally near.
        if (climb && base.routing_path_id > 0 && !pyramid_laborer_can_enter_ramp(id())) {
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, -1, ACTION_13_LABORER_RETURNING)) {
            if (climb) {
                pyramid_laborer_pair_with_mason(id());
                pyramid_figure_start_climb(id());
                advance_action(ACTION_18_LABORER_CLIMB_RAMP);
            } else {
                advance_action(ACTION_29_LABORER_DELIVERED);
            }
        } else if (!climb) {
            figure *mason = figure_get(rd.mason_fid);
            if (mason && mason->is_alive()) {
                base.destination_tile = mason->tile;
            }
        }
        break;
    }

    case ACTION_18_LABORER_CLIMB_RAMP: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        figure_id mason_id = base.leading_figure_id ? (figure_id)base.leading_figure_id : rd.mason_fid;
        building_id mason_part = 0;
        if (figure *mason = figure_get(mason_id)) {
            mason_part = pyramid_figure_work_part_bid(mason);
            if (!mason_part) {
                mason_part = map_building_at(mason->tile);
            }
        }
        if (!mason_part || (!pyramid_engine_part_has_active_worker(mason_part) && !mastaba_engine_part_has_active_worker(mason_part))) {
            building *head = b_dest ? (b_dest->main() ? b_dest->main() : b_dest) : nullptr;
            figure_id new_mason = head
                ? g_monument_pyramid_figure.find_mason_waiting_for_block(head, 1)
                : 0;
            if (new_mason) {
                base.leading_figure_id = (int16_t)new_mason;
                rd.mason_fid = new_mason;
                if (figure *m = figure_get(new_mason)) {
                    m->leading_figure_id = (int16_t)id();
                }
            } else {
                auto *ms = head ? pyramid_main_state_get(head->id) : nullptr;
                if (ms && ms->remaining_blocks != 0) {
                    break;
                }
                rd.walk_mode = PYRAMID_WALK_NONE;
                set_destination(home());
                advance_action(ACTION_13_LABORER_RETURNING);
                break;
            }
        }
        pyramid_figure_walk_on_ramp(id(), 2, ACTION_13_LABORER_RETURNING, ACTION_19_LABORER_TO_MASON);
        if (action_state() == ACTION_13_LABORER_RETURNING) {
            rd.walk_mode = PYRAMID_WALK_NONE;
            set_destination(home());
        }
        break;
    }

    case ACTION_19_LABORER_TO_MASON: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        figure_id mason_id = base.leading_figure_id ? (figure_id)base.leading_figure_id : rd.mason_fid;
        figure *mason = figure_get(mason_id);
        building_id part_id = mason ? map_building_at(mason->tile) : 0;
        if (!part_id && mason) {
            part_id = pyramid_figure_work_part_bid(mason);
        }
        auto *work = pyramid_figure_work_data(&base);
        if (part_id && (b_dest->dcast_pyramid() || mastaba_engine_is(b_dest))) {
            pyramid_figure_set_walk_target(id(), part_id, work ? work->height : 0, false);
            advance_action(ACTION_20_LABORER_WALK_TO_MASON);
        } else {
            rd.walk_mode = PYRAMID_WALK_NONE;
            set_destination(home());
            advance_action(ACTION_13_LABORER_RETURNING);
        }
        break;
    }

    case ACTION_20_LABORER_WALK_TO_MASON: {
        base.terrain_usage = TERRAIN_USAGE_ANY;
        base.outside_road_ticks = 0;
        if (pyramid_figure_climb_step(id(), 1)) {
            figure_id mason_id = base.leading_figure_id ? (figure_id)base.leading_figure_id : rd.mason_fid;
            pyramid_engine_laborer_deliver_block(mason_id);
            mastaba_engine_laborer_deliver_block(mason_id);
            rd.delivering_block = 0;
            rd.mason_fid = 0;
            rd.walk_mode = PYRAMID_WALK_NONE;
            base.leading_figure_id = 0;
            set_destination(home());
            advance_action(ACTION_13_LABORER_RETURNING);
        }
        break;
    }

    case ACTION_29_LABORER_DELIVERED:
        // Mastaba and mudbrick bricklayers share wait-for-block wake.
        pyramid_engine_laborer_deliver_block(rd.mason_fid);
        mastaba_engine_laborer_deliver_block(rd.mason_fid);
        rd.delivering_block = 0;
        rd.mason_fid = 0;
        rd.walk_mode = PYRAMID_WALK_NONE;
        base.leading_figure_id = 0;
        set_destination(home());
        advance_action(ACTION_13_LABORER_RETURNING);
        break;

    case ACTION_13_LABORER_RETURNING:
        if (do_gotobuilding(destination() ? destination() : home(), stop_at_road, TERRAIN_USAGE_PREFER_ROADS,
                            ACTION_13_LABORER_RETURNING, ACTION_14_LABORER_ROUTE_LOST)) {
            worker_handoff_path_to_camp(base);
            poof();
        }
        break;
    }
}

void figure_worker::figure_before_action() {
    building *b = home();
    if (b->state != BUILDING_STATE_VALID || !b->has_figure(0, id())) {
        poof();
    }
}

void figure_worker::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_22_LABORER_LEVEL_WORK:
    case ACTION_29_LABORER_DELIVERED:
        image_set_animation(animkeys().work);
        break;

    case ACTION_13_LABORER_RETURNING:
    case ACTION_15_LABORER_TO_STORAGE_YARD:
    case ACTION_17_LABORER_TO_PYRAMID:
    case ACTION_18_LABORER_CLIMB_RAMP:
    case ACTION_19_LABORER_TO_MASON:
    case ACTION_20_LABORER_WALK_TO_MASON:
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_worker::on_destroy() {
    if (destination() && destination()->id) {
        if (auto *b = destination()->dcast()) {
            b->remove_worker(id());
        }
    }
}

void figure_worker::poof() {
    figure_impl::poof();
}
