#include "figure_worker.h"

#include "building/building.h"
#include "building/building_farm.h"
#include "building/building_storage_yard.h"
#include "building/monument_mastaba.h"
#include "grid/building.h"
#include "grid/point.h"
#include "grid/road_access.h"
#include "building/monument_mastaba_engine.h"
#include "building/monument_pyramid_engine.h"
#include "building/monument_pyramid_figure.h"
#include "building/monument_sun_temple.h"
#include "building/monuments.h"
#include "figuretype/figure_bricklayer.h"
#include "figuretype/figure_sled.h"
#include "figuretype/figure_stonemason.h"
#include "building/building_impl.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "city/city_figures.h"
#include "city/city_floods.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "city/city_recorded_paths.h"
#include "city/city_resource.h"
#include "city/ratings.h"
#include "core/calc.h"
#include "game/game_config.h"
#include "graphics/image_groups.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_worker);

void figure_worker::static_params::archive_init() {
    verify_no_crash(load > 0);
    verify_no_crash(yard_wait_ticks > 0);
    verify_no_crash(delivered_wait_ticks > 0);
    verify_no_crash(max_roam_ticks > 0);
    verify_no_crash(max_out > 0);
    verify_no_crash(farm_labor_days > 0);
    verify_no_crash(level_tiles_in_a_row > 0);
}

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

namespace {

building_id laborer_yard_for_getting(building *near, e_resource resource, int min_amount, tile2i &dst) {
    dst = tile2i::invalid;
    if (!near || resource == RESOURCE_NONE || min_amount <= 0) {
        return 0;
    }
    if (g_city.resource.is_stockpiled(resource)) {
        return 0;
    }

    int best_distance = 10000;
    building_id best_id = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building_storage_yard *yard = building_get(i)->dcast_storage_yard();
        if (!yard || !yard->is_valid()) {
            continue;
        }
        if (yard->stored_amount(resource) < min_amount) {
            continue;
        }
        int dist = calc_distance_with_penalty(yard->tile(), near->tile, near->distance_from_entry,
                                              yard->base.distance_from_entry);
        if (dist < best_distance) {
            best_distance = dist;
            best_id = yard->id();
        }
    }
    if (!best_id) {
        return 0;
    }

    building *yard_b = building_get(best_id);
    if (yard_b->road_access.valid()) {
        dst = yard_b->road_access;
    } else if (yard_b->has_road_access == 1) {
        map_point_store_result(yard_b->tile, dst);
    } else {
        dst = map_has_road_access_rotation(yard_b->orientation, yard_b->tile, 3);
        if (!dst.valid()) {
            return 0;
        }
    }
    return best_id;
}

bool laborer_take_yard_load(building_storage_yard *yard, e_resource resource, int load, figure &f) {
    f.resource_amount_full = 0;
    if (!yard || resource == RESOURCE_NONE || load <= 0) {
        return false;
    }
    const int missing = yard->remove_resource(resource, load);
    if (missing == load) {
        return false;
    }
    if (missing == 0) {
        f.resource_amount_full = (uint16_t)load;
        f.resource_id = resource;
        return true;
    }
    yard->add_resource(resource, load - missing, true);
    return false;
}

building_id laborer_partner_part(figure_id laborer_fid, figure_id mason_fid) {
    figure *mason = figure_get(mason_fid);
    if (!mason || !mason->is_alive()) {
        return 0;
    }
    if (mason->leading_figure_id != laborer_fid) {
        return 0;
    }
    if (auto *bl = mason->dcast_bricklayer()) {
        if (bl->runtime_data().destination_bid) {
            return bl->runtime_data().destination_bid;
        }
    }
    if (auto *sm = mason->dcast_stonemason()) {
        if (sm->runtime_data().destination_bid) {
            return sm->runtime_data().destination_bid;
        }
    }
    building_id part = pyramid_figure_work_part_bid(mason);
    if (part) {
        return part;
    }
    return map_building_at(mason->tile);
}

} // namespace

