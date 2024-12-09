#include "empire.h"

#include "core/profiler.h"
#include "city/buildings.h"
#include "city/message.h"
#include "city/trade.h"
#include "city/city.h"
#include "city/population.h"
#include "building/count.h"
#include "scenario/map.h"
#include "trade_route.h"
#include "empire_object.h"
#include "io/io_buffer.h"
#include "game/mission.h"
#include "dev/debug.h"
#include "io/gamefiles/lang.h"

#include <iostream>
#include <algorithm>

empire_t g_empire;

#ifndef _WIN32
#define stricmp strcasecmp
#endif

declare_console_command_p(makeseatraders, game_cheat_make_sea_traders)
void game_cheat_make_sea_traders(std::istream &is, std::ostream &os) {
    for (auto &city : g_empire.get_cities()) {
        if (city.in_use) {
            city.is_sea_trade = true;
        }
    }
};

void empire_t::load_mission_metadata(const mission_id_t &missionid) {
    g_config_arch.r_section(missionid, [] (archive arch) {
        auto &data = g_empire;
        arch.r_array("cities", [&data] (archive city_arch) {
            pcstr name = city_arch.r_string("name");
            auto city = data.city(name);

            if (!city) {
                return;
            }

            city->is_sea_trade = city_arch.r_bool("is_sea_trade", city->is_sea_trade);
        });
    });
}

void empire_t::clear_cities_data() {
    memset(cities, 0, sizeof(cities));
}

empire_city* empire_t::city(int city_id) {
    if (city_id >= 0 && city_id < MAX_CITIES)
        return &cities[city_id];
    else
        return nullptr;
}

empire_city *empire_t::city(pcstr name) {
    for (auto &city : cities) {
        pcstr city_name = (pcstr)lang_get_string(195, city.name_id);
        if (stricmp(city_name, name) == 0) {
            return &city;
        }
    }
    return nullptr;
}

bool empire_t::can_import_resource(e_resource resource, bool check_if_open) {
    for (const auto &city: cities) {
        if (city.in_use && city.can_trade()
            && (city.is_open || !check_if_open) && city.sells_resource[resource]) {
            return true;
        }
    }
    return false;
}

bool empire_t::can_export_resource(e_resource resource, bool check_if_open) {
    for (const auto &city: cities) {
        if (city.in_use && city.can_trade()
            && (city.is_open || !check_if_open) && city.buys_resource[resource]) {
            return true;
        }
    }
    return false;
}

int empire_t::get_city_for_object(int empire_object_id) {
    for (auto &city: cities) {
        if (city.in_use && city.empire_object_id == empire_object_id) {
            return std::distance(cities, &city);
        }
    }
    return 0;
}

void empire_t::expand() {
    for (auto &city: cities) {
        if (!city.in_use)
            continue;

        if (city.type == EMPIRE_CITY_EGYPTIAN_TRADING) {
            city.type = EMPIRE_CITY_PHARAOH;
        } else if (city.type == EMPIRE_CITY_FOREIGN) {
            city.type = EMPIRE_CITY_OURS;
        } else {
            continue;
        }
        empire_object_set_expanded(city.empire_object_id, city.type);
    }
}

int empire_t::count_wine_sources() {
    int sources = 0;
    for (const auto &city: cities) {
        if (city.in_use && city.is_open && city.sells_resource[RESOURCE_BEER]) {
            sources++;
        }
    }
    return sources;
}

int empire_t::trade_route_for_city(int city_id) {
    return city(city_id)->route_id;
}

void empire_t::reset_yearly_trade_amounts() {
    for (const auto &city: cities) {
        if (city.in_use && city.is_open) {
            trade_route &route = get_route(city.route_id);
            route.reset_traded();
        }
    }
}

bool empire_t::is_trade_route_open(int route_id) {
    for (const auto &city: cities) {
        if (city.in_use && city.route_id == route_id)
            return city.is_open; // ? true : false;
    }
    return false;
}

int empire_t::get_city_for_trade_route(int route_id) {
    for (auto &city: cities) {
        if (city.in_use && city.route_id == route_id) {
            return std::distance(cities, &city);
        }
    }
    return -1;
}

int empire_t::get_city_vulnerable() {
    int index = 0;
    for (auto &city: cities) {
        if (city.in_use) {
            if (city.type == EMPIRE_CITY_FOREIGN_TRADING) {
                index = std::distance(cities, &city);
            }
        }
    }
    return index;
}

void empire_t::generate_traders() {
    OZZY_PROFILER_SECTION("Game/Run/Tick/Trade Update/Genereate trader");
    for (auto &city: cities) {
        if (!city.in_use || !city.is_open) {
            continue;
        }

        if (city.is_sea_trade) {
            if (!g_city.buildings.has_working_dock()) {
                city_message_post_with_message_delay(MESSAGE_CAT_NO_WORKING_DOCK, 1, MESSAGE_NO_WORKING_DOCK_PH, 384);
                continue;
            }

            if (!scenario_map_has_river_entry()) {
                continue;
            }

            city_trade_add_sea_trade_route();
        } else {
            city_trade_add_land_trade_route();
        }

        if (g_city.generate_trader_from(city)) {
            break;
        }
    }
}

int get_max_raw_stock_for_population(e_resource resource) {
    int finished_good = RESOURCE_NONE;
    switch (resource) {
    case RESOURCE_CLAY: finished_good = RESOURCE_POTTERY; break;
    case RESOURCE_GEMS: finished_good = RESOURCE_LUXURY_GOODS; break;
    case RESOURCE_STRAW: finished_good = RESOURCE_OIL; break;
    case RESOURCE_BARLEY: finished_good = RESOURCE_BEER; break;
    case RESOURCE_FLAX: finished_good = RESOURCE_LINEN; break;
    case RESOURCE_COPPER: finished_good = RESOURCE_WEAPONS; break;
    }

    int max_in_stock = 0;
    if (finished_good) {
        max_in_stock = 200 + 200 * building_count_industry_active(resource);
    }

    return max_in_stock;
}

