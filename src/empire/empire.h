#pragma once

#include "empire_city.h"
#include "game/resource.h"
#include "core/custom_span.hpp"
#include "trade_route.h"
#include "core/svector.h"
#include "building/building_type.h"

struct mission_id_t;

// OG trade_recommends.txt: what the city keeps of the advisor's goods before it exports, by population.
struct trade_recommend_row {
    int32_t population_below = 0; // 0 = no upper bound (last row)
    int32_t food = 0;
    int32_t pottery = 0;
    int32_t beer = 0;
    int32_t linen = 0;
    int32_t papyrus = 0;
    int32_t luxury_goods = 0;
};
ANK_CONFIG_STRUCT(trade_recommend_row, population_below, food, pottery, beer, linen, papyrus, luxury_goods)

// OG monument_unplaced_needs by the scenario's monument id; building tells a placed slot from an unplaced one.
struct trade_monument_unplaced_need {
    int32_t monument = 0;
    e_building_type building = BUILDING_NONE;
    e_resource resource = RESOURCE_NONE;
    int32_t amount = 0;
    int32_t limestone = 0;
};
ANK_CONFIG_STRUCT(trade_monument_unplaced_need, monument, building, resource, amount, limestone)

struct empire_trade_rules_t {
    // OG trader_size: up to this many traders per city at once, fewer on small routes.
    int32_t max_traders_per_city = 3;
    int32_t trader_limit_small = 1500;
    int32_t trader_limit_medium = 2500;
    int32_t keep_workshop_amount = 200;
    int32_t keep_monument_amount = 500;
    int32_t keep_other_amount = 1000;
    int32_t stock_cap_small = 10000;
    int32_t stock_cap_default = 15000;
    int32_t stock_cap_large = 30000;
    svector<trade_recommend_row, 8> recommends;
    svector<trade_monument_unplaced_need, 40> monument_unplaced_needs;
};
ANK_CONFIG_STRUCT(empire_trade_rules_t, max_traders_per_city, trader_limit_small, trader_limit_medium,
  keep_workshop_amount, keep_monument_amount, keep_other_amount, stock_cap_small, stock_cap_default, stock_cap_large,
  recommends, monument_unplaced_needs)

extern empire_trade_rules_t empire_trade_rules;

class empire_t {
public:
    enum {
        // Classic Pharaoh saves serialize 61 slots (0..60). Cleopatra adds name ids
        // 61+ (Siwi, Maritis, …) — keep headroom for those lang ids as array indices.
        MAX_CITIES = 80,
        MAX_CITIES_CLASSIC = 61,
        MAX_ROUTES = 20
    };

    void generate_traders();
    void clear_cities_data();
    bool can_import_resource(e_resource resource, bool check_if_open);
    bool can_export_resource(e_resource resource, bool check_if_open);
    resource_list importable_resources_from_city(int city_id);
    resource_list exportable_resources_from_city(int city_id);
    bool can_export_resource_to_city(int city_id, e_resource resource);
    bool can_import_resource_from_city(int city_id, e_resource resource);
    int import_stock_limit(e_resource resource);
    int get_city_for_trade_route(int route_id);
    bool is_trade_route_open(int route_id);
    int trade_route_for_city(int city_id);
    void reset_yearly_trade_amounts();
    int get_city_for_object(int empire_object_id) const;
    int count_beer_sources();
    void expand();
    int get_city_vulnerable();
    void end_siege(int city_id);
    void end_all_sieges();

    void load_mission_metadata(const mission_id_t &missionid, bool preserve_runtime = false);
    void update_month();

    void hide_non_city_objects();
    void hide_unused_city_objects();
    void clear_route_objects();
    int alloc_empire_object();
    full_empire_object *ref_full_object(int object_id);
    int find_region_name_id(pcstr name) const;
    int find_city_name_id(pcstr name) const;

    empire_city *city(int city_id);
    empire_city *city(xstring name);

    xspan<empire_city> get_cities() { return make_span(cities); }
    xspan<trade_route> get_routes() { return make_span(trade_routes.routes); }

    template<typename T, typename F>
    void select_cities(T& arr, F func) {
        for (auto &city : get_cities()) {
            if (!city.in_use) {
                continue;
            }

            if (func(&city)) {
                arr.push_back(&city);
            }
        }
    }

    int random_city();

    inline trade_route &get_route(int route_id) {
        route_id = std::max(route_id, 0);
        assert(route_id < MAX_ROUTES);
        return trade_routes.routes[route_id];
    }

    struct {
        trade_route routes[MAX_ROUTES] = {};
    } trade_routes;

    void init_cities();
    void foreach_object(std::function<void(int object_index, const empire_object &)> callback);

    void fix_trade_routes();

    bool is_sea_trade_route(int route_id) const;
    void set_trade_route_type(int route_id, bool is_sea_route);
    int init_distant_battle_travel_months(int object_type);
    const full_empire_object *get_full_object(int object_id) const;
    const empire_object *get_object(int object_id) const;
    const empire_object *ourcity_object() const;

    const empire_object *get_battle_icon(int path_id, int year);
    int get_max_invasion_path();

    int get_closest_object(vec2i pos, int* distance = nullptr) const;
    void object_set_expanded(int object_id, e_empire_city new_city_type);
    bool city_buys_resource(int object_id, e_resource resource, bool from_raw_object);
    bool city_sells_resource(int object_id, e_resource resource, bool from_raw_object);

    int update_animation(int object_index, const empire_object &obj, int image_id);

    const map_route_object &get_route_object(int id) const ;
    map_route_object &ref_route_object(int id);

private:
    void load_empire_cities(archive arch, bool preserve_runtime);
    void load_empire_routes(archive arch);
    void load_empire_texts(archive arch);
    void load_empire_ornaments(archive arch);
    void load_empire_battle_icons(archive arch);
    void load_empire_land_routes(archive arch);
    void load_empire_sea_routes(archive arch);
    void load_empire_kingdome_armies(archive arch);
    void load_empire_enemy_armies(archive arch);

    empire_city cities[MAX_CITIES] = {};
};

extern empire_t g_empire;