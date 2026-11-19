#include "empire.h"

#include "core/profiler.h"
#include "dev/debug.h"
#include "js/js_register.h"
#include "empire/empire_traders.h"
#include "city/buildings.h"
#include "city/city_message.h"
#include "city/city.h"
#include "city/city_trade.h"
#include "city/city_resource_handle.h"
#include "city/city_population.h"
#include "scenario/map.h"
#include "trade_route.h"
#include "empire_object.h"
#include "io/io_buffer.h"
#include "io/chunk_serializer.h"
#include "game/mission.h"
#include "io/gamefiles/lang.h"
#include "game/game_config.h"
#include "core/log.h"
#include "core/random.h"
#include "game/simulation.h"
#include "content/vfs.h"
#include <string>

#include <algorithm>
#include <array>

//empire_t ANK_VARIABLE_N(g_empire, "empire");
empire_t g_empire;
empire_trade_rules_t ANK_VARIABLE(empire_trade_rules);

#ifndef _WIN32
#define stricmp strcasecmp
#endif

declare_console_command_p(save_empire_routes) {
    const int MAX_ROUTE_OBJECTS = 50;
    vfs::path fs_file = vfs::path("empire_routes.js").resolve();
    FILE* fp = vfs::file_open_os(fs_file, "wt");
    if (!fp) {
        logs::error("Unable to empire_routes file %s", fs_file.c_str());
        return;
    }

    fputs("log_info(\"akhenaten: akhenaten.conf started\")\n", fp);
    fputs("var empire_routes = [\n", fp);

    for (int id = 0; id < MAX_ROUTE_OBJECTS; id++) {
        const map_route_object& obj = g_empire.get_route_object(id);
        if (!obj.in_use) {
            continue;
        }

        fputs("{\n", fp);
        fprintf(fp, "\tunk_header : [%d, %d]\n", obj.unk_header[0], obj.unk_header[1]);

        fputs("\tpoints = [\n", fp);
        for (int i = 0; i < 50; i++) {
            fprintf(fp, "\t\t{ x : %d, y : %d, is_in_use : %i },\n", obj.points[i].p.x, obj.points[i].p.y, obj.points[i].is_in_use);
        }
        fputs("\t]\n", fp);

        int city_id = g_empire.get_city_for_trade_route(id);
        const empire_city& city = *g_empire.city(city_id);
        const empire_city& ourcity = g_city.ourcity();

        fprintf(fp, "\tstart : \"%s\"\n", lang_get_string(21, city.name_id));
        fprintf(fp, "\told_name : \"%s\"\n", lang_get_string(195, city.name_id));
        fprintf(fp, "\tstop : \"%s\"\n", lang_get_string(21, ourcity.name_id));
        fprintf(fp, "\tcity_id : %d\n", city.name_id);
        fprintf(fp, "\troute_id : %d\n", id);
        fprintf(fp, "\tlength : %d\n", obj.length);
        fprintf(fp, "\tunk_00 : %d\n", obj.unk_00);
        fprintf(fp, "\tunk_01 : %d\n", obj.unk_01);

        fprintf(fp, "\troute_type : %d\n", obj.route_type); // 1 = land, 2 = sea
        fprintf(fp, "\tnum_points : %d\n", obj.num_points);
        fprintf(fp, "\tin_use : %d\n", obj.in_use);
        fprintf(fp, "\tunk_03 : %d\n", obj.unk_03);

        fputs("},\n", fp);
    }
    fputs("]\n", fp);

    vfs::file_close_os(fp);
}

