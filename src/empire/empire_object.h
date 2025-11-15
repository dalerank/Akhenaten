#pragma once

#include "empire/type.h"
#include "core/vec2i.h"
#include "game/resource.h"

#include <functional>

struct empire_object {
    int id;
    int type;
    int animation_index;
    vec2i pos;
    int width;
    int height;
    int image_id;
    int text_align;
    struct {
        vec2i pos;
        int image_id;
    } expanded;
    int distant_battle_travel_months;
    uint8_t trade_route_id;
    int invasion_path_id;
    int invasion_years;
};

#define EMPIRE_OBJ_MAX_SOLD_RESOURCES 14
#define EMPIRE_OBJ_MAX_BOUGHT_RESOURCES 8

struct full_empire_object {
    int in_use; // this can be 2, so it's an int!
    e_empire_city city_type;
    int city_name_id;
    int trade_route_open;
    int trade_route_cost;
    e_resource city_sells_resource[EMPIRE_OBJ_MAX_SOLD_RESOURCES];
    e_resource city_buys_resource[EMPIRE_OBJ_MAX_BOUGHT_RESOURCES];
    int trade_demand[RESOURCES_MAX];
    int trade40;
    int trade25;
    int trade15;
    empire_object obj;

    void add_sell_resource(e_resource);
};

void empire_object_init_cities();

int empire_object_init_distant_battle_travel_months(int object_type);

const full_empire_object* empire_get_full_object(int object_id);
const empire_object* empire_object_get(int object_id);
const empire_object* empire_object_get_our_city();

void empire_object_foreach(std::function<void(const empire_object &)> callback);

void empire_object_set_trade_route_type(int route_id, bool is_sea_route);

const empire_object* empire_object_get_battle_icon(int path_id, int year);

int empire_object_get_max_invasion_path();

int empire_object_get_closest(vec2i pos);

void empire_object_set_expanded(int object_id, e_empire_city new_city_type);

bool empire_object_city_buys_resource(int object_id, e_resource resource, bool from_raw_object = false);
bool empire_object_city_sells_resource(int object_id, e_resource resource, bool from_raw_object = false);

int empire_object_update_animation(const empire_object &obj, int image_id);

struct map_route_object {
    int unk_header[2]; // 05 00 00 00 00 00 00 00
    /////
    struct {
        vec2i p;
        bool is_in_use;
    } points[50];
    int length;
    int unk_00; // 00 00 00 00
    int unk_01; // FF FF FF FF
    char route_type;
    unsigned char num_points;
    bool in_use;
    char unk_03; // 00
    int path_length;

    int calc_length();
};

const map_route_object& empire_get_route_object(int id);
map_route_object& empire_ref_route_object(int id);
