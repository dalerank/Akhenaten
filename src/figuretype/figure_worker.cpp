#include "figure_worker.h"

#include "building/monument_mastaba.h"
#include "building/building_farm.h"
#include "figure/image.h"
#include "graphics/image_groups.h"
#include "city/city.h"
#include "city/city_floods.h"
#include "city/city_health.h"
#include "city/city_labor.h"
#include "city/ratings.h"
#include "js/js_game.h"

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_worker);

auto any_mastaba_types = make_array(
    BUILDING_SMALL_MASTABA, BUILDING_SMALL_MASTABA_SIDE, BUILDING_SMALL_MASTABA_WALL, BUILDING_SMALL_MASTABA_ENTRANCE,
    BUILDING_MEDIUM_MASTABA, BUILDING_MEDIUM_MASTABA_SIDE, BUILDING_MEDIUM_MASTABA_WALL, BUILDING_MEDIUM_MASTABA_ENTRANCE
);

tile2i figure_worker::mastaba_tile4work(building *b) {
    building_mastaba *mastaba = b->dcast_mastaba();
    if (!mastaba) {
        return tile2i{-1, -1};
    }

    auto &d = mastaba->runtime_data();
    if (d.phase >= 2) {
        return tile2i{-1, -1};
    }

    grid_tiles tiles = map_grid_get_tiles(b, 0);
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

    if (building_is_floodplain_farm(*b_dest)) {
        auto &d = b_dest->dcast_farm()->runtime_data();
        if (d.worker_id != id()) {
            poof();
            return;
        }

        terrain_usage = TERRAIN_USAGE_ROADS;
    } else if (b_dest->is_monument()) {
        terrain_usage = TERRAIN_USAGE_PREFER_ROADS;
        stop_at_road = false;
    } else {
        terrain_usage = TERRAIN_USAGE_ROADS;
    }

    switch (base.action_state) {
    case 9:
        break;

    case ACTION_10_WORKER_GOING:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage)) {
            if (building_is_floodplain_farm(*b_dest)) {
                auto &d = b_dest->dcast_farm()->runtime_data();
                b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                d.work_camp_id = bhome->id;
                d.worker_id = 0;
                d.labor_state = LABOR_STATE_JUST_ENTERED;
                d.labor_days_left = 96;
            } else if (b_dest->type == BUILDING_PYRAMID) {
                // todo: MONUMENTSSSS
            } else if (building_type_any_of(b_dest->type, any_mastaba_types)) {
                tile2i tile_need_leveling = mastaba_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    poof();
                    return;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                base.destination_tile = tile_need_leveling;
                advance_action(ACTION_11_WORKER_GOING_TO_PLACE);
            }
        }
        break;

    case ACTION_11_WORKER_GOING_TO_PLACE:
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            base.direction = 0;
            advance_action(ACTION_12_WORKER_LEVELING_GROUND);
        }
        break;

    case ACTION_12_WORKER_LEVELING_GROUND:
        progress = map_monuments_get_progress(tile());
        if (progress < 200) {
            map_monuments_set_progress(tile(), progress + 1);
        } else {
            advance_action(ACTION_13_WORKER_BACK_FROM_WORKS);
            if (home()) {
                set_destination(home());
            }
        }
        break;

    case ACTION_13_WORKER_BACK_FROM_WORKS:
        if (do_gotobuilding(destination(), stop_at_road, TERRAIN_USAGE_PREFER_ROADS)) {
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

void figure_worker::poof() {
    figure_impl::poof();

    building_impl *b = destination()->dcast();

    if (b) {
        b->remove_worker(id());
    }
}

sound_key figure_worker::phrase_key() const {
    int enemies = g_city.figures.enemies;
    if (enemies > 10) {
        return "enemies_in_city";
    }

    svector<sound_key, 10> keys;
    if (base.action_state == ACTION_10_GOING) {
        keys.push_back("going_to_workplace");
    }

    if (!g_floods.state_is(FLOOD_STATE_FARMABLE)) {
        keys.push_back("farm_is_flooded");
    }

    if (g_city.health.value < 30) {
        keys.push_back("desease_can_start_at_any_moment");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_FOOD) {
        keys.push_back("no_food_in_city");
    }

    if (g_city.labor.workers_needed >= 10) {
        keys.push_back("need_workers");
    }

    if (g_city.religion.least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("gods_are_angry");
    }

    if (g_city.kingdome.rating < 30) {
        keys.push_back("city_is_bad");
    }

    if (g_city.sentiment.low_mood_cause == LOW_MOOD_NO_JOBS) {
        keys.push_back("much_unemployments");
    }

    if (g_city.festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("low_entertainment");
    }

    const int sentiment = g_city.sentiment.value;
    if (sentiment > 50) {
        keys.push_back("city_is_good");
    }

    if (sentiment > 90) {
        keys.push_back("city_is_amazing");
    }

    int index = rand() % keys.size();
    return xstring().printf( "worker_", keys[index].c_str());
}

figure_sound_t figure_worker::get_sound_reaction(pcstr key) const {
    return current_params().sounds[key];
}