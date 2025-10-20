#pragma once

#include "empire_city.h"
#include "game/resource.h"
#include "core/custom_span.hpp"
#include "trade_route.h"
#include "core/svector.h"

struct mission_id_t;

class empire_t {
public:
    enum {
        MAX_CITIES = 61,
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
    int get_city_for_trade_route(int route_id);
    bool is_trade_route_open(int route_id);
    int trade_route_for_city(int city_id);
    void reset_yearly_trade_amounts();
    int get_city_for_object(int empire_object_id);
    int count_beer_sources();
    void expand();
    int get_city_vulnerable();
    void end_siege(int city_id);
    void end_all_sieges();

    void load_mission_metadata(const mission_id_t &missionid);
    void update_month();

    empire_city *city(int city_id);
    empire_city *city(pcstr name);

    custom_span<empire_city> get_cities() { return make_span(cities); }
    custom_span<trade_route> get_routes() { return make_span(trade_routes.routes); }

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

    int random_city() {
        svector<empire_city*, 32> valid_cities;
        select_cities(valid_cities, [] (empire_city *c) { return c->in_use; });

        if (valid_cities.empty()) {
            return -1;
        }

        return valid_cities[rand() % valid_cities.size()]->name_id;
    }

    inline trade_route &get_route(int route_id) {
        route_id = std::max(route_id, 0);
        assert(route_id < MAX_ROUTES);
        return trade_routes.routes[route_id];
    }

    struct {
        trade_route routes[MAX_ROUTES] = {};
    } trade_routes;

private:
    empire_city cities[MAX_CITIES] = {};
};

extern empire_t g_empire;