int get_max_food_stock_for_population(e_resource resource) {
    switch (resource) {
    case RESOURCE_GRAIN:
    case RESOURCE_MEAT:
    case RESOURCE_LETTUCE:
    case RESOURCE_GAMEMEAT:
    case RESOURCE_POTTERY:
    case RESOURCE_LUXURY_GOODS:
    case RESOURCE_OIL:
    case RESOURCE_BEER:
        return std::max(100, (city_population() / 100) * 100);

    default:
        assert(false);
    }

    return 0;
}

resource_list empire_t::importable_resources_from_city(int city_id) {
    resource_list result;
    for (const auto &r: resource_list::all) {
        if (can_import_resource_from_city(city_id, r.type)) {
            result[r.type] = 1;
        }
    }

    return result;
}

resource_list empire_t::exportable_resources_from_city(int city_id) {
    resource_list result;
    for (const auto &r: resource_list::all) {
        if (can_export_resource_to_city(city_id, r.type)) {
            result[r.type] = 1;
        }
    }

    return result;
}

bool empire_t::can_export_resource_to_city(int city_id, e_resource resource) {
    empire_city* city = g_empire.city(city_id);
    trade_route &trade_route = g_empire.get_route(city->route_id);
    if (city_id && trade_route.limit_reached(resource)) {
        // quota reached
        return false;
    }

    if (city_resource_warehouse_stored(resource) <= city_resource_trading_amount(resource)) {
        // stocks too low
        return false;
    }

    if (city_id == 0 || city->buys_resource[resource]) {
        int status = city_resource_trade_status(resource);
        switch (status) {
        case TRADE_STATUS_EXPORT: return true;
        case TRADE_STATUS_EXPORT_SURPLUS: return city_resource_trade_surplus(resource);
        }
    }

    return false;
}

bool empire_t::can_import_resource_from_city(int city_id, e_resource resource) {
    empire_city* city = this->city(city_id);
    if (!city->sells_resource[resource]) {
        return false;
    }

    int status = city_resource_trade_status(resource);
    switch (status) {
    case TRADE_STATUS_IMPORT:
    case TRADE_STATUS_IMPORT_AS_NEEDED:
        ;
        break;

    default:
        return false;
    }

    trade_route &trade_route = g_empire.get_route(city->route_id);
    if (trade_route.limit_reached(resource)) {
        return false;
    }

    int in_stock = city_resource_warehouse_stored(resource);
    int max_in_stock = 0;

    if (status == TRADE_STATUS_IMPORT_AS_NEEDED) {
        switch (resource) {
            // food and finished materials
        case RESOURCE_GRAIN:
        case RESOURCE_MEAT:
        case RESOURCE_LETTUCE:
        case RESOURCE_GAMEMEAT:
        case RESOURCE_OIL:
        case RESOURCE_BEER:
            max_in_stock = get_max_food_stock_for_population(resource);
            break;

        case RESOURCE_MARBLE:
        case RESOURCE_WEAPONS:
            max_in_stock = 10;
            break;

        case RESOURCE_CLAY:
        case RESOURCE_STRAW: 
        case RESOURCE_BARLEY:
        case RESOURCE_COPPER:
        case RESOURCE_FLAX:
            max_in_stock = get_max_raw_stock_for_population(resource);
            break;

        case RESOURCE_TIMBER:
            max_in_stock = building_count_active(BUILDING_SHIPWRIGHT) * 200;
            break;

        case RESOURCE_BRICKS:
            max_in_stock = std::max(100, (city_population() / 100) * 100);
            break;

        case RESOURCE_POTTERY:
        case RESOURCE_LUXURY_GOODS:
            max_in_stock = std::max(100, (city_population() / 100) * 50);
            break;

        case RESOURCE_PAPYRUS:
            max_in_stock = std::max(100, (building_count_active(BUILDING_SCRIBAL_SCHOOL) + building_count_active(BUILDING_LIBRARY)) * 100);
            break;

        default:
            max_in_stock = 100;
            break;
        }
    } else {
        max_in_stock = city_resource_trading_amount(resource);
    }

    return in_stock < max_in_stock ? 1 : 0;
}


io_buffer* iob_empire_cities = new io_buffer([](io_buffer* iob, size_t version) {
    for (int i = 0; i < g_empire.get_cities().size(); i++) {
        empire_city* city = &g_empire.get_cities()[i];
        iob->bind(BIND_SIGNATURE_UINT8, &city->in_use);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &city->type);
        iob->bind(BIND_SIGNATURE_UINT8, &city->name_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->is_open);

        for (int r = 0; r < RESOURCES_MAX; r++)
            iob->bind(BIND_SIGNATURE_UINT8, &city->buys_resource[r]);
        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &city->sells_resource[r]);
        }

        iob->bind(BIND_SIGNATURE_INT16, &city->cost_to_open);
        iob->bind(BIND_SIGNATURE_INT16, &city->ph_unk01);
        iob->bind(BIND_SIGNATURE_INT16, &city->trader_entry_delay);
        iob->bind(BIND_SIGNATURE_INT16, &city->ph_unk02);
        iob->bind(BIND_SIGNATURE_INT16, &city->empire_object_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city->is_sea_trade);
        iob->bind____skip(1);

        for (int f = 0; f < 3; f++)
            iob->bind(BIND_SIGNATURE_INT16, &city->trader_figure_ids[f]);
        
        iob->bind____skip(10);
    }
});
