#include "city/city_houses.h"
#include "city/city.h"
#include "city/city_houses_chunks.h"
#include "core/xvalue.h"
#include "io/chunk_serializer.h"
#include "io/gamestate/save_versions.h"
#include "core/app_module.h"
#include "game/sim_schedule.h"

#include "core/random.h"
#include "core/profiler.h"
#include "figure/service.h"
#include "game/simulation.h"
#include "game/game_config.h"
#include "grid/routing/routing_terrain.h"
#include "building/building_house.h"

city_houses_t& city_houses() {
    return xvalue<city_houses_t>::ref();
}

void city_houses_t::reset() {
    *this = {};
}

void city_houses_t::update_health() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([] (auto house) {
        if (house->house_population() <= 0) {
            return;
        }

        decay_service(house->base.common_health);

        auto &housed = house->runtime_data();
        int target_common_health = (!!housed.apothecary ? 33 : 0)
                                    + (!!housed.physician ? 33 : 0)
                                    + (!!housed.dentist ? 33 : 0);

        auto &b = house->base;
        b.common_health += ((b.common_health < target_common_health) ? +1 : -1);
        b.common_health = std::clamp<int8_t>(b.common_health, 0, 100);

        if (b.has_plague) {
            random_generate_next();
            int chance_death = std::max(100 - b.common_health, 10);
            int randm = (random_short() % 99 + 1);
            bool has_death_today = (randm < chance_death);
            if (has_death_today && house->house_population() > 0) {
                house->change_population(-1);
            }
        }
    });
}

void city_houses_t::calculate_culture_demands() {
    // OG finance_estimates.c: the health advisor's demand (1 courthouse, 2 dentist, 3 health, 4 no courthouse at all).
    health = 0;
    int max = 0;
    if (missing.courthouse > 0 || missing.any_courthouse > 0) {
        if (missing.courthouse < missing.any_courthouse) {
            health = 4;
            max = missing.any_courthouse;
        } else {
            health = 1;
            max = missing.courthouse;
        }
    }

    if (max < missing.dentist) {
        health = 2;
        max = missing.dentist;
    }

    if (max < missing.health) {
        health = 3;
    }

    // education
    education = 0;
    if (missing.more_education > missing.education)
        education = 1; // schools(academies?)
    else if (missing.more_education < missing.education)
        education = 2; // libraries
    else if (missing.more_education || missing.education)
        education = 3; // more education

    // entertainment
    entertainment = 0;
    if (missing.entertainment > missing.more_entertainment)
        entertainment = 1;
    else if (missing.more_entertainment)
        entertainment = 2;

    // religion
    religion = 0;
    max = 0;
    if (missing.religion > max) {
        religion = 1;
        max = missing.religion;
    }
    if (missing.second_religion > max) {
        religion = 2;
        max = missing.second_religion;
    }
    if (missing.third_religion > max)
        religion = 3;
}

void city_houses_t::decay_houses_covered() {
    OZZY_PROFILER_FUNCTION();
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        building* b = building_get(i);
        if (b->state != BUILDING_STATE_UNUSED) { // b->type != BUILDING_TOWER
            if (b->houses_covered > 0)
                b->houses_covered--;
            //            if (building_is_farm(b->type) && b->data.industry.labor_days_left > 0)
            //                b->data.industry.labor_days_left--;
            ////            else if (b->houses_covered > 0)
            ////                b->houses_covered--;
            //
            ////            if (b->houses_covered == 255)
            ////                b->houses_covered = 0;
            //            if (GAME_ENV == ENGINE_ENV_PHARAOH) {
            //                if (b->data.industry.labor_state == 2)
            //                    b->data.industry.labor_state = 1;
            //                if (b->data.industry.labor_days_left == 0)
            //                    b->data.industry.labor_state = 0;
            //            }
        }
    }
}

void city_houses_t::process_evolve() {
    OZZY_PROFILER_FUNCTION();
    reset_demands();
    house_demands& demands = *this;
    bool has_expanded = false;
    const int day = g_simulation.simtime.day;
    buildings_house_do([&](building_house* house) {
        building& b = house->base;
        e_building_type save_type = house->type();
        has_expanded |= house->evolve(&demands);
        if (b.type != save_type) {
            b.clear_impl();
        }

        // OG building_house_process_evolve_and_consume_goods: goods are eaten right after the evolve, days 0 and 7.
        if ((day == 0 || day == 7) && b.state == BUILDING_STATE_VALID) {
            if (auto* consumer = b.dcast_house()) {
                consumer->consume_goods(day);
            }
        }
    });

    if (has_expanded) {
        map_routing_update_land();
    }
}

