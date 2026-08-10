#include "empire_object.h"

#include "core/calc.h"
#include "core/log.h"
#include "core/string.h"
#include "core/svector.h"
#include "empire/empire.h"
#include "empire/trade_route.h"
#include "empire/type.h"
#include "empire/empire_city.h"
#include "graphics/image.h"
#include "graphics/elements/lang_text.h"
#include "io/gamefiles/lang.h"
#include "io/gamestate/boilerplate.h"
#include "io/io_buffer.h"
#include "io/manager.h"
#include "scenario/empire.h"
#include "game/game.h"
#include "dev/debug.h"

#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <cmath>

#define MAX_OBJECTS 200
#define MAX_ROUTES 20
#define EMPIRE_REGION_NAME_SCAN 128

full_empire_object g_empire_objects[MAX_OBJECTS];
std::array<map_route_object, 50> g_empire_route_objects;

void empire_t::foreach_object(std::function<void(int object_index, const empire_object&)> callback) {
    auto& objects = g_empire_objects;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use)
            callback(i, objects[i].obj);
    }
}

void empire_t::hide_non_city_objects() {
    // Clear all non-city map objects so mission JS can fully redefine them
    // (texts, ornaments, battle icons, land/sea route markers, armies).
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (g_empire_objects[i].obj.type == EMPIRE_OBJECT_CITY) {
            continue;
        }
        g_empire_objects[i].in_use = 0;
    }
}

void empire_t::hide_unused_city_objects() {
    // Drop city map icons that are not in the scripted cities[] list.
    for (int i = 0; i < MAX_OBJECTS; i++) {
        full_empire_object &full = g_empire_objects[i];
        if (!full.in_use || full.obj.type != EMPIRE_OBJECT_CITY) {
            continue;
        }

        empire_city *city = g_empire.city(full.city_name_id);
        if (!city || !city->in_use) {
            full.in_use = 0;
        }
    }
}

int empire_t::alloc_empire_object() {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (g_empire_objects[i].in_use) {
            continue;
        }
        g_empire_objects[i] = {};
        g_empire_objects[i].obj.id = i;
        g_empire_objects[i].in_use = 1;
        return i;
    }
    logs::error("empire: no free map object slots");
    return -1;
}

full_empire_object *empire_t::ref_full_object(int object_id) {
    if (object_id < 0 || object_id >= MAX_OBJECTS) {
        return nullptr;
    }
    return &g_empire_objects[object_id];
}

int empire_t::find_region_name_id(pcstr name) const {
    if (!name || !name[0]) {
        return -1;
    }
    for (int id = 0; id < EMPIRE_REGION_NAME_SCAN; id++) {
        pcstr s = lang_get_string(196, id);
        if (!s || !s[0]) {
            continue;
        }
        if (string_compare_case_insensitive(s, name) == 0) {
            return id;
        }
    }
    return -1;
}

int empire_t::find_city_name_id(pcstr name) const {
    if (!name || !name[0]) {
        return -1;
    }

    // City slot index == lang id (group 195 old names / 21 new names).
    for (int id = 0; id < empire_t::MAX_CITIES; id++) {
        pcstr old_name = lang_get_string(195, id);
        if (old_name && old_name[0] && string_compare_case_insensitive(old_name, name) == 0) {
            return id;
        }
        pcstr new_name = lang_get_string(21, id);
        if (new_name && new_name[0] && string_compare_case_insensitive(new_name, name) == 0) {
            return id;
        }
    }
    return -1;
}

static int find_city_object_index(int city_name_id) {
    for (int i = 0; i < MAX_OBJECTS; i++) {
        const full_empire_object &full = g_empire_objects[i];
        if (full.obj.type != EMPIRE_OBJECT_CITY) {
            continue;
        }
        if (full.city_name_id == city_name_id) {
            return i;
        }
    }
    return -1;
}

static void sync_city_object_size(full_empire_object *full, e_empire_city city_type) {
    const int image_id = empire_city_images.image_id(city_type, false);
    if (image_id <= 0) {
        return;
    }
    full->obj.image_id = image_id;
    if (full->obj.expanded.image_id <= 0) {
        const int expanded_id = empire_city_images.image_id(city_type, true);
        full->obj.expanded.image_id = expanded_id > 0 ? expanded_id : image_id;
    }
    const image_t *img = image_get(image_id);
    if (img) {
        full->obj.width = img->width;
        full->obj.height = img->height;
    }
}

