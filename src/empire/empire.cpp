#include "empire.h"

#include "core/profiler.h"
#include "city/buildings.h"
#include "city/message.h"
#include "city/trade.h"
#include "city/city.h"
#include "scenario/map.h"
#include "trade_route.h"
#include "empire_object.h"

#include "io/io_buffer.h"
#include "dev/debug.h"
#include <iostream>

empire_t g_empire;

declare_console_command_p(makeseatraders, game_cheat_make_sea_traders)
void game_cheat_make_sea_traders(std::istream &is, std::ostream &os) {
    for (auto &city : g_empire.get_cities()) {
        if (city.in_use) {
            city.is_sea_trade = true;
        }
    }
};

void empire_t::clear_cities_data() {
    memset(cities, 0, sizeof(cities));
}

empire_city* empire_t::city(int city_id) {
    if (city_id >= 0 && city_id < MAX_CITIES)
        return &cities[city_id];
    else
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

void empire_t::reset_yearly_trade_amounts() {
    for (const auto &city: cities) {
        if (city.in_use && city.is_open)
            trade_route_reset_traded(city.route_id);
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
            if (!city_buildings_has_working_dock()) {
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

        if (g_city.generate_trader_from(std::distance(cities, &city), city)) {
            break;
        }
    }
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