e_resource figure_worker::block_material_for(building *monument, figure_id mason_fid) const {
    building *head = monument ? (monument->main() ? monument->main() : monument) : nullptr;
    if (!head) {
        return RESOURCE_BRICKS;
    }

    e_pyramid_style style = g_monument_pyramid_engine.style_of(head);
    if (mastaba_engine_is(head)) {
        style = PYRAMID_STYLE_MASTABA;
    }

    building_id part_id = 0;
    if (figure *mason = figure_get(mason_fid)) {
        part_id = pyramid_figure_work_part_bid(mason);
        if (!part_id) {
            part_id = map_building_at(mason->tile);
        }
    }

    bool needs_main = true;
    if (auto *ps = pyramid_part_state_get(part_id)) {
        needs_main = g_monument_pyramid_engine.needs_main_material(*ps, style);
    }

    const bool mudbrick = style == PYRAMID_STYLE_MUDBRICK || style == PYRAMID_STYLE_MASTABA;
    if (needs_main) {
        return mudbrick ? RESOURCE_BRICKS : RESOURCE_STONE;
    }
    if (style == PYRAMID_STYLE_STEPPED) {
        return RESOURCE_STONE;
    }
    if (style == PYRAMID_STYLE_MASTABA) {
        return RESOURCE_BRICKS;
    }
    return RESOURCE_LIMESTONE;
}

void figure_worker::enter_idle_pool() {
    auto &rd = runtime_data();
    rd.delivering_block = 0;
    rd.mason_fid = 0;
    rd.walk_mode = PYRAMID_WALK_NONE;
    rd.level_tiles_done = 0;
    rd.yard_bid = 0;
    base.leading_figure_id = 0;
    base.resource_amount_full = 0;
    base.collecting_item_id = RESOURCE_NONE;
    base.resource_id = RESOURCE_NONE;
    base.wait_ticks = 0;
    base.animctx.frame = 0;
    base.set_flag(e_figure_flag_invisible, true);
    advance_action(ACTION_8_LABORER_IDLE);
}

void figure_worker::finish_block_delivery() {
    auto &rd = runtime_data();
    pyramid_engine_laborer_deliver_block(rd.mason_fid);
    mastaba_engine_laborer_deliver_block(rd.mason_fid);
    rd.delivering_block = 0;
    rd.mason_fid = 0;
    rd.walk_mode = PYRAMID_WALK_NONE;
    rd.yard_bid = 0;
    base.leading_figure_id = 0;
    base.resource_amount_full = 0;
    base.collecting_item_id = RESOURCE_NONE;
    base.resource_id = RESOURCE_NONE;
    base.wait_ticks = 0;
    advance_action(ACTION_29_LABORER_DELIVERED);
}

bool figure_worker::assign_block_delivery(building *monument, figure_id mason_fid) {
    building *head = monument ? (monument->main() ? monument->main() : monument) : nullptr;
    if (!head || !mason_fid) {
        return false;
    }

    const e_resource resource = block_material_for(head, mason_fid);
    const int load = (int)current_params().load;
    tile2i yard_tile;
    building_id yard_id = laborer_yard_for_getting(head, resource, load, yard_tile);
    if (!yard_id || !yard_tile.valid()) {
        return false;
    }

    auto &rd = runtime_data();
    rd.mason_fid = mason_fid;
    rd.delivering_block = 1;
    rd.walk_mode = PYRAMID_WALK_NONE;
    rd.yard_bid = yard_id;
    set_destination(head);
    base.wait_ticks = 0;
    base.resource_amount_full = 0;
    base.collecting_item_id = (uint8_t)resource;
    base.resource_id = resource;
    base.leading_figure_id = (int16_t)mason_fid;
    if (figure *mason = figure_get(mason_fid)) {
        mason->leading_figure_id = (int16_t)id();
    }
    base.destination_tile = yard_tile;
    base.set_flag(e_figure_flag_invisible, false);
    advance_action(ACTION_15_LABORER_TO_STORAGE_YARD);
    return true;
}