static void apply_scripted_trade_route_limits(empire_city *city, archive entry) {
    if (!city || !city->can_trade()) {
        return;
    }

    trade_route &route = city->get_route();
    bool has_explicit_limits = false;

    // route_limits [ { resource: RESOURCE_FIGS, limit: 4000, traded: 0 } ]
    entry.r_array("route_limits", [&](archive lim) {
        const e_resource res = lim.r_type<e_resource>("resource", RESOURCE_NONE);
        if (res <= RESOURCE_NONE || res >= RESOURCES_MAX) {
            return;
        }

        has_explicit_limits = true;
        const int limit = lim.r_int("limit", -1);
        if (limit >= 0) {
            route.set_limit(res, limit);
        }

        const int traded = lim.r_int("traded", -1);
        if (traded >= 0) {
            route.set_traded(res, traded);
        } else if (limit >= 0) {
            // New limit without traded → start year fresh.
            route.set_traded(res, 0);
        }
    });

    if (has_explicit_limits) {
        return;
    }

    // No route_limits: fill missing sells/buys with default yearly tier.
    constexpr int k_default_limit = 1500;
    for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
        if (city->sells_resource[resource] || city->buys_resource[resource]) {
            if (route.limit(resource, trade_route::e_limit_base_only) <= 0) {
                route.init(resource, k_default_limit);
            }
        }
    }
}

void empire_t::load_empire_cities(archive arch) {
    arch.r_array("cities", [](archive entry) {
        const int name_id_field = entry.r_int("name_id", -1);
        xstring name = entry.r_string("name");

        int name_id = name_id_field;
        if (name_id < 0) {
            name_id = g_empire.find_city_name_id(name.c_str());
        }
        if (name_id < 0 || name_id >= empire_t::MAX_CITIES) {
            logs::info("empire: unknown city name '%s'", name.c_str() ? name.c_str() : "");
            return;
        }

        empire_city *city = g_empire.city(name_id);
        if (!city) {
            return;
        }

        // pos / idx → full map-object create or replace; otherwise patch an existing pak city.
        const bool has_pos = !std::holds_alternative<archive::variant_none_t>(entry.r_variant("pos"));
        const int object_idx = entry.r_int("idx", -1);
        const bool full_define = has_pos || object_idx >= 0;

        full_empire_object *full = nullptr;
        int object_id = -1;

        if (full_define) {
            object_id = object_idx >= 0 ? object_idx : find_city_object_index(name_id);
            if (object_id < 0 && city->name_id == name_id
                && city->empire_object_id >= 0 && city->empire_object_id < MAX_OBJECTS
                && g_empire_objects[city->empire_object_id].obj.type == EMPIRE_OBJECT_CITY
                && g_empire_objects[city->empire_object_id].city_name_id == name_id) {
                object_id = city->empire_object_id;
            }

            const bool fresh_slot = (object_id < 0);

            if (object_id < 0) {
                object_id = g_empire.alloc_empire_object();
            }
            full = object_id >= 0 ? g_empire.ref_full_object(object_id) : nullptr;

            if (!full) {
                logs::info("empire: failed to allocate city object for '%s'", name.c_str() ? name.c_str() : "");
                return;
            }

            full->in_use = 1;
            full->obj.id = object_id;
            full->obj.type = EMPIRE_OBJECT_CITY;
            full->city_name_id = name_id;
            full->obj.pos = entry.r_vec2i("pos", full->obj.pos);
            const vec2i expanded_fallback = (full->obj.expanded.pos.x || full->obj.expanded.pos.y)
                ? full->obj.expanded.pos
                : full->obj.pos;
            full->obj.expanded.pos = entry.r_vec2i("expanded_pos", expanded_fallback);
            full->obj.text_align = entry.r_int("text_align", full->obj.text_align);
            full->obj.trade_route_id = (uint8_t)entry.r_int("route", full->obj.trade_route_id);
            full->trade_route_open = entry.r_bool("is_open", full->trade_route_open != 0) ? 1 : 0;
            full->trade_route_cost = entry.r_int("cost_to_open", full->trade_route_cost);

            city->in_use = 1;
            city->name_id = name_id;
            city->empire_object_id = object_id;
            city->route_id = full->obj.trade_route_id;
            city->is_open = full->trade_route_open != 0;
            city->cost_to_open = full->trade_route_cost;

            const int type_value = entry.r_int("type", -1);
            if (type_value >= EMPIRE_CITY_OURS && type_value < EMPIRE_CITY_COUNT) {
                city->type = (e_empire_city)type_value;
            } else if (fresh_slot) {
                city->type = EMPIRE_CITY_EGYPTIAN_TRADING;
            }
            full->city_type = city->type;
        } else {
            object_id = find_city_object_index(name_id);
            if (object_id < 0 && city->name_id == name_id
                && city->empire_object_id >= 0 && city->empire_object_id < MAX_OBJECTS
                && g_empire_objects[city->empire_object_id].obj.type == EMPIRE_OBJECT_CITY
                && g_empire_objects[city->empire_object_id].city_name_id == name_id) {
                object_id = city->empire_object_id;
            }
            if (object_id < 0 || object_id >= MAX_OBJECTS
                || g_empire_objects[object_id].obj.type != EMPIRE_OBJECT_CITY) {
                logs::info("empire: city '%s' has no pak object; add pos:[x,y] for full define",
                    name.c_str() ? name.c_str() : "");
                return;
            }
            full = &g_empire_objects[object_id];
            full->in_use = 1;
            city->in_use = 1;
            city->name_id = name_id;
            city->empire_object_id = object_id;
        }

        entry.r(*city);

        // Keep object in sync after archive_load may change type / trade / route fields.
        full->city_type = city->type;
        full->city_name_id = city->name_id;
        full->obj.trade_route_id = (uint8_t)std::clamp(city->route_id, 0, MAX_ROUTES - 1);
        city->route_id = full->obj.trade_route_id;
        full->trade_route_open = city->is_open ? 1 : 0;
        full->trade_route_cost = city->cost_to_open;

        if (has_pos && full->obj.expanded.pos.x == 0 && full->obj.expanded.pos.y == 0) {
            full->obj.expanded.pos = full->obj.pos;
        }

        sync_city_object_size(full, city->type);
        city->name_str = empire_city::get_display_name(city->name_id);
        city->check_attributes();

        if (city->can_trade()) {
            g_empire.set_trade_route_type(city->route_id, city->is_sea_trade);
            apply_scripted_trade_route_limits(city, entry);
        }
    });
}

