#include "figure_worker.h"

#include "building/monument_mastaba.h"
#include "figure/image.h"
#include "graphics/image_groups.h"
#include "city/sentiment.h"
#include "city/figures.h"
#include "city/floods.h"
#include "city/health.h"
#include "city/labor.h"
#include "city/sentiment.h"
#include "city/gods.h"
#include "city/ratings.h"
#include "city/data_private.h"

#include "js/js_game.h"

struct worker_model : public figures::model_t<FIGURE_LABORER, figure_worker> {};
worker_model worker_m;

ANK_REGISTER_CONFIG_ITERATOR(config_load_figure_worker);
void config_load_figure_worker() {
    g_config_arch.r_section("figure_worker", [] (archive arch) {
        worker_m.anim.load(arch);
    });
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

    if (b_dest->is_industry()) {
        if (b_dest->data.industry.worker_id != id()) {
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

    case FIGURE_ACTION_10_WORKER_GOING:
        if (do_gotobuilding(destination(), stop_at_road, terrain_usage)) {
            if (building_is_farm(b_dest->type)) {
                b_dest->num_workers = std::clamp<int>((1.f - bhome->tile.dist(b_dest->tile) / 20.f) * 12, 2, 10);
                b_dest->data.industry.work_camp_id = bhome->id;
                b_dest->data.industry.worker_id = 0;
                b_dest->data.industry.labor_state = LABOR_STATE_JUST_ENTERED;
                b_dest->data.industry.labor_days_left = 96;
            } else if (b_dest->type == BUILDING_PYRAMID) {
                // todo: MONUMENTSSSS
            } else if (building_type_any_of(b_dest->type, BUILDING_SMALL_MASTABA, BUILDING_SMALL_MASTABA_SIDE, BUILDING_SMALL_MASTABA_WALL, BUILDING_SMALL_MASTABA_ENTRANCE)) {
                tile2i tile_need_leveling = building_small_mastaba_tile4work(b_dest);
                if (tile_need_leveling == tile2i{-1, -1}) {
                    poof();
                    return;
                }
                map_monuments_set_progress(tile_need_leveling, 1);
                base.destination_tile = tile_need_leveling;
                advance_action(FIGURE_ACTION_11_WORKER_GOING_TO_PLACE);
            }
        }
        break;

    case FIGURE_ACTION_11_WORKER_GOING_TO_PLACE:
        if (do_goto(base.destination_tile, false, TERRAIN_USAGE_ANY)) {
            base.wait_ticks = 0;
            base.direction = 0;
            advance_action(FIGURE_ACTION_12_WORKER_LEVELING_GROUND);
        }
        break;

    case FIGURE_ACTION_12_WORKER_LEVELING_GROUND:
        progress = map_monuments_get_progress(tile());
        if (progress < 200) {
            map_monuments_set_progress(tile(), progress + 1);
        } else {
            advance_action(FIGURE_ACTION_13_WORKER_BACK_FROM_WORKS);
            if (home()) {
                set_destination(home());
            }
        }
        break;

    case FIGURE_ACTION_13_WORKER_BACK_FROM_WORKS:
        if (do_gotobuilding(destination(), stop_at_road, TERRAIN_USAGE_PREFER_ROADS)) {
            poof();
        }
        break;
    }

    switch (base.action_state) {
    case FIGURE_ACTION_12_WORKER_LEVELING_GROUND:
        image_set_animation(worker_m.anim["work"]);
        break;
    }
}

void figure_worker::poof() {
    figure_impl::poof();

    building *b = destination();
    if (b && b->is_industry()) {
        b->industry_remove_worker(id());
    } else if (b && b->is_monument()) {
        b->monument_remove_worker(id());
    }
}

sound_key figure_worker::phrase_key() const {
    int enemies = city_figures_enemies();
    if (enemies > 10) {
        return "worker_enemies_in_city";
    }

    svector<sound_key, 10> keys;
    if (base.action_state == ACTION_10_GOING) {
        keys.push_back("worker_going_to_workplace");
    }

    if (!floodplains_is(FLOOD_STATE_FARMABLE)) {
        keys.push_back("worker_farm_is_flooded");
    }

    if (city_health() < 30) {
        keys.push_back("worker_desease_can_start_at_any_moment");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_FOOD) {
        keys.push_back("worker_no_food_in_city");
    }

    if (city_labor_workers_needed() >= 10) {
        keys.push_back("worker_need_workers");
    }

    if (city_gods_least_mood() <= GOD_MOOD_INDIFIRENT) { // any gods in wrath
        keys.push_back("worker_gods_are_angry");
    }

    if (city_rating_kingdom() < 30) {
        keys.push_back("worker_city_is_bad");
    }

    if (city_sentiment_low_mood_cause() == LOW_MOOD_NO_JOBS) {
        keys.push_back("worker_much_unemployments");
    }

    if (city_data_struct()->festival.months_since_festival > 6) {  // low entertainment
        keys.push_back("worker_low_entertainment");
    }

    if (city_sentiment() > 50) {
        keys.push_back("worker_city_is_good");
    }

    if (city_sentiment() > 90) {
        keys.push_back("worker_city_is_amazing");
    }

    int index = rand() % keys.size();
    return keys[index];
}