bool figure_worker::assign_farm_task(building *farm) {
    if (!farm || !farm->is_valid()) {
        return false;
    }
    const int radius = (int)current_params().home_road_radius;
    tile2i road = map_closest_road_within_radius(farm->tile, farm->size, radius);
    if (!road.valid()) {
        return false;
    }
    if (auto *impl = farm->dcast()) {
        impl->add_workers(id());
    }
    set_destination(farm);
    base.destination_tile = road;
    base.roam_length = 0;
    base.set_flag(e_figure_flag_invisible, false);
    advance_action(ACTION_10_LABORER_TO_FARM);
    return true;
}

bool figure_worker::assign_monument_task(building *monument, figure_id mason_fid) {
    if (!monument || !monument->is_valid()) {
        return false;
    }
    building *head = monument->main() ? monument->main() : monument;
    auto *mon = head->dcast_monument();
    if (!mon) {
        return false;
    }

    if (mason_fid) {
        return assign_block_delivery(head, mason_fid);
    }

    tile2i level_tile = monumen_tile4work(head);
    if (level_tile == tile2i{-1, -1}) {
        return false;
    }
    mon->add_workers(id());
    map_monuments_set_progress(level_tile, 1);
    set_destination(head);
    base.destination_tile = level_tile;
    base.roam_length = 0;
    runtime_data().level_tiles_done = 0;
    base.set_flag(e_figure_flag_invisible, false);
    advance_action(ACTION_21_LABORER_TO_LEVEL_TILE);
    return true;
}

void figure_worker::find_work() {
    const auto &p = current_params();
    building *best = nullptr;
    figure_id best_mason = 0;
    int best_distance = 0x7fffffff;

    if (g_floods.state_is(FLOOD_STATE_FARMABLE)) {
        for (auto &b : city_buildings()) {
            if (!b.is_valid() || !b.is_floodplain_farm()) {
                continue;
            }
            if (!b.has_road_access || b.distance_from_entry == 0) {
                continue;
            }
            if (b.state == BUILDING_STATE_MOTHBALLED) {
                continue;
            }
            auto *farm = b.dcast_farm();
            if (!farm || !farm->requested_workers()) {
                continue;
            }
            int distance = calc_maximum_distance(tile(), b.tile);
            if (distance > (int)p.farm_search_distance) {
                continue;
            }
            distance += farm->runtime_data().labor_days_left;
            if (distance >= best_distance) {
                continue;
            }
            best_distance = distance;
            best = &b;
            best_mason = 0;
        }
    }

    if (!best) {
        best_distance = 0x7fffffff;
        for (auto &b : city_buildings()) {
            if (!b.is_valid() || !b.is_monument() || !b.is_main()) {
                continue;
            }
            if (!b.dcast_pyramid() && !mastaba_engine_is(&b)) {
                continue;
            }
            auto *mon = b.dcast_monument();
            if (!mon || mon->is_finished()) {
                continue;
            }

            figure_id mason_id = 0;
            bool has_work = false;
            if (mon->phase() < 2) {
                if (mon->need_workers() && monumen_tile4work(&b) != tile2i{-1, -1}) {
                    has_work = true;
                }
            } else {
                mason_id = g_monument_pyramid_figure.find_mason_waiting_for_block(&b, 0);
                has_work = mason_id != 0;
            }
            if (!has_work) {
                continue;
            }

            int distance = calc_maximum_distance(tile(), b.tile);
            if (distance >= best_distance) {
                continue;
            }
            best_distance = distance;
            best = &b;
            best_mason = mason_id;
        }
    }

    if (!best) {
        poof();
        return;
    }

    if (best->is_floodplain_farm()) {
        if (!assign_farm_task(best)) {
            poof();
        }
        return;
    }

    if (!assign_monument_task(best, best_mason)) {
        poof();
    }
}