void empire_t::clear_route_objects() {
    for (auto &route : g_empire_route_objects) {
        route = {};
    }
}

void empire_t::load_empire_routes(archive arch) {
    arch.r_array("empire_routes", [](archive entry) {
        const int route_id = entry.r_int("route", entry.r_int("route_id", -1));
        if (route_id < 0 || route_id >= (int)g_empire_route_objects.size()) {
            logs::info("empire: invalid empire_routes id=%d", route_id);
            return;
        }

        map_route_object &route = g_empire_route_objects[route_id];
        route = {};
        route.in_use = true;

        // 1 = land, 2 = sea (same as pak). Also accept is_sea bool.
        int route_type = entry.r_int("route_type", entry.r_int("type", 0));
        if (route_type != 1 && route_type != 2) {
            route_type = entry.r_bool("is_sea", false) ? 2 : 1;
        }
        route.route_type = (char)route_type;

        std::vector<vec2i> points = entry.r_array_vec2i("points");
        const int max_points = (int)std::size(route.points);
        const int count = std::min((int)points.size(), max_points);
        for (int i = 0; i < count; i++) {
            route.points[i].p = points[i];
            route.points[i].is_in_use = true;
        }
        route.num_points = (unsigned char)count;
        route.length = entry.r_int("length", 0);
        route.deviation = entry.r_int("deviation", 0);
        route.path_length = route.calc_length();
        if (route.length <= 0) {
            route.length = route.path_length;
        }

        if (route.num_points == 0) {
            logs::info("empire: empire_routes[%d] has no points", route_id);
            route.in_use = false;
        }
    });
}

