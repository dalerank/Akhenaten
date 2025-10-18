#pragma once

#include "core/vec2i.h"
#include "empire/empire_object.h"

struct empire_trader {
    int id;
    int trade_route_id;
    int destination_city_id;
    vec2i current_position;
    int current_route_point;
    int movement_delay;
    bool is_active;
    bool returning_home;
    int animation_frame;
    int direction;

    int32_t bought_amount;
    int32_t bought_value;
    uint16_t bought_resources[RESOURCES_MAX];

    int32_t sold_amount;
    int32_t sold_value;
    uint16_t sold_resources[RESOURCES_MAX];
    
    void update();
    bool is_at_destination() const;
    void complete_trade();
};

class empire_traders_manager {
public:   
    void init();
    void update();
    void create_trader(int trade_route_id, int destination_city_id);
    void remove_trader(int trader_id);
    void clear_all();
    
    std::array<empire_trader, 100> traders;

private:   
    empire_trader* get_free_trader();
    vec2i get_position_on_route(int route_id, int point_index);
};

extern empire_traders_manager g_empire_traders;