void figure_worker::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = (int)current_params().max_roam_ticks;
    int progress = 0;
    building *bhome = home();
    building *b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    bool stop_at_road = true;
    auto &rd = runtime_data();
    const int action = base.action_state;

    if (!bhome || !bhome->is_valid()) {
        poof();
        return;
    }

    // IDLE / GOING_OUT have no work destination yet; brick delivery may briefly lack one.
    if (action != ACTION_8_LABORER_IDLE && action != ACTION_9_LABORER_GOING_OUT && !rd.delivering_block) {
        if (!b_dest || !b_dest->is_valid()) {
            poof();
            return;
        }
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
    case ACTION_8_LABORER_IDLE: {
        base.set_flag(e_figure_flag_invisible, true);
        base.leading_figure_id = 0;
        base.animctx.frame = 0;
        base.wait_ticks--;
        if (base.wait_ticks > 0) {
            break;
        }
        const int radius = (int)current_params().home_road_radius;
        tile2i road = map_closest_road_within_radius(bhome->tile, bhome->size, radius);
        if (!road.valid()) {
            poof();
            break;
        }
        advance_action(ACTION_9_LABORER_GOING_OUT);
        base.set_cross_country_destination(road);
        base.roam_length = 0;
        break;
    }

    case ACTION_9_LABORER_GOING_OUT:
        if (rd.delivering_block) {
            break;
        }
        // Enhanced destination-at-spawn: destination already assigned → go work.
        if (b_dest && b_dest->is_valid() && b_dest != bhome
            && (b_dest->is_floodplain_farm() || b_dest->is_monument())) {
            base.set_flag(e_figure_flag_invisible, false);
            if (dest_fid && dest_fid != id()) {
                set_destination(home());
                advance_action(ACTION_13_LABORER_RETURNING);
            } else {
                advance_action(ACTION_10_LABORER_TO_FARM);
            }
            break;
        }
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, true);
        if (base.move_ticks_cross_country(1)) {
            find_work();
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
                if (game_features::gameplay_change_work_camp_distance_scaled_farm_workers.to_bool()) {
                    b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                } else {
                    // OG: full model laborers for the farm type.
                    b_dest->num_workers = b_dest->max_workers;
                }
                d.work_camp_id = bhome->id;
                d.worker_id = 0;
                d.labor_state = LABOR_STATE_JUST_ENTERED;
                d.labor_days_left = current_params().farm_labor_days;
                poof();
            } else if (b_dest->is_monument()) {
                // Enhanced destination-at-spawn may still arrive via TO_FARM.
                tile2i tile_need_leveling = monumen_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    enter_idle_pool();
                    break;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                base.destination_tile = tile_need_leveling;
                rd.level_tiles_done = 0;
                advance_action(ACTION_21_LABORER_TO_LEVEL_TILE);
            }
        }
        break;

    case ACTION_21_LABORER_TO_LEVEL_TILE:
        base.use_cross_country = true;
        base.set_flag(e_figure_flag_invisible, false);
        if (!base.destination_tile.valid()) {
            enter_idle_pool();
            break;
        }
        base.set_cross_country_destination(base.destination_tile);
        if (base.move_ticks_cross_country(1)) {
            advance_action(ACTION_22_LABORER_LEVEL_WORK);
            base.wait_ticks = 0;
            base.direction = 0;
        }
        break;

    case ACTION_22_LABORER_LEVEL_WORK:
        progress = map_monuments_get_progress(tile());
        if (progress < 200) {
            if (auto *monument = b_dest ? b_dest->dcast_monument() : nullptr) {
                monument->set_tile_progress(tile(), progress + 1);
            } else {
                map_monuments_set_progress(tile(), progress + 1);
            }
            break;
        }
        rd.level_tiles_done++;
        if (rd.level_tiles_done >= current_params().level_tiles_in_a_row) {
            enter_idle_pool();
            break;
        }
        if (b_dest && b_dest->is_monument()) {
            tile2i next = monumen_tile4work(b_dest);
            if (next != tile2i{-1, -1}) {
                map_monuments_set_progress(next, 1);
                base.destination_tile = next;
                advance_action(ACTION_21_LABORER_TO_LEVEL_TILE);
                break;
            }
        }
        enter_idle_pool();
        break;

    case ACTION_15_LABORER_TO_STORAGE_YARD:
        base.set_flag(e_figure_flag_invisible, false);
        if (!laborer_partner_part(id(), rd.mason_fid)) {
            poof();
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_PREFER_ROADS, -1, ACTION_14_LABORER_ROUTE_LOST)) {
            base.wait_ticks = 0;
            advance_action(ACTION_16_LABORER_AT_STORAGE_YARD);
        }
        break;

    case ACTION_16_LABORER_AT_STORAGE_YARD: {
        base.set_flag(e_figure_flag_invisible, false);
        figure *mason = figure_get(rd.mason_fid);
        building_id part_id = laborer_partner_part(id(), rd.mason_fid);
        if (!mason || !part_id) {
            poof();
            break;
        }
        const bool mason_active = pyramid_engine_part_has_active_worker(part_id)
            || mastaba_engine_part_has_active_worker(part_id);
        if (!mason_active) {
            poof();
            break;
        }

        base.wait_ticks++;
        if (base.wait_ticks <= (int)current_params().yard_wait_ticks) {
            base.animctx.frame = 0;
            break;
        }

        building *yb = rd.yard_bid ? building_get(rd.yard_bid) : nullptr;
        if (!yb) {
            int at_tile = map_building_at(base.destination_tile);
            yb = at_tile ? building_get(at_tile) : nullptr;
        }
        auto *yard = storage_yard_cast(yb ? yb->main() : nullptr);
        const e_resource resource = (e_resource)base.collecting_item_id;
        const int load = (int)current_params().load;
        if (!laborer_take_yard_load(yard, resource, load, base)) {
            enter_idle_pool();
            break;
        }

        if (uses_ramp_climb(b_dest)) {
            tile2i entry = ramp_entry_tile(b_dest);
            base.destination_tile = entry.valid() ? entry : mason->tile;
            pyramid_figure_spawn_sled_train(id(), b_dest);
        } else {
            base.destination_tile = mason->tile;
        }
        base.wait_ticks = 0;
        advance_action(ACTION_17_LABORER_TO_PYRAMID);
        break;
    }

    case ACTION_17_LABORER_TO_PYRAMID: {
        const bool climb = rd.delivering_block && uses_ramp_climb(b_dest);
        // OG SLED_AT_RAMP: while still routed to the entry, yield if another laborer is equally near.
        if (climb && base.routing_path_id > 0 && !pyramid_laborer_can_enter_ramp(id())) {
            break;
        }
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, -1, ACTION_14_LABORER_ROUTE_LOST)) {
            if (climb) {
                pyramid_laborer_pair_with_mason(id());
                pyramid_figure_start_climb(id());
                advance_action(ACTION_18_LABORER_CLIMB_RAMP);
            } else if (rd.mason_fid) {
                finish_block_delivery();
            } else {
                enter_idle_pool();
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
            if (!rd.mason_fid && base.leading_figure_id) {
                rd.mason_fid = (figure_id)base.leading_figure_id;
            }
            finish_block_delivery();
        }
        break;
    }

    case ACTION_29_LABORER_DELIVERED:
        // OG: wait delivered_wait_ticks then reuse IDLE pool (no return/poof).
        base.wait_ticks++;
        if (base.wait_ticks > (int)current_params().delivered_wait_ticks) {
            enter_idle_pool();
        }
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
    // OG: laborers keep working while the home work camp is valid (not tied to a single figure slot).
    if (!b || b->state != BUILDING_STATE_VALID || b->type != BUILDING_WORK_CAMP) {
        poof();
    }
}