static full_empire_object *begin_script_map_object(archive arch, e_empire_object type) {
    const int idx = arch.r_int("idx", -1);
    full_empire_object *full = nullptr;
    if (idx >= 0) {
        full = g_empire.ref_full_object(idx);
        if (!full) {
            logs::info("empire: invalid map object idx=%d", idx);
            return nullptr;
        }
    } else {
        const int allocated = g_empire.alloc_empire_object();
        if (allocated < 0) {
            return nullptr;
        }
        full = g_empire.ref_full_object(allocated);
    }

    full->in_use = 1;
    if (idx >= 0) {
        full->obj.id = idx;
    }
    full->obj.type = type;
    full->obj.pos = arch.r_vec2i("pos", full->obj.pos);

    // image: raw tid, or image_desc ({pack,id} / {path} / "path")
    image_desc img_desc;
    if (arch.r_desc("image", img_desc) && img_desc.valid()) {
        full->obj.image_id = img_desc.tid();
    } else {
        full->obj.image_id = arch.r_int("image", full->obj.image_id);
    }

    full->obj.expanded.pos = arch.r_vec2i("expanded_pos", full->obj.expanded.pos);
    if (full->obj.expanded.pos.x == 0 && full->obj.expanded.pos.y == 0) {
        full->obj.expanded.pos = full->obj.pos;
    }

    image_desc expanded_img;
    if (arch.r_desc("expanded_image", expanded_img) && expanded_img.valid()) {
        full->obj.expanded.image_id = expanded_img.tid();
    } else {
        full->obj.expanded.image_id = arch.r_int("expanded_image", full->obj.expanded.image_id);
    }
    if (full->obj.expanded.image_id <= 0) {
        full->obj.expanded.image_id = full->obj.image_id;
    }

    full->obj.text_align = arch.r_int("text_align", full->obj.text_align);
    return full;
}

void empire_t::load_empire_texts(archive arch) {
    arch.r_array("empire_texts", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_TEXT);
        if (!full) {
            return;
        }

        const int name_id = entry.r_int("name_id", -1);
        if (name_id >= 0) {
            full->city_name_id = name_id;
            full->text_key = {};
            return;
        }

        // Text key as [group, id] (e.g. [196, 11] for SINAI) — same pattern as mission tooltips.
        const vec2i text_key = entry.r_vec2i("name", {-1, -1});
        if (text_key.x >= 0 && text_key.y >= 0) {
            full->city_name_id = text_key.y;
            full->text_key = {};
            return;
        }

        xstring name = entry.r_string("name");
        if (!!name && name[0] == '#') {
            const xstring resolved = lang_xtext_from_key(name);
            if (!resolved || resolved == name) {
                logs::info("empire: unknown region text key '%s'", name.c_str());
                full->in_use = 0;
                return;
            }
            full->text_key = name;
            return;
        }

        const int resolved = g_empire.find_region_name_id(name.c_str());
        if (resolved < 0) {
            logs::info("empire: unknown region text name '%s'", name.c_str() ? name.c_str() : "");
            full->in_use = 0;
            return;
        }
        full->city_name_id = resolved;
        full->text_key = {};
    });
}

void empire_t::load_empire_ornaments(archive arch) {
    arch.r_array("empire_ornaments", [](archive entry) {
        begin_script_map_object(entry, EMPIRE_OBJECT_ORNAMENT);
    });
}

void empire_t::load_empire_battle_icons(archive arch) {
    arch.r_array("empire_battle_icons", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_BATTLE_ICON);
        if (!full) {
            return;
        }
        full->obj.invasion_path_id = entry.r_int("path", full->obj.invasion_path_id);
        full->obj.invasion_years = entry.r_int("years", full->obj.invasion_years);
    });
}

void empire_t::load_empire_land_routes(archive arch) {
    arch.r_array("empire_land_routes", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_LAND_TRADE_ROUTE);
        if (!full) {
            return;
        }
        full->obj.trade_route_id = (uint8_t)entry.r_int("route", full->obj.trade_route_id);
    });
}

void empire_t::load_empire_sea_routes(archive arch) {
    arch.r_array("empire_sea_routes", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_SEA_TRADE_ROUTE);
        if (!full) {
            return;
        }
        full->obj.trade_route_id = (uint8_t)entry.r_int("route", full->obj.trade_route_id);
    });
}

