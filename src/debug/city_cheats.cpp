#include "dev/debug.h"

#include "building/building_house.h"
#include "city/city.h"
#include "city/city_animals.h"
#include "city/city_buildings.h"
#include "core/calc.h"

declare_console_ref_bool(allow_span_ostrich, g_animals.allow_spawn_ostrich);

declare_console_command_p(plague_start) {
    int plague_people = args.next_int(100);

    int total_population = 0;
    buildings_house_do([&](building_house* house) {
        if (!house->base.is_main() || house->house_population() <= 0) {
            return;
        }
        total_population += house->house_population();
    });
    g_city.health.start_disease(total_population, true, plague_people);
}

declare_console_command_p(plague_no) {
    buildings_house_do([&](building_house* house) {
        building& main = house->main()->base;
        main.disease_days = 0;
        main.has_plague = false;
        if (house->house_population() > 0) {
            main.common_health = 100;
        }
    });
    g_city.figures.remove_figures(FIGURE_PLAGUED_CITIZEN);
}

declare_console_command_p(show_pop_milestone) {
    g_city.population.reached_milestone(true);
}

declare_console_command_p(addprosperity) {
    int amount = args.next_int(10);
    g_city.ratings.prosperity = calc_bound(g_city.ratings.prosperity + amount, 0, 100);
}

declare_console_command_p(addculture) {
    int amount = args.next_int(10);
    g_city.ratings.culture = calc_bound(g_city.ratings.culture + amount, 0, 100);
};