namespace {

int count_camp_laborers(building_id camp_id) {
    int n = 0;
    for (figure *f : map_figures()) {
        if (!f || !f->is_alive() || f->type != FIGURE_LABORER) {
            continue;
        }
        if (f->home_building_id == camp_id) {
            n++;
        }
    }
    return n;
}

int og_spawn_delay_for_pct(int pct) {
    const auto &p = figure_worker::current_params();
    if (pct >= 100) {
        return p.spawn_delay_full;
    }
    if (pct >= 75) {
        return p.spawn_delay_75_percent;
    }
    if (pct >= 50) {
        return p.spawn_delay_50_percent;
    }
    if (pct >= 25) {
        return p.spawn_delay_25_percent;
    }
    if (pct >= 1) {
        return p.spawn_delay_low;
    }
    return -1;
}

} // namespace

// OG building_work_camp_spawn_figure: IDLE laborer, max_out, staffing delay.
static int __work_camp_spawn_laborer_og(int bid) {
    building *b = building_get(bid);
    if (!b || !b->is_valid() || b->type != BUILDING_WORK_CAMP) {
        return 0;
    }
    auto *impl = b->dcast();
    if (!impl) {
        return 0;
    }

    impl->check_labor_problem();
    if (!impl->has_road_access()) {
        return 0;
    }

    const auto &p = figure_worker::current_params();
    if (b->houses_covered <= (int)p.labor_seeker_houses) {
        impl->common_spawn_labor_seeker((int)p.labor_seeker_houses);
    }

    if (game_features::gameplay_change_work_camp_one_worker_per_month.to_bool()
        && b->spawned_worker_this_month) {
        return 0;
    }

    const int pct = impl->worker_percentage();
    const int delay = og_spawn_delay_for_pct(pct);
    if (delay < 0) {
        return 0;
    }
    if (count_camp_laborers(bid) >= (int)p.max_out) {
        return 0;
    }

    b->figure_spawn_delay++;
    if (b->figure_spawn_delay <= delay) {
        return 0;
    }
    b->figure_spawn_delay = 0;

    tile2i spawn_tile = b->road_access.valid() ? b->road_access : b->tile;
    figure *f = figure_create(FIGURE_LABORER, spawn_tile, DIR_0_TOP_RIGHT);
    if (!f) {
        return 0;
    }
    f->action_state = ACTION_8_LABORER_IDLE;
    f->set_home(bid);
    if (!b->has_figure(BUILDING_SLOT_SERVICE)) {
        b->set_figure(BUILDING_SLOT_SERVICE, f);
    }
    b->spawned_worker_this_month = 1;
    return f->id;
}
ANK_FUNCTION_1(__work_camp_spawn_laborer_og)

void figure_worker::update_animation() {
    figure_impl::update_animation();

    switch (action_state()) {
    case ACTION_22_LABORER_LEVEL_WORK:
        image_set_animation(animkeys().work);
        break;

    case ACTION_15_LABORER_TO_STORAGE_YARD:
    case ACTION_16_LABORER_AT_STORAGE_YARD:
    case ACTION_17_LABORER_TO_PYRAMID:
    case ACTION_18_LABORER_CLIMB_RAMP:
    case ACTION_19_LABORER_TO_MASON:
    case ACTION_20_LABORER_WALK_TO_MASON:
    case ACTION_29_LABORER_DELIVERED:
    case ACTION_30_LABORER_SLED_AT_RAMP:
        image_set_animation(animkeys().pulling);
        break;

    case ACTION_8_LABORER_IDLE:
    case ACTION_13_LABORER_RETURNING:
    case ACTION_9_LABORER_GOING_OUT:
    case ACTION_10_LABORER_TO_FARM:
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