void empire_t::load_empire_kingdome_armies(archive arch) {
    arch.r_array("empire_kingdome_armies", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_KINGDOME_ARMY);
        if (!full) {
            return;
        }
        full->obj.distant_battle_travel_months = entry.r_int("months", full->obj.distant_battle_travel_months);
    });
}

void empire_t::load_empire_enemy_armies(archive arch) {
    arch.r_array("empire_enemy_armies", [](archive entry) {
        full_empire_object *full = begin_script_map_object(entry, EMPIRE_OBJECT_ENEMY_ARMY);
        if (!full) {
            return;
        }
        full->obj.distant_battle_travel_months = entry.r_int("months", full->obj.distant_battle_travel_months);
    });
}

static bool is_trade_city(int index) {
    auto& objects = g_empire_objects;
    if (objects[index].obj.type != EMPIRE_OBJECT_CITY)
        return 0;

    return (objects[index].city_type == EMPIRE_CITY_OURS || objects[index].city_type == EMPIRE_CITY_PHARAOH_TRADING
            || objects[index].city_type == EMPIRE_CITY_EGYPTIAN_TRADING
            || objects[index].city_type == EMPIRE_CITY_FOREIGN_TRADING);
}

static int get_trade_amount_code(int index, int resource) {
    auto& objects = g_empire_objects;
    if (!is_trade_city(index))
        return 0;

    if (FILEIO.get_file_version() < 160) {
        int result = 0;
        if (resource < 32) { // only holds data up to 31 (sandstone)
            int resource_flag = 1 << resource;
            if (objects[index].trade40 & resource_flag)
                result = 3;
            else if (objects[index].trade25 & resource_flag)
                result = 2;
            else if (objects[index].trade15 & resource_flag)
                result = 1;
        }
        objects[index].trade_demand[resource] = result; // also record into post-160 format automatically
        return result;
    } else
        return objects[index].trade_demand[resource];
}

bool empire_t::is_sea_trade_route(int route_id) const {
    const auto& route = get_route_object(route_id);
    return route.route_type == 2;
}

void empire_t::set_trade_route_type(int route_id, bool is_sea_route) {
    auto &route = ref_route_object(route_id);
    route.route_type = is_sea_route ? 2 : 1;
}

void empire_t::init_cities() {
    auto& objects = g_empire_objects;

    clear_cities_data();
    //    int route_index = 1;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].in_use || objects[i].obj.type != EMPIRE_OBJECT_CITY)
            continue;

        full_empire_object* obj = &objects[i];
        obj->obj.trade_route_id = std::clamp<uint8_t>(obj->obj.trade_route_id, 0, MAX_ROUTES - 1);
        empire_city* city = g_empire.city(obj->city_name_id);
        if (!city) {
            logs::warn("empire: skip city object %d with invalid city_name_id=%d", i, obj->city_name_id);
            continue;
        }
        city->in_use = 1;
        city->type = obj->city_type;
        city->name_id = obj->city_name_id;
        city->name_str = empire_city::get_display_name(obj->city_name_id);

        city->route_id = obj->obj.trade_route_id;
        city->is_open = obj->trade_route_open;
        city->cost_to_open = obj->trade_route_cost;
        city->is_sea_trade = is_sea_trade_route(obj->obj.trade_route_id);

        for (e_resource resource = RESOURCES_MIN; resource < RESOURCES_MAX; ++resource) {
            city->sells_resource[resource] = false;
            city->buys_resource[resource] = false;
            if (!is_trade_city(i)) {
                continue;
            }

            city->sells_resource[resource] = g_empire.city_sells_resource(i, resource, true);
            city->buys_resource[resource] = g_empire.city_buys_resource(i, resource, true);

            int amount;
            switch (get_trade_amount_code(i, resource)) {
            case 1:
                amount = 1500;
                break;
            case 2:
                amount = 2500;
                break;
            case 3:
                amount = 4000;
                break;
            default:
                amount = 0;
                break;
            }

            city->get_route().init(resource, amount);
        }

        city->trader_entry_delay = 4;
        city->trader_figure_ids[0] = 0;
        city->trader_figure_ids[1] = 0;
        city->trader_figure_ids[2] = 0;
        city->empire_object_id = i;
        city->max_traders = 1;
    }
}

