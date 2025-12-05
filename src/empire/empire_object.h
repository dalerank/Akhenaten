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

struct map_route_object {
    int unk_header[2]; // 05 00 00 00 00 00 00 00
    struct point {
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
    void improve_route();
};