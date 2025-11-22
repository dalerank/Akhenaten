#include "empire.h"

#include "core/profiler.h"
#include "dev/debug.h"
#include "js/js_game.h"
#include <iostream>
#include "empire/empire_traders.h"
#include "city/buildings.h"
#include "city/city_message.h"
#include "city/city.h"
#include "city/city_population.h"
#include "scenario/map.h"
#include "trade_route.h"
#include "empire_object.h"
#include "io/io_buffer.h"
#include "game/mission.h"
#include "dev/debug.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "core/log.h"
#include "content/vfs.h"
#include <string>

#include <iostream>
#include <algorithm>

//empire_t ANK_VARIABLE_N(g_empire, "empire");
empire_t g_empire;

#ifndef _WIN32
#define stricmp strcasecmp
#endif

declare_console_command_p(save_empire_routes) {
    const int MAX_ROUTE_OBJECTS = 50;
    vfs::path fs_file = vfs::content_path("empire_routes.js");
    FILE* fp = vfs::file_open_os(fs_file, "wt");
    if (!fp) {
        logs::error("Unable to empire_routes file %s", fs_file.c_str());
        return;
    }

    std::string sroutesdata = "log_info(\"akhenaten: akhenaten.conf started\")\n";
    sroutesdata.append("var empire_routes = [\n");

    for (int id = 0; id < MAX_ROUTE_OBJECTS; id++) {
        const map_route_object& obj = g_empire.get_route_object(id);
        if (!obj.in_use) {
            continue;
        }

        sroutesdata.append("{\n");
        sroutesdata.append(bstring128().printf("\tunk_header : [%d, %d]\n", obj.unk_header[0], obj.unk_header[1]).c_str());;

        sroutesdata.append("\tpoints = [\n");
        for (int i = 0; i < 50; i++) {
            sroutesdata.append(bstring128().printf("\t\t{ x : %d, y : %d, is_in_use : %i },\n", obj.points[i].p.x, obj.points[i].p.y, obj.points[i].is_in_use).c_str());
        }
        sroutesdata.append("\t]\n");

        int city_id = g_empire.get_city_for_trade_route(id);
        const empire_city& city = *g_empire.city(city_id);
        const empire_city& ourcity = g_city.ourcity();

        sroutesdata.append(bstring128().printf("\tstart : \"%s\"\n", lang_get_string(21, city.name_id)));
        sroutesdata.append(bstring128().printf("\told_name : \"%s\"\n", lang_get_string(195, city.name_id)));
        sroutesdata.append(bstring128().printf("\tstop : \"%s\"\n", lang_get_string(21, ourcity.name_id)));
        sroutesdata.append(bstring128().printf("\tcity_id : %d\n", city.name_id));
        sroutesdata.append(bstring128().printf("\troute_id : %d\n", id));
        sroutesdata.append(bstring128().printf("\tlength : %d\n", obj.length));
        sroutesdata.append(bstring128().printf("\tunk_00 : %d\n", obj.unk_00));
        sroutesdata.append(bstring128().printf("\tunk_01 : %d\n", obj.unk_01));

        sroutesdata.append(bstring128().printf("\troute_type : %d\n", obj.route_type)); // 1 = land, 2 = sea
        sroutesdata.append(bstring128().printf("\tnum_points : %d\n", obj.num_points));
        sroutesdata.append(bstring128().printf("\tin_use : %d\n", obj.in_use));
        sroutesdata.append(bstring128().printf("\tunk_03 : %d\n", obj.unk_03));

        sroutesdata.append("},\n");
    }
    sroutesdata.append("]\n");

    fprintf(fp, "%s", sroutesdata.c_str());
    sroutesdata.clear();

    vfs::file_close(fp);
}

void empire_t::load_mission_metadata(const mission_id_t &missionid) {
    g_config_arch.r_section(missionid, [] (archive arch) {
        auto &data = g_empire;
        arch.r_array("cities", [&data] (archive city_arch) {
            pcstr name = city_arch.r_string("name");
            auto city = data.city(name);

            if (!city) {
                return;
            }

            city_arch.r(*city);

            g_empire.set_trade_route_type(city->route_id, city->is_sea_trade);
        });
    });
}

void empire_t::update_month() {
    for (auto &city: cities) {
        if (!city.in_use) {
            continue;
        } 
        
        if (city.months_under_siege > 0) {
            city.months_under_siege--;
        }
    }
}

void empire_t::clear_cities_data() {
    std::fill_n(cities, MAX_CITIES, empire_city{});

    for (int i = 0; i < MAX_CITIES; ++i) {
        cities[i].lookup_id = i;
    }
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
        g_empire.object_set_expanded(city.empire_object_id, city.type);
    }
}