int empire_t::init_distant_battle_travel_months(int object_type) {
    auto& objects = g_empire_objects;
    int month = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use && objects[i].obj.type == object_type) {
            month++;
            objects[i].obj.distant_battle_travel_months = month;
        }
    }
    return month;
}

const full_empire_object* empire_t::get_full_object(int object_id) const {
    auto& objects = g_empire_objects;
    return &objects[object_id];
}

const empire_object* empire_t::get_object(int object_id) const {
    auto& objects = g_empire_objects;
    return &objects[object_id].obj;
}

const empire_object* empire_t::ourcity_object() const {
    auto const &cities = g_empire.get_cities();
    auto it = std::find_if(cities.begin(), cities.end(), [] (auto &city) { return (city.in_use && (city.type == EMPIRE_CITY_OURS)); });

    verify_no_crash(it != cities.end());
    return it->get_empire_object();
}

const empire_object* empire_t::get_battle_icon(int path_id, int year) {
    auto& objects = g_empire_objects;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use) {
            empire_object* obj = &objects[i].obj;
            if (obj->type == EMPIRE_OBJECT_BATTLE_ICON && obj->invasion_path_id == path_id
                && obj->invasion_years == year) {
                return obj;
            }
        }
    }
    return 0;
}

int empire_t::get_max_invasion_path() {
    auto& objects = g_empire_objects;
    int max_path = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (objects[i].in_use && objects[i].obj.type == EMPIRE_OBJECT_BATTLE_ICON) {
            if (objects[i].obj.invasion_path_id > max_path)
                max_path = objects[i].obj.invasion_path_id;
        }
    }
    return max_path;
}

int empire_t::get_closest_object(vec2i pos) const {
    auto& objects = g_empire_objects;
    int min_dist = 10000;
    int min_obj_id = 0;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        if (!objects[i].in_use) {
            continue;
        }
        const empire_object* obj = &objects[i].obj;
        vec2i obj_pos;
        if (scenario_empire_is_expanded()) {
            obj_pos = obj->expanded.pos;
        } else {
            obj_pos = obj->pos;
        }

        if (obj_pos.x - 8 > pos.x || obj_pos.x + obj->width + 8 <= pos.x) {
            continue;
        }

        if (obj_pos.y - 8 > pos.y || obj_pos.y + obj->height + 8 <= pos.y) {
            continue;
        }

        if (obj->type == EMPIRE_OBJECT_CITY) {
            const int city_id = get_city_for_object(i);
            const empire_city* ecity = city_id ? g_empire.city(city_id) : nullptr;
            if (!ecity || !ecity->is_selectable_on_empire_map()) {
                continue;
            }
        }

        int dist = calc_maximum_distance(pos, vec2i(obj_pos.x + obj->width / 2, obj_pos.y + obj->height / 2));
        if (dist < min_dist) {
            min_dist = dist;
            min_obj_id = i + 1;
        }
    }
    return min_obj_id;
}

void empire_t::object_set_expanded(int object_id, e_empire_city new_city_type) {
    auto& objects = g_empire_objects;
    objects[object_id].city_type = new_city_type;
    const int image_id = empire_city_images.image_id(new_city_type, true);
    if (image_id > 0) {
        objects[object_id].obj.expanded.image_id = image_id;
    }
}

bool empire_t::city_buys_resource(int object_id, e_resource resource, bool from_raw_object) {
    auto& objects = g_empire_objects;
    if (object_id == -1)
        return false;

    if (from_raw_object) {
        const full_empire_object* object = &objects[object_id];
        for (int i = 0; i < EMPIRE_OBJ_MAX_BOUGHT_RESOURCES; i++) {
            if (object->city_buys_resource[i] == resource)
                return true;
        }
        return false;
    } 

    int city_id = g_empire.get_city_for_object(object_id);
    const empire_city* city = g_empire.city(city_id);
    return city->buys_resource[resource];
}