void empire_t::load_mission_metadata(const mission_id_t &missionid, bool preserve_runtime) {
    std::array<uint8_t, MAX_CITIES> saved_open{};
    std::array<bool, MAX_CITIES> had_city{};
    if (preserve_runtime) {
        for (int i = 0; i < MAX_CITIES; ++i) {
            if (!cities[i].in_use) {
                continue;
            }
            had_city[i] = true;
            saved_open[i] = cities[i].is_open ? 1 : 0;
        }
    }

    g_config_arch.r_section(missionid, [preserve_runtime] (archive arch) {
        // When true: ignore all pak cities and show only cities listed in JS (including ours).
        const bool hide_pak_cities = arch.r_bool("hide_pak_cities", false);
        if (hide_pak_cities) {
            for (auto &city : g_empire.get_cities()) {
                if (!city.in_use) {
                    continue;
                }
                city.in_use = 0;
            }
        }

        g_empire.load_empire_cities(arch, preserve_runtime);

        if (hide_pak_cities) {
            g_empire.hide_unused_city_objects();
        }

        if (arch.r_bool("hide_pak_routes", false)) {
            g_empire.clear_route_objects();
        }
        g_empire.load_empire_routes(arch);

        if (arch.r_bool("hide_pak_objects", false)) {
            g_empire.hide_non_city_objects();
        }
        g_empire.load_empire_texts(arch);
        g_empire.load_empire_ornaments(arch);
        g_empire.load_empire_battle_icons(arch);
        g_empire.load_empire_land_routes(arch);
        g_empire.load_empire_sea_routes(arch);
        g_empire.load_empire_kingdome_armies(arch);
        g_empire.load_empire_enemy_armies(arch);
    });

    if (preserve_runtime) {
        for (int i = 0; i < MAX_CITIES; ++i) {
            if (!cities[i].in_use || !had_city[i]) {
                continue;
            }
            cities[i].is_open = saved_open[i] != 0;
            // Maps store "open" as any non-zero byte (0xff in OG maps); keep it unless openness changed.
            full_empire_object* full = ref_full_object(cities[i].empire_object_id);
            if (full && (full->trade_route_open != 0) != (saved_open[i] != 0)) {
                full->trade_route_open = saved_open[i];
            }
        }
    }

    for (auto &city : cities) {
        if (!city.in_use) {
            continue;
        }

        city.name_str = empire_city::get_display_name(city.name_id);

        if (full_empire_object *full = ref_full_object(city.empire_object_id)) {
            if (full->obj.type == EMPIRE_OBJECT_CITY) {
                // OG keeps the stored value: objects from the empire file carry in_use 2.
                if (!full->in_use) {
                    full->in_use = 1;
                }
                full->city_name_id = city.name_id;
                full->city_type = city.type;
            }
        }
    }
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

empire_city *empire_t::city(xstring name) {
    const int name_id = find_city_name_id(name.c_str());
    if (name_id >= 0) {
        return city(name_id);
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

int empire_t::get_city_for_object(int empire_object_id) const {
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

// OG empire_count_luxury_goods_kinds + empire_city_generate_trader: a city with a luxury workshop has the first
// kind; every open city that sells luxury goods on a route with a limit adds its culture's kind while the city
// imports them.
int empire_t::count_luxury_goods_kinds() {
    int kinds[LUXURY_KIND_MAX] = {};
    kinds[LUXURY_JEWELRY] = g_city.buildings.count_industry_total(RESOURCE_LUXURY_GOODS) > 0;

    const e_trade_status status = g_city.resource.trade_status[RESOURCE_LUXURY_GOODS];
    const bool imports = (status == TRADE_STATUS_IMPORT || status == TRADE_STATUS_IMPORT_AS_NEEDED);
    for (int id = 1; imports && id < MAX_CITIES; id++) {
        const empire_city& city = cities[id];
        if (!city.in_use || !city.is_open || !city.sells_resource[RESOURCE_LUXURY_GOODS]) {
            continue;
        }
        if (get_route(city.route_id).limit(RESOURCE_LUXURY_GOODS) <= 0) {
            continue;
        }
        const auto& table = empire_city_cultures.luxury_kind;
        const int kind = (city.name_id < table.size()) ? table[city.name_id] : LUXURY_JEWELRY;
        if (kind < LUXURY_KIND_MAX) {
            kinds[kind]++;
        }
    }

    int count = 0;
    for (int kind : kinds) {
        count += (kind != 0) ? 1 : 0;
    }
    return count;
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
    OZZY_PROFILER_FUNCTION();
        
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

    city_resource_handle hresource{ resource };
    const int stored = g_city.resource.yards_stored(resource);
    switch (hresource.trade_status()) {
    case TRADE_STATUS_EXPORT:
        if (stored <= hresource.trading_amount()) {
            return false;
        }
        break;

    case TRADE_STATUS_EXPORT_SURPLUS:
        if (stored <= city_trade_export_keep(resource)) {
            return false;
        }
        break;

    default:
        return false;
    }

    return city_id == 0 || city->buys_resource[resource];
}

bool empire_t::can_import_resource_from_city(int city_id, e_resource resource) {
    empire_city* city = this->city(city_id);
    if (!city->sells_resource[resource]) {
        return false;
    }

    city_resource_handle hresource{ resource };
    int status = hresource.trade_status();
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

    return g_city.resource.yards_stored(resource) < import_stock_limit(resource);
}

int empire_t::import_stock_limit(e_resource resource) {
    city_resource_handle hresource{ resource };
    if (hresource.trade_status() == TRADE_STATUS_IMPORT_AS_NEEDED) {
        return city_trade_export_keep(resource);
    }

    return hresource.trading_amount();
}

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
    int city_id = args.next_int(0);
    
    empire_city* city = g_empire.city(city_id);
    if (city && city->in_use && city->can_trade()) {
        city->set_under_siege(true);
        out.printf("City %d is now under siege!\n", city_id);
    } else {
        out.printf("City %d cannot be sieged!\n", city_id);
    }
}

declare_console_command_p(end_siege) {
    int city_id = args.next_int(0);
    
    if (city_id == 0) {
        g_empire.end_all_sieges();
        out.println("All sieges ended!");
    } else {
        g_empire.end_siege(city_id);
        out.printf("Siege ended for city %d\n", city_id);
    }
}

declare_console_command_p(list_cities) {
    out.println("Empire Cities Status:");
    for (int i = 0; i < empire_t::MAX_CITIES; i++) {
        empire_city* city = g_empire.city(i);
        if (city && city->in_use) {
            out.printf("City %d: Type=%d, Open=%s, Sieged=%s, CanTrade=%s\n", i, (int)city->type,
                       city->is_open ? "Yes" : "No",
                       city->is_sieged() ? "Yes" : "No",
                       city->can_trade() ? "Yes" : "No");
        }
    }
}

int empire_t::random_city() {
    svector<empire_city*, 32> valid_cities;
    select_cities(valid_cities, [](empire_city* c) { return c->in_use; });

    if (valid_cities.empty()) {
        return -1;
    }

    const uint32_t h
      = random_hash(g_simulation.simtime.absolute_day(true), (uint32_t)valid_cities.size(), RANDOM_SALT_EMPIRE_CITY);
    return valid_cities[h % valid_cities.size()]->name_id;
}
