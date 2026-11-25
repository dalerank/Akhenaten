#include "city/city_crime.h"
#include "city/city_houses.h"
#include "city/city_buildings.h"
#include "core/xvalue.h"
#include "city/city_population.h"
#include "city/ratings.h"
#include "city/city_sentiment.h"
#include "game/simulation.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "core/profiler.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "grid/road_access.h"
#include "figuretype/figure_robber.h"
#include "figuretype/figure_protestor.h"
#include "building/building_house.h"
#include "building/building_mansion.h"
#include "figuretype/figure_rioter.h"
#include "core/random.h"
#include "building/destruction.h"
#include "game/game_config.h"

static void generate_rioter(building* b) {
    tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 4);
    if (!road_tile.valid()) {
        return;
    }

    city_sentiment().criminals++;
    int people_in_mob;
    const int population = city_population().current;
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
            events::emit(event_rioter_created{f->id});
        } else {
            f->poof();
        }
    }

    auto bmain = b->main();
    bmain->destroy_by_fire();

    city_ratings().monument_record_rioter();
    city_houses().change_happiness(20);

    message_manager().apply_sound_interval(MESSAGE_CAT_RIOT);
    message_manager().post_with_popup_delay(MESSAGE_CAT_RIOT, false, "message_riot", b->type, road_tile.grid_offset());
}

static void generate_protestor(building* b) {
    auto house = b->dcast_house();

    if (!house) {
        return;
    }

    city_sentiment().protesters++;

    auto &housed = house->runtime_data();
    if (housed.criminal_active > 30 && city_sentiment().can_create_protestor) {
        housed.criminal_active -= 30;
        tile2i road_tile = map_closest_road_within_radius(b->tile, b->size, 2);
        if (road_tile.valid()) {
            figure* f = figure_create(FIGURE_PROTESTER, road_tile, DIR_4_BOTTOM_LEFT);
            f->wait_ticks = 10 + (b->map_random_7bit & 0xf);
            if (game_features::gameplay_change_protestor_hunt_nobles.to_bool()) {
                f->advance_action(ACTION_8_PROTESTOR_WAITING);
                f->set_flag(e_figure_flag_criminal, true);
            }
            city_ratings().monument_record_criminal();
        }
    }
}

city_crime_t& city_crime() {
    return xvalue<city_crime_t>::ref();
}

void city_crime_t::generate_criminals() {
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
        const int sentiment = city_sentiment().value;

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

void city_crime_t::update_day() {
    buildings_house_do([](auto house) {
        if (!house->hsize()) {
            return;
        }

        int delta;
        auto& housed = house->runtime_data();
        if (housed.house_happiness >= 50) {
            delta = (housed.house_happiness - 50) / 30;
        } else if (housed.house_happiness < 50) {
            delta = -std::max<int>((50 - housed.house_happiness) / 10, 0);
        }

        housed.criminal_active += delta;
        housed.criminal_active = std::clamp<int>(housed.criminal_active, 0, 100);
    });
}

class crime_system : public sim_system {
public:
    const char* name() const override { return "crime"; }
    void on_reset() override {}
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_crime, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 30) {
                              return;
                          }
                          g_crime.update();
                      }});
        schedule.add({sim_step_criminals, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 45) {
                              return;
                          }
                          city_crime().generate_criminals();
                      }});
        schedule.add({sim_step_criminals_day, SIM_PHASE_DAY, [](int) { city_crime().update_day(); }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_crime_system) {
    static crime_system system;
    g_simulation.register_system(&system);
}