bool empire_t::city_sells_resource(int object_id, e_resource resource, bool from_raw_object) {
    auto& objects = g_empire_objects;
    if (object_id == -1) {
        return false;
    }

    if (from_raw_object) {
        const full_empire_object* object = &objects[object_id];
        for (int i = 0; i < EMPIRE_OBJ_MAX_SOLD_RESOURCES; i++) {
            if (object->city_sells_resource[i] == resource)
                return true;
        }
        return false;
    } 
    
    int city_id = g_empire.get_city_for_object(object_id);
    const empire_city* city = g_empire.city(city_id);
    return city->sells_resource[resource];
}

static int get_animation_offset(int image_id, int current_index) {
    if (current_index <= 0)
        current_index = 1;

    const image_t* img = image_get(image_id);
    int animation_speed = img->animation.speed_id;
    if (!game.animation_should_advance(animation_speed))
        return current_index;

    if (img->animation.can_reverse) {
        int is_reverse = 0;
        if (current_index & 0x80)
            is_reverse = 1;

        int current_sprite = current_index & 0x7f;
        if (is_reverse) {
            current_index = current_sprite - 1;
            if (current_index < 1) {
                current_index = 1;
                is_reverse = 0;
            }
        } else {
            current_index = current_sprite + 1;
            if (current_index > img->animation.num_sprites) {
                current_index = img->animation.num_sprites;
                is_reverse = 1;
            }
        }
        if (is_reverse)
            current_index = current_index | 0x80;

    } else {
        // Absolutely normal case
        current_index++;
        if (current_index > img->animation.num_sprites)
            current_index = 1;
    }
    return current_index;
}

int empire_t::update_animation(int object_index, const empire_object &obj, int image_id) {
    auto& objects = g_empire_objects;
    objects[object_index].obj.animation_index = get_animation_offset(image_id, obj.animation_index);
    return objects[object_index].obj.animation_index & 0x7f;
}

const map_route_object& empire_t::get_route_object(int id) const {
    return g_empire_route_objects[id];
}

map_route_object &empire_t::ref_route_object(int id) {
    return g_empire_route_objects[id];
}

void empire_t::fix_trade_routes() {
    for (int id = 0; id < g_empire_route_objects.max_size(); id++) {
        map_route_object &obj = g_empire_route_objects[id];
        obj.improve_route();
    }
}

io_buffer* iob_empire_map_objects = new io_buffer([](io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_objects");
    auto& objects = g_empire_objects;
    int last_object_was_used = 1;
    for (int i = 0; i < MAX_OBJECTS; i++) {
        full_empire_object* full = &objects[i];
        empire_object* obj = &full->obj;
        obj->id = i;
        //
        iob->bind(BIND_SIGNATURE_UINT8, &obj->type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->in_use);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->animation_index);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.y);
        iob->bind(BIND_SIGNATURE_INT16, &obj->width);
        iob->bind(BIND_SIGNATURE_INT16, &obj->height);
        iob->bind(BIND_SIGNATURE_INT16, &obj->image_id);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.image_id);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->distant_battle_travel_months);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->text_align);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded.pos.y);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_name_id);
        iob->bind_u8(obj->trade_route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &full->trade_route_open);
        iob->bind(BIND_SIGNATURE_INT16, &full->trade_route_cost);

        for (int r = 0; r < EMPIRE_OBJ_MAX_SOLD_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_sells_resource[r]);
        }
        iob->bind____skip(8);
        for (int r = 0; r < EMPIRE_OBJ_MAX_BOUGHT_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_buys_resource[r]);
        }

        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_path_id);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_years);

        // TODO: WRITE
        if (FILEIO.get_file_version() < 160) {
            iob->bind____skip(2);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade40);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade25);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade15);
        } else {
            for (int r = 0; r < RESOURCES_MAX; r++) {
                iob->bind(BIND_SIGNATURE_UINT8, &full->trade_demand[r]);
            }
        }

        if (iob->is_read_access()) {
            if (last_object_was_used) {
                last_object_was_used = full->in_use;
            } else {
                full->in_use = 0;
            }
        }
    }
});