void city_houses_t::calculate_culture_aggregates() {
    OZZY_PROFILER_FUNCTION();
    int base_entertainment = city_avg_coverage().calc_average_entertainment() / 5;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (!house || house->state() != BUILDING_STATE_VALID || !house->hsize())
            continue;

        // entertainment
        auto &housed = house->runtime_data();
        const model_house& model = house->model();
        housed.entertainment = base_entertainment;
        const int jugglers_value = std::max<int>(housed.booth_juggler, housed.bandstand_juggler);
        housed.entertainment += (jugglers_value * 10) / model.entertainment_juggler_divider;

        const int musicians_value = std::max<int>(housed.bandstand_musician, housed.pavillion_musician);
        housed.entertainment += (musicians_value * 10) / model.entertainment_musician_divider;

        const int dancers_value = housed.pavillion_dancer;
        housed.entertainment += (dancers_value * 10) / model.entertainment_dancer_divider;

        const int senet_value = housed.senet_player;
        housed.entertainment += (senet_value * 10) / model.entertainment_senet_divider;

        // any zoo visit adds 40 while the house is still at or below 60, otherwise the visit fills entertainment to 100.
        if (housed.zookeeper) {
            if (housed.entertainment <= 60) {
                housed.entertainment += 40;
            } else {
                housed.entertainment = 100;
            }
        }

        housed.entertainment = std::min<int>(housed.entertainment, 100);

        // education
        housed.education = 0;
        if (housed.school || housed.library) {
            housed.education = 1;
            if (housed.school && housed.library) {
                housed.education = 2;
                if (housed.academy)
                    housed.education = 3;
            }
        }

        // religion
        housed.num_gods = 0;
        if (housed.temple_osiris)
            ++housed.num_gods;

        if (housed.temple_ra)
            ++housed.num_gods;

        if (housed.temple_ptah)
            ++housed.num_gods;

        if (housed.temple_seth)
            ++housed.num_gods;

        if (housed.temple_bast)
            ++housed.num_gods;

        if (game_features::gameplay_change_shrine_house_access.to_bool()
            && housed.num_gods == 0 && housed.shrine_access) {
            housed.num_gods = 1;
        }

        // health — OG: physician + mortuary (apothecary is a separate access byte)
        housed.health = 0;
        if (housed.physician)
            ++housed.health;

        if (housed.mortuary)
            ++housed.health;
    }
}

void city_houses_t::decay_tax_coverage() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([&](building_house* house) { house->decay_tax_coverage(); });
}

void city_houses_t::decay_services() {
    OZZY_PROFILER_FUNCTION();
    buildings_house_do([](auto house) { house->decay_services(); });
}

void city_houses_t::reset_demands() {
    missing.fountain = 0;
    missing.well = 0;
    missing.entertainment = 0;
    missing.more_entertainment = 0;
    missing.education = 0;
    missing.more_education = 0;
    missing.religion = 0;
    missing.second_religion = 0;
    missing.third_religion = 0;
    missing.dentist = 0;
    missing.courthouse = 0;
    missing.any_courthouse = 0;
    missing.health = 0;
    missing.more_health = 0;
    missing.food = 0;
    // OG city_houses_reset_demands leaves houses_missing_second_luxury alone too.

    requiring.school = 0;
    requiring.library = 0;
    requiring.dentist = 0;
    requiring.courthouse = 0;
    requiring.more_courthouse = 0;
    requiring.health = 0;
    requiring.religion = 0;
}

class houses_system : public sim_system {
public:
    const char* name() const override { return "houses"; }
    void on_reset() override { city_houses().reset(); }
    void push_save_sections(int file_version) override {
        if (file_version >= save_version_city_sections) {
            g_chunk_io.push_chunk<city_houses_chunk>(city_houses_chunk::size, false);
        }
    }
    void register_steps(sim_schedule_t& schedule) override {
        schedule.add({sim_step_house_service_decay, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 9) {
                              return;
                          }
                          city_houses().decay_services();
                      }});
        schedule.add({sim_step_houses_covered_decay, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 12) {
                              return;
                          }
                          city_houses().decay_houses_covered();
                      }});
        schedule.add({sim_step_house_health, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 35) {
                              return;
                          }
                          city_houses().update_health();
                      }});
        schedule.add({sim_step_culture_aggregates, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 36) {
                              return;
                          }
                          city_houses().calculate_culture_aggregates();
                      }});
        schedule.add({sim_step_house_evolve, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 39) {
                              return;
                          }
                          city_houses().process_evolve();
                      }});
        schedule.add({sim_step_house_tax_coverage_decay, SIM_PHASE_TICK, [](int tick) {
                          if (tick != 48) {
                              return;
                          }
                          city_houses().decay_tax_coverage();
                      }});
    }
};

void ANK_REGISTER_APPLICATION_MODULE(register_houses_system) {
    static houses_system system;
    g_simulation.register_system(&system);
}
