#include "city/city.h"

#include "core/profiler.h"
#include "city/sentiment.h"
#include "city/population.h"
#include "city/message.h"
#include "grid/road_access.h"
#include "figure/figure.h"
#include "building/building_house.h"
#include "core/random.h"
#include "game/tutorial.h"
#include "building/destruction.h"

static void generate_rioter(building* b) {
    tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 4);
    if (!road_tile.valid()) {
        return;
    }

    city_sentiment_add_criminal();
    int people_in_mob;
    int population = city_population();
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
        figure* f = figure_create(FIGURE_TOMB_ROBER, road_tile, DIR_4_BOTTOM_LEFT);
        f->advance_action(FIGURE_ACTION_120_RIOTER_CREATED);
        f->roam_length = 0;
        f->wait_ticks = 10 + 4 * i;
        if (target_building_id) {
            f->destination_tile.set(x_target, y_target);
            f->set_destination(target_building_id);
        } else {
            f->poof();
        }
    }

    building_destroy_by_rioter(b);
    g_city.ratings.monument_record_rioter();
    city_sentiment_change_happiness(20);
    g_tutorials_flags.on_crime();
    city_message_apply_sound_interval(MESSAGE_CAT_RIOT);
    city_message_post_with_popup_delay(MESSAGE_CAT_RIOT, false, MESSAGE_RIOT, b->type, road_tile.grid_offset());
}

static void generate_robber(building* b) {
    city_sentiment_add_criminal();
    if (b->house_criminal_active > 60 && city_can_create_mugger()) {
        b->house_criminal_active -= 60;
        tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
        if (road_tile.valid()) {
            figure* f = figure_create(FIGURE_ROBBER, road_tile, DIR_4_BOTTOM_LEFT);
            f->advance_action(FIGURE_ACTION_120_MUGGER_CREATED);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);

            g_city.ratings.monument_record_criminal();
            int taxes_this_year = city_finance_overview_this_year()->income.taxes;
            if (taxes_this_year > 20) {
                int money_stolen = taxes_this_year / 4;
                if (money_stolen > 400) {
                    money_stolen = 400 - random_byte() / 2;
                }

                city_show_message_criminal(MESSAGE_TUTORIAL_CRIME, money_stolen, f->tile.grid_offset());
                city_finance_process_stolen(money_stolen);              
            } else {
                int treasury = city_finance_treasury();
                int money_stolen = 0;
                if (treasury > 0) {
                    money_stolen = (random_byte() / 2) % 100;
                }

                if (money_stolen > 0) {
                    city_show_message_criminal(MESSAGE_TUTORIAL_CRIME, money_stolen, f->tile.grid_offset());
                    city_finance_process_stolen(money_stolen);
                }
            }
        }
    }
}

static void generate_protestor(building* b) {
    city_sentiment_add_protester();
    if (b->house_criminal_active > 30 && city_can_create_protestor()) {
        b->house_criminal_active -= 30;
        tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
        if (road_tile.valid()) {
            figure* f = figure_create(FIGURE_PROTESTER, road_tile, DIR_4_BOTTOM_LEFT);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);
            g_city.ratings.monument_record_criminal();
        }
    }
}

void city_t::figures_generate_criminals() {
    OZZY_PROFILER_SECTION("Game/Update/Generate Criminals");
    building* min_building = nullptr;
    int min_happiness = 50;
    int max_id = building_get_highest_id();
    for (int i = 1; i <= max_id; i++) {
        auto house = building_get(i)->dcast_house();

        if (house && house->state() == BUILDING_STATE_VALID && house->base.house_size) {
            auto &housed = house->runtime_data();
            if (housed.house_happiness >= 50) {
                house->base.house_criminal_active = 0;
            } else if (housed.house_happiness < min_happiness) {
                min_happiness = housed.house_happiness;
                min_building = &house->base;
            }
        }
    }

    if (min_building) {
        int sentiment = city_sentiment();

        if (sentiment < 30) {
            if (random_byte() >= sentiment + 50) {
                if (min_happiness <= 10) {
                    // if (GAME_ENV == ENGINE_ENV_C3) { // Temporary disable rioters in Egypt
                    //     generate_rioter(min_building);
                    // } else if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    generate_robber(min_building);
                } else if (min_happiness < 30) {
                    generate_robber(min_building);
                } else if (min_happiness < 50) {
                    generate_protestor(min_building);
                }
            }
        } else if (sentiment < 60) {
            if (random_byte() >= sentiment + 40) {
                if (min_happiness < 30) {
                    generate_robber(min_building);
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
}