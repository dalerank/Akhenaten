#include "figure_worker.h"

#include "building/monument_mastaba.h"
#include "building/monument_sun_temple.h"
#include "building/building_farm.h"
#include "graphics/image_groups.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "city/city_recorded_paths.h"
#include "city/ratings.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_worker);

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

    // Sun Temple: body-only leveling. map_grid_get_tiles(b,0) walks linked parts by
    // size² and would send laborers onto the 3×3 hall (path is size=1 so only its origin).
    grid_tiles tiles;
    if (b->dcast_sun_temple()) {
        building *main = b->main();
        const int body = main->size > 0 ? main->size : 10;
        tiles = map_grid_get_tiles(main->tile, main->tile.shifted(body - 1, body - 1));
    } else {
        tiles = map_grid_get_tiles(b, 0);
    }
    tile2i tile = map_grid_area_first(tiles, [&mastaba] (tile2i tile) {
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

void figure_worker::figure_action() {
    base.use_cross_country = false;
    base.max_roam_length = 384;
    int progress = 0;
    building* bhome = home();
    building* b_dest = destination();
    e_terrain_usage terrain_usage = TERRAIN_USAGE_ROADS;
    bool stop_at_road = true;
    if (!bhome->is_valid() || !b_dest->is_valid()) {
        poof();
        return;
    }

    figure_id dest_fid = 0;
    if (b_dest->is_floodplain_farm()) {       
        terrain_usage = TERRAIN_USAGE_ROADS;
        dest_fid = b_dest->dcast_farm()->expected_worker_id();
    } else if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        stop_at_road = false;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (base.action_state) {
    case ACTION_9_WORKER_CREATED:
    case ACTION_14_WORKER_CHECK_DESTINATION:        
        if (dest_fid && dest_fid != id()) {
            set_destination(home());
            advance_action(ACTION_13_WORKER_BACK_FROM_WORKS);
        } else {
            advance_action(ACTION_10_WORKER_GOING);
        }
        break;

    case ACTION_15_REACHED_DESTINATION:
        if (dest_fid && dest_fid == id()) {
            poof();
        } else {
            advance_action(ACTION_13_WORKER_BACK_FROM_WORKS);
        }
        break;

    case ACTION_10_WORKER_GOING:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage, ACTION_15_REACHED_DESTINATION, ACTION_14_WORKER_CHECK_DESTINATION)) {
            worker_handoff_path_to_camp(base);
            if (b_dest->is_floodplain_farm()) {
                auto &d = b_dest->dcast_farm()->runtime_data();
                b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                d.work_camp_id = bhome->id;
                d.worker_id = 0;
                d.labor_state = LABOR_STATE_JUST_ENTERED;
                d.labor_days_left = 96;
            } else if (b_dest->is_monument()) {
                tile2i tile_need_leveling = monumen_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    advance_action(ACTION_13_WORKER_BACK_FROM_WORKS);
                    return;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                base.destination_tile = tile_need_leveling;
                advance_action(ACTION_11_WORKER_GOING_TO_PLACE);
            }
        }
        break;

    case ACTION_11_WORKER_GOING_TO_PLACE:
        if (do_goto(base.destination_tile, TERRAIN_USAGE_ANY, ACTION_15_REACHED_DESTINATION, ACTION_14_WORKER_CHECK_DESTINATION)) {
            base.wait_ticks = 0;
            base.direction = 0;
            advance_action(ACTION_12_WORKER_LEVELING_GROUND);
        }
        break;

    case ACTION_12_WORKER_LEVELING_GROUND:
        progress = map_monuments_get_progress(tile());
        if (progress < 200) {
            auto monument = b_dest->dcast_monument();
            monument->set_tile_progress(tile(), progress + 1);
        } else {
            advance_action(ACTION_13_WORKER_BACK_FROM_WORKS);
            if (home()) {
                set_destination(home());
            }
        }
        break;

    case ACTION_13_WORKER_BACK_FROM_WORKS:
        if (do_gotobuilding(destination(), stop_at_road, TERRAIN_USAGE_PREFER_ROADS, ACTION_15_REACHED_DESTINATION, ACTION_14_WORKER_CHECK_DESTINATION)) {
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
    case ACTION_12_WORKER_LEVELING_GROUND:
        image_set_animation(animkeys().work);
        break;

    case ACTION_13_WORKER_BACK_FROM_WORKS:
        image_set_animation(animkeys().walk);
        break;
    }
}

void figure_worker::on_destroy() {
    building_impl *b = destination()->dcast();
    if (b) {
        b->remove_worker(id());
    }
}

void figure_worker::poof() {
    figure_impl::poof();
}