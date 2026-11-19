#pragma once

#include "building/building.h"

struct event_fire_damage { building_id bid; };
struct event_collase_damage { building_id bid; };
struct event_flooded_damage { building_id bid; };

inline void describe_into(bstring256 &s, const event_fire_damage &ev) {
    s.printf("building=%d", (int)ev.bid);
}
inline void describe_into(bstring256 &s, const event_collase_damage &ev) {
    s.printf("building=%d", (int)ev.bid);
}
inline void describe_into(bstring256 &s, const event_flooded_damage &ev) {
    s.printf("building=%d", (int)ev.bid);
}

struct city_maintenance_t {
    int fire_spread_direction = 0;

    void check_building_destroying();
    void collapse_building(building *b);
    void flood_building(building *b);
    void destroy_by_enemy(building *b);
    void subscribe_events();
    void check_kingdome_access();
    void update_fire_direction();

    int find_nearest_enemy_formation(tile2i tile);
};