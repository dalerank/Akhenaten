#pragma once

#include "empire_city.h"
#include "game/resource.h"
#include "core/span.hpp"

class empire_t {
public:
    enum {
        MAX_CITIES = 61
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
    void reset_yearly_trade_amounts();
    int get_city_for_object(int empire_object_id);
    int count_wine_sources();
    void expand();
    int get_city_vulnerable();

    empire_city *city(int city_id);
    std::span<empire_city> get_cities() { return make_span(cities); }

private:
    empire_city cities[MAX_CITIES] = {};
};

extern empire_t g_empire;