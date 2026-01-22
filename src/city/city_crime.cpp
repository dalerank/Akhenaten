#include "city/city.h"

#include "core/profiler.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "grid/road_access.h"
#include "figuretype/figure_robber.h"
#include "building/building_house.h"
#include "building/building_mansion.h"
#include "figuretype/figure_rioter.h"
#include "core/random.h"
#include "game/tutorial.h"
#include "building/destruction.h"

static void generate_rioter(building* b) {
    tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 4);
    if (!road_tile.valid()) {
        return;
    }

    g_city.sentiment.criminals++;
    int people_in_mob;
    const int population = g_city.population.current;
    if (population <= 150)
        people_in_mob = 1;
    else if (population <= 300)
        people_in_mob = 2;
    else if (population <= 800)
        people_in_mob = 3;
    else if (population <= 1200)
        people_in_mob = 4;
    else if (population <= 2000)
        people_in_mob = 5;
    else {
        people_in_mob = 6;
    }

    int x_target, y_target;
    int target_building_id = formation_rioter_get_target_building(&x_target, &y_target);
    for (int i = 0; i < people_in_mob; i++) {
        // TODO: to add correct rioter image
        figure* f = figure_create(FIGURE_RIOTER, road_tile, DIR_4_BOTTOM_LEFT);
        f->advance_action(ACTION_120_RIOTER_CREATED);
        f->roam_length = 0;
        f->wait_ticks = 10 + 4 * i;
        if (target_building_id) {
            f->destination_tile.set(x_target, y_target);
            f->set_destination(target_building_id);
        } else {
            f->poof();
        }
    }

    auto bmain = b->main();
    bmain->destroy_by_fire();

    g_city.ratings.monument_record_rioter();
    g_city.change_happiness(20);
    g_tutorials_flags.on_crime();
    city_message_apply_sound_interval(MESSAGE_CAT_RIOT);
    city_message_post_with_popup_delay(MESSAGE_CAT_RIOT, false, "message_riot", b->type, road_tile.grid_offset());
}

static void generate_protestor(building* b) {
    auto house = b->dcast_house();

    if (!house) {
        return;
    }

    g_city.sentiment.protesters++;

    auto &housed = house->runtime_data();
    if (housed.criminal_active > 30 && g_city.sentiment.can_create_protestor) {
        housed.criminal_active -= 30;
        tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
        if (road_tile.valid()) {
            figure* f = figure_create(FIGURE_PROTESTER, road_tile, DIR_4_BOTTOM_LEFT);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);
            g_city.ratings.monument_record_criminal();
        }
    }
}

void city_t::figures_generate_criminals() {
    OZZY_PROFILER_FUNCTION();
    building* min_building = nullptr;
    int min_happiness = 50;

    buildings_house_do([&] (auto house) {
        if (house->is_valid() && house->house_population()) {
            auto &housed = house->runtime_data();
            if (housed.house_happiness >= 50) {
                house->runtime_data().criminal_active = 0;
            } else if (housed.house_happiness < min_happiness) {
                min_happiness = housed.house_happiness;
                min_building = &house->base;
            }
        }
    });

    if (min_building) {
        const int sentiment = g_city.sentiment.value;

        if (sentiment < 30) {
            if (random_byte() >= sentiment + 50) {
                if (min_happiness <= 10) {
                    figure_robber::create(min_building);
                } else if (min_happiness < 30) {
                    figure_robber::create(min_building);
                } else if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        } else if (sentiment < 60) {
            if (random_byte() >= sentiment + 40) {
                if (min_happiness < 30) {
                    figure_robber::create(min_building);
                } else if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        } else {
            if (random_byte() >= sentiment + 20) {
                if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        }
    }
    
    // Check for theft from mansions
    building_mansion::check_theft_from_mansions();
}