io_buffer* iob_empire_map_routes = new io_buffer([](io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_routes");
    for (int id = 0; id < g_empire_route_objects.max_size(); id++) {
        map_route_object& obj = g_empire_route_objects[id];

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[0]); // 05 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[1]); // 00 00 00 00

        for (int i = 0; i < 50; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.x);
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.y);
            iob->bind(BIND_SIGNATURE_UINT8, &obj.points[i].is_in_use);
            iob->bind____skip(1);
        }
        iob->bind(BIND_SIGNATURE_UINT32, &obj.length);

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_00); // 00 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_01); // FF FF FF FF

        iob->bind(BIND_SIGNATURE_UINT8, &obj.route_type); // 1 = land; 2 = sea;
        iob->bind(BIND_SIGNATURE_UINT8, &obj.num_points);
        iob->bind(BIND_SIGNATURE_UINT8, &obj.in_use);

        iob->bind(BIND_SIGNATURE_UINT8, &obj.unk_03);

        // Not stored in pak/save — only set from JS empire_routes.
        obj.deviation = 0;
        obj.path_length = obj.calc_length();
    }
});

void full_empire_object::add_sell_resource(e_resource r) {
    // check resource exist in set
    auto it = std::find(std::begin(city_sells_resource), std::end(city_sells_resource), r);
    if (it != std::end(city_sells_resource)) {
        return;
    }

    // find empty place
    it = std::find(std::begin(city_sells_resource), std::end(city_sells_resource), 0);
    verify_no_crash(it != std::end(city_sells_resource));
    *it = r;
}

int map_route_object::calc_length() {
    if (num_points == 0) {
        return 0;
    }

    float pathlen = 0.f;
    for (int i = 0; i < num_points - 1; i++) {
        const auto route_point = points[0];
        const auto nextup_route_point = points[i + 1];
        vec2i d = nextup_route_point.p - route_point.p;
        pathlen += 0.2f * sqrtf(float(d.x * d.x) + float(d.y * d.y));
    }

    return (int)pathlen;
}

void map_route_object::improve_route() {
    if (!in_use || num_points < 2) {
        return;
    }

    // Copy active points to a temporary vector
    svector<map_route_object::point, 256> temp_points;
    std::copy_n(points, num_points, std::back_inserter(temp_points));

    if (temp_points.size() < 2) {
        return;
    }

    const float max_deviation = (float)std::max(0, deviation);

    // Step 1: Split long segments (> 50). With deviation>0, nudge midpoints off the line.
    bool has_changes = true;
    while (has_changes) {
        has_changes = false;

        for (size_t i = 0; i < temp_points.size() - 1; i++) {
            const vec2i a = temp_points[i].p;
            const vec2i b = temp_points[i + 1].p;
            const float dist = a.dist(b);

            if (dist > 50.0f) {
                vec2i mid_point;
                mid_point.x = (a.x + b.x) / 2;
                mid_point.y = (a.y + b.y) / 2;

                if (max_deviation > 0.f && dist > 0.f) {
                    // Perpendicular unit vector; scale offset by segment length so fine splits wiggle less.
                    const float dx = (float)(b.x - a.x);
                    const float dy = (float)(b.y - a.y);
                    const float px = -dy / dist;
                    const float py = dx / dist;
                    const float t = ((rand() % 2001) - 1000) / 1000.f; // [-1, 1]
                    const float amount = t * max_deviation * std::min(1.f, dist / 200.f);
                    mid_point.x += (int)(px * amount);
                    mid_point.y += (int)(py * amount);
                }

                map_route_object::point new_point;
                new_point.p = mid_point;
                new_point.is_in_use = true;

                temp_points.insert(temp_points.begin() + i + 1, new_point);
                has_changes = true;
                break;
            }
        }

        // Safety check: prevent infinite loop
        if (temp_points.size() > 100) {
            break;
        }
    }

    // Step 2: If we have more than 50 points, remove random points (except first and last)
    while (temp_points.size() > 50) {
        if (temp_points.size() <= 2) {
            break; // Can't remove more
        }

        // Pick a random index between 1 and size-2
        int index_to_remove = 1 + (rand() % (temp_points.size() - 2));
        temp_points.erase(temp_points.begin() + index_to_remove);
    }

    // Copy back the improved points
    num_points = std::min<uint8_t>(temp_points.size(), 50);
    std::copy_n(temp_points.data(), num_points, points);

    path_length = calc_length();
}
