#include "scenario.h"

#include "building/destruction.h"
#include "building/building_type.h"
#include "city/city_finance.h"
#include "city/city_health.h"
#include "city/city.h"
#include "game/game_events.h"
#include "city/city_message.h"
#include "city/city_population.h"
#include "city/trade.h"
#include "core/random.h"
#include "game/game_config.h"

enum E_EVENT_DK {
    EVENT_KINGDOME_RAISES_WAGES = 1,
    EVENT_KINGDOME_LOWERS_WAGES = 2,
    EVENT_LAND_TRADE_DISRUPTED = 3,
    EVENT_LAND_SEA_DISRUPTED = 4,
    EVENT_CONTAMINATED_WATER = 5,
    EVENT_COPPER_MINE_COLLAPSED = 6,
    EVENT_CLAY_PIT_FLOODED = 7
};

static const int RANDOM_EVENT_PROBABILITY[128]
  = {0, 0, 1, 0, 0, 0, 4, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6,
     0, 0, 2, 0, 0, 0, 7, 0, 5, 0, 0, 7, 0, 0, 0, 0, 0, 7, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
     6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 6, 0, 0,
     0, 7, 0, 1, 6, 0, 0, 0, 0, 0, 2, 0, 0, 4, 0, 0, 0, 0, 3, 0, 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0};

static void raise_wages(void) {
    if (g_scenario.random_events.raise_wages) {
        if (g_city.finance.raise_wages_kingdome())
            events::emit(event_message{ true, "message_kingdome_raises_wages", 0, 0 });
    }
}

static void lower_wages(void) {
    if (g_scenario.random_events.lower_wages) {
        if (g_city.finance.lower_wages_kingdome())
            events::emit(event_message{ true, "message_kingdome_lowers_wages", 0, 0 });
    }
}

static void disrupt_land_trade(void) {
    if (g_scenario.random_events.land_trade_problem) {
        if (city_trade_has_land_trade_route()) {
            city_trade_start_land_trade_problems(48);
            if (scenario_property_climate() == CLIMATE_DESERT)
                events::emit(event_message{ true, "message_land_trade_disrupted_sandstorms", 0, 0 });
            else {
                events::emit(event_message{ true, "message_land_trade_disrupted_landslides", 0, 0 });
            }
        }
    }
}

static void disrupt_sea_trade(void) {
    if (g_scenario.random_events.sea_trade_problem) {
        if (city_trade_has_sea_trade_route()) {
            city_trade_start_sea_trade_problems(48);
            events::emit(event_message{ true, "message_sea_trade_disrupted", 0, 0 });
        }
    }
}

static void contaminate_water(void) {
    if (g_scenario.random_events.contaminated_water) {
        const int city_population = g_city.population.current;
        if (city_population > 200) {
            int change;
            int health_rate = g_city.health.value;
            if (health_rate > 80)
                change = -50;
            else if (health_rate > 60)
                change = -40;
            else {
                change = -25;
            }
            g_city.health.change(change);
            events::emit(event_message{ true, "message_tutorial_major_plagues", 0, 0 });
        }
    }
}

static void destroy_copper_mine() {
    if (!g_scenario.random_events.copper_mine_collapsed) {
        return;
    }

    building_id bid = building_id_random(BUILDING_COPPER_MINE);
    auto b = building_get(bid);
    b->destroy_by_collapse();
    if (b) {
        messages::popup("message_copper_mine_collaped", 0, b->tile.grid_offset());
    }
}

static void destroy_clay_pit(void) {
    if (!g_scenario.random_events.clay_pit_flooded) {
        return;
    }

    building_id bid = building_id_random(BUILDING_CLAY_PIT);
    auto b = building_get(bid);
    b->destroy_by_flooded();
    if (b) {
        messages::popup("message_tutorial_flooded_clay_pit", 0, b->tile.grid_offset());
    }
}

void event_manager_t::process_random_events() {
    int event = RANDOM_EVENT_PROBABILITY[random_byte()];
    switch (event) {
    case EVENT_KINGDOME_RAISES_WAGES:
        raise_wages();
        break;
    case EVENT_KINGDOME_LOWERS_WAGES:
        lower_wages();
        break;
    case EVENT_LAND_TRADE_DISRUPTED:
        disrupt_land_trade();
        break;
    case EVENT_LAND_SEA_DISRUPTED:
        disrupt_sea_trade();
        break;
    case EVENT_CONTAMINATED_WATER:
        contaminate_water();
        break;
    case EVENT_COPPER_MINE_COLLAPSED:
        destroy_copper_mine();
        break;
    case EVENT_CLAY_PIT_FLOODED:
        destroy_clay_pit();
        break;
    }
}