int empire_t::count_beer_sources() {
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
    OZZY_PROFILER_SECTION("Game/Run/Tick/Trade Update/Generate trader");
        
    for (auto &city: cities) {
        if (!city.in_use || !city.is_open) {
            continue;
        }

        if (city.is_sea_trade) {
            if (!g_city.buildings.has_working_dock()) {
                city_message_post_with_message_delay(MESSAGE_CAT_NO_WORKING_DOCK, 1, "message_no_working_dock", 384);
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
        max_in_stock = 200 + 200 * g_city.buildings.count_industry_active(resource);
    }

    return max_in_stock;
}

int get_max_food_stock_for_population(e_resource resource) {
    const int city_population = g_city.population.current;

    switch (resource) {
    case RESOURCE_GRAIN:
    case RESOURCE_MEAT:
    case RESOURCE_LETTUCE:
    case RESOURCE_GAMEMEAT:
    case RESOURCE_POTTERY:
    case RESOURCE_LUXURY_GOODS:
    case RESOURCE_OIL:
    case RESOURCE_BEER:
        return std::max(100, (city_population / 100) * 100);

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

    if (g_city.resource.yards_stored(resource) <= city_resource_trading_amount(resource)) {
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

    const int city_population = g_city.population.current;
    int in_stock = g_city.resource.yards_stored(resource);
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
            max_in_stock = g_city.buildings.count_active(BUILDING_SHIPWRIGHT) * 200;
            break;

        case RESOURCE_BRICKS:
            max_in_stock = std::max(100, (city_population / 100) * 100);
            break;

        case RESOURCE_POTTERY:
        case RESOURCE_LUXURY_GOODS:
            max_in_stock = std::max(100, (city_population / 100) * 50);
            break;

        case RESOURCE_PAPYRUS:
            max_in_stock = std::max(100, g_city.buildings.count_active({ BUILDING_SCRIBAL_SCHOOL, BUILDING_LIBRARY }) * 100);
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
        empire_city& city = g_empire.get_cities()[i];
        city.lookup_id = i;
        iob->bind_u8(city.in_use);
        iob->bind_u8(city.max_traders);
        iob->bind_u8((uint8_t&)city.type);

        iob->bind(BIND_SIGNATURE_UINT8, &city.name_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.is_open);

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind_bool(city.buys_resource[r]);
        }

        for (int r = 0; r < RESOURCES_MAX; r++) {
            iob->bind_bool(city.sells_resource[r]);
        }

        iob->bind_i16(city.cost_to_open);
        iob->bind(BIND_SIGNATURE_INT16, &city.ph_unk01);
        iob->bind(BIND_SIGNATURE_INT16, &city.trader_entry_delay);
        iob->bind(BIND_SIGNATURE_INT16, &city.ph_unk02);
        iob->bind(BIND_SIGNATURE_INT16, &city.empire_object_id);
        iob->bind(BIND_SIGNATURE_UINT8, &city.is_sea_trade);
        iob->bind_u8(city.months_under_siege);

        for (int f = 0; f < 3; f++) {
            iob->bind(BIND_SIGNATURE_INT16, &city.trader_figure_ids[f]);
        }
        
        iob->bind____skip(10);

        if (iob->is_read_access()) {
            city.check_attributes();
        }
    }
});

void empire_t::end_siege(int city_id) {
    empire_city* city = this->city(city_id);
    if (city && city->is_sieged()) {
        city->set_under_siege(0);
    }
}

void empire_t::end_all_sieges() {
    for (auto &city : cities) {
        if (city.in_use && city.is_sieged()) {
            city.set_under_siege(0);
        }
    }
}

// Console commands for testing siege functionality
declare_console_command_p(siege_city) {
    std::string args; is >> args;
    int city_id = atoi(args.empty() ? "0" : args.c_str());
    
    empire_city* city = g_empire.city(city_id);
    if (city && city->in_use && city->can_trade()) {
        city->set_under_siege(true);
        std::cout << "City " << city_id << " is now under siege!" << std::endl;
    } else {
        std::cout << "City " << city_id << " cannot be sieged!" << std::endl;
    }
}

declare_console_command_p(end_siege) {
    std::string args; is >> args;
    int city_id = atoi(args.empty() ? "0" : args.c_str());
    
    if (city_id == 0) {
        g_empire.end_all_sieges();
        std::cout << "All sieges ended!" << std::endl;
    } else {
        g_empire.end_siege(city_id);
        std::cout << "Siege ended for city " << city_id << std::endl;
    }
}

declare_console_command_p(list_cities) {
    std::cout << "Empire Cities Status:" << std::endl;
    for (int i = 0; i < empire_t::MAX_CITIES; i++) {
        empire_city* city = g_empire.city(i);
        if (city && city->in_use) {
            std::cout << "City " << i << ": Type=" << (int)city->type 
                      << ", Open=" << (city->is_open ? "Yes" : "No")
                      << ", Sieged=" << (city->is_sieged() ? "Yes" : "No")
                      << ", CanTrade=" << (city->can_trade() ? "Yes" : "No") << std::endl;
        }
    }